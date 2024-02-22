// Name: Lanz Alexander Malto
// Date Created: November 3, 2023
// Date Finished: November 9, 2023
/* Summary of the problem: The program shall take the user's input on a particular number of 
people's height and weight information to determine their BMI and BMI classification, one at a time. 
Taking elements to display, edit, or delete will follow the concept/format of LINKED-LIST BASED QUEUES, 
utilizing standard functions based on this data structure.*/

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <stdbool.h>
#define strsize 40

typedef struct queue *nodeptr;
typedef struct queue
{
	char first[strsize];
	char last[strsize];
	float heightcm;
	float weightlb;
	nodeptr next;
} QUEUE;

//function prototypes
int menu(void);

//prototypes of the program's main features 
void AddToQueue(nodeptr *MAINQ, nodeptr *MHEAD, nodeptr *MTAIL, bool *chk);
void SearchandEdit(nodeptr *MAINQ, nodeptr *MHEAD, nodeptr *MTAIL, bool *chk);
void SearchandDelete(nodeptr *MAINQ, nodeptr *MHEAD, nodeptr *MTAIL, bool *chk);
void DisplayQueue(nodeptr *MAINQ, nodeptr *MHEAD, nodeptr *MTAIL, bool *chk);

//prototypes of queue-based functions/operations
void CreateQueue(nodeptr *MAINQ, nodeptr *MHEAD, nodeptr *MTAIL, bool *chk);
void Enqueue(nodeptr *QUE, nodeptr *ELEMENT, nodeptr *HEAD, nodeptr *TAIL);
nodeptr Dequeue(nodeptr *QUE, nodeptr *HEAD, nodeptr *TAIL);
bool EmptyQueue(nodeptr QUE);

//prototypes of other functions
void proceed(void);
void display(nodeptr element);

int main(void)
{
	int pick;
	nodeptr MAINQ, MHEAD, MTAIL;
	bool chk = false; 
	
	do {
		pick = menu();
	
		switch (pick)
		{
			//create queue
			case 1: CreateQueue(&MAINQ, &MHEAD, &MTAIL, &chk);
					break;
			//add element into the queue
			case 2: AddToQueue(&MAINQ, &MHEAD, &MTAIL, &chk);
					break;
			case 3: SearchandEdit(&MAINQ, &MHEAD, &MTAIL, &chk);
					break;
			//search and delete element from the queue
			case 4: SearchandDelete(&MAINQ, &MHEAD, &MTAIL, &chk);
					break;
			//display all the elements in the queue
			case 5: DisplayQueue(&MAINQ, &MHEAD, &MTAIL, &chk);
					break;
			//exit program
			case 6: printf("\n Press any key to continue... ");
					getch();
					exit(0);
		}
	
 	} while (pick != 6); 
	
	return 0;
}

//function definitions

int menu(void)
{
	int choice;
	
	do {

		printf("\t==========\n");
		printf("\t   MENU");
		printf("\n\t==========\n\n");
		
		printf(" 1. Create Queue");
		printf("\n 2. Add to Queue");
		printf("\n 3. Search and Edit");
		printf("\n 4. Search and Delete");
		printf("\n 5. Display All Element of the Queue");
		printf("\n 6. Exit the Program");
		
		printf("\n\n Pick a choice (1-6): ");
		scanf("%d", &choice);
		
		if (choice < 1 || choice > 6)
		{
			printf("\n Error in choice! Please pick a number from 1 to 6.\n\n");
			proceed();
		}
				
	} while (choice < 1 || choice > 6); // trapping for invalid menu choice.
	
	return choice;
}

