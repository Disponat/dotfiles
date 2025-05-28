#!/bin/bash

# mocp -i format:
# State: STOP
# File: /home/myfile.mp3

MOC_INFO=$(mocp -i)

IMG="${HOME}/.moc/moc_cover.png"
MOC_STATE=$(echo "$MOC_INFO" | awk -F': ' '/^State:/ {print $2}')

SONG_PATH=$(echo "$MOC_INFO" | awk -F': ' '/^File:/ {print $2}')
FILENAME=$(basename -- "$SONG_PATH")
FILENAME="${FILENAME%.*}"


if [[ "$MOC_STATE" == "PLAY" ]]; then
  $(mocp -G)
  dunstify -i "${IMG}" " PAUSED " "$FILENAME" -t 2000
fi

if [[ "$MOC_STATE" == "PAUSE" ]]; then
  $(mocp -G)
  dunstify -i "${IMG}" "  PLAYING " "$FILENAME" -t 2000
fi


