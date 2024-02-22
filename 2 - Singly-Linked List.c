// Name: Lanz Alexander Malto
// Date Created: September 6, 2023
// Date Finished: September 8, 2023
/* Summary of the problem: This program is a conversion from the use of array of
structures to the use of singly linked list in inputting/storing, searching for, and displaying
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
int searchBMI(nodeptr h);
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
			case 1: num = input(&head, index); 
					index = num; 
					break;
			case 2: displayAll(head, index);
					break;
			case 3: searchBMI(head);
					break;
			case 4: printf("\n Press any key to continue... ");
					getch();
					exit(0);
		}
	
 	} while (pick != 4); 
	
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
		printf("\n 2. Display All Records");
		printf("\n 3. Search for a Record");
		printf("\n 4. Exit the Program");
		printf("\n\n Pick a choice (1-4): ");
		scanf("%d", &choice);
		
		if (choice < 1 || choice > 4)
		{
			printf("\n Error in choice! Please pick a number from 1 to 4.\n\n");
			proceed();
		}
				
	} while (choice < 1 || choice > 4); // trapping for invalid menu choice.
	
	return choice;
}

int input(nodeptr *head, int index)
{
	char fnam[strsize], lnam[strsize];
	float height, weight;
	nodeptr h, temp, p;
	
	h = *head; //local head nodeptr in this function.
	
	system("cls");
	
	if (h == NULL) // meaning, this function will create the first node.
	{
		h = (nodeptr) malloc(sizeof(Node));
	
		printf("\t==============\n");
		printf("\t   PERSON %d", index + 1); // for appropriate numbering of the data, we shall start at PERSON 1 (index [which is 0] + 1).
		printf("\n\t==============\n\n");
	
		printf(" Enter first name of person %d: ", index + 1);
		fflush(stdin); 
		gets(fnam);
		strcpy(h -> first, fnam); 
					
		printf("\n Enter last name of person %d: ", index + 1);
		fflush(stdin); 
		gets(lnam);
		strcpy(h -> last, lnam);
	
		do {
			printf("\n Enter person %d's height (in centimeters): ", index + 1);
			scanf("%f", &height); // takes height input in cm.
			
			if (height < 1)
				printf("\n Invalid value. Please try again.\n"); // trapping for negative integer input by user.
			
		} while (height < 1);
		
		h -> heightcm = height;
		
		do {
			printf("\n Enter person %d's weight (in pounds): ", index + 1);
			scanf("%f", &weight); // takes weight input in lbs.
			
			if (weight < 1)
				printf("\n Invalid value. Please try again.\n"); // trapping for negative integer input by user.
			
		} while (weight < 1);
		
		h -> weightlb = weight; 
		
		h -> next = NULL; //this completes the node pointed to by h (the local head).
		
		*head = h; //this will allow the local head variable to share the linked list with the head variable local to main().
			
	}

	else // meaning, there is/are already existing node/s.
	{
		p = h; //since h is already equated to *head before this else segment, we only need to situate p at the beginning of the list.
		
		temp = (nodeptr) (malloc(sizeof(Node))); //creating temp variable we will be connecting h and *head to later.
		
		do {
			p = *head; // (a).
			
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
			
			// Algorithm to see if the user is trying to add a record under a particular name that already exists in the list.
			
			/* Logic: temp is holding a node. We need to traverse the list attached to h/*head, checking the nodes one by one if
			there is a pair. If so, an error message will appear and the rest of the loop segment will be skipped with "break". 
			p will go back to the beginning of the list (see "(a)"), allowing for proper checking of the linked list from the start should 
			the user enter another name that already is in the list. The user will then be prompted to re-input information. */
		
			while (p != NULL)
			{
				if ((strcmpi(temp -> first, p -> first) == 0) && (strcmpi(temp -> last, p -> last) == 0))
				{
					printf("\n Sorry! This record already exists. Please try again.\n\n");
					proceed();
					break;
				}
				p = p -> next;
			}
			
		} while ((strcmpi(temp -> first, p -> first) == 0) && (strcmpi(temp -> last, p -> last) == 0));
		
		// If there are no like information, we will proceed with asking the user for height/weight inputs.
		
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
		
		temp -> next = NULL; //temp is now filled with unique information.
		
		p = h;
		
		// finding the last node.
		while (p -> next != NULL)
			p = p -> next;
			
		// at this point, p -> next == NULL. Thus, we append temp node to the end of the linked list. 
		
		p -> next = temp;
		
		*head = h; 
		
		p = h;
			
	}
	
	printf("\n Information recorded!");
	proceed();
	
	index++; // adding 1 to our index for UI if the user will want to input again.
	
	return index;

}

int displayAll(nodeptr h, int index)
{
	int y, row, col;
	float height, weight, BMI;
	nodeptr p = h;
	
	if (h == NULL)
	{
		printf("\n Sorry! The list is empty. There are no records to display.");
		printf("\n\n You are required to pick a different option.");
		proceed();
		
		return 0;
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
		p = p -> next;
		y++;
		printf("\n");
	}
	
	printf("\n\n");
	printf(" Current number of records: %d\n\n", index);	
	proceed();
}

int searchBMI(nodeptr h)
{
	char fnam[strsize], lnam[strsize];
	int check1, check2;
	float height, weight, BMI;
	
	if (h == NULL)
	{
		printf("\n Sorry! The list is empty. There are no records to display.");
		printf("\n\n You are required to pick a different option.");
		proceed();
		return 0;
	}
	
	system("cls");
	
	printf("\t===================\n");
	printf("\t   SEARCH RECORD");
	printf("\n\t===================\n\n");
	
	printf(" Please enter the person's first name: ");
	fflush(stdin); // this line is implemented to prevent problems in user string input.
	gets(fnam); // takes user input for FIRST NAME.
	
	printf("\n Please enter the person's last name: ");
	fflush(stdin); 
	gets(lnam); // takes user input for LAST NAME.
	
	nodeptr p = h;	
	while (p != NULL)
	{
		if ((strcmpi(fnam, p -> first) == 0) && (strcmpi(lnam, p -> last) == 0)) 
		{
			system("cls");
	
			printf("\t==================\n");
			printf("\t   DISPLAY INFO");
			printf("\n\t==================\n\n");
			
			printf(" %s", p -> first);
			
			printf(" %s", p -> last);
			
			height = p -> heightcm;
			printf("\n Height: ");
			printf("%.2f meters", height / 100); // height conversion from cm to m.
			
			weight = p -> weightlb;
			printf("\n Weight: ");
			printf("%.1f kilograms", weight * 0.45359237); // weight conversion from lbs to kg.
			
			BMI = ((weight * 0.45359237) / ((height / 100) * (height / 100))); // this line computes for the BMI.	
			
			/* the code segment below matches the person's calculated BMI to 
			its respective classification and prints this information afterwards. */
			
			printf("\n Your BMI is %.1f and your classification is ", BMI);
			
			if (BMI < 18.5)
				printf("Underweight.");
			else if (BMI >= 18.5 && BMI <= 24.9)
				printf("Normal weight.");
			else if (BMI >= 25 && BMI <= 29.9)
				printf("Overweight.");
			else if (BMI >= 30)
				printf("Obese.");
			
			printf("\n\n");
			
			proceed();	
			
			return 0;
		}
		
		p = p -> next;
	}
	
	printf("\n Name does not exist within our records. Please try again.\n\n");
	proceed();
}

// a simple function reused in this program for continuity.

void proceed(void)
{
	printf(" Press any key to continue... ");
	getch();
	system("cls");
}
