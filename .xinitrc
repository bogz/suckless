#!/bin/zsh

export BROWSER=firefox-browser
export DE=gnome

if [ -d /etc/X11/xinit/xinitrc.d ]; then
    for f in /etc/X11/xinit/xinitrc.d/*; do
        [ -x "$f" ] && . "$f"
    done
    unset f
 fi

#############
# WM related#
#############

# set dpi
xrandr --dpi 138

# Load .Xresources
xrdb -merge $HOME/.Xresources

# Enable restart X
setxkbmap -option terminate:ctrl_alt_bksp

# Set additional keybinds
xbindkeys

# Set wmname
wmname compiz

# Set the screen brightness
xbacklight -set 55% &

# Set wallpaper
sleep 10 && nitrogen --restore &

# Set cursor
xsetroot -cursor_name left_ptr &

# Hide cursor
unclutter -noevents -idle 3 &

# Start terminal emulation daemon
urxvtd -q -o -f

# Notify daemon
twmnd &

# Auto{u}mount drives
udiskie -qN &

# Shadowing with compton
compton --config ~/.config/compton -b

# Shut off system bell
/usr/bin/xset b off

# clipboard synching
autocutsel -fork &
autocutsel -selection PRIMARY -fork &

# Sleep after 5 minutes of inactivity
xautolock -time 5 -locker /usr/local/bin/slock -corners 0+0- -cornerdelay 1 -cornerredelay 5 -cornersize 10 -secure &

#Keyboard layout
setxkbmap -option 'grp:alt_shift_toggle' -layout us,ro -variant ,std

# Daemons
gnome-keyring-daemon --start &
thunar --daemon &
nm-applet --sm-disable &
skypeforlinux &

# Start dwm with xinitrc
exec $HOME/src/dwmstart

