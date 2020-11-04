#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"types_macros.h"
#include"image_pbm.h"

/* macro donnant l'indice d'un pixel de coordonnées (_x,_y) de l'image _I */
#define INDICE_PIXEL(_I,_x,_y) ((_x)-1)+(_I).L*((_y)-1)

/* création d'une image PBM de dimensions L x H avec tous les pixels blancs */
Image creer_image(UINT L, UINT H)
{
	Image I;
	UINT i;
	
	I.L = L;
	I.H = H;
	
	/* alloctaion dynamique d'un tableau de L*H Pixel*/
	I.tab = (Pixel *)malloc(sizeof(Pixel)*L*H);
	
	/* test si le tableau a ete correctement alloue */
	if (I.tab == (Pixel *)0)
	{
		ERREUR_FATALE("Impossible de creer une image");
	}
	
	/* remplir le tableau avec des pixels blancs */
	for (i=0; i<L*H; i++)
		I.tab[i] = BLANC;
		
	return I;
}

/* suppression de l'image I = *p_I*/
void supprimer_image(Image *p_I)
{
	free(p_I->tab);
	p_I->tab = NULL; 
	p_I->L = 0;
	p_I->H = 0;
}

/* renvoie la valeur du pixel (x,y) de l'image I
   si (x,y) est hors de l'image la fonction renvoie BLANC */
/* La fonction nous renvoie la nature du pixel (NOIR ou BLANC)*/ 
Pixel get_pixel_image(Image I, int x, int y)
{
	if (x<1 || x>I.L || y<1 || y>I.H)
		return BLANC;
	return I.tab[INDICE_PIXEL(I,x,y)];
}

/* change la valeur du pixel (x,y) de l'image I avec la valeur v
   si (x,y) est hors de l'image la fonction ne fait rien */
void set_pixel_image(Image I, int x, int y, Pixel v)
{
	if (x<1 || x>I.L || y<1 || y>I.H)
		return;
	I.tab[INDICE_PIXEL(I,x,y)] = v;
}

/****************************************************************************************/
/************************** Lire L'image du fichier image *******************************/
/****************************************************************************************/

Image lire_fichier_image(char *nom_f)
{
	/**************************** Déclaration des variables *****************************/

	FILE *f;
	int compteur = 0; 
	int res_fscanf;
	char C; 
	char *ligne;
	UINT L,H;
	size_t n;
	ssize_t l_ligne;
	Image I;
	
	/************************ Ouverture du fichier image (nom_f) ************************/
	
	f = fopen(nom_f, "r");
	if (f == (FILE *)NULL)
	{
		ERREUR_FATALE("lire_fichier_image : ouverture du fichier impossible\n");
	}
	
	/************************** lecture et test de la ligne 1 ***************************/

	ligne = (char *)NULL;
	n = 0;
	l_ligne = getline(&ligne, &n, f);

	if (l_ligne != 3)
	{
		ERREUR_FATALE("lire_fichier_image : ligne 1 incorrecte\n");
	}
	if ((ligne[0] != 'P') || (ligne[1] != '1'))
	{
		ERREUR_FATALE("lire_fichier_image : ligne 1 incorrecte\n");
	}
	free(ligne);
	
	/************************** lecture et test de la ligne 2 ***************************/
	
	ligne = (char *)NULL;
	n = 0;
	l_ligne = getline(&ligne, &n, f); 
	
	if ((ligne[0] != '#') || ligne[l_ligne - 1] != '\n')
	{
		ERREUR_FATALE("lire_fichier_image : ligne 2 incorrecte\n");
	}
	free(ligne);
	
	/**************************** lecture des dimensions *********************************/
	
	res_fscanf = fscanf(f, "%d%c%d", &L, &C, &H); 

	if ( (res_fscanf != 3) || (L < 0) || (H < 0) || (C !=' ') )
	{
		ERREUR_FATALE("lire_fichier_image : ligne 3 incorrecte\n");
	}

	/********************* création de l'image de dimensions L x H ***********************/
	
	I = creer_image(L,H); 

	/********************************** Lecture des pixels *******************************/

	while (compteur < L*H){
		fscanf (f, "%c", &C); 
		if (C == '0'){
			I.tab[compteur] = BLANC; 
			compteur++;
		}
		if (C == '1'){
			I.tab[compteur] = NOIR; 
			compteur++;
		}
	}
	
	/******************************** fermeture du fichier *******************************/
	
	fclose(f);
	
	return I;
}

/****************************************************************************************/
/************************** Écrire l'image I sur le terminale ***************************/
/****************************************************************************************/

void ecrire_image(Image I)
{
	int i; 
	printf("\n*************** Image ***************\n\n");
	
	printf("La largeur : %d\n", I.L); 
	printf("La hauteur : %d\n\n", I.H);
	
	for ( i=0 ; i < I.L*I.H ; i++){ 
		printf("%d", I.tab[i]); 
		if ((i+1)%I.L == 0)
			printf("\n");
	}  
	
	printf("\n**************************************\n\n");
}
