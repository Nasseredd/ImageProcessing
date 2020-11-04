#ifndef _SIMPLIFICATION_DE_CONTOURS_
#define _SIMPLIFICATION_DE_CONTOURS_


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "image_pbm.h"
#include "geometrie_2D.h"
#include "extraction_contour.h"
#include "TTV_Point.h"
#include "sortie_eps.h"


TTV_Point simplification_douglas_peucker (TTV_Point Contour, UINT j1, UINT j2, double distance); 

void sortie_simplification_eps (Image I, char *nom_image, double d); 

void extraire_tous_contour_simplification(Image I, FILE *feps, double d); 

void nom_sortie_simplification (char *nom_image,char *nom_sortie); 


#endif /*_SIMPLIFICATION_DE_CONTOURS_*/ 