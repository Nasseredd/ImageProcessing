#ifndef _SIMPLIFICATION_DE_CONTOURS_
#define _SIMPLIFICATION_DE_CONTOURS_


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "TTV_Point.h"
#include "extraction_contour.h"
#include "sortie_eps.h"
#include "bezier.h"


void sortie_simplification_eps (Image I, char *nom_image, double d);

void extraire_tous_contour_simplification(Image I, FILE *feps, double d);

void nom_sortie_simplification (char *nom_image,char *nom_sortie);

TTV_Point simplification_douglas_peucker_bezier3(TTV_Point CONT, UINT j1, UINT j2, double d, int *compteur);

#endif /*_SIMPLIFICATION_DE_CONTOURS_*/