void CreateQueue(nodeptr *MAINQ, nodeptr *MHEAD, nodeptr *MTAIL, bool *chk) 
{
	nodeptr mainq = *MAINQ, head = *MHEAD, tail = *MTAIL;
	bool chkr = *chk;
	char c;
	
	if (chkr && !EmptyQueue(mainq)) // * If elements are inside the queue...
	{
		// ...warn the user and ask for confirmation if they want to continue deleting the existing elements.
		printf("\n The queue already has elements!\n\n"); 
		
		do { 			
			printf(" Would you like to continue initiating this function and empty out the queue's contents (Y/N)? ");
			scanf(" %c", &c);
			
			if (c == 'Y' || c == 'y')
			{
				printf("\n The queue has been overwritten!\n\n");					
				break;				
			}
							
			else if (c == 'N' || c == 'n')
			{
				printf("\n The overwriting of the queue has been cancelled.\n\n");
				proceed();
				return;
			}
			
			else 
				printf("\n Error in choice! Please try again.\n\n");
			
		} while (c != 'Y' && c != 'y' && c != 'N' && c != 'n');
	}
	
	else
		printf("\n The queue has been created!\n\n");
	
	mainq = NULL;		
	head = NULL;
	tail = NULL;
	
	*MAINQ = mainq;		// (b) Return the memory addresses of queue, head, and tail.
	*MHEAD = head;
	*MTAIL = tail;
	
	chkr = true;		// (a) Return true once the linked-list has been initialized.
	*chk = chkr; 		
	
	proceed();
	return;	
	
}

void AddToQueue(nodeptr *MAINQ, nodeptr *MHEAD, nodeptr *MTAIL, bool *chk)
{
	nodeptr mainq = *MAINQ, head = *MHEAD, tail = *MTAIL;
	nodeptr element = (nodeptr) malloc(sizeof(QUEUE));
	bool chkr = *chk;
	
	//structure elements
	char fnam[strsize], lnam[strsize];
	float height, weight;
	
	// * Check if the queue has been created. 
	// (a) If the queue hasn't been created, output an error message & tell the user to create the queue first.
	if (chkr == false) 	
		printf("\n The queue has not been created. Please create one first.\n\n");
	
	else // (b) Since we're using a linked-list to simulate the queue, there is no need to check for a full queue.				
	{	
		// i. Ask for input...
		system("cls");
		printf("\t ================\n");
		printf("\t   ADD TO QUEUE\n");
		printf("\t ================\n");
		
		printf("\n Enter first name: " );
		fflush(stdin); 
		gets(fnam);
		strcpy(element -> first, fnam);
	
		printf("\n Enter last name: " );
		fflush(stdin); 
		gets(lnam); 
		strcpy(element -> last, lnam);
		
		do {
			printf("\n Enter height (in centimeters): ");
			scanf("%f", &height); 
			
			if (height < 1)
				printf("\n Invalid value. Please try again.\n"); 
			
		} while (height < 1);
		
		element -> heightcm = height;
			
		do {
			printf("\n Enter weight (in pounds): ");
			scanf("%f", &weight); 
			
			if (weight < 1)
				printf("\n Invalid value. Please try again.\n");
			
		} while (weight < 1);
		
		element -> weightlb = weight; 
		element -> next = NULL; 
		
		// ...then call Enqueue() to add the new element at the end of the queue. 
		Enqueue(&mainq, &element, &head, &tail);	// (c) Be sure to pass the element to be added as parameter of Enqueue().
		
		*MAINQ = mainq;
		*MHEAD = head;
		*MTAIL = tail;
		
		// ii. Output an informational message that a new element has been added to the queue.
		printf("\n Information recorded! This element block has been added to the queue.\n\n");			
	}
	
	proceed();
	return;
}

