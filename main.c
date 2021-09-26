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
       regarding the adresse space , when working with processes when forking we are duplicating all th variables into a child processes so we get 2 different
       variabels one on eache process and we can modify them individually, but with threads there's a big difference where we have all the variables in the same place
       , all threads can acces all variables and they all have a common adresse  space. */
    while (1);
    return (0);
}