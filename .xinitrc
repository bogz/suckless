#!/bin/zsh

export DE=dwm

# Dbus fix
if [ -z "$DBUS_SESSION_BUS_ADDRESS" ]; then
    eval "$(dbus-launch --sh-syntax --exit-with-session)"
fi
#############
# WM related#
#############

# Load .Xresources
xrdb -merge $HOME/.Xresources

# Enable restart X
setxkbmap -option terminate:ctrl_alt_bksp

# Disable CapsLock & map to Escape
#setxkbmap -option caps:swapescape

# Set additional keybinds
xbindkeys

# Set wmname
wmname compiz

# Set the screen brightness
xbacklight -set 45% &

# Set wallpaper in different ways
#imlibsetroot -s $XDG_CONFIG_HOME/background.jpg &
sleep 10 && nitrogen --restore &

# Set cursor
xsetroot -cursor_name left_ptr &

# Hide cursor
unclutter -noevents -idle 3 &


# Start terminal emulation daemon
urxvtd -q -o -f

# Auto{u}mount drives
udiskie -qN &

# Shadowing with compton
compton --config ~/.config/compton -b

# Shut off system bell
/usr/bin/xset b off

# Start the daemons
mpd &
#xscreensaver &
gnome-keyring-daemon --start &
thunar --daemon &
parcellite &
nm-applet --sm-disable &
xfce4-power-manager &
skype &
conky &

#exec $1

# Start dwm with xinitrc
exec /opt/dwmstart

# Start awesome with xinitrc
#exec awesome > ~/awesome_startup.log 2>&1

