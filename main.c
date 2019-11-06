/* Project 2
*               Vasileios Georgoulas AM:2118147
*  Author's:    &
*               Ioannis Skoumpas     AM: 2118063
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>


struct process{
	int id;
	int size;
	int strtime;
	char condition [10];
	int runtime;
	struct process *next;
};

struct Q1{
    int front;
    int rear;
    int size;
};

struct Q2{
    int front;
    int rear;
    int size;
};



int main() {

    int main_counter = 0;
    

    while(main_counter != 10){


        main_counter++;
        printf("asdf");
    }
}

// Procedure for 10%
int chance10(){

    srand(time(NULL));
    int randomq = rand() % 10 + 1;
    if(randomq < 2){	// select Queue 1 for 10%
        return 1;
    }else{
        return 0;
    }

}

// Procedure for random numbers
int randomNumber(){
	srand(time(NULL));	//Connect random engine with time,
	int randomnumber;		            //to generate real random numbers
	randomnumber = rand()%10 + 1;	    // generate random numbers (1-10)
	return randomnumber;
}

// Procedure for Queue random selection
int randomQueue(){
	srand(time(NULL));
	int randomq = rand() % 10 + 1;
	if(randomq < 4){	// select Queue 1 for 30%
		return 1;
	}
	else if(randomq > 4 && randomq < 6 ){ // select Queue 2 for 20%
		return 2;
	}
	else{			// select no Queue for remain 50%
		return 0;
	}

}
