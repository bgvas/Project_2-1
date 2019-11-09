/* Project 2
*               Vasileios Georgoulas AM:2118147
*  Author's:    &
*               Ioannis Skoumpas     AM: 2118063
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int idcount = 1;
int main_counter = 1;

struct process{
	int id;
	int size;
	int strtime;
	char *condition;
	int runtime;
	struct process *next;
	int steps;
};

struct queue{
    struct process *front;
    struct process *rear;
    int size;
};


void deQueue(struct queue *queue);
int queueSize(struct queue *queue);
void Init(struct queue *queue);
int chance10();
int randomNumber();
int randomQueue();
int isEmpty(struct queue *queue);
void enqueue(struct queue *queue, int startTime);
int idCounter();
int getTime();




int main() {

	struct queue *q1, *q2;
	q1 = (struct queue *)malloc(sizeof(struct queue));
	q2 = (struct queue *)malloc(sizeof(struct queue));
	Init(q1);
	Init(q2);



    while(main_counter != 10){
        main_counter++;
    }
}



// Initialize the Queue
void Init(struct queue *queue){
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
	return queue->front == NULL;
}

// Delete an item from the Queue
void deQueue(struct queue *queue){
	if(isEmpty(queue)){		// if queue is empty return.
		return;
	}
	else{
		queue->size--;			// decrease size of queue
		struct process *temp;	// create a temporary pointer
		temp = queue->front;	// set the address of the node for delete, equal to temp
		queue->front = temp->next; // set the front pointer of the queue equal to next node
		free(temp);
	}
}

int idCounter(){
	return idcount++;
}

// Get the size of a queue
int queueSize(struct queue *queue){
	return queue->size;
}

// add a new node in the queue
void enqueue(struct queue *queue, int startTime){
	struct process *new;
	new = (struct process *)malloc(sizeof(struct process));
	new->id = idCounter();
	new->size = randomNumber();
	new->strtime = getTime();
	new->condition = "standBy";
	new->runtime = -1;
	new->next = NULL;

	if(isEmpty(queue)){	// if queue is empty, then set new as front and rear together.
		queue->front = new;
	}
	else{
		(queue->rear)->next = new;
	}
	queue->rear = new;
	queue->size++;
}

int getTime(){
	return main_counter;
}









