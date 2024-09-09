# Philosophers

## Objective
Implement a simulation of the Dining Philosophers problem with threading and synchronization.

## Description
Setup: Multiple philosophers (threads) sit at a round table with a bowl of spaghetti. Each philosopher has a fork on their left and right, and there are as many forks as there are philosophers.

Behavior: Philosophers alternate between eating, thinking, and sleeping. To eat, a philosopher must hold both forks (left and right). After eating, they put down the forks and then sleep before resuming thinking.

Termination: The simulation stops when a philosopher dies of starvation (fails to eat within time_to_die milliseconds). Alternatively, if provided, the simulation will also stop when all philosophers have eaten at least number_of_times_each_philosopher_must_eat times.

## Arguments
1. number_of_philosophers: Number of philosophers and forks.
2. time_to_die: Maximum time in milliseconds a philosopher can go without eating before starving.
3. time_to_eat: Time in milliseconds a philosopher spends eating.
4. time_to_sleep: Time in milliseconds a philosopher spends sleeping.
5. number_of_times_each_philosopher_must_eat (optional): Minimum times each philosopher must eat before the simulation ends.

## Logging
Format log messages with a timestamp in milliseconds.
Log states: "X has taken a fork," "X is eating," "X is sleeping," "X is thinking," and "X died."
Ensure death messages are displayed within 10 ms of the event.

## Requirements
Use threads for each philosopher.
Protect fork states with a mutex to prevent duplication.


## Constraints
No global variables allowed.

