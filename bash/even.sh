#!/bin/bash

nums=(23 56 86 44 237 89 76 98 103)

for n in "${nums[@]}"; do
	if [[ ${n} -eq 237 ]]; then
		break
	fi

	if [[ $((n % 2)) -eq 0 ]]; then
		echo "${n}"
	fi
done
