#!/bin/bash

size=$1
number_matrix=$2
output="matrix_reload.dat"

if [ -f "$output" ]
then
    rm $output
fi

echo "nro matrices: $number_matrix"

for i in `seq $number_matrix`
do
    line=""
    rows=$size
    cols=$size

	total=$(($cols * $rows))

    line="${rows}"

    for c in `seq $total`
    do
		number=$(( ( RANDOM % 200 )))
        decimals=$((RANDOM % 99))
		line="$line $number.$decimals "
    done

line="${line}"
echo $line >> $output


#Para que si el primero es de la forma AxB el segundo sea BxC
    line=""
    rows="$cols"
    cols="$cols"

    total=$(($cols * $rows))

    line="${rows}"

    for c in `seq $total`
    do
        number=$(( ( RANDOM % 200 )))
        decimals=$((RANDOM % 99))
        line="$line $number.$decimals "
    done

    line="${line}"
    echo $line >> $output


done
