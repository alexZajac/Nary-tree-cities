#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "arbre.h"


infos_noeud* initialiser_donnees_noeud(char* ville, int distance, int duree, bool contient_arrivee){
	infos_noeud* resultat = NULL;
	
	if(ville != NULL){
		//on alloue l'espace pour les donnees du noeud
		resultat = (infos_noeud*)malloc(sizeof(infos_noeud));
		
		int longueur = longueur_chaine(ville);
		//on alloue l'espace pour la ville
		resultat -> ville = (char*)malloc(sizeof(char) * longueur);
		
		//affectation
		if(resultat -> ville != NULL){
			resultat -> ville = ville;
			resultat -> distance = distance;
			resultat -> duree = duree;
			resultat -> contient_arrivee = contient_arrivee;
		}
	}
	return resultat;
}

noeud* initialiser_racine(char* depart, vecteur** matrice_connexions){
	
	noeud* resultat = NULL;
	
	if(depart != NULL){
		resultat = (noeud*)malloc(sizeof(noeud));
		//création de l'espace mémoire du noeud racine
		infos_noeud* donnees_noeud = initialiser_donnees_noeud(depart, 0, 0, false);
		//durée et distance à 0 car il s'agit du départ du trajet et donc de la première ville parcouru
		//false car le trajet ne continet pas encore l'arrivée
		if(resultat != NULL){
			resultat -> fils = NULL;
			resultat -> frere_droit = NULL;
			resultat -> frere_gauche = NULL;
			resultat -> parent = NULL;
			//initialisation des noeuds relatifs à celui créé à NULL
			resultat -> donnees = donnees_noeud;
		}
	}
	return resultat;
}

noeud* determiner_noeud_fils(noeud* parent, char* arrivee_finale, vecteur** matrice_connexions, int* hauteur_racine, int nb_connexions){
	noeud* resultat = NULL;
	
	//si nos pointeurs sont valides
	if(parent != NULL && arrivee_finale != NULL && (*matrice_connexions) != NULL && hauteur_racine != NULL){
			//on continue ssi on a a pas atteint la ville d'arrivee
			if(strcmp(parent -> donnees -> ville, arrivee_finale) != 0){
				char* depart = parent -> donnees -> ville;
				bool premier_fils_trouve = false;
				
				//on parcourt toutes les connexions possibles de notre tableau de vecteurs
				for(int i = 0; i < nb_connexions; i++){
					
					char* depart_fichier = (char*)obtenir_element_position(matrice_connexions[i], 0);
					//si le depart (ville du parent) est la meme que celle du fichier
					if(strcmp(depart, depart_fichier) == 0){
						
						char* arrivee_fichier = (char*)obtenir_element_position(matrice_connexions[i], 1);
						//on regarde si la ville d'arrivee de la connexion n'a pas ete parcourue
						if(ville_non_parcourue(parent, arrivee_fichier)){
							
							//on recupere la distance et duree du trajet
							int distance = (int)atof((char*)obtenir_element_position(matrice_connexions[i], 2));
							int duree = convertir_duree_minutes((char*)obtenir_element_position(matrice_connexions[i], 3));
							
							//si on a pas encore trouve de fils pour ce parent (i.e. premier trajet possible pour une ville)
							if(!premier_fils_trouve){
								
								//on alloue l'espace pour le fils
								resultat = (noeud*)malloc(sizeof(noeud));
								premier_fils_trouve = true;
								//si on peut encore placer un fils après celui ci, on alloue de l'espace pour l'accuellir
								if(*hauteur_racine > 1){
									resultat -> fils = (noeud*)malloc(sizeof(noeud));
								}
								else{
									resultat -> fils = NULL;
								}
								//affectation
								resultat -> frere_gauche = NULL;
								resultat -> frere_droit = NULL;
								resultat -> parent = parent;
								resultat -> donnees = initialiser_donnees_noeud(arrivee_fichier, distance + parent -> donnees -> distance, duree + parent -> donnees -> duree, false);
								
								//s'il s'agit de l'arrivee finale de l'utilisateur, on passe le fait que ce trajet contient l'arrivee
								if(strcmp(arrivee_finale, arrivee_fichier) == 0){
									resultat -> donnees -> contient_arrivee = true;
									passer_contenance_arrivee_parents(parent);
								}
							}
							
							else{
								//on alloue l'espace pour le frere du premier fils
								noeud* frere = (noeud*)malloc(sizeof(noeud));
								if(frere != NULL){
									if(*hauteur_racine > 1){
										frere -> fils = (noeud*)malloc(sizeof(noeud));
									}
									else{
										frere -> fils = NULL;
									}
									frere -> frere_gauche = resultat;
									frere -> frere_droit = NULL;
									frere -> parent = parent;
									frere -> donnees = initialiser_donnees_noeud(arrivee_fichier, distance + parent -> donnees -> distance, duree + parent -> donnees -> duree, false);
									
									if(strcmp(arrivee_finale, arrivee_fichier) == 0){
										frere -> donnees -> contient_arrivee = true;
										passer_contenance_arrivee_parents(parent);
									}
								}
								//on affecte au fils du parent un frere
								resultat -> frere_droit = frere;
								//on se déplace sur la branche
								resultat = resultat -> frere_droit;
							}
						}
					}
				}
			}
	}
	return resultat;
}

