// Name: Lanz Alexander Malto
// Date Created: September 22, 2023
// Date Finished: September 28, 2023
/* Summary of the problem: The program shall take the user's input on a particular number of 
people's height and weight information to determine their BMI and BMI classification, one at a time. 
Taking elements to display, edit, or delete will follow the concept/format of STACKS, utilizing standard 
functions based on this data structure.*/

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <stdbool.h>
#define size 10
#define strsize 40

typedef struct stck
{
	char first[strsize];
	char last[strsize];
	float heightcm;
	float weightlb;
} STCK;

//function prototypes
int menu(void);
//prototypes of the program's main features 
void CreateStack(STCK stack[size], int *top, bool *chk);
void AddToStack(STCK stack[size], int *top, bool *chk);
void SearchandEdit(STCK stack[size], STCK temp[size], int *maintop, int *temptop, bool *chk);
void SearchandDelete(STCK stack[size], STCK temp[size], int *maintop, int *temptop, bool *chk);
void DisplayStack(STCK stack[size], STCK temp[size], int *maintop, int *temptop, bool *chk);
void DisplayTop(STCK stack[size], int *maintop, bool *chk);
//prototypes of stack-based functions 
void Push(STCK s[size], STCK element, int *top);
STCK Pop(STCK s[size], STCK element, int *top);
bool isFull(int top);
bool isEmpty(int top);
STCK Peek(STCK s[size], int top);
//prototypes of other functions
void proceed(void);
void display(STCK element);

