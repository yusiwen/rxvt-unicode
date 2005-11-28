#ifndef DEFAULTFONT_H_
#define DEFAULTFONT_H_

#include <X11/Xlib.h>
#if XFT
# include <X11/Xft/Xft.h>
#endif

#ifdef HAVE_XSETLOCALE
# define X_LOCALE
# include <X11/Xlocale.h>
#else
# ifdef HAVE_SETLOCALE
#  include <clocale>
# endif
#endif				/* HAVE_XLOCALE */

#ifdef HAVE_NL_LANGINFO
# include <langinfo.h>
#endif

#include <inttypes.h>

#include "feature.h"
#include "encoding.h"
#include "rxvtutil.h"
#include "rxvttoolkit.h"

struct rxvt_term;

struct rxvt_fontprop {
  enum {
    unset  = -1,
    medium = 100, bold = 200,
    roman  = 0, italic = 100,
  };
  int width, height;
  int weight, slant;
};

struct rxvt_drawable {
  rxvt_display *display;
#if XFT
  XftDraw *xftdrawable;
  operator XftDraw *();
#endif
  Drawable drawable;

  rxvt_drawable (rxvt_display *display, Drawable drawable)
  : display(display),
#if XFT
    xftdrawable(0),
#endif
    drawable(drawable)
  { }

#if XFT
  ~rxvt_drawable ();
#endif

  operator Drawable() { return drawable; }
};

struct rxvt_font {
  // managed by the fontset
  rxvt_term *r;
  void set_term (rxvt_term *r) { this->r = r; }

  char *name;
  codeset cs;
  bool loaded; // wether we tried loading it before (not wether it's loaded)

  // managed by the font object
  int ascent, descent,
      width, height;

  void set_name (char *name);

  rxvt_font () { name = 0; }
  virtual ~rxvt_font () { free (name); };

  virtual void clear () { };

  void clear_rect (rxvt_drawable &d, int x, int y, int w, int h, int color);

  virtual rxvt_fontprop properties () = 0;

  virtual bool load (const rxvt_fontprop &morph) = 0;
  virtual bool has_char (uint32_t unicode, const rxvt_fontprop *prop, bool &careful) = 0;

  virtual void draw (rxvt_drawable &d,
                     int x, int y,
                     const text_t *text, int len,
                     int fg, int bg) = 0;
};

#define FONT_UNREF(f) do { (f)->clear (); delete (f); } while (0)

struct rxvt_fallback_font;

struct rxvt_fontset {
  char *fontdesc;

  rxvt_fontset (rxvt_term *r);
  ~rxvt_fontset ();

  bool populate (const char *desc);
  void set_prop (const rxvt_fontprop &prop) { this->prop = prop; }
  int find_font (uint32_t unicode);
  int find_font (const char *name) const;
  bool realize_font (int i);

  // font-id's MUST fit into a signed 16 bit integer, and within 0..255
  rxvt_font *operator [] (int id) const
  {
    return fonts[id & 0x7f];
  }

private:
  rxvt_term *r;
  rxvt_fontprop prop;
  simplevec<rxvt_font *> fonts;
  const rxvt_fallback_font *fallback;

  typedef unsigned char pagemap[256];
  vector<pagemap *> fmap;

  void clear ();
  rxvt_font *new_font (const char *name, codeset cs);
  void add_fonts (const char *desc);
};

#endif /* _DEFAULTFONT_H_ */

