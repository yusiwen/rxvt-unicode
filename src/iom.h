/*
    iom.h -- generic I/O multiplexor
    Copyright (C) 2003 Marc Lehmann <pcg@goof.com>
 
    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.
 
    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
 
    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc. 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#ifndef VPE_IOM_H__
#define VPE_IOM_H__

#include <cassert>

#include "callback.h"
#include "rxvtvec.h"

#ifndef IOM_IO
# define IOM_IO 1
#endif
#ifndef IOM_TIME
# define IOM_TIME 1
#endif
#ifndef IOM_CHECK
# define IOM_CHECK 1
#endif
#ifndef IOM_IDLE
# define IOM_IDLE 0
#endif

typedef double tstamp;
extern tstamp NOW;

#if IOM_IO
  struct io_watcher;
#endif
#if IOM_TIME
  struct time_watcher;
#endif
#if IOM_CHECK
  struct check_watcher;
#endif
#if IOM_IDLE
  struct idle_watcher;
#endif

template<class watcher>
struct io_manager_vec : protected simplevec<watcher *> {
  friend class io_manager;
protected:
  void erase_unordered (unsigned int pos)
  {
    watcher *w = (*this)[size () - 1];
    pop_back ();

    if (size ())
      if ((*this)[pos] = w)
        w->active = pos + 1;
  }
};

class io_manager {
#if IOM_IO
  io_manager_vec<io_watcher>    iow;
#endif
#if IOM_CHECK
  io_manager_vec<check_watcher> cw;
#endif
#if IOM_TIME
  io_manager_vec<time_watcher>  tw;
#endif
#if IOM_IDLE
  io_manager_vec<idle_watcher>  iw;
#endif

  template<class watcher>
  void reg (watcher *w, simplevec<watcher *> &queue);

  template<class watcher>
  void unreg (watcher *w, simplevec<watcher *> &queue);

public:
  // register a watcher
#if IOM_IO
  void reg (io_watcher    *w); void unreg (io_watcher    *w);
#endif
#if IOM_TIME
  void reg (time_watcher  *w); void unreg (time_watcher  *w);
#endif
#if IOM_CHECK
  void reg (check_watcher *w); void unreg (check_watcher *w);
#endif
#if IOM_IDLE
  void reg (idle_watcher  *w); void unreg (idle_watcher  *w);
#endif
  
  void loop ();

  io_manager ();
  ~io_manager ();
};

extern io_manager iom; // a singleton, together with it's construction/destruction problems.

struct watcher {
  int active; /* 0 == inactive, else index into respective vector */

  watcher() : active(0) { }
};

#if IOM_IO
enum { EVENT_READ = 1, EVENT_WRITE = 2 };

struct io_watcher : watcher, callback2<void, io_watcher &, short> {
  int fd;
  short events;

  void set (int fd_, short events_) { fd = fd_; events = events_; }

  void set (short events_) { set (fd, events_); }
  void start () { iom.reg (this); }
  void start (int fd_, short events_) { set (fd_, events_); iom.reg (this); }
  void stop () { iom.unreg (this); }

  template<class O1, class O2>
  io_watcher (O1 *object, void (O2::*method)(io_watcher &, short))
  : callback2<void, io_watcher &, short>(object,method)
  { }
  ~io_watcher () { stop (); }
};
#endif

#if IOM_TIME
struct time_watcher : watcher, callback1<void, time_watcher &> {
  tstamp at;

  void trigger ();

  void set (tstamp when) { at = when; }
  void operator ()() { trigger (); }
  void start () { iom.reg (this); }
  void start (tstamp when) { set (when); iom.reg (this); }
  void stop () { iom.unreg (this); }

  template<class O1, class O2>
  time_watcher (O1 *object, void (O2::*method)(time_watcher &))
  : callback1<void, time_watcher &>(object,method)
  { }
  ~time_watcher () { stop (); }
};
#endif

#if IOM_CHECK
// run before checking for new events
struct check_watcher : watcher, callback1<void, check_watcher &> {
  void start () { iom.reg (this); }
  void stop () { iom.unreg (this); }

  template<class O1, class O2>
  check_watcher (O1 *object, void (O2::*method)(check_watcher &))
  : callback1<void, check_watcher &>(object,method)
  { }
  ~check_watcher () { stop (); }
};
#endif

#if IOM_IDLE
// run after checking for any i/o, but before waiting
struct idle_watcher : watcher, callback1<void, idle_watcher &> {
  void start () { iom.reg (this); }
  void stop () { iom.unreg (this); }

  template<class O1, class O2>
  idle_watcher (O1 *object, void (O2::*method)(idle_watcher &))
    : callback1<void, idle_watcher &>(object,method)
    { }
  ~idle_watcher () { stop (); }
};
#endif

#endif

