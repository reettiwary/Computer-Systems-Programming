#include <stdio.h>
#include <stdlib.h>
#include "maze.h"

//Intro Paragraph:
//This is a program which serves as a maze solver utlizing recursive steps and with the first depth search. It also uses a series of functions to make sure
//that the correct solution can be verified. How we go through the program is understanding that the output onto the monitor is in fact the intial width and 
//height of the maze alongside its structure. By referencing other files within the memory and data we can see that within the maze '%' is used to pose as 
//walls while the space serves as an empty cell. Additionally, 'S' serves as the start of the maze for the user to understand while 'E' serves as the end of the
//maze. We modified different functions alongside making sure that the call to reference in the file system was allowing our maze to be displayed and accurate. 

//partners: shreyav3, tkarim3

/*
 * createMaze -- Creates and fills a maze structure from the given file
 * INPUTS:       fileName - character array containing the name of the maze file
 * OUTPUTS:      None 
 * RETURN:       A filled maze structure that represents the contents of the input file
 * SIDE EFFECTS: None
 */
maze_t * createMaze(char * fileName)
{
    // Your code here. Make sure to replace following line with your own code.
  int x, y, row, col; //initialize variables x, y, row, col 
  char z; //create/declare character z 
  FILE *reader = fopen(fileName, "r"); //create a stream in order to map the maze by utilizing file with pointer reader
    
  fscanf(reader, "%d %d", &col, &row); //read the column and row data provided in the file

  maze_t *mazenew = malloc(sizeof(maze_t)); //allocate the memory for the maze_t function and its structure within the program

  mazenew -> height = row; //structure for the row 
  mazenew -> width = col; //structure for the column 

  mazenew -> cells = (char **)malloc(row * sizeof(char *)); //here we allocate the memory for the cells within the program

  //create a for loop to go through the allocation structure and allow data from the memory to be written onto the program
  //so when x is 0 as it is less than row, go through the iteration of cells and increment x
    for(x = 0; x < row; x++){
      mazenew -> cells[x] = (char *)malloc(col * sizeof(char));
    }

    //create another for loop, for accessing the row as well as the column in order to copy maze onto the program file 
    for(x = 0; x < row; x++){
    for(y = 0; y < col; y++){

      z = fgetc(reader); //here we copy the maze into the file 

      //we then create a conditional statement to map out how to go through the iteration and loops
      //if z is not equal to the newline character, then duplication equals to the current value set at z
    if(z != '\n'){
    mazenew -> cells[x][y] = z;
    }

    //then we add another part of the conditional statement 
    else{
      y--; //if it is a newline character, we do not save into the data and then loop through the iteration
    }

    //create another nested if conditional statement
    //if the column(y) variable is greater than or equal to 0 
    if(y >= 0){

      //and if the the mazenew is set to the start point 
    if(mazenew -> cells[x][y] == START){

      //then the mazenew data is set to x which is correlated with the row
    mazenew -> startRow = x;

    //and the mazenew data is set to the y variable which is correlated with the column data 
    mazenew -> startColumn = y;
    }

    //we then create a conditional statement to access the end point of the program through the maze data 
    if(mazenew -> cells[x][y] == END){

      //here we do the similar way where we set the data to the current value of x
    mazenew -> endRow = x;

    //similarily, the data of mazenew is with y which is correlated with the endColumn
    mazenew -> endColumn = y;
    }
    }
    }
    }

    fclose(reader); //we close the stream of the mazenew data here
    
    return mazenew; //then we return the data back into the program
}

/*
 * destroyMaze -- Frees all memory associated with the maze structure, including the structure itself
 * INPUTS:        maze -- pointer to maze structure that contains all necessary information 
 * OUTPUTS:       None
 * RETURN:        None
 * SIDE EFFECTS:  All memory that has been allocated for the maze is freed
 */
void destroyMaze(maze_t * maze)
{
    // Your code here.
  int x; //we re-intialize the variable of x here 

  //here is the for loop where as x is 0, and as x is less than maze is set to the height data then the iteration
    for(x = 0; x < maze -> height; x++){

      free(maze -> cells[x]); //simply accesses all the mallocs and effects into the maze creation
    }

    free(maze -> cells); //here we can use the free access data with the cells 

    free(maze); //reference

    maze = NULL; //here we set the maze to NULL 
}

