#!/bin/bash

if [ $# -eq 3 ]; then
    # Arithmetic operation with command-line arguments
    case "$2" in 
        "+") result=$(( $1 + $3 ));;
        "-") result=$(( $1 - $3 ));;
        "*") result=$(( $1 * $3 ));;
        "/") if [ $3 -ne 0 ]; then 
                result=$(( $1 / $3 ))
            else
                echo "cannot divide by 0"
                exit 1
            fi;;
        *) echo "Invalid operator"; exit 1;;
    esac
    echo "$* = $result"
elif [ "$1" == "start" ]; then
    # Continuous calculator prompt
    echo -e "Starting calc ... Enter \"exit\" to exit"
    while true; do
        echo "Enter the expression: "
        read expression
        if [ "$expression" == "exit" ]; then
            break
        fi
        if [[ "$expression" =~ ([0-9]+)[[:space:]]*([-+*/])[[:space:]]*([0-9]+) ]]; then
            a="${BASH_REMATCH[1]}"
            op="${BASH_REMATCH[2]}"
            b="${BASH_REMATCH[3]}"
            case "$op" in 
                "+") result=$(( a + b ));;
                "-") result=$(( a - b ));;
                "*") result=$(( a * b ));;
                "/") if [ "$b" -ne 0 ]; then 
                        result=$(( a / b ))
                    else
                        echo "cannot divide by 0"
                        continue
                    fi;;
                *) echo "Invalid operator"; continue;;
            esac
            echo "$expression = $result"
        else
            echo "Invalid expression format"
        fi
    done
else
    echo "Invalid usage, enter a simple expression separated by whitespaces or \"start\" to open in endless mode"
fi

