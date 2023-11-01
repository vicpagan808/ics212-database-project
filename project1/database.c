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
//  FILE:        database.c
//
//  DESCRIPTION: Database for storing user account numbers, names, 
//               and addresses. Functions not implemented yet. Prints
//               the function that was called as well as the parameters
//               passed to it when in debug mode.
//
****************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "record.h"
#include "database.h"

extern int debugMode;

/*****************************************************************
//
//  Function name: addRecord
//
//  DESCRIPTION:   Stub function that prints the name of the function and the parameters passed to it when called
//                 in debug mode
//
//  Parameters:    recordPointer (struct record **) : Pointer to the address of the record struct
//                 accNum (int) : The account number input by the user
//                 name (char[]) : Pointer to the address of the first element in the name character array
//                                 input by the user
//                 address (char[]) : Pointer to the address of the first element in the address character
//                                    array input by the user
//
****************************************************************/

int addRecord(struct record ** startPointer, int accNum, char name[], char address[])
{
    if (debugMode == 1)
    {
        printf("\nThe addRecord function from database.c was called with parameters:\n");
        printf("Account number: %d\n", accNum);
        printf("Name: %s\n", name);
        printf("Address: %s\n", address);
        return 0;
    }
    else
    {
        struct record *newRecord;

        if (*startPointer == NULL)
        {
            newRecord = (struct record*)malloc(sizeof(struct record));
            strcpy(newRecord->address, address);
            strcpy(newRecord->name, name);
            newRecord->accountno = accNum;
            newRecord->next = NULL;
            *startPointer = newRecord;
            
            return 0;
        }
        else
        {
            struct record *temp = *startPointer;
            struct record *prev = NULL;

            while (temp != NULL && accNum <= temp->accountno)
            {
                if (accNum == temp->accountno)
                    return -1;
                prev = temp;
                temp = temp->next;
            }

            newRecord = (struct record*)malloc(sizeof(struct record));              
            strcpy(newRecord->address, address); 
            strcpy(newRecord->name, name);
            newRecord->accountno = accNum;
        
            if (prev == NULL)
            {
                newRecord->next = temp;
                *startPointer = newRecord;
                return 0;
            }
            else if (temp == NULL)
            {
                newRecord->next = NULL;
                prev->next = newRecord;
                return 0;
            }
            else
            {
                newRecord->next = temp;
                prev->next = newRecord;
                return 0;
            }   
        }
    }
}

/*****************************************************************
//
//  Function name: printAllRecords
//
//  DESCRIPTION:   Stub function that prints the name of the function and the parameters passed to it when called
//                 in debug mode
//
//  Parameters:    start (struct record *) : Pointer to the first element in the record struct
//
****************************************************************/

void printAllRecords(struct record * start)
{
    if (debugMode == 1)
    {
        printf("\nThe printAllRecords function from database.c was called.\n");
    }
    else
    {
        if (start == NULL)
            printf("\nPrintall selected. Database is empty.\n");
        else
        {
            struct record * temp = start;

            printf("\nPrintall selected. Printing all records.\n");

            while (temp != NULL)
            {
                printf("Account Number: %d\nName: %s\nAddress: %s\n\n", temp->accountno, temp->name, temp->address);
                temp = temp->next;
            }
        }
    }
}

/*****************************************************************
//
//  Function name: findRecord
//
//  DESCRIPTION:   Stub function that prints the name of the function and the parameters passed to it when called
//                 in debug mode
//
//  Parameters:    start (struct record *) : Pointer to the first element in the record struct
//                 accNum (int) : The account number input by the user
//
****************************************************************/

int findRecord(struct record * start, int accNum)
{
    if (debugMode == 1)
    {
        printf("\nThe findRecord function from database.c was called with parameters:\n");
        printf("Account number: %d\n", accNum);
        return 0;
    }
    else
    {
        struct record * temp = start;

        while (temp != NULL)
        {
            if(temp->accountno == accNum)
            {
                printf("\nRecord found:\nAccount Number: %d\nName: %s\nAddress: %s\n", temp->accountno, temp->name, temp->address);
                return 0;
            }
        
            temp = temp->next;
        }

        printf("\nRecord with account number %d not found.\n", accNum);
        return -1;
    }
}

