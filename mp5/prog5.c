/*      
 *
 * prog5.c - source file adapted from UIUC ECE198KL Spring 2013 Program 4
 *           student code -- GOLD VERSION by Steven S. Lumetta
 */


/*
 * The functions that you must write are defined in the header file.
 * Blank function prototypes with explanatory headers are provided
 * in this file to help you get started.
 */

/*Intro Paragraph:
 *The goal of this MP was to utlize three funcions and be able to generate a guessing game with the correct scores/ accuracy.
 *Three functions were used set_seed allows the user to be able to enter an integer through scanf. Through the scanf function, if 
 *it does not return 1 then there is an invalid message indicated on the monitor. After set_seed, the post  is checked and if it is empty, seed 
 *can be instilled through the function code, returning a 1.
 *
 *start_game utlizes the alogrithm where there is an array that keeps track of the solution numbers entered. From 0-7 an integer can be inputted and through the 
 *array, the program find the index to make the Wheel of Fortune pool string which keeps the string words. 
 *
 *make_guess makes sure that the user is able to guess at least 4 guesses, if not then user sees an invalid message printed. Pool then checks to make sure that 
 *guesses from the user is stored there. The guesses must be correct not only through accuracy, but through the placement. Once that is checked the program 
 *calculates the score for the user. Essentially, the program has a set in max_score. So user's score is compared with max_score and if it exceeds then the 
 *program should store the new highest score. 
 */

//Members: shreyav3

//given
#include <stdio.h>
#include <stdlib.h>

#include "prog5.h"

int guess_number;
int max_score;
char solutions[4][10];
char* pool[] = {"Vader", "Padme", "R2-D2", "C-3PO", "Jabba", "Dooku", "Lando", "Snoke",};
/* Show guessing pool -- This function prints "pool" to stdout
 * INPUT: none
 * OUTPUT: none
 */
void print_pool() {
    printf("Valid term to guess:\n\t");
    for(int i = 0; i < 8 ; ++i) {
        printf("%s ", pool[i]);
    }
    printf("\n");
}

/*
 * is_valid -- This function checks whether a string is valid
 * INPUTS: str -- a string to be checked
 * OUTPUTS: none
 * RETURN VALUE: 0 if str is invalid, or 1 if str is valid
 * SIDE EFFECTS: none
 */

//given
int is_valid(char* str) {
    int i = 0;
    if (str == NULL) {
        return 0;
    }
    for (i = 0; i < 8; i++) {
        if (strcmp(str, pool[i]) == 0) {
            return 1;
        }
    }
    return 0;
}


/*
 * set_seed -- This function sets the seed value for pseudorandom
 * number generation based on the number the user types.
 * The input entered by the user is already stored in the string seed_str by the code in main.c.
 * This function should use the function sscanf to find the integer seed value from the 
 * string seed_str, then initialize the random number generator by calling srand with the integer
 * seed value. To be valid, exactly one integer must be entered by the user, anything else is invalid. 
 * INPUTS: seed_str -- a string (array of characters) entered by the user, containing the random seed
 * OUTPUTS: none
 * RETURN VALUE: 0 if the given string is invalid (string contains anything
 *               other than a single integer), or 1 if string is valid (contains one integer)
 * SIDE EFFECTS: initializes pseudo-random number generation using the function srand. Prints "set_seed: invalid seed\n"
 *               if string is invalid. Prints nothing if it is valid.
 */
int set_seed (const char seed_str[]) {
//    Example of how to use sscanf to read a single integer and check for anything other than the integer
//    "int seed" will contain the number typed by the user (if any) and the string "post" will contain anything after the integer
//    The user should enter only an integer, and nothing else, so we will check that only "seed" is read. 
//    We declare
//    int seed;
//    char post[2];
//    The sscanf statement below reads the integer into seed. 
//    sscanf (seed_str, "%d%1s", &seed, post)
//    If there is no integer, seed will not be set. If something else is read after the integer, it will go into "post".
//    The return value of sscanf indicates the number of items read succesfully.
//    When the user has typed in only an integer, only 1 item should be read sucessfully. 
//    Check that the return value is 1 to ensure the user enters only an integer. 
//    Feel free to uncomment these statements, modify them, or delete these comments as necessary. 
//    You may need to change the return statement below
    int seed; //given
    char post[2]; //given
    post[0] = 0; //set pos[0] to a number

    //checks to see if the seed may be invalid 
    if (sscanf (seed_str, "%d%1s", &seed, post) != 1) { 
      // your code here
      printf("set_seed: invalid seed\n"); //prints the error message to displayed onto the monitor
      return 0; //returns to 0 if the set_seed function does not work
    }
    // your code here
    srand(seed); //else sets seed
    return 1; //returns 1 which means function was successful
}


/*
 * start_game -- This function is called by main.c after set_seed but before the user makes guesses.
 *               This function creates the four solution numbers using the approach
 *               described in the wiki specification (using rand())
 *               The four solution numbers should be stored in the static variables defined above. 
 *               The values at the pointers should also be set to the solution numbers.
 *               The guess_number should be initialized to 1 (to indicate the first guess)
 *               The score should be initialized to -1.  
 * INPUTS: none
 * OUTPUTS: none
 * RETURN VALUE: none
 * SIDE EFFECTS: records the solution in the static solution variables for use by make_guess, set guess_number
 */
