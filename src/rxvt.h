#ifndef RXVT_H_                /* include once only */
#define RXVT_H_

#include "rxvtlib.h"

#include "feature.h"

#if defined (ISO_14755) || defined (ENABLE_PERL)
# define ENABLE_OVERLAY 1
#endif

#if ENABLE_PERL
# define ENABLE_FRILLS 1
# define ENABLE_COMBINING 1
#endif

#if ENABLE_FRILLS
# define ENABLE_XEMBED 1
# define ENABLE_EWMH   1
# define CURSOR_BLINK  1
#endif

#include <limits.h>

#include <X11/cursorfont.h>
#include <X11/keysym.h>
#include <X11/keysymdef.h>
#include <X11/Xatom.h>
#if ENABLE_FRILLS
# include <X11/Xmd.h>
#endif

#include "encoding.h"
#include "rxvtfont.h"
#include "rxvttoolkit.h"
#include "iom.h"
#include "salloc.h"

#include "rxvtperl.h"

/*
 *****************************************************************************
 * SYSTEM HACKS
 *****************************************************************************
 */
/* Consistent defines - please report on the necessity
 * @ Unixware: defines (__svr4__)
 */
#if defined (SVR4) && !defined (__svr4__)
# define __svr4__ 1
#endif
#if defined (sun) && !defined (__sun__)
# define __sun__ 1
#endif

#ifndef HAVE_XPOINTER
typedef char *XPointer;
#endif

#ifdef HAVE_TERMIOS_H
# include <termios.h>
typedef struct termios ttymode_t;
#else
# include <sgtty.h>
typedef struct {
  struct sgttyb   sg;
  struct tchars   tc;
  struct ltchars  lc;
  int             line;
  int             local;
} ttymode_t;
#endif

#ifdef XPM_BACKGROUND
# ifdef XPM_INC_X11
#  include <X11/xpm.h>
# else
#  include <xpm.h>
# endif
#endif

#ifndef STDIN_FILENO
# define STDIN_FILENO   0
# define STDOUT_FILENO  1
# define STDERR_FILENO  2
#endif

/*
 *****************************************************************************
 * PROTOTYPES                    
 *****************************************************************************
 */
// main.C
RETSIGTYPE       rxvt_Child_signal                (int sig);
RETSIGTYPE       rxvt_Exit_signal                 (int sig);
void             rxvt_clean_exit                  ();
void           * rxvt_malloc                      (size_t size);
void           * rxvt_calloc                      (size_t number, size_t size);
void           * rxvt_realloc                     (void *ptr, size_t size);
void             rxvt_privileges                  (rxvt_privaction action);

// util.C
char *           rxvt_wcstombs                    (const wchar_t *str, int len = -1);
wchar_t *        rxvt_mbstowcs                    (const char *str, int len = -1);
char *           rxvt_wcstoutf8                   (const wchar_t *str, int len = -1);
wchar_t *        rxvt_utf8towcs                   (const char *str, int len = -1);
char *           rxvt_strdup                      (const char *str);

// misc.C
char *           rxvt_r_basename                  (const char *str);
void             rxvt_vlog                        (const char *fmt, va_list arg_ptr);
void             rxvt_log                         (const char *fmt,...);
void             rxvt_warn                        (const char *fmt,...);
void             rxvt_fatal                       (const char *fmt,...);
void             rxvt_exit_failure                ();
int              rxvt_Str_match                   (const char *s1, const char *s2);
const char *     rxvt_Str_skip_space              (const char *str);
char           * rxvt_Str_trim                    (char *str);
int              rxvt_Str_escaped                 (char *str);
char          ** rxvt_splitcommastring            (const char *cs);
void             rxvt_freecommastring             (char **cs);
char           * rxvt_File_find                   (const char *file, const char *ext, const char *path);
void             rxvt_Draw_Shadow                 (Display *display, Window win, GC topShadow, GC botShadow, int x, int y, int w, int h);
void             rxvt_Draw_Triangle               (Display *display, Window win, GC topShadow, GC botShadow, int x, int y, int w, int type);
void             rxvt_usleep                      (int usecs);

/////////////////////////////////////////////////////////////////////////////

// temporarily replace the process environment
extern char **environ;
extern char **rxvt_environ; // the original environ pointer

inline void set_environ (stringvec *envv)
{
  if (envv)
    environ = (char **)envv->begin ();
}

inline void set_environ (char **envv)
{
  if (envv)
    environ = envv;
}

/*
 *****************************************************************************
 * STRUCTURES AND TYPEDEFS
 *****************************************************************************
 */
struct grwin_t;

/* Sanitize menubar info */
#ifndef MENUBAR
# undef MENUBAR_MAX
#endif
#ifndef MENUBAR_MAX
# define MENUBAR_MAX    0
#endif

/* If we're using either the rxvt scrollbar or menu bars, keep the
 * scrollColor resource.
 */
#if defined(RXVT_SCROLLBAR) || defined(NEXT_SCROLLBAR) || defined(MENUBAR) || defined(PLAIN_SCROLLBAR)
# define KEEP_SCROLLCOLOR 1
#else
# undef KEEP_SCROLLCOLOR
#endif

#ifdef XPM_BACKGROUND
typedef struct {
  short w, h, x, y;
  Pixmap pixmap;
} bgPixmap_t;
#endif

/*
 * the 'essential' information for reporting Mouse Events
 * pared down from XButtonEvent
 */
struct mouse_event {
  int clicks;
  Time time;             /* milliseconds */
  unsigned int state;    /* key or button mask */
  unsigned int button;   /* detail */
};

#if ENABLE_FRILLS
typedef struct _mwmhints {
  CARD32 flags;
  CARD32 functions;
  CARD32 decorations;
  INT32  input_mode;
  CARD32 status;
} MWMHints;
#endif

#if ENABLE_XEMBED
// XEMBED messages
# define XEMBED_EMBEDDED_NOTIFY          0 
# define XEMBED_WINDOW_ACTIVATE          1 
# define XEMBED_WINDOW_DEACTIVATE        2 
# define XEMBED_REQUEST_FOCUS            3 
# define XEMBED_FOCUS_IN                 4 
# define XEMBED_FOCUS_OUT                5 
# define XEMBED_FOCUS_NEXT               6 
# define XEMBED_FOCUS_PREV               7

# define XEMBED_MODALITY_ON              10 
# define XEMBED_MODALITY_OFF             11 
# define XEMBED_REGISTER_ACCELERATOR     12 
# define XEMBED_UNREGISTER_ACCELERATOR   13 
# define XEMBED_ACTIVATE_ACCELERATOR     14

// XEMBED detail code
# define XEMBED_FOCUS_CURRENT            0 
# define XEMBED_FOCUS_FIRST              1 
# define XEMBED_FOCUS_LAST               2

# define XEMBED_MAPPED			(1 << 0)
#endif

/*
 *****************************************************************************
 * NORMAL DEFINES
 *****************************************************************************
 */

/* COLORTERM, TERM environment variables */
#define COLORTERMENV    "rxvt"
#ifdef XPM_BACKGROUND
# define COLORTERMENVFULL COLORTERMENV "-xpm"
#else
# define COLORTERMENVFULL COLORTERMENV
#endif
#ifndef TERMENV
# define TERMENV        "rxvt-unicode"
#endif

