#include <stdio.h>
#include <stdbool.h>
#include "arbre.h"


// ######################### PROTOTYPES DES FONCTIONS DU MAIN ####################################


/* Fonction qui affiche le menu général au lancement
 */
void menu();

/* Fonction qui laisse choisir a l'utilisateur une option de menu
 * Retour : entier representant le choix parmi les options du menu
 */
int choix_menu();

/* Fonction qui recupere dans la ville de depart et celle d'arrivée de l'arbre des trajets
 * Paramètre depart: tableau pouvant contenir la ville de départ
 * Paramètre arrivee: tableau qui contient la ville d'arrivée
 * Paramètre villes: vecteur qui contient les villes du fichier villes.csv
 */
void recuperer_depart_arrivee(char* depart, char* arrivee, vecteur* villes);

/* Fonction qui correspond au premier choix du menu, afficher un trajet
 */
void afficher_un_trajet(noeud* racine);

/* Fonction qui correspond au deuxieme choix du menu, afficher tous les trajets
 */
void afficher_tous_trajets(noeud* racine, char* arrivee);

/* Fonction qui correspond au troisieme choix du menu, afficher le trajet le plus court
 */
void afficher_trajet_court(noeud* racine, char* arrivee);

/* Fonction qui correspond au troisieme choix du menu, afficher le trajet le plus rapide
 */
void afficher_trajet_rapide(noeud* racine, char* arrivee);

/* Fonction qui correspond au dernier choix du menu, afficher l'arbre des trajets
 */
void afficher_arbre_trajets(noeud* racine);

/* Fonction qui correspond au dernier choix du menu, quitter le programme et donc libérer en mémoire tout les pointeurs nécéssaires au projet
 */
void quitter_programme(noeud* racine, vecteur** villes, vecteur*** connexions);
 


//######################### FONCTION PROPRE AU MENU ####################################



void menu(){
	
	printf("Bienvenue dans le probleme de ce semestre : Construire un arbre des trajets concernant les villes de France! \n\n");
	
	//CHAREGEMENT EN MEMOIRE DES DONNEES
	char fichier_villes[] = "villes.csv";
	char fichier_connexions[] = "connexions.csv";
	vecteur* villes = ouvrir_charger_villes(fichier_villes);
	int nb_connexions = 0;
	//on va changer la valeur de nb_connexions dans la fonction, on le passe donc en pointeur
	vecteur** connexions = ouvrir_charger_connexions(fichier_connexions, &nb_connexions);
	
	//on vérifie la validité des pointeurs
	if(villes != NULL && connexions != NULL){
		//CHOIX DE L'UTILISATEUR SUR LA VILLE DE DEPART ET ARRIVEE ET GENEREATION DE L'ARBRE DES TRAJETS
		
		//on recupere un vecteur contenant les nombres de caractères de chaque ligne du fichier villes
		FILE* fichier = fopen(fichier_villes, "r");
		vecteur* caracteres_ligne = nombre_caracteres_par_ligne(fichier);
		//on récupère le maximum pour s'assurer que l'utilisateur rentre une ville valide
		int maximum_caracteres = maximum_vecteur_entier(caracteres_ligne);
		//on déclare deux tableaux statiques de chars qui vont contenir les villes choisies par l'utilisateur
		char *depart = (char*)malloc(sizeof(char) * maximum_caracteres);
		char *arrivee = (char*)malloc(sizeof(char) * maximum_caracteres);
		//on demande a l'utilisateur de saisir deux villes pour contruire l'arbre des trajets
		recuperer_depart_arrivee(depart, arrivee, villes);
		
		printf("Avant de construire l'arbre, veuillez renseigner une hauteur maximale : \n");
		int hauteur;
		scanf("%d", &hauteur);
		
		printf("\nConstruction de l'arbre des trajets...\n\n");
		
		noeud* racine = initialiser_racine(depart, connexions);
		construire_arbre(arrivee, hauteur, connexions, racine, nb_connexions);
		verifier_arbre_contient_arrivee(racine, &hauteur, arrivee, connexions, nb_connexions);
		
		printf("Arbre des trajets construit avec succes !\n\n");
		
		//on demande un choix parmi les options du menu
		int choix = choix_menu();
		bool continuer = true;
		while(continuer){
			
			switch(choix){
				//CHOIX 1
				case 1: 
					afficher_un_trajet(racine);
					choix = choix_menu();
					break;
				//CHOIX 2
				case 2: 
					afficher_tous_trajets(racine, arrivee);
					choix = choix_menu();
					break;
				//CHOIX 3
				case 3: 
					afficher_trajet_court(racine, arrivee);
					choix = choix_menu();
					break;
				//CHOIX 4
				case 4: 
					afficher_trajet_rapide(racine, arrivee);
					choix = choix_menu();
					break;
				//CHOIX 5
				case 5: 
					afficher_arbre_trajets(racine);
					choix = choix_menu();
					break;
				//CHOIX 6
				case 6: 
					quitter_programme(racine, &villes, connexions);
					continuer = false;
					break;
				}
		}
	}
	else{
		printf("Erreur lors du chargement des données, reessayez !\n");
	}
}

