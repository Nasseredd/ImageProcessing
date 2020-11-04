#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "image_pbm.h"
#include "geometrie_2D.h"
#include "extraction_contour.h"
#include "TTV_Point.h"
#include "sortie_eps.h"

typedef TTV_Point Contour; 

int main(int argc, char **argv)
{
	float temps;
    	clock_t t1, t2;

	t1 = clock();

	/* ----------------------- Déclaration des variables -------------------- */	
	
	Image I; 

	/* --------------- Vérification de la lecture de l'image ---------------- */

	if (argc != 2){
		printf(" \n");
		printf("********************************* ERREUR ***************************************\n");
		printf("********************************************************************************\n");
		printf("**                                                                            **\n"); 
		printf("** - Le programme prend 1 argument : < nos_images/image >                     **\n"); 
		printf("** - Ne pas oublier de placer l'image à tester dans le répértoire nos_image/  **\n"); 
		printf("** - NB :Il est possible de générer toutes les images grace au bash exec.sh   **\n"); 
		printf("**       (en revanche cela prend un temps non négligeable)                    **\n"); 
		printf("**                                                                            **\n");
		printf("********************************************************************************\n\n");
		return 0; 
	}

	printf("\n");

	/* -------------------------- Lecture de l'image  ----------------------- */
	
	I = lire_fichier_image(argv[1]); 

	/* ------------------------ Extraction du contour  ---------------------- */

	sortie_eps (I, argv[1]); 

	t2 = clock();
    	temps = (float)(t2-t1)/CLOCKS_PER_SEC;
    	printf("Le temps d'execution est de %f s\n", temps);	

	printf("\n");
	return 0; 
}
