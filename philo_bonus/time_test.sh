# Test script
#!/bin/bash

for i in {1..10}; do
    echo "Test $i:"
    ./philo_bonus 2 310 200 200 > output.txt
    grep "died" output.txt | cut -d' ' -f1
done
