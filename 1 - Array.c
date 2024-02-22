// Name: Lanz Alexander Malto
// Date Created: ‎August ‎18, ‎2023
// Date Finished: ‎August ‎29, ‎2023
/* Summary of the problem: 
The user shall choose from the main menu an option that will either: 
a.) Allow the inputting/registering of the basic information (first/last name, weight, height) of at most 10 people; 
b.) Display these collated information (with some modifications) in tabular form; 
c.) Search the record of a particular person; or
d.) Immediately exit the program.
The program utilizes multiple instances of trapping (for empty/full array, for invalid choice, etc.) as well. */

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <windows.h>
#define size 10
#define strsize 40

typedef struct Info 
{
	char first[strsize];
	char last[strsize];
	float heightcm;
	float weightlb;
} INFO;

//function prototypes

void gotoxy(short x, short y);
int menu(void);
int input(INFO p[size], int index);
int displayAll(INFO p[size], int index);
int searchBMI(INFO p[size], int index);
int displayBMI(INFO p[size], int index);
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
	int index = 0, pick, num;
	INFO person[size];
	
	do {
		pick = menu();
	
		switch (pick)
		{
			case 1: num = input(person, index); 
					index = num; 
					break;
			case 2: displayAll(person, index);
					num = index;
					break;
			case 3: searchBMI(person, index);
					num = index;
					break;
			case 4: printf("\n Press any key to continue... ");
					getch();
					exit(0);
		}
	
 	} while (num <= size); 
	 
	 /* This do-while loop exists to check whether or not the array of structures is full or not. 
	 When 'num' has the value 0 to 9, it allows the user to input a person's data in the array. 
	 When 'num' reaches 10, the program utilizes trapping inside the function definitions below 
	 to disallow the user from inputting more information in the array. */
	
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

int input(INFO p[size], int index)
{
	char fnam[strsize], lnam[strsize];
	
	if (index >= size)
	{
		printf("\n Sorry! The array is full and can no longer accommodate any more inputs.");
		printf("\n\n You are required to pick a different option.");
		proceed();
		
		return index;
	}
	
	/* TRAPPING: Once the current index reaches at least 10, the user will encounter 
	this error message and will be prompted to return to the main menu. */
	
	system("cls");
	
	printf("\t==============\n");
	printf("\t   PERSON %d", index + 1); // for appropriate numbering of the data, we shall start at PERSON 1 (index [which is 0] + 1).
	printf("\n\t==============\n\n");

	printf(" Enter first name of person %d: ", index + 1);
	fflush(stdin); // this line is implemented to prevent problems in user string input.
	gets(fnam); // takes user input for FIRST NAME.
	strcpy(p[index].first, fnam); // copying the contents of local variable to its appropriate match in the array passed in this function.
		
	printf("\n Enter last name of person %d: ", index + 1);
	fflush(stdin); 
	gets(lnam); // takes user input for LAST NAME.
	strcpy(p[index].last, lnam); // copying the contents of local variable to its appropriate match in the array passed in this function.
	
	do {
		printf("\n Enter person %d's height (in centimeters): ", index + 1);
		scanf("%f", &p[index].heightcm); // takes height input in cm.
		
		if (p[index].heightcm < 1)
			printf("\n Invalid value. Please try again.\n"); // trapping for negative integer input by user.
		
	} while (p[index].heightcm < 1);
	
	do {
		printf("\n Enter person %d's weight (in pounds): ", index + 1);
		scanf("%f", &p[index].weightlb); // takes weight input in lbs.
		
		if (p[index].weightlb < 1)
			printf("\n Invalid value. Please try again.\n"); // trapping for negative integer input by user.
		
	} while (p[index].weightlb < 1);
	
	printf("\n Information recorded!");
	proceed();
	
	index++; // adding 1 to our index to check for the array size later on.
	
	return index;
}

int displayAll(INFO p[size], int index)
{
	int y, row, col;
	float BMI;
	
	if (index == 0)
	{
		printf("\n Sorry! The array is empty. There are no records to display.");
		printf("\n\n You are required to pick a different option.");
		proceed();
		
		return index;
	} 
	
	/* TRAPPING: Once the current index is 0, the user will encounter this error message and 
	will be prompted to return to the main menu. We set the return value to 0 since
	we didn't add or remove information to the array--it is simply empty at the moment.*/
	
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
						printf(" %s", p[row].first);
						break;
				case 1: gotoxy(24, y);
						printf(" %s", p[row].last);
						break;
				case 2: gotoxy(40, y);
						printf(" %.2f", p[row].heightcm / 100); // height conversion from cm to m.
						break;
				case 3: gotoxy(56, y);
						printf(" %.1f", p[row].weightlb * 0.45359237); // weight conversion from lbs to kg.
						break;
				case 4: BMI = ((p[row].weightlb * 0.45359237) / ((p[row].heightcm / 100) * (p[row].heightcm / 100))); //this line computes for the BMI.	
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
		y++;
		printf("\n");
	}
	
	printf("\n\n");
	proceed();
}

int searchBMI(INFO p[size], int index)
{
	char fnam[strsize], lnam[strsize];
	int check1, check2;
	
	if (index == 0)
	{
		printf("\n Sorry! The array is empty. There are no records to display.");
		printf("\n\n You are required to pick a different option.");
		proceed();
		
		return index;
	}
	
	/* TRAPPING: Once the current index is 0, the user will encounter this error message and 
	will be prompted to return to the main menu. We set the return value to 0 since
	we didn't add or remove information to the array--it is simply empty at the moment.*/
	
	system("cls");
	
	/* The logic of this function goes as follows: the user is to input the first name
	and last name of the record they want to search. The for-loop in this function will
	check if a record exists similar to what the user wishes to search (case-insensitive).
	If the record exists, the information of that particular person will be displayed. 
	Else, an error message will be displayed and the user will be brought back to the menu.*/
	
	printf("\t===================\n");
	printf("\t   SEARCH RECORD");
	printf("\n\t===================\n\n");
	
	printf(" Please enter the person's first name: ");
	fflush(stdin); // this line is implemented to prevent problems in user string input.
	gets(fnam); // takes user input for FIRST NAME.
	
	printf("\n Please enter the person's last name: ");
	fflush(stdin); 
	gets(lnam); // takes user input for LAST NAME.
		
	for (check1 = 0; check1 < index; check1++)
	{	
		if ((strcmpi(fnam, p[check1].first) == 0) && (strcmpi(lnam, p[check1].last) == 0)) 
		{
			displayBMI(p, check1);
			proceed();
			return 0;	
		}
	}
	
	printf("\n Name does not exist within our records. Please try again.\n\n");
	proceed();
}

int displayBMI(INFO p[size], int person)
{
	float BMI; 
	
	system("cls");
	
	printf("\t==================\n");
	printf("\t   DISPLAY INFO");
	printf("\n\t==================\n\n");
	
	printf(" %s", p[person].first);
	
	printf(" %s", p[person].last);
	
	printf("\n Height: ");
	printf("%.2f meters", p[person].heightcm / 100); // height conversion from cm to m.
	
	printf("\n Weight: ");
	printf("%.1f kilograms", p[person].weightlb * 0.45359237); // weight conversion from lbs to kg.
	
	BMI = ((p[person].weightlb * 0.45359237) / ((p[person].heightcm / 100) * (p[person].heightcm / 100))); // this line computes for the BMI.	
	
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
}

// a simple function reused in this program for continuity.

void proceed(void)
{
	printf(" Press any key to continue... ");
	getch();
	system("cls");
}