void passer_contenance_arrivee_parents(noeud* arrivee){
	if(arrivee != NULL){
		if(arrivee -> donnees -> contient_arrivee == false){
			arrivee -> donnees -> contient_arrivee = true;
		}
		passer_contenance_arrivee_parents(arrivee -> parent);
	}
}

bool ville_non_parcourue(noeud* futur_noeud, char* ville){
	bool resultat = true;
	if(futur_noeud != NULL && ville != NULL){
		//tant qu'on a pas atteint le parent on continue de tester
		while(futur_noeud -> parent != NULL){
			//si une fois la ville est parcourue, on arrete
			if(strcmp(futur_noeud -> parent -> donnees -> ville, ville) == 0){
				resultat = false;
				break;
			}
			futur_noeud = futur_noeud -> parent;
		}
	}
	return resultat;
}

void construire_arbre(char* arrivee, int hauteur, vecteur** connexions, noeud* racine, int nb_connexions){
	if(racine != NULL){
		//etant donne qu'on determine le fils du noeud a chaque fois, tant que la hauteur > 0 et non >= 0
		if(hauteur > 0){
			//on construit l'arbre recursivement fils, puis frer egauche
			racine -> fils = determiner_noeud_fils(racine, arrivee, connexions, &hauteur, nb_connexions);
			//la hauteur diminue uniquement si on passe au fils
			construire_arbre(arrivee, hauteur - 1, connexions, racine -> fils, nb_connexions);
			construire_arbre(arrivee, hauteur, connexions, racine -> frere_gauche, nb_connexions);
		}
	}
}

void verifier_arbre_contient_arrivee(noeud* racine, int* hauteur, char* arrivee, vecteur** connexions, int nb_connexions){
	if(racine != NULL && hauteur != NULL && arrivee != NULL && connexions != NULL){
		while(racine -> donnees -> contient_arrivee == false){
			printf("L'arbre est trop petit pour contenir un trajet jusqu'a l'arrivee...\n");
			printf("Veuillez resaisir une hauteur plus grande : \n");
			scanf("%d", &hauteur);
			printf("\nConstruction de l'arbre des trajets...\n\n");
			construire_arbre(arrivee, hauteur, connexions, racine, nb_connexions);
		}
	}
}

void afficher_arbre_arborescence(noeud* racine, int offset){
	//offset nous permet de visualiser plus clairement chaque niveau de l'arbre
	for(int i = 0; i < offset; i++){
		printf("\t");
	}
	if(racine != NULL){
			printf("|- %s \n", racine -> donnees -> ville);
			//on augmente donc offset quand on affiche le fils (niveau + 1)
			afficher_arbre_arborescence(racine -> fils, offset + 1);
			afficher_arbre_arborescence(racine -> frere_gauche, offset);
	}
	else {
		printf("\n");
	}
}

void afficher_trajet(noeud* racine){
	if(racine != NULL){
		//on affiche le trajet que si le noeud courant contient l'arrivee
		if(racine -> donnees -> contient_arrivee){
			if(racine -> parent == NULL){
				printf("%s", racine -> donnees -> ville);
			}
			else{
				afficher_donnees_intermediaires(racine);
			}
			if(racine -> fils == NULL){
				afficher_donnees_feuille(racine);
			}
			afficher_trajet(racine -> fils);
		}
		//sinon on passe au frere gauche
		else{
			afficher_trajet(racine -> frere_gauche);
		}
	}
}

