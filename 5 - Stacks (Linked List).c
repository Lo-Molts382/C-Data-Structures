// Name: Lanz Alexander Malto
// Date Created: October 3, 2023
// Date Finished: October 12, 2023
/* Summary of the problem: The program shall take the user's input on a particular number of 
people's height and weight information to determine their BMI and BMI classification, one at a time. 
Taking elements to display, edit, or delete will follow the concept/format of STACKS using 
elements in a linked list format, and utilizing standard functions based on stacks.*/

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <stdbool.h>
#define strsize 40

typedef struct stck *nodeptr;
typedef struct stck
{
	char first[strsize];
	char last[strsize];
	float heightcm;
	float weightlb;
	nodeptr next; //internal pointer
} STCK;

//function prototypes
int menu(void);

//prototypes of the program's main features 
void CreateStack(nodeptr *STACK, nodeptr *TOP, bool *CHK);
void AddToStack(nodeptr *STACK, nodeptr *TOP, bool CHKR);
void SearchandEdit(nodeptr *STACK, nodeptr *TEMP, nodeptr *MTOP, nodeptr *TTOP, bool CHKR);
void SearchandDelete(nodeptr *STACK, nodeptr *TEMP, nodeptr *MTOP, nodeptr *TTOP, bool CHKR);
void DisplayTop(nodeptr STACK, nodeptr *TOP, bool CHK);
void DisplayStack(nodeptr *STACK, nodeptr *TEMP, nodeptr *MTOP, nodeptr *TTOP, bool CHKR);

//prototypes of stack-based functions 
void Push(nodeptr *STACK, nodeptr *ELEMENT, nodeptr *TOP);
nodeptr Pop(nodeptr *STACK, nodeptr *TOP);
nodeptr Peek(nodeptr STACK, nodeptr TOP);
bool isEmpty(nodeptr STK);

//prototypes of other functions
void proceed(void);
void display(nodeptr ELEMENT);

int main(void)
{
	int pick;
	nodeptr STACK = NULL, TEMP = NULL, MTOP = NULL, TTOP = NULL;
	STCK element; 
	bool CHK = false; 
	
	do {
		pick = menu();
	
		switch (pick)
		{
			//create stack
			case 1: CreateStack(&STACK, &MTOP, &CHK);
					break;
			//add element into the stack
			case 2: AddToStack(&STACK, &MTOP, CHK);
					break;
			//search and edit the contents of an element
			case 3: SearchandEdit(&STACK, &TEMP, &MTOP, &TTOP, CHK);
					break;
			//search and delete element from the stack
			case 4: SearchandDelete(&STACK, &TEMP, &MTOP, &TTOP, CHK);
					break;
			//take a peek at the top of the stack
			case 5: DisplayTop(STACK, &MTOP, CHK);
					break;
			//display all the elements in the stack
			case 6: DisplayStack(&STACK, &TEMP, &MTOP, &TTOP, CHK);
					break;
			//exit program
			case 7: printf("\n Press any key to continue... ");
					getch();
					exit(0);
		}
	
 	} while (pick != 7); 
	
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
		
		printf(" 1. Create Stack");
		printf("\n 2. Add to Stack");
		printf("\n 3. Search and Edit");
		printf("\n 4. Search and Delete");
		printf("\n 5. Peek at the Top");
		printf("\n 6. Display All Stack Elements");
		printf("\n 7. Exit the Program");
		
		printf("\n\n Pick a choice (1-7): ");
		scanf("%d", &choice);
		
		if (choice < 1 || choice > 7)
		{
			printf("\n Error in choice! Please pick a number from 1 to 7.\n\n");
			proceed();
		}
				
	} while (choice < 1 || choice > 7); // trapping for invalid menu choice.
	
	return choice;
}

