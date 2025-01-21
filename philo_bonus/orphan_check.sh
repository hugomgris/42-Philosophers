#!/bin/bash

# Run the program
#./philo_bonus 5 800 200 200 
./philo_bonus 5 800 200 200 7
#./philo_bonus 4 410 200 200
#./philo_bonus 4 310 200 100
#./philo_bonus 2 310 200 100

# Check for any remaining processes
remaining=$(pgrep philo_bonus | wc -l)

if [ $remaining -gt 0 ]; then
    echo "Warning: Found $remaining orphan processes"
    pgrep philo_bonus
else
    echo "No orphan processes found"
fi