#!/usr/bin/bash

if [ "$#" -ne 1 ]; then
    echo "./script [filename]"
else
    OUTPUT=`diff <(./prog $1) <(radon cc -s $1)`
    if [ ${#OUTPUT} -gt 0 ]; then
        echo "${OUTPUT}"
    else
        echo "SUCCESS!"
    fi
fi