void CreateStack(nodeptr *STACK, nodeptr *MTOP, bool *CHK)
{
	nodeptr s = *STACK, t = *MTOP;
	bool c = *CHK;
	char choice;
	
	if (c == true && !isEmpty(t)) // If stack has elements inside...
	{
		printf("\n The stack already has elements!\n\n"); //...warn the user...
		
		do { 
			//...and ask for confirmation if he/she wants to continue deleting the existing elements.
			printf(" Would you like to continue initiating this function and empty out the stack's contents (Y/N)? ");
			scanf(" %c", &choice); 
			
			if (choice == 'Y' || choice == 'y')
				break;
			
			else if (choice == 'N' || choice == 'n')
			{
				printf("\n The overwriting of the stack has been cancelled.\n\n");
				proceed();
				return;
			}
			
			else 
				printf("\n Error in choice! Please try again.\n\n");
				
		} while (choice != 'Y' && choice != 'y' && choice != 'N' && choice != 'n');
	}
	
	s = NULL;	
	*STACK = s;
	t = s;
	*MTOP = t;
	c = true; 
	*CHK = c;
	
	printf("\n Stack has been initialized!\n\n");
	proceed();
	return;
}

void AddToStack(nodeptr *STACK, nodeptr *TOP, bool CHKR)
{
	nodeptr stk = *STACK, t = *TOP;
	nodeptr element = (nodeptr) malloc(sizeof(STCK)); 
	bool c = CHKR;
	//structure elements 
	char fnam[strsize], lnam[strsize]; 
	float height, weight;
	
	//Make sure that the stack has been created. Output an error message if it was not.	
	if (c == false) 
		printf("\n The stack has not been created. Please create one first.\n\n");

	//In this implementation, the programmer chose to insert at the end of the linked-list.
	else
	{
		system("cls");
		printf("\t ================\n");
		printf("\t   ADD TO STACK\n");
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
		
		Push(&stk, &element, &t); //the newly-created element block will be the topmost one in the stack (i.e., end of the linked list).
		
		*STACK = stk;
		*TOP = t;
		
		printf("\n Information recorded! This element block has been added to the stack.\n\n");
	}		
		
	proceed();	
}

void SearchandEdit(nodeptr *STACK, nodeptr *TEMP, nodeptr *MTOP, nodeptr *TTOP, bool CHKR)
{
	nodeptr s = *STACK, t = *TEMP, mt = *MTOP, tt = *TTOP;
	nodeptr element = (nodeptr) malloc(sizeof(STCK));
	bool ch = CHKR, exist = false;
	char c, fn[strsize], ln[strsize];
	float height, weight;
	
	//Make sure that the stack has been created. Output an error message if it was not.	
	if (ch == false)
		printf("\n The stack has not been created. Please create one first.\n\n");

	else //If the stack was created...
	{
		if (isEmpty(mt)) //...check for an empty stack. Output an error message if the stack is empty.
			printf("\n The stack is empty! Please insert at least one element inside it.\n\n");
		
		else
		{
			system("cls");
			printf("\t ===================\n");
			printf("\t   SEARCH AND EDIT\n");
			printf("\t ===================\n");
			
			/*Search the non-empty stack for the element the user wishes to edit using first name
			and last name.*/
			printf("\n Enter first name: " );
			fflush(stdin); 
			gets(fn);
		
			printf("\n Enter last name: " );
			fflush(stdin); 
			gets(ln); 
			
			while (!isEmpty(mt))
			{
				element = Pop(&s, &mt);
				
				if ((strcmpi(element -> first, fn) == 0) && (strcmpi(element -> last, ln) == 0)) //If the element exists...
				{	
					exist = true;
					printf("\n Record found! Displaying: \n\n");
					display(element); //...show the contents on the screen...
										
					do {
						//...and output a confirmation message before editing the element's contents.
						printf(" Continue with editing (y/n)? ");
						scanf(" %c", &c);
						
						if (c == 'Y' || c == 'y')
							break;
													
						else if (c == 'N' || c == 'n')
						{
							printf("\n Information not edited. Returning to main menu.\n\n");
							proceed();
							Push(&s, &element, &mt); 
							
							while (!isEmpty(tt)) //Utilizing a temp stack to move elements to/from the original stack.
							{
								element = Pop(&t, &tt); 
								Push(&s, &element, &mt); 
							}
							
							return;
						}
						
						else
							printf("\n Error in choice! Please try again.");
							
					} while (c != 'Y' && c != 'y' && c != 'N' && c != 'n');
					
					//Allow editing only on the height and weight.
					
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
						
					Push(&s, &element, &mt);
					
					//Informational messaage that element was successfully edited.
					printf("\n Information updated successfully!\n\n"); 
					break;
				}
				
				//Utilizing a temp stack to move elements to/from the original stack.
				else
					Push(&t, &element, &tt);
			}
	
			/*If main stack gets emptied out because the element blocks were exhausted trying to 
			look for fn & ln, but it doesn't exist, put everything back in main stack.*/
			
			while (!isEmpty(tt))
			{
				element = Pop(&t, &tt); 
				Push(&s, &element, &mt); 
			}
			
			if (!exist) //If the element does not exist, output an error message.
				printf("\n This information does not exist.\n\n");
		}
	}
	
	*STACK = s;
	*TEMP = t; 
	*MTOP = mt; 
	*TTOP = tt;
	
	proceed();
}

