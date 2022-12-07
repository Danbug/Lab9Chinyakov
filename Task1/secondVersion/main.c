//https://www.geeksforgeeks.org/multithreading-c-2/

/*
    Задание №1 ( Состояние гонки )
    Напишите программу, которая показывает возможность повреждения данных 
    (переменная длинного целого типа с нулевым начальным значением) 
    несколькими одновременно работающими потоками 
    (демонстрирует поведение, описывающееся понятием race conditions). 
    Программа запускает некоторое количество пар потоков-­потомков. 
    Поток из одной части этой пары заданное количество раз увеличивает значение переменной на 1 ,
    поток из другой части пары такое же количество раз уменьшает значение переменной на 1 .
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
long long g = 0;
int numOfIterations = 1000000;

void *myThreadPlus(void *vargp)
{
    printf("Thread [%d] PLUS Start \n",*(int *) vargp);

    for (int i = 0 ; i < numOfIterations ; i++){
        g++;
    }

    printf("Thread [%d] PLUS END \n",*(int *) vargp);
}

// The function to be executed by all threads
void *myThreadMinus(void *vargp)
{
    printf("Thread [%d] MINUS Start \n",*(int *) vargp);

    for (int i = 0 ; i < numOfIterations ; i++){
        g--;
    }

    printf("Thread [%d] MINUS END \n",*(int *) vargp);
}

// gcc -o main main.c -lpthread
int main(int argc, char const *argv[])
{
    int numOfThreads = 5;
    pthread_t thid[numOfThreads];
 
    // Let us create three threads
    for (int i = 0; i < numOfThreads; i++){
        pthread_create(&thid[i], NULL, myThreadPlus, (void *) &i);
        pthread_create(&thid[i], NULL, myThreadMinus, (void *) &i);
    }

    for (int i = 0; i < numOfThreads; i++){
        pthread_join(thid[i],NULL);
        pthread_join(thid[i],NULL);
    }
    printf("Variable = %lld\n",g);

    //pthread_exit(NULL);
    return 0;
}
