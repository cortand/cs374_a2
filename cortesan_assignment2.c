#include <stdio.h>
#include <stdlib.h> // for atoi,  EXIT_SUCCESS and EXIT_FAILURE
#include <string.h> // for strtok_r

/*define a structure movie with elements title, year, languages, rating*/
struct movie{
    char* title;
    int year;
    char* languages[5];
    double rating;
    struct movie *next;     // pointer to next node
};

// define the head pointer
struct movie* head = NULL;

void parseCSVline(char* CSVline){
    struct movie* newMovie = calloc(1, sizeof(struct movie));
    newMovie->next = NULL;
    
    char* CSVlineCopy;
    CSVlineCopy = strdup(CSVline);

    char* savePtr1;
    char* titleToken = strtok_r(CSVlineCopy, ",", &savePtr1);
    newMovie->title = strdup(titleToken);

    char* yearToken = strtok_r(NULL, ",", &savePtr1);
    newMovie->year = atoi(yearToken);

    char* savePtr2;
    char* languagesToken = strtok_r(NULL, ",", &savePtr1);
    languagesToken++;   // advance pointer by 1 to exclude "["
    int len = strlen(languagesToken); // find the string length
    languagesToken[len - 1] = '\0'; // replace "]" with string terminator
    int i = 0;
    char* langToken = strtok_r(languagesToken, ";", &savePtr2);
    while (langToken != NULL && i <5) {
        newMovie->languages[i] = strdup(langToken);
        i++;
        langToken = strtok_r(NULL, ";", &savePtr2);
    }
    
    char* ratingToken = strtok_r(NULL, ",", &savePtr1);
    newMovie->rating = strtof(ratingToken, NULL);
   
    free(CSVlineCopy);

    return newMovie;

 }
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

    int firstLine = 1;
    // Read the file line by line
    while(getline(&currLine, &len, movieFile) != -1)
    {
        printf("%s", currLine);

        if (firstLine) {
            firstLine = 0;
            continue;
        }

        // intead of print, use malloc and parse strings to get title, year, lang, rating
        // make local variable that gets populated with parsed data and plug into linked list
        struct movie* node = parseCSVline(currLine);

        node->next = head;
        head = node;
    
        *numMovies += 1;
    }
    // subtract header line from movie count
    *numMovies = *numMovies - 1;  
    // Free the memory allocated by getline for currLine
    free(currLine);
    // Close the file
    fclose(movieFile);
}


void searchMoviesByYear(int targetYear){
    // define pointer to a new node and initialize to first node of the linked list (head)
    struct movie* newNode = head;
    int movieFound = 0;
   
    // check if there is a movie released in the desired year
    while (newNode != NULL) {
        if (newNode->year == targetYear) {
            printf("%s\n", newNode->title);
            movieFound = 1;
        }
        newNode = newNode->next;        // advance node pointer
    }
        if (!movieFound) {
            printf("No data about movies released in the year %d\n", targetYear);
    }
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

    int movieCount = 0;
    processMovieFile(argv[1], &movieCount);
    char* filePath = argv[1];
    printf("\nProcessed file %s and parsed data for %d movies\n", filePath, movieCount);
  
    int choiceNum;      // holds int 1-4 representing menu choice
    int yearInput;      // holds year specified by user

    while(1){
        printf("\n1. Show movies released in the specified year\n"
            "2. Show highest rated movie for each year\n"
            "3. Show the title and year of release of all movies in a specific language\n"
            "4. Exit from the program\n"
            "Enter a choice from 1 to 4: ");
        scanf("%d", &choiceNum);

        // enter menu choice number
        if(choiceNum==1){
            printf("Enter the year for which you want to see movies: ");
            scanf("%d", &yearInput);
            searchMoviesByYear(yearInput);
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
    }
    return EXIT_SUCCESS;
}
