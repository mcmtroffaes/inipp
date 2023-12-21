
#include <inipp.h>
#include <sstream>
#include <string>

using namespace inipp;

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  std::string fuzz_input(reinterpret_cast<const char *>(data), size);
  std::istringstream fuzz_stream(fuzz_input);
  Ini<char> ini;
  ini.parse(fuzz_stream);

  return 0;
}