int choix_menu(){

	//on affiche le menu
	printf("\n--------------------- MENU ---------------------\n\n");
	printf("1. Afficher un trajet trouve.\n");
	printf("2. Afficher tous les trajets trouves.\n");
	printf("3. Afficher le trajet le plus court.\n");
	printf("4. Afficher le trajet le plus rapide.\n");
	printf("5. Afficher l'arbre des trajets.\n");
	printf("6. Quitter.\n\n");
	printf("------------------------------------------------\n\n");
	printf("Selectionnez votre choix a l'aide d'un numero : \n");
	int choix;
	scanf("%d", &choix);
	printf("\n");
	
	//si le choix n'est pas valide on rappelle recursivement la fonction
	if(choix <= 0 || choix > 6){
		printf("Choix non valide, reessayez ! \n");
		choix = choix_menu();
	}

	return choix;
}

void recuperer_depart_arrivee(char* depart, char* arrivee, vecteur* villes){
	if(villes != NULL){
		bool sont_valides = false;
		//afin que les deux villes soient valides, il faut que le fichier de villes contienne les deux villes et qu'elles soient différentes
		while(!sont_valides){
			printf("Veuillez saisir la ville de depart du trajet : \n");
			scanf("%s", depart);
			printf("\n");
			//on vérifie si la liste des villes contient bien la ville choisie par l'utilisateur
			bool depart_valide = verifier_contenance(villes, depart);
			while(!depart_valide){
				printf("Cette ville n'existe pas dans le fichier, veuillez resaisir une ville de depart : \n");
				scanf("%s", depart);
				printf("\n");
				depart_valide = verifier_contenance(villes, depart);
			}
			//Ici la premiere ville est valide, on applique la même logique pour la seconde
			printf("Veuillez saisir la ville d'arrivee du trajet : \n");
			scanf("%s", arrivee);
			printf("\n");
			bool arrivee_valide = verifier_contenance(villes, arrivee);
			while(!arrivee_valide){
				printf("Cette ville n'existe pas dans le fichier, veuillez resaisir une ville d'arrivee : \n");
				scanf("%s", arrivee);
				printf("\n");
				arrivee_valide = verifier_contenance(villes, arrivee);
			}
			//Ici les deux villes sont contenues dans le fichier, mais elles sont identiques, on redemande les deux choix
			if(strcmp(depart, arrivee) == 0){
				printf("Les deux villes rentrees sont les memes, veuillez recommencer !\n\n");
			}
			else{
				printf("Les deux villes rentrees sont valides, nous allons generer l'arbre des trajets !\n\n");
				sont_valides = true;
			}
		}
	}
}




//######################### CHOIX DU MENU (1, 2, 3, 4, 5) ####################################


//CES FONCTIONS SONT ORGANISEES EN FONCTIONS DES 5 CHOIX POSSIBLES DU MENU (LE DERNIER CHOIX CONSISTE A QUITTER LE PROGRAMME), ET REAFFICHEES A CHAQUE ACTIONS DE L'UTILISATEUR
//CHAQUE PARTIE CONTIENT UNE FONCTION PRINCIPALE (APPELEE DANS LE SWITCH GENERAL DU MENU) ET/OU DES SOUS-FONCTIONS POUR UNE MEILLEUR LISIBILITE


//------------------ Choix: 1 - Afficher un trajet (le premier trouvé)  -----------------------------

void afficher_un_trajet(noeud* racine){
	afficher_trajet(racine);
}

//------------------ Choix: 2 - Afficher tous les trajets  ---------------------------

void afficher_tous_trajets(noeud* racine, char* arrivee){
	vecteur* liste_arrivee = creation_vecteur();
	if(liste_arrivee != NULL){
		remplir_liste_arrivee(racine, arrivee, liste_arrivee);
		afficher_ensemble_trajets(racine, arrivee, liste_arrivee);
	}
	liberation_vecteur(&liste_arrivee);
}

//------------------ Choix: 3 - Afficher le(s) trajets le(s) plus court(s) en distance -----------------------------

void afficher_trajet_court(noeud* racine, char* arrivee){
	vecteur* liste_arrivee = creation_vecteur();
	if(liste_arrivee != NULL){
		remplir_liste_arrivee(racine, arrivee, liste_arrivee);
		printf("TRAJET(S) LE(S) PLUS COURT(S) : \n\n");
		afficher_trajet_distance(racine, arrivee, liste_arrivee);
	}
	liberation_vecteur(&liste_arrivee);
}

//------------------ Choix: 4 - Afficher le(s) trajets le(s) plus court(s) en duree -----------------------------

void afficher_trajet_rapide(noeud* racine, char* arrivee){
	vecteur* liste_arrivee = creation_vecteur();
	if(liste_arrivee != NULL){
		remplir_liste_arrivee(racine, arrivee, liste_arrivee);
		printf("TRAJET(S) LE(S) PLUS RAPIDE(S) : \n\n");
		afficher_trajet_duree(racine, arrivee, liste_arrivee);
	}
	liberation_vecteur(&liste_arrivee);
}

//------------------ Choix: 5 - Afficher l'abre des trajets  -----------------------------

void afficher_arbre_trajets(noeud* racine){
	printf("ARBRE DES TRAJETS : \n\n");
	afficher_arbre_arborescence(racine, 0);
}

//------------------ Choix: 6 - Quitter (libération de mémoire)  -----------------------------

void quitter_programme(noeud* racine, vecteur** villes, vecteur*** connexions){
		liberation_arbre(racine);
		free(racine -> donnees);
		free(racine);
		racine = NULL;
		liberation_vecteur(villes);
		free(villes);
		villes = NULL;
		int nb_lignes = 72;
		liberation_tableau_vecteurs(connexions, nb_lignes);
		free(connexions);
		connexions = NULL;
}



//################################ MAIN ############################################


int main(int argc, char **argv){
	menu();
	return 0;
}
