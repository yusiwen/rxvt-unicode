=head1 NAME

rxvtperl - rxvt-unicode's embedded perl interpreter

=head1 SYNOPSIS

* Put your scripts into F<@@RXVT_LIBDIR@@/urxvt/perl-ext/>, they will be loaded automatically.

* Each script will only be loaded once, even in urxvtd, and will be valid
globally.

* Scripts are evaluated in a 'use strict' and 'use utf8' environment, and
thus must be encoded as UTF-8.

   sub on_sel_grab {
      warn "you selected ", $_[0]->selection;
      ()
   }

   1

=head1 DESCRIPTION

=head2 Hooks

The following subroutines can be declared in loaded scripts, and will be called
whenever the relevant event happens.

All of them must return a boolean value. If it is true, then the event
counts as being I<consumed>, and the invocation of other hooks is skipped,
and the relevant action might not be carried out by the C++ code.

When in doubt, return a false value (preferably C<()>).

=over 4

=item on_init $term

Called after a new terminal object has been initialized, but before
windows are created or the command gets run.

=item on_reset $term

Called after the screen is "reset" for any reason, such as resizing or
control sequences. Here is where you can react on changes to size-related
variables.

=item on_start $term

Called at the very end of initialisation of a new terminal, just before
returning to the mainloop.

=item on_sel_make $term, $eventtime

Called whenever a selection has been made by the user, but before the
selection text is copied, so changes to the beginning, end or type of the
selection will be honored.

Returning a true value aborts selection making by urxvt, in which case you
have to make a selection yourself by calling C<< $term->selection_grab >>.

=item on_sel_grab $term, $eventtime

Called whenever a selection has been copied, but before the selection is
requested from the server.  The selection text can be queried and changed
by calling C<< $term->selection >>.

Returning a true value aborts selection grabbing. It will still be hilighted.

=item on_focus_in $term

Called whenever the window gets the keyboard focus, before urxvt does
focus in processing.

=item on_focus_out $term

Called wheneever the window loses keyboard focus, before urxvt does focus
out processing.

=item on_view_change $term, $offset

Called whenever the view offset changes, i..e the user or program
scrolls. Offset C<0> means display the normal terminal, positive values
show this many lines of scrollback.

=item on_scroll_back $term, $lines, $saved

Called whenever lines scroll out of the terminal area into the scrollback
buffer. C<$lines> is the number of lines scrolled out and may be larger
than the scroll back buffer or the terminal.

It is called before lines are scrolled out (so rows 0 .. min ($lines - 1,
$nrow - 1) represent the lines to be scrolled out). C<$saved> is the total
number of lines that will be in the scrollback buffer.

=item on_tty_activity $term *NYI*

Called whenever the program(s) running in the urxvt window send output.

=item on_refresh_begin $term

Called just before the screen gets redrawn. Can be used for overlay
or similar effects by modify terminal contents in refresh_begin, and
restoring them in refresh_end. The built-in overlay and selection display
code is run after this hook, and takes precedence.

=item on_refresh_end $term

Called just after the screen gets redrawn. See C<on_refresh_begin>.

=back

=head2 Functions in the C<urxvt> Package

=over 4

=item urxvt::fatal $errormessage

Fatally aborts execution with the given error message. Avoid at all
costs! The only time this is acceptable is when the terminal process
starts up.

=item urxvt::warn $string

Calls C<rxvt_warn> witht eh given string which should not include a
newline. The module also overwrites the C<warn> builtin with a function
that calls this function.

Using this function has the advantage that its output ends up in the
correct place, e.g. on stderr of the connecting urxvtc client.

=item $cellwidth = urxvt::wcswidth $string

Returns the number of screen-cells this string would need. Correctly
accounts for wide and combining characters.

=item $time = urxvt::NOW

Returns the "current time" (as per the event loop).

=cut

package urxvt;

use strict;

our $term;
our @HOOKNAME;
our $LIBDIR;

BEGIN {
   urxvt->bootstrap;

   # overwrite perl's warn
   *CORE::GLOBAL::warn = sub {
      my $msg = join "", @_;
      $msg .= "\n"
         unless $msg =~ /\n$/;
      urxvt::warn ($msg);
   };
}

my $verbosity = $ENV{URXVT_PERL_VERBOSITY} || 10;

sub verbose {
   my ($level, $msg) = @_;
   warn "$msg\n"; #d#
}

my @invoke_cb;

# called by the rxvt core
sub invoke {
   local $term = shift;
   my $htype = shift;

   my $cb = $invoke_cb[$htype];

   verbose 10, "$HOOKNAME[$htype] (" . (join ", ", $term, @_) . ")"
      if $verbosity >= 10;

   while (my ($k, $v) = each %$cb) {
      return 1 if $v->($term, @_);
   }

   0
}

# find on_xxx subs in the package and register them
# as hooks
sub register_package($) {
   my ($pkg) = @_;

   for my $hook (0.. $#HOOKNAME) {
      my $name = $HOOKNAME[$hook];

      my $ref = $pkg->can ("on_" . lc $name)
         or next;

      $invoke_cb[$hook]{$ref*1} = $ref;
      set_should_invoke $hook, 1;
   }
}

