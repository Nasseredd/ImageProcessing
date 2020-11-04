#ifndef _SORTIE_EPS_
#define _SORTIE_EPS_ 

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "image_pbm.h"
#include "geometrie_2D.h"
#include "extraction_contour.h"
#include "TTV_Point.h"

void nom_sortie (char *nom_image,char *nom_sortie); 

void sortie_eps (Image I, char *nom_txt); 

void rep_eps (TTV_Point T, FILE *feps, Image I);


#endif /*_SORTIE_EPS_*/
