#include "game.h"

//Intro Paragraph:
//This program is a game set out to users to play around. Essentially the game starts off with the user being able to request for a random tile of 
//2 or 4 to be implemented onto the gameboard. Theuser is requested to use the w, s, a, d keys to play around with the numbers and mimic the 2048 
//game. When the user prompts the slide indication, once the two numbers of the exact value are combined to confronted with each other, then a single tile is 
//formed in which the value is the result of the two tiles which were originally combined with each other. The program contains functions 4 being key to the 
//w, s, a, d keys; through changing the keys, various results can occurr and the end result can be differed. We utilized several pointer to pointer applications
//for this to be successful. 

//Group Members: shreyav3, tkasim3


game * make_game(int rows, int cols)
/*! Create an instance of a game structure with the given number of rows
    and columns, initializing elements to -1 and return a pointer
    to it. (See game.h for the specification for the game data structure) 
    The needed memory should be dynamically allocated with the malloc family
    of functions.
*/
{
    //Dynamically allocate memory for game and cells (DO NOT modify this)
    game * mygame = malloc(sizeof(game));
    mygame->cells = malloc(rows*cols*sizeof(cell));

    //YOUR CODE STARTS HERE:  Initialize all other variables in game struct
    int x = 0; //initialize variable x 

    //create a for loop in which as x is 0 and as long as it is les than the product of rows and cols combined minus 1, x will
    //iterate through as it increments by 1; it allows every cell in the game to be set to -1
    for(x = 0; x <= ((rows * cols) - 1); x++){
      *((*mygame).cells + x) = -1; //here we set the iteration aspect to be a pointer pointing to the pointer ((*mygame).cells) plus x and set it to -1
    }

    //we set both pointer to store the rows and columns into the mygame structure
    (*mygame).rows = rows; 
    (*mygame).cols = cols;

    return mygame; //then we return whatever is currently stored within the mygame
}

void remake_game(game ** _cur_game_ptr,int new_rows,int new_cols)
/*! Given a game structure that is passed by reference, change the
	game structure to have the given number of rows and columns. Initialize
	the score and all elements in the cells to -1. Make sure that any 
	memory previously allocated is not lost in this function.	
*/
{
	/*Frees dynamically allocated memory used by cells in previous game,
	 then dynamically allocates memory for cells in new game.  DO NOT MODIFY.*/
	free((*_cur_game_ptr)->cells);
	(*_cur_game_ptr)->cells = malloc(new_rows*new_cols*sizeof(cell));

	 //YOUR CODE STARTS HERE:  Re-initialize all other variables in game struct
	int x = 0; //here we reinitialize our x variable for the new function

	for(x = 0; x <= ((new_rows * new_cols) - 1); x++){ //then we repeat the same idea of reinitializing the cells to -1, but with the function set variables
	  *((**_cur_game_ptr).cells + x) = -1; //we then take a pointer to a double pointer of _cur_game_ptr.cells plus x and set it to -1
	}

	//then we re-store the new rows and columns for the current game
	(**_cur_game_ptr).rows = new_rows; 
	(**_cur_game_ptr).cols = new_cols;

	return;	//return
}

void destroy_game(game * cur_game)
/*! Deallocate any memory acquired with malloc associated with the given game instance.
    This includes any substructures the game data structure contains. Do not modify this function.*/
{
    free(cur_game->cells);
    free(cur_game);
    cur_game = NULL;
    return;
}

cell * get_cell(game * cur_game, int row, int col)
/*! Given a game, a row, and a column, return a pointer to the corresponding
    cell on the game. (See game.h for game data structure specification)
    This function should be handy for accessing game cells. Return NULL
	if the row and col coordinates do not exist.
*/
{
    //YOUR CODE STARTS HERE

  //here we decided to set conditional statements in order for the current game to locate the right column and row to return the cell potential value

  //conditional if statment, so if row is less than 0 OR row is greater than or equal to the pointer of cur_game.rows
  if(row < 0 || row >= (* cur_game).rows){
    return NULL; //then we would return a NULL
  }

  //similarily, conditional statement for column, if column is less than 0 OR column is greater than or equal to the pointer of cur_game.cols
  if(col < 0 || col >= (* cur_game).cols){
    return NULL; //then we would return a NULL
  }

  return (*cur_game).cells + row * (*cur_game).cols + col; //returns the result of pointer value of cur_game.cells plus row times pointer value of cur_game.cols
                                                           //plus column value
}

