#!/bin/bash
#enter input encoding here
FROM_ENCODING="UTF-8"
#output encoding(UTF-8)
TO_ENCODING="CP1251"
#convert
CONVERT="iconv -f $FROM_ENCODING -t $TO_ENCODING"
#loop to convert multiple files
for file in *.txt; do
$CONVERT "$file" -o "${file%.txt}.txt"
done
exit 0