/*****************************************************************
//
//  Function name: deleteRecord
//
//  DESCRIPTION:   Stub function that prints the name of the function and the parameters passed to it when called
//                 in debug mode
//
//  Parameters:    recordPointer (struct record **) : Pointer to the address of the record struct pointer
//                 accNum (int) : The account number input by the user
//
****************************************************************/

int deleteRecord(struct record ** startPointer, int accNum)
{
    if (debugMode == 1)
    {
        printf("\nThe deleteRecord function from database.c was called with parameters:\n");
        printf("Account number: %d\n", accNum);
        return 0;
    }
    else
    {
        struct record * temp = *startPointer;
        struct record * prev = NULL;

        while (temp != NULL && accNum != temp->accountno)
        {
            prev = temp;
            temp = temp->next;
        }
        
        if (temp == NULL)
        {   
            printf("\nRecord with account number %d not found.\n", accNum);
            return -1;
        }

        if (prev == NULL)
            *startPointer = temp->next;
        else
            prev->next = temp->next;

        free(temp);
        printf("\nRecord with account number %d deleted.\n", accNum);
        return 0;
    }
}

/*****************************************************************
//
//  Function name: writefile
//
//  DESCRIPTION:   This functions writes to a file using the given
//                 array of struct pokemon
//
//  Parameters:    pokearray (struct pokemon []) : The array of struct pokemons
//                                                 to write onto the file
//                 num (int) : The number of struct pokemon to write onto the file
//                 filename (char []) : The name of the file to write onto
//
//  Return values:  0 : Functions was successful
//                 -1 : File was not able to be accessed
//
****************************************************************/

int writefile(struct record * start, char filename[])
{
    if (debugMode == 1)
    {
        printf("\nThe writefile function from database.c was called with parameters:\n");
        printf("Filename: %s\n", filename);
        return 0;
    }
    else
    {
        FILE *file = fopen(filename, "w");
        struct record * temp = start;

        if (file == NULL)
        {
            return -1;
        }
    
        while (temp != NULL)
        {
            fprintf(file, "%d\n%s\n%s$\n", temp->accountno, temp->name, temp->address);
            temp = temp->next;
        }

        fclose(file);
        return 0;
    }
}

/*****************************************************************
//
//  Function name: readfile
//
//  DESCRIPTION:   Reads the data of a file and copies it to an
//                 array of struct pokemon
//
//  Parameters:    pokearray (struct pokemon []) : The array of struct pokemon
//                                                 to copy the data read off the file
//                                                 to
//                 num (int *) : The address of the variable noting the number
//                               of arrays of struct pokemon in the file
//                 filename (char []) : The name of the file to read off of
//
//  Return values:  0 : Function was successful
//                 -1 : File was not able to be accessed
//
****************************************************************/

int readfile(struct record ** startPointer, char filename[])
{
    if (debugMode == 1)
    {
        printf("\nThe readfile function from database.c was called with parameters:\n");
        printf("Filename: %s\n", filename);
        return 0;
    }
    else
    {
        FILE * file = fopen(filename, "r");
        int i;
        int getAccountNo;
        char getName[30];
        char getAddress[50];

        if (file == NULL)
            return -1;

        while (fscanf(file, "%d\n", &getAccountNo) != EOF)
        {
            fgets(getName, 30, file);
            getName[strlen(getName) - 1] = '\0';
            i = 0;
    
            do
            {
                getAddress[i] = fgetc(file);
                i++;
            }
            while (i < 50 && getAddress[i-1] != '$');
       
            getAddress[i-1] = '\0';
            addRecord(startPointer, getAccountNo, getName, getAddress);
        }

    fclose(file);
    return 0;
    }
}

/*****************************************************************
//
//  Function name: readfile
//
//  DESCRIPTION:   Reads the data of a file and copies it to an
//                 array of struct pokemon
//
//  Parameters:    pokearray (struct pokemon []) : The array of struct pokemon
//                                                 to copy the data read off the file
//                                                 to
//                 num (int *) : The address of the variable noting the number
//                               of arrays of struct pokemon in the file
//                 filename (char []) : The name of the file to read off of
//
//  Return values:  0 : Function was successful
//                 -1 : File was not able to be accessed
//
****************************************************************/

void cleanup(struct record ** startPointer)
{
    struct record * current = *startPointer;

    while (current != NULL)
    {
        struct record * temp = current;
        current = current->next;
        free(temp);
    }

    *startPointer = NULL;
}