#if defined (NO_MOUSE_REPORT) && !defined (NO_MOUSE_REPORT_SCROLLBAR)
# define NO_MOUSE_REPORT_SCROLLBAR 1
#endif

/* now look for other badly set stuff */

#if !defined (EACCESS) && defined(EAGAIN)
# define EACCESS EAGAIN
#endif

#ifndef EXIT_SUCCESS            /* missing from <stdlib.h> */
# define EXIT_SUCCESS           0       /* exit function success */
# define EXIT_FAILURE           1       /* exit function failure */
#endif

#define menuBar_esc             10
#define scrollBar_esc           30
#define menuBar_margin          2       /* margin below text */

#if defined(RXVT_SCROLLBAR) || defined(NEXT_SCROLLBAR) || defined(XTERM_SCROLLBAR) || defined(PLAIN_SCROLLBAR)
# define HAVE_SCROLLBARS 1
#endif

/* width of scrollBar, menuBar shadow, must be 1 or 2 */
#ifdef HALFSHADOW
# define MENU_SHADOW 1
#else
# define MENU_SHADOW 2
#endif

#define R_SB_ALIGN_CENTRE       0
#define R_SB_ALIGN_TOP          1
#define R_SB_ALIGN_BOTTOM       2

#define R_SB_NEXT               1
#define R_SB_XTERM              2
#define R_SB_PLAIN              4
#define R_SB_RXVT               8

#define SB_WIDTH_NEXT           19
#define SB_WIDTH_XTERM          15
#define SB_WIDTH_PLAIN          7
#ifndef SB_WIDTH_RXVT
# define SB_WIDTH_RXVT          10
#endif

/*
 * NeXT scrollbar defines
 */
#define SB_PADDING              1
#define SB_BORDER_WIDTH         1
#define SB_BEVEL_WIDTH_UPPER_LEFT       1
#define SB_BEVEL_WIDTH_LOWER_RIGHT      2
#define SB_LEFT_PADDING         (SB_PADDING + SB_BORDER_WIDTH)
#define SB_MARGIN_SPACE         (SB_PADDING * 2)
#define SB_BUTTON_WIDTH         (SB_WIDTH_NEXT - SB_MARGIN_SPACE - SB_BORDER_WIDTH)
#define SB_BUTTON_HEIGHT        (SB_BUTTON_WIDTH)
#define SB_BUTTON_SINGLE_HEIGHT (SB_BUTTON_HEIGHT + SB_PADDING)
#define SB_BUTTON_BOTH_HEIGHT   (SB_BUTTON_SINGLE_HEIGHT * 2)
#define SB_BUTTON_TOTAL_HEIGHT  (SB_BUTTON_BOTH_HEIGHT + SB_PADDING)
#define SB_BUTTON_BEVEL_X       (SB_LEFT_PADDING)
#define SB_BUTTON_FACE_X        (SB_BUTTON_BEVEL_X + SB_BEVEL_WIDTH_UPPER_LEFT)
#define SB_THUMB_MIN_HEIGHT     (SB_BUTTON_WIDTH - (SB_PADDING * 2))
 /*
  *    +-------------+
  *    |             | <---< SB_PADDING
  *    | ::::::::::: |
  *    | ::::::::::: |
  *   '''''''''''''''''
  *   ,,,,,,,,,,,,,,,,,
  *    | ::::::::::: |
  *    | ::::::::::: |
  *    |  +---------------< SB_BEVEL_WIDTH_UPPER_LEFT
  *    |  | :::::::: |
  *    |  V :::: vv-------< SB_BEVEL_WIDTH_LOWER_RIGHT
  *    | +---------+ |
  *    | | ......%%| |
  *    | | ......%%| |
  *    | | .. ()..%%| |
  *    | | ......%%| |
  *    | | %%%%%%%%| |
  *    | +---------+ | <.........................
  *    |             | <---< SB_PADDING         :
  *    | +---------+ | <-+..........            :---< SB_BUTTON_TOTAL_HEIGHT
  *    | | ......%%| |   |         :            :
  *    | | ../\..%%| |   |---< SB_BUTTON_HEIGHT :
  *    | | %%%%%%%%| |   |         :            :
  *    | +---------+ | <-+         :            :
  *    |             |             :            :
  *    | +---------+ | <-+         :---< SB_BUTTON_BOTH_HEIGHT
  *    | | ......%%| |   |         :            :
  *    | | ..\/..%%| |   |         :            :
  *    | | %%%%%%%%| |   |---< SB_BUTTON_SINGLE_HEIGHT
  *    | +---------+ |   |         :            :
  *    |             |   |         :            :
  *    +-------------+ <-+.........:............:
  *    ^^|_________| :
  *    ||     |      :
  *    ||     +---< SB_BUTTON_WIDTH
  *    ||            :
  *    |+------< SB_PADDING
  *    |:            :
  *    +----< SB_BORDER_WIDTH
  *     :            :
  *     :............:
  *           |
  *           +---< SB_WIDTH_NEXT
  */

enum {
  NO_REFRESH       = 0   ,  /* Window not visible at all!        */
  FAST_REFRESH     = 1<<0,  /* Fully exposed window              */
  SLOW_REFRESH     = 1<<1,  /* Partially exposed window          */
  SMOOTH_REFRESH   = 1<<2,  /* Do sync'ing to make it smooth     */
};

#ifdef NO_SECONDARY_SCREEN
# define NSCREENS               0
#else
# define NSCREENS               1
#endif

/* special (internal) prefix for font commands */
#define FONT_CMD                '#'
#define FONT_DN                 "#-"
#define FONT_UP                 "#+"

/* flags for rxvt_scr_gotorc () */
enum {
  C_RELATIVE = 1,       /* col movement is relative */
  R_RELATIVE = 2,       /* row movement is relative */
  RELATIVE   = C_RELATIVE | R_RELATIVE,
};

/* modes for rxvt_scr_insdel_chars (), rxvt_scr_insdel_lines () */
enum {
  INSERT = -1,				/* don't change these values */
  DELETE = +1,
  ERASE  = +2,
};

/* modes for rxvt_scr_page () - scroll page. used by scrollbar window */
enum page_dirn {
  UP,
  DN,
  NO_DIR,
};

/* arguments for rxvt_scr_change_screen () */
enum {
  PRIMARY = 0,
  SECONDARY,
};

#define RS_None                 0

#define RS_fgMask               0x0000007fUL    // 128 colors
#define RS_bgMask               0x00003f80UL    // 128 colors

// font styles
#define RS_Bold                 0x00004000UL    // value 1
#define RS_Italic		0x00008000UL    // value 2

// fake styles
#define RS_Blink                0x00010000UL    // blink
#define RS_RVid                 0x00020000UL    // reverse video
#define RS_Uline                0x00040000UL    // underline

// 5 custom bits for extensions
#define RS_customCount          32
#define RS_customMask           0x00f80000UL
#define RS_customShift          19

// other flags
#define RS_Careful		0x80000000UL	/* be careful when drawing these */

#define RS_styleCount		4
#define RS_styleMask		(RS_Bold | RS_Italic)
#define RS_styleShift		14

#define RS_baseattrMask         (RS_Italic | RS_Bold | RS_Blink | RS_RVid | RS_Uline)
#define RS_attrMask             (RS_baseattrMask | RS_fontMask)

#define RS_fontCount		127		// not 127 or 256, see rxvtfont.h
#define RS_fontMask             0xff000000UL    // plenty(?) of fonts, includes RS_Careful
#define RS_fontShift            24

