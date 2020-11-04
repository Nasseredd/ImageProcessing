#ifndef _TTV_Point_
#define _TTV_Point_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "image_pbm.h"
#include "geometrie_2D.h"

typedef struct TTV_Point
{
	UINT nb;
	UINT cap;
	UINT taille_elt;
	Point *tab;

} TTV_Point;


TTV_Point creer_TTV_Point_vide ();


Point element_TTV_Point(TTV_Point T, UINT i);


UINT nb_elements_TTV_Point (TTV_Point T);


TTV_Point ajouter_element_TTV_Point(TTV_Point T, Point e);


TTV_Point concatener_TTV_Point(TTV_Point T1, TTV_Point T2);


void supprimer_TTV_Point(TTV_Point *ptr_T);


#endif /* _TTV_Point_ */