void afficher_ensemble_trajets(noeud* racine, char* arrivee, vecteur* liste_arrivee){
	if(racine != NULL && arrivee != NULL && liste_arrivee != NULL){
		//on, affiche chaque trajet dans la liste des arrivees
		for(int i = 0; i < liste_arrivee -> taille; i++){
			printf("TRAJET : %d \n\n", i + 1);
			afficher_trajet_parents((noeud*)obtenir_element_position(liste_arrivee, i));
		}
		printf("%d TRAJETS TROUVES\n\n", liste_arrivee -> taille);
	}
}

void afficher_donnees_intermediaires(noeud* racine){
	if(racine != NULL){
		printf("\n  |\n");
		int heures, minutes;
		//on convertit les min et h:m
		convertir_duree_heures(racine -> donnees -> duree - racine -> parent -> donnees -> duree, &heures, &minutes);
		printf("[%dkm de distance et %02dh%02dm de duree]\n", racine -> donnees -> distance - racine -> parent -> donnees -> distance, heures, minutes);
		printf("  |\n");
		printf("%s", racine -> donnees -> ville);
	}
}

void afficher_donnees_feuille(noeud* racine){
	if(racine != NULL){
		printf(" (DISTANCE TOTALE: %dkm et", racine -> donnees -> distance);
		int heures, minutes;
		convertir_duree_heures(racine -> donnees -> duree, &heures, &minutes);
		printf(" DUREE TOTALE: %02dh%02dm)\n\n\n", heures, minutes);
	}
}

void afficher_trajet_parents(noeud* racine){
	if(racine != NULL){
		//on appelle recursivement jusqu'a arriver au parent
		afficher_trajet_parents(racine -> parent);
		//si on l'a atteint on affiche ses donnees
		if(racine -> parent == NULL){
			printf("%s", racine -> donnees -> ville);
		}
		//sinon on affiche les donnees intermediaires entre deux villes
		else{
			afficher_donnees_intermediaires(racine);
		}
		//si c'est une feuille on affiche la distance et duree totale
		if(racine -> fils == NULL){
			afficher_donnees_feuille(racine);
		}
	}
}

void remplir_liste_arrivee(noeud* racine, char* arrivee, vecteur* liste_arrivee){
	if(racine != NULL && liste_arrivee != NULL){
		if(strcmp(arrivee, racine -> donnees -> ville) == 0){
			ajouter_vecteur(liste_arrivee, racine);
		}
		//on ajoute la racine de l'arbre comme premier noeud du vecteur des noeuds parcourus
		remplir_liste_arrivee(racine -> fils, arrivee, liste_arrivee);
		remplir_liste_arrivee(racine -> frere_gauche, arrivee, liste_arrivee);
		//on ajoute au vecteur des villes parcourues le noeud par lequel on vient de passer dans l'arbre
	}
}

void afficher_trajet_distance(noeud* racine, char* arrivee, vecteur* liste_arrivee){
	if(racine != NULL && arrivee != NULL && liste_arrivee != NULL && liste_arrivee -> taille > 0){
		//à la condition que les villes de départ et d'arrivée soient fournies, et qu'il y ait eu au moins un segment entre 2 villes parcouru
		tri_rapide_distance(liste_arrivee, 0, liste_arrivee -> taille - 1);
		afficher_trajet_parents((noeud*)obtenir_element_position(liste_arrivee, 0));
	}
}

void afficher_trajet_duree(noeud* racine, char* arrivee, vecteur* liste_arrivee){
	if(racine != NULL && arrivee != NULL && liste_arrivee != NULL && liste_arrivee -> taille > 0){
		//à la condition que les villes de départ et d'arrivée soient fournies, et qu'il y ait eu au moins un segment entre 2 villes parcouru
		tri_rapide_duree(liste_arrivee, 0, liste_arrivee -> taille - 1);
		afficher_trajet_parents((noeud*)obtenir_element_position(liste_arrivee, 0));
	}
}


    