#define DEFAULT_RSTYLE  (RS_None | Color_fg | (Color_bg << Color_Bits))
#define OVERLAY_RSTYLE  (RS_None | Color_Black | (Color_Yellow << Color_Bits))

#define Sel_none                0       /* Not waiting */
#define Sel_normal              0x01    /* normal selection */
#define Sel_incr                0x02    /* incremental selection */
#define Sel_direct              0x00
#define Sel_Primary             0x01
#define Sel_Secondary           0x02
#define Sel_Clipboard           0x03
#define Sel_whereMask           0x0f
#define Sel_CompoundText        0x10    /* last request was COMPOUND_TEXT */
#define Sel_UTF8String          0x20    /* last request was UTF8_STRING */

enum {
  C0_NUL = 0x00,
          C0_SOH, C0_STX, C0_ETX, C0_EOT, C0_ENQ, C0_ACK, C0_BEL,
  C0_BS , C0_HT , C0_LF , C0_VT , C0_FF , C0_CR , C0_SO , C0_SI ,
  C0_DLE, C0_DC1, C0_DC2, D0_DC3, C0_DC4, C0_NAK, C0_SYN, C0_ETB,
  C0_CAN, C0_EM , C0_SUB, C0_ESC, C0_IS4, C0_IS3, C0_IS2, C0_IS1,
}; 
#define CHAR_ST                 0x9c    /* 0234 */

/*
 * XTerm Operating System Commands: ESC ] Ps;Pt (ST|BEL)
 * colour extensions by Christian W. Zuckschwerdt <zany@triq.net>
 */
enum {
  XTerm_name             =  0,
  XTerm_iconName         =  1,
  XTerm_title            =  2,
  XTerm_property         =  3,      // change X property
  XTerm_Color            =  4,      // change colors
  XTerm_Color00          = 10,      // not implemented, CLASH!
  XTerm_Color01          = 11,      // not implemented
  XTerm_Color_cursor     = 12,      // change actual 'Cursor' color
  XTerm_Color_pointer_fg = 13,      // change actual 'Pointer' fg color
  XTerm_Color_pointer_bg = 14,      // change actual 'Pointer' bg color
  XTerm_Color05          = 15,      // not implemented (tektronix fg)
  XTerm_Color06          = 16,      // not implemented (tektronix bg)
  XTerm_Color_RV         = 17,      // change actual 'Highlight' color
  XTerm_logfile          = 46,      // not implemented
  XTerm_font             = 50,

  XTerm_konsole30        = 30,      // reserved for konsole
  XTerm_konsole31        = 31,      // reserved for konsole
  XTerm_emacs51          = 51,      // reserved for emacs shell
  /*
   * rxvt extensions of XTerm OSCs: ESC ] Ps;Pt (ST|BEL)
   * at least Rxvt_Color_BD and Rxvt_Color_UL clash with xterm
   */
  Rxvt_Color_BD          = 18,      // change actual 'Bold' color
  Rxvt_Color_UL          = 19,      // change actual 'Underline' color
  Rxvt_Pixmap            = 20,      // new bg pixmap
  Rxvt_restoreFG         = 39,      // change default fg color
  Rxvt_restoreBG         = 49,      // change default bg color
  Rxvt_dumpscreen        = 55,      // dump scrollback and all of screen

  URxvt_locale           = 701,     // change locale
  URxvt_Menu             = 703,     // set menu item
  URxvt_Color_IT         = 704,     // change actual 'Italic' colour
  URxvt_Color_tint       = 705,     // change actual tint colour
  URxvt_Color_BD         = 706,
  URxvt_Color_UL         = 707,

  URxvt_font             = 710,
  URxvt_boldFont         = 711,
  URxvt_italicFont       = 712,
  URxvt_boldItalicFont   = 713,

  URxvt_view_up          = 720,
  URxvt_view_down        = 721,

  URxvt_perl             = 777,
};

/* Words starting with `Color_' are colours.  Others are counts */
/*
 * The PixColor and rendition colour usage should probably be decoupled
 * on the unnecessary items, e.g. Color_pointer, but won't bother
 * until we need to.  Also, be aware of usage in pixcolor_set
 */

enum colour_list {
  Color_fg = 0,
  Color_bg,
  minCOLOR,                   /* 2 */
  Color_Black = minCOLOR,
  Color_Red3,
  Color_Green3,
  Color_Yellow3,
  Color_Blue3,
  Color_Magenta3,
  Color_Cyan3,
  maxCOLOR,                   /* minCOLOR + 7 */
#ifndef NO_BRIGHTCOLOR
  Color_AntiqueWhite = maxCOLOR,
  minBrightCOLOR,             /* maxCOLOR + 1 */
  Color_Grey25 = minBrightCOLOR,
  Color_Red,
  Color_Green,
  Color_Yellow,
  Color_Blue,
  Color_Magenta,
  Color_Cyan,
  maxBrightCOLOR,             /* minBrightCOLOR + 7 */
  Color_White = maxBrightCOLOR,
#else
  Color_White = maxCOLOR,
#endif
  minTermCOLOR = Color_White + 1,
  maxTermCOLOR = Color_White + 72,
#ifndef NO_CURSORCOLOR
  Color_cursor,
  Color_cursor2,
#endif
  Color_pointer_fg,
  Color_pointer_bg,
  Color_border,
#ifndef NO_BOLD_UNDERLINE_REVERSE
  Color_BD,
  Color_IT,
  Color_UL,
  Color_RV,
#endif
#if ENABLE_FRILLS
  Color_underline,
#endif
#ifdef OPTION_HC
  Color_HC,
#endif
#ifdef KEEP_SCROLLCOLOR
  Color_scroll,
  Color_trough,
#endif
#if TINTING
  Color_tint,
#endif
#if OFF_FOCUS_FADING
  Color_fade,
#endif
  NRS_COLORS,                 /* */
#ifdef KEEP_SCROLLCOLOR
  Color_topShadow = NRS_COLORS,
  Color_bottomShadow,
  TOTAL_COLORS
#else
  TOTAL_COLORS = NRS_COLORS
#endif
};

#define Color_Bits      7 // 0 .. maxTermCOLOR

#define NPIXCLR_SETS    ((TOTAL_COLORS + 31) / 32)
#define NPIXCLR_BITS    32

/*
 * Resource list
 */
enum {
# define def(name) Rs_ ## name,
# define reserve(name,count) Rs_ ## name ## _ = Rs_ ## name + (count) - 1,
# include "rsinc.h"
# undef def
# undef reserve
  NUM_RESOURCES
};

// see init.C:xa_names, which must be kept in sync
enum {
  XA_TEXT = 0,
  XA_COMPOUND_TEXT,
  XA_UTF8_STRING,
  XA_MULTIPLE,
  XA_TARGETS,
  XA_TIMESTAMP,
  XA_VT_SELECTION,
  XA_INCR,
  XA_WM_PROTOCOLS,
  XA_WM_DELETE_WINDOW,
  XA_CLIPBOARD,
#if ENABLE_FRILLS
  XA_MOTIF_WM_HINTS,
#endif
#if ENABLE_EWMH
  XA_NET_WM_PID,
  XA_NET_WM_NAME,
  XA_NET_WM_ICON_NAME,
  XA_NET_WM_PING,
#endif
#if USE_XIM
  XA_WM_LOCALE_NAME,
#endif
#if TRANSPARENT
  XA_XROOTPMAP_ID,
  XA_ESETROOT_PMAP_ID,
#endif
#if OFFIX_DND                /* OffiX Dnd (drag 'n' drop) support */
  XA_DNDPROTOCOL,
  XA_DNDSELECTION,
#endif
#if ENABLE_XEMBED
  XA_XEMBED,
  XA_XEMBED_INFO,
#endif
  NUM_XA
};

