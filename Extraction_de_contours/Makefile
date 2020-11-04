 #############################################################################
# Fichier Makefile 
# UE MAP401 - DLST - UGA - 2017/2018
#############################################################################
# utilisation des variables internes $< $@ $*
# $@ : correspond au nom de la cible
# $< : correspond au nom de la premiere dependance
# $^ : correspond à toutes les dépendances
# $* : correspond au nom du fichier sans extension 
#       (dans les regles generiques uniquement)
#############################################################################
# information sur la regle executee avec la commande @echo
# (une commande commancant par @ n'est pas affichee a l'ecran)
#############################################################################


#############################################################################
# definition des variables locales
#############################################################################

# compilateur C
CC = gcc

# chemin d'acces aux librairies (interfaces)
INCDIR = .

# chemin d'acces aux librairies (binaires)
LIBDIR = .

# options pour l'édition des liens
LDOPTS = -L$(LIBDIR) -lm

# options pour la recherche des fichiers .o et .h
INCLUDEOPTS = -I$(INCDIR)

# options de compilation
COMPILOPTS = -g -Wall $(INCLUDEOPTS)

# liste des executables
EXECUTABLES = test_contours_eps 


#############################################################################
# definition des regles
#############################################################################

########################################################
# la règle par défaut
all : $(EXECUTABLES) 

########################################################
# regle generique : 
#  remplace les regles de compilation separee de la forme
#	module.o : module.c module.h
#		$(CC) -c $(COMPILOPTS) module.c
%.o : %.c %.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module "$*
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<

########################################################
# regles explicites de compilation separee de modules
# n'ayant pas de fichier .h ET/OU dependant d'autres modules

image_pbm.o : image_pbm.c image_pbm.h types_macros.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module image"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<
		
geometrie_2D.o : geometrie_2D.c geometrie_2D.h 
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module geometrie_2D"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<

extraction_contour.o : extraction_contour.c extraction_contour.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module extraction_contour"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<

TTV_Point.o : TTV_Point.c TTV_Point.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module TTV_Point"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<


sortie_eps.o : sortie_eps.c sortie_eps.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module sortie_eps"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<


test_contours_eps.o : test_contours_eps.c 
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module tous_contours_eps"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<

########################################################
# regles explicites de creation des executables

test_contours_eps : test_contours_eps.o sortie_eps.o TTV_Point.o extraction_contour.o geometrie_2D.o image_pbm.o
	@echo ""
	@echo "---------------------------------------------"
	@echo "Creation de l'executable tous_contours_eps"$@
	@echo "---------------------------------------------"
	$(CC) $^ $(LDOPTS) -o $@
# regle pour "nettoyer" le répertoire
clean:
	rm -fR $(EXECUTABLES) *.o *.eps
