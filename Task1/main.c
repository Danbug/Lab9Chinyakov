//https://www.geeksforgeeks.org/multithreading-c-2/

/*
    Задание №1 (Состояние гонки)
    Напишите программу, которая показывает возможность повреждения данных 
    (переменная длинного целого типа с нулевым начальным значением) 
    несколькими одновременно работающими потоками 
    (демонстрирует поведение, описывающееся понятием race conditions). 
    Программа запускает некоторое количество пар потоков-­потомков. 
    Поток из одной части этой пары заданное количество раз увеличивает значение переменной на 1 ,
    поток из другой части пары такое же количество раз уменьшает значение переменной на 1.
    Основной поток ожидает завершения работы всех потоков — потомков и выводит финальное значение
    изменяемой переменной. Количество потоков и количество операций, которые выполняет каждый поток,
    передаются в программу с помощью коротких опций. Если какая­то опция не задана, то предусмотреть для
    нее значение по умолчанию. Программа, должна заданное количество раз выполнить эти 
    действия и каждый раз вывести то финальное значение переменной, какое получится 
    в результате каждого запуска.Проанализируйте поведение программы в зависимости от значения параметров.

*/


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
 
// Let us create a global variable to change it in threads
int g = 0;
int numOfIterations = 9;

void *myThreadPlus(void *vargp)
{
    // Store the value argument passed to this thread
    int *myid = (int *)vargp;
 
    // Let us create a static variable to observe its changes
    //static int s = 0;
 
    // Change static and global variables
    //s++;
    for(int i = 0 ; i < numOfIterations ; i++){
        int read = g;
        read++;
        sleep(1);
        g = read;
    }
 
    // Print the argument, static and global variables
    //printf("Thread ID: %d, Static: %d, Global: %d\n", *myid, ++s, ++g);
}

// The function to be executed by all threads
void *myThreadMinus(void *vargp)
{
    // Store the value argument passed to this thread
    int *myid = (int *)vargp;
 
    // Let us create a static variable to observe its changes
    //static int s = 0;
 
    // Change static and global variables
    //s++; 
    for(int i = 0 ; i < numOfIterations ; i++){
        int read = g;
        read--;
        sleep(1);
        g = read;
    }
 
    // Print the argument, static and global variables
    //printf("Thread ID: %d, Static: %d, Global: %d\n", *myid, ++s, ++g);
}

// gcc -o main main.c -lpthread
int main(int argc, char const *argv[])
{
    int numOfThreads = 3;
    pthread_t tid1;
    pthread_t tid2;
 
    // Let us create three threads
    for (int i = 0; i < numOfThreads; i++){
        pthread_create(&tid1, NULL, myThreadPlus, NULL);
        pthread_create(&tid2, NULL, myThreadMinus, NULL);
        pthread_join(tid1,NULL);
        pthread_join(tid2,NULL);
    }
    printf("Variable = %d\n",g);

    //pthread_exit(NULL);
    return 0;
}
