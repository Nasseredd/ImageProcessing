#ifndef _EXTRACTION_
#define _EXTRACTION_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "image_pbm.h"
#include "geometrie_2D.h"
#include "TTV_Point.h"

typedef enum { NORD, EST, OUEST, SUD } Orientation; 

void avancer (Point *position, Orientation O);

Orientation tourner_a_gauche (Orientation O);

Orientation tourner_a_droite (Orientation O);

Orientation nouvelle_orientation(Image I, Point *position, Orientation O); 

bool trouver_pixel_depart (Image I, int *x, int *y);

TTV_Point extraire_contour(Image I, int x, int y, Image *Masque); 

Image extraire_masque(Image I);

void supprimer_masque(Image *Masque, int x, int y, Orientation O); 

void extraire_tous_contour(Image I, FILE *feps); 

void ecrire_contour (TTV_Point T, FILE *f, int j); 

#endif
