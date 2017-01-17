#!/bin/sh

# open a new terminal with screen and ncmpcpp
open_new() {
  urxvtc -geometry 120x40 -e screen ncmpcpp &
  exit 0
}

# open ncmpcpp in a running attached screen
# tty/pts number passed in as $1
# this may need tweaking...
open_in_existing() {
  screen -X -S terminal screen -t ncmpcpp ncmpcpp &
  exit 0
}

# reattach a detached screen and open ncmpcpp in it
# tty/pid number is pass in as $1
# can you use -R and -t here?
open_reattach() {
  urxvtc -geometry 120x40 -e screen -X -S terminal -t ncmpcpp screen ncmpcpp &
  exit 0
}

attached=$(screen -ls | awk '/Attached/ {print $1}' | head -n1 | cut -d '.' -f 1)
detached=$(screen -ls | awk '/Detached/ {print $1}' | head -n1 | cut -d '.' -f 1)
# if an attached is found...
if [ -n "$attached" ]; then 
    open_in_existing $attached
# if a detached is found...
elif [ -n "$detached" ];then 
    open_reattach $detached
# if nothing's found...
else open_new
fi