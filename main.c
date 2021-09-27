#include "philo.h"

void*   routine() {
    printf("test from threads\n");
    sleep(2);
    printf("ending thread\n");
}

int     main(int argc, char **argv)
{
    // test(26);
    /*start creating threads
    we first have to define a sort of place where basically the API can store some information about the thread and
     this place is a varibale of type pthread_t;
    to initialize a thread we just call the pthread_create() function; the first parametre is a pointer to the 
    variable we have created, second is the attribute
    you can pass NULL, third is the actual func that is going to execute when it creats the thread, and lastly is 
    the argument that going to be passed to the func.*
    pthread_t   t1, t2;
    if (pthread_create(&t1, NULL, &routine, NULL) != 0)
        return 1;
    if (pthread_create(&t2, NULL, &routine, NULL) != 0)
        return 2;
    we have to wait for that threads to finish its execution:
    call the function pthread_join() we pass the actual variable, and the we can pass in some poin
    ter that gets the result from that thread
    if (pthread_join(t1, NULL) != 0)
        return 3;
    if (pthread_join(t2, NULL) != 0)
        return 4;
    the difference between threads and procecesses:
    processes can contain multiple threads th inverse is incorrect.
    regarding the adresse space , when working with processes when forking we are duplicating all th variables
    into a child processes so we get 2 different
    variabels one on eache process and we can modify them individually, but with threads there's a big difference
    where we have all the variables in the same place
    , all threads can acces all variables and they all have a common adresse  space.
    >>What happens when you forget to unlock a pthread_mutex?:
    -In your code, you launch 10 threads with the same function. The first time one of your threads calls
    pthread_mutex_lock, it acquires the mutex. This means all other
    threads calling pthread_mutex_lock will simply block and wait for the first thread to release the mutex
    by calling pthread_mutex_unlock.
    Since you commented out pthread_mutex_unlock, it is never called and therefore, the mutex is never released.
    Since you wait for the other threads in the main function and they never return because they block infinitely,
    your main function never returns as well.
    Mutexes work like toilets. Once you go inside and lock the door, everyone else has to wait until you unlock
    the door and come out.
    If you never do that, everyone else (in theory) will have to wait infinitely. */
    // while (1);

    struct timeval	time;
	unsigned int	i;

	gettimeofday(&time, NULL);
    printf("%lu\n", time.tv_sec * 1000);
	// i = (unsigned int)time.tv_sec;
    if (required_meals != 1)
    {
        pthread_mutex_lock();
        while (philo){
            if (philo->eaten_meals < required_meals)
            {
                
            }
            philo = philo->next;
        }
    }

    return (0);
}