void SearchandDelete(nodeptr *STACK, nodeptr *TEMP, nodeptr *MTOP, nodeptr *TTOP, bool CHKR)
{
	nodeptr s = *STACK, t = *TEMP, mt = *MTOP, tt = *TTOP, run = s;
	nodeptr element = (nodeptr) malloc(sizeof(STCK));
	bool ch = CHKR, exist = false;
	char c, fn[strsize], ln[strsize];
	float height, weight;
	
	//Make sure that the stack has been created. Output an error message if it was not.	
	if (ch == false)
		printf("\n The stack has not been created. Please create one first.\n\n");

	else //If the stack was created...
	{
		if (isEmpty(mt)) //...check for an empty stack. Output an error message if the stack is empty.
			printf("\n The stack is empty! Please insert at least one element inside it.\n\n");
		
		else
		{
			system("cls");
			printf("\t =====================\n");
			printf("\t   SEARCH AND DELETE\n");
			printf("\t =====================\n");
			
			printf("\n Enter first name: " );
			fflush(stdin); 
			gets(fn);
		
			printf("\n Enter last name: " );
			fflush(stdin); 
			gets(ln); 
			
			while (!isEmpty(mt))
			{
				element = Pop(&s, &mt);
				
				if ((strcmpi(element -> first, fn) == 0) && (strcmpi(element -> last, ln) == 0)) //If the element exists...
				{	
					printf("\n Record found! Displaying: \n\n");
					display(element); //...show the contents on the screen...
					
					do {
						printf(" Continue with deleting (y/n)? ");
						scanf(" %c", &c);
						
						if (c == 'Y' || c == 'y') 
						{
							printf("\n Element deleted!\n\n"); 
							break;
						}
						
						else if (c == 'N' || c == 'n')
						{
							printf("\n Information not deleted. Returning to main menu.\n\n");
							proceed();
							Push(&s, &element, &mt);
							
							while (!isEmpty(tt)) //Utilizing a temp stack to move elements to/from the original stack.
							{
								element = Pop(&t, &tt); 
								Push(&s, &element, &mt); 
							}
							
							return;
						}
						
						else
							printf("\n Error in choice! Please try again.");
							
					} while (c != 'Y' && c != 'y' && c != 'N' && c != 'n');
				}
				
				//Utilizing a temp stack to move elements to/from the original stack.
				else
					Push(&t, &element, &tt);
			}
	
			/*If the main stack gets emptied out because the element blocks were 
			exhausted trying to look for fn & ln, but it doesn't exist, 
			put everything back in main stack.*/
			
			while (!isEmpty(tt))
			{
				element = Pop(&t, &tt); 
				Push(&s, &element, &mt); 
			}
			
			if (!exist) //If the element does not exist, output an error message.
				printf("\n This information does not exist.\n\n");
		}
	}
	
	*STACK = s;
	*TEMP = t; 
	*MTOP = mt; 
	*TTOP = tt;
	
	proceed();
}

