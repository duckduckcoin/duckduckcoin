#!/bin/bash
# create multiresolution windows icon
ICON_SRC=../../src/qt/res/icons/duckduckcoin.png
ICON_DST=../../src/qt/res/icons/duckduckcoin.ico
convert ${ICON_SRC} -resize 16x16 duckduckcoin-16.png
convert ${ICON_SRC} -resize 32x32 duckduckcoin-32.png
convert ${ICON_SRC} -resize 48x48 duckduckcoin-48.png
convert duckduckcoin-16.png duckduckcoin-32.png duckduckcoin-48.png ${ICON_DST}