/* DEC private modes */
#define PrivMode_132            (1UL<<0)
#define PrivMode_132OK          (1UL<<1)
#define PrivMode_rVideo         (1UL<<2)
#define PrivMode_relOrigin      (1UL<<3)
#define PrivMode_Screen         (1UL<<4)
#define PrivMode_Autowrap       (1UL<<5)
#define PrivMode_aplCUR         (1UL<<6)
#define PrivMode_aplKP          (1UL<<7)
#define PrivMode_HaveBackSpace  (1UL<<8)
#define PrivMode_BackSpace      (1UL<<9)
#define PrivMode_ShiftKeys      (1UL<<10)
#define PrivMode_VisibleCursor  (1UL<<11)
#define PrivMode_MouseX10       (1UL<<12)
#define PrivMode_MouseX11       (1UL<<13)
#define PrivMode_scrollBar      (1UL<<14)
#define PrivMode_menuBar        (1UL<<15)
#define PrivMode_TtyOutputInh   (1UL<<16)
#define PrivMode_Keypress       (1UL<<17)
#define PrivMode_smoothScroll   (1UL<<18)
#define PrivMode_vt52           (1UL<<19)
#define PrivMode_LFNL		(1UL<<20)
/* too annoying to implement X11 highlight tracking */
/* #define PrivMode_MouseX11Track       (1LU<<21) */

#define PrivMode_mouse_report   (PrivMode_MouseX10|PrivMode_MouseX11)
#define PrivMode(test,bit)              \
    if (test)                           \
        priv_modes |= (bit);            \
    else                                \
        priv_modes &= ~(bit)

#ifdef ALLOW_132_MODE
# define PrivMode_Default (PrivMode_Autowrap|PrivMode_ShiftKeys|PrivMode_VisibleCursor|PrivMode_132OK)
#else
# define PrivMode_Default (PrivMode_Autowrap|PrivMode_ShiftKeys|PrivMode_VisibleCursor)
#endif

// do not change these constants lightly, there are many interdependencies
#define IMBUFSIZ               128     // input modifier buffer sizes
#define KBUFSZ                 512     // size of keyboard mapping buffer
#define CBUFSIZ                2048    // size of command buffer
#define UBUFSIZ                2048    // character buffer

#ifndef PATH_MAX
# define PATH_MAX 16384
#endif

/* Motif window hints */
#define MWM_HINTS_FUNCTIONS     (1L << 0)
#define MWM_HINTS_DECORATIONS   (1L << 1)
#define MWM_HINTS_INPUT_MODE    (1L << 2)
#define MWM_HINTS_STATUS        (1L << 3)
/* bit definitions for MwmHints.functions */
#define MWM_FUNC_ALL            (1L << 0)
#define MWM_FUNC_RESIZE         (1L << 1)
#define MWM_FUNC_MOVE           (1L << 2)
#define MWM_FUNC_MINIMIZE       (1L << 3)
#define MWM_FUNC_MAXIMIZE       (1L << 4)
#define MWM_FUNC_CLOSE          (1L << 5)
/* bit definitions for MwmHints.decorations */
#define MWM_DECOR_ALL           (1L << 0)
#define MWM_DECOR_BORDER        (1L << 1)
#define MWM_DECOR_RESIZEH       (1L << 2)
#define MWM_DECOR_TITLE         (1L << 3)
#define MWM_DECOR_MENU          (1L << 4)
#define MWM_DECOR_MINIMIZE      (1L << 5)
#define MWM_DECOR_MAXIMIZE      (1L << 6)
/* bit definitions for MwmHints.inputMode */
#define MWM_INPUT_MODELESS                  0
#define MWM_INPUT_PRIMARY_APPLICATION_MODAL 1
#define MWM_INPUT_SYSTEM_MODAL              2
#define MWM_INPUT_FULL_APPLICATION_MODAL    3
#define PROP_MWM_HINTS_ELEMENTS             5

/*
 *****************************************************************************
 * MACRO DEFINES
 *****************************************************************************
 */
#define dDisp			Display *disp = display->display

/* convert pixel dimensions to row/column values.  Everything as int32_t */
#define Pixel2Col(x)            Pixel2Width((int32_t)(x))
#define Pixel2Row(y)            Pixel2Height((int32_t)(y))
#define Pixel2Width(x)          ((int32_t)(x) / (int32_t)fwidth)
#define Pixel2Height(y)         ((int32_t)(y) / (int32_t)fheight)
#define Col2Pixel(col)          ((int32_t)Width2Pixel(col))
#define Row2Pixel(row)          ((int32_t)Height2Pixel(row))
#define Width2Pixel(n)          ((int32_t)(n) * (int32_t)fwidth)
#define Height2Pixel(n)         ((int32_t)(n) * (int32_t)fheight)

#define OPTION(opt)		(options & (opt))
#define DEFAULT_OPTIONS		(Opt_scrollBar | Opt_scrollTtyOutput \
				 | Opt_jumpScroll | Opt_secondaryScreen \
				 | Opt_pastableTabs | Opt_intensityStyles)

// for m >= -n, ensure remainder lies between 0..n-1
#define MOD(m,n) (((m) + (n)) % (n))

#define LINENO(n) MOD (term_start + int(n), total_rows)
#define ROW(n) row_buf [LINENO (n)]

/* how to build & extract colors and attributes */
#define GET_BASEFG(x)           (((x) & RS_fgMask))
#define GET_BASEBG(x)           (((x) & RS_bgMask)>>Color_Bits)

#define GET_FONT(x)             (((x) & RS_fontMask) >> RS_fontShift)
#define SET_FONT(x,fid)         (((x) & ~RS_fontMask) | ((fid) << RS_fontShift))

#define GET_STYLE(x)		(((x) & RS_styleMask) >> RS_styleShift)
#define SET_STYLE(x,style)	(((x) & ~RS_styleMask) | ((style) << RS_styleShift))

#define GET_ATTR(x)             (((x) & RS_attrMask))
#define GET_BGATTR(x)                                                   \
    (((x) & RS_RVid) ? (((x) & (RS_attrMask & ~RS_RVid))                \
                        | (((x) & RS_fgMask)<<Color_Bits))              \
                     : ((x) & (RS_attrMask | RS_bgMask)))
#define SET_FGCOLOR(x,fg)       (((x) & ~RS_fgMask)   | (fg))
#define SET_BGCOLOR(x,bg)       (((x) & ~RS_bgMask)   | ((bg)<<Color_Bits))
#define SET_ATTR(x,a)           (((x) & ~RS_attrMask) | (a))

#define RS_SAME(a,b)		(!(((a) ^ (b)) & ~RS_Careful))

#define SET_PIXCOLOR(x)         (pixcolor_set[(x) / NPIXCLR_BITS] |= (1 << ((x) % NPIXCLR_BITS)))
#define ISSET_PIXCOLOR(x)       (pixcolor_set[(x) / NPIXCLR_BITS] &  (1 << ((x) % NPIXCLR_BITS)))