void DisplayTop(nodeptr STACK, nodeptr *TOP, bool CHK)
{
	nodeptr s = STACK, t = *TOP, elmt; 

	char fn[strsize], ln[strsize];
	float height_m, weight_kg, BMI;
	
	if (CHK == false) 
		printf("\n The stack has not been created. Please create one first.\n\n");
	
	else 
	{
		if (isEmpty(t)) 
			printf("\n The stack is empty! Please insert at least one element inside it.\n\n");
		
		else 
		{
			system("cls");
			printf("\t ============\n");
			printf("\t   PEEK TOP\n");
			printf("\t ============\n");
			
			// Return the data of the topmost element, but do not delete it from the stack.
			printf("\n Displaying the information of the topmost element in the stack:\n\n");
			elmt = Peek(s, t); // Utilizing the Peek() function.
			display(elmt); 	// Display the contents of the returned element.
		}
	}

	proceed();
	return;
}

void DisplayStack(nodeptr *STACK, nodeptr *TEMP, nodeptr *MTOP, nodeptr *TTOP, bool CHKR)
{
	nodeptr ms = *STACK, ts = *TEMP, mt = *MTOP, tt = *TTOP;
	nodeptr run = ms, element;
	bool c = CHKR;
	
	if (c == false) 
		printf("\n The stack has not been created. Please create one first.\n\n");
	
	else
	{
		if (isEmpty(mt)) 
			printf("\n The stack is empty! Please insert at least one element inside it.\n\n");
			
		else
		{
			system("cls");
			printf("\t ================\n");
			printf("\t    DISPLAY ALL\n");
			printf("\t ================\n\n");
			
			//Pop from main stack -> display the element -> push to temp stack.
			while (!isEmpty(mt))
			{
				element = Pop(&ms, &mt);
				display(element);
				Push(&ts, &element, &tt);
			}
			
			//Pop from temp stack -> return to main stack after displaying.			
			while (!isEmpty(tt))
			{
				element = Pop(&ts, &tt);
				Push(&ms, &element, &mt);
			}
			
			printf(" All information displayed!\n\n");
		}
	}
	
	*STACK = ms;
	*MTOP = mt;
	*TEMP = ts;
	*TTOP = tt;
	
	proceed();
	return;
}

void Push(nodeptr *STACK, nodeptr *ELEMENT, nodeptr *TOP)
{
	nodeptr run, s = *STACK, t = *TOP, e = *ELEMENT;
	
	if (s == NULL)
	{
		s = e;
		t = e;
	}
	
	else
	{
		run = s;
		
		while (run -> next != NULL)
			run = run -> next;
			
		run -> next = e;
		t = run -> next;
	}
	
	*STACK = s;
	*TOP = t;
	*ELEMENT = e;
}

nodeptr Pop(nodeptr *STACK, nodeptr *TOP)
{
	nodeptr s = *STACK, t = *TOP, run = s, e = *TOP;
	
	if (run != t)
		while (run -> next != t)
			run = run -> next;	
	
	run -> next = NULL;

	//updating top
	if (run != t)
		t = run;
	else 
	{
		s = NULL;
		t = s;
	}
	
	*STACK = s;
	*TOP = t;
	
	return e; 
}

nodeptr Peek(nodeptr STACK, nodeptr TOP)
{
	nodeptr element = STACK;
	
	while (element != TOP)
		element = element -> next;
	
	return element;	
}

bool isEmpty(nodeptr TOP)
{
	if (TOP == NULL)
		return true;
	else
		return false;
}

void proceed(void)
{
	printf(" Press any key to continue... ");
	getch();
	system("cls");
}

void display(nodeptr ELEMENT)
{
	nodeptr elmnt = ELEMENT;
	char fn[strsize], ln[strsize], c;
	float height_m, weight_kg, BMI;

	strcpy(fn, elmnt -> first);
	strcpy(ln, elmnt -> last);
	printf(" Name: %s %s\n", fn, ln);
	
	height_m = elmnt -> heightcm/100;					
	printf(" Height: %.2f meters\n", height_m);
	
	weight_kg = elmnt -> weightlb * 0.45359237;
	printf(" Weight: %.2f kilograms\n", weight_kg);
	
	printf(" Classification: ");
	
	BMI = weight_kg/(height_m * height_m);
	if (BMI < 18.5)
		printf("Underweight\n\n");
	else if (BMI >= 18.5 && BMI <= 24.9)
		printf("Normal weight\n\n");
	else if (BMI >= 25 && BMI <= 29.9)
		printf("Overweight\n\n");
	else if (BMI >= 30)
		printf("Obese\n\n");
}