void liberation_arbre(noeud* racine){
	if(racine != NULL){
		liberation_arbre(racine -> frere_gauche);
		//on libère chaque noeud de l'arbre de manière récursive au coeur de cette fonction
		liberation_arbre(racine -> fils);
		//en procédant de manière inverse à la construction de l'arbre, on libère les noeuds en partant des noeuds finaux des branches de l'arbre (d'où l'appel de lafonction pour le frère gauche puis pour le fils avant de libérer le noeud et remojnter dans l'arbre)
		free(racine -> frere_gauche);
		racine -> frere_gauche = NULL;
		free(racine -> donnees);
		//une fois les espaces des noeuds fils et frères libérés, on libère l'espace de stockage des données relatives au noeud
		free(racine -> fils);
		racine -> fils = NULL;
		//puis la racine elle-même est mise à NULL avant de remonter dans l'arbre et passer à la racine supérieure
	}
}

void tri_rapide_duree(vecteur* arrivees, int debut, int fin){ 
	if(arrivees != NULL){
		//si on est pas a la fin du tri
		if(debut < fin){ 
			//recupere le nouvel index du pivot
			int index_partition = partition_duree(arrivees, debut, fin); 
	  
			// On trie separement les elements apres et avant le pivot
			tri_rapide_duree(arrivees, debut, index_partition - 1); 
			tri_rapide_duree(arrivees, index_partition + 1, fin); 
		} 
	}
} 

void tri_rapide_distance(vecteur* arrivees, int debut, int fin){ 
	if(arrivees != NULL){
		//si on est pas a la fin du tri
		if(debut < fin){ 
			//recupere le nouvel index du pivot
			int index_partition = partition_distance(arrivees, debut, fin); 
	  
			// On trie separement les elements apres et avant le pivot
			tri_rapide_distance(arrivees, debut, index_partition - 1); 
			tri_rapide_distance(arrivees, index_partition + 1, fin); 
		} 
	}
} 

int partition_duree(vecteur* arrivees, int debut, int fin){ 
	//on initialise i en dehors du tableau
	int i = (debut - 1); 
	if(arrivees != NULL){
		//on initilaise le pivot au dernier element
		int pivot = ((noeud*)obtenir_element_position(arrivees, fin)) -> donnees -> duree;
		// pour tous les elements restants
		for(int j = debut; j < fin; j++){ 
			//Si l'element courant est plus petit ou egal que le pivot
			if (((noeud*)obtenir_element_position(arrivees, j)) -> donnees -> duree <= pivot){ 
				i++; //on incrémente l'index du plus petit element 
				//on permute les deux elements
				permuter((noeud*)obtenir_element_position(arrivees, i), (noeud*)obtenir_element_position(arrivees, j)); 
			} 
		} 
		//après avoir tout parcouru, on permute le pivot et l'element a l'index i + 1
		permuter((noeud*)obtenir_element_position(arrivees, i + 1), (noeud*)obtenir_element_position(arrivees, fin)); 
	}
	return (i + 1); 
} 

int partition_distance(vecteur* arrivees, int debut, int fin){ 
	//on initialise i en dehors du tableau
	int i = (debut - 1); 
	if(arrivees != NULL){
		//on initilaise le pivot au dernier element
		int pivot = ((noeud*)obtenir_element_position(arrivees, fin)) -> donnees -> distance;
		// pour tous les elements restants
		for(int j = debut; j < fin; j++){ 
			//Si l'element courant est plus petit ou egal que le pivot
			if (((noeud*)obtenir_element_position(arrivees, j)) -> donnees -> distance <= pivot){ 
				i++; //on incrémente l'index du plus petit element 
				//on permute les deux elements
				permuter((noeud*)obtenir_element_position(arrivees, i), (noeud*)obtenir_element_position(arrivees, j)); 
			} 
		} 
		//après avoir tout parcouru, on permute le pivot et l'element a l'index i + 1
		permuter((noeud*)obtenir_element_position(arrivees, i + 1), (noeud*)obtenir_element_position(arrivees, fin)); 
	}
	return (i + 1);
} 


void permuter(noeud* a, noeud* b){ 
	//noeud temporaire pour stocker les infos du noeud a
	noeud temp = *a; 
	*a = *b; 
	*b = temp; 
} 

 