#if ENABLE_STYLES
# define FONTSET(style) fontset[GET_STYLE (style)]
#else
# define FONTSET(style) fontset[0]
#endif

#ifdef HAVE_SCROLLBARS
# define scrollbar_TotalWidth() (scrollBar.width + sb_shadow * 2)
#else
# define scrollbar_TotalWidth() (0)
#endif
#define scrollbar_isMotion()    (scrollBar.state == 'm')
#define scrollbar_isUp()        (scrollBar.state == 'U')
#define scrollbar_isDn()        (scrollBar.state == 'D')
#define scrollbar_isUpDn()      isupper (scrollBar.state)
#define isScrollbarWindow(w)    (scrollBar.state && (w) == scrollBar.win)

#define scrollbarnext_dnval()   (scrollBar.end + (scrollBar.width + 1))
#define scrollbarnext_upButton(y)       ((y) > scrollBar.end \
                                         && (y) <= scrollbarnext_dnval ())
#define scrollbarnext_dnButton(y)       ((y) > scrollbarnext_dnval())
#define SCROLLNEXT_MINHEIGHT    SB_THUMB_MIN_HEIGHT
#define scrollbarrxvt_upButton(y)       ((y) < scrollBar.beg)
#define scrollbarrxvt_dnButton(y)       ((y) > scrollBar.end)
#define SCROLLRXVT_MINHEIGHT    10
#define SCROLLXTERM_MINHEIGHT   10

#define scrollbar_minheight()   (scrollBar.style == R_SB_NEXT        \
                                 ? SCROLLNEXT_MINHEIGHT                 \
                                 : SCROLLRXVT_MINHEIGHT)
#define scrollbar_above_slider(y)       ((y) < scrollBar.top)
#define scrollbar_below_slider(y)       ((y) > scrollBar.bot)
#define scrollbar_position(y)           ((y) - scrollBar.beg)
#define scrollbar_size()                (scrollBar.end - scrollBar.beg \
                                         - scrollbar_minheight ())

#if (MENUBAR_MAX > 1)
/* rendition style flags */
# define menuBar_height()       (fheight + MENU_SHADOW)
# define menuBar_TotalHeight()  (menuBar_height() + MENU_SHADOW + menuBar_margin)
# define isMenuBarWindow(w)     ((w) == menuBar.win)
#else
# define menuBar_height()       (0)
# define menuBar_TotalHeight()  (0)
# define isMenuBarWindow(w)     (0)
#endif

#ifdef XPM_BACKGROUND
# define XPMClearArea(a, b, c, d, e, f, g)      XClearArea((a), (b), (c), (d), (e), (f), (g))
#else
# define XPMClearArea(a, b, c, d, e, f, g)
#endif

#ifdef UTMP_SUPPORT
# if !defined(RXVT_UTMPX_FILE) || !defined(HAVE_STRUCT_UTMPX)
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
#endif

#ifdef DEBUG_CMD
# define D_CMD(x)               fprintf x ; fputc('\n', stderr)
#else
# define D_CMD(x)
#endif
#ifdef DEBUG_INIT
# define D_INIT(x)              fprintf x ; fputc('\n', stderr)
#else
# define D_INIT(x)
#endif
#ifdef DEBUG_MAIN
# define D_MAIN(x)              fprintf x ; fputc('\n', stderr)
#else
# define D_MAIN(x)
#endif
#ifdef DEBUG_SIZE
# define D_SIZE(x)              fprintf x ; fputc('\n', stderr)
#else
# define D_SIZE(x)
#endif

extern class rxvt_failure_exception { } rxvt_failure_exception;

typedef callback1<void, const char *> log_callback;
typedef callback1<int, int> getfd_callback;

extern void rxvt_vlog (const char *fmt, va_list arg_ptr);
extern void rxvt_log (const char *fmt, ...);
extern void rxvt_warn (const char *fmt, ...);
extern void rxvt_fatal (const char *fmt, ...) __attribute__ ((noreturn));
extern void rxvt_exit_failure () __attribute__ ((noreturn));

#define SET_LOCALE(locale) rxvt_set_locale (locale)
extern bool rxvt_set_locale (const char *locale);
extern void rxvt_push_locale (const char *locale);
extern void rxvt_pop_locale ();

/****************************************************************************/

#ifdef MENUBAR
# include "menubar.h"
#endif

#define BLINK_INTERVAL 0.5
#define TEXT_BLINK_INTERVAL 0.5

#ifndef __attribute__
# ifdef __GNUC__
#  if (__GNUC__ == 2 && __GNUC_MINOR__ < 5) || (__GNUC__ < 2)
#   define __attribute__(x)
#  endif
# endif
# define __attribute__(x)
#endif

/****************************************************************************/

#define LINE_LONGER     0x0001 // line is continued on the next row
#define LINE_FILTERED   0x0002 // line has been filtered
#define LINE_COMPRESSED 0x0004 // line has been compressed (NYI)

struct line_t {
   text_t *t; // terminal the text
   rend_t *r; // rendition, uses RS_ flags
   tlen_t_ l; // length of each text line, LINE_CONT == continued on next line
   uint32_t f; // flags

   bool is_longer ()
   {
     return f & LINE_LONGER;
   }

   void is_longer (int set)
   {
     if (set)
       f |= LINE_LONGER;
     else
       f &= ~LINE_LONGER;
   }

   void clear ()
   {
     t = 0;
     r = 0;
     l = 0;
     f = 0;
   }

   void touch () // call whenever a line is changed/touched/updated
   {
#if ENABLE_PERL
     f &= ~LINE_FILTERED;
#endif
   }

   void touch (int col)
   {
     max_it (l, col);
     touch ();
   }
};

/****************************************************************************/

// primivite wrapper around mbstate_t to ensure initialisation
struct mbstate {
  mbstate_t mbs;

  operator mbstate_t *() { return &mbs; }
  void reset () { memset (&mbs, 0, sizeof (mbs)); }
  mbstate () { reset (); }
};

/****************************************************************************/

#define UNICODE_MASK 0x1fffffUL

#if UNICODE3
# define COMPOSE_LO 0x40000000UL
# define COMPOSE_HI 0x400fffffUL
# define IS_COMPOSE(n) ((int32_t)(n) >= COMPOSE_LO)
#else
# if ENABLE_PERL
#  define COMPOSE_LO 0xe000UL // our _own_ routiens don't like (illegal) surrogates
#  define COMPOSE_HI 0xf8ffUL // in utf-8, so use private use area only
# else
#  define COMPOSE_LO 0xd800UL
#  define COMPOSE_HI 0xf8ffUL
# endif
# define IS_COMPOSE(n) IN_RANGE_INC ((n), COMPOSE_LO, COMPOSE_HI)
#endif

#if ENABLE_COMBINING
// compose chars are used to represent composite characters
// that are not representable in unicode, as well as characters
// not fitting in the BMP.
struct compose_char {
  unicode_t c1, c2; // any chars != NOCHAR are valid
  compose_char (unicode_t c1, unicode_t c2)
  : c1(c1), c2(c2)
  { }
};

class rxvt_composite_vec {
  vector<compose_char> v;
public:
  text_t compose (unicode_t c1, unicode_t c2 = NOCHAR);
  int expand (unicode_t c, wchar_t *r);
  compose_char *operator [](text_t c)
  {
    return c >= COMPOSE_LO && c < COMPOSE_LO + v.size ()
           ? &v[c - COMPOSE_LO]
           : 0;
  }
};

