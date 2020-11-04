#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "image_pbm.h"
#include "geometrie_2D.h"
#include "extraction_contour.h"
#include "TTV_Point.h"
#include "sortie_eps.h"

void avancer (Point *position, Orientation O){

	double X = position->x ; 
	double Y = position->y ; 
	switch(O){

		case NORD :  position->x = X ;  position->y =  Y-1 ;  break; 
		case SUD :   position->x = X  ; position->y =  Y+1 ;  break; 
		case EST :   position->x = X+1  ; position->y = Y  ;  break; 
		case OUEST : position->x =  X-1 ; position->y = Y  ;  break; 
	}
}

Orientation tourner_a_gauche (Orientation O){
	
	switch(O){

		case NORD :  return OUEST ; 
		case SUD :   return EST   ;   
		case EST :   return NORD  ; 
		default : return SUD   ; 
	}		
}

Orientation tourner_a_droite (Orientation O){
	
	switch(O){

		case NORD :   return EST   ;  
		case SUD :    return OUEST ;   
		case EST :    return SUD   ;   
		default :  return NORD  ;   
	}	
}

Orientation nouvelle_orientation(Image I, Point *position, Orientation O){

	Point pG, pD;
	double x,y; 
	Orientation new_orientation = O; 

	x = position->x ; 
	y = position->y ; 

	/* initialisation du point G et point D */ 
	switch(O){

		case NORD :   pG.x = x;    pG.y = y;    pD.x = x+1 ;  pD.y = y  ;  break; 
		case SUD :    pG.x = x+1 ; pG.y = y+1 ; pD.x = x;     pD.y = y+1 ; break; 
		case EST :    pG.x = x+1;  pG.y = y;    pD.x = x+1;   pD.y = y+1 ; break; 
		case OUEST :  pG.x = x;    pG.y = y+1;  pD.x = x;     pD.y = y  ;  break; 
	}

	/* Où va tourner le robot ? */ 
	if (get_pixel_image(I, pG.x, pG.y) == NOIR)
		new_orientation = tourner_a_gauche(O);

	else if (get_pixel_image(I, pD.x, pD.y) == BLANC)
		new_orientation = tourner_a_droite(O);

	return new_orientation ;  
}

/* Explication : Cette méthode nous permet de trouver le premier pixel noir qui 
aura toujours pour pixel voisin N un pixel blanc. C'est une sorte de scan de haut 
en bas avec la ligne scannée toujours blanche. */ 

bool trouver_pixel_depart (Image I, int *x, int *y) {

	*x = 1; 
	*y = 1;

	while (get_pixel_image(I, *x, *y) != NOIR){
		
		*x = *x+1 ; 
		*y = *y ;

		if (*x > I.L){
			*x = 1 ; 
			*y = *y+1 ; 
		}

		if ( *y > I.H ) /* Si on sort de l'image avec y > H */
			return false; /* Si on n'a pas trouvé notre pixel noir */  
 		
	}
	return true; /* Si on a trouvé notre pixel noir */ 
}

TTV_Point extraire_contour(Image I, int x, int y, Image *Masque){
	
	/* la fonction extraction_contour() a été modifiée pour mémoriser 
	les points de contours dans une séquence */ 

	/**************************** VARIABLES ******************************/  

	int x_0, y_0; 

	bool boucle;

	TTV_Point sequence; 
	  
	Orientation O; 

	/********************** Création d'un Point *************************/ 

	Point *position = (Point *)malloc(sizeof(Point));

	/**************** Création d'une séquence vide **********************/ 

	sequence = creer_TTV_Point_vide(); 

	/******** Affectation des coordonnées du pixel noir de départ ******/

	x_0 = x-1; 
	y_0 = y-1;
	
	position->x = x_0; 
	position->y = y_0;

	O = EST; 

	boucle = true; 

	/***************** Stockage des points du contour *****************/

	while (boucle){
		sequence = ajouter_element_TTV_Point(sequence, *position);
		avancer(position,O);

		/* ---------- Supprimer un dans le masquer --------- */
		supprimer_masque(Masque, (int)position->x, (int)position->y, O);

		O = nouvelle_orientation(I,position,O); 

		/* --------- Vérification : fin du contour ? -------- */ 
		if ( (position->x) == x_0 && (position->y) == y_0)
			boucle = false; 

	}
	/* ------------- L'ajout du dernier élément ------------- */
	
	sequence = ajouter_element_TTV_Point(sequence, *position);

  
	return sequence; 
}

Image extraire_masque(Image I){

	int i, j; 
	Image Masque = creer_image(I.L, I.H); 

	for ( i=1; i<I.L+1; i++){ 
		for( j=1; j<I.H+1; j++){ 
			if( get_pixel_image(I,i,j) == NOIR && get_pixel_image(I,i,j-1) == BLANC){
				set_pixel_image(Masque, i,j, NOIR); 
			}
		}
	}
	return Masque; 
}

void supprimer_masque(Image *Masque, int x, int y, Orientation O){

	if (O == EST){
		switch(O){

			case NORD  : set_pixel_image(*Masque,x+1,y+1, BLANC);  break;  
			case SUD   : set_pixel_image(*Masque,x,y, BLANC);      break;   
			case EST   : set_pixel_image(*Masque,x,y+1, BLANC);    break;
			case OUEST : set_pixel_image(*Masque,x+1,y, BLANC);    break;   
		}
	}
} 

void extraire_tous_contour(Image I, FILE *feps){

	/************************************ VARIABLES *********************************/ 

	int  Nombre_de_contours = 0;
	int Total_Points = 0; 
	int Total_Segments = 0; 
	TTV_Point C;

	int *x = (int*)malloc(sizeof(int)); 
	int *y = (int*)malloc(sizeof(int));  
	Image *Masque = (Image*)malloc(sizeof(Image));  

	/******************* Extraction du masque à partir de l'image  ******************/
	
	*Masque = extraire_masque(I);  

	
	while (trouver_pixel_depart(*Masque,x,y) == true){

		/* -------- Extraction d'un contour et Suppression dans le masque ------ */
		
		C = extraire_contour(I,*x,*y,Masque); 


		/* ----------------- Traduction d'un contour en postscript ------------- */

		rep_eps(C, feps, I);

		/* -------------- Incrémentation du nombre total de points ------------- */

		Total_Points = Total_Points + C.nb; 
		
		/* ------------------ Ecrire le contour dans le fichier ---------------- */
		 
		 Nombre_de_contours++; 

		
	}


	/******************** Affichage du nombre contour(s)  *********************/ 

	printf("Le nombre de contour(s) est de %d\n", Nombre_de_contours); 

	/******************** Affichage du nombre total de points  *********************/ 

	printf("Le nombre total de points est de %d points\n", Total_Points); 

	/****************** Affichage du nombre total de segments  *******************/ 

	Total_Segments = Total_Points -  Nombre_de_contours; 
	printf("Le nombre total de segments est %d segments\n", Total_Segments);
}

void ecrire_contour (TTV_Point T, FILE *ftxt, int j){

	int i; 

	/*********** Nombre total de points ******************/ 
	
	fprintf(ftxt, "%d\n", T.nb ); 

	/*********** Affichage de points  ********************/ 

	for ( i=0; i < T.nb; i++)
	{
		fprintf(ftxt, " %.1f %.1f \n", T.tab[i].x, T.tab[i].y);
	} 
	fprintf(ftxt, "\n");
}