
--------------------------------- fonctionnement -----------------------------------------

le programe  "test_sortie_eps"  prend en argument une image et crée trois images: 

	<nom_image>_mode_1.eps	(Tracé du contour avec segments)

	<nom_image>_mode_2.eps	(Tracé du contour avec segments et points)

	<nom_image>_mode_3.eps	(Remplissage du contour)

------------------------------------------------------------------------------------------

Remarque : Pour que les contours soient clairs (surtout pour le mode 2), lors de la 
génération des fichiers ".eps", nous avons intentionnellement fait le choix d'ajouter un 
cadre (contour) de pixels blancs.  



########################### Génération manuelle des images ###############################
#                                                                                        #
#  Pour générer les images manuellement entrer la commande:                              #
#	./test_sortie_eps <nos_images/nom image>                                             #
#                                                                                        #
#  NB: les images à tester doivent etre placées dans le répértoire nos_images/           #
#  (c-à-d il faut passer le nom de l'image sous la forme : nos_images/nom image)         #
#                                                                                        #
##########################################################################################




######################### Génération automatique des images ##############################
#                                                                                        #
#  Pour générer les images automatiquement, on a créé un bash "exec.sh" pour executer    #
#  le programme sur toutes les images situées dans le répértoire nos_images/ et les      #
#  afficher l'une après l'autre à l'aide de l'interface gv.                              #
#                                                                                        #
##########################################################################################




------------------------------------ Commandes -------------------------------------------
  
 make clean_eps : supprimmer tous les fichier.eps
  
 ./exec.sh : exécuter le programme sur toutes les images situées au répértoire nos_images/