extern class rxvt_composite_vec rxvt_composite;
#endif

/****************************************************************************/

#ifdef KEYSYM_RESOURCE
  class keyboard_manager;
#endif

struct rxvt_term : zero_initialized, rxvt_vars {
  log_callback   *log_hook;               // log error messages through this hook, if != 0
  getfd_callback *getfd_hook;           // convert remote to local fd, if != 0
#if ENABLE_PERL
  rxvt_perl_term  perl;
#endif
  struct mbstate  mbstate;              // current input multibyte state

  unsigned char   want_refresh:1,
#ifdef TRANSPARENT
                  want_full_refresh:1,	/* awaiting full screen refresh      */
#endif
#if defined(XPM_BACKGROUND) || defined(TRANSPARENT)
                  am_transparent:1,	/* is a transparent term             */
                  am_pixmap_trans:1, 	/* transparency w/known root pixmap  */
#endif
                  current_screen:1,	/* primary or secondary              */
                  hate_those_clicks:1,	/* a.k.a. keep mark position         */
                  num_scr_allow:1,
                  bypass_keystate:1,
#ifdef CURSOR_BLINK
                  hidden_cursor:1,
#endif
#ifdef TEXT_BLINK
                  hidden_text:1,
#endif
#ifdef POINTER_BLANK
                  hidden_pointer:1,
#endif
                  enc_utf8:1,		/* wether locale uses utf-8 */
                  seen_input:1,         /* wether we have seen some program output yet */
                  seen_resize:1,	/* wether we had a resize event */
                  parsed_geometry:1;

  unsigned char   refresh_type,
#ifdef META8_OPTION
                  meta_char,            /* Alt-key prefix */
#endif
                  scrollbar_align,
                  selection_wait,
                  selection_type;
/* ---------- */
  short           rvideo;
  int             num_scr;              /* screen: number lines scrolled */
  int             prev_ncol,            /* screen: previous number of columns */
                  prev_nrow;            /* screen: previous number of rows */
/* ---------- */
  rend_t          rstyle;
/* ---------- */
  uint32_t        pixcolor_set[NPIXCLR_SETS];
/* ---------- */
#ifdef SELECTION_SCROLLING
  int             scroll_selection_lines;
  enum page_dirn  scroll_selection_dir;
  int             selection_save_x,
                  selection_save_y,
                  selection_save_state;
#endif
/* ---------- */
  int             csrO,       /* Hops - csr offset in thumb/slider to      */
                              /*   give proper Scroll behaviour            */
#if defined(MOUSE_WHEEL) && defined(MOUSE_SLIP_WHEELING)
                  mouse_slip_wheel_speed,
#endif
                  refresh_count,
                  refresh_limit,
                  last_bot,   /* scrollbar last bottom position            */
                  last_top,   /* scrollbar last top position               */
                  last_state, /* scrollbar last state                      */
                  scrollbar_len,
#ifdef MENUBAR
                  menu_readonly,      /* okay to alter menu? */
                  Arrows_x,
#endif
#if MENUBAR_MAX > 1
                  Nbars,
#endif
                  window_vt_x,
                  window_vt_y,
                  window_sb_x,
# ifdef POINTER_BLANK
                  pointerBlankDelay,
# endif
                  allowedxerror;
/* ---------- */
  unsigned int    ModLevel3Mask,
                  ModMetaMask,
                  ModNumLockMask;
  int             old_width,  /* last used width in screen resize          */
                  old_height; /* last used height in screen resize         */
  unsigned long   priv_modes,
                  SavedModes;
/* ---------- */
  Atom            xa[NUM_XA];
/* ---------- */
#ifdef MENUBAR
  GC              menubarGC;
#endif
#if defined(MENUBAR) || defined(RXVT_SCROLLBAR)
  GC              scrollbarGC,
                  topShadowGC,
                  botShadowGC;
#endif
#ifdef XTERM_SCROLLBAR
  GC              xscrollbarGC,
                  ShadowGC;
#endif
#ifdef PLAIN_SCROLLBAR
  GC              pscrollbarGC;
#endif
#ifdef NEXT_SCROLLBAR
  GC              blackGC,
                  whiteGC,
                  grayGC,
                  darkGC,
                  stippleGC;
  Pixmap          dimple,
                  upArrow,
                  downArrow,
                  upArrowHi,
                  downArrowHi;
#endif
/* ---------- */
  Time            selection_time,
                  selection_request_time;
  pid_t           cmd_pid;    /* process id of child */
  char *          incr_buf;
  size_t          incr_buf_size, incr_buf_fill;
/* ---------- */
  Cursor          leftptr_cursor;
/* ---------- */
#ifndef NO_BACKSPACE_KEY
  const char     *key_backspace;
#endif
#ifndef NO_DELETE_KEY
  const char     *key_delete;
#endif
  struct mouse_event MEvent;
  XComposeStatus  compose;
  ttymode_t       tio;
#ifdef UTMP_SUPPORT
# ifdef HAVE_STRUCT_UTMP
  struct utmp     ut;
# endif
# ifdef HAVE_STRUCT_UTMPX
  struct utmpx    utx;
# endif
# if (defined(HAVE_STRUCT_UTMP) && defined(HAVE_UTMP_PID)) || defined(HAVE_STRUCT_UTMPX)
  char            ut_id[5];
# endif
  int             utmp_pos;
#endif
  row_col_t       oldcursor;
#ifdef XPM_BACKGROUND
  bgPixmap_t      bgPixmap;
  XpmAttributes   xpmAttr;    /* originally loaded pixmap and its scaling */
#endif
#ifdef MENUBAR
  menu_t         *ActiveMenu,         /* currently active menu */
                 *BuildMenu;          /* the menu currently being built */
  bar_t          *CurrentBar;
# if ! (MENUBAR_MAX > 1)
  bar_t           BarList;
# endif                         /* (MENUBAR_MAX > 1) */
#endif

#if ENABLE_OVERLAY
  int ov_x, ov_y, ov_w, ov_h; // overlay dimensions
  text_t **ov_text;
  rend_t **ov_rend;

  void scr_swap_overlay ();
  void scr_overlay_new (int x, int y, int w, int h);
  void scr_overlay_off ();
  void scr_overlay_set (int x, int y,
                        text_t text,
                        rend_t rend = OVERLAY_RSTYLE);
  void scr_overlay_set (int x, int y, const char *s);
  void scr_overlay_set (int x, int y, const wchar_t *s);
#endif

  vector<void *> allocated;           // free these memory blocks with free()

  char           *env_windowid;       /* environmental variable WINDOWID */
  char           *env_display;        /* environmental variable DISPLAY  */
  char           *env_term;           /* environmental variable TERM     */
  char           *env_colorfgbg;
  char           *locale;
  char            charsets[4];
  char           *v_buffer;           /* pointer to physical buffer */
  unsigned int    v_buflen;           /* size of area to write */
  stringvec      *argv, *envv;        /* if != 0, will be freed on destroy time */

#ifdef KEYSYM_RESOURCE
  keyboard_manager *keyboard;
#endif

  const char     *rs[NUM_RESOURCES];
  /* command input buffering */
  char           *cmdbuf_ptr, *cmdbuf_endp;
  char            cmdbuf_base[CBUFSIZ];

