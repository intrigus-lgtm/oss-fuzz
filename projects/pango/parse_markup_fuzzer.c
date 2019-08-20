#include <stdint.h>
#include <string.h>
#include <unistd.h>

#include "glib/glib/glib.h"
#include "pango/pango/pangocairo.h"

int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
  GError *error = NULL;
  gchar *text;
  PangoAttrList *attrs;

  gboolean ret = pango_parse_markup(Data, Size, 0, &attrs, &text, NULL, &error);
  if (ret) {
    g_free(text);
  } else {
    g_error_free(error);
  }

  return 0;  // Non-zero return values are reserved for future use.
}
