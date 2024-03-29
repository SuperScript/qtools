#include "fmt.h"

unsigned int fmt_strn(register char *s,register const char *t,register unsigned int n)
{
  register unsigned int len;
  char ch;
  len = 0;
  if (s) { while (n-- && (ch = t[len])) s[len++] = ch; }
  else while (n-- && t[len]) len++;
  return len;
}
