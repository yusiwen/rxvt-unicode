#ifndef PTYTTY_H
#define PTYTTY_H

#include "rxvt.h"
#include "feature.h"

#if defined(HAVE__GETPTY) || defined(HAVE_OPENPTY) || defined(UNIX98_PTY)
# define NO_SETOWNER_TTYDEV 1
#endif

#if UTMP_SUPPORT
# if !defined(RXVT_UTMPX_FILE) || !defined(HAVE_STRUCT_UTMPX) || defined(__GLIBC__)
#  undef HAVE_UTMPX_H
#  undef HAVE_STRUCT_UTMPX
# endif
# if !defined(RXVT_UTMP_FILE) || !defined(HAVE_STRUCT_UTMP)
#  undef HAVE_UTMP_H
#  undef HAVE_STRUCT_UTMP
# endif

# ifdef HAVE_UTMPX_H
#  include <utmpx.h>
# endif
# ifdef HAVE_UTMP_H
#  include <utmp.h>
# endif

# if ! defined(HAVE_STRUCT_UTMPX) && ! defined(HAVE_STRUCT_UTMP)
#  error cannot build with utmp support - no utmp or utmpx struct found
# endif

# ifdef HAVE_LASTLOG_H
#  include <lastlog.h>
# endif

# include <pwd.h>

# ifdef RXVT_UTMP_SYSV
#  ifndef USER_PROCESS
#   define USER_PROCESS		7
#  endif
#  ifndef DEAD_PROCESS
#   define DEAD_PROCESS		8
#  endif
# endif

#endif

struct rxvt_ptytty_unix : rxvt_ptytty
{
  char *name;

public:

  rxvt_ptytty_unix ();
  ~rxvt_ptytty_unix ();

  bool get ();
  void put ();

  void login (int cmd_pid, bool login_shell, const char *hostname);

#if UTMP_SUPPORT
  int utmp_pos;
  int cmd_pid;
  bool login_shell;

#ifdef HAVE_STRUCT_UTMP
  struct utmp ut;
#endif
#ifdef HAVE_STRUCT_UTMPX
  struct utmpx utx;
#endif
#if (defined(HAVE_STRUCT_UTMP) && defined(HAVE_UTMP_PID)) || defined(HAVE_STRUCT_UTMPX)
  char ut_id[5];
#endif

  void logout ();
#endif
};

#endif

