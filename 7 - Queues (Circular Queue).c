// Name: Lanz Alexander Malto
// Date Created: October 18, 2023
// Date Finished: October 27, 2023
/* Summary of the problem: The program shall take the user's input on a particular number of 
people's height and weight information to determine their BMI and BMI classification, one at a time. 
Taking elements to display, edit, or delete will follow the concept/format of CIRCULAR QUEUES, 
utilizing standard functions based on this data structure.*/

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <stdbool.h>
#define size 5
#define strsize 40

typedef struct queue
{
	char first[strsize];
	char last[strsize];
	float heightcm;
	float weightlb;
} QUEUE;

//function prototypes
int menu(void);
//prototypes of the program's main features 
void AddToQueue(QUEUE main_q[size], int *mhead, int *mtail, bool *chk);
void SearchandEdit(QUEUE main_q[size], int *mhead, int *mtail, bool *chk);
void SearchandDelete(QUEUE main_q[size], int *mhead, int *mtail, bool *chk);
void DisplayQueue(QUEUE main_q[size], int *mhead, int *mtail, bool *chk);
//prototypes of queue-based functions/operations
void CreateQueue(QUEUE main_q[size], int *mhead, int *mtail, bool *chk);
void Enqueue(QUEUE queue[size], QUEUE element, int *tail);
QUEUE Dequeue(QUEUE queue[size], int *head);
bool FullQueue(QUEUE queue[size], int tail, int head);
bool EmptyQueue(QUEUE queue[size], int tail, int head);
//prototypes of other functions
void proceed(void);
void display(QUEUE element);