  rxvt_salloc    *talloc;             // text line allocator
  rxvt_salloc    *ralloc;             // rend line allocator

  static vector<rxvt_term *> termlist; // a vector of all running rxvt_term's

#if ENABLE_FRILLS || ISO_14755
  // ISO 14755 entry support
  unicode_t iso14755buf;
  void commit_iso14755 ();
  int hex_keyval (XKeyEvent &ev);
# if ISO_14755
  void iso14755_51 (unicode_t ch, rend_t r = DEFAULT_RSTYLE, int x = 0, int y = -1);
  void iso14755_54 (int x, int y);
# endif
#endif

  // modifies first argument(!)
  void paste (char *data, unsigned int len);

  long vt_emask, vt_emask_perl;

  void vt_select_input ()
  {
    XSelectInput (display->display, vt, vt_emask | vt_emask_perl);
  }

#if TRANSPARENT
  void rootwin_cb (XEvent &xev);
  xevent_watcher rootwin_ev;
#endif

  void x_cb (XEvent &xev);
  void flush ();
  xevent_watcher termwin_ev;
  xevent_watcher vt_ev;
#ifdef HAVE_SCROLLBARS
  xevent_watcher scrollbar_ev;
#endif
#ifdef MENUBAR
  xevent_watcher menubar_ev;
#endif

  void check_cb (check_watcher &w); check_watcher check_ev;
  void destroy_cb (time_watcher &w); time_watcher destroy_ev;
  void flush_cb (time_watcher &w); time_watcher flush_ev;

  void pty_cb (io_watcher &w, short revents); io_watcher pty_ev;

  void incr_cb (time_watcher &w); time_watcher incr_ev;

#ifdef CURSOR_BLINK
  void cursor_blink_cb (time_watcher &w); time_watcher cursor_blink_ev;
#endif
#ifdef TEXT_BLINK
  void text_blink_cb (time_watcher &w); time_watcher text_blink_ev;
#endif

#ifndef NO_SCROLLBAR_BUTTON_CONTINUAL_SCROLLING
  void cont_scroll_cb (time_watcher &w); time_watcher cont_scroll_ev;
#endif
#ifdef SELECTION_SCROLLING
  void sel_scroll_cb (time_watcher &w); time_watcher sel_scroll_ev;
#endif
#if defined(MOUSE_WHEEL) && defined(MOUSE_SLIP_WHEELING)
  void slip_wheel_cb (time_watcher &w); time_watcher slip_wheel_ev;
#endif

#ifdef POINTER_BLANK
  void pointer_cb (time_watcher &w); time_watcher pointer_ev;
  void pointer_blank ();
#endif
  void pointer_unblank ();

  void tt_printf (const char *fmt,...);
  void tt_write (const char *data, unsigned int len);
  void pty_write ();

  void tt_winch ();

  rxvt_term ();
  ~rxvt_term ();
  void child_exit (); // child has exited, usually destroys
  void destroy ();
  void emergency_cleanup ();

  bool init (int argc, const char *const *argv);
  bool init_vars ();

  bool pty_fill ();

  void init_secondary ();
  const char **init_resources (int argc, const char *const *argv);
  const char *x_resource (const char *name);
  void init_env ();
  void set_locale (const char *locale);
  void init_xlocale ();
  void init_command (const char *const *argv);
  void run_command (const char *const *argv);
  int run_child (const char *const *argv);

  void color_aliases (int idx);
  void recolour_cursor ();
  void create_windows (int argc, const char *const *argv);
  void resize_all_windows (unsigned int newwidth, unsigned int newheight, int ignoreparent);
  void window_calc (unsigned int newwidth, unsigned int newheight);

#if USE_XIM
  rxvt_xim       *input_method;
  XIC             Input_Context;
  XIMStyle        input_style;
  XPoint          spot; // most recently sent spot position

  void im_destroy ();
  void im_cb (); im_watcher im_ev;
  void im_set_size (XRectangle &size);
  void im_set_position (XPoint &pos);
  void im_set_color (unsigned long &fg, unsigned long &bg);
  void im_set_preedit_area (XRectangle &preedit_rect, XRectangle &status_rect, const XRectangle &needed_rect);

  bool IMisRunning ();
  void IMSendSpot ();
  bool IM_get_IC (const char *modifiers);
  void IMSetStatusPosition ();
#endif

  void resize_scrollbar ();

  void pixel_position (int *x, int *y);

  void selection_click (int clicks, int x, int y);
  void selection_extend (int x, int y, int flag);
  void selection_rotate (int x, int y);

  /* autoconvert */

  // command.C
  void lookup_key (XKeyEvent &ev);
  unsigned int cmd_write (const char *str, unsigned int count);

  wchar_t next_char ();
  wchar_t cmd_getc ();
  uint32_t next_octet ();
  uint32_t cmd_get8 ();

  bool cmd_parse ();
  void mouse_report (XButtonEvent &ev);
  void button_press (XButtonEvent &ev);
  void button_release (XButtonEvent &ev);
  void focus_in ();
  void focus_out ();
  int check_our_parents ();
#ifdef PRINTPIPE
  FILE *popen_printer ();
  int pclose_printer (FILE *stream);
#endif
  void process_print_pipe ();
  void process_nonprinting (unicode_t ch);
  void process_escape_vt52 (unicode_t ch);
  void process_escape_seq ();
  void process_csi_seq ();
  void process_window_ops (const int *args, unsigned int nargs);
  char *get_to_st (unicode_t &ends_how);
  void process_dcs_seq ();
  void process_osc_seq ();
  void process_color_seq (int report, int color, const char *str, char resp);
  void process_xterm_seq (int op, const char *str, char resp);
  int privcases (int mode, unsigned long bit);
  void process_terminal_mode (int mode, int priv, unsigned int nargs, const int *arg);
  void process_sgr_mode (unsigned int nargs, const int *arg);
  void process_graphics ();
  // init.C
  void Get_Colours ();
  void get_ourmods ();
  // logging.C
  void makeutent (const char *pty, const char *hostname);
  void cleanutent ();
  // main.C
  void privileged_utmp (rxvt_privaction action);
  bool set_fonts ();
  void set_string_property (Atom prop, const char *str, int len = -1);
  void set_utf8_property (Atom prop, const char *str, int len = -1);
  void set_title (const char *str);
  void set_icon_name (const char *str);
  void set_window_color (int idx, const char *color);
  void set_colorfgbg ();
  int rXParseAllocColor (rxvt_color * screen_in_out, const char *colour);
  void set_widthheight (unsigned int newwidth, unsigned int newheight);

#ifdef MENUBAR
  // menubar.C
  void menuitem_free (menu_t *menu, menuitem_t *item);
  int action_dispatch (action_t *action);
  void menuarrow_free (char name);
  void menuarrow_add (char *string);
  char *menu_find_base (menu_t **menu, char *path);
  menu_t *menu_delete (menu_t *menu);
  menu_t *menu_add (menu_t *parent, char *path);
  void drawbox_menubar (int x, int len, int state);
  void drawtriangle (int x, int y, int state);
  void drawbox_menuitem (int y, int state);
  void menu_show ();
  void menu_display (void (rxvt_term::*update) ());
  void menu_hide_all ();
  void menu_hide ();
  void menu_clear (menu_t *menu);
  void menubar_clear ();
  bar_t *menubar_find (const char *name);
  int menubar_push (const char *name);
  void menubar_remove (const char *name);
  void menubar_dump (FILE *fp);
  void menubar_read (const char *filename);
  void menubar_dispatch (char *str);
  void draw_Arrows (int name, int state);
  void menubar_expose ();
  int menubar_mapping (int map);
  int menu_select (XButtonEvent &ev);
  void menubar_select (XButtonEvent &ev);
  void menubar_control (XButtonEvent &ev);
  void map_menuBar (int map);
#endif

