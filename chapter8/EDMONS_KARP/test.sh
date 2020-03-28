#!/bin/bash

CMDNAME=`basename $0`
CMDPATH=`dirname $0`/
USAGE="usage: $CMDNAME"

if [ ! "$1" = "" ]; then
    echo "$USAGE" 1>&2
    exit 1
fi

if [ ! -e edmons_karp/target/release/edmons_karp ]; then
    cd edmons_karp
    cargo build --release
    cd ../
fi

for i in {1..40}
do
    edmons_karp/target/release/edmons_karp -v \
	../test_instances/inputs/input"$i".txt
    diff=`diff output.txt ../test_instances/outputs/output"$i".txt`
    if [ "$diff" = "" ]; then
	echo ""$i": AC"
    else
	echo ""$i": WA"
	echo $diff
    fi
done

if [ -e output.txt ]; then
    rm output.txt
fi

