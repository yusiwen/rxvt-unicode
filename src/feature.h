/*
 * File:	feature.h
 *
 * Compile-time configuration.
 *-----------------------------------------------------------------------
 * Copyright (c) 1997,1998 Oezguer Kesim <kesim@math.fu-berlin.de>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 *----------------------------------------------------------------------*/
#ifndef FEATURE_H
#define FEATURE_H

#ifndef X11USRLIBDIR
# define X11USRLIBDIR		"/usr/X11R6/lib"
#endif
#ifndef X11LIBDIR
# define X11LIBDIR		X11USRLIBDIR "/X11"
#endif
#ifndef XAPPLOADDIR
# define XAPPLOADDIR		X11LIBDIR "/app-defaults" 
# define XAPPLOADDIRLOCALE	X11LIBDIR "/%-.*s/app-defaults"
#endif

/*-----------------------SCREEN OPTIONS AND COLOURS---------------------*/

/*
 * NOTE:
 *
 * Most of these configuration options have not been tested within the new
 * rxvt-unicode framework. Changing them might work, might have no effect,
 * destroy your disks or have any other effects. You may freely try (and
 * report bugs, too!), but don't _expect_ them to work.
 */

/*
 * Define the name of the environment variable to be used in
 * addition to the "PATH" environment and the `path' resource.
 * Usually it should point to where you keep your background pixmaps and/or
 * your menu files
 */
#define PATH_ENV	"RXVTPATH"

/*
 * Avoid enabling the colour cursor (-cr, cursorColor, cursorColor2)
 */
/* #define NO_CURSORCOLOR */

/*
 * Suppress use of BOLD and BLINK attributes for setting bright foreground
 * and background, respectively.  Simulate BOLD using colorBD or
 * overstrike characters.
 */
/* #define NO_BRIGHTCOLOR */

/*
 * Make colours match xterm colours instead of `traditional' rxvt colours
 */
#define XTERM_COLORS

/*
 * Disable separate colours for bold, underline and reverse video
 */
/* #define NO_BOLD_UNDERLINE_REVERSE */

/*
 * Define maximum possible columns and rows
 */
#define MAX_COLS	4000
#define MAX_ROWS	1000

/*
 * Define default colours for certain items.  If you have a low colour
 * display, then consider using colours which are already pre-allocated:
 *   Black		(#000000)
 *   Red3		(#CD0000)	+ these
 *   Green3		(#00CD00)	+ colours
 *   Yellow3		(#CDCD00)	+ are
 *   Blue3		(#0000CD)	+ not
 *   Magenta3		(#CD00CD)	+ pre-allocated
 *   Cyan3		(#00CDCD)	+ if
 *   AntiqueWhite	(#FAEBD7)	+ NO_BRIGHTCOLOR
 *   Grey25		(#404040)	+ defined
 *   Red		(#FF0000)
 *   Green		(#00FF00)
 *   Yellow		(#FFFF00)
 *   Blue		(#0000FF)
 *   Magenta		(#FF00FF)
 *   Cyan		(#00FFFF)
 *   White		(#FFFFFF)
 */
/* These colours MUST be defined */
#define COLOR_FOREGROUND	"Black"
#define COLOR_BACKGROUND	"White"
#define COLOR_SCROLLBAR		"#B2B2B2"	/* scrollColor match Netscape */
#define COLOR_SCROLLTROUGH	"#969696"

/*
 * The cursor colours are special.  Be very careful about setting these:
 * foreground/background colours may be modified by command line or resources
 * prior to this allocation.  Also, they are not valid if NO_CURSORCOLOR is
 * defined
 */
#define COLOR_CURSOR_FOREGROUND	NULL	/* if NULL, use background colour */
#define COLOR_CURSOR_BACKGROUND	NULL	/* if NULL, use foreground colour */

/*
 * Define to remove support for XCopyArea () support.  XCopyArea () is useful
 * for scrolling on non-local X displays
 */
#define NO_SLOW_LINK_SUPPORT

/*
 * Printer pipe which will be used for emulation of attached vt100 printer
 */
#define PRINTPIPE	"lpr"

/*
 * Allow 80/132 mode switching on startup
 */
