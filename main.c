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

struct queue{
    struct process *front;
    struct process *rear;
    int size;
}*q1, *q2;


void deQueue(struct queue *queue);
int queueSize(struct queue *queue);
void Init(struct queue * queue);
int chance10();
int randomNumber();
int randomQueue();
int isEmpty(struct queue *queue);

int main() {

    int main_counter = 0;


    while(main_counter != 10){


        main_counter++;
    }
}

// Initialize the Queue
void Init(struct queue * queue){
    queue->front = NULL;
    queue->rear = NULL;
    queue->size = 0;
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

// Check if queue is empty
int isEmpty(struct queue *queue){
	return (queue->front == queue->rear);
}

// Delete an item from the Queue
void deQueue(struct queue *queue){
	if(queue->size == 0){		// if queue is empty return.
		return;
	}
	else{
		queue->size--;			// decrease size of queue
		struct process *temp;	// create a temporary pointer
		temp = queue->front;	// set the address of the element for delete equal to temp
		queue->front = temp->next; // set the front pointer of the queue equal to second element
		free(temp);
	}
}

// Get the size of a queue
int queueSize(struct queue *queue){
	return queue->size;
}

// add a new node in the queue
void enqueue(struct queue *queue){
	struct process *new;
	new = (struct process *)malloc(sizeof(struct process));
	struct process *temp;
	new->id = 0 ;
	new->size = randomNumber();
	new->strtime = 0;
	new->condition = "anamoni";
	new->runtime = -1;
	new->next = NULL;

	if(isEmpty(queue)){
		queue->front = new;
	}
	else{
		temp = queue->rear;
		temp->next = new;
	}
	queue->rear = new;
	queue->size++;
}








