#!/usr/bin/bash

declare -A functions
declare -A instructions
regex_func="(^[0-9a-f]+) <(.*)>"
regex_instr="[[:space:]]*[0-9a-f]+:[[:space:]]+([0-9a-z]+ )+[[:space:]]+([0-9a-z]+)"

echo 'Hi, this is the output of the analysis:'
while read line
do
    if  [[ $line =~ $regex_func ]]; then
        functions[${BASH_REMATCH[1]}]=${BASH_REMATCH[2]}
    elif [[ $line =~ $regex_instr ]]; then
        instructions[${BASH_REMATCH[2]}]+=1
    fi

done < "$1"

echo -e "    You have ${#instructions[@]} kinds of instructions in this object file:"
for i in "${!instructions[@]}"
do
    printf "\t%-15s: %10s\n" "$i" "Executed ${#instructions[$i]} times"
done

echo -e "    You have ${#functions[@]} functions:"
for i in "${!functions[@]}"
do
    printf "\t%-23s: %10s\n" "${functions[$i]}"  "Located at $i addr"
done
