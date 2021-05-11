/*

    Name: inventory_task1n2.c
    Purpose: Represents a part shop
    Author: grivera64
    Date: 05/07/2021

*/

#include <stdio.h>
#include <stdlib.h>                                                 /* For Dynamic Memory Location Functions */
#include "readline.h"

#define NAME_LEN 25

struct part
{

    int number;
    char name[NAME_LEN + 1];                                        /* Because last character is '\0' */
    int on_hand;
    struct part *next;

};

/* Function Prototypes/Declarations */

struct part *find_part(struct part *inventory, int number);         /* Helper Function */
struct part *find_last(struct part *inventory, int n);

void print_node(struct part *node);                                 /* Helper function */

struct part *erase_part(struct part *inventory);
struct part *erase_all(struct part *inventory);

struct part *insert(struct part *inventory);
void search(struct part *inventory);
void update(struct part *inventory);
void print(struct part *inventory);

void clear_input(void);
void print_codes(void);

/* Main Function */
int main(void)
{

    struct part *inventory = NULL;                              /* This refers to the first node of the inventory linked list */
    char code;
    int n;

    for (;;)
    {

        printf("Hint: Press h to print possible operation codes\n");
        printf("Enter operation code: ");
        scanf("%c", &code);                                     /* Request for user input */

        clear_input();

        printf("\n\n");

        switch (code)
        {

            /* Insert */
            case 'i':
                inventory = insert(inventory);
                clear_input();
                break;

            /* Search */
            case 's':
                search(inventory);
                clear_input();
                break;

            /* Update */
            case 'u':
                update(inventory);
                clear_input();
                break;

            /* Print Inventory */
            case 'p':
                print(inventory);
                break;
            
            /* Find Last */
            case 'f':

                /* Ask User for the on hand value they are looking for */
                printf("Please enter the quantity you are searching for: ");
                scanf("%d", &n);
                while (getchar() != '\n');

                printf("Searching for the last node...\n");

                struct part *node_found = find_last(inventory, n);
                
                /* Print the node if found */
                if (node_found)
                {
                    printf("Node Found!\n\n");
                    print_node(node_found);
                }
                /* Else print error */
                else
                {

                    printf("Node not found!\n");

                }

                break;

            /* Erase Part */
            case 'e':
                inventory = erase_part(inventory);
                clear_input();
                break;

            /* Print Codes */
            case 'h':
                print_codes();
                break;
            
            /* Quit */
            case 'q':
                printf("\n\nEnd of program!\n");
                inventory = erase_all(inventory);

                /* Terminate Program */
                return 0;

            /* Invalid Code */
            default:
                printf("\nIllegal operational code!\n");

        } //end of switch

        printf("\n\n");

    } //end of for loop

} //end of main

/* Function Definitions */

/* Finds a part in the inventory base on its number */
struct part *find_part(struct part *inventory, int number)
{

    struct part *p;

    /* Find the number against the arguement value */
    for (p = inventory; 
        p != NULL && number > p -> number;                                  /* Assuming inventory is ordered */
        p = p -> next);
    //end of for

    if (p != NULL && number == p -> number)
    {

        return p;

    }
    else
    {

        return NULL;

    }

} //end of find_part

/* Locates the last part in the inventory */
struct part *find_last(struct part *inventory, int n)
{

    /* Guard case if inventory == NULL */
    if (!inventory) 
    {

        printf("Error! Inventory is empty!\n\n");
        return NULL;
    
    }

    /* Locate the last available part */
    struct part *curr, *prev, *latest = NULL;

    for (curr = inventory, prev = NULL; 
        curr != NULL;
        prev = curr, curr = curr -> next)
    {

        if (curr -> on_hand == n)
        {

            latest = curr;

        }

    }
    //end of for

    /* If curr == NULL and previous != NULL, then return the last node, otherwise, NULL */
    return latest;

} //end of find_last

/* Prints a node at the address provided */
void print_node(struct part *node)
{

    /* Print Part Number, Name, and On-Hand */
    printf("Part Number: %d\n", node -> number);
    printf("Part name: %s\n", node -> name);
    printf("Quantity on hand: %d\n", node -> on_hand);

} //end of print_node

/* Erases a part while connecting the separated ends of the inventory */
struct part *erase_part(struct part *inventory)
{

    /* Guard case to check if inventory is NULL */
    if (!inventory) 
    {
        
        printf("Command failed!\nThere are no parts to erase!\n");
        return NULL;

    }

    int number;

    printf("Enter the number of the part you want to delete: ");
    scanf("%d", &number);

    /* Search for part that User wants to delete */
    struct part *curr, *prev;

