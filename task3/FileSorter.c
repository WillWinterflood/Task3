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

void BubbleSort(FitnessData *array, int length) {
    int swapped = 1;

    while (swapped == 1) {
        //While loop that keeps going through the file until it is all sorted
        swapped = 0;

        int i;
        for (i = 0; i < length - 1; i++) {
            if (array[i].steps < array[i + 1].steps) {
            // This if statement is saying that if the steps of this line is less than the amount of 
            //  steps on the next line then..

                FitnessData temp;
                temp = array[i];
                array[i] = array[i + 1];
                array[i  + 1] = temp;
                //  ... then it makes the line befroe = to the line after thus swapping the lines

                swapped = 1;
            }
        }
    }
}


int main() {

    int buffer_size = 1000;
    int steps;
    char date[11];
    char time[6];
    char FileName[1000];
    FILE *file;
    char line[buffer_size];
    char filename[buffer_size];
    int count = 0;
    int Max_Records = 1000;
    FitnessData array[Max_Records];

    printf("Input Filename: ");
    scanf("%s", FileName);
    file = fopen(FileName, "r");
    if (file == NULL) {
        perror("Error: Invalid File\n");
        // Error message.
        return 1;
    }
    while (fgets(line, sizeof(line), file) != NULL) {
        int day;
        int month;
        int year;
        int hours;
        int minutes;

        int valid = sscanf(line, "%d-%d-%d,%d:%d,%d", &year, &month, &day, &hours, &minutes, &steps);
        if (valid != 6) {
            perror("Error: Invalid File\n");
        }

    }
    printf("File successfully loaded.\n");
    //declaring all my variables im going to use in this case
    //This holds each individual lines date and time value as the while loop is going through it.
    rewind(file);
    while (fgets(line, buffer_size, file) != NULL && count < Max_Records) {
        tokeniseRecord(line ,',' , date ,time , &array[count].steps);
        strcpy(array[count].time, time);
        strcpy(array[count].date, date);
        //splits the line up when theres a comma
        count = count + 1;
    }
    fclose(file);
    //First part of code is done, now we need to write it to the new file.

    BubbleSort(array, count);
    char OutFileName[] = "FitnessData_2023.csv.tsv";
    FILE *OutputFile;

    OutputFile = fopen(OutFileName, "w");
    if (OutputFile == NULL) {
        perror("Error: Invalid File");
        return 1;
    }

    for (int i = 0; i < count; i++ ) 
    {
        fprintf(OutputFile, "%s\t%s\t%d\n", array[i].date, array[i].time, array[i].steps);
    }
    fclose(OutputFile); 
    return 0;
}