int move_w(game * cur_game)
/*!Slides all of the tiles in cur_game upwards. If a tile matches with the 
   one above it, the tiles are merged by adding their values together. When
   tiles merge, increase the score by the value of the new tile. A tile can 
   not merge twice in one turn. If sliding the tiles up does not cause any 
   cell to change value, w is an invalid move and return 0. Otherwise, return 1. 
*/
{
    //YOUR CODE STARTS HERE
  int x = 0; //reinitialize x variable to 0
  int y = 0; //initialize new variable y to 0
  int finalrow = -1; //intitialize new variable finalrow to -1
  int currentrow = -1; //initialize currentrow to -1 
  int current_sol = 0; //initialize current_sol to 0
  int modified = 0; //initialize modified to 0 

  //we then create a nested for-loop in a sense where we can navigate through all the tiles and utlize w to match the procedure as well as the results

  //we start off with y being correlated with columns so as y is 0 and less than or equal to the value of the pointer of cur_game.cols -1, y increments
  for(y = 0; y <= (*cur_game).cols - 1; y++){ 
    finalrow = -1; //as it iterates and makes sure that final row is -1

    //we do the same for loop idea  with x as it correlates with row
    for(x = 0; x <= (*cur_game).rows - 1; x++){

      //we instead add a conditional as part of the iteration to make sure that the current row value is filled and containing numbers/values within the cells
      //so if the pointer value at the result of pointer of cur_game.cells plus x times the pointer value of cur_game.cols + y is not equal to -1
      if(*((*cur_game).cells + x * (* cur_game).cols + y) != -1){

	//the the initial value at current solution will be set to 0
	current_sol = 0;

	//in order to find the current row and allow the porgram to locate it and proceed onwards we create a 
	//for loop in which as current row is set to 0 and as long as it is less than the current value of x 
	//then the current row can increment as long as it iterates through the conditional statement, find the current_sol and set it to 1 and exit the game
	for(currentrow = 0; currentrow < x; currentrow++){

	  //conditional if statment is added where we see the pointer of a result is equal to the value of -1 and if it is
	  if(*((*cur_game).cells + currentrow * (*cur_game).cols + y) == -1) {
	    current_sol = 1; //then the current solution will be set to 1
	    break; //user exits the program
	  }
	}
	
	//we then set a conditional statement to indicate that if the current solution value is equal to 1 
	if(current_sol == 1){

	  //then the pointer of the result for the first part will be set to the pointer of the result of the second part 
	  *((*cur_game).cells + currentrow * (*cur_game).cols + y) = *((*cur_game).cells + x * (*cur_game).cols + y);

	  //and the pointer of the result as we repeat from previous code above will be able to determine the current contents of row and allocate space into it
	  //where it is equal to -1 
	  *((*cur_game).cells + x * (*cur_game).cols + y) = -1;
	  modified = 1; //modified is then set to 1
	}

	//we then add a nest if-statement
	//if the current value at currentrow - 1 is not equal to current value at finalrow
	if((currentrow - 1) != finalrow){

	  //and if the both results are the same/equivalent to each other 
	  if(*((*cur_game).cells + (currentrow - 1) * (*cur_game).cols + y) == *((*cur_game).cells + currentrow * (*cur_game).cols + y)){

	    //then the row ahead of the value at currentrow will be set to the result doubled 
	    *((*cur_game).cells + (currentrow - 1) * (*cur_game).cols + y) *= 2;

	    //then the score aspect of the code is integrated and updated with the following and up-to-date result
	    (*cur_game).score += *((*cur_game).cells + (currentrow - 1) * (*cur_game).cols + y);

	    //we then make sure again that the value at currentrow is set to storing no values/being empty
	    *((*cur_game).cells + currentrow * (*cur_game).cols + y) = -1;

	    //we then set finalrow to the current value at currentrow - 1
	    finalrow = currentrow - 1;

	    //modified is then set to 1
	    modified = 1;
	  }
	}
      }
    }
  }
 
	    
  return modified; //we then return the current value at modified
};

