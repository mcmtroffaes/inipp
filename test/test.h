#include "inipp.h"

#include <fstream>
#include <sstream>

using namespace inipp;

template <class CharT>
auto read_all(const std::string & filename) {
	std::basic_ifstream<CharT> is(filename);
	std::basic_stringstream<CharT> sstr;
	sstr << is.rdbuf();
	return sstr.str();
}

template <class CharT>
auto parse(const std::string & filename, basic_ini_reader<CharT> & ini) {
	std::basic_ifstream<CharT> is(filename);
	ini.parse(is);
}

template <class CharT>
void errors(std::basic_ostream<CharT> & os, const basic_ini_reader<CharT> & ini) {
	for (auto err = ini.errors.cbegin(); err != ini.errors.cend(); err++) {
		os << *err << std::endl;
	}
}

template <class CharT>
auto test(const std::string & inifile, basic_ini_reader<CharT> & ini) {
	std::basic_ostringstream<CharT> os;
	parse(inifile, ini);
	os << ">>> ERRORS <<<" << std::endl;
	errors(os, ini);
	os << ">>> GENERATE <<<" << std::endl;
	ini.generate(os);
	os << ">>> INTERPOLATE <<<" << std::endl;
	ini.interpolate();
	ini.generate(os);
	return os.str();
}
