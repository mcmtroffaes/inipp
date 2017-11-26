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

## Default section algorithm

Insert every variable from the default section into every other section, without overwriting existing variables.

## Interpolation algorithm

1. Locally within each section, every occurrence "${variable}" is replaced by "${section:variable}".
2. Every occurrence of "${section:variable}" is replaced by its value.
3. The previous step is repeated until no more replacements are possible, or until the recursion depth (by default, 10) is reached.