int move_s(game * cur_game) //slide down
{
    //YOUR CODE STARTS HERE

  //we re-intialize the same variables we used in the previous function
  int x = 0;
  int y = 0;
  int finalrow = -1;
  int currentrow = -1;
  int current_sol = 0;
  int modified = 0; 
  
  //we then repeat the same idea of how we make sure that the value at finalrow is reset back to -1 
  for(y = 0; y <= (*cur_game).cols -1; y++){
    finalrow = -1;

    //create a for loop in which we can set a conditional iteration and see whether the current row value and its solution is empty or not
    for(x = (*cur_game).rows -1; x >= 0; x--){
      if(*((*cur_game).cells + x * (*cur_game).cols + y) != -1){
	current_sol = 0;

	//set another for loop with conditional statement in order to find the current solution at the cell, iterate through 
	//the conditional 
	for(currentrow = (*cur_game).rows -1; currentrow > x; currentrow--){
	  if(*((*cur_game).cells + currentrow * (*cur_game).cols + y) == -1){
	    current_sol = 1; //set current solution to 1
	    break; //break out of the program/code
	  }
	}
	
	//set the conditional where if the current solution is equal to 1 then copy the same type of method we did in the earlier function
	if(current_sol == 1){

	  //repeat the same idea changed if needed
	  *((*cur_game).cells + currentrow * (*cur_game).cols + y) = *((*cur_game).cells + x * (*cur_game).cols + y);

	  //then we repeat the same idea where the contents at row can be cleared at the cell 
	  *((*cur_game).cells + x * (*cur_game).cols + y) = -1;

	  //setting modified to 1 
	  modified = 1;
	}

	//Repeat the same type of thing we did in the previous function
	if ((currentrow + 1) != finalrow){

	  //if the pointer values are the same, repeat the same procedure 
	  if(*((*cur_game).cells + (currentrow + 1) * (*cur_game).cols + y) == *((*cur_game).cells + currentrow * (*cur_game).cols + y)){

	    *((*cur_game).cells + (currentrow + 1) * (*cur_game).cols + y) *= 2;

	    (*cur_game).score += *((*cur_game).cells + (currentrow + 1) * (*cur_game).cols + y);

	     *((*cur_game).cells + currentrow * (*cur_game).cols + y) = -1;

	     finalrow = currentrow + 1;

	     modified = 1;
	  }
	}
      }
    }
  }

	
    return modified; 
};

int move_a(game * cur_game) //slide left
{
    //YOUR CODE STARTS HERE

  //reinitialize
  int x = 0;
  int y = 0;
  int finalcolumn = -1; //instead of finalrow we replace with final column since we can switch with one another 
  int current_col = -1;
  int current_sol = 0;
  int modified = 0; 

  //here we repeat the same idea but we clear with the column's contents and see whether it becomes empty or not and what the 
  //current solution value is at, we do this through the numerious for loops and conditional statements
  for(x = 0; x <= (*cur_game).rows - 1; x++){
    finalcolumn = -1;

    for(y = 0; y <= (*cur_game).cols - 1; y++){

      if(*((*cur_game).cells + x * (*cur_game).cols + y) != -1){
	current_sol = 0;

	for(current_col = 0; current_col < y; current_col++){

	  //similar conditional statement set
	  if(*((*cur_game).cells + x * (*cur_game).cols + current_col) == -1){
	    current_sol = 1; 
	    break; //break out of the program/game
      }
    }

	//here we basicially repeat the same type of way we have been doing with other codes in a sense we clear out the row contents with column contents
	//into consideration
    if(current_sol == 1){

      *((*cur_game).cells + x * (*cur_game).cols + current_col) = *((*cur_game).cells + x * (*cur_game).cols + y);

      *((*cur_game).cells + x * (*cur_game).cols + y) = -1;

      modified = 1;
    }

    //column rearrangment for the tiles repeats the same idea but instead with columns through the conditionals and iterations 

    if((current_col - 1) != finalcolumn){

      if(*((*cur_game).cells + x * (*cur_game).cols + (current_col - 1)) == *((*cur_game).cells + x * (*cur_game).cols + current_col)){

	*((*cur_game).cells + x * (*cur_game).cols + (current_col - 1)) *= 2;

	(*cur_game).score += *((*cur_game).cells + x * (*cur_game).cols + (current_col - 1));

	*((*cur_game).cells + x * (*cur_game).cols + current_col) = -1;

	modified = 1;
      }
    }
      }
    }
  }

    return modified;
};

