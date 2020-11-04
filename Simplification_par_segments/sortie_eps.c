#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "image_pbm.h"
#include "geometrie_2D.h"
#include "extraction_contour.h"
#include "TTV_Point.h"
#include "sortie_eps.h"


void nom_sortie (char *nom_image,char *nom_sortie){
	
	/****************************** Les variables  *******************************/

	int i=0,j,k;
	int debut_nom = 11;
	char mareftch[11]={'_','r','e','m','p', 'l','i','.','e','p','s'};

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

void sortie_eps (Image I, char *nom_image){

	/****************************** Les variables  *******************************/
	
	char fichier_sortie_eps[40];
	nom_sortie (nom_image,fichier_sortie_eps);

	/**************************** Ouvrir le fichier  ****************************/
	
	FILE *feps = fopen(fichier_sortie_eps,"w"); 

	/****************************** Première ligne ******************************/

	fprintf(feps,"%s\n", "%!PS-Adobe-150 EPSF-150"); 

	/****************************** Deuxième ligne ******************************/

	fprintf(feps,"%%%%BoundingBox: 0 0 %u %u \n", I.L+2, I.H+2 );

	/****************************** Tous les contours ***************************/

	extraire_tous_contour(I, feps); 

	/********************************* Remplissage ******************************/

	fprintf(feps,"fill\n\n" );

	/********************************** Showpage ********************************/

	fprintf(feps,"showpage");

	/****************************** Fermer le fichier ***************************/

	fclose(feps);

}

void rep_eps (TTV_Point T, FILE *feps, Image I){

	int i = 0; 
	float epaisseur = 1; 

	/********************************** Contour  ********************************/ 

	fprintf(feps,"%.1f %.1f moveto ",T.tab[0].x+1,I.H-T.tab[0].y+1);

	for( i=1 ; i<T.nb ; i++){
		fprintf(feps,"%.1f %.1f lineto ",T.tab[i].x+1,I.H-T.tab[i].y+1);
	}

	/********************************** Couleur *********************************/

	fprintf(feps,"\n%% de couleur noir \n0 0 0 setrgbcolor \n" );

	/********************************** Epaisseur  ******************************/

	fprintf(feps,"%% épaisseur \n %.1f setlinewidth \n", epaisseur );


} 