int main(void)
{
	int pick;
	QUEUE main_q[size];
	QUEUE element; 
	int mtail = -1, mhead = 0;
	bool chk = false; 
	
	do {
		pick = menu();
	
		switch (pick)
		{
			//create queue
			case 1: CreateQueue(main_q, &mhead, &mtail, &chk);
					break;
			//add element into the queue
			case 2: AddToQueue(main_q, &mhead, &mtail, &chk);
					break;
			case 3: SearchandEdit(main_q, &mhead, &mtail, &chk);
					break;
			//search and delete element from the queue
			case 4: SearchandDelete(main_q, &mhead, &mtail, &chk);
					break;
			//display all the elements in the queue
			case 5: DisplayQueue(main_q, &mhead, &mtail, &chk);
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


void CreateQueue(QUEUE main_q[size], int *mhead, int *mtail, bool *chk) // (a) pass the queue, the head, and the tail as parameters.
{
	int i, MHEAD = *mhead, MTAIL = *mtail;
	bool chkr = *chk;
	char c;
	
	if (!EmptyQueue(main_q, MTAIL, MHEAD)) // * If elements are inside the queue...
	{
		// ...warn the user and ask for confirmation if they want to continue deleting the existing elements.
		printf("\n The queue already has elements!\n\n"); 
		
		do { 			
			printf(" Would you like to continue initiating this function and empty out the queue's contents (Y/N)? ");
			scanf(" %c", &c);
			
			if (c == 'Y' || c == 'y')
			{
				for (i = 0; i < size; i++) // (b) initialize the contents of the array [Alternate case]. 
				{
					strcpy(main_q[i].first, " ");
					strcpy(main_q[i].last, " ");
					main_q[i].heightcm = 0.00;
					main_q[i].weightlb = 0.00;	
				}
				
				printf("\n The queue has been overwritten!\n\n");
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
	{
		for (i = 0; i < size; i++) // (b) initialize the contents of the array [Default case].
		{
			strcpy(main_q[i].first, " ");
			strcpy(main_q[i].last, " ");
			main_q[i].heightcm = 0.00;
			main_q[i].weightlb = 0.00;	
		}
		
		printf("\n The queue has been created!\n\n");		
	}
	
	// (c) Return true once the array has been initialized; and
	// (d) Also, assign a -1 to tail, a 0 to head, and return its value to the calling function.
	MTAIL = -1;  		
	*mtail = MTAIL; 
	MHEAD = 0;
	*mhead = MHEAD;
	chkr = true;
	*chk = chkr; 		
	
	proceed();
	return;	
	
}

void AddToQueue(QUEUE main_q[size], int *mhead, int *mtail, bool *chk)
{
	int MHEAD = *mhead, MTAIL = *mtail;
	QUEUE element;
	bool chkr = *chk;
	//structure elements
	char fnam[strsize], lnam[strsize];
	float height, weight;
	
	// * Check if the queue has been created. 
	
	if (chkr == false) 	// (a) If not created: output an error message telling the user to create the queue.
		printf("\n The queue has not been created. Please create one first.\n\n");
	
	else 				// (b) If created, check if the queue is full.
	{	
		if (FullQueue(main_q, MTAIL, MHEAD)) // (i.) If it is full, output an error message.
			printf("\n The queue is full! No additional elements can be accomodated.\n\n");
		
		else								// (ii.) If it is not full, ask for input...
		{
			system("cls");
			printf("\t ================\n");
			printf("\t   ADD TO QUEUE\n");
			printf("\t ================\n");
			
			printf("\n Enter first name: " );
			fflush(stdin); 
			gets(fnam);
			strcpy(element.first, fnam);
		
			printf("\n Enter last name: " );
			fflush(stdin); 
			gets(lnam); 
			strcpy(element.last, lnam);
			
			do {
				printf("\n Enter height (in centimeters): ");
				scanf("%f", &height); 
				
				if (height < 1)
					printf("\n Invalid value. Please try again.\n"); 
				
			} while (height < 1);
			
			element.heightcm = height;
			
			do {
				printf("\n Enter weight (in pounds): ");
				scanf("%f", &weight); 
				
				if (weight < 1)
					printf("\n Invalid value. Please try again.\n");
				
			} while (weight < 1);
			
			element.weightlb = weight; 
			
			Enqueue(main_q, element, &MTAIL); // ... then call Enqueue(). Add the new element at the end of the queue.
			
			*mhead = MHEAD;
			*mtail = MTAIL;
			
			// (iii.) Output an informational message that a new element has been added to the queue.
			printf("\n Information recorded! This element block has been added to the queue.\n\n");			
		}
	}
	
	proceed();
	return;
}

void SearchandEdit(QUEUE main_q[size], int *mhead, int *mtail, bool *chk)
{
	int MHEAD = *mhead, MTAIL = *mtail; 	//main queue
	int TTAIL = -1, THEAD = 0; 				//temp queue
	QUEUE element, temp[size];
	bool chkr = *chk;
	//structure elements
	char fnam[strsize], lnam[strsize], c;
	float height, weight;
	
	// Check if the queue has been created. 
	
	if (chkr == false) 	// (a) If not created: output an error message telling the user to create the queue.
		printf("\n The queue has not been created. Please create one first.\n\n");
	
	
	else 				// (b) If created, check if the queue is empty.
	{
		if (EmptyQueue(main_q, MTAIL, MHEAD)) 	// (i.) If it is empty, output an error message.
			printf("\n The queue is empty! Please insert at least one element inside it.\n\n");
			
		else 									// (ii.) if not empty:
		{
			system("cls");
			printf("\t ===================\n");
			printf("\t   SEARCH AND EDIT\n");
			printf("\t ===================\n");
			
			printf("\n Enter first name: " );
			fflush(stdin); 
			gets(fnam);
			strcpy(element.first, fnam);
		
			printf("\n Enter last name: " );
			fflush(stdin); 
			gets(lnam); 
			strcpy(element.last, lnam);
			
			while (!EmptyQueue(main_q, MTAIL, MHEAD))	// Search for the element in the queue.
			{
				
				element = Dequeue(main_q, &MHEAD);		// calling Dequeue().
				
				//Comparing the element to the one being searched for.
				if ((strcmpi(element.first, fnam) == 0) && (strcmpi(element.last, lnam) == 0)) 
				{	
					/* If element exists, show the contents on screen and output a confirmation message 
					before editing the contents. */
					printf("\n Record found! Displaying: \n\n");
					display(element);					
					
					do {
						
						printf(" Continue with editing (y/n)? ");
						scanf(" %c", &c);
						
						if (c == 'Y' || c == 'y')
						{
							// (1.) Allow editing only on the height and weight.
							// (2.) Modify the contents before returning it back to the original queue.
							do {
								printf("\n Enter height (in centimeters): ");
								scanf("%f", &height); 
								
								if (height < 1)
									printf("\n Invalid value. Please try again.\n"); 
								
							} while (height < 1);
						
							element.heightcm = height;
							
							do {
								printf("\n Enter weight (in pounds): ");
								scanf("%f", &weight); 
								
								if (weight < 1)
									printf("\n Invalid value. Please try again.\n");
								
							} while (weight < 1);
							
							element.weightlb = weight;
						}
							
						else if (c == 'N' || c == 'n')
							break;
						
						else
							printf("\n Error in choice! Please try again.");
							
					} while (c != 'Y' && c != 'y' && c != 'N' && c != 'n');
					
					// I opted to enqueue all the elements (+ the one searched for) into the temp queue 
					// so it follows the proper ordering when returning it all back to the main queue.
					
					Enqueue(temp, element, &TTAIL); 
					
					while (!EmptyQueue(main_q, MTAIL, MHEAD))
					{
						element = Dequeue(main_q, &MHEAD);
						Enqueue(temp, element, &TTAIL); 
					}
								
					// (d.) Returning the elements from the temporary queue to the original queue in the proper sequence:
					while (!EmptyQueue(temp, TTAIL, THEAD))
					{
						element = Dequeue(temp, &THEAD); 
						Enqueue(main_q, element, &MTAIL);
					}
				
					*mhead = MHEAD;
					*mtail = MTAIL;

					if (c == 'Y' || c == 'y')
						printf("\n Information updated successfully!\n\n");
					else if (c == 'N' || c == 'n')
						printf("\n Information not edited. Returning to main menu.\n\n");
						
					proceed();
					return;
				}
			
				// (iv.) If the element is not the one being searched for, call Enqueue() and load into a temp queue.
				else
					Enqueue(temp, element, &TTAIL); 
			}
			
			// If the main queue gets emptied out trying to look for fn & ln but it doesn't exist, 
			// we put everything back from temp queue back into the main queue.
			
			while (!EmptyQueue(temp, TTAIL, THEAD))
			{
				element = Dequeue(temp, &THEAD); 
				Enqueue(main_q, element, &MTAIL);
			}
			
			*mhead = MHEAD;
			*mtail = MTAIL;
			
			// * If the element is not existing, output an error message.
			printf("\n This information does not exist.\n\n");
		}
	}
	
	proceed();
	return;
}

void SearchandDelete(QUEUE main_q[size], int *mhead, int *mtail, bool *chk)
{
	int MHEAD = *mhead, MTAIL = *mtail; 	//main queue
	int TTAIL = -1, THEAD = 0; 				//temp queue
	QUEUE element, temp[size];
	bool chkr = *chk;
	//structure elements
	char fn[strsize], ln[strsize], c;	
	
	// Check if the queue has been created.
	
	if (chkr == false) 	// (a) If not created: output an error message telling the user to create the queue.
		printf("\n The queue has not been created. Please create one first.\n\n");
	
	else				// (b) If created, check if the queue is empty.
	{
		if (EmptyQueue(main_q, MTAIL, MHEAD)) 	// (i.) If it is empty, output an error message.
			printf("\n The queue is empty! Please insert at least one element inside it.\n\n");

		else 									// (ii.) if not empty:
		{
			system("cls");
			printf("\t =====================\n");
			printf("\t   SEARCH AND DELETE\n");
			printf("\t =====================\n");
			
			printf("\n Enter first name: "); 
			fflush(stdin);	
			gets(fn);
			
			printf("\n Enter last name: ");	
			fflush(stdin);
			gets(ln);
			
			while (!EmptyQueue(main_q, MTAIL, MHEAD)) 	// Search for the element in the queue.
			{
				element = Dequeue(main_q, &MHEAD); 		// calling Dequeue().
				
				// Comparing the element to the one being searched for.
				if ((strcmpi(element.first, fn) == 0) && (strcmpi(element.last, ln) == 0))
				{
					/* If the element is existing, show the contents on screen and 
					output a confirmation message before deleting the element
					from the queue. */
					printf("\n Record found! Displaying: \n\n");
					display(element);
										
					do {
						
						printf(" Continue with deleting (y/n)? ");
						scanf(" %c", &c);
							
						if (c == 'Y' || c == 'y')
							break; 
						
						// If the user chooses to cancel the deletion, we put the element in temp queue.				
						else if (c == 'N' || c == 'n')
							Enqueue(temp, element, &TTAIL);	
						
						else if (c != 'Y' && c != 'y' && c != 'N' && c != 'n')
							printf("\n Error in choice! Please try again.");
						
					} while (c != 'Y' && c != 'y' && c != 'N' && c != 'n');
								
					// All other elements in main queue will be transferred to temp queue...
					while (!EmptyQueue(main_q, MTAIL, MHEAD))	
					{
						element = Dequeue(main_q, &MHEAD);
						Enqueue(temp, element, &TTAIL); 
					}
					
					// And temp queue will then be emptied out, with all elements being returned back to main queue,
					// in the correct order.
					while (!EmptyQueue(temp, TTAIL, THEAD))
					{
						element = Dequeue(temp, &THEAD); 
						Enqueue(main_q, element, &MTAIL);
					}			
												
					*mhead = MHEAD;
					*mtail = MTAIL;
					
					if (c == 'Y' || c == 'y')
						printf("\n Information deleted successfully!\n\n");
					else if (c == 'N' || c == 'n')
						printf("\n Information not deleted. Returning to main menu.\n\n");
						
					proceed();
					return;
				}
				
				else
					Enqueue(temp, element, &TTAIL);
			}
			
			// If the main queue gets emptied out trying to look for fn & ln but it doesn't exist, 
			// we put everything back from temp queue back into the main queue.
			
			while (!EmptyQueue(temp, TTAIL, THEAD))
			{
				element = Dequeue(temp, &THEAD); 
				Enqueue(main_q, element, &MTAIL);
			}	
			
			*mhead = MHEAD;
			*mtail = MTAIL;
			
			// * If the element is not existing, output an error message.		
			printf("\n This information does not exist.\n\n");
		}
	}
	
	proceed();
	return;
}

void DisplayQueue(QUEUE main_q[size], int *mhead, int *mtail, bool *chk)
{
	QUEUE element, temp[size];
	int MHEAD = *mhead, MTAIL = *mtail;		//main queue
	int TTAIL = -1, THEAD = 0; 				//temp queue
	bool chkr = *chk;
	
	// Check if the queue has been created.
	
	if (chkr == false) 	// (a) If not created: output an error message telling the user to create the queue.
		printf("\n The queue has not been created. Please create one first.\n\n");
	
	else 				// (b) If created, check if the queue is empty.
	{
		if (EmptyQueue(main_q, MTAIL, MHEAD)) 	// (i.) If it is empty, output an error message.
			printf("\n The queue is empty! Please insert at least one element inside it.\n\n");
			
		else									// (ii.) if not empty:
		{
			system("cls");
			printf("\t ================\n");
			printf("\t    DISPLAY ALL\n");
			printf("\t ================\n\n");
			
												
			while (!EmptyQueue(main_q, MTAIL, MHEAD))		// While the main queue is not empty:
			{
				element = Dequeue(main_q, &MHEAD); 			// pop topmost element;
				display(element); 							// display it on screen;
				Enqueue(temp, element, &TTAIL); 			// store it in a temporary queue.				
			}
			
			// Returning the elements from the temporary queue to the original queue in the proper sequence:
			while (!EmptyQueue(temp, TTAIL, THEAD))
			{
				element = Dequeue(temp, &THEAD); 
				Enqueue(main_q, element, &MTAIL);
			}
			
			printf(" All information displayed!\n\n");
			
		}
	}
	
	*mhead = MHEAD;
	*mtail = MTAIL;
	proceed();
	return;
}

void Enqueue(QUEUE queue[size], QUEUE element, int *tail)
{	
	int TAIL = *tail;
	
	TAIL = (TAIL + 1) % size;		// Updating the value of tail.
			
	queue[TAIL] = element;			// Adding the value of element inside the tail's index.
	*tail = TAIL; 					// Returning the value of tail.
	
	return;
}

QUEUE Dequeue(QUEUE queue[size], int *head)
{
	int HEAD = *head;
			
	QUEUE element = queue[HEAD]; 	// Taking the value of the content inside head's index and storing it in "element".

	strcpy(queue[HEAD].first, " ");	// Clearing out the contents...
	strcpy(queue[HEAD].last, " ");
	queue[HEAD].heightcm = 0.00;
	queue[HEAD].weightlb = 0.00;
	
	HEAD = (HEAD + 1) % size;		// Updating the value of head.
	
	*head = HEAD; 					// Returning the value of head.
	return element;					// Returning element.
}

bool FullQueue(QUEUE queue[size], int tail, int head)
{
	if ((tail != -1 && (tail + 1) % size == head) && (strcmpi(queue[tail].first, " ") != 0))
		return true;
	else
		return false;
}

bool EmptyQueue(QUEUE queue[size], int tail, int head)
{
	if (tail == -1 || (tail + 1) % size == head && (strcmpi(queue[tail].first, " ") == 0))
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

void display(QUEUE element) 
{
	char fn[strsize], ln[strsize], c;
	float height_m, weight_kg, BMI;

	strcpy(fn, element.first);
	strcpy(ln, element.last);
	printf(" Name: %s %s\n", fn, ln);
	
	height_m = element.heightcm/100;					
	printf(" Height: %.2f meters\n", height_m);
	
	weight_kg = element.weightlb * 0.45359237;
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
