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

int compareDescending(const void *a, const void *b) {
    return (*(int *)b - *(int *)a);
}


int main() {
    FILE *file;
    char FileName[] = "FitnessData_2023.csv";
    int buffer = 250;
    char read[buffer];
    int steps;
    char date[11];
    char time[6];
    int x = 0;
    char NewFilename[] = "FitnessData_2023.csv.tsv";
    FILE *NewFile;


    printf("Enter Filename: ");
    scanf("%s", FileName);
    file = fopen(FileName, "r");
    if (file == NULL) {
        perror("Error: could not find or open the file. \n");
        // Error message.
            return 1;

    }
    printf("File successfully loaded.\n");
    


    


    while (fgets(read, buffer, file) != NULL) {
        char CSteps[100];
        // Declaring them all as characters to tokenise is, as thye cannot be tokenised as integers.
        tokeniseRecord(read, ",", date[x], time[x], CSteps);
        steps = atoi(CSteps);
        x++;
         

    }

    qsort(file, x, sizeof(steps), compareDescending);
    NewFile = fopen(NewFilename, "w");
    if (NewFile == NULL) {
        perror("Error");
        return 1;
    }



    return 0;

    
    
}