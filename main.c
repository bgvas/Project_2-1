/* Project 2
*               Vasileios Georgoulas AM:2118147
*  Author's:    &
*               Ioannis Skoumpas     AM: 2118063
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define STEPS 100000

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


int queueSize(struct queue *queue);
void Init(struct queue *queue);
void chance10(struct queue *q1, struct queue *q2);
int randomNumber();
int randomQueue();
int isEmpty(struct queue *queue);
void enqueue(struct queue *queue);
int idCounter();
int getTime();
void mixQueues(struct queue *q);
void deleteIf10steps(struct queue *q1, struct queue *q2);
void checkCompletedProcesses(struct queue *q);
struct queue *merge(struct queue *q1, struct queue *q2);
void sort(struct queue *q);
int cmpNode(struct process *a, struct process *b);
int sumForProcessSize = 0;




int main() {

	srand(time(NULL)); // set random-engine
	struct queue *q1, *q2;
	q1 = (struct queue *)malloc(sizeof(struct queue));
	q2 = (struct queue *)malloc(sizeof(struct queue));
	Init(q1);
	Init(q2);
	int processes, i, pro;


	// ask from user to set the number of starting process
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
	
	int sumForQ1Size = 0;
	int sumForQ2Size = 0;
	int processCounter = 0;
	float processSizeAverage = 0;
	float q1SizeAverage = 0;
	float q2SizeAverage = 0;

	while(main_counter <= STEPS){ // starting simulation

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
				(q1->front)->steps = 0;
			}
		}
		else{
			if((q2->front)->runtime == -1){
				(q2->front)->runtime = randomNumber();
				(q2->front)->condition = "running";
				(q2->front)->steps = 0;
			}
		}
		
		// check if running processes, has completed
		checkCompletedProcesses(q1);
		checkCompletedProcesses(q2);
	
		// if a process in q2 is for 10 steps "standBy" delete it and put it in q1 rear
		deleteIf10steps(q1,q2);

		// for 10% get randomly a node from queue and put it in the front position of queue
		chance10(q1, q2);
		
		// increase every process by one step
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
		
		sumForQ1Size += q1->size;
		sumForQ2Size += q2->size;
        main_counter++;
    }
    q1SizeAverage = (float)sumForQ1Size/STEPS;
    q2SizeAverage = (float)sumForQ2Size/STEPS;
    processSizeAverage = (float)sumForProcessSize/sumForQ2Size;
    printf("\n\nAverage size of Q1: %0.1f", q1SizeAverage);
    printf("\nAverage size of Q2: %0.1f", q2SizeAverage);
    printf("\nAverage size of node: %0.1f", processSizeAverage);
    sort(merge(q1, q2)); // merge the 2 queues, sort the new list and print it
    free(proc);
    free(q1);
    free(q2);
}





// Initialize the Queue
void Init(struct queue *queue){
    queue->front = NULL;
    queue->rear = NULL;
    queue->size = 0;
}

// change positions in Q2 and Q1 if 10%
void chance10(struct queue *q1, struct queue *q2){
    int randomq = rand() % 10 + 1;
    if(randomq < 1){	// when 10% go on
       mixQueues(q1);
       mixQueues(q2);
    }else{
        return;
    }
}

// Get randomly a node from queue and put it in the front position of this queue
void mixQueues(struct queue *q){
		int i, randSelection;

		if(!isEmpty(q)){
			struct process *previous;
			struct process *actual;
			previous = (struct process *)malloc(sizeof(struct process));
			actual = (struct process *)malloc(sizeof(struct process));
			actual = q->front;
			previous = actual;
			randSelection = rand()%sizeof(q) + 1;	// get a random node
			for(i = 1; i < randSelection; i++){ // begin from 1 and stop queue crossing in the random node
				previous = actual;
				actual = actual->next;
			}
			previous->next = actual->next;	// remove the random node from it position
			actual->next = q->front;	// and put it in the front position of queue
			q->front = actual;
			free(previous);
			free(actual);
		}

		else {
			return;
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
	if(randomq < 4){	// select Queue-1 with  30% possibility
		return 1;
	}
	else if(randomq < 6){
		return 2;		// select Queue-2 with  20% possibility
	}
	else return 0;
}

// Check if queue is empty
int isEmpty(struct queue *queue){
	return queue->front == NULL;
}

// Get numbers for Processes id
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

	if(isEmpty(queue)){	// if queue is empty, then set new as front & rear together.
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
	struct process *node, *previous;
	node = q2->front;
	previous = node;
	while(node != NULL){
		sumForProcessSize += node->size; // get sum of q2 nodes->size 
		if((node->steps >= 10) && node->condition == "standBy"){ // if the node is the only node of queue
			if(q2->front == node && q2->rear == node){
				q2->front = q2->rear = NULL;
				q2->size--;
				
				(q1->rear)->next = node;
				q1->rear = node;	// put the node from q2 to q1 rear
				node->next = NULL;
				node->steps = 0;
				q1->size++;
				return;
			}
			else if(q2->front == node && q2->rear != node){ // if the node is the queue-front
				q2->front = node->next;
				previous = node->next;
				q2->size--;
				
				(q1->rear)->next = node;
				q1->rear = node;	// put the node from q2 to q1 rear
				node->next = NULL;
				node->steps = 0;
				q1->size++;
				
				node = previous;
			}
			else if(q2->front != node && q2->rear == node){// if the node is the queue-rear
				q2->rear = previous;
				previous->next = NULL;
				
				q2->size--;
				(q1->rear)->next = node;
				q1->rear = node;	// put the node from q2 to q1 rear
				node->next = NULL;
				node->steps = 0;
				q1->size++;
				
				return;
			}
			else if(q2->front != node && q2->rear != node){ // if the node is in the middle of queue
				previous->next = node->next;
				
				q2->size--;
				(q1->rear)->next = node;
				q1->rear = node;	// put the node from q2 to q1 rear
				node->next = NULL;
				node->steps = 0;
				q1->size++;
				
				node = previous->next;
			}
			
		}
		else{
			previous = node;
			node = node->next;	// if can't find node with 10 steps in standBy, go on next
		}
	}
}

// check if there are completed running processes, and delete them
void checkCompletedProcesses(struct queue *q){
	if(isEmpty(q)){
		return;
	}
	struct process *node, *previous;
	node = q->front;
	previous = node;
	while(node != NULL){
		if((node->steps == node->runtime) && node->condition == "running"){
			if(q->front == node && q->rear == node){// if the node is the only node of queue
				q->front = q->rear = NULL;
				free(node);
				free(previous);
				q->size--;
				return;
			}
			else if(q->front == node && q->rear != node){// if the node is the queue-front
				q->front = node->next;
				previous = node->next;
				node = previous;
				q->size--;
			}
			else if(q->front != node && q->rear == node){// if the node is the queue-rear
				previous->next = NULL;
				q->rear = previous;
				free(node);
				free(previous);
				q->size--;
				return;
			}
			else if(q->rear != node && q->front != node){// if the node is in the middle of queue
				previous->next = node->next;
				node = previous->next;
				q->size--;
			}
		}
		else{ // if can't find completed running node, go on next
			previous = node;
			node = node->next;
		}
	}
	
}

// merge the 2 queues in one
struct queue *merge(struct queue *q1, struct queue *q2){
    struct queue *list = (struct queue *)malloc(sizeof(struct queue));
    struct process *node = (struct process *)malloc(sizeof(struct process));
    list = q1;
    node = q2->front;
    while(node != NULL){
        (list->rear)->next = node;
        list->size++;
        list->rear = node;
        node = node->next;
    }
    free(node);
    return list;
}

// function for sorting and printing data from queues
void sort(struct queue *q){
	struct process *node;
	struct process *temp;
	
	// create an array of structs
	struct process *list[queueSize(q)];
	node = q->front;
	int i = 0, j;
	printf("\n\nWait for sorting...\n");
	while(node != NULL){	// put every node that exists in the array
		list[i] = node; 	
		node = node->next;
		i++;
	}
	// sort with Bubble Sort
	for (j = 0; j < queueSize(q) - 1; ++j){
    	for (i = 0; i < queueSize(q) - j - 1; ++i){
      		if (list[i]->size > list[i + 1]->size){ // if previous-size > next-size then
        		temp = list[i];		// switch places
        		list[i] = list[i + 1];
        		list[i + 1] = temp;
      		}
    	}
  	}
	
    // print all sorted nodes
    printf("\nId - size\n");
    printf("-----------\n");
    for(i = 0; i < queueSize(q); i++){
		printf("%d   \t%d\n",list[i]->id, list[i]->size);
	}
	
	free(temp);
	free(node);
}