void start_game () {
    //your code here
  for(int i = 0; i<4; i++){ //utlize a for loop to set conditions and allow the number to be able to be accessed
    int number = rand()%8; //by modulo, 0-7 integers are set in the range
    strcpy(solutions[i],pool[number]); // copies the string from the pool in order to correlate it to the solutions 
  }

  guess_number = 1; //from description both guess_number and max_score are initialized and set 
  max_score = -1; 
}

/*
 * make_guess -- This function is called by main.c after the user types in a guess.
 *               The guess is stored in the string guess_str. 
 *               The function must calculate the number of perfect and misplaced matches
 *               for a guess, given the solution recorded earlier by start_game
 *               The guess must be valid (contain only 4 strings from pool). If it is valid
 *               the number of correct and incorrect matches should be printed, using the following format
 *               "With guess %d, you got %d perfect matches and %d misplaced matches.\n"
 *               If valid, the guess_number should be incremented.
 *               If invalid, the error message "make_guess: invalid guess\n" should be printed and 0 returned.
 *               For an invalid guess, the guess_number is not incremented.
 * INPUTS: guess_str -- a string consisting of the guess typed by the user
 * OUTPUTS: none
 * RETURN VALUE: 2 if guess string is valid and got all 4 perfect matches, or 1 if the guess string is valid, 
 *               or 0 if it is invalid
 * SIDE EFFECTS: prints (using printf) the number of matches found and increments guess_number(valid guess) 
 *               or an error message (invalid guess)
 *               (NOTE: the output format MUST MATCH EXACTLY, check the wiki writeup)
 */
int make_guess (const char guess_str[]) {
  // your code here
  char guesses_array[4][10]; //an array where the guesses will be stored is set
  char extra_char[2]; // an array which will store the extra characters can be set with 2 similar to post[2] 
 
  if(sscanf(guess_str,"%s %s %s %s %1s", guesses_array[0], guesses_array[1], guesses_array[2], guesses_array[3], extra_char)!= 4){ //splits the guess_str properly
    //if more than 4 guesses are made then prints an error message if it does exceed by alot
    printf("make_guess: invalid guess\n");
    return 0;
}

  for (int x = 0; x<4;  x++){ //sets up a for loop to check if the guesses are matching up with the pool for accuracy and placement 
    if(is_valid(guesses_array[x])==0){ 
	printf("make_guess: invalid guess\n");
	return 0;
      }
  }
   
    //Points and Scores are validated here 

  int correct_guesses = 0; //intializes the number of correct guesses made 
  int correct_placement = 0; //intializes the placement number if it matches with the soltutions 
    
  int storedguesses[4] = {0,0,0,0}; //sets up an array for storing the guesses 
  int stored_solution[4] = {0,0,0,0}; //sets up an array for storing the correct guessing within solutions 

  for(int s = 0; s<4; s++){ //here we check our guesses to see if they match up with the program's set in output
    if(strcmp(guesses_array[s],solutions[s])==0){ //here we see if the user's guesses are in the correct order
      correct_placement ++; //if it is, increase the placment by 1
      storedguesses[s] = 1; //stored guesses keeps the stored value at the index equal to 1
      stored_solution[s] = 1; //same with the solutions array
	}
    }

  for (int s = 0; s<4; s++){ //here we create the same loop to make sure that our inital array is storing current and updated values 
    if(storedguesses[s]==0){ //if the index value at the array is equal to 0 then it goes into a another forloop with a nested if statement
      for(int t = 0; t<4; t++){ //here the solutions are iterated and checked to see if the computer is storing the solutions and updating it
	if(stored_solution[t]==0){ //if the index value at the solutions array is equal to 0 then 
	  if(strcmp(guesses_array[s],solutions[t])==0){ //correct value from user and computer are checked 
	    correct_guesses ++; //correct guesses increases by 1.
	    storedguesses[s] = 1; //stored guesses keeps the stored value at the index equal to 1
	    stored_solution[t] = 1; //same with the solutions array
	    break; // breaks out of the program 
		}
	    }
	  }
	}
      }

  printf("With guess %d, you got %d perfect matches and %d misplaced matches\n", guess_number, correct_placement, correct_guesses); //prints the statment to user
	guess_number++; // guess number is incremented here
	int maxscore_sub = 0; //initializes the user score to be compared with the computer's score
	maxscore_sub = 1000 * correct_placement + 100 * correct_guesses; //calculates the score accurately
	if(maxscore_sub > max_score){ // if the user's score is greater than the max score 
	  max_score = maxscore_sub; // then the max score which is from computer is set to the user's highest score 
	}
	printf("Your score is %d and current max score is %d.\n", maxscore_sub, max_score); //print statement for the user to be updated with their score
	if(max_score == 4000){ //if the max score is equal to the 4000 then
	  return 2; // 2 is signaled indicating that the user was accurate in all guesses 
	}
	else{
	  return 1; // returns 1 if  the user failed to guess correctly 
	}
	return 0; // return 0
      }
		  



