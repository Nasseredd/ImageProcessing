#!/bin/bash

for var in nos_images/*; do
echo "----------------- $var -----------------"

echo "--------- Avant simplification ---------"
	./test_contours_eps $var

echo "------- Simplification avec d = $1 --------"
echo -e " "
	./test_simplification_de_contours $var $1 
echo -e " "

done 