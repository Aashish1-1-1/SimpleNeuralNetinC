#!bin/sh
set -xe
gcc -Wall -Wextra -o  exec $1 && ./exec