int main(void)
{
	int pick;
	STCK stack[size], temp[size]; 
	STCK element; 
	int maintop = -1, temptop = -1; 
	bool chk = false; 
	
	do {
		pick = menu();
	
		switch (pick)
		{
			//create stack
			case 1: CreateStack(stack, &maintop, &chk);
					break;
			//add element into the stack
			case 2: AddToStack(stack, &maintop, &chk);
					break;
			//search and edit the contents of an element
			case 3: SearchandEdit(stack, temp, &maintop, &temptop, &chk);
					break;
			//search and delete element from the stack
			case 4: SearchandDelete(stack, temp, &maintop, &temptop, &chk);
					break;
			//take a peek at the top of the stack
			case 5: DisplayTop(stack, &maintop, &chk);
					break;
			//display all the elements in the stack
			case 6: DisplayStack(stack, temp, &maintop, &temptop, &chk);
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

void CreateStack(STCK stack[size], int *top, bool *chk) //(a) pass the stack and top as parameters
{
	int i, t = *top;
	bool chkr = *chk;
	char c;
	
	if (!isEmpty(t)) //If the stack has elements inside...
	{
		printf("\n The stack already has elements!\n\n"); //warn the user...
		//and ask for confirmation if they want to continue deleting the existing elements.
		do { 			
			printf(" Would you like to continue initiating this function and empty out the stack's contents (Y/N)? ");
			scanf(" %c", &c);
			
			if (c == 'Y' || c == 'y')
			{
				for (i = 0; i < size; i++) // (b) initialize the contents of the array
				{
					strcpy(stack[i].first, " ");
					strcpy(stack[i].last, " ");
					stack[i].heightcm = 0.00;
					stack[i].weightlb = 0.00;	
				}
				
				printf("\n The stack has been overwritten!\n\n");
			}
							
			else if (c == 'N' || c == 'n')
			{
				printf("\n The overwriting of the stack has been cancelled.\n\n");
				proceed();
				return;
			}
			
			else 
				printf("\n Error in choice! Please try again.\n\n");
			
		} while (c != 'Y' && c != 'y' && c != 'N' && c != 'n');
	}
	
	else 
	{
		for (i = 0; i < size; i++) // (b) initialize the contents of the array
		{
			strcpy(stack[i].first, " ");
			strcpy(stack[i].last, " ");
			stack[i].heightcm = 0.00;
			stack[i].weightlb = 0.00;	
		}
		
		printf("\n The stack has been created!\n\n");		
	}
	
	t = -1; 
	*top = t; // (d) also, assign a -1 to top and return its value to a calling function.
	chkr = true;
	*chk = chkr; // (c) return true once the array has been initialized.
	
	proceed();
	return;	
	
}

void AddToStack(STCK stack[size], int *top, bool *chk)
{
	int i, TOP = *top, val;
	STCK element;
	bool chkr = *chk;
	//structure elements
	char fnam[strsize], lnam[strsize];
	float height, weight;
	
	// check if the stack has been created. 
	if (chkr == false) // (a) if not created: output an error message.
		printf("\n The stack has not been created. Please create one first.\n\n");
	
	else // (b) if created: 
	{
		if (isFull(TOP)) //check if the stack is full. Output an error message if it is full (i.)
			printf("\n The stack is full! No additional elements can be accomodated.\n\n");
		
		else 
		{
			system("cls");
			printf("\t ================\n");
			printf("\t   ADD TO STACK\n");
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
			
			Push(stack, element, &TOP); // (ii.) Add the new element on top of the stack if it is not full.
			
			*top = TOP;
			
			// (iii.) Output an informational message that a new element has been added to the stack.
			printf("\n Information recorded! This element block has been added to the stack.\n\n");			
		}
	}
	
	proceed();
	return;
}

void SearchandEdit(STCK stack[size], STCK temp[size], int *maintop, int *temptop, bool *chk)
{
	STCK element; 
	int MTOP = *maintop, TTOP = *temptop;
	bool chkr = *chk;
	//structure elements
	char fn[strsize], ln[strsize], c;
	float height, weight, height_m, weight_kg, BMI;
	
	// check if the stack has been created. 
	if (chkr == false)  // (a) if not created: output an error message.
		printf("\n The stack has not been created. Please create one first.\n\n");
	
	else // (b) if created: 
	{
		if (isEmpty(MTOP)) //check if the stack is empty. Ouptut an error message if it is empty (i.)
			printf("\n The stack is empty! Please insert at least one element inside it.\n\n");
		
		else //if not empty:
		{
			system("cls");
			printf("\t ===================\n");
			printf("\t   SEARCH AND EDIT\n");
			printf("\t ===================\n");
			
			printf("\n Enter first name: " );
			fflush(stdin); 
			gets(fn);
			strcpy(element.first, fn);
		
			printf("\n Enter last name: " );
			fflush(stdin); 
			gets(ln); 
			strcpy(element.last, ln);
			
			// (ii.) Search for the element in the stack.
			while (!isEmpty(MTOP))
			{
				// (iii.) Remove the element that you want to edit...
				element = Pop(stack, element, &MTOP);
				
				if ((strcmpi(element.first, fn) == 0) && (strcmpi(element.last, ln) == 0))
				{	
					/* If the element is existing, show the contents on screen and 
					output a confirmation message before editing the contents of the
					element. */
					printf("\n Record found! Displaying: \n\n");
					display(element);					
					
					do {
						
						printf(" Continue with editing (y/n)? ");
						scanf(" %c", &c);
						
						if (c == 'Y' || c == 'y')
							break;
							
						else if (c == 'N' || c == 'n')
						{
							printf("\n Information not edited. Returning to main menu.\n\n");
							proceed();
							return;
						}
						
						else
							printf("\n Error in choice! Please try again.");
							
					} while (c != 'Y' && c != 'y' && c != 'N' && c != 'n');
					
					//...and modify the contents...
						//allow editing only on the height and weight.
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
					
					//...before returning it back to the original stack.
					Push(stack, element, &MTOP); 
					
					// (iv.) Return the elements from the temp stack to the original stack.
					while (!isEmpty(TTOP))
					{
						element = Pop(temp, element, &TTOP);
						Push(stack, element, &MTOP);
					}
					
					printf("\n Information updated successfully!\n\n");
					proceed();
					return;
				}
				
				// * If current element block is not a match, load the block to the temp stack.
				else
					Push(temp, element, &TTOP);	
			}
			
			/*if the main stack gets emptied out because the element blocks were 
			exhausted trying to look for fn & ln, put everything back in main stack.*/
			
			while (!isEmpty(TTOP))
			{
				element = Pop(temp, element, &TTOP); 
				Push(stack, element, &MTOP); 
			}
			
			// * If the element is not existing, output an error message.
			printf("\n This information does not exist.\n\n");
			proceed();
			return;
		}
	}

		proceed();
		return;
}

void SearchandDelete(STCK stack[size], STCK temp[size], int *maintop, int *temptop, bool *chk)
{
	STCK element; 
	int MTOP = *maintop, TTOP = *temptop;
	bool chkr = *chk;
	//structure elements
	char fn[strsize], ln[strsize], c;
	float height, weight, height_m, weight_kg, BMI;
	
	// * Check if the stack has been created.
	if (chkr == false) // (a) if not created: output an error message.
		printf("\n The stack has not been created. Please create one first.\n\n");
	
	else // (b) if created: 
	{
		if (isEmpty(MTOP)) //check if the stack is empty. Ouptut an error message if it is empty (i.)
			printf("\n The stack is empty! Please insert at least one element inside it.\n\n");

		else //if not empty:
		{
			system("cls");
			printf("\t =====================\n");
			printf("\t   SEARCH AND DELETE\n");
			printf("\t =====================\n");
			
			printf("\n Enter first name: "); fflush(stdin);	gets(fn);
			printf("\n Enter last name: ");	fflush(stdin); gets(ln);
			
			//(ii.) do the same searching process as in search and edit function.
			while (!isEmpty(MTOP))
			{
				// (iii.) Remove the element that you want to delete.
				element = Pop(stack, element, &MTOP);
				
				if ((strcmpi(element.first, fn) == 0) && (strcmpi(element.last, ln) == 0))
				{
					/* If the element is existing, show the contents on screen and 
					output a confirmation message before deleting the element
					from the stack. */
					printf("\n Record found! Displaying: \n\n");
					display(element);
										
					do {
						
						printf(" Continue with deleting (y/n)? ");
						scanf(" %c", &c);
						
						if (c == 'Y' || c == 'y')
							break;
							
						else if (c == 'N' || c == 'n')
						{
							
							printf("\n Information not deleted. Returning to main menu.\n\n");
							proceed();
							return;
						}
						
						else
							printf("\n Error in choice! Please try again.");
							
					} while (c != 'Y' && c != 'y' && c != 'N' && c != 'n');
					
					// (iv.) Return the elements from the temp stack to the original stack.
					while (!isEmpty(TTOP)) 
					{
						element = Pop(temp, element, &TTOP);
						Push(stack, element, &MTOP);
					}
					
					*maintop = MTOP;
					*temptop = TTOP;
					
					printf("\n Element deleted!");
					proceed();
					return;
				}
				
				else
					Push(temp, element, &TTOP);	
			}
			
			/*if the main stack gets emptied out because the element blocks were 
			exhausted trying to look for fn & ln, put everything back in main stack.*/
			
			while (!isEmpty(TTOP))
			{
				element = Pop(temp, element, &TTOP); //pop from temp
				Push(stack, element, &MTOP); //return to main
			}
			
			// * If the element is not existing, output an error message.		
			printf("\n This information does not exist.\n\n");
			proceed();
			return;
		}
	}

	proceed();
	return;
}

void DisplayTop(STCK stack[size], int *maintop, bool *chk)
{
	int MTOP = *maintop;
	STCK element = stack[MTOP]; // (1)
	bool chkr = *chk;
	//structure elements
	char fn[strsize], ln[strsize];
	float height_m, weight_kg, BMI;
	
	if (chkr == false) //if stack has not been created yet...
		printf("\n The stack has not been created. Please create one first.\n\n");
	
	else //if the stack has been created...
	{
		//check if the stack is empty.
		if (isEmpty(MTOP)) 	
			printf("\n The stack is empty! Please insert at least one element inside it.\n\n");
		
		else //if not empty:
		{
			system("cls");
			printf("\t ============\n");
			printf("\t   PEEK TOP\n");
			printf("\t ============\n");
			
			/* (a), (b). Return the data of topmost element (1) but do not delete from the stack. 
			Display the contents of the element.*/
			printf("\n Displaying the information of the topmost element in the stack:\n\n");
			element = Peek(stack, MTOP);
			display(element); 	
		}
	}

	proceed();
	return;
}

STCK Peek(STCK s[size], int top)
{
	int t = top;
	return s[t];
}


void DisplayStack(STCK stack[size], STCK temp[size], int *maintop, int *temptop, bool *chk)
{
	STCK element;
	int MTOP = *maintop, TTOP = *temptop;
	bool chkr = *chk;
	
	if (chkr == false) //if stack has not been created yet...
		printf("\n The stack has not been created. Please create one first.\n\n");
	
	else //if the stack has been created...
	{
		//check if the stack is empty.
		if (isEmpty(MTOP)) 
			printf("\n The stack is empty! Please insert at least one element inside it.\n\n");
			
		else
		{
			system("cls");
			printf("\t ================\n");
			printf("\t    DISPLAY ALL\n");
			printf("\t ================\n\n");
			
			//...place the following in a loop until the main stack is empty.
			while (!isEmpty(MTOP))
			{
				element = Pop(stack, element, &MTOP); // (a) pop topmost element;
				display(element); // (b) display it on screen;
				Push(temp, element, &TTOP); // (c) store it in a temporary stack.
			}
			
			/* After displaying all the elements, return them back to the original
			stack. */
			
			while (!isEmpty(TTOP))
			{
				element = Pop(temp, element, &TTOP);
				Push(stack, element, &MTOP);
			}
			
			printf(" All information displayed!\n\n");
			
		}
	}
	
	proceed();
	return;
}

void Push(STCK s[size], STCK element, int *top)
{
	int TOP = *top; 
	TOP++; //moves top 1 value up (top is updated).
	s[TOP] = element; //plugging the current element block inside the top.
	*top = TOP;	//returning the new value of top.
}

STCK Pop(STCK s[size], STCK element, int *top)
{
	int TOP = *top;	
	element = s[TOP]; //assigns element to be the topmost block that was just popped out.	
	TOP--; //decrements top by 1 to highlight the new topmost block in the main stack.
	*top = TOP;
	return element; //returns element block (with information now!) to the calling body.
}

bool isFull(int TOP)
{
	if (TOP == size - 1)
		return true;
	else
		return false;
}

bool isEmpty(int TOP)
{
	if (TOP == -1)
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

void display(STCK element)
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



