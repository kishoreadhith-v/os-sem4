#!/bin/bash

a=(1 2 3 4 5)
b=(2 3 5 7 11)
c=(2 4 6 9 5)

common=()

for elem in "${a[@]}"; do
    if [[ " ${b[@]} " =~ " ${elem} " ]] && [[ " ${c[@]} " =~ " ${elem} " ]]; then
        common+=($elem)
    fi
done

echo "Common elements: ${common[@]}"
