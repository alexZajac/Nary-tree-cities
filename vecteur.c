#include "vecteur.h"
#include <stdlib.h>
#include <stdbool.h>


vecteur* creation_vecteur(){
	//on alooue l'espace mémoire pour un vecteur
	vecteur* vec = (vecteur*)malloc(sizeof(vecteur));
	
	//on l'initialise
	if(vec != NULL){
		vec -> taille = 0; 
		vec -> donnees = NULL;
	}
	return vec;
}

int taille_vecteur(vecteur* p_vec){
	int taille = 0;
	if(p_vec != NULL){
		taille = p_vec -> taille;
	}
	return taille;
}

void redimensionner_vecteur(vecteur* p_vec, int taille){
	if(p_vec != NULL){
		//Ici, on réalloue l'espace en mémoire des données de notre vecteur en fonction de la taille passee en paramètre
		void** donnees = (void**)realloc(p_vec -> donnees, sizeof(void*) * taille);
		if(donnees != NULL){
			p_vec -> donnees = donnees;
			p_vec -> taille = taille;
		}
	}
}

void ajouter_vecteur(vecteur* p_vec, void* elem){
	if(p_vec != NULL){
		//avant d'ajouter un element a un vecteur, il faut redimensionner sa taille pour contenir un element en plus
		redimensionner_vecteur(p_vec, p_vec -> taille + 1);
		p_vec -> donnees[p_vec -> taille - 1] = elem;
	}
}

void ajouter_element_position(vecteur* p_vec, void* elem, int position){
	if(p_vec != NULL){
		//si la position est valide
		if(position >= 0 && position < p_vec -> taille){
			p_vec -> donnees[position] = elem;
		}
	}
}

void* obtenir_element_position(vecteur* p_vec, int position){
	void* elem = NULL;
	//ici l'element retourne est un pointeur void, qu'il faudra caster vers le type de donnes que nous avons placé dans le vecteur
	if(p_vec != NULL){
		if(position >= 0 && position < p_vec -> taille){
			elem = p_vec -> donnees[position];
		}
	}
	return elem;
}

void* obtenir_dernier_element(vecteur* p_vec){
	void* elem = NULL;
	if(p_vec != NULL){
		if(p_vec -> taille > 0){
			elem = p_vec -> donnees[p_vec -> taille - 1];
		}
	}
	return elem;
}

void afficher_vecteur_entier(vecteur* p_vec){
	if(p_vec != NULL){
		for(int i = 0; i < p_vec -> taille; i++){
			//pour affichier un entier, il faut obtenir l'element (de type void*), le caster vers un pointeur int, et prendre son contenu avec *
			printf("%d ", *((int*)obtenir_element_position(p_vec, i)));
		}
	}
}


void afficher_tableau_vecteurs(vecteur** p_vec, int lignes){
	if(p_vec != NULL){
		for(int i = 0; i < lignes; i++){
			for(int j = 0; j < (*p_vec) -> taille; j++){
				//le formattage choisi pour afficher la chaine etant %s, pas besoin de prendre la valeur contenue dans char* mais bien son pointeur
				printf("%s ", (char*)obtenir_element_position(p_vec[i], j));
			}
			printf("\n");
		}
	}
}

void afficher_vecteur_char(vecteur* p_vec){
	if(p_vec != NULL){
		for(int i = 0; i < p_vec -> taille; i++){
			printf("%s\n", (char*)obtenir_element_position(p_vec, i));
		}
	}
}

int maximum_vecteur_entier(vecteur* p_vec){
	int max = 0;
	if(p_vec != NULL){
		for(int i = 0; i < p_vec -> taille; i++){
			//on effectue une comparaison sur tous les elements du tableau (il faut qu'il soit composé d'entier) afin de trouver le maximum
			int elem = *((int*)obtenir_element_position(p_vec, i));
			if(elem > max){
				max = elem;
			}
		}
	}
	return max;
}

