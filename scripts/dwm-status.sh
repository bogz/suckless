#!/usr/bin/env bash
# Status script for dwm

# The MIT License (MIT) http://opensource.org/licenses/MIT

# colours: 01:normal 02:white 03:red 04:green 05:yellow 06:blue
# 07:cyan 08:magenta 09:grey

sp="$(echo -ne " ")"

music(){
  track="$(mpc current)"
  artist="${track%%- *}"
  title="${track#*- }"
  [[ -n $artist ]] && printf "%b" "•  $artist - $title "
}

vol(){
	vol="$(pactl list sinks | grep 'Volume' |awk 'FNR == 1 {print $5}')"
	printf "%b" " $vol "
}

bat(){
  onl="$(</sys/class/power_supply/AC/online)"
  bat0="$(</sys/class/power_supply/BAT0/capacity)"
  bat1="$(</sys/class/power_supply/BAT1/capacity)"
  if [[ $onl -eq 0 && $bat0 -ge 15 ]] || [[ $onl -eq 0 && $bat1 -ge 15 ]]; then
    printf " $bat0 $bat1"
  elif [[ $onl -eq 0 && $bat0 -le 14 ]] || [[ $onl -eq 0 && $bat1 -le 14 ]]; then
    printf " $bat0 $bat1"
  else
    printf " $bat0 $bat1"
  fi
}

mem(){
  mem="$(awk '/^Mem/ {print $3}' <(free -m))"
  printf " $mem"
}

cpu(){
  read cpu a b c previdle rest < /proc/stat
  prevtotal=$((a+b+c+previdle))
  sleep 0.5
  read cpu a b c idle rest < /proc/stat
  total=$((a+b+c+idle))
  cpu="$((100*( (total-prevtotal) - (idle-previdle) ) / (total-prevtotal) ))"
  printf " $cpu"
}

hdd(){
    hd=( $(awk '
        {i=$5} /boot/ {a=i}; /root/ {b=i}; /home/ {c=i}; /media/&&!/sr0/ {d=i}
            END {print (NR>=11) ? a" "b" "c" "d : a" "b" "c}
        ' <(df -P)) )
    drives="${#hd[@]}"
    if (( drives > 3 )); then
        printf "%b " "${hd[@]:0:3} ${hd[@]:3:1}"
    else
        printf "%b " "${hd[@]}"
    fi
}

dte(){
    dte="$(date "+%H:%M")"
    printf "%b" " $dte"
}

kb(){
	keys="$(xkblayout-state print "%s")"
	printf "%b" " $keys"
}

temp(){
	tmp="$(awk '/^Package/ {print +$4}' <(sensors))"
	mb="${tmp#* }"
	if (( mb < 70 )); then
		printf "%b" " $mb°"
	else
		printf "%b" " $mb°"
	fi
}

# Pipe to status bar
xsetroot -name "$(music)  $(bat)  $(temp)  $(cpu)  $(mem)  $(vol)  $(kb)  $(dte) "
