// for checking the time of execution (works on linux)
//  time gcc -o thread2.c thread2

#include <pthread.h>
#include <stdio.h>

void *compute(void *add) {
    // deferencing the add variable
    long *add_num = (long *) (add);

    printf("ADD is : %d\n", *add_num);
    return NULL;
}

int main() {
    pthread_t thread1; 
    pthread_t thread2;

    long value1 = 1;
    long value2 = 5;
    // passing the parameter to the compute function
    pthread_create(&thread1, NULL, compute, (void *) &value1);
    pthread_create(&thread2, NULL, compute, (void *) &value2);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    return 0;
}