int move_d(game * cur_game){ //slide to the right
    //YOUR CODE STARTS HERE

  //reinitialize
  int x = 0;
  int y = 0;
  int finalcolumn = -1;
  int current_col = -1;
  int current_sol = 0;
  int modified = 0;

  //here we repeat the same exact idea in the last function where we utilize the final column, reset it and go through the current solution for 
  //finalcolumn 

  for(x = 0; x <= (*cur_game).rows - 1; x++){
    finalcolumn = -1;

    for(y = (*cur_game).cols - 1; y >= 0; y--){

      if(*((*cur_game).cells + x * (*cur_game).cols + y) != -1){
	current_sol = 0;

	for(current_col = (*cur_game).cols - 1; current_col >= y; current_col--){

	  if(*((*cur_game).cells + x * (*cur_game).cols + current_col) == -1){
	    current_sol = 1;

	    break; //break out of the program
	  }
	}

	if(current_sol == 1){

	  *((*cur_game).cells + x * (*cur_game).cols + current_col) = *((*cur_game).cells + x * (*cur_game).cols + y);

	  *((*cur_game).cells + x * (* cur_game).cols + y) = -1;

	  modified = 1; 
	}

	//the same exact idea is implemented and repeated in order for the tiles to move appropriately with the key directions

	if((current_col + 1) != finalcolumn){

	  if(*((*cur_game).cells + x * (*cur_game).cols + (current_col + 1)) == *((*cur_game).cells + x * (*cur_game).cols + current_col)){

	    *((*cur_game).cells + x * (*cur_game).cols + (current_col + 1)) *= 2;

	    (*cur_game).score += *((*cur_game).cells + x * (*cur_game).cols + (current_col + 1)); 

	    *((*cur_game).cells + x * (*cur_game).cols + current_col) = -1;

	    finalcolumn = current_col + 1;

	    modified = 1;
	  }
	}
      }
    }
  }

    return modified;
};

int legal_move_check(game * cur_game)
/*! Given the current game check if there are any legal moves on the board. There are
    no legal moves if sliding in any direction will not cause the game to change.
	Return 1 if there are possible legal moves, 0 if there are none.
 */
{
    //YOUR CODE STARTS HERE

  //here we made the same game form and mimicked it so our testing for our program/code can go well
  game * mimic_game = make_game((*cur_game).rows, (*cur_game).cols);
  
  //we initialize a new variable end to 0
  int end = 0;

  int x; //then we reinitialize the x variable

  //create a forloop wehere as long as x is 0 and as long as it is less than or equal to the value of the pointer at cur_game.rows times the value of 
  //the pointer at cur_game.cols minus 1, then x can increment by 1 as it iterated through 
  for (x = 0; x <= (((*cur_game).rows * (*cur_game).cols) - 1); x++){

    //conducting pointer of value of pointer mimic_game.cells + x set to the pointer value of the pointer at cure_game.cells plus x
    *((*mimic_game).cells + x) = *((*cur_game).cells + x);
  }

  //we then set a conditional statement so if the sum of the various functions we created calling mimic_game is not equal to 0; seeing if movement of cell values 
  //is happening 
  if((move_w(mimic_game) + move_a(mimic_game) + move_s(mimic_game) + move_d(mimic_game)) != 0){
    end = 1; //then end is set to 1
  }

  return end; //and we return the current value of end 
}


/*! code below is provided and should not be changed */

