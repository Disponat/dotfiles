#!/bin/bash

SONG_PATH="$1"

IMG="${HOME}/.moc/moc_cover.png"

rm -f "${IMG}"

ffmpeg -loglevel quiet -i "${SONG_PATH}" -an -vcodec copy -y "${IMG}"

FILENAME=$(basename -- "$SONG_PATH")
FILENAME="${FILENAME%.*}"

dunstify -i "${IMG}" " PLAYING " "$FILENAME"


