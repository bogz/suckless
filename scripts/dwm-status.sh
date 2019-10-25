#!/usr/bin/env bash
# Status script for dwm

# The MIT License (MIT) http://opensource.org/licenses/MIT

music(){
  track="$(mpc current)"
  artist="${track%%- *}"
  title="${track#*- }"
  [[ -n $artist ]] && printf "%b" "•  $artist - $title "
}

vol(){
	vol="$(pactl list sinks | grep '^[[:space:]]Volume:' | head -n $(( $SINK + 1 )) | tail -n 1 | sed -e 's,.* \([0-9][0-9]*\)%.*,\1,')"
	if (( $vol == 0 )); then
		printf "%b" " $vol%"
	elif (( $vol >= 1 && $vol <= 15 )); then
		printf "%b" " $vol%"
	elif (( $vol > 15  && $vol <= 65)); then
		printf " $vol%"
	else
		printf "%b" " $vol%"
	fi
}

bat(){
  onl="$(</sys/class/power_supply/AC/online)"
  bat0="$(</sys/class/power_supply/BAT0/capacity)"
  bat1="$(</sys/class/power_supply/BAT1/capacity)"
  if [[ $onl -eq 0 && $bat0 -ge 15 ]] || [[ $onl -eq 0 && $bat1 -ge 15 ]]; then
    printf " $bat0 $bat1"
  elif [[ $onl -eq 0 && $bat0 -le 14 ]] || [[ $onl -eq 0 && $bat1 -le 14 ]]; then
    printf " $bat0 $bat1"
  else
    printf " $bat0 $bat1"
  fi
}

mem(){
  mem="$(awk '/^Mem/ {print $3}' <(free -m))"
  printf " $mem"
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
        {i=$5} /root/ {a=i}; /home/ {b=i}; /media/&&!/sr0/ {c=i}
            END {print (NR>=11) ? a" "b" "c" "d : a" "b" "c}
        ' <(df -P)) )
    drives="${#hd[@]}"
    if (( drives > 3 )); then
        printf "%b " " ${hd[@]:0:3} ${hd[@]:3:1}"
    else
        printf "%b " " ${hd[@]}"
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

int(){
	con="$(nmcli | grep -v p2p-dev-wlp3s0 | grep disconnected | cut -c 9-)"
	if (( $con == "disconnected" )); then
		printf "%b" " n/a"
	else
		printf "%b" " on"
	fi
}

# Pipe to status bar
xsetroot -name "$(music) • $(bat) • $(temp) • $(cpu)% • $(mem) • $(hdd)• $(vol) • $(kb) • $(dte) • $(int)"
