#ifndef _GEOMETRIE_2D_
#define _GEOMETRIE_2D_

#include<stdio.h>
#include<stdlib.h>
#include "types_macros.h"

typedef struct Vecteur {
	double x,y;
} Vecteur;

typedef struct Point {
	double x,y;
} Point;

Point set_point(double x, double y);

Point add_point(Point P1, Point P2);

Point produit_point_scalaire (Point P1, double a);

Vecteur vect_bipoint(Point A, Point B);

Vecteur somme_vecteurs (Vecteur V1, Vecteur V2);

Vecteur produit_reel (Vecteur V, double x);

double produit_scalaire (Vecteur V1, Vecteur V2);

double norme (Vecteur V);

double distance_2points (Point P1, Point P2);

void afficher_vecteur (Vecteur V);

void afficher_point (Point P);

double distance_point_segment (Point P, Point A, Point B);

double factorielle (double n);

double combinaison (double n, double k);

double Bernstein (UINT i, UINT d, double t);

#endif /*_GEOMETRIE_2D_*/
