#!/bin/bash
# usage: ./bomb_download.sh
#        ./bomb_download.sh <username>
#
# Downloads a binary bomb via the command line from the bomb server.

server=bomblab.cselabs.umn.edu:15213

username=$1
if [[ "$username" = "" ]]; then
    username=$USER
fi

echo Fetching bomb for user "$username"
curl --get -O -J --no-progress-meter \
     -d username=$username -d submit=Submit \
     $server
