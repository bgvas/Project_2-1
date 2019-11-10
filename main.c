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
void enqueue(struct queue *queue);
int idCounter();
int getTime();
void deleteIf10steps(struct queue *q1, struct queue *q2);






int main() {

	srand(time(NULL)); // set random-engine
	struct queue *q1, *q2;
	q1 = (struct queue *)malloc(sizeof(struct queue));
	q2 = (struct queue *)malloc(sizeof(struct queue));
	Init(q1);
	Init(q2);
	int processes, i, pro;


	printf("How many processes would you like to add?");
	scanf("%d", &processes);
	for(i = 1; i <= processes;){
		pro = randomQueue();
		if(pro == 1){
			enqueue(q1);
			i++;
		}
		else if(pro == 2){
			enqueue(q2);
			i++;
		}
	}

	struct process *proc;

	while(main_counter <= 10){

		// add a new process into q1(30%) or q2(20%)
		pro = randomQueue();
		if(pro == 1){
			enqueue(q1);
		}
		else if(pro == 2){
			enqueue(q2);
		}


		// run a process from q1 (if not empty) Or from q2
		if(!isEmpty(q1)){
			if((q1->front)->runtime == -1){
				(q1->front)->runtime = randomNumber();
				(q1->front)->condition = "running";
			}
		}
		else{
			if((q2->front)->runtime == -1){
				(q2->front)->runtime = randomNumber();
				(q2->front)->condition = "running";
			}
		}

		// if a process in q2 is for 10 steps "standBy" delete it and put it in q1 rear
		proc = q2->front;
		while(proc != NULL){
			if(proc->steps >= 10 && proc->condition == "standBy"){
				deleteIf10steps(q1,q2);
			}
			proc = proc->next;
		}


		// increase every process one step
		proc = q1->front;
		while(proc != NULL){
			proc->steps++;
			proc = proc->next;
		}

		proc = q2->front;
		while(proc != NULL){
			proc->steps++;
			proc = proc->next;
		}
		printf("\nSize of queue 1: %d - Size of queue 2: %d\n", q1->size, q2->size);
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
    int randomq = rand() % 10 + 1;
    if(randomq < 2){	// select Queue 1 for 10%
        return 1;
    }else{
        return 0;
    }
}

// Function for random numbers
int randomNumber(){
	int randomnumber = rand()%10 + 1;	    // generate random numbers (1-10)
	return randomnumber;
}

// Function for Queue random selection
int randomQueue(){
	int randomq = randomNumber();
	if(randomq < 4){
		return 1;
	}
	else if(randomq < 6){
		return 2;
	}
	else return 0;
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
void enqueue(struct queue *queue){
	struct process *new;
	new = (struct process *)malloc(sizeof(struct process));
	new->id = idCounter();
	new->size = randomNumber();
	new->strtime = getTime();
	new->condition = "standBy";
	new->runtime = -1;
	new->next = NULL;
	new->steps = 0;

	if(isEmpty(queue)){	// if queue is empty, then set new as front - rear together.
		queue->front = new;
	}
	else{
		(queue->rear)->next = new;
	}
	queue->rear = new;
	queue->size++;
}

// get time from mainCounter
int getTime(){
	return main_counter;
}

// if a process in q2 is for 10 steps "standBy" delete it and put it in q1 rear
void deleteIf10steps(struct queue *q1, struct queue *q2){
	if(isEmpty(q2)){
		return;
	}
	struct process *temp;
	temp = q2->front;
	q2->front = (q2->front)->next;
	if(isEmpty(q1)){
		q1->front == temp;
	}
	else{
		(q1->rear)->next = temp;
	}
	q1->rear = temp;
	temp->next = NULL;
	q1->size++;
	q2->size--;
}
