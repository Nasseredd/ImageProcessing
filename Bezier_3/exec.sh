#!/bin/bash

for var in nos_images/*; do
echo "***************************************************************"
echo "------------------------- $var "
echo "***************************************************************"
echo -e " "

echo "------------------ Avant simplification -----------------------"

echo -e " "
	./test_contours_eps $var
echo -e " "

echo "------- Simplification par Courbe de Bezier 3 avec d = $1 --------"

echo -e " "
	./test_simplification_bezier_3 $var $1
echo -e " "


done
