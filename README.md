# philosophers

The “Philosophers” project simulates the classic Dining Philosophers Problem using threads. The goal is to handle concurrent access to shared resource properly, avoiding deadlocks and race conditions, using mutexes.

## Features:

All philosophers will have the same time-to-die, time-to-eat, time-to-sleep and optionally number-of-meals they need to eat.
- Each philosopher needs 2 forks to eat, so he needs to share forks with adjacent philosopher. 2 philosophers can not pick up the same fork at the same time.
- Each philosopher needs to eat, sleep and think alternatively. He will take time-to-eat and time-to-sleep, no limit on time to think.
- If a philosopher doesn't eat within time-to-die, he will die.
- If number of meals is input, the program will end when all philosophers have eaten at least number-of-meals.
  
All the actions taken by all philosophers need to be printed to standard output with a time stamp. 

## How To Run:

### Requirements:
Linux OS

### Installment:
#### 1. Clone the Repository

```bash
git clone https://github.com/TrangPham93/philosophers.git philo
cd philo
```

#### 2. Compile the Project

```bash
make
```

#### 3. Run the project

```bash
./philo [number of philos] [time-to-die] [time-to-eat] [time-to-sleep] [number-of-meals-must-eat<optional>]
```

#### 4. Examples

<img width="583" height="375" alt="image" src="https://github.com/user-attachments/assets/11990c20-e405-4262-8b25-89a98a792f7d" />


