#include <stdio.h>
#include <stdlib.h> // for atoi,  EXIT_SUCCESS and EXIT_FAILURE
#include <string.h> // for strtok_r

/* Copied from movies.c provided by Assignment materials
 * Function: processMovieFile
 *   Opens a file, reads and prints each line
 *   filePath: path to the file
 * 
 *  This function shows sample code that opens a file, then in a loop reads and prints each line in that file.
 *  You can use this code however you want in your Prog Assignment 2.
 */
 void processMovieFile(char* filePath, int* numMovies){
    char *currLine = NULL;
    size_t len = 0;

    // Open the specified file for reading only
    FILE *movieFile = fopen(filePath, "r");

    // Read the file line by line
    while(getline(&currLine, &len, movieFile) != -1)
    {
        printf("%s", currLine);
        *numMovies += 1;
    }
    // subtract header line from movie count
    *numMovies = *numMovies - 1;  
    // Free the memory allocated by getline for currLine
    free(currLine);
    // Close the file
    fclose(movieFile);
}

void searchMovieYear(int* year){

}

/**
 * 
 */
int main ( int argc, char **argv ){
    if (argc < 2)
    {
        printf("You must provide the name of the file to process\n");
        printf("Example usage: ./movies movies.csv\n");
        return EXIT_FAILURE;
    }

    /*define a structure movie with elements title, year, languages, rating*/
    struct movie{
        char* title;
        int year;
        char* languages[5];
        double rating;
        struct movie *next;
    };

    int movieCount = 0;
    processMovieFile(argv[1], &movieCount);
    char* filePath = argv[1];
    printf("\nProcessed file %s and parsed data for %d movies\n", filePath, movieCount);
  
    int choiceNum;      // holds int 1-4 representing menu choice
    int yearInput;      // holds year specified by user

    //while(1){
        printf("\n1. Show movies released in the specified year\n"
            "2. Show highest rated movie for each year\n"
            "3. Show the title and year of release of all movies in a specific language\n"
            "4. Exit from the program\n"
            "Enter a choice from 1 to 4: ");
    //}
        scanf("%d", &choiceNum);

        // enter menu choice number
        if(choiceNum==1){
            printf("Enter the year for which you want to see movies: ");
            scanf("%d", &yearInput);
        }

        else if(choiceNum==2){

        }

        else if(choiceNum==3){

        }

        else if(choiceNum==4){
            return EXIT_SUCCESS;
        }

        else{
            printf("You entered an incorrect choice. Try again.\n");
        }

    return EXIT_SUCCESS;
}