void rand_new_tile(game * cur_game)
/*! insert a new tile into a random empty cell. First call rand()%(rows*cols) to get a random value between 0 and (rows*cols)-1.
*/
{
	
	cell * cell_ptr;
    cell_ptr = 	cur_game->cells;
	
    if (cell_ptr == NULL){ 	
        printf("Bad Cell Pointer.\n");
        exit(0);
    }
	
	
	//check for an empty cell
	int emptycheck = 0;
	int i;
	
	for(i = 0; i < ((cur_game->rows)*(cur_game->cols)); i++){
		if ((*cell_ptr) == -1){
				emptycheck = 1;
				break;
		}		
        cell_ptr += 1;
	}
	if (emptycheck == 0){
		printf("Error: Trying to insert into no a board with no empty cell. The function rand_new_tile() should only be called after tiles have succesfully moved, meaning there should be at least 1 open spot.\n");
		exit(0);
	}
	
    int ind,row,col;
	int num;
    do{
		ind = rand()%((cur_game->rows)*(cur_game->cols));
		col = ind%(cur_game->cols);
		row = ind/cur_game->cols;
    } while ( *get_cell(cur_game, row, col) != -1);
        //*get_cell(cur_game, row, col) = 2;
	num = rand()%20;
	if(num <= 1){
		*get_cell(cur_game, row, col) = 4; // 1/10th chance
	}
	else{
		*get_cell(cur_game, row, col) = 2;// 9/10th chance
	}
}

int print_game(game * cur_game) 
{
    cell * cell_ptr;
    cell_ptr = 	cur_game->cells;

    int rows = cur_game->rows;
    int cols = cur_game->cols;
    int i,j;
	
	printf("\n\n\nscore:%d\n",cur_game->score); 
	
	
	printf("\u2554"); // topleft box char
	for(i = 0; i < cols*5;i++)
		printf("\u2550"); // top box char
	printf("\u2557\n"); //top right char 
	
	
    for(i = 0; i < rows; i++){
		printf("\u2551"); // side box char
        for(j = 0; j < cols; j++){
            if ((*cell_ptr) == -1 ) { //print asterisks
                printf(" **  "); 
            }
            else {
                switch( *cell_ptr ){ //print colored text
                    case 2:
                        printf("\x1b[1;31m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 4:
                        printf("\x1b[1;32m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 8:
                        printf("\x1b[1;33m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 16:
                        printf("\x1b[1;34m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 32:
                        printf("\x1b[1;35m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 64:
                        printf("\x1b[1;36m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 128:
                        printf("\x1b[31m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 256:
                        printf("\x1b[32m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 512:
                        printf("\x1b[33m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 1024:
                        printf("\x1b[34m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 2048:
                        printf("\x1b[35m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 4096:
                        printf("\x1b[36m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 8192:
                        printf("\x1b[31m%04d\x1b[0m ",(*cell_ptr));
                        break;
					default:
						printf("  X  ");

                }

            }
            cell_ptr++;
        }
	printf("\u2551\n"); //print right wall and newline
    }
	
	printf("\u255A"); // print bottom left char
	for(i = 0; i < cols*5;i++)
		printf("\u2550"); // bottom char
	printf("\u255D\n"); //bottom right char
	
    return 0;
}

int process_turn(const char input_char, game* cur_game) //returns 1 if legal move is possible after input is processed
{ 
	int rows,cols;
	char buf[200];
	char garbage[2];
    int move_success = 0;
	
    switch ( input_char ) {
    case 'w':
        move_success = move_w(cur_game);
        break;
    case 'a':
        move_success = move_a(cur_game);
        break;
    case 's':
        move_success = move_s(cur_game);
        break;
    case 'd':
        move_success = move_d(cur_game);
        break;
    case 'q':
        destroy_game(cur_game);
        printf("\nQuitting..\n");
        return 0;
        break;
	case 'n':
		//get row and col input for new game
		dim_prompt: printf("NEW GAME: Enter dimensions (rows columns):");
		while (NULL == fgets(buf,200,stdin)) {
			printf("\nProgram Terminated.\n");
			return 0;
		}
		
		if (2 != sscanf(buf,"%d%d%1s",&rows,&cols,garbage) ||
		rows < 0 || cols < 0){
			printf("Invalid dimensions.\n");
			goto dim_prompt;
		} 
		
		remake_game(&cur_game,rows,cols);
		
		move_success = 1;
		
    default: //any other input
        printf("Invalid Input. Valid inputs are: w, a, s, d, q, n.\n");
    }

	
	
	
    if(move_success == 1){ //if movement happened, insert new tile and print the game.
         rand_new_tile(cur_game); 
		 print_game(cur_game);
    } 

    if( legal_move_check(cur_game) == 0){  //check if the newly spawned tile results in game over.
        printf("Game Over!\n");
        return 0;
    }
    return 1;
}
