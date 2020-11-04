#include <stdio.h>
#include <stdlib.h>
#include "math.h"
#include "bezier.h"


/* ---------------------------------------------------------------------------------- */

double distance_point_bezier2 (Point Pj, Bezier_2 B2, double ti){

	double D = distance_2points (Pj, calcul_point_deg2 (B2, ti)); 
	return D; 

}

Point calcul_point_deg2 (Bezier_2 B2, double t){

	Point resultat = {0,0};

	/************ Vérifier si 0 <= t <= 1 **********/ 

	if (t<0 || t>1){
		printf("le t en entrée est eronné\n"); 
		return resultat; 
	}

	/*********** Calculer C2 - 2C1 + C0 ***********/
	Point coef2 = add_point(B2.C2,add_point(produit_point_scalaire(B2.C1,-2), B2.C0)); 

	/************ Calculer 2C1 - 2C0 *************/      
	Point coef1 = add_point(produit_point_scalaire(B2.C1,2), produit_point_scalaire(B2.C0,-2)); 

	/***************** Calculer C0 *****************/
	Point coef0 = B2.C0; 			

	resultat = add_point(
								produit_point_scalaire(coef2, t*t), 
								add_point(
										produit_point_scalaire(coef1, t), 
										coef0
									)
								); 

	return resultat; 
}

Point somme_points_tab (TTV_Point CONT, UINT j1, UINT j2){

	Point somme_points = {0,0};
	double n = j2 - j1;

	for (int i=1; i < n; i++){
		somme_points = add_point(CONT.tab[i+j1], somme_points); 
	}

	return somme_points; 
}

Bezier_2 approx_bezier2(TTV_Point CONT, UINT j1, UINT j2){

	Bezier_2 B2;
	double n = j2 - j1;

	if (n == 1){

		B2.C0 = CONT.tab[j1];
		B2.C2 = CONT.tab[j2];
		B2.C1 = produit_point_scalaire(add_point(B2.C0,B2.C2),0.5);
		
	}
	if (n > 1){

		double alpha = (3*n)/(n*n - 1); 
		double beta = (1-2*n)/(2*(n+1)); 

		B2.C0 = CONT.tab[j1];
		
		B2.C2 = CONT.tab[j2];

		B2.C1 = add_point(
				produit_point_scalaire(somme_points_tab(CONT, j1, j2), alpha), 
				produit_point_scalaire(add_point(B2.C0, produit_point_scalaire(B2.C2,1)),beta)
				); 

	}

	return B2; 		
}

/* ---------------------------------------------------------------------------------- */

Bezier_3 conversion_degre_2a3 (Bezier_2 B2){

	Bezier_3 B3; 

	B3.C0 = B2.C0; 
	B3.C1 = add_point(produit_point_scalaire(B2.C0, 0.3333), produit_point_scalaire(B2.C1, 0.6666)); 
	B3.C2 = add_point(produit_point_scalaire(B2.C2, 0.3333), produit_point_scalaire(B2.C1, 0.6666));  
	B3.C3 = B2.C2; 

	return B3; 
}

/* ---------------------------------------------------------------------------------- */

double distance_point_bezier3 (Point Pj, Bezier_3 B3, double ti){

	double D = distance_2points (Pj, calcul_point_deg3 (B3, ti)); 
	return D; 

}

Point calcul_point_deg3 (Bezier_3 B3, double t){

	Point resultat = {0,0};

	/************ Vérifier si 0 <= t <= 1 **********/ 

	if (t<0 && t>1){
		printf("le t en entrée est eronné\n"); 
		return resultat; 
	}

	/*********** Calculer C3 - 3C2 + 3C1 -C0 ***********/
	Point coef3 =  add_point(
					B3.C3, 
					add_point(
							produit_point_scalaire(B3.C2, -3),
							add_point(
									produit_point_scalaire(B3.C1,3), 
									produit_point_scalaire(B3.C0,-1)
								)
						)
					);


	/*********** Calculer 3C2 - 6C1 + 3C3 ***********/
	Point coef2 =  add_point(produit_point_scalaire(B3.C2, 3),add_point(produit_point_scalaire(B3.C1,-6), produit_point_scalaire(B3.C0,3)));

	/************ Calculer 3C1 - 3C0 *************/      
	Point coef1 = add_point(produit_point_scalaire(B3.C1,3), produit_point_scalaire(B3.C0,-3)); 

	/***************** Calculer C0 *****************/
	Point coef0 = B3.C0; 
	

	resultat = add_point(add_point(produit_point_scalaire(coef3, pow(t,3)), produit_point_scalaire(coef2, pow(t,2))), add_point(produit_point_scalaire(coef1, t), coef0));

	return resultat;
}











