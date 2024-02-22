// Name: Lanz Alexander Malto
// Date Created: November 25, 2023
// Date Finished: December 4, 2023
/* Summary of the problem: This program focuses on a BINARY SEARCH TREE Data Structure involving taking user's input on 
a number of people's height and weight information to determine their BMI and BMI classification, one at a time. 
Taking elements to display, edit, or delete will follow the concepts of BINARY SEARCH TREES and IN-ORDER TRAVERSALS, 
utilizing standard functions based on this data structure.*/

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <stdbool.h>
#define strsize 40

typedef struct bstree *nodeptr;
typedef struct bstree
{
	nodeptr left;
	char first[strsize];
	char last[strsize];
	float heightcm;
	float weightlb;
	nodeptr right;
} BSTree;

//function prototypes
int menu(void);																

//prototypes of binary search tree-based functions/operations
void CreateTree(nodeptr *ROOT, bool *chk);									
void AddtoTree(nodeptr *ROOT, bool *chk);									
void SearchandDisplay(nodeptr *ROOT, bool *chk, bool *src);
void SearchandDelete(nodeptr *ROOT, bool *chk, bool *src);
void DisplayAll(nodeptr *ROOT, bool *chk);									
void FindMinMax(nodeptr *ROOT, bool *chk);									

void InOrderTraversal(nodeptr *root, nodeptr element, int mode, bool *srch);
bool IsEmpty(nodeptr root);													
int InsertElement(nodeptr *ROOT, nodeptr element);							
void DeleteElement(nodeptr *ROOT, nodeptr element, bool *src);

//prototypes of other functions
void proceed(void);															
void display(nodeptr element);												
void SearchedElement(nodeptr *p, nodeptr e, int mode);						
int Compare(nodeptr root, nodeptr element);									
bool DeleteMenu();

