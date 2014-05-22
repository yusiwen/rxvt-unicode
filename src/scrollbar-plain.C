/*----------------------------------------------------------------------*
 * File:	scrollbar-plain.C
 *----------------------------------------------------------------------*
 *
 * Copyright (c) 1997,1998 mj olesen <olesen@me.QueensU.CA>
 * Copyright (c) 1999-2001 Geoff Wing <gcw@pobox.com>
 * Copyright (c) 2004-2006 Marc Lehmann <schmorp@schmorp.de>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
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
 *----------------------------------------------------------------------*/

#include "../config.h"		/* NECESSARY */
#include "rxvt.h"		/* NECESSARY */

/*----------------------------------------------------------------------*/
#if defined(PLAIN_SCROLLBAR)

int
scrollBar_t::show_plain (int update)
{
  int xsb = 0;
  int sbwidth = width - 1;

  if ((init & SB_STYLE_PLAIN) == 0)
    {
      XGCValues gcvalue;

      init |= SB_STYLE_PLAIN;
      gcvalue.foreground = term->pix_colors_focused[Color_scroll];

      pscrollbarGC = XCreateGC (term->dpy, win, GCForeground, &gcvalue);
    }

  xsb = term->option (Opt_scrollBar_right) ? 1 : 0;

  if (update)
    {
      if (last_top < top)
        XClearArea (term->dpy, win,
                    0, last_top,
                    sbwidth + 1, top - last_top, False);

      if (bot < last_bot)
        XClearArea (term->dpy, win,
                    0, bot,
                    sbwidth + 1, last_bot - bot, False);
    }
  else
    XClearWindow (term->dpy, win);

  /* scrollbar slider */
  XFillRectangle (term->dpy, win, pscrollbarGC,
                  1 - xsb, top, sbwidth, bot - top);

  return 1;
}

#endif