/* #define ALLOW_132_MODE */
 
/*------------------------------RESOURCES-------------------------------*/
/*
 * Define to find installed application defaults for rxvt
 * Only if USE_XGETDEFAULT is not defined.
 */
#define USE_XAPPLOADDIR

/*
 * Add support for the Offix DND (Drag 'n' Drop) protocol
 */
/* #define OFFIX_DND */

/*---------------------------------KEYS---------------------------------*/

/*
 * Define defaults for backspace and delete keys - unless they have been
 * configured out with --disable-backspace-key / --disable-delete-key
 */
#define DEFAULT_BACKSPACE	"DEC"		/* SPECIAL */
#define DEFAULT_DELETE		"\033[3~"

/*
 * To use
 *	Home = "\E[1~", End = "\E[4~"
 * instead of
 *	Home = "\E[7~", End = "\E[8~"	[default]
 */
/* #define LINUX_KEYS */

/*
 * Enable the keysym resource which allows you to define strings associated
 * with various KeySyms (0xFF00 - 0xFFFF).
 * Only works with the default hand-rolled resources.
 */
#if !NO_RESOURCES && ENABLE_FRILLS
# define KEYSYM_RESOURCE
#endif

/*
 * Modifier/s to use to allow up/down arrows and Prior/Next keys
 * to scroll single or page-fulls
 */
#define SCROLL_ON_SHIFT
/* #define SCROLL_ON_CTRL */
/* #define SCROLL_ON_META */

/*
 * Allow scrolling with modifier+Up/Down keys, in addition
 * to modifier+Prior/Next? (modifier is controlled with
 * SCROLL_ON_* defines above.). 
 * Also for modifier+Home/End keys to move to top/bottom
 */
/* #define SCROLL_ON_UPDOWN_KEYS */
/* #define SCROLL_ON_HOMEEND_KEYS */

/*
 * Allow unshifted Next/Prior keys to scroll forward/back
 * (in addition to shift+Next/shift+Prior)       --pjh
 */
/* #define UNSHIFTED_SCROLLKEYS */

/* (Hops) Set to choose a number of lines of context between pages
 *      (rather than a proportion (1/5) of savedlines buffer)
 *      when paging the savedlines with SHIFT-{Prior,Next} keys.
 */
#define PAGING_CONTEXT_LINES 1 /* */

/*
 * Have either Ctrl+Tab or Mod4+Tab emit \e\t
 * Useful when window manager grabs Alt+Tab   -- mg
 */
/* #define CTRL_TAB_MAKES_META */
/* #define MOD4_TAB_MAKES_META */

/*--------------------------------MOUSE---------------------------------*/
/*
 * Disable sending escape sequences (up, down, page up/down)
 * from the scrollbar when XTerm mouse reporting is enabled
 */
/* #define NO_SCROLLBAR_REPORT */

/*
 * Default separating chars for multiple-click selection
 * Space and tab are separate separating characters and are not settable
 */
#define CUTCHARS	"\"&'()*,;<=>?@[\\]^`{|}"

/*
 * Add run-time support for changing the cutchars for double click selection
 */
#define CUTCHAR_RESOURCE

/*
 * Have mouse reporting include double-click info for button1
 */
//#define MOUSE_REPORT_DOUBLECLICK

/*
 * Set delay between multiple click events [default: 500 milliseconds]
 */
/* #define MULTICLICK_TIME 500 */

/*
 * Time factor to slow down a `jumpy' mouse.  Motion isn't recognised until
 * this long after the last mouse click [default: 50 milliseconds]
 */
#define MOUSE_THRESHOLD		50

/*
 * If mouse wheel is defined, then scrolling is by 5 lines (or 1 line
 * if the shift key is down).  Scrolling can be smooth or jump scrolling
 */
#define JUMP_MOUSE_WHEEL

/*
 * Set delay periods for continuous scrolling with scrollbar buttons
 */
/* #define SCROLLBAR_INITIAL_DELAY 0.33 */
/* #define SCROLLBAR_CONTINUOUS_DELAY 0.05 */

/*
 * The speed of selection scrolling is proportional to the distance
 * the mouse pointer is out of the text window.  This is the max
 * number of lines to scroll at a time.
 */
