#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "image_pbm.h"
#include "simplification_de_contours.h"


int main(int argc, char **argv){

	/* ----------------------- Déclaration des variables -------------------- */	
	
	Image I; 
	
	/* -------------------------- Lecture de l'image  ----------------------- */
	
	I = lire_fichier_image(argv[1]); 

	/* --------------- Vérification de la lecture de l'image ---------------- */

	if (argc != 3){
		printf("Le programme prend 2 arguments : < image.pbm >\n"); 
		return 0; 
	}

	/* ---------------------- Simplification du contour --------------------- */ 
	
	double d = atoi(argv[2]); 
	sortie_simplification_eps (I, argv[1], d); 
	

	return 0; 
}
