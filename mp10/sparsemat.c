#include "sparsemat.h"

#include <stdio.h>
#include <stdlib.h>

int sort_tuples(sp_tuples_node *var_1, sp_tuples_node *var_2){
  if((var_1->row) != (var_2->row)){
    return ((var_1->row) > (var_2->row));
  }
  else{
    return ((var_1->col) > (var_2->col));
  }
	
    return -1;
}  

sp_tuples * load_tuples(char* input_file)
{
  int x;
  int y; 

  sp_tuples *series = (sp_tuples*)malloc(sizeof(sp_tuples));
  FILE *fseries = fopen(input_file, "r");
  if(fseries == NULL){
    printf("Error: %s not found", input_file);
    return NULL;
  }

  fscanf(fseries, "%d %d\n", &x, &y);

  series->m = x;
  series->n = y;
  series->nz = 0;
  series->tuples_head = NULL;

  int i;
  int j;
  double z;
  while(fscanf(fseries, "%d %d %lf\n", &i, &j, &z) == 3) {
    set_tuples(series, i, j, z);
  }

  if(!feof(fseries)){
    return NULL;
  }
  fclose(fseries);
  return series;
}

double gv_tuples(sp_tuples * mat_t,int row,int col)

{

  sp_tuples_node *var = mat_t->tuples_head;

  while(var != NULL){

    if(var->row == row && var->col == col){
      return var->value;
    }

    var = var->next;
  }
    return 0;
}

void set_tuples(sp_tuples * mat_t, int row, int col, double value)
{

  if(mat_t->tuples_head == NULL){
    if(value != 0){

      sp_tuples_node *var2 = (sp_tuples_node*)malloc(sizeof(sp_tuples_node));

      var2->row = row;
      var2->col = col;
      var2->value = value;
      var2->next = NULL;

      mat_t->tuples_head = var2;
      mat_t->nz ++;
    }
    return;
  }

  if(gv_tuples(mat_t, row, col) != 0){

    if(value == 0){
      sp_tuples_node *reverse = NULL;
      sp_tuples_node *var = mat_t->tuples_head;

      while(var != NULL){
	if(var->row == row && var->col == col){

	  if(reverse == NULL){
	    mat_t->tuples_head = var->next;
	  }

	  else{
	    reverse->next = var->next;
	  }

	  free(var);
	  mat_t->nz --;
	  return;
	}
	reverse = var;
	var = var->next;
      }
    }

    else{
      sp_tuples_node *var = mat_t->tuples_head;

      while(var != NULL){
	if(var->row == row && var->col == col){
	  var->value = value;
	  return;
	}
	var = var->next;
      }
    }
  }
  else{
    if(value == 0){
      return;
    }

    else{
      sp_tuples_node *reverse = NULL;
      sp_tuples_node *var = mat_t->tuples_head;
      sp_tuples_node *copynew = (sp_tuples_node*)malloc(sizeof(sp_tuples_node));

      copynew->row = row;
      copynew->col = col;
      copynew->value = value;
      copynew->next = NULL;
      mat_t->nz ++;

      while(var != NULL){
	if(sort_tuples(var, copynew)){

	  if(reverse == NULL){
	    copynew->next = var;
	    mat_t->tuples_head = copynew;
	  }

	  else{
	    reverse->next = copynew;
	    copynew->next = var;
	  }
	  return;
	}
	reverse = var;
	var = var->next;
      }

      reverse->next = copynew;
      return;
    }
  }
  return;
}

void save_tuples(char * file_name, sp_tuples * mat_t)
{

  FILE* fseries = fopen(file_name, "w");
  fprintf(fseries, "%d %d\n", mat_t->m, mat_t->n);
  sp_tuples_node* var = mat_t->tuples_head;
  while(var != NULL){
    fprintf(fseries, "%d %d %lf\n", var->row, var->col, var->value);
    var = var->next;
  }

  fclose(fseries);
	return;
}

sp_tuples * add_tuples(sp_tuples * matA, sp_tuples * matB){

  sp_tuples *retmat = (sp_tuples*)malloc(sizeof(sp_tuples));
  retmat->m = matA->m;
  retmat->n = matA->n;
  retmat->nz = 0;
  retmat->tuples_head = NULL;

  sp_tuples_node *varA = matA->tuples_head;
  sp_tuples_node *varB = matB->tuples_head;

  while(varA != NULL){
    set_tuples(retmat, varA->row, varA->col, varA->value);
    varA = varA->next;
  }

  while(varB != NULL){
    double val_C = gv_tuples(retmat, varB->row, varB->col);
    set_tuples(retmat, varB-> row, varB->col, varB->value + val_C);
    varB = varB->next;
  }

	return retmat;
}

sp_tuples * mult_tuples(sp_tuples * matA, sp_tuples * matB){ 

  if(matA->n != matB->m){
    return NULL;
  }

  sp_tuples *retmat = (sp_tuples*)malloc(sizeof(sp_tuples));
  retmat->m = matA->m;
  retmat->n = matB->n;
  retmat->nz = 0;
  retmat->tuples_head = NULL;

  sp_tuples_node *varA = matA->tuples_head;
  while(varA != NULL){
    int xA = varA->row;
    int yA = varA->col;

    sp_tuples_node *varB = matB->tuples_head;
    while(varB != NULL){
      int xB = varB->row;
      int yB = varB->col;

      if(xB == yA){
	double valA = gv_tuples(matA, xA, yA);
	double valB = gv_tuples(matB, xB, yB);
	double val_retmat = gv_tuples(retmat, xA, yB);
	double new_val = val_retmat + (valA * valB);
	set_tuples(retmat, xA, yB, new_val);
      }

      else if(xB > yA){
	break;
      }

      varB = varB->next;
    }

    varA = varA->next;
  }

    return retmat;

}
	
void destroy_tuples(sp_tuples * mat_t){

  sp_tuples_node *var = mat_t->tuples_head;
  sp_tuples_node *next = NULL;

  while(var != NULL){
    next = var->next;
    free(var);
    var = next;
  }

  free(mat_t);

  return;
}








