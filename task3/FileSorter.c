#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the struct for the fitness data
typedef struct {
    char date[11];
    char time[6];
    int steps;
} FitnessData;

// Function to tokenize a record
void tokeniseRecord(char *record, char delimiter, char *date, char *time, int *steps) {
    char *ptr = strtok(record, &delimiter);
    if (ptr != NULL) {
        strcpy(date, ptr);
        ptr = strtok(NULL, &delimiter);
        if (ptr != NULL) {
            strcpy(time, ptr);
            ptr = strtok(NULL, &delimiter);
            if (ptr != NULL) {
                *steps = atoi(ptr);
            }
        }
    }
}


int main() {
    char FileName[1000];
    FILE *file;

    printf("Enter Filename: ");
    scanf("%s", FileName);
    file = fopen(FileName, "r");
    if (file == NULL) {
        perror("Error: could not find or open the file. \n");
        // Error message.
            return 1;

    }
    printf("File successfully loaded.\n");
    fclose(file);


    
    
}