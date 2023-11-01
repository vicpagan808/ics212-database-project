/*****************************************************************
//
//  NAME:        Victor Pagan
//
//  HOMEWORK:    3b
//
//  CLASS:       ICS 212
//
//  INSTRUCTOR:  Ravi Narayan
//
//  DATE:        September 23, 2023
//
//  FILE:        user_interface.c
//
//  DESCRIPTION: This file is a user interface for a database that holds
//               name and address information with an account number. It
//               asks the user which functions of the database they wish to ask,
//               asks for relevant information for those functions, then 
//               calls the function in the database class file, sending over
//               any needed parameters.
//
****************************************************************/

#include "record.h"
#include "database.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int debugMode = 0;
void getAddress(char [], int);

/*****************************************************************
//
//  Function name: main
//
//  DESCRIPTION:   Asks the user for input as to what function they wish to access
//                 and then asks them for any required information relating to that function.
//
//  Parameters:    argc (int) : The number of elements in argv
//                 argv (char*[]) : An array of arguments passed
//                                  to the program.
//
//  Return values:  0 : Function was run and correctly exited.
//                 -1 : Improper arguments passed onto function. Function did not run.
//
****************************************************************/

int main(int argc, char* argv[])
{
    struct record * start = NULL;
    int accNum;
    char name[30];
    char address[50];
    int quitSelect;
    char filename[] = "database.txt";

    if (argc == 2)
    {
        if (strcmp(argv[1],"debug") == 0)
            debugMode = 1;
        else
        {
            printf("Error invalid argument! Only valid arguments are 'debug' for debug mode or no arguments.\n");
            return -1;
        }
    }
    else if (argc > 2)
    {
        printf("Error invalid argument! Only valid arguments are 'debug' for debug mode or no arguments.\n");
        return -1;
    }

    printf("This program stores the user input data of their name and address and attaches it to the user's input account number.\n");
    if (debugMode == 1)
    {
        printf("\nNote that this program is running in debug mode.\n");
    }
  
    readfile(&start, filename);
   
    do
    { 
        char input[80];
        quitSelect = 0;

        printf("\nPlease type in the name of the function you would like to access then press enter.\n");
        printf("add: adds a new record to the database\n");
        printf("printall: prints all the records in the database\n");
        printf("find: finds record(s) with user input account #\n");
        printf("delete: deletes existing record(s) from the database from user input account #\n");
        printf("\nEnter selection here or enter 'quit' to quit the program: ");

        fgets(input, 80, stdin);
      
        if (strlen(input) == 1)
            printf("Error please enter a choice before pressing enter.");
        else
        {
            if (strncmp(input, "add", (strlen(input)-1)) == 0)
            {
                char flush[80];
                printf("\nAdd selected. Please enter your account number: ");
                scanf("%d", &accNum);
          
                while(accNum <= 0)
                {
                    char flush[80];
                    fgets(flush, 80, stdin);
                    printf("\nInvalid input. Please enter a valid account number: ");
                    scanf("%d", &accNum);
                }

                printf("\nPlease enter your name: ");
                fgets(flush, 80, stdin);
                fgets(name, 30, stdin);
            
                while (strlen(name) <= 1)
                {
                    printf("\nInvalid input. Please enter a valid name: ");
                    fgets(name, 30, stdin);
                }

                name[strlen(name)-1] = '\0';
                getAddress(address, 50);

                if (debugMode == 1)
                {
                    addRecord(&start, accNum, name, address);
                    fgets(flush, 80, stdin);
                }
                else
                {
                    if (addRecord(&start, accNum, name, address) == 0)
                        printf("\nRecord with accountno %d successfully added to database.\n", accNum);
                    else
                        printf("\nUnsuccessful adding of record. Accountno %d already exists within the database.\n", accNum);
                    fgets(flush, 80, stdin);
                }
            }
            else if (strncmp(input, "printall", (strlen(input)-1)) == 0)
                printAllRecords(start);
            else if (strncmp(input, "find", (strlen(input)-1)) == 0)
            {
                char flush[80];
                printf("\nFind selected. Please enter your account number: ");
                scanf("%d", &accNum);
               
                while(accNum <= 0)
                {
                    char flush[80];
                    fgets(flush, 80, stdin);
                    printf("\nInvalid input. Please enter a valid account number: ");
                    scanf("%d", &accNum);
                }

                findRecord(start, accNum);
                fgets(flush, 80, stdin);
            }
            else if (strncmp(input, "delete", (strlen(input)-1)) == 0)
            {
                char flush[80];
                printf("\nDelete selected. Please enter your account number: ");
                scanf("%d", &accNum);

                while(accNum <= 0)
                {
                    char flush[80];
                    fgets(flush, 80, stdin);
                    printf("\nInvalid input. Please enter a valid account number: ");
                    scanf("%d", &accNum);
                }

                deleteRecord(&start, accNum);
                fgets(flush, 80, stdin);
            }
            else if (strncmp(input, "quit", (strlen(input)-1)) == 0)
            {
                quitSelect = 1;

                writefile(start, filename);
                cleanup(&start);

                printf("\nQuit selected. Quitting program.\n");
            }
            else
                printf("\nInvalid selection. Please select a valid function.");
        }
    }
    while (quitSelect == 0);

    return 0;
}

/*****************************************************************
//
//  Function name: getAddress
//
//  DESCRIPTION:   Prompts the user for input for their address, then asking
//                 for them to enter a $ symbol to let the function know when
//                 they are finished with the input. The function then replaces this
//                 symbol with a null terminate character to remove it from the end of
//                 the string.
//
//  Parameters:    address (char[]) : The pointer to the address of the
//                                    first element of the address character array
//                 addressSize (int) : The size of the address character array
//
****************************************************************/

void getAddress(char address[], int addressSize)
{
    int i = 0;

    printf("\nPlease enter your full address. When you are finished, input the '$' character and press ENTER: ");

    while (i < addressSize && address[i-1] != '$')
    {
        address[i] = fgetc(stdin);
        i++;
    }

    address[strlen(address)-1] = '\0';
}
