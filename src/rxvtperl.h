/*
 * rxvtperl.h
 */

#ifndef RXVTPERL_H_
#define RXVTPERL_H_

#if ENABLE_PERL
# define SHOULD_INVOKE(htype) perl.should_invoke [htype]
# define HOOK_INVOKE(args) rxvt_perl.invoke args

#include "rxvt.h"

enum data_type {
  DT_END,
  DT_INT,
  DT_LONG,
  DT_STR,
  DT_STR_LEN,
  DT_WCS_LEN,
  DT_XEVENT,
};

enum hook_type {
# define def(sym) HOOK_ ## sym,
# include "hookinc.h"
# undef def
  HOOK_NUM,
};

struct rxvt_perl_term
{
  void *self;
  unsigned long grabtime;
  uint8_t should_invoke[HOOK_NUM];
};

struct rxvt_perl_interp
{
  char **perl_environ;

  ~rxvt_perl_interp ();

  void init ();
  bool invoke (rxvt_term *term, hook_type htype, ...);
  void line_update (rxvt_term *term);
};

extern struct rxvt_perl_interp rxvt_perl;

#else
# define SHOULD_INVOKE(htype) false
# define HOOK_INVOKE(args) false
#endif

#endif

