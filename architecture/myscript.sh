while read line
do
    echo $line | ./a.out
done < "input.txt"