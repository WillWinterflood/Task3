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
    //Using a bubble sort to sort the data in descending order
    int swapped = 1;

    while (swapped == 1) {
        //While loop that keeps going through the file until it is all sorted
        swapped = 0;

        int x;
        for (x = 0; x < length - 1; x++) {
            if (array[x].steps < array[x + 1].steps) {
            // This if statement is saying that if the steps of this line is less than the amount of 
            //  steps on the next line then..

                FitnessData TempValue;
                TempValue = array[x];
                array[x] = array[x + 1];
                array[x  + 1] = TempValue;
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
    //the amount of things in this array is the amount that is max records.

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
        //This is another error checker

        int valid = sscanf(line, "%d-%d-%d,%d:%d,%d", &year, &month, &day, &hours, &minutes, &steps);
        //checking that everything is in the correct format
        if (valid != 6) {
            //If the correct format doesnt apply to at least 1 of these then it will print an error
            perror("Error: Invalid File\n");
        }

    }
    printf("File successfully loaded.\n");
    rewind(file);
    //After the first while loop we need to rewind the file.
    while (fgets(line, buffer_size, file) != NULL && count < Max_Records) {
        tokeniseRecord(line ,',' , date ,time , &array[count].steps);
        //splits the line up when theres a comma
        strcpy(array[count].time, time);
        strcpy(array[count].date, date);
        //strcpy is useful here as it allows the time and date to be added to an array
        
        count = count + 1;
    }
    fclose(file);
    //First part of code is done, now we need to write it to the new file.

    BubbleSort(array, count);
    char OutFileName[buffer_size];
    sprintf(OutFileName, "%s.tsv", FileName);
    //to ensure the filename has .tsv on the end
    // Cant do strcat because there was an error saying that there was too many arguments 
    //   therefore sprintf is good to use, as the string needs to be printed.
    FILE *OutputFile;

    OutputFile = fopen(OutFileName, "w");
    if (OutputFile == NULL) {
        perror("Error: Invalid File");
        return 1;
    }

    for (int x = 0; x < count; x++ ) 
    {
        fprintf(OutputFile, "%s\t%s\t%d\n", array[x].date, array[x].time, array[x].steps);
        //fprintf to print this into the new sorted file. 
    }
    fclose(OutputFile); 
    return 0;
}