void liberation_vecteur(vecteur** p_vec){
	if(*p_vec != NULL){
		//pour liberer un vecteur, nous avons besoin d'un double pointeur car sinon, la variable en paramètre n'est qu'une copie de notre pointeur sur p_vec et est détruite a la fin de cette fonction
		free((*p_vec) -> donnees);
		free((*p_vec));
		*p_vec = NULL;
	}
}

void liberation_tableau_vecteurs(vecteur*** p_vec, int nb_lignes){
	if(**p_vec != NULL){
		//même principe que plus haut, nous allons libérer ligne par ligne le tableau de vecteur
		for(int i = 0; i < nb_lignes; i++){
			liberation_vecteur((p_vec[i]));
		}
		free((**p_vec));
		**p_vec = NULL;
	}
}

vecteur* nombre_caracteres_par_ligne(FILE* fichier){
	vecteur* resultat = NULL;
	//on vérifie la validité de l'ouverture fichier
	if(fichier != NULL){
		//on initialise notre vecteur de données
		resultat = creation_vecteur();
		
		//on initialise un compteur de caractères, et un caractère qui correspond a la premiere lettre lue a l'endroit actuel du curseur + 1
		int compteur = 0;
		char c = fgetc(fichier);
		
		//on parcourt tous le fichier
		while(c != EOF){
			//tant que nous n'atteignons pas la fin de la ligne
			while(c != '\n'){
				c = fgetc(fichier);
				compteur++;
			}
			
			//on déclare un pointeur d'entier sur le nombre de caracteres et on ajoute ce nombre dans notre vecteur
			int *nb_caracteres = (int*)malloc(sizeof(int));
			*nb_caracteres = compteur + 2; //on ajoute le nombre de lettres du mot + '\0' + '\n'
			ajouter_vecteur(resultat, nb_caracteres); 
			//on réinitialise nos valeurs
			compteur = 0;
			c = fgetc(fichier);
		}
		
	}
	//on retourne au début du fichier
	rewind(fichier);
	
	return resultat;
}

vecteur** ouvrir_charger_connexions(char nom_fichier[], int* nb_connexions){

	vecteur** tableau_connexions = NULL;
	FILE* fichier = fopen(nom_fichier, "r");
	if(fichier != NULL && nb_connexions != NULL){
		//on saute la premiere ligne du fichier 'ville1,ville2,distance,duree' donc de taille 28
		passer_premiere_ligne(fichier, 28);
		//on récupère un tableau qui a pour taille le nombre de lignes dans le fichier et qui contient le nombre de caractères pour chaque ligne
		vecteur* tab_nb_caracteres = nombre_caracteres_par_ligne(fichier);
		//nous sommes revenus au debut du fichier après la dernière fonction, on repasse donc la premiere ligne
		passer_premiere_ligne(fichier, 28);
		//on initialise nos indexs de matrice et notre taille de tableau de caracteres
		int i = 0;
		int taille_tableau_caracteres = taille_vecteur(tab_nb_caracteres);
		//on mets a jour le nombre de connexions possibles
		*nb_connexions = taille_tableau_caracteres;
		
		//on initialise notre matrice de vecteurs avec le nombre de lignes et 4 colonnes quoi qu'il arrive : 'ville1 ville2 distance duree' 
		tableau_connexions = (vecteur**)malloc(sizeof(vecteur*) * taille_tableau_caracteres);
		for(int i = 0; i < taille_tableau_caracteres; i++){
			tableau_connexions[i] = creation_vecteur();
		}
		
		//on accède au premier element du tableau de nombre de caractères et on déclare un tableau pouvant l'accueillir
		void* premier_element = obtenir_element_position(tab_nb_caracteres, i);
		int nb_caracteres_ligne = *((int*)premier_element);
		char *ligne = (char*)malloc(sizeof(char) * (nb_caracteres_ligne));
		
		if(ligne != NULL){
			//on boucle jusqu'à la fin du fichier
			while(fgets(ligne, nb_caracteres_ligne - 1, fichier) != NULL){
				
				//si le buffer n'est pas sur un caractère de retour a la ligne (i.e. une ville)
				if(ligne[0] != '\n'){
					//on crée une variable qui correspond a la partie de la ligne jusqu'à la virgule
					char* nouvelle_ligne = strtok(ligne, ",");
					//on continue jusqu'à ce que le pointeur ne pointe plus sur rien (délimotation finie)
					while(nouvelle_ligne != NULL){
						//on a besoin ici de copier la chaine dans une autre varaible car chaque element du vecteur pointe sur une chaine, et on va modifier 'nouvelle_ligne' après chaque itération de cette boucle
						char* element_matrice = strdup(nouvelle_ligne);
						ajouter_vecteur(tableau_connexions[i], element_matrice);
						//on récupère la prochaine chaine après le délimiteur ','
						nouvelle_ligne = strtok(NULL, ",");
					}
					i++;
					//si nous n'avons pas attient la fin du tableau de caractères
					if(i < taille_tableau_caracteres){
						//on recupère le nombre de caractère de la prochaine ligne
						nb_caracteres_ligne = *((int*)obtenir_element_position(tab_nb_caracteres, i));
						//on réalloue l'espace nécéssaire a la ligne
						ligne = (char*)realloc(ligne, sizeof(char) * (nb_caracteres_ligne));
					}
				}
			}
		}
		fclose(fichier);
	}
	return tableau_connexions;
}

