#ifndef INIT_H_
#define INIT_H_

#undef CERASE /* TODO */
#define CERASE	'\010'	/* ^H */

#ifdef HAVE_XSETLOCALE
# define X_LOCALE
# include <X11/Xlocale.h>
#else
# ifdef HAVE_SETLOCALE
#  include <clocale>
# endif
#endif

#ifdef TTY_GID_SUPPORT
# include <grp.h>
#endif

/* ways to deal with getting/setting termios structure */

/* termios interface */
#define GET_TERMIOS(fd,tios)	tcgetattr (fd, tios)
#define SET_TERMIOS(fd,tios)		\
      cfsetospeed (tios, BAUDRATE),	\
      cfsetispeed (tios, BAUDRATE),	\
      tcsetattr (fd, TCSANOW, tios)

/* use the fastest baud-rate */
#ifdef B38400
# define BAUDRATE	B38400
#else
# ifdef B19200
#  define BAUDRATE	B19200
# else
#  define BAUDRATE	B9600
# endif
#endif

/* Disable special character functions */
#ifdef _POSIX_VDISABLE
# define VDISABLE	_POSIX_VDISABLE
#else
# define VDISABLE	255
#endif

/*----------------------------------------------------------------------*
 * system default characters if defined and reasonable
 */
#ifndef CINTR
# define CINTR		'\003'	/* ^C */
#endif
#ifndef CQUIT
# define CQUIT		'\034'	/* ^\ */
#endif
#ifndef CERASE
# ifdef linux
#  define CERASE	'\177'	/* ^? */
# else
#  define CERASE	'\010'	/* ^H */
# endif
#endif
#ifndef CKILL
# define CKILL		'\025'	/* ^U */
#endif
#ifndef CEOF
# define CEOF		'\004'	/* ^D */
#endif
#ifndef CSTART
# define CSTART		'\021'	/* ^Q */
#endif
#ifndef CSTOP
# define CSTOP		'\023'	/* ^S */
#endif
#ifndef CSUSP
# define CSUSP		'\032'	/* ^Z */
#endif
#ifndef CDSUSP
# define CDSUSP		'\031'	/* ^Y */
#endif
#ifndef CRPRNT
# define CRPRNT		'\022'	/* ^R */
#endif
#ifndef CFLUSH
# define CFLUSH		'\017'	/* ^O */
#endif
#ifndef CWERASE
# define CWERASE	'\027'	/* ^W */
#endif
#ifndef CLNEXT
# define CLNEXT		'\026'	/* ^V */
#endif

#ifndef VDISCRD
# ifdef VDISCARD
#  define VDISCRD	VDISCARD
# endif
#endif

#ifndef VWERSE
# ifdef VWERASE
#  define VWERSE	VWERASE
# endif
#endif

#ifndef O_NOCTTY
# define O_NOCTTY	0
#endif
#ifndef ONLCR
# define ONLCR		0
#endif

#define CONSOLE		"/dev/console"	/* console device */

#endif	/* _INIT_H_ */