#define SELECTION_SCROLL_MAX_LINES 8

/*
 * The number of lines (measured in character's heights, not pixels)
 * the pointer must be out of the window for each increase in the
 * number of lines scrolled.
 */
#define SELECTION_SCROLL_LINE_SPEEDUP 3

/*--------------------------------MISC----------------------------------*/
/*
 * Disable to reset tty device to pre-incovation state
 */
#define RESET_TTY_TO_COMMON_DEFAULTS

/*
 * Only log in wtmp file when we're a login shell (-ls option)
 */
#define WTMP_ONLY_ON_LOGIN

/*--------------------------------BELL----------------------------------*/
/*
 * Disable all bell indications
 */
/* #define NO_BELL */

/*
 * Disable automatic de-iconify when a bell is received
 */
/* #define NO_MAPALERT */

/*
 * Have mapAlert behaviour selectable with mapAlert resource
 */
#define MAPALERT_OPTION

/*-----------------------------SCROLL BAR-------------------------------*/
/*
 * Choose the rxvt style scrollbar width
 * - should be an even number [default: 10]
 */
/* #define SB_WIDTH_RXVT 10 */

/*
 * Minimum and maximum widths of the scrollbar (all styles)
 */
#define SB_WIDTH_MINIMUM 	5
#define SB_WIDTH_MAXIMUM 	100

/*
 * When using Rxvt scrollbar, clicking above or below the slider will move
 * 1/4 of the screen height, if possible.  Setting RXVT_SCROLL_FULL will move
 * it one screen height less one line, if possible
 */
#define RXVT_SCROLL_FULL 1

/*
 * (Hops) draw an internal border line on inside edge of the scrollbar
 */
/* #define SB_BORDER */

/*------------------------------MENU BAR--------------------------------*/
/*
 * Choose how many of (experimental) menuBars you want to be able to stack at
 * one time.
 *  A value of 1 disables menuBar stacking.
 *  A value of 0 disables menuBar all together.
 *  Note that the amount of memory overhead is the same for any value >= 2.
 */
#define MENUBAR_MAX 16

/*
 * Change the default shadow style
 */
/* #define MENUBAR_SHADOW_IN */

/*
 * Change the default shadow style
 */
#define MENU_SHADOW_IN

/*---------------------------MULTILINGUAL-------------------------------*/
/*
 * Allow run-time selection of Meta (Alt) to set the 8th bit on
 */
#define META8_OPTION

/*---------------------------DISPLAY OPTIONS----------------------------*/
/*
 * Force local connection to be socket (or other local) communication
 */
/* #define LOCAL_X_IS_UNIX */

/*
 * Have DISPLAY environment variable & "\E[7n" transmit display with IP number
 */
/* #define DISPLAY_IS_IP */

/*
 * Change what ESC Z transmits instead of the default "\E[?1;2c"
 */
/* #define ESCZ_ANSWER	"\033[?1;2C" */

/*
 * Check the current value of the window-time/icon-name and avoid
 * re-setting it to the same value -- avoids unnecessary window refreshes
 */
//#define SMART_WINDOW_TITLE // currently disabled, needs to be reimplemented

/*
 * Allow foreground/background colour to be changed with an
 * xterm escape sequence "\E]39;colour^G" -- still experimental
 */
#define XTERM_COLOR_CHANGE

/*
 * Remove secondary screen's independent cursor position, a la xterm
 */
/* #define NO_SECONDARY_SCREEN_CURSOR */

/*
 * Width of the term internal border
 */
#define INTERNALBORDERWIDTH	2

/*
 * Width of the term external border
 */
#define EXTERNALBORDERWIDTH	0

/*
 * Default number of extra dots between lines
 */
#define LINESPACE	0

/*
 * Default number of lines in the scrollback buffer
 */
#define SAVELINES	64

/*
 * Provide termcap/terminfo bw support (wrap backwards on cub1)
 */
#define TERMCAP_HAS_BW

/*
 * Some (older, e.g. fvwm 2.2.2) window managers need some time when
 * updating window positions. If transparency isn't working correctly
 * then you might try out this one.
 */
/* #define WAIT_FOR_WM */

#endif

