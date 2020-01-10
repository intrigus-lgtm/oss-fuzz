#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

#include "fuzzer_temp_file.h"
#include "libimobiledevice/common/utils.h"

int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  const char* filename = fuzzer_get_tmpfile(data, size);
  char* buffer = NULL;
  uint64_t length;

  if (!filename) return 0;

  buffer_read_from_filename(filename, &buffer, &length);

  if (!buffer) {
    return 0;
  }

  free(buffer);
  return 0;
}
