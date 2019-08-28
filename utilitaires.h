#include <stdio.h>



// ######################### FONCTION UTILITAIRES POUR LE PROJET ####################################


/*
 * Fonction qui saute une ligne dans un fichier
 * Paramètre taille : taille en caractères de la ligne a sauter dans le fichier
 * Paramètre fichier: le pointeur sur le fichier
 */
void passer_premiere_ligne(FILE* fichier, int taille);

/*
 * Fonction qui rcalcule la longueur d'une chaine de caractère
 * Paramètre chaine : chaine dont on souhaite calculer la longueur
 * Retour : la longueur de la chaine
 */
int longueur_chaine(char* chaine);

/*
 * Fonction qui convertit les duree passée dans le format h:m
 * Paramètre duree: la duree initiale en minute
 * Paramètre heures : un pointeur sur les heures en fin de fonction (on modifie la valeur du pointeur)
 * Paramètre minutres : un pointeur sur les minutes en fin de fonction (on modifie la valeur du pointeur)
 */
void convertir_duree_heures(int duree, int* heures, int* minutes);

/*
 * Fonction qui convertit une duree de chaine de caractères en minutes (ex: 2h06 = 126m)
 * Paramètre chaine: duree sous forme de char
 * Retour : duree entier en int
 */
int convertir_duree_minutes(char* duree);
