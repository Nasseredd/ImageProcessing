#include<stdio.h>
#include<stdlib.h>
#include "geometrie_2D.h"
#include "math.h"

Point set_point(double x, double y){

	Point P = {x,y}; 
	return P; 
}

Point add_point(Point P1, Point P2){

	return set_point( P1.x + P2.x , P1.y + P2.y ); 
}

Vecteur vect_bipoint(Point A, Point B){

	Vecteur V = { B.x - A.x, B.y - A.y }; 
	return V; 
}


Vecteur somme_vecteurs (Vecteur V1, Vecteur V2){

	Vecteur V = { V1.x + V2.x, V1.y + V2.y };
	return V; 
}

Vecteur produit_reel (Vecteur V, double a){

	Vecteur V_bis = { (V.x)*a , (V.y)*a };
	return V_bis; 
}

double produit_scalaire (Vecteur V1, Vecteur V2){

	return V1.x*V2.x + V1.y*V2.y ; 
} 

double norme (Vecteur V){

	return sqrt(V.x*V.x + V.y*V.y); 

} 

double distance_2points (Point P1, Point P2){

	return sqrt( pow((P1.x - P2.x),2) + pow((P1.y - P2.y),2) );  
} 


void afficher_point (Point P){

	printf("(%.2f, %.2f)\n", P.x, P.y); 
}

void afficher_vecteur (Vecteur V){

	printf("(%.2f %.2f)\n", V.x, V.y); 
}

double distance_point_segment (Point P, Point A, Point B){

	Point O = set_point(0,0); 
	double lambda; 
	Vecteur AP, AB, OA, OQ; 

	if (A.x == B.x && A.y == B.y)
		return distance_2points(P,A); 

	else{
		
		AP = vect_bipoint(A,P); 
		AB = vect_bipoint(A,B); 
		OA = vect_bipoint(O,A); 

		lambda = produit_scalaire(AP, AB)/produit_scalaire(AB, AB); 
		
		OQ = somme_vecteurs(OA, produit_reel(AB, lambda)); 
		Point Q = set_point(OQ.x, OQ.y); 

		if (lambda < 0)
			return distance_2points(A,P); 

		else if (lambda >= 0 && lambda <= 1)
			return distance_2points(Q,P); 

		else /* lambda > 1 */ 
			return distance_2points(B,P); 

	}

}

















