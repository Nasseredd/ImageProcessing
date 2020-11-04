#!/bin/bash

for var in nos_images/*; do
echo "----------------- $var -----------------"
	./test_contours_eps $var
done 

