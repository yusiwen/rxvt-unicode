/*
 * $Id$
 */

#ifndef COMMAND_H_
#define COMMAND_H_

// STRING_MAX __MUST__ not be larger than what CBUFSIZ can hold.
#define STRING_MAX	1024	/* max string size for process_rxvt_xterm_seq() */

#define ESC_ARGS	32	/* max # of args for esc sequences */

#ifdef OFFIX_DND
# define DndFile	2
# define DndDir		5
# define DndLink	7
#endif

/* a large REFRESH_PERIOD causes problems with `cat' */
#define REFRESH_PERIOD		2

#ifndef MULTICLICK_TIME
# define MULTICLICK_TIME	500
#endif
#ifndef SCROLLBAR_INITIAL_DELAY
# ifdef NEXT_SCROLLER
#  define SCROLLBAR_INITIAL_DELAY	20
# else
#  define SCROLLBAR_INITIAL_DELAY	40
# endif
#endif
#ifndef SCROLLBAR_CONTINUOUS_DELAY
# define SCROLLBAR_CONTINUOUS_DELAY	2
#endif

/*
 * key-strings: if only these keys were standardized <sigh>
 */
#ifdef LINUX_KEYS
# define KS_HOME	"\033[1~"	/* Home == Find */
# define KS_END		"\033[4~"	/* End == Select */
#else
# define KS_HOME	"\033[7~"	/* Home */
# define KS_END		"\033[8~"	/* End */
#endif

#ifdef SCROLL_ON_SHIFT
# define SCROLL_SHIFTKEY (shft)
#else
# define SCROLL_SHIFTKEY 0
#endif
#ifdef SCROLL_ON_CTRL
# define SCROLL_CTRLKEY  (ctrl)
#else
# define SCROLL_CTRLKEY 0
#endif
#ifdef SCROLL_ON_META
# define SCROLL_METAKEY  (meta)
#else
# define SCROLL_METAKEY 0
#endif
#define IS_SCROLL_MOD  (SCROLL_SHIFTKEY || SCROLL_CTRLKEY || SCROLL_METAKEY)

/*
 * ESC-Z processing:
 *
 * By stealing a sequence to which other xterms respond, and sending the
 * same number of characters, but having a distinguishable sequence,
 * we can avoid having a timeout (when not under an rxvt) for every login
 * shell to auto-set its DISPLAY.
 *
 * This particular sequence is even explicitly stated as obsolete since
 * about 1985, so only very old software is likely to be confused, a
 * confusion which can likely be remedied through termcap or TERM. Frankly,
 * I doubt anyone will even notice.  We provide a #ifdef just in case they
 * don't care about auto-display setting.  Just in case the ancient
 * software in question is broken enough to be case insensitive to the 'c'
 * character in the answerback string, we make the distinguishing
 * characteristic be capitalization of that character. The length of the
 * two strings should be the same so that identical read (2) calls may be
 * used.
 */
#define VT100_ANS	"\033[?1;2c"	/* vt100 answerback */
#ifndef ESCZ_ANSWER
# define ESCZ_ANSWER	VT100_ANS	/* obsolete ANSI ESC[c */
#endif

#include "command.intpro"	/* PROTOS for internal routines */
#endif	/* _COMMAND_H_ */
