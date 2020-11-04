#ifndef _SORTIE_EPS_
#define _SORTIE_EPS_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "TTV_Point.h"
#include "extraction_contour.h"

void nom_sortie (char *nom_image,char *nom_sortie);

void sortie_eps (Image I, char *nom_txt);

void rep_eps (TTV_Point T, FILE *feps, Image I);

//void rep_eps_curve (TTV_Point T, FILE *feps, Image I)

#endif /*_SORTIE_EPS_*/
