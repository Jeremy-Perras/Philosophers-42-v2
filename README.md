# Philosophers-42

## Table of content :
* [What is Philosophers ?](#what-is-Philosophers-)
* [What is in it ?](#what-is-it-)
* [How does is work ?](#how-does-is-work-)

### What is Philosophers ?
 Philosophers is a individual project at 42. The purpose is to learn more about thread, mutex.
 
### What is it ?
<a href="https://zupimages.net/viewer.php?id=22/13/dyc0.png"><img src="https://zupimages.net/up/22/13/dyc0.png" alt="" /></a>

Each philosopher eat spaghetti but they need two forks for eat them. Each philosophers start with one fork, and need too eat before time to die is ended. If they eat the time to die is restart until next meal. They do routine : 

**eat or wait for fork -> sleep -> think -> eat or wait for fork.**

#### How I code this ?
  Each philosopher is a thread, they do routine until one is dead and each fork is a mutex. I check death in main program and we loop until someone is dead or they do the number of times each philosophers eat.

### How does is work ?
The Makefile contain 4 rules : all clean fclean and re.
Create a program called philo. 
**$> ./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]**
