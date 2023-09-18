// for checking the time of execution (works on linux)
//  time gcc -o thread1.c thread1


#include <pthread.h>
#include <stdio.h>

void *compute() {
    printf("Compute sample code !!");
    return NULL;
}

int main() {

    pthread_t thread1;
    // address of thread, 
    // attribute for inter process communication, 
    // function for thread, 
    // parameters for that function
    pthread_create(&thread1, NULL, compute, NULL);
    pthread_join(thread1, NULL);
    return 0;
}
