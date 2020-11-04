#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "simplification_de_contours.h"

TTV_Point simplification_douglas_peucker (TTV_Point Contour, UINT j1, UINT j2, double distance){

	double dmax = 0;
	double distance_j;  
	UINT k = j1; 
	int j; 
	TTV_Point L; 

	Point Pj, Pj1, Pj2; 

	for (j = j1+1; j <= j2; j++){
		
		Pj = element_TTV_Point(Contour, j);
		Pj1 = element_TTV_Point(Contour, j1);
		Pj2 = element_TTV_Point(Contour, j2);
		
		distance_j = distance_point_segment (Pj, Pj1, Pj2);

		if (dmax < distance_j){
			dmax = distance_j; 
			k = j; 
		}
	}

	if (dmax <= distance){
		L = creer_TTV_Point_vide ();
		L = ajouter_element_TTV_Point(L, Pj1);				
		L = ajouter_element_TTV_Point(L, Pj2); 
	}
	else{
		
		TTV_Point L1 = creer_TTV_Point_vide ();
		L1 = simplification_douglas_peucker (Contour, j1, k, distance); 

		TTV_Point L2 = creer_TTV_Point_vide ();
		L2 = simplification_douglas_peucker (Contour, k, j2, distance); 

		L = concatener_TTV_Point(L1, L2); 
	}

	return L; 
}

void sortie_simplification_eps (Image I, char *nom_image, double d){

	/****************************** Les variables  *******************************/
	
	char fichier_sortie_eps[40];
	nom_sortie_simplification (nom_image,fichier_sortie_eps);

	/**************************** Ouvrir le fichier  ****************************/
	
	FILE *feps = fopen(fichier_sortie_eps,"w"); 

	/****************************** Première ligne ******************************/

	fprintf(feps,"%s\n", "%!PS-Adobe-150 EPSF-150"); 

	/****************************** Deuxième ligne ******************************/

	fprintf(feps,"%%%%BoundingBox: 0 0 %u %u \n", I.L+2, I.H+2 );

	/****************************** Tous les contours ***************************/

	extraire_tous_contour_simplification(I, feps, d); 

	/********************************* Remplissage ******************************/

	fprintf(feps,"fill\n\n" );

	/********************************** Showpage ********************************/

	fprintf(feps,"showpage");

	/****************************** Fermer le fichier ***************************/

	fclose(feps);
}

void extraire_tous_contour_simplification(Image I, FILE *feps, double d){

	/************************************ VARIABLES *********************************/ 
	
	int *compteur = (int*)malloc(sizeof(int)); 
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
		TTV_Point L = simplification_douglas_peucker_bezier2(C, 0, C.nb - 1, d, compteur); 

		/* ----------------- Traduction d'un contour en postscript ------------- */

		rep_eps(L, feps, I);

		/* -------------- Incrémentation du nombre total de points ------------- */

		Total_Points = Total_Points + L.nb; 
		
		/* ------------------ Ecrire le contour dans le fichier ---------------- */
		 
		 Nombre_de_contours++; 

	}
	
	/******************** Le nombre de courbes de Bezier3  *********************/ 

	printf("Le nombre de courbes de Bezier2 est de %d \n", *compteur); 

	/******************** Affichage du nombre contour(s)  *********************/ 

	printf("Le nombre de contour(s) est de %d\n", Nombre_de_contours); 

	/******************** Affichage du nombre total de points  *********************/ 

	printf("Le nombre total de points est de %d points\n", Total_Points); 

	/****************** Affichage du nombre total de segments  *******************/ 

	Total_Segments = Total_Points -  Nombre_de_contours; 
	printf("Le nombre total de segments est %d segments\n", Total_Segments);
}

void nom_sortie_simplification (char *nom_image,char *nom_sortie){
	
	/****************************** Les variables  *******************************/

	int i=0,j,k;
	int debut_nom = 11;
	char mareftch[11]={'_','s','i','m','p', 'l','i','.','e','p','s'};

	/****************************  ****************************/ 

	while(nom_image[i+debut_nom]!='.'){
		nom_sortie[i] = nom_image[i+debut_nom];
		i++;
	} 

	/****************************   ****************************/ 

	for(j=i;j<i+11;j++){
		nom_sortie[j]=mareftch[j-i];
	}

	/****************************   ****************************/ 

	for( k=j ; k<40 ; k++)
		nom_sortie[j] ='\0';
}

TTV_Point simplification_douglas_peucker_bezier2(TTV_Point CONT, UINT j1, UINT j2, double d, int *compteur){

	double n = j2 - j1; 
	Bezier_2 B2 = approx_bezier2(CONT, j1, j2); 

	Bezier_3 B3 = conversion_degre_2a3 (B2);
	
	double dmax = 0;
	double distance_j, ti;  
	UINT k = j1; 
	UINT j, i; 
	TTV_Point L; 

	Point Pj; 

	for (j = j1+1; j <= j2; j++){
		
		i = j - j1; 
		ti = (double)i/(double)n; 
		Pj = element_TTV_Point(CONT, j);

		
		distance_j = distance_point_bezier3 (Pj, B3, ti);

		if (dmax < distance_j){
			dmax = distance_j; 
			k = j; 
		}
	}

	if (dmax <= d){
		*compteur = *compteur + 1; 
		L = creer_TTV_Point_vide ();
		L = ajouter_element_TTV_Point(L, B3.C0);
		L = ajouter_element_TTV_Point(L, B3.C1);
		L = ajouter_element_TTV_Point(L, B3.C2);
		L = ajouter_element_TTV_Point(L, B3.C3);
	}
	else{
		
		TTV_Point L1 = creer_TTV_Point_vide ();
		L1 = simplification_douglas_peucker_bezier2 (CONT, j1, k, d, compteur); 

		TTV_Point L2 = creer_TTV_Point_vide ();
		L2 = simplification_douglas_peucker_bezier2 (CONT, k, j2, d, compteur); 

		L = concatener_TTV_Point(L1, L2); 
	}

	return L; 
}