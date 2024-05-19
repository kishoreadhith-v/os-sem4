#!/bin/bash

n1=$1
n2=$3
op=$2

if [[ "$op" = "plus" ]]; then
	echo "$n1 + $n2 = $((n1 + n2))"
elif [[ "$op" = "minus" ]]; then
        echo "$n1 - $n2 = $((n1 - n2))"
elif [[ "$op" = "times" ]]; then
        echo "$n1 * $n2 = $((n1 * n2))"
fi

