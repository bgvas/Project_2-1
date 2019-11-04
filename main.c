#include <stdio.h>
#include <stdlib.h>
#include <time.h>


struct process{

};

struct Q1{
    int front;
    int rear;
    int arr[]
};

struct Q2{
    int front;
    int rear;
    int arr[]
};

int chance10();


int main() {

    int main_counter = 0;
    srand(time(NULL));

    while(main_counter != 10){



        main_counter++;
    }



}

// Procedure for 10%
int chance10(){

    srand(time(NULL));
    float chance = 10.f;

    float n = rand() % 2;
    n = (float) n * 100;

    if(n<chance){
        printf("10%%\n");
    }

}