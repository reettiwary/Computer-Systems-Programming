#include "sudoku.h"

//-------------------------------------------------------------------------------------------------
// Start here to work on your MP7
//-------------------------------------------------------------------------------------------------

// You are free to declare any private functions if needed.

//Introduction Paragraph:
//The point of this program is to implement a C program to solve the Sudoku puzzle using recursive backtracking. 
//How we did this program was to implement a code through the following functions to see that every block is filled with a correct number. Additionally, 
//the number can only be repeated once within the 3x3 zone on every row and column of the sudoku. The functions consisted of is_val_in_row, is_val_in_col,
//is_val_in_3x3_zone, is_val_valid, and we created a function assignedvalues, and the other functions that were given solve_sudoku, print_sudoku, parsue_sudoku. 


//Group Members: shreyav3, tkarim3

// Function: is_val_in_row
// Return true if "val" already existed in ith row of array sudoku.
int is_val_in_row(const int val, const int i, const int sudoku[9][9]) {

  assert(i>=0 && i<9); //given

  // BEG TODO
  int y; //initialize the column variable
  
  //create a for loop where we set the column variable y to 0 and as y is less than or equal to 8
  //increment y by 1, and navigate through the conditional statement
  for(y = 0; y <= 8; y++){
  
  //conditional statement where we see if val is equal to the value of the sudoku array with column
  if(val == sudoku[i][y]){
  return 1; //then return 1
  }
  }
  
  return 0; //return 0
  // END TODO
  
}

// Function: is_val_in_col
// Return true if "val" already existed in jth column of array sudoku.
int is_val_in_col(const int val, const int j, const int sudoku[9][9]) {

  assert(j>=0 && j<9); //given

  // BEG TODO
  int x; //initialize the row variable
  
  //create a for loop where row variable x is set to 0 and as x is less than or equal to 8 
  //increment x by 1, and navigate through the conditional statement just as the code for column
  for(x = 0; x <= 8; x++){
  
  //conditional statement where we see if val is equal to the value of the sudoku array with row
  if(val == sudoku[x][j]){
  return 1; // then return 1
  }
  }
  
  return 0; // return 0 
  // END TODO
}

// Function: is_val_in_3x3_zone
// Return true if val already existed in the 3x3 zone corresponding to (i, j)
int is_val_in_3x3_zone(const int val, const int i, const int j, const int sudoku[9][9]) {
   
  assert(i>=0 && i<9); //given
  int x, y; //here we reintialize the x and y variables 
  int init_x = 3 * int(i / 3); // here we take the sudoku block and cut it down into nine 3 block by 3 block 
  int init_y = 3 * int(j / 3); // then we start checking if val is in the 3x3 zone by it starting from the leftest top most block 
  
  // BEG TODO
  
  //create a for loop where we set x to the init_x current value and as long as x is less than and equal to init_x's current value plus 2, x will be incremented
  for(x = init_x; x <= init_x + 2; x++){ 
  
  //while in the first loop accessing the row, we can do the same thing where we set y to the init_y current value and as long as y is less than or 
  //equal to init_y's current value plus 2, y will be incremented 
  for(y = init_y; y <= init_y + 2; y++){
  
  //while in this loop, we can set to the conditional statement and if val is equal to the sudoku array value at x and y 
  if(val == sudoku[x][y]){
  return 1; //then the program can return the correct output, return 1 
  }
  }
  }
  
  return 0; // return 0
  // END TODO
}

