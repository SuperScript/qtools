#include "stralloc.h"
#include "openreadclose.h"
#include "strerr.h"
#include "byte.h"
#include "getconf.h"

static stralloc data = {0};

static void nomem(const char *fatal)
{
  strerr_die2x(111,fatal,"out of memory");
}

int getconf(stralloc *sa,const char *fn,int flagrequired,const char *fatal,const char *dir)
{
  int i;
  int j;
  int k;

  if (!stralloc_copys(&data,""))
    nomem(fatal);
  switch(openreadclose(fn,&data,128)) {
    case -1:
      strerr_die6sys(111,fatal,"unable to read ",dir,"/",fn,": ");
    case 0:
      if (!flagrequired)
	return 0;
      strerr_die5x(100,fatal,dir,"/",fn," does not exist");
  }
  if (!stralloc_append(&data,"\n")) nomem(fatal);
  if (!stralloc_copys(sa,"")) nomem(fatal);
  i = 0;
  for (j = 0;j < data.len;++j)
    if (data.s[j] == '\n') {
      k = j;
      while ((k > i) && ((data.s[k-1] == ' ') || (data.s[k-1] == '\t'))) --k;
      if ((k > i) && (data.s[i] != '#')) {
        if (!stralloc_catb(sa,data.s + i,k - i)) nomem(fatal);
        if (!stralloc_0(sa)) nomem(fatal);
      }
      i = j + 1;
    }
  return 1;
}

int getconf_line(stralloc *sa,const char *fn,int flagrequired,const char *fatal,const char *dir)
{
  if (!getconf(sa,fn,flagrequired,fatal,dir)) return 0;
  sa->len = byte_chr(sa->s,sa->len,0);
  return 1;
}
