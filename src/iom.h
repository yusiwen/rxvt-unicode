/*
    iom.h -- generic I/O multiplexer
    Copyright (C) 2003-2006 Marc Lehmann <gvpe@schmorp.de>
 
    This file is part of GVPE.

    GVPE is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.
 
    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
 
    You should have received a copy of the GNU General Public License
    along with gvpe; if not, write to the Free Software
    Foundation, Inc. 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef IOM_H__
#define IOM_H__

// required:
// - a vector template like simplevec or stl's vector
// - defines for all watcher types required in your app
// edit iom_conf.h as appropriate.
#include "iom_conf.h"

#if IOM_CHILD
# undef IOM_SIG
# define IOM_SIG 1
#endif

#include "callback.h"

typedef double tstamp;
extern tstamp NOW;

// TSTAMP_MAX must still fit into a positive struct timeval
#define TSTAMP_MAX (double)(1UL<<31)

//#define IOM_LIBEVENT "event.h" *NOT* a supported feature
#ifdef IOM_LIBEVENT
# include <sys/time.h>
# include IOM_LIBEVENT
# undef IOM_IO
# define IOM_IO 1
# undef IOM_TIME
# define IOM_TIME 1
# undef IOM_IDLE // NYI
# undef IOM_SIG // NYI
# undef IOM_CHILD // NYI
#endif

struct watcher;
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
#if IOM_SIG
struct sig_watcher;
#endif
#if IOM_CHILD
struct child_watcher;
#endif

template<class watcher>
struct io_manager_vec : vector<watcher *> {
  void erase_unordered (unsigned int pos)
  {
    watcher *w = (*this)[this->size () - 1];
    this->pop_back ();

    if (!this->empty ())
      if (((*this)[pos] = w)) // '=' is correct!
        w->active = pos + 1;
  }
};

// only used as a namespace, and for initialisation purposes
class io_manager {
  template<class watcher>
  static void reg (watcher &w, io_manager_vec<watcher> &queue);

  template<class watcher>
  static void unreg (watcher &w, io_manager_vec<watcher> &queue);

public:
#if IOM_TIME
  // fetch time only
  static tstamp now ();

  // set NOW
  static void set_now ();
#endif

  // register a watcher
#ifndef IOM_LIBEVENT
#if IOM_IO
  static void reg (io_watcher    &w); static void unreg (io_watcher    &w);
#endif
#if IOM_TIME
  static void reg (time_watcher  &w); static void unreg (time_watcher  &w);
#endif
#if IOM_SIG
  static void reg (sig_watcher   &w); static void unreg (sig_watcher   &w);
#endif
#if IOM_CHECK
  static void reg (check_watcher &w); static void unreg (check_watcher &w);
#endif
#endif
#if IOM_IDLE
  static void reg (idle_watcher  &w); static void unreg (idle_watcher  &w);
#endif
#if IOM_CHILD
  static void reg (child_watcher &w); static void unreg (child_watcher &w);
#endif
  
  static void loop ();
};

struct watcher {
  int active; /* 0 == inactive, else index into respective vector */

  bool is_active () { return active; }

  watcher () : active (0) { }
};

#if IOM_IO
#ifdef IOM_LIBEVENT
enum { EVENT_UNDEF = -1, EVENT_NONE = 0, EVENT_READ = EV_READ, EVENT_WRITE = EV_WRITE };

void iom_io_c_callback (int fd, short events, void *data);

struct io_watcher : watcher, callback<void (io_watcher &, short)> {
  struct event ev;
  int fd;
  short events;

  void set (int fd_, short events_);
  void set (short events_) { set (fd, events_); }
  void start () { if (!active) event_add (&ev, 0); active = 1; }
  void start (int fd_, short events_) { set (fd_, events_); start (); }
  void stop () { if (active) event_del (&ev); active = 0; }

  template<class O, class M>
  io_watcher (O object, M method)
  : callback<void (io_watcher &, short)> (object, method)
  { }
  ~io_watcher () { stop (); }
};
#else
enum { EVENT_UNDEF = -1, EVENT_NONE = 0, EVENT_READ = 1, EVENT_WRITE = 2 };

struct io_watcher : watcher, callback<void (io_watcher &, short)> {
  int fd;
  short events;

  void set (int fd_, short events_) { fd = fd_; events = events_; }

  void set (short events_) { set (fd, events_); }
  void start () { io_manager::reg (*this); }
  void start (int fd_, short events_) { set (fd_, events_); start (); }
  void stop () { io_manager::unreg (*this); }

  template<class O, class M>
  io_watcher (O object, M method)
  : callback<void (io_watcher &, short)> (object, method)
  { }
  ~io_watcher () { stop (); }
};
#endif
#endif

#if IOM_TIME
#ifdef IOM_LIBEVENT
void iom_time_c_callback (int fd, short events, void *data);

struct time_watcher : watcher, callback<void (time_watcher &)> {
  struct event ev;
  tstamp at;

  void trigger ();

  void set (tstamp when)
  {
    at = when;
    if (active)
      start ();
  }
  void operator () () { trigger (); }
  void start ();
  void start (tstamp when) { at = when; start (); }
  void stop () { if (active) evtimer_del (&ev); active = 0; }

  template<class O, class M>
  time_watcher (O object, M method)
  : callback<void (time_watcher &)> (object, method), at (0)
  { }
  ~time_watcher () { stop (); }
};
#else
struct time_watcher : watcher, callback<void (time_watcher &)> {
  tstamp at;

  void trigger ();

  void set (tstamp when) { at = when; }
  void operator () () { trigger (); }
  void start () { io_manager::reg (*this); }
  void start (tstamp when) { set (when); start (); }
  void stop () { io_manager::unreg (*this); }

  template<class O, class M>
  time_watcher (O object, M method)
  : callback<void (time_watcher &)> (object, method), at (0)
  { }
  ~time_watcher () { stop (); }
};
#endif
#endif

#if IOM_CHECK
// run before checking for new events
struct check_watcher : watcher, callback<void (check_watcher &)> {
  void start () { io_manager::reg (*this); }
  void stop () { io_manager::unreg (*this); }

  template<class O, class M>
  check_watcher (O object, M method)
  : callback<void (check_watcher &)> (object, method)
  { }
  ~check_watcher () { stop (); }
};
#endif

#if IOM_IDLE
// run after checking for any i/o, but before waiting
struct idle_watcher : watcher, callback<void (idle_watcher &)> {
  void start () { io_manager::reg (*this); }
  void stop () { io_manager::unreg (*this); }

  template<class O, class M>
  idle_watcher (O object, M method)
    : callback<void (idle_watcher &)> (object, method)
    { }
  ~idle_watcher () { stop (); }
};
#endif

#if IOM_SIG
struct sig_watcher : watcher, callback<void (sig_watcher &)> {
  int signum;

  void start (int signum);
  void stop () { io_manager::unreg (*this); }

  template<class O, class M>
  sig_watcher (O object, M method)
  : callback<void(sig_watcher &)> (object, method), signum (0)
  { }
  ~sig_watcher () { stop (); }
};
#endif

#if IOM_CHILD
struct child_watcher : watcher, callback<void (child_watcher &, int)> {
  int /*pid_t*/ pid;

  void start (int pid) { this->pid = pid; io_manager::reg (*this); }
  void stop () { io_manager::unreg (*this); }

  template<class O, class M>
  child_watcher (O object, M method)
  : callback<void (child_watcher &, int)> (object, method), pid (0)
  { }
  ~child_watcher () { stop (); }
};
#endif

#endif