/*
 * printMaze --  Prints out the maze in a human readable format (should look like examples)
 * INPUTS:       maze -- pointer to maze structure that contains all necessary information 
 *               width -- width of the maze
 *               height -- height of the maze
 * OUTPUTS:      None
 * RETURN:       None
 * SIDE EFFECTS: Prints the maze to the console
 */
void printMaze(maze_t * maze)
{
    // Your code here.
  int x, y; //here we reinitialize the variables x and y 

  printf("%d %d\n", maze -> width, maze -> height); //then we create a print statement in which we print out the data we requested

  //then we create a nested for loop in which as x is 0 and less than the data reference to maze and its height, x will increment and move through the iteration 
    for(x = 0; x < maze -> height; x++){

      //then we create another for loop in which y is 0 and as it is less than the data reference to maze and its width, y will increment and move through the
      //iteration, it will go through the print statements
    for(y = 0; y < maze -> width; y++){

      printf("%c", maze -> cells[x][y]); //then the print statements will be executed while the maze data is set to cells array value of x and y
    }

    printf("\n"); //here we add the print line statement where we print a newline after every row
    }
}

/*
 * solveMazeManhattanDFS -- recursively solves the maze using depth first search,
 * INPUTS:               maze -- pointer to maze structure with all necessary maze information
 *                       col -- the column of the cell currently beinging visited within the maze
 *                       row -- the row of the cell currently being visited within the maze
 * OUTPUTS:              None
 * RETURNS:              0 if the maze is unsolvable, 1 if it is solved
 * SIDE EFFECTS:         Marks maze cells as visited or part of the solution path
 */ 
int solveMazeDFS(maze_t * maze, int col, int row)
{
    // Your code here. Make sure to replace following line with your own code.

  //set a conditional statement where if the column value is less than 0 OR the column current value is greater than or equal to maze data is set to width data
  //OR row is less than 0 OR row is greater than or equal to the maze data set to the height data as well
    if(col < 0 || col >= maze -> width || row < 0 || row >= maze -> height){

      return 0; //then it is returning false and is out of the maze data bounds 
    }

    //here we set another conditional statement where if the maze data is set to the cells at row and col and if that equals to WALL reference OR
    //maze value data reference is set to the cells and row and col that equals to PATH OR maze reference at row and col is equal to VISITED
    if(maze -> cells[row][col] == WALL || maze -> cells[row][col] == PATH || maze -> cells[row][col] == VISITED){

      return 0; //then the code returns 0, false since it is not an empty cell within the structure
    }
    
    //we then set a conditional statement where the structure of maze if the col is equal to maze and is refernced to the endColumn data AND row is equal to the 
    //maze reference to endRow data 
    if(col == maze -> endColumn && row == maze -> endRow){

      //then we restore the starting point of the maze and its sequence before it reaches the very end through the program
    maze -> cells[maze -> startRow][maze -> startColumn] = START;
    return 1; //returning a 1
    }
    
    //here we set a bunch of conditional statements contuining off for the code to be able to access the data points and reference successfully

    //here we set the column and row into the solution path of the maze 
    if(maze -> cells[row][col] != END){
      maze -> cells[row][col] = PATH; //maze is basically written to start off with PATH being the starting point and being restored into the structure last
    }
    
    //if the direction is left or in any other direction then the return statement will always return a 1 and be true

    //here we see the left movement as the above comment
    if(solveMazeDFS(maze, col - 1, row)){

      return 1; //returning true value
    }
    
    //where row is being in another direction
    if(solveMazeDFS(maze, col, row - 1)){

      return 1; //returning true value
    }
    
    //where column is being in another directions in the positive side 
    if(solveMazeDFS(maze, col + 1, row)){

      return 1; //returning true value
    }
    
    //where the row is being in another direction in the positive side
    if(solveMazeDFS(maze, col, row + 1)){

      return 1; //returning true value
    }
    
    //then we set the conditional statement where accessing the maze data cell at the current row and column if it is not equal to the START reference AND 
    //the maze data cell reference at the current row and column if it is not equal to the END reference then 
    if(maze -> cells[row][col] != START && maze -> cells[row][col] != END){

      maze -> cells[row][col] = VISITED; //the row and column data value poses as unmarked within the solution and and turns/sets into VISTED reference
    }
    
    return 0; //we then return a 0 at the end of the loop/program
}
