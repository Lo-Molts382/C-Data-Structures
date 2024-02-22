// Name: Lanz Alexander Malto
// Date Created: September 12, 2023
// Date Finished: September 15, 2023
/* Summary of the problem: This program is a conversion from the use of singly-linked list 
to the use of doubly-linked list in inputting/storing, searching for, and displaying
BMI records of persons. */

//pre-processing directives

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <windows.h>
#define strsize 40

//structure definitions

typedef struct Info *nodeptr;
struct Info
{
	nodeptr prev;
	char first[strsize];
	char last[strsize];
	float heightcm;
	float weightlb;
	nodeptr next; //internal pointer
} Node;

//function prototypes

void gotoxy(short x, short y);
int menu(void);
int input(nodeptr *head, int index);
int displayAll(nodeptr h, int index);
void searchBMI(nodeptr h);
void searchandedit(nodeptr *head);
void nodeprint(nodeptr p);
int searchanddelete(nodeptr *head, int index);
void proceed(void);


//gotoxy() function definition

void gotoxy(short x, short y)
{
	COORD pos = {x, y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

//main function

int main(void)
{
	nodeptr head;
	int pick, num, index = 0;
	head = NULL; //external pointer
	
	do {
		pick = menu();
	
		switch (pick)
		{
			case 1: index = input(&head, index); //add record
					break;
			case 2: searchBMI(head); //search and display
					proceed();
					break;
			case 3: searchandedit(&head); //search and edit
					proceed();
					break;
			case 4: index = searchanddelete(&head, index); //search and delete
					break;
			case 5: index = displayAll(head, index); //display all records
					break; 
			case 6: printf("\n Press any key to continue... "); //exit fxn
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
		
		printf(" 1. Add Record");
		printf("\n 2. Search for a Record");
		printf("\n 3. Search and Edit a Record");
		printf("\n 4. Search and Delete a Record");
		printf("\n 5. Display All Records");
		printf("\n 6. Exit Program");
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

int input(nodeptr *head, int index)
{
	char fnam[strsize], lnam[strsize];
	float height, weight;
	nodeptr h, temp, p;
	
	h = *head;
	
	system("cls");
	
	temp = (nodeptr) malloc(sizeof(Node));
	temp -> prev = NULL;
	
	do {
			
		p = h;
		
		printf("\t==============\n");
		printf("\t   PERSON %d", index + 1); // for appropriate numbering of the data, we shall start at PERSON 1 (index [which is 0] + 1).
		printf("\n\t==============\n\n");
		
		printf(" Enter first name of person %d: ", index + 1);
		fflush(stdin); 
		gets(fnam);
		strcpy(temp -> first, fnam); 
					
		printf("\n Enter last name of person %d: ", index + 1);
		fflush(stdin); 
		gets(lnam);
		strcpy(temp -> last, lnam);
	
		while (p != NULL)
		{
			if ((strcmpi(p -> first, temp -> first) == 0) && (strcmpi(p -> last, temp -> last) == 0))
			{
				printf("\n Sorry! This record already exists. Please try again.\n\n");
				proceed();
				return index;
			}
			
			p = p -> next;
		}	
		
		break;
		
	} while ((strcmpi(p -> first, fnam) == 0) && (strcmpi(p -> last, lnam) == 0));
	
	do {
		
		printf("\n Enter person %d's height (in centimeters): ", index + 1);
		scanf("%f", &height); // takes height input in cm.
		
		if (height < 1)
			printf("\n Invalid value. Please try again.\n"); // trapping for negative integer input by user.
		
	} while (height < 1);
	
	temp -> heightcm = height;
	
	do {
		
		printf("\n Enter person %d's weight (in pounds): ", index + 1);
		scanf("%f", &weight); // takes weight input in lbs.
		
		if (weight < 1)
			printf("\n Invalid value. Please try again.\n"); // trapping for negative integer input by user.
		
	} while (weight < 1);
		
	temp -> weightlb = weight; 
	
	temp -> next = NULL;
	
	if (h == NULL) // first node
	{
		h = temp;
		*head = h;
	}
	
	else // not the first node
	{
		p = h;
		
		// find the last node
		while (p -> next != NULL)
			p = p -> next;
		
		//insert after the last node
		p -> next = temp;
		temp -> prev = p;
		*head = h;
	}
			
	printf("\n Information recorded!");
	proceed();
	
	index++; // adding 1 to our index for UI if the user will want to input again.
	
	return index;
}

int displayAll(nodeptr h, int index)
{
	int y, row, col, dispch;
	float height, weight, BMI;
	nodeptr p;

	if (h == NULL) //if the list is empty...
	{
		printf("\n Sorry! The list is empty. There are no records to display.");
		printf("\n\n You are required to pick a different option.");
		proceed();
		
		return index;
	} 
	
	//if the list is not empty...
	
	do {
		system("cls");
		printf("\n\n Display from first node to last node, or last node to first node?\n\n");
		printf("\t 1. First to Last\n");
		printf("\t 2. Last to First\n\n");
		printf(" Choice: ");
		scanf("%d", &dispch);
		
		if (dispch < 1 || dispch > 2)
		{
			printf("\n Error in input! Please try again. \n\n");
			proceed();
		}
			
	} while (dispch < 1 || dispch > 2);	
	
	if (dispch == 1) //if first-to-last: set p = h for printing later.
		p = h;
		
	else if (dispch == 2) //else if last-to-first: find last node to print backwards later.
	{
		p = h;
		while (p -> next != NULL)
			p = p -> next;	
	}	
	
	
	system("cls");
	
	printf("\t=============\n");
	printf("\t   DISPLAY");
	printf("\n\t=============\n\n");
	
	//row headings
	gotoxy(0, 4);
	printf(" First Name");
	gotoxy(20, 4);
	printf("\t Last Name");
	gotoxy(35, 4);
	printf("\t Height (m)");
	gotoxy(50, 4);
	printf("\t Weight (kgs)");
	gotoxy(65, 4);
	printf("\t BMI");
	gotoxy(75, 4);
	printf("\t BMI Classification");
	
	printf("\n");
	
	y = 6;
	// row
	for (row = 0; row < index; row++)
	{
		// column
		col = 0; 
		while (col < 6)
		{
			switch (col)
		 	{
		 		case 0: gotoxy(0, y);
						printf(" %s", p -> first);
						break;
				case 1: gotoxy(24, y);
						printf(" %s", p -> last);
						break;
				case 2: gotoxy(40, y);
						height = p -> heightcm;
						printf(" %.2f", height / 100); // height conversion from cm to m.
						break;
				case 3: gotoxy(56, y);
						weight = p -> weightlb;
						printf(" %.1f", weight * 0.45359237); // weight conversion from lbs to kg.
						break;
				case 4: BMI = ((weight * 0.45359237) / ((height / 100) * (height / 100))); //this line computes for the BMI.	
						gotoxy(72, y);
						printf(" %.1f", BMI);
						break;
				case 5: gotoxy(81, y);
						{
							if (BMI < 18.5)
								printf("Underweight");
							else if (BMI >= 18.5 && BMI <= 24.9)
								printf("Normal weight");
							else if (BMI >= 25 && BMI <= 29.9)
								printf("Overweight");
							else if (BMI >= 30)
								printf("Obese");
						} // this if-else statement allows us to match the person's BMI to their respective BMI classification.
						break;		
			}
			col++; 
		}
		if (dispch == 1 && p -> next != NULL)
			p = p -> next;
		else if (dispch == 2 && p -> prev != NULL)
			p = p -> prev;
		y++;
		printf("\n");
	}
	
	printf("\n\n");
	printf(" Current number of records: %d\n\n", index);	
	proceed();
	return index;
}

void searchBMI(nodeptr h)
{
	char fnam[strsize], lnam[strsize];
	nodeptr p, l_back, l_ahead;
	
	p = h;
	
	if (p == NULL)
	{
		printf("\n Sorry! The list is empty. There are no records to display.");
		printf("\n\n You are required to pick a different option.");
		return;
	}
	
	system("cls");
	
	printf("\t===================\n");
	printf("\t   SEARCH RECORD");
	printf("\n\t===================\n\n");
	
	//user input
	
	printf(" Please enter the person's first name: ");
	fflush(stdin); // this line is implemented to prevent problems in user string input.
	gets(fnam); // takes user input for FIRST NAME.
	
	printf("\n Please enter the person's last name: ");
	fflush(stdin); 
	gets(lnam); // takes user input for LAST NAME.
	
	while (p != NULL)
	{
		if ((strcmpi(p -> first, fnam) == 0) && (strcmpi(p -> last, lnam) == 0))
		{
			l_back = p;
			l_ahead = p;			

			system("cls");
		
			printf("\t==================\n");
			printf("\t   DISPLAY INFO");
			printf("\n\t==================\n\n");
			
				printf(" =================\n");
				printf("   PREVIOUS NODE");
				printf("\n =================\n\n");
				
				if (p -> prev == NULL)
					printf("\t No node detected.\n\n");	
				else
				{
					//printing last node...
					l_back = p -> prev;
					nodeprint(l_back);	
				}
				
				printf(" ================\n");
				printf("   CURRENT NODE");
				printf("\n ================\n\n");
				
				//printing current node...
				nodeprint(p);
				
				printf(" =============\n");
				printf("   NEXT NODE");
				printf("\n =============\n\n");
			
				if (p -> next == NULL)
					printf("\t No node detected.\n\n");	
				else
				{
					//printing next node...
					l_ahead = p -> next;
					nodeprint(l_ahead);	
				}
			
			return;	//terminating the loop if we output something.	
		}
		
		p = p -> next;
	}
	
	//if we don't find a record, print an error message.
	printf("\n Name does not exist within our records. Please try again.\n\n");
}

void nodeprint(nodeptr target)
{
	float height, weight, BMI;
	
	/* only one particular node pointed to by a certain pointer in the function call
	is passed here. Thus, this function prints only that one.*/
	
	printf("\t %s", target -> first);
	printf(" %s", target -> last);
			
	height = (target -> heightcm) / 100;
	printf("\n\t Height: ");
	printf("%.2f meters", height); // height conversion from cm to m.
		
	weight = (target -> weightlb) * 0.45359237;
	printf("\n\t Weight: ");
	printf("%.1f kilograms", weight); // weight conversion from lbs to kg.
	
	BMI = (weight / (height*height)); // this line computes for the BMI.	
	
	/* the code segment below matches the person's calculated BMI to 
	its respective classification and prints this information afterwards. */
	
	printf("\n\t Your BMI is %.1f and your classification is ", BMI);
	
	if (BMI < 18.5)
		printf("Underweight.");
	else if (BMI >= 18.5 && BMI <= 24.9)
		printf("Normal weight.");
	else if (BMI >= 25 && BMI <= 29.9)
		printf("Overweight.");
	else if (BMI >= 30)
		printf("Obese.");
	
	printf("\n\n");	
}

// a simple function reused in this program for continuity.
void proceed(void)
{
	printf(" Press any key to continue... ");
	getch();
	system("cls");
}

void searchandedit(nodeptr *head)
{
	char fnam[strsize], lnam[strsize], edtch;
	float height, weight;
	nodeptr p, h;
	
	h = *head;
	p = h;
	
	if (p == NULL)
	{
		printf("\n Sorry! The list is empty. There are no records to display.");
		printf("\n\n You are required to pick a different option.");
		return;
	}
	
	system("cls");
	
	printf("\t===================\n");
	printf("\t   SEARCH RECORD");
	printf("\n\t===================\n\n");
	
	//user input
	
	printf(" Please enter the person's first name: ");
	fflush(stdin); // this line is implemented to prevent problems in user string input.
	gets(fnam); // takes user input for FIRST NAME.
	
	printf("\n Please enter the person's last name: ");
	fflush(stdin); 
	gets(lnam); // takes user input for LAST NAME.
	
	while (p != NULL)
	{
		if ((strcmpi(p -> first, fnam) == 0) && (strcmpi(p -> last, lnam) == 0)) //if existing
		{
			//print the current data
		
			system("cls");
		
			printf("\t==================\n");
			printf("\t   DISPLAY INFO");
			printf("\n\t==================\n\n");
			
			//output the current node (to possibly edit).
			nodeprint(p);
			
			//get only new height and new weight info.
			do { 
				printf(" Edit height and weight info (Y/N)? ");
				scanf(" %c", &edtch);
				
				if (edtch == 'Y' || edtch == 'y')
				{
					do { 
						printf("\n Enter new height (in centimeters): ");
						scanf("%f", &height); // takes height input in cm.
						
						if (height < 1)
							printf("\n Invalid value. Please try again.\n"); // trapping for negative integer input by user.
						
					} while (height < 1);
	
					p -> heightcm = height;
					
					do {
						printf("\n Enter person new weight (in pounds): ");
						scanf("%f", &weight); // takes weight input in lbs.
						
						if (weight < 1)
							printf("\n Invalid value. Please try again.\n"); // trapping for negative integer input by user.
						
					} while (weight < 1);
						
					p -> weightlb = weight; 
					
					printf("\n Information updated! The updated information is as follows:\n\n");
					nodeprint(p);
					return;
				}
				
				else if (edtch == 'N' || edtch == 'n')
				{
					printf("\n Will not proceed with editing. the information remains as follows:\n\n");
					nodeprint(p);
					return;
				}
				
				//trapping for invalid choice.
				else
					printf("\n Error in choice! Please try again.\n\n");
			
			} while (edtch != 'Y' && edtch != 'y' && edtch != 'N' && edtch != 'n');	
									
		p = h;
	
		}
	
		p = p -> next; //loop update
	}
	
	//if we don't find a record, print an error message.	
	printf("\n Name does not exist within our records. Please try again.\n\n");
}

int searchanddelete(nodeptr *head, int index)
{
	char fnam[strsize], lnam[strsize], edtch;
	float height, weight;
	nodeptr p, h;
	
	h = *head;
	p = h;
	
	if (p == NULL) //if the list is empty...
	{
		printf("\n Sorry! The list is empty. There are no records to display.");
		printf("\n\n You are required to pick a different option.");
		proceed();
		return index;
	}
	
	//if the list isn't empty...
	
	system("cls");
	
	printf("\t===================\n");
	printf("\t   SEARCH RECORD");
	printf("\n\t===================\n\n");
	
	//user input segment
	
	printf(" Please enter the person's first name: ");
	fflush(stdin); // this line is implemented to prevent problems in user string input.
	gets(fnam); // takes user input for FIRST NAME.
	
	printf("\n Please enter the person's last name: ");
	fflush(stdin); 
	gets(lnam); // takes user input for LAST NAME.
	
	while (p != NULL)
	{
		if ((strcmpi(p -> first, fnam) == 0) && (strcmpi(p -> last, lnam) == 0)) //if existing
		{
			//print the current data:
			system("cls");
		
			printf("\t==================\n");
			printf("\t   DISPLAY INFO");
			printf("\n\t==================\n\n");
			
			nodeprint(p);
			
			do { 
				printf(" Delete this information (Y/N)? ");
				scanf(" %c", &edtch);
					
				if (edtch == 'Y' || edtch == 'y')
				{
					if (p -> prev == NULL) //deleting head
					{
						h = p -> next;
						p -> next -> prev = NULL;
						p -> next = NULL;
						p = h;
						*head = h;
					}
					
					else if (p -> next == NULL) //deleting tail
					{
						p -> prev -> next = NULL;
						p -> prev = NULL;
						p = h;
						*head = h;
					}
					
					else //deleting middle
					{
						p -> prev -> next = p -> next;
						p -> next -> prev = p -> prev;
						p -> prev = NULL;
						p -> next = NULL;
						p = h;
						*head = h;
					}
				
					printf("\n Node removed. The updated data will be shown on the screen. \n\n");
					proceed();
					//passing the linked list for printing, and updating the index after deletion.
					displayAll(*head, index - 1); 
					return index - 1;
				}
			
				else if (edtch == 'N' || edtch == 'n')
				{
					printf(" Node is NOT removed. The data will be shown on the screen. \n\n");
					proceed();
					//passing the linked list for printing.
					displayAll(*head, index); 
					return index;
				}
				
				else //trapping for invalid choice.
					printf("\n Error in choice! Please try again.\n\n");
			
			} while (edtch != 'Y' && edtch != 'y' && edtch != 'N' && edtch != 'n');	
		
			p = h;
		
		}
		
		p = p -> next;
	}	
		//if we don't find a record, print an error message.
		printf("\n Name does not exist within our records. Please try again.\n\n");
		proceed();
		return index;
}