void SearchandEdit(nodeptr *MAINQ, nodeptr *MHEAD, nodeptr *MTAIL, bool *chk)
{
	nodeptr mq = *MAINQ, mh = *MHEAD, mt = *MTAIL, element;		//main queue
	nodeptr tq = NULL, th = NULL, tt = NULL;					//temp queue
	bool chkr = *chk;
	
	//structure elements
	char fnam[strsize], lnam[strsize], c;
	float height, weight;
	
	// * Check if the queue has been created. 
	// (a) If the queue hasn't been created, output an error message & tell the user to create the queue first.
	if (chkr == false)
		printf("\n The queue has not been created. Please create one first.\n\n");
	
	else
	{
		 // (b) If the queue has been created, check if it is empty by calling EmptyQueue().
		 	// i. If the queue is empty, output an error message.
		if (EmptyQueue(mq))				 
			printf("\n The queue is empty! Please insert at least one element inside it.\n\n");
			
			// ii. If the queue is NOT empty...
		else 									
		{
			system("cls");
			printf("\t ===================\n");
			printf("\t   SEARCH AND EDIT\n");
			printf("\t ===================\n");
			
			printf("\n Enter first name: " );
			fflush(stdin); 
			gets(fnam);
		
			printf("\n Enter last name: " );
			fflush(stdin); 
			gets(lnam); 
			
			while (!EmptyQueue(mq))	
			{
				// ...search for the element by calling Dequeue() and comparing the element to the one you're searching for.
				element = Dequeue(&mq, &mh, &mt); 		
				
				// iii. If the element exists, display contents on the screen (incl. BMI + category)...
				if ((strcmpi(element -> first, fnam) == 0) && (strcmpi(element -> last, lnam) == 0))
				{	
					printf("\n Record found! Displaying: \n\n");
					display(element);					
					
					// ...and output a confirmation message before editing the element's contents.
					do {
						printf(" Continue with editing (y/n)? ");
						scanf(" %c", &c);
						
						// 1. Allow editing only on height and weight. 
						// 2. Modify the contents before returning it to the original queue.*	
						if (c == 'Y' || c == 'y')	
						{
							do {
								printf("\n Enter height (in centimeters): ");
								scanf("%f", &height); 
								
								if (height < 1)
									printf("\n Invalid value. Please try again.\n"); 
								
							} while (height < 1);
						
							element -> heightcm = height;
							
							do {
								printf("\n Enter weight (in pounds): ");
								scanf("%f", &weight); 
								
								if (weight < 1)
									printf("\n Invalid value. Please try again.\n");
								
							} while (weight < 1);
							
							element -> weightlb = weight;
						}
							
						else if (c == 'N' || c == 'n')
							break;
						
						else
							printf("\n Error in choice! Please try again.");
							
					} while (c != 'Y' && c != 'y' && c != 'N' && c != 'n');
					
					// *I opted to enqueue all the elements (+ the one searched for) into the temp queue first 
					// before returning so it follows the proper order in the main queue (d).
					
					Enqueue(&tq, &element, &th, &tt);	// Enqueueing the element to temp queue...
					
					while (!EmptyQueue(mq))		// Flushing out the remaining contents of main queue...
					{
						element = Dequeue(&mq, &mh, &mt); 			
						Enqueue(&tq, &element, &th, &tt); 							
					}
					
					while (!EmptyQueue(tq))		// Returning contents of temp queue back to main queue, in proper order.
					{
						element = Dequeue(&tq, &th, &tt); 
						Enqueue(&mq, &element, &mh, &mt);
					}
				
					*MAINQ = mq;
					*MHEAD = mh;
					*MTAIL = mt;

					if (c == 'Y' || c == 'y')
						printf("\n Information updated successfully!\n\n");
					else if (c == 'N' || c == 'n')
						printf("\n Information not edited. Returning to main menu.\n\n");
						
					proceed();
					return;
				}
			
				else	// iv. If the element isn't the one being searched for, call Enqueue() to add it into the temp queue.
					Enqueue(&tq, &element, &th, &tt); 							
			}
			
			// If the main queue gets emptied out trying to look for the element but it doesn't exist, 
			// we put everything back from temp queue back into the main queue.
			
			while (!EmptyQueue(tq))
			{
				element = Dequeue(&tq, &th, &tt); 
				Enqueue(&mq, &element, &mh, &mt);
			}
			
			*MAINQ = mq;
			*MHEAD = mh;
			*MTAIL = mt;
			
			// (c) If the element does not exist, output an error message.
			printf("\n This information does not exist.\n\n");
		}
	}
	
	proceed();
	return;
}