int main(void)
{
	int pick;
	nodeptr ROOT = NULL;
	bool chk = false, src = false; 
	
	do {
		pick = menu();
	
		switch (pick)
		{
			//create BST
			case 1: CreateTree(&ROOT, &chk);
					break;
			//add element into the BST
			case 2: AddtoTree(&ROOT, &chk);
					break;
			//Search and display one element		
			case 3: SearchandDisplay(&ROOT, &chk, &src);
					break;
			//search and delete element from the tree
			case 4: SearchandDelete(&ROOT, &chk, &src);
					break;
			//display all elements in the tree
			case 5: DisplayAll(&ROOT, &chk);
					break;
			//Find the maximum and minimum element (based on last/first name combination)
			case 6:	FindMinMax(&ROOT, &chk);
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
		printf("\t ==========\n");
		printf("\t    MENU");
		printf("\n\t ==========\n\n");
		
		printf(" 1. Create Binary Search Tree");
		printf("\n 2. Add to Binary Search Tree");
		printf("\n 3. Search and Display An Element");
		printf("\n 4. Search and Delete");
		printf("\n 5. Display All Elements of the Binary Search Tree");
		printf("\n 6. Find the Minimum/Maximum Elements");
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

void CreateTree(nodeptr *ROOT, bool *chk)		
{
	nodeptr r = *ROOT;
	bool chkr = *chk;
	char c;
	
	if (chkr && !IsEmpty(r))	// (b.) When re-creating the tree, check if there are elements (i.e., root->left or root->right is not NULL)
	{
		printf("\n The tree already has elements!\n\n"); // (c.) If tree isn't empty, output a confirmation message if the user wants to continue.
		
		do { 			
			printf(" Would you like to continue initiating this function and empty out the tree's contents (Y/N)? ");
			scanf(" %c", &c);
			
			if (c == 'Y' || c == 'y')			// (i.) If yes, set your root to NULL
			{
				printf("\n The tree has been overwritten!\n\n");					
				break;				
			}
							
			else if (c == 'N' || c == 'n') 		// (ii.) If no, go back to the Main Menu.
			{
				printf("\n The overwriting of the tree has been cancelled.\n\n");
				proceed();
				return;
			}
			
			else 
				printf("\n Error in choice! Please try again.\n\n");
			
		} while (c != 'Y' && c != 'y' && c != 'N' && c != 'n');
	}
	
	else
		printf("\n The tree has been created!\n\n");
	
	r = NULL;		// (a.)/(i.) just set your root to NULL 
	*ROOT = r; 
	
	chkr = true;		
	*chk = chkr; 		
	
	proceed();
	return;		
}

void AddtoTree(nodeptr *ROOT, bool *chk)	// (c.) Be sure to pass the root as a parameter to this function.
{
	// (d.) You can create the element/node in this function or create it in another function.
	// I chose to create it in this function.
	
	nodeptr r = *ROOT, n;
	nodeptr element = (nodeptr) malloc(sizeof(BSTree)); 
	char c;
	bool chkr = *chk;
	int x;

	//structure elements
	char fnam[strsize], lnam[strsize];
	float height, weight;
	
	if (!chkr) 	
		printf("\n The tree has not been created. Please create one first.\n\n");
	
	else 
	{	
		system("cls");
		printf("\t ===============\n");
		printf("\t   ADD TO TREE\n");
		printf("\t ===============\n");
		
		element -> left = NULL;
		element -> right = NULL; 
		
		// (a.) Ask the user for data to be stored in the element/node.
		printf("\n Enter first name: " );
		fflush(stdin); 
		gets(fnam);
		strcpy(element -> first, fnam);
	
		printf("\n Enter last name: " );
		fflush(stdin); 
		gets(lnam); 
		strcpy(element -> last, lnam);
		
		// (b.) Follow the rule when inserting elements/nodes in a BST.
		
		x = InsertElement(&r, element);	// checking first for duplicates.
		
		// (e.) If the node is a duplicate, output an error message to the user before returning to the main menu.
		if (x == 3)
			printf("\n Error! There is already data registered for %s %s. Please try again.\n\n", strupr(element -> first), strupr(element -> last));	
		
		else // if element has no match, fetch the remaining data.
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
			
			printf("\n Information recorded! This node has been added to the tree.\n\n");			
		}
		
		// updating root.
		*ROOT = r;

	}
	
	proceed();
	return;
}

int InsertElement(nodeptr *ROOT, nodeptr element) 
{
    nodeptr e = element;
	    
	if (IsEmpty(*ROOT))
		*ROOT = element;   
		
	else if (*ROOT != NULL)
	{
		int x = Compare(*ROOT, e);	//are the names recorded r less than the names in element?
		
		if (x == 1)	// element < root
			InsertElement(&(*ROOT) -> left, element);
			
		else if (x == 2) // element > root
			InsertElement(&(*ROOT) -> right, element);
			
		else if (x == 3) // duplicate! 
			return x;
	}
}

void SearchandDelete(nodeptr *ROOT, bool *chk, bool *src)
{
	nodeptr r = *ROOT, ntd = r, P_ntd = r;
	nodeptr e = (nodeptr) malloc(sizeof(BSTree));
	bool chkr = *chk, srch = *src;

	//structure elements
	char fnam[strsize], lnam[strsize], c;
	
	if (!chkr)
		printf("\n The tree has not been created. Please create one first.\n\n");
	
	else 				
	{
		if (IsEmpty(r)) // (a). Output an error message if the tree is empty. 	
			printf("\n The tree is empty! Please insert at least one element inside it.\n\n");
			
		else			// (b.) If the tree is not empty:							
		{
			system("cls");
			printf("\t =====================\n");
			printf("\t   SEARCH AND DELETE\n");
			printf("\t =====================\n");
			
			// (i.) Ask the user for the last name and first name to search:
			printf("\n Enter first name: " );
			fflush(stdin); 
			gets(fnam);
			strcpy(e -> first, fnam);
		
			printf("\n Enter last name: " );
			fflush(stdin); 
			gets(lnam); 
			strcpy(e -> last, lnam);
			e -> left = NULL;
			e -> right = NULL;

			DeleteElement(&r, e, &srch);	// (ii.) Traverse the tree to search for the element.
			
			// (iii.) iii. Output an error message if it does not exist in the tree before returning to the main menu.
			if (!srch)
				printf("\n Error! This record does not exist. Please try again.\n\n");
				
			// (iv.); (1.) If the element exists, display all the data in the element (including the BMI and category)
			// 		* This happens in the DeleteElement function below.		
			
		}
	}
	
	*ROOT = r;					
	proceed();
	return;
}

void DeleteElement(nodeptr *ROOT, nodeptr element, bool *src) //a variation of InOrderTraversal made for the deleting.
{
    nodeptr e = element, temp, IO_Pred;
    
    if (IsEmpty(*ROOT))
		return; 
		
	else if (*ROOT != NULL)
	{
		int x = Compare(*ROOT, e);	// are the names recorded r less than the names in element?
			
		if (x == 1)	// element < root
			DeleteElement(&(*ROOT) -> left, element, &(*src));
			
		else if (x == 2) // element > root
			DeleteElement(&(*ROOT) -> right, element, &(*src));
			
		else if (x == 3) // element found! 
		{
			if (*src == false)
			{
				printf("\n ELEMENT FOUND:\n\n");				// visit the root (and display, only if the element exists)
				display(*ROOT);
				*src = true;
				
				if (!DeleteMenu())								// (2.) Ask the user for confirmation before deleting the element.
				{
					printf("\n Information not deleted. Returning to main menu.\n\n");
					return;	
				}	
				
				else
					printf("\n Element deleted!\n\n"); 
			}
	
			// case 1: if node has no children
			if ((*ROOT) -> left == NULL && (*ROOT) -> right == NULL)
				*ROOT = NULL;	
			
			// case 2: if node has ONE child (L)
			else if ((*ROOT) -> left == NULL)
			{
				temp = *ROOT;
				*ROOT = (*ROOT) -> right;
				free(temp);
			}
			
			// case 2: if node has ONE child (R)
			else if ((*ROOT) -> right == NULL)
			{
				temp = *ROOT;
				*ROOT = (*ROOT) -> left;
				free(temp);	
			}	
			
			// case 3: if node has TWO children [applying in-order PREDECESSOR]
			else if ((*ROOT) -> left != NULL && (*ROOT) -> right != NULL)
			{
				// Finding the predecessor node:
				IO_Pred = (*ROOT) -> left;			// move one level left.
				
				while (IO_Pred  -> right != NULL)	// traverse all the way to the right.
					IO_Pred  = IO_Pred -> right;
		
				strcpy((*ROOT) -> first, IO_Pred  -> first);
				strcpy((*ROOT) -> last, IO_Pred  -> last);
				(*ROOT) -> heightcm = IO_Pred -> heightcm;
				(*ROOT) -> weightlb = IO_Pred -> weightlb;
										
				DeleteElement(&(*ROOT) -> left, IO_Pred, &(*src));
			}
		}
	}
}

int Compare(nodeptr root, nodeptr element)
{
	char e_first[strsize], e_last[strsize], r_first[strsize], r_last[strsize];
	
	strcpy(e_first, element -> first);
	strcpy(e_last, element -> last);
	strcpy(r_first, root -> first);
	strcpy(r_last, root -> last);
	
	int res_ln = stricmp(e_last, r_last);		//is the ln in element <, >, = ln in root?
	int res_fn = stricmp(e_first, r_first);		//is the fn in element <, >, = fn in root?
	
	if (res_ln < 0)								//element_last name < than root_last name
		return 1;
	
	else if (res_ln > 0)						//element_last name > than root_last name
		return 2;
		
	else
	{
		if (res_fn < 0)							//element_first name < than root_first name
			return 1;
			
		else if (res_fn > 0)					//element_first name > than root_first name
			return 2;
			
		else if (res_fn == 0 && res_ln == 0) 	//reject duplicates:
			return 3;	
	}
}

bool IsEmpty(nodeptr root)
{
	if (root == NULL)
		return true;
	else
		return false;
}

void FindMinMax(nodeptr *ROOT, bool *chk)		
{
	nodeptr r = *ROOT, p = r;
	bool chkr = *chk;
	
	if (!chkr) 	
		printf("\n The tree has not been created. Please create one first.\n\n");
		
	else
	{
		if (IsEmpty(r))
			printf("\n The tree is empty. Please insert an element inside it first.\n\n");		
	
		else 
		{	
			system("cls");
			printf("\t ===================\n");
			printf("\t   MINIMUM ELEMENT\n");
			printf("\t ===================\n\n");
			
			while (p -> left != NULL)		// farthest leaf on the left side of our BST.
				p = p -> left;
			
			display(p);
			
			p = r;
			
			printf("\t ===================\n");
			printf("\t   MAXIMUM ELEMENT\n");
			printf("\t ===================\n\n");
			
			while (p -> right != NULL)		// farthest leaf on the right side of our BST.
				p = p -> right;
			
			display(p);
		}	
	}

	proceed();
	return;
}

void DisplayAll(nodeptr *ROOT, bool *chk)
{
	nodeptr r = *ROOT, p = r;
	bool chkr = *chk;
	
	if (!chkr) 
		printf("\n The tree has not been created. Please create one first.\n\n");
	
	else 				
	{
		if (IsEmpty(r)) 	
			printf("\n The tree is empty! Please insert at least one element inside it first.\n\n");
			
		else									
		{
			system("cls");
			printf("\t ================\n");
			printf("\t    DISPLAY ALL\n");
			printf("\t ================\n\n");
			
			InOrderTraversal(&r, NULL, 1, false);	// Using in-order Traversal.
			
			// For more information, I passed "NULL" for the 'element' parameter since there's no need to check for an element in
			// simply displaying all the existing elements. I also passed "false" for the 'srch' parameter since we're not trying
			// to match any elements to the root we're currently holding.
		}
	}
	
	*ROOT = r;
	
	proceed();
	return;
}

void SearchandDisplay(nodeptr *ROOT, bool *chk, bool *src)
{
	nodeptr r = *ROOT;
	nodeptr e = (nodeptr) malloc(sizeof(BSTree));
	bool chkr = *chk, srch = *src;

	//structure elements
	char fnam[strsize], lnam[strsize];
	
	if (!chkr) 		// (a.) Output an error message if the tree is empty.
		printf("\n The tree has not been created. Please create one first.\n\n");
	
	else 			// (b.) If the tree is not empty:
	{
		if (IsEmpty(r)) 	
			printf("\n The tree is empty! Please insert at least one element inside it.\n\n");
			
		else									
		{
			system("cls");
			printf("\t ======================\n");
			printf("\t   SEARCH AND DISPLAY\n");
			printf("\t ======================\n");
			
			// (i.) Ask the user for the last name and first name to search:
			printf("\n Enter first name: " );
			fflush(stdin); 
			gets(fnam);
			strcpy(e -> first, fnam);
		
			printf("\n Enter last name: " );
			fflush(stdin); 
			gets(lnam); 
			strcpy(e -> last, lnam);
					
			InOrderTraversal(&r, e, 2, &srch);	// (ii.) Traverse the tree to search for the element.
			
			// (iii.) iii. Output an error message if it does not exist in the tree before returning to the main menu.
			if (!srch)
				printf("\n Error! This record does not exist. Please try again.\n\n");
		
			// (iv.) If the element exists, display all the data in the element (including the BMI and category)
			// 		* This happens in the InOrderTraversal function below.		
		}
	}
	
	proceed();
	return;
}

void InOrderTraversal(nodeptr *root, nodeptr element, int mode, bool *srch)	
{
	nodeptr r = *root, e = element;
	
	//mode: 1 for display all, 2 for search and display.
	if (mode == 1)
	{
		if (r == NULL)
			return;
		InOrderTraversal(&r -> left, e, mode, &(*srch));				//traverse the left subtree
		
		if (mode == 1)
			display(r);													//visit the root
				
		InOrderTraversal(&r -> right, e, mode, &(*srch));				//traverse the right subtree
	}
	
	else if (mode == 2)
	{
		if (r == NULL)
			return;
	
		InOrderTraversal(&r -> left, e, mode, &(*srch));				//traverse the left subtree
					
		if (Compare(r, e) == 3)										
		{
			printf("\n ELEMENT FOUND:\n\n");							//visit the root (and display, only if the element exists)
			display(r);
			*srch = true;
		}
			
		InOrderTraversal(&r -> right, e, mode, &(*srch));				//traverse the right subtree
	}
	
	*root = r;
}

bool DeleteMenu()
{
	char c;
	
	do {
		printf(" Continue with deleting (y/n)? ");
		scanf(" %c", &c);
		
		if (c == 'Y' || c == 'y')	
			return true;		
										
		else if (c == 'N' || c == 'n')
			return false;
	
		else
			printf("\n Error in choice! Please try again.\n\n");
				
	} while (c != 'Y' && c != 'y' && c != 'N' && c != 'n');
}

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

	strupr(strcpy(fn, element -> first));
	strupr(strcpy(ln, element -> last));
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