// Function: is_val_valid
// Return true if the val is can be filled in the given entry.
int is_val_valid(const int val, const int i, const int j, const int sudoku[9][9]) {

  assert(i>=0 && i<9 && j>=0 && j<9); //given

  // BEG TODO
  
  //here we set a conditional statement where we can call the following functions and the current values it is at and if it is equal to 1 it is ORed with 
  //another call to a function repeated for the third function as well
  
  //so if the function value at is_val_in_row is equal 1 and is ORed with the function value at is_val_in_col if that is equal to 1 and is ORed with the third 
  //function call is_val_in_3x3_zone that may be equal to 1 then the program can return a 0
  if((is_val_in_row(val, i, sudoku) == 1) || (is_val_in_col(val, j, sudoku) == 1) || (is_val_in_3x3_zone(val, i, j, sudoku) == 1)){ 
  return 0; //then returns a 0
  }
  return 1; //else return a 1 
  // END TODO
}

//here my group created and added a new function called assignedvalues where we can check if the specific blocks of the sudoku has a number placed within it 
int assignedvalues(int sudoku[9][9]){
int i, j; //we reinitialize i and j again here 

//here we set a for loop where we can navigate through the i as long as it is set to 0 and less than or equal to 8 then it can increment as it steps through
//the code
for(i = 0; i <= 8; i++){ 

//we set another for loop here where we can navigate through j as long as it is set to 0 and is less than or equal to 8 then it can increment as it steps through
//the code when it reaches the conditional statement
for(j = 0; j <= 8; j++){

//here we set a conditional statement where if the value at sudoku array is equal to 0
if (sudoku[i][j] == 0){
return 0; //then we return a 0
}
}
}
return 1; //return 1 if the individual blocks have a number within it 
}

// Procedure: solve_sudoku
// Solve the given sudoku instance.
int solve_sudoku(int sudoku[9][9]) {

  // BEG TODO.
  int i, j, x, y, num; //here we re-initialize the variables we have used throughout this program then introduce another variable called num
  if (assignedvalues(sudoku) == 1){ //then we set a conditional statement where we call the function name entering sudoku and if that is equal to 1
  return 1; //then we return a 1 
  }
  
  //create an else conditional statement 
  else{
  
  //where we set a for loop and navigate through the code 
  //so for i being equal to 0 as long as it is less than or equal to 8, then we can increment i by 1
  for(i = 0; i <= 8; i++){ 
  
  //we step to the next for loop where as long as j is equal to 0 and is less than or equal to 8, then we can increment j by 1
  for(j = 0; j <= 8; j++){
  
  //we then set a conditional statement where if the sudoku array is equal to 0
  if(sudoku[i][j] == 0){
  
  //then the current variables are set to the current value of i and j for x and y
  x = i; //here x is set to the current value at i
  
  y = j; //here y is set to the current value at j
  
  i = 9; //here we then set i to 9
  
  j = 9; //here we then set j to 9 
  }
 }
}
}

//then we create another for loop where we start off num being 1 and as long num is less than or equal to 9, then we can increment num a we move on through the code
for (num = 1; num <= 9; num++){ 

//here we set a conditional statement where if the function we call is_val_valid is equal to 1
if(is_val_valid(num, x, y, sudoku) == 1){

//then the sudoku array at x and y i set to the current value at num
sudoku[x][y] = num;

//then we set a conditional statement where if the function we call solve_sudoku is equal to 1  
if(solve_sudoku(sudoku) == 1){

return 1; //then we return a 1
}
sudoku[x][y] = 0; //then sudoku array at x and y is set to 0
}
}


  return 0; //return a 0
  // END TODO.
}

//given 

// Procedure: print_sudoku
void print_sudoku(int sudoku[9][9])
{
  int i, j;
  for(i=0; i<9; i++) {
    for(j=0; j<9; j++) {
      printf("%2d", sudoku[i][j]);
    }
    printf("\n");
  }
}

//given

// Procedure: parse_sudoku
void parse_sudoku(const char fpath[], int sudoku[9][9]) {
  FILE *reader = fopen(fpath, "r");
  assert(reader != NULL);
  int i, j;
  for(i=0; i<9; i++) {
    for(j=0; j<9; j++) {
      fscanf(reader, "%d", &sudoku[i][j]);
    }
  }
  fclose(reader);
}