void SearchandDelete(nodeptr *MAINQ, nodeptr *MHEAD, nodeptr *MTAIL, bool *chk)
{
	nodeptr mq = *MAINQ, mh = *MHEAD, mt = *MTAIL, element;		//main queue
	nodeptr tq = NULL, th = NULL, tt = NULL;					//temp queue
	bool chkr = *chk;

	//structure elements
	char fnam[strsize], lnam[strsize], c;
	float height, weight;
	
	// * Check if the queue has been created. 
	// (a) If the queue hasn't been created, output an error message & tell the user to create the queue first.
	if (chkr == false) 	
		printf("\n The queue has not been created. Please create one first.\n\n");
	
	else				
	{
		// (b) If the queue has been created, check if it is empty by calling EmptyQueue().
			// i. If the queue is empty, output an error message.
		if (EmptyQueue(mq)) 
			printf("\n The queue is empty! Please insert at least one element inside it.\n\n");

			// ii. If the queue is NOT empty...			
		else 									
		{
			system("cls");
			printf("\t ===================\n");
			printf("\t   SEARCH AND DELETE\n");
			printf("\t ===================\n");
			
			printf("\n Enter first name: " );
			fflush(stdin); 
			gets(fnam);
		
			printf("\n Enter last name: " );
			fflush(stdin); 
			gets(lnam); 
			
			while (!EmptyQueue(mq))	
			{
				// ...search for the element by calling Dequeue() and comparing the element to the one you're searching for.
				element = Dequeue(&mq, &mh, &mt); 		
				
				// iii. If the element exists, display contents on the screen (incl. BMI + category)...
				if ((strcmpi(element -> first, fnam) == 0) && (strcmpi(element -> last, lnam) == 0))
				{
					printf("\n Record found! Displaying: \n\n");
					display(element);
					
					// ...and output a confirmation message before removing the element. 					
					do {
						printf(" Continue with deleting (y/n)? ");
						scanf(" %c", &c);
						
						// Upon the choice of the user to delete the element, I opted to overwrite it by dequeueing 
						// once more from main queue, then inserting that one into the temp queue.
						if (c == 'Y' || c == 'y')	
						{
							printf("\n Element deleted!\n\n"); 
							break;
						}
						
						// If the user decides not to go through with the deletion, I opted to simply enqueue it inside
						// the temp queue, and the next algorithm below will follow.	
						else if (c == 'N' || c == 'n')
						{
							printf("\n Information not deleted. Returning to main menu.\n\n");
							Enqueue(&tq, &element, &th, &tt);
							
							break;
						}
						
						else
							printf("\n Error in choice! Please try again.");
							
					} while (c != 'Y' && c != 'y' && c != 'N' && c != 'n');
								
					// All elements remaining in main queue will be enqueued into the temp queue to retain the correct order.
					while (!EmptyQueue(mq))		
					{
						element = Dequeue(&mq, &mh, &mt); 	// element will be overwritten when c is Y or y.			
						Enqueue(&tq, &element, &th, &tt); 							
					}
					
					// Then, temp queue will be emptied out next. All elements will be returned back to main queue, 
					// in the correct order.
					while (!EmptyQueue(tq))
					{
						element = Dequeue(&tq, &th, &tt); 
						Enqueue(&mq, &element, &mh, &mt);
					}			
												
					*MAINQ = mq;
					*MHEAD = mh;
					*MTAIL = mt;
					
					proceed();
					return;
				}
				
				else
					Enqueue(&tq, &element, &th, &tt);
			}
			
			// If the main queue gets emptied out trying to look for the element but it doesn't exist, 
			// we put everything back from temp queue back into the main queue.
			
			while (!EmptyQueue(tq))
			{
				element = Dequeue(&tq, &th, &tt); 
				Enqueue(&mq, &element, &mh, &mt);
			}	
			
			*MAINQ = mq;
			*MHEAD = mh;
			*MTAIL = mt;
			
			// (c) If the element does not exist, output an error message.		
			printf("\n This information does not exist.\n\n");
		}
	}
	
	proceed();
	return;
}

