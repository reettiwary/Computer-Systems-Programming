//Intro Paragraph:
//This is a program which is Game of Life. Throughout the program an array is utilized to pose as the board game.
//Game of Life's as a game itself has different rules and conditions which is found on the wiki. However in this program
//every x and y (row and column wise element) makes sure it counts the number of live neighbors, this is done through the first fucntion countLiveNeighbor. 
//The function then allows it to traverse and move on to next criteria of the Game of Life to work. 
//updateBoard function is used to first check if the board game is consistent with its values and if it is necessary to leave the program/and or finish the game.
//Finally, the aliveStable function helps along with updateBoard to create a new comparing board game, comparing with the old values, updating to the new values.
//Essentially, traversing through arrays and pointers would allow each and every x and y, row and column values to step through Game of Life rules. 

//partners: shreyav3 

/*
 * countLiveNeighbor
 * Inputs:
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * row: the row of the cell that needs to count alive neighbors.
 * col: the col of the cell that needs to count alive neighbors.
 * Output:
 * return the number of alive neighbors. There are at most eight neighbors.
 * Pay attention for the edge and corner cells, they have less neighbors.
 */

int countLiveNeighbor(int* board, int boardRowSize, int boardColSize, int row, int col){
  int live = 0; //initializes the variable called live which increases throughout the program, serves as the output
  int x, y; //intitalizes the variables x and y, x will be in regards to the row and y will be in regards to the column

  //creates a for loop with conditionals to proceed to the next for loop
  //we create a for loop with x being related with the row
for(x = row - 1; x <= row + 1; x++){

  //set a condition, if x is greater than or equal to 0 AND x is less than or equal to the current boardRowSize - 1
  //then proceed onto the next loop
  if((x >= 0) && (x <= boardRowSize - 1)){

    //create a for loop for the y with regards with the column
    for(y = col - 1; y <= col + 1; y++){

      //create a nested if statement/conditionals
      //if y is greater than or equal to 0 AND y is less than or equal to current boardColSize -1
      //then proceed onto the next conditional statement
      if((y >= 0) && (y <= boardColSize - 1)){

	//set up another conditional statement where board + x times the current boardColSize + y, and if the pointer equalizes to 1
	if(*(board + x * boardColSize + y) == 1){
	  live++; //increment live variable by 1
	}
      }
    }
  }
 }

//update the live variable by setting up the current value of live - the pointer value of board + row * boardColSize + col
live = live - *(board + row * boardColSize + col);

 return live; //return the new value of live 
}

/*
 * Update the game board to the next step.
 * Input: 
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * Output: board is updated with new values for next step.
 */
void updateBoard(int* board, int boardRowSize, int boardColSize) {
  int live; //reinitialize the live variable here 
  int newboardgame[boardRowSize * boardColSize]; //initiliaze a new array with boardRowSize and boardColSize
  int x, y; //reinitialize the x and y variables here 

  //create a two way for loop where x is again set to 0, if x is less than or equal to boardRowSize -1 it goes through the program and increments
  for(x = 0; x <= boardRowSize - 1; x++){

    //heads to the next for loop if set conditions are met, if y meets the same requirments with regards to column
    for(y=0; y <= boardColSize - 1; y++){

      //then the newboardgame array is equal to the pointer where it points to the value of  board + x * boardColSize + y
      newboardgame[x * boardColSize + y] = *(board + x * boardColSize + y);
    }
}
  
  //we create another for loop where we do the same thing repeated above in order for our program to work with the various row 
  //and column areas, we make sure that it is not overlapping or counting the corners twice 
  for(x = 0; x <= boardRowSize - 1; x++){
    for(y = 0; y <= boardColSize - 1; y++){

      //here instead we set live's value to be referencing to the countLiveNeighbor function and repeat the process there
      live = countLiveNeighbor(board, boardRowSize, boardColSize, x, y);

      //here we set a conditional if-statement where if live's current value is less than 2 OR greater than 3,
      //then newboardgame[x * boardColSize +y] array is set to 0
      if((live < 2) || (live > 3)){
	newboardgame[x * boardColSize +y] = 0; //if conditions are met, set to 0
      }

      //then we add another conditional statment where if live's current value is equal to 3
      //then newboardgame array is set to 1
      if (live == 3){
	newboardgame[x * boardColSize +y] = 1; //if conditons are met, set to 1
      }
    }
  }

  //afterwards we repeated the same two for loops, to keep in check that our boardgame and the gameoflife compilates correctly
  for(x = 0; x <= boardRowSize - 1; x++){
    for(y = 0; y <= boardColSize -1; y++){

      //here we set the pointer to the array value of newboardgame[x * boardColSize + y]
      *(board + x * boardColSize + y) = newboardgame[x * boardColSize + y];
    }
  }
  return; //then we return back to the program
}

/*
 * aliveStable
 * Checks if the alive cells stay the same for next step
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * Output: return 1 if the alive cells for next step is exactly the same with 
 * current step or there is no alive cells at all.
 * return 0 if the alive cells change for the next step.
 */ 
int aliveStable(int* board, int boardRowSize, int boardColSize){
  int alive = 1; //here we set a new variable called alive setting it to 1
  int live = 0; // again since it is a new function we reinitialize our live variable to 0
  int boardcomparison[boardRowSize * boardColSize]; //here we set a new array called boardcomparison[boardRowSize * boardColSize]
  int x, y; //here we reinitialize our x and y values 
  
  //repeat the same for loops like we have done previously 
  for(x = 0; x <= boardRowSize - 1; x++){
    for(y = 0; y <= boardColSize - 1; y++){

      //here we set the board comparison array to the point of board + x * boardColSize + y 
      boardcomparison[x * boardColSize + y] = *(board + x * boardColSize + y);
    }
  }

  //another for loop is added here similar to the one we previously did, we have to keep doin this to update our boardgame 
  for (x = 0; x <= boardRowSize - 1; x++){
    for(y = 0; y <= boardColSize - 1; y++){

      //here we set the live variable to the countive Neighbor function's return value 
      live = countLiveNeighbor (board, boardRowSize, boardColSize, x, y);

      //then we set a condition statement, if the current value of live is less than 2
      if(live < 2){
	boardcomparison[x * boardColSize + y] = 0; //then the boardcomparision array is set to 0
      }
      //if the current value of live is exactly 3
      if(live == 3){
	boardcomparison[x * boardColSize + y] = 1; //then the boardcomparison array is set to 1
      }
      //if the current value of live is greater than 3 
      if(live > 3){
	boardcomparison[x * boardColSize + y] = 0; //then the boardcomparison array is set to 0
      }
    }
  }

  //then we repeat the same for loops for the last time
  for(x = 0; x <= boardRowSize - 1; x++){
    for(y = 0; y  <= boardColSize - 1; y++){

      //however we set a conditional statement here where if the board comparison array value is not equal to the pointer of board + x * boardColSize + y
      if(boardcomparison[x * boardColSize + y] != *(board + x * boardColSize + y)){
	alive = 0; //then alive is reset to 0
      }
    }
  }
  return alive; //here we return the current value of alive at the enf of the fuction

}

				
				
			

