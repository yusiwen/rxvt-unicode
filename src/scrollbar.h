#ifndef SCROLLBAR_H
#define SCROLLBAR_H

#include <X11/Xlib.h>

struct rxvt_term;

#define R_SB_NEXT               1
#define R_SB_XTERM              2
#define R_SB_PLAIN              4
#define R_SB_RXVT               8

struct scrollBar_t {
  char            state;        /* scrollbar state                          */
  char            init;         /* scrollbar has been initialised           */
  unsigned int    beg;          /* slider sub-window begin height           */
  unsigned int    end;          /* slider sub-window end height             */
  unsigned int    top;          /* slider top position                      */
  unsigned int    bot;          /* slider bottom position                   */
  unsigned int    style;        /* style: rxvt, xterm, next                 */
  unsigned int    width;        /* scrollbar width                          */
  int             shadow;       /* scrollbar shadow width                   */
  int             last_bot;     /* scrollbar last bottom position           */
  int             last_top;     /* scrollbar last top position              */
  int             last_state;   /* scrollbar last state                     */
  int             len;
  unsigned char   align;
  Window          win;
  Cursor          leftptr_cursor;
  int             (rxvt_term::*update)(int, int, int, int);

  void setIdle()   { state =  1 ; }
  void setMotion() { state = 'm'; }
  void setUp()     { state = 'U'; }
  void setDn()     { state = 'D'; }

  bool upButton (int y)
  {
    if (style == R_SB_NEXT)
      return y > end && y <= end + width + 1;
    if (style == R_SB_RXVT)
      return y < beg;
    return false;
  }
  bool dnButton (int y)
  {
    if (style == R_SB_NEXT)
      return y > end + width + 1;
    if (style == R_SB_RXVT)
      return y > end;
    return false;
  }
};

#define scrollbar_TotalWidth()  (scrollBar.width + scrollBar.shadow * 2)
#define scrollbar_isMotion()    (scrollBar.state == 'm')
#define scrollbar_isUp()        (scrollBar.state == 'U')
#define scrollbar_isDn()        (scrollBar.state == 'D')
#define scrollbar_isUpDn()      (scrollbar_isUp () || scrollbar_isDn ())

#define SCROLLNEXT_MINHEIGHT    SB_THUMB_MIN_HEIGHT
#define SCROLLRXVT_MINHEIGHT    10

#define scrollbar_minheight()   (scrollBar.style == R_SB_NEXT        \
                                 ? SCROLLNEXT_MINHEIGHT                 \
                                 : SCROLLRXVT_MINHEIGHT)
#define scrollbar_above_slider(y)       ((y) < scrollBar.top)
#define scrollbar_below_slider(y)       ((y) > scrollBar.bot)
#define scrollbar_position(y)           ((y) - scrollBar.beg)
#define scrollbar_size()                (scrollBar.end - scrollBar.beg \
                                         - scrollbar_minheight ())

#define R_SB_ALIGN_CENTRE       0
#define R_SB_ALIGN_TOP          1
#define R_SB_ALIGN_BOTTOM       2

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

#endif
