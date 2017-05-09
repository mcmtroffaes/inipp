#pragma once

#include <iostream>
#include <string>
#include <list>
#include <unordered_map>
#include <algorithm> 
#include <functional> 
#include <cctype>
#include <locale>

namespace inipp {

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

// string replacement function taken from http://stackoverflow.com/a/3418285

template <class CharT>
void replace(std::basic_string<CharT> & str, const std::basic_string<CharT> & from, const std::basic_string<CharT> & to) {
	size_t start_pos = 0;
	while ((start_pos = str.find(from, start_pos)) != std::basic_string<CharT>::npos) {
		str.replace(start_pos, from.length(), to);
		start_pos += to.length();
	}
}

template<class CharT>
class basic_ini_reader
{
public:
	typedef std::basic_string<CharT> String;
	typedef std::basic_istream<CharT> IStream;
	typedef std::unordered_map<String, String> Values;
	typedef std::unordered_map<String, Values> Sections;

	Sections sections;
	std::list<String> errors;

	virtual CharT char_section_start()    const = 0;
	virtual CharT char_section_end()      const = 0;
	virtual CharT char_assign()           const = 0;
	virtual CharT char_comment()          const = 0;
	virtual CharT char_interpol()         const = 0;
	virtual CharT char_interpol_start()   const = 0;
	virtual CharT char_interpol_end()     const = 0;
	virtual String default_section_name() const = 0;

	void generate(std::basic_ostream<CharT> & os) {
		for (auto sec = sections.cbegin(); sec != sections.cend(); sec++) {
			os << char_section_start() << sec->first << char_section_end() << std::endl;
			for (auto val = sec->second.cbegin(); val != sec->second.cend(); val++) {
				os << val->first << char_assign() << val->second << std::endl;
			}
		}
	}

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
						section = line.substr(1, length - 2);
				}
				else if (pos != String::npos) {
					String variable(line.substr(0, pos));
					String value(line.substr(pos + 1, length));
					rtrim(variable);
					ltrim(value);
					sections[section][variable] = value;
				}
				else {
					errors.push_back(line);
				}
			}
		}
	}

	void interpolate(const Values & src, Values & dst) {
		for (auto val = dst.begin(); val != dst.end(); val++) {
			for (auto srcval = src.cbegin(); srcval != src.cend(); srcval++)
				replace(val->second, char_interpol() + (char_interpol_start() + srcval->first + char_interpol_end()), srcval->second);
		}
	}

	void interpolate() {
		auto defsec = sections.find(default_section_name());
		if (defsec != sections.end())
			interpolate(defsec->second, defsec->second);
		for (auto sec = sections.begin(); sec != sections.end(); sec++) {
			if (sec != defsec) {
				interpolate(sec->second, sec->second);
				interpolate(defsec->second, sec->second);
			}
		}
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

} // namespace inipp
