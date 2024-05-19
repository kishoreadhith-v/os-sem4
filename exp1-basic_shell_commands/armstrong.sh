#!/bin/bash

# Function to calculate the power of a number
power() {
    local base=$1
    local exponent=$2
    local result=1

    for ((i=1; i<=$exponent; i++)); do
        result=$((result * base))
    done

    echo "$result"
}

# Function to check if a number is an Armstrong number
is_armstrong() {
    local num=$1
    local len=${#num}
    local sum=0

    for ((i=0; i<$len; i++)); do
        digit=${num:i:1}
        sum=$((sum + $(power $digit $len)))
    done

    if [ $sum -eq $num ]; then
        echo "$num is an Armstrong number."
    else
        echo "$num is not an Armstrong number."
    fi
}

# Check if a number is provided as argument
if [ $# -ne 1 ]; then
    echo "Usage: $0 <number>"
    exit 1
fi

# Call the function to check if the number is an Armstrong number
is_armstrong $1