void DisplayQueue(nodeptr *MAINQ, nodeptr *MHEAD, nodeptr *MTAIL, bool *chk)
{
	nodeptr mq = *MAINQ, mh = *MHEAD, mt = *MTAIL, element;		//main queue
	nodeptr tq = NULL, th = NULL, tt = NULL;					//temp queue
	bool chkr = *chk;
	
	if (chkr == false) 
		printf("\n The queue has not been created. Please create one first.\n\n");
	
	else 				
	{
		// Making calls to EmptyQueue(), Dequeue(), and Enqueue(). Also utilizing a temporary queue.
		if (EmptyQueue(mh)) 	
			printf("\n The queue is empty! Please insert at least one element inside it.\n\n");
			
		else									
		{
			system("cls");
			printf("\t ================\n");
			printf("\t    DISPLAY ALL\n");
			printf("\t ================\n\n");
												
			while (!EmptyQueue(mq))					
			{
				element = Dequeue(&mq, &mh, &mt); 			
				display(element); 						
				Enqueue(&tq, &element, &th, &tt); 							
			}
			
			// ...after displaying all elements, we return them from the temp queue to the original queue.
			while (!EmptyQueue(tq))
			{
				element = Dequeue(&tq, &th, &tt); 
				Enqueue(&mq, &element, &mh, &mt);
			}
			
			printf(" All information displayed!\n\n");
		}
	}
	
	*MAINQ = mq;
	*MHEAD = mh;
	*MTAIL = mt;
	
	proceed();
	return;
}

void Enqueue(nodeptr *QUE, nodeptr *ELEMENT, nodeptr *HEAD, nodeptr *TAIL)
{	
	nodeptr q = *QUE, e = *ELEMENT, h = *HEAD, t = *TAIL;
	
	if (q == NULL) 			// empty queue.
	{
		q = e;
		h = e;
		t = e;
	}
	
	else 
	{
		t -> next = e;
		t = t -> next;
	}
	
	*QUE = q;
	*ELEMENT = e;
	*HEAD = h;
	*TAIL = t;
}

nodeptr Dequeue(nodeptr *QUE, nodeptr *HEAD, nodeptr *TAIL)
{
	nodeptr q = *QUE, h = *HEAD, t = *TAIL, e = *HEAD;
	
	if (q -> next == NULL)	//last element.
		t = NULL;
		
	q = q -> next;
	h -> next = NULL;
	h = q;
	
	*QUE = q;
	*HEAD = h;
	*TAIL = t;
	
	return e;
}

bool EmptyQueue(nodeptr QUE)
{
	if (QUE == NULL)
		return true;
	else
		return false;
}

// a simple function reused in this program for continuity.
void proceed(void)
{
	printf(" Press any key to continue... ");
	getch();
	system("cls");
}

void display(nodeptr element) 
{
	char fn[strsize], ln[strsize], c;
	float height_m, weight_kg, BMI;

	strcpy(fn, element -> first);
	strcpy(ln, element -> last);
	printf(" Name: %s %s\n", fn, ln);
	
	height_m = element -> heightcm/100;					
	printf(" Height: %.2f meters\n", height_m);
	
	weight_kg = element -> weightlb * 0.45359237;
	printf(" Weight: %.2f kilograms\n", weight_kg);
	
	BMI = weight_kg/(height_m * height_m);
	printf(" BMI: %.2f\n", BMI);
	
	printf(" Classification: ");
	
	if (BMI < 18.5)
		printf("Underweight");
	else if (BMI >= 18.5 && BMI <= 24.9)
		printf("Normal weight");
	else if (BMI >= 25 && BMI <= 29.9)
		printf("Overweight");
	else if (BMI >= 30)
		printf("Obese");
		
	printf("\n\n");
}
