#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

#include "fuzzer_temp_file.h"
#include "libimobiledevice/common/utils.h"

int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  const char* filename = fuzzer_get_tmpfile(data, size);
  plist_t file_info = NULL;
  plist_read_from_filename(&file_info, filename);
  return 0;
}
