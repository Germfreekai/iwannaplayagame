#include <stdio.h>
#include <stdlib.h>
int count=0;
typedef struct Processes{
	int id;
	int remainingTime;
	struct Processes *next;
} Process;

Process *front;

Process *createProcess(int id, int remainingTime){
	Process *toAdd=(Process *)malloc(sizeof(Process));
	toAdd->id=id;
	toAdd->remainingTime=remainingTime;
	toAdd->next=NULL;
	return toAdd;
}
void enqueue(Process *toAdd){
	if(front==NULL){
		front=toAdd;
	}else{
		Process *temp=front;
		while(temp->next!=NULL){
			temp=temp->next;
		}
		temp->next=toAdd;
	}
	count++;
}

Process *dequeue(){
	Process *toReturn=front;
	front=front->next;
	count--;
	toReturn->next=NULL;
	return toReturn;
}

void printQueue(){
	Process *temp=front;
	printf("Total:%d;", count);
	while(temp!=NULL){
			printf("id:%d,rT:%d;",temp->id, temp->remainingTime);
			temp=temp->next;
	}
	printf("\n");
}

int main(){
	printQueue();
	enqueue(createProcess(1, 10));
	Process *p1=createProcess(2, 20);
	enqueue(p1);
	printQueue();
	Process *p=dequeue();
	printf("Sacado %d con tiempo %d\n", p->id, p->remainingTime);
	p=dequeue();
	printf("Sacado %d con tiempo %d\n", p->id, p->remainingTime);
	printQueue();
	return 0;
}