vecteur* ouvrir_charger_villes(char nom_fichier[]){

	vecteur* tableau_villes = creation_vecteur();
	FILE* fichier = fopen(nom_fichier, "r");
	if(fichier != NULL){
		//on saute la premiere ligne du fichier 'ville' donc de taille 5
		passer_premiere_ligne(fichier, 5);
		//on récupère un tableau qui a pour taille le nombre de lignes dans le fichier et qui contient le nombre de caractères pour chaque ligne
		vecteur* tab_nb_caracteres = nombre_caracteres_par_ligne(fichier);
		//nous sommes revenus au debut du fichier après la dernière fonction, on repasse donc la premiere ligne
		passer_premiere_ligne(fichier, 5);
		
		//on initialise notre index de tableau et notre taille de tableau de caracteres
		int i = 0;
		int taille_tableau_caracteres = taille_vecteur(tab_nb_caracteres);
		
		//on accède au premier element du tableau de nombre de caractères et on déclare un tableau pouvant l'accueillir
		void* premier_element = obtenir_element_position(tab_nb_caracteres, i);
		int nb_caracteres_ville = *((int*)premier_element);
		char *ligne = (char*)malloc(sizeof(char) * (nb_caracteres_ville));
		
		if(ligne != NULL){
			//on boucle jusqu'à la fin du fichier
			while(fgets(ligne, nb_caracteres_ville - 1, fichier) != NULL){
				
				//si le buffer n'est pas sur un caractère de retour a la ligne (i.e. une ville)
				if(ligne[0] != '\n'){
					//on duplique la ligne dans une nouvelle varaible afin de pourvoir l'ajouter au vecteur
					char* nouvelle_ligne = strdup(ligne);
					ajouter_vecteur(tableau_villes, nouvelle_ligne);
					i++;
					//si nous n'avons pas attient la fin du tableau de caractères
					if(i < taille_tableau_caracteres){
						//on recupère le nombre de caractère de la prochaine ligne
						nb_caracteres_ville = *((int*)obtenir_element_position(tab_nb_caracteres, i));
						//on réalloue l'espace nécéssaire a la ligne
						ligne = (char*)realloc(ligne, sizeof(char) * (nb_caracteres_ville));
					}
				}
			}
		}
		fclose(fichier);
	}
	return tableau_villes;
}

bool verifier_contenance(vecteur* p_vec, char ville[]){
	bool resultat = false;
	//si le vecteur est traitable
	if(p_vec != NULL && p_vec -> donnees != NULL){
		//on récupère sa taille
		int taille = taille_vecteur(p_vec);
		for(int i = 0; i < taille; i++){
			char* elem = (char*)obtenir_element_position(p_vec, i);
			//on regarde si chacun de ses elements est la ville rechercher
			if(strcmp(elem, ville) == 0){
				resultat = true;
				//si oui, on peut arreter de chercher
				break;
			}
		}
	}
	return resultat;
}

