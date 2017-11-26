# IniPP

Simple header-only C++ ini parser and generator.

[![Build Status](https://travis-ci.org/mcmtroffaes/inipp.svg?branch=develop)](https://travis-ci.org/mcmtroffaes/inipp) [![Build status](https://ci.appveyor.com/api/projects/status/74hf86c4yhtmb1j5/branch/develop?svg=true)](https://ci.appveyor.com/project/mcmtroffaes/inipp/branch/develop)

## Features

* Header-only.
* Both parsing and generating.
* Wide character support for native unicode on Windows.
* Default section support (similar to Python's ConfigParser).
* Interpolation support (i.e. variable substitution, similar to Python's ConfigParser).
* Simple design and implementation.
* Permissive MIT license.

## Example

```
#include <fstream>
#include "inipp.h"

int main() {
	inipp::Ini<char> ini;
	std::ifstream is("example.ini");
	ini.parse(is);
	std::cout << "raw ini file:" << std::endl;
	ini.generate(std::cout);
	ini.default_section(ini.sections["DEFAULT"]);
	ini.interpolate();
	std::cout << "ini file after default section and interpolation:" << std::endl;
	ini.generate(std::cout);
	int compression_level = -1;
	inipp::extract(ini.sections["bitbucket.org"]["CompressionLevel"], compression_level);
	std::cout << "bitbucket.org compression level: " << compression_level << std::endl;
	return 0;
}
```

## Default section algorithm

Insert every variable from the default section into every other section, without overwriting existing variables.

## Interpolation algorithm

1. Locally within each section, every occurrence "${variable}" is replaced by "${section:variable}".
2. Every occurrence of "${section:variable}" is replaced by its value.
3. The previous step is repeated until no more replacements are possible, or until the recursion depth (by default, 10) is reached.