my $script_pkg = "script0000";
my %script_pkg;

# load a single script into its own package, once only
sub load_script($) {
   my ($path) = @_;

   $script_pkg{$path} ||= do {
      my $pkg = $script_pkg++;
      verbose 3, "loading script '$path' into package '$pkg'";

      open my $fh, "<:raw", $path
         or die "$path: $!";

      eval "package $pkg; use strict; use utf8;\n"
         . "#line 1 \"$path\"\n"
         . do { local $/; <$fh> }
         or die "$path: $@";

      register_package $pkg;

      $pkg
   };
}

load_script $_ for grep -f $_, <$LIBDIR/perl-ext/*>;


=back

=head2 The C<urxvt::term> Class

=over 4

=item ($row, $col) = $term->selection_mark ([$row, $col])

=item ($row, $col) = $term->selection_beg ([$row, $col])

=item ($row, $col) = $term->selection_end ([$row, $col])

Return the current values of the selection mark, begin or end positions,
and optionally set them to new values.

=item $success = $term->selection_grab ($eventtime)

Try to request the primary selection from the server (for example, as set
by the next method).

=item $oldtext = $term->selection ([$newtext])

Return the current selection text and optionally replace it by C<$newtext>.

=item $term->scr_overlay ($x, $y, $text)

Create a simple multi-line overlay box. See the next method for details.

=cut

sub urxvt::term::scr_overlay {
   my ($self, $x, $y, $text) = @_;

   my @lines = split /\n/, $text;

   my $w = 0;
   for (map urxvt::wcswidth $_, @lines) {
      $w = $_ if $w < $_;
   }

   $self->scr_overlay_new ($x, $y, $w, scalar @lines);
   $self->scr_overlay_set (0, $_, $lines[$_]) for 0.. $#lines;
}

=item $term->scr_overlay_new ($x, $y, $width, $height)

Create a new (empty) overlay at the given position with the given
width/height. A border will be put around the box. If either C<$x> or
C<$y> is negative, then this is counted from the right/bottom side,
respectively.

=item $term->scr_overlay_off

Switch the overlay off again.

=item $term->scr_overlay_set_char ($x, $y, $char, $rend = OVERLAY_RSTYLE)

Put a single character (specified numerically) at the given overlay
position.

=item $term->scr_overlay_set ($x, $y, $text)

Write a string at the given position into the overlay.

=back

=head2 The C<urxvt::timer> Class

This class implements timer watchers/events. Time is represented as a
fractional number of seconds since the epoch. Example:

   # create a digital clock display in upper right corner
   $term->{timer} = urxvt::timer
                    ->new
                    ->start (urxvt::NOW)
                    ->cb (sub {
                       my ($timer) = @_;
                       my $time = $timer->at;
                       $timer->start ($time + 1);
                       $self->scr_overlay (-1, 0, 
                          POSIX::strftime "%H:%M:%S", localtime $time);
                    });

=over 4

=item $timer = new urxvt::timer

Create a new timer object in stopped state.

=item $timer = $timer->cb (sub { my ($timer) = @_; ... })

Set the callback to be called when the timer triggers.

=item $tstamp = $timer->at

Return the time this watcher will fire next.

=item $timer = $timer->set ($tstamp)

Set the time the event is generated to $tstamp.

=item $timer = $timer->start

Start the timer.

=item $timer = $timer->start ($tstamp)

Set the event trigger time to C<$tstamp> and start the timer.

=item $timer = $timer->stop

Stop the timer.

=back

=head2 The C<urxvt::iow> Class

This class implements io watchers/events. Example:

  $term->{socket} = ...
  $term->{iow} = urxvt::iow
                 ->new
                 ->fd (fileno $term->{socket})
                 ->events (1) # wait for read data
                 ->start
                 ->cb (sub {
                   my ($iow, $revents) = @_;
                   # $revents must be 1 here, no need to check
                   sysread $term->{socket}, my $buf, 8192
                      or end-of-file;
                 });


=over 4

=item $iow = new urxvt::iow

Create a new io watcher object in stopped state.

=item $iow = $iow->cb (sub { my ($iow, $reventmask) = @_; ... })

Set the callback to be called when io events are triggered. C<$reventmask>
is a bitset as described in the C<events> method.

=item $iow = $iow->fd ($fd)

Set the filedescriptor (not handle) to watch.

=item $iow = $iow->events ($eventmask)

Set the event mask to watch. Bit #0 (value C<1>) enables watching for read
data, Bit #1 (value C<2>) enables watching for write data.

=item $iow = $iow->start

Start watching for requested events on the given handle.

=item $iow = $iow->stop

Stop watching for events on the given filehandle.

=back

=head1 AUTHOR

 Marc Lehmann <pcg@goof.com>
 http://software.schmorp.de/pkg/rxvt-unicode

=cut

1
