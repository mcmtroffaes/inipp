#pragma once

#include <iostream>
#include <string>
#include <unordered_map>
#include <algorithm> 
#include <functional> 
#include <cctype>
#include <locale>

// trim functions taken from http://stackoverflow.com/a/217605

template <class CharT>
static inline void ltrim(std::basic_string<CharT> & s) {
	s.erase(s.begin(), std::find_if(s.begin(), s.end(),
		std::not1(std::ptr_fun<int, int>(std::isspace))));
}

template <class CharT>
static inline void rtrim(std::basic_string<CharT> & s) {
	s.erase(std::find_if(s.rbegin(), s.rend(),
		std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
}

template<class CharT>
class basic_ini_reader
{
public:
	typedef std::basic_string<CharT> String;
	typedef std::basic_istream<CharT> IStream;
	typedef std::unordered_map<String, String> Values;
	typedef std::unordered_map<String, Values> Sections;
	virtual CharT char_section_start()    const = 0;
	virtual CharT char_section_end()      const = 0;
	virtual CharT char_assign()           const = 0;
	virtual CharT char_comment()          const = 0;
	virtual CharT char_interpol()         const = 0;
	virtual CharT char_interpol_start()   const = 0;
	virtual CharT char_interpol_end()     const = 0;
	virtual String default_section_name() const = 0;
	Sections sections;
	void parse(IStream & is) {
		String line;
		String section;
		while (!is.eof()) {
			std::getline(is, line);
			ltrim(line);
			rtrim(line);
			auto length = line.length();
			if (length > 0) {
				const auto pos = line.find_first_of(char_assign());
				const auto & front = line.front();
				if (front == char_comment()) {
					continue;
				}
				else if (front == char_section_start()) {
					if (line.back() == char_section_end())
						section = line.substr(1, length - 1);
				}
				else if (pos != String::npos) {
					String variable(line.substr(0, pos));
					String value(line.substr(pos + 1, length));
					rtrim(variable);
					ltrim(value);
					sections[section][variable] = value;
				}
			}
		}
	}

	String interpolate(const String & str) const {
		String new_str = str;
		const auto section_iter = sections.find(default_section_name());
		if (section_iter != sections.end()) {
			auto default_values = section_iter->second;
			for (auto other = default_values.cbegin(); other != default_values.cend(); other++) {
			    // see http://stackoverflow.com/a/3418285
				String::size_type pos = 0;
				auto old_str = char_interpol() + (char_interpol_start() + other->first) + char_interpol_end();
				auto new_str = other->second;
				while ((pos = new_str.find(old_str, pos)) != String::npos) {
					new_str.replace(pos, old_str.length(), other->second);
					pos += other->second.length();
				}
			}
		}
		return new_str;
	}
};

class ini_reader : public basic_ini_reader<char> {
public:
	char char_section_start()  const { return '['; };
	char char_section_end()    const { return ']'; };
	char char_assign()         const { return '='; };
	char char_comment()        const { return ';'; };
	char char_interpol()       const { return '%'; };
	char char_interpol_start() const { return '('; };
	char char_interpol_end()   const { return ')'; };
	std::string default_section_name() const { return "DEFAULT"; };
};

class wini_reader : public basic_ini_reader<wchar_t> {
public:
	wchar_t char_section_start()  const { return L'['; };
	wchar_t char_section_end()    const { return L']'; };
	wchar_t char_assign()         const { return L'='; };
	wchar_t char_comment()        const { return L';'; };
	wchar_t char_interpol()       const { return L'%'; };
	wchar_t char_interpol_start() const { return L'('; };
	wchar_t char_interpol_end()   const { return L')'; };
	std::wstring default_section_name() const { return L"DEFAULT"; };
};
