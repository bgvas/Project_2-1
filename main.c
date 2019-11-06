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

// Function for random numbers
int randomNumber(){
	srand(time(NULL));	//Connect random engine with time,
	int randomnumber;		            //to generate real random numbers
	randomnumber = rand()%10 + 1;	    // generate random numbers (1-10)
	return randomnumber;
}

// Function for Queue random selection
int randomQueue(){
	srand(time(NULL));
	int randomq = rand() % 10 + 1;
	if(randomq < 4){	// select Queue 1 for 30%
		return 1;
	}
	else if(randomq > 3 && randomq < 6 ){ // select Queue 2 for 20%
		return 2;
	}
	else{			// select no Queue for remain 50%
		return 0;
	}

}

// Delete an item from the Queue
void deQueue(struct Q1 *queue, struct process *pro){
	if(queue->size == 0){		// if queue is empty return.
		return;
	}
	else{
		queue->size--;			// decrease size of queue
		struct process *temp;	// create a temporary pointer
		temp = pro;				// set the address of the element for delete equal to temp
		temp->next = pro->next;
		queue->front = pro->next; // set the front pointer of the queue equal the second element
		free(temp); 			// delete
	}
}