    for (curr = inventory, prev = NULL;
        curr != NULL && number > curr -> number;
        prev = curr, curr = curr -> next);

    /* Checking if part exists */
    if (curr != NULL && number == curr -> number)
    {

        /* Checking if isn't the first node */
        if (prev) 
        {

            /* Connect the prev and next of curr and free curr */
            prev -> next = curr -> next;

            free(curr);
        }
        /* Check if there is more than one node */
        else if (curr -> next)
        {

            inventory = curr -> next;

            free(curr);

        }
        /* Free the head node */
        else
        {

            free(inventory);
            inventory = NULL;

        }

        printf("Part deleted!\n");

        return inventory;

    }
    else
    {

        /* Print error message */
        printf("The part already does not exist!\n");
        return inventory;

    }

} //end of erase_part

/* Erases all of the dynamically stored information to avoid memory leaks */
struct part *erase_all(struct part *inventory)
{
    
    /* Free all nodes until no more nodes exist */
    struct part *curr, *prev;

    while(1)
    {
        for (curr = inventory, prev = NULL;
            curr != NULL;
            prev = curr, curr = curr -> next);

        /* Checking for duplicate */
        if (curr != NULL)
        {

            if (prev) 
            {
                prev -> next = curr -> next;

                free(curr);
            }
            else
            {

                free(inventory);

            }

            printf("Part deleted!\n");

            inventory = (prev) ? inventory : NULL;

        }
        else
        {

            break;

        }
    }

    return NULL;

} //end of erase_all

/* Inserts a part into the inventory */
struct part *insert(struct part *inventory)
{

    struct part *prev, *curr, *new;

    /* Create a new node */
    new = (struct part *) malloc(sizeof(struct part));

    /* Check if successful */
    if (new == NULL)
    {

        printf("Database (memory) is full; can't add more parts\n");
        return inventory;

    }

    /* Ask User for part number */
    printf("Enter a part number: ");
    scanf("%d", &new -> number);

    /* Find the correct spot to insert */
    for (curr = inventory, prev = NULL;
        curr != NULL && new -> number > curr -> number;
        prev = curr, curr = curr -> next);

    /* Checking for duplicate */
    if (curr != NULL && new -> number == curr -> number)
    {

        printf("Part already exists!\n");
        free(new);
        return inventory;

    }

    /* Ask User for other details about part */
    printf("Enter part name: ");
    read_line(new -> name, NAME_LEN);

    printf("Enter quantity on-hand: ");
    scanf("%d", &new -> on_hand);

    /* Adding the new node to the linked list */

    new -> next = curr;

    if (prev == NULL)
    {

        inventory = new;

    }
    else
    {

        prev -> next = new;

    }

    return inventory;

} //end of insert

/* Searching for a part in the inventory */
void search(struct part *inventory)
{

    int number;
    struct part *p;

    /* Ask User for part to search */
    printf("Enter part number: ");
    scanf("%d", &number);
    p = find_part(inventory, number);

    /* Print if the node exists, otherwise, error */
    if (p != NULL)
    {

        print_node(p);

    }
    else
    {

        printf("Part not found!\n");

    }

} //end of search

/* Updates a selected part in the inventory */
void update(struct part *inventory)
{

    int number, change;

    struct part *p;

    /* Ask User for a part number to search */
    printf("Enter part number: ");
    scanf("%d", &number);
    p = find_part(inventory, number);

    /* If part exists, ask user to update on-hand, else, error */
    if (p != NULL)
    {

        printf("Enter change in quantity on hand: ");
        scanf("%d", &change);

        p -> on_hand += change;

    }
    else
    {

        printf("Part not found!\n");

    }

} //end of update

/* Print the entire inventory */
void print(struct part *inventory)
{

    struct part *p;

    printf("%-20s%-20s%-10s\n", "Part number:", "Part name:", "Quantity:");

    for (p = inventory; p != NULL; p = p -> next)
    {

        printf("%-20d%-20s%-20d\n", p -> number, p -> name, p -> on_hand);

    }

} //end of print

/* Clear the input stream */
void clear_input(void)
{

    while(getchar() != '\n');         /* Skip to the end of the user-defined input */

} //end of clear_input

/* Print all of the valid codes */
void print_codes(void)
{

    /* Print Possible Codes chart */
    printf("======================\nPossible Codes:\n======================\n");

    printf("i - insert a part into the inventory\n");
    printf("s - search for a part in the inventory\n");
    printf("u - update the on-hand amount for an existing part\n");
    printf("p - print the entire inventory\n");
    printf("f - find the last added part in the inventory\n");
    printf("e - erase/remove a part from the inventory\n");
    printf("h - help menue\n");
    printf("q - quit the program\n");
    return;

} //end of print_codes