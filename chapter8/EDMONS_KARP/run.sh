#!/bin/bash

DEBUG=TRUE
CMDNAME=`basename $0`
CMDPATH=`dirname $0`/
USAGE="usage: $CMDNAME [-v] file"

while :
do
    case $1 in
	-v) DEBUG=FALSE
	    shift
	    ;;
	-*) echo "$USAGE" 1>&2
	   exit 1
	   ;;
	*) break
	   ;;
    esac
done

if [ ! -e edmons_karp/target/release/edmons_karp ]; then
    cd edmons_karp
    cargo build --release
    cd ../
fi

if [ "$1" = "" ]; then
    echo "$USAGE" 1>&2
    exit 1
fi

if [ ! "$2" = "" ]; then
    echo "$USAGE" 1>&2
    exit 1
fi

if [ "$DEBUG" = TRUE ]; then
    edmons_karp/target/release/edmons_karp "$1"
else 
    edmons_karp/target/release/edmons_karp -v "$1"
fi

if [ -e output.txt ]; then
    cat output.txt
fi
