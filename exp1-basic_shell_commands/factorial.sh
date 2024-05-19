#!/bin/bash

# Initialize result to 1
res=1
i=1

# Loop from 1 to the given number
while [ $i -le $1 ]; do
    # Multiply result by the current value of i
    res=$((res * i))
    # Increment i
    i=$((i + 1))
done

# Output the factorial
echo "Factorial of $1 is $res"

