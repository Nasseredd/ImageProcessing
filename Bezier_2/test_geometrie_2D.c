#include <stdio.h>
#include <stdlib.h>
#include "types_macros.h"
#include "geometrie_2D.h"

int main(void){

	//Point P, A, B;
	//double Distance;
	//double x;
	//double n, k; 
	UINT i, d; 
	double t;   

	/************************* Demandes au clavier ***********************/ 

	printf("Les paramètres de Bernstein i/d/t : \n"); 
	scanf("%u %u %lf", &i, &d, &t); 
	printf("Le coef de bernstein(%f) = %f\n", t, Bernstein(i,d,t)); 



	return 0; 
}