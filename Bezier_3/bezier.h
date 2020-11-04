#ifndef _BEZIER_
#define _BEZIER_

#include <stdio.h>
#include <stdlib.h>
#include "math.h"
#include "geometrie_2D.h"
#include "TTV_Point.h"
#include "types_macros.h"

/* ------------------------------------------------------------------------- */

typedef struct Bezier_2{

	Point C0;
	Point C1;
	Point C2;

} Bezier_2;

typedef struct Bezier_3{

	Point C0;
	Point C1;
	Point C2;
	Point C3;

} Bezier_3;

/* ------------------------------------------------------------------------- */

Point calcul_point_deg2 (Bezier_2 B2, double t);

double distance_point_bezier2 (Point Pj, Bezier_2 B2, double ti);

Point sigma_bezier2 (TTV_Point CONT, UINT j1, UINT j2);

Bezier_2 approx_bezier2(TTV_Point CONT, UINT j1, UINT j2);

/* ------------------------------------------------------------------------- */

Bezier_3 conversion_degre_2a3 (Bezier_2 B2);

/* ------------------------------------------------------------------------- */

double distance_point_bezier3 (Point Pj, Bezier_3 B3, double ti);

Point calcul_point_deg3 (Bezier_3 B3, double t);

Bezier_3 approx_bezier3(TTV_Point CONT, UINT j1, UINT j2); 

Point sigma_C1_bezier3(TTV_Point CONT,double n, double j1); 

Point sigma_C2_bezier3(TTV_Point CONT,double n, double j1); 

double gama_Bezier3(double k,double n);

#endif /* _BEZIER_ */