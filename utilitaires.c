#include "utilitaires.h"
#include <stdlib.h>




// ######################### FONCTION UTILITAIRES POUR LE PROJET ####################################




void passer_premiere_ligne(FILE* fichier, int taille){
	if(fichier != NULL){
		//on déclare ce tableau pour passser directement a la ligne après "ville" dans le fichier, il est donc de taille fixe 'taille' en nb de caractères du premier mot + 2 pour \0 et \n + 1 pour le debut du fichier '(' soit taille + 3.
		char tab[taille + 3];
		//on passe a la ligne suivante
		fgets(tab, taille + 2, fichier);
		//on libère l'espace pour le tableau
		free(tab);
	}
}

int convertir_duree_minutes(char* duree){
	int resultat = 0;
	if(duree != NULL){
		//on recupere la donnees avant les deux points, il s'agit des heures
		char* heures = strtok(duree, ":");
		//on multiplie les heures obtenue par 60 pour les avoir en minutes
		int heure_en_minutes = (int)atof(strdup(heures)) * 60;
		//on déplace le pointeur après les deux points pour acceder aux minutes
		duree = strtok(NULL, ":");
		//(int)atof(duree)) cast notre duree en minutes
		resultat = heure_en_minutes + (int)atof(duree);
	}
	return resultat;
}

void convertir_duree_heures(int duree, int* heures, int* minutes){
	if(heures != NULL && minutes != NULL){
		*heures = duree / 60;
		*minutes = duree % 60;
	}
}

int longueur_chaine(char* chaine){
	int longueur = 0;
	if(chaine != NULL){
		while(chaine[longueur] != '\0'){
			longueur++;
		}
	}
	return longueur;
}


