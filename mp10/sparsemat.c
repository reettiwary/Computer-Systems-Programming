	
#include "sparsemat.h"
	
	#include <stdio.h>
	
	#include <stdlib.h>
	
	//Introduction Paragraph:
	//This program stores a matrix as a linked list of non-zero elements. In order to make the list, we read the file that holds the elements for the width and height of the matrix, as well as the coordinates and values. In set_tuples, we check if the matrix is empty and we create a node and use it as the head. Else, if the value needs to be set to zero, we remove the node or ignore it. Otherwise, if the value is non-zero, we create a new node and point to the correct location, or we update a previous node and store it there.
	
	//Group Members: shreyav3, tkarim3, rtiwary2
	
	
	
	//firstly we created a helper function order_tuples to help the program //order the tuples correctly and go through and produce the right //matrices, it calls the node and head function pointers that we will //find through the rest of the program
	
	
	int order_tuples(sp_tuples_node *var_1, sp_tuples_node *var_2){
	
	//here we set a conditional statement where we compare the row elements of var_1 and var_2, and we check if they are equal or not
	
	
	 if((var_1->row) != (var_2->row)){
	
	//if they are not equal, we return 1 if var_1’s row element is greater than var_2’s row element, and 0 if var_1’s row element is less than var_2’s row element
	
	   return ((var_1->row) > (var_2->row)); 
	 }
	
	//if the row elements are equal, then we check the columns. We return 1 if var_1’s column element is greater than var_2’s column element, and 0 otherwise
	 else{
	
	   return ((var_1->col) > (var_2->col));
	 }
	} 
	
	
	
	
	//this is the first function that we wrote code into
	sp_tuples * load_tuples(char* input_file)
	{
	//initialize row variable r and column variable c
	 int r, c;
	
	//create a new sp_tuple to hold our matrix and named our pointer to it “series”
	 sp_tuples *series = (sp_tuples*)malloc(sizeof(sp_tuples)); 
	
	//open input_file to read the contents to be added to our matrix
	 FILE *fseries = fopen(input_file, "r"); 
	
	//scan the first two elements in the file to our row and column variables
	 fscanf(fseries, "%d %d\n", &r, &c); 
	
	 series->m = r; //set number of rows in series to r
	
	 series->n = c; //set number of columns in series to c
	
	 series->nz = 0; //initialize number of nonzero elements to 0
	
	 series->tuples_head = NULL; //initialize head pointer to NULL
	
	
	
	 int i, j; //initialize i and j
	
	 double z; //initialize double variable z
	
	//use a for loop to iterate through the tuple and fill it with the right values at the right positions based on contents of input_file
	 while(fscanf(fseries, "%d %d %lf\n", &i, &j, &z) == 3) {
	
	//calling set_tuples to fill a position with the value next to it
	   set_tuples(series, i, j, z); 
	 }
	
	//here we set a conditional statement, so if we are not at the end of the //program file, then we return null
	 if(!feof(fseries)){
	   return NULL; //return null
	 }
	
	 fclose(fseries); //closes the file 
	 return series; //return series
	}
	
	
	//second function we write code into
	double gv_tuples(sp_tuples * mat_t,int row,int col)
	{
	
	//set var to point to the same location as the head pointer of the input //matrix tuple
	 sp_tuples_node *var = mat_t->tuples_head; 
	
	//while variable does not equal null, here we traverse through the tuple //pointed to by var until we reach the last variable value
	
	 while(var != NULL){
	
	//if var’s row element is equal to row and var’s column element is equal to col
	   if(var->row == row && var->col == col){
	
	// we return var’s value element
	     return var->value; 
	   }
	
	//var becomes var with elements in next, moving onto the next var
	   var = var->next; 
	 }
	
	   return 0; //return 0, if the right var value was not returned 
	}
	
	//third function we write code into
	void set_tuples(sp_tuples * mat_t, int row, int col, double value)
	{
	//if mat_t with elements in tuples_head comes back as null
	 if(mat_t->tuples_head == NULL){
	
	//if value does not equal 0
	   if(value != 0){
	
	
	
	//allocate new var node which we call var2
	     sp_tuples_node *var2 = (sp_tuples_node*)malloc(sizeof(sp_tuples_node));
	
	//we dereference var2’s attributes and then set them to the arguments passed when the function is called
	     var2->row = row; //set number of rows in the var2 node to row
	     var2->col = col; //set number of columns in the var2 node to col
	     var2->value = value; //set var2 with elements in value to value
	     var2->next = NULL; //set var2 with elements in next to null
	
	//set mat_t with elements in tuples_head to var2/point to new head
	     mat_t->tuples_head = var2; 
	     mat_t->nz ++; //increment the number of non-zero elements
	   }
	
	   return; //return the value 
	 }
	
	
	
	//here we create a series of nested if-statements as well as loops 
	 if(gv_tuples(mat_t, row, col) != 0){
	
	//so firstly, if the var exists and its value is 0, then we proceed on to //delete the var value
	   if(value == 0){ //the element added to the matrix is 0
	
	     sp_tuples_node *reverse = NULL;
	     sp_tuples_node *var = mat_t->tuples_head;
	
	//while the variable does not equal null
	     while(var != NULL){
	
	//if var with elements in row is equal to row and var with elements in col is equal to col
	
	if(var->row == row && var->col == col){
	
	//if the reverse is null, so here we delete the var node and set the new //var value to pose as the next var node
	 if(reverse == NULL){
	
	//set mat_t with elements in tuples_head to be the next variable
	   mat_t->tuples_head = var->next;
	 }
	
	//here if the var value exists and the value is non-zero, then we update the var node to the current value 
	 else{
	
	//then the reverse var is set to the next var
	   reverse->next = var->next;
	 }
	
	 free(var); //free var node
	 mat_t->nz --;//decrement non-zero matrix
	
	 return;//return
	}
	
	reverse = var; //reverse is equal to var
	var = var->next; //set variable equal to var with elements in next
	     }
	   }
	
	//here we then update the var
	   else{
	
	//update variable node with matrix holding head elements
	     sp_tuples_node *var = mat_t->tuples_head;
	
	     while(var != NULL){ //while the variable does not come back null
	
	//set the conditional statement 
	if(var->row == row && var->col == col){
	
	
	 var->value = value; //variable with elements in value is set to value
	 return; //return
	}
	
	var = var->next;//set variable to next variable
	     }
	   }
	 }
	
	
	 else{ //otherwise if the var node does not exist and the value at var is 0, we do not engage
	
	   if(value == 0){ //if element added to matrix is 0
	
	     return; //return
	   }
	
	
	//otherwise, we add more to the var node, so else if the var node does not exist and value is 
	//non-zero, then we add to the var node
	   else{ 
	
	     sp_tuples_node *reverse = NULL; //reverse node comes back as null
	
	     sp_tuples_node *var = mat_t->tuples_head; //var node is matrix with elements in head
	
	
	//copy new pointer file reference with malloc
	     sp_tuples_node *copynew = (sp_tuples_node*)malloc(sizeof(sp_tuples_node));
	
	     copynew->row = row; //row element of copynew is set to row
	
	     copynew->col = col; //column element of copynew is set to col
	
	     copynew->value = value; //value element of copynew is set to value
	
	     copynew->next = NULL;  //”next” element of copynew is set to NULL
	
	
	     mat_t->nz ++; //increment non-zero matrix
	
	
	     while(var != NULL){ //while variable does not equal null
	
	// if the var node comes after the copynew 
	if(order_tuples(var, copynew)){
	
	//if we replace the var side 
	    if(reverse == NULL){//if reverse comes back as null
	
	   copynew->next = var;//set copynew with next elements to the variable
	
	   mat_t->tuples_head = copynew;//set matrix with head elements to copynew
	
	 }
	
	//otherwise we insert the value between the var nodes and what occurs
	 else{ 
	
	   reverse->next = copynew; //reverse pointing to next is set to copynew
	
	   copynew->next = var; //copynew pointing to next is set to the variable.
	
	 }
	
	 return; //return
	
	}
	
	reverse = var; //reverse equals variable
	
	var = var->next; //var becomes the var with elements held in next
	
	     }
	
	//here we allocate the new var node to the end of the remaining nodes 
	
	     reverse->next = copynew; //reverse with elements in next is set to copynew
	
	     return; //return
	
	   }
	
	 }
	
	 return; //return
	
	}
	
	void save_tuples(char * file_name, sp_tuples * mat_t)
	{
	
	 FILE* fseries = fopen(file_name, "w"); //open file_name to begin writing into it
	
	 fprintf(fseries, "%d %d\n", mat_t->m, mat_t->n); //print mat_t row elements m and n
	
	 sp_tuples_node* var = mat_t->tuples_head; //node variable is set to matrix with head elements
	
	 while(var != NULL){  //while variable does not equal null
	
	 //print string with variables containing row, column, and value elements
	   fprintf(fseries, "%d %d %lf\n", var->row, var->col, var->value);
	
	   var = var->next; //variable becomes var with elements held in next/point to next variable
	 }
	
	 fclose(fseries); //close fseries stream
	
	return; //return
	}
	
	
	//this is the other function we add information onto
	sp_tuples * add_tuples(sp_tuples * matA, sp_tuples * matB){
	
	//allocate and initialize new matrix retmat pointing to dimensions m and n and set equal to matrix A with dimensions m and n
	 sp_tuples *retmat = (sp_tuples*)malloc(sizeof(sp_tuples));
	
	 retmat->m = matA->m; //the row element of retmat is set equal to the row element of matA
	
	 retmat->n = matA->n; //the column element of retmat is set equal to the column element of matA
	
	 retmat->nz = 0; //non-zero matrix is set equal to 0
	
	 retmat->tuples_head = NULL;//matrix with head is set to null
	
	
	//here we create new “nodes” in a sense to traverse the varA and varB
	 sp_tuples_node *varA = matA->tuples_head; //node for traversing varA
	
	 sp_tuples_node *varB = matB->tuples_head; //node for traversing varB
	
	 //while variable A does not equal null
	 while(varA != NULL){
	
	//here we set the values of the matrix retmat to those at varA matrix
	//set matrix retmat values to values in varA
	   set_tuples(retmat, varA->row, varA->col, varA->value); 
	
	   varA = varA->next; //varA becomes varA with elements in next
	 }
	
	 while(varB != NULL){ //while variable B does not equal null
	
	//set a double value C equal to called gv_tuples function
	   double val_C = gv_tuples(retmat, varB->row, varB->col); 
	
	   set_tuples(retmat, varB-> row, varB->col, varB->value + val_C); //call set_tuples function
	
	   varB = varB->next; //variable B is set to variable B with next elements
	 }
	
	return retmat; //return retmat matrix
	}
	
	//OPTIONAL CODE
	sp_tuples * mult_tuples(sp_tuples * matA, sp_tuples * matB){
	
	 if(matA->n != matB->m){ //if matrices do not equal n and m dimensions
	
	   return NULL; //return null
	 }
	
	 sp_tuples *retmat = (sp_tuples*)malloc(sizeof(sp_tuples)); //allocate and reinitialize retmat
	
	 retmat->m = matA->m; //set retmat with dimension m to matrix A with dimension m
	
	 retmat->n = matB->n; //set retmat with dimension n to matrix B with dimension n
	
	 retmat->nz = 0; //non-zero matrix is 0
	
	 retmat->tuples_head = NULL; //head matrix is null
	
	
	 sp_tuples_node *varA = matA->tuples_head; //traverse matrix varA
	
	 while(varA != NULL){ //while varA does not equal null
	
	   int xA = varA->row; //initialize variable xA and set it equal to varA with elements in row
	
	   int yA = varA->col; //initialize yA and set it equal to varA with elements in col
	
	   sp_tuples_node *varB = matB->tuples_head; //traverse matrix varB
	
	   while(varB != NULL){ //while varB does not equal null
	
	     int xB = varB->row; //initialize variable xB and set it equal to varB with elements in row
	
	     int yB = varB->col; //initialize variable yB and set it equal to varB with elements in col
	
	//if row B is equal to column A, accumulate value in retmat
	     if(xB == yA){
	
	double valA = gv_tuples(matA, xA, yA); //valA set to value in matA at (xA, yA)
	
	double valB = gv_tuples(matB, xB, yB); //valB set to value in matB at (xB, yB)
	
	double val_retmat = gv_tuples(retmat, xA, yB); //retmat set to value in retmat at (xA, yB)
	
	//new_val set to the sum of val_retmat and the product of valA and valB
	double new_val = val_retmat + (valA * valB); 
	
	set_tuples(retmat, xA, yB, new_val); //set the element of retmat at position (xA, yB) to new_val
	     }
	
	//if row B is greater than column A, then we stop going through B information
	     else if(xB > yA){
	break; //stop traversing B
	     }
	
	//otherwise set varB equal to varB with elements in next/move to the next node
	     varB = varB->next;   
	 }
	
	//after traversing B, set varA equal to varA with next elements/move to the next node
	   varA = varA->next; 
	 }
	
	   return retmat; //return retmat matrix
	}
	
	//final function we added code into
	void destroy_tuples(sp_tuples * mat_t){
	
	//create node var and set it to point to the head of mat_t
	 sp_tuples_node *var = mat_t->tuples_head;  
	
	//set new node next to null, will point to next element in node to be looked at
	sp_tuples_node *next = NULL; 
	
	//here we go through the entirety of the var nodes and its values, saving each new upcoming 
	//ones
	 while(var != NULL){ //while var is not equal to null
	
	   next = var->next; //set next equal to the element next in var
	
	   free(var); //free the variable
	
	   var = next; //var is equal to next
	 }
	
	 free(mat_t); //free the matrix mat_t
	
	 return; //return
	}
	








