
# Philosophers

## 📜 Description
"Philosophers" is a classic synchronization problem from 42 School. The challenge involves simulating a scenario where philosophers alternately think, eat, and sleep without running into issues like deadlock or starvation. This project introduces key concepts of multithreading, process synchronization, and resource sharing.

#### ⭐ My 42 score for this project:
![image](https://github.com/user-attachments/assets/c5736868-82ff-4960-aaa1-5406752df518)

#### 📄 Official 42 School Subject:
[Philosophers Subject](https://github.com/yvann-ba/Philosophers/blob/main/en.subject.pdf)

## 🌟 Features
- Simulation of the dining philosophers problem
- Multi-threaded solution with proper synchronization
- Management of shared resources (forks)
- Prevention of deadlock and starvation

## ⚙️ Installation

To clone and compile this project, follow these steps:

```bash
git clone https://github.com/yvann-ba/Philosophers.git
cd Philosophers
make
```

## 🚀 Usage
To simulate the philosophers' dining problem, run the following command:

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

Example:

```bash
./philo 5 800 200 200
```

This will launch a simulation with 5 philosophers where each philosopher must:
- Avoid starving within 800ms
- Take 200ms to eat
- Take 200ms to sleep

You can also specify an optional number of times each philosopher must eat before the simulation stops.