  // screen.C

  void lalloc (line_t &l)
  {
    l.t = (text_t *)talloc->alloc ();
    l.r = (rend_t *)ralloc->alloc ();
  }

#if 0
  void lfree (line_t &l)
  {
    talloc->free (l.t);
    ralloc->free (l.r);
  }
#endif

  void lresize (line_t &l)
  {
    if (!l.t)
      return;

    l.t = (text_t *)talloc->alloc (l.t, prev_ncol * sizeof (text_t));
    l.r = (rend_t *)ralloc->alloc (l.r, prev_ncol * sizeof (rend_t));

    l.l = min (l.l, ncol);

    if (ncol > prev_ncol)
      scr_blank_line (l, prev_ncol, ncol - prev_ncol, DEFAULT_RSTYLE);
  }

  int fgcolor_of (rend_t r)
  {
    int base = GET_BASEFG (r);
#ifndef NO_BRIGHTCOLOR
    if (r & RS_Bold
# if ENABLE_STYLES
        && OPTION (Opt_intensityStyles)
# endif
        && IN_RANGE_INC (base, minCOLOR, minBrightCOLOR))
      base += minBrightCOLOR - minCOLOR;
#endif
    return base;
  }

  int bgcolor_of (rend_t r)
  {
    int base = GET_BASEBG (r);
#ifndef NO_BRIGHTCOLOR
    if (r & RS_Blink
# if ENABLE_STYLES
        && OPTION (Opt_intensityStyles)
# endif
        && IN_RANGE_INC (base, minCOLOR, minBrightCOLOR))
      base += minBrightCOLOR - minCOLOR;
#endif
    return base;
  }

  bool option (uint32_t opt)
  {
    return OPTION (opt);
  }

  void set_option (uint32_t opt, bool set)
  {
    if (set)
      options |= opt;
    else
      options &= ~opt;
  }

  void scr_blank_line (line_t &l, unsigned int col, unsigned int width, rend_t efs);
  void scr_blank_screen_mem (line_t &l, rend_t efs);
  int scr_scroll_text (int row1, int row2, int count);
  void scr_reset ();
  void scr_release ();
  void scr_clear (bool really = false);
  void scr_refresh (unsigned char refresh_type);
  bool scr_refresh_rend (rend_t mask, rend_t value);
  void scr_erase_screen (int mode);
#if ENABLE_FRILLS
  void scr_erase_savelines ();
  void scr_backindex ();
  void scr_forwardindex ();
#endif
  void scr_touch (bool refresh);
  void scr_expose (int x, int y, int width, int height, bool refresh);
  rxvt_fontset *scr_find_fontset (rend_t r = DEFAULT_RSTYLE);
  void scr_recolour ();
  void scr_remap_chars ();
  void scr_remap_chars (line_t &l);

  void scr_poweron ();
  void scr_cursor (int mode);
  void scr_do_wrap ();
  int scr_change_screen (int scrn);
  void scr_color (unsigned int color, int fgbg);
  void scr_rendition (int set, int style);
  void scr_add_lines (const wchar_t *str, int len, int minlines = 0);
  void scr_backspace ();
  void scr_tab (int count, bool ht = false);
  void scr_gotorc (int row, int col, int relative);
  void scr_index (enum page_dirn direction);
  void scr_erase_line (int mode);
  void scr_E ();
  void scr_insdel_lines (int count, int insdel);
  void scr_insdel_chars (int count, int insdel);
  void scr_scroll_region (int top, int bot);
  void scr_cursor_visible (int mode);
  void scr_autowrap (int mode);
  void scr_relative_origin (int mode);
  void scr_insert_mode (int mode);
  void scr_set_tab (int mode);
  void scr_rvideo_mode (int mode);
  void scr_report_position ();
  void set_font_style ();
  void scr_charset_choose (int set);
  void scr_charset_set (int set, unsigned int ch);
  int scr_move_to (int y, int len);
  int scr_page (enum page_dirn direction, int nlines);
  int scr_changeview (unsigned int oldviewstart);
  void scr_bell ();
  void scr_printscreen (int fullhist);
  void scr_xor_rect (int beg_row, int beg_col, int end_row, int end_col, rend_t rstyle1, rend_t rstyle2);
  void scr_xor_span (int beg_row, int beg_col, int end_row, int end_col, rend_t rstyle);
  void scr_reverse_selection ();
  void scr_dump (int fd);
  void selection_check (int check_more);
  void selection_paste (Window win, Atom prop, bool delete_prop);
  void selection_property (Window win, Atom prop);
  void selection_request (Time tm, int x, int y);
  int selection_request_other (Atom target, int selnum);
  void selection_clear ();
  void selection_make (Time tm);
  bool selection_grab (Time tm);
  void selection_start_colrow (int col, int row);
  void selection_delimit_word (enum page_dirn dirn, const row_col_t *mark, row_col_t *ret);
  void selection_extend_colrow (int32_t col, int32_t row, int button3, int buttonpress, int clickchange);
  void selection_remove_trailing_spaces ();
  void selection_send (const XSelectionRequestEvent &rq);

#if defined(NEXT_SCROLLBAR)
  // scrollbar-next.C
  Pixmap renderPixmap (const char *const *data, int width, int height);
  void init_scrollbar_stuff ();
  void drawBevel (Drawable d, int x1, int y1, int w, int h);
  int scrollbar_show_next (int update, int last_top, int last_bot, int scrollbar_len);
#endif

#if defined(RXVT_SCROLLBAR)
  // scrollbar-rxvt.C
  void Draw_button (int x, int y, int state, int dirn);
  int scrollbar_show_rxvt (int update, int last_top, int last_bot, int scrollbar_len);
#endif

#if defined(XTERM_SCROLLBAR)
  // scrollbar-xterm.C
  int scrollbar_show_xterm (int update, int last_top, int last_bot, int scrollbar_len);
#endif

#if defined(PLAIN_SCROLLBAR)
  // scrollbar-plain.C
  int scrollbar_show_plain (int update, int last_top, int last_bot, int scrollbar_len);
#endif

  // scrollbar.C
  int scrollbar_mapping (int map);
  int scrollbar_show (int update);
  void setup_scrollbar (const char *scrollalign, const char *scrollstyle, const char *thickness);

  // xdefaults.C
  void get_options (int argc, const char *const *argv);
  int parse_keysym (const char *str, const char *arg);
  void get_xdefaults (FILE *stream, const char *name);
  void extract_resources ();
  // xpm.C
  int scale_pixmap (const char *geom);
  void resize_pixmap ();
  Pixmap set_bgPixmap (const char *file);
};

/*
 *****************************************************************************
 * PROTOTYPES
 *****************************************************************************
 */
#ifdef PROTOTYPES
# define __PROTO(p)     p
#else
# define __PROTO(p)     ()
#endif

#ifdef DEBUG_malloc
# include "dmalloc.h"           /* This comes last */
#endif

#endif                          /* _RXVT_H_ */

