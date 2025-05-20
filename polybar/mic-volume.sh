#!/bin/bash

color_unmuted="#9ABEB7"
color_muted="#E54242"

print_volume() {
  local is_muted=$(pactl get-source-mute @DEFAULT_SOURCE@ | grep -Eo 'yes|no')
  if [[ "$is_muted" == "yes" ]]; then echo "%{F${color_muted}} %{F-}"; return; fi
  local raw_str=$(pactl get-source-volume @DEFAULT_SOURCE@)
  local volume_str=$(echo $raw_str | grep -o '[0-9]\+%'| head -n1)
  echo "%{F${color_unmuted}}%{F-} "$volume_str
}

# Initial print
print_volume

# Subscribe to pulse audio events and filter for source changes
pactl subscribe | while read -r line; do
    if echo "$line" | grep -q "source"; then
      print_volume
    fi
done
