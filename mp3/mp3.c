//This program prints the desired row for Pascal's Triangle
// by allowing the user to input a row number and the 
//program outputting the correct numbers for that specified row.

//partners: shreyav3

#include <stdio.h>
#include <stdlib.h>

//given
int main()
{
  int row;

  printf("Enter a row index: ");
  scanf("%d",&row);

  // Write your code here

  //initialize the variables x, i and value to unsigned long
  unsigned long x, i, value; 

  //create a for loop when x is 0 and is less than
  //or equal to the value of row, increment by 1
  for (x = 0; x <= row; x++){

    //set value equal to 1
    value = 1; 

    //within the first for loop, add another for loop
    //iterate through using variable i
    // and print the correct result

    //for i is equal to 1 and is less than or equal to the current 
    //value at x, increment i by 1
    for (i = 1; i <= x; i++){ 

      //set value to the formula value times the row+1-i, all divided by i
      value = (value * (row +1 -i))/i;
    }
    //print the result of the value as unsigned long type
    printf ("%lu ", value);
  }
  //exit the program
  return 0;
}


