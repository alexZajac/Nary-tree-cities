#include "vecteur.h"
#include "utilitaires.h"
#include <stdbool.h>

//on crée la structure des informations du noeud, c'est à dire le nom de la ville du noeud (pointeur sur chaine chaine de caractères), la distance et la durée séparant cette ville de la précedente (entiers, infos contenues dans le fichier 'connexions'), et l'information sur l'atteinte de la ville d'arrivée (booléen)
typedef struct
{
	char* ville;
	int distance;
	int duree;
	bool contient_arrivee;
} infos_noeud;

//on crée la structure du noeud de manière à pouvoir créer puis parcourir notre arbre des trajets : un pointeur renvoie vers les informations relatives au noeud (structure ci-dessus), puis des pointeurs permettent d'accéder aux noeud parent, fils et frères du noeud
typedef struct _noeud
{
	infos_noeud* donnees;
	struct _noeud* parent;
	struct _noeud* frere_droit;
	struct _noeud* frere_gauche;
	struct _noeud* fils;
} noeud;


/*
 * Fonction qui saute une ligne dans un fichier
 * Paramètre ville: pointeur vers le nom de la ville du noeud
 * Paramètre distance: valeur de la distance de la connexion
 * Paramètre duree: valeur de la durée de la connexion
 * Paramètre contient_arrivee: booléen dont l'état indique si la ville d'arrivée est atteinte ou non
 */
infos_noeud* initialiser_donnees_noeud(char* ville, int distance, int duree, bool contient_arrivee);

/*
 * Fonction qui initialise l'espace mémoire et les données du noeud racine de l'arbre en fonction de la ville de départ choisie 
 * Paramètre depart: pointeur vers le nom de la ville de départ
 * Paramètre matrice_connexions: tableau de vecteurs de connexions qui sert a reconstruire l'arbre si jamais il ne contient pas l'arrivee
 */
noeud* initialiser_racine(char* depart, vecteur** matrice_connexions);

/*
 * Fonction de recherche des noeuds fils d'un noeud racine, avec notre contrustion d'arbre en étage (un fils direct et lers autres fils comme frères de ce dernier)
 * Paramètre parent: pointeur sur le noeud parent dans l'arbre
 * Paramètre arrivee_finale: pointeur sur la ville d'arrivée souhaitée
 * Paramètre matrice_connexions: tableau de vecteurs de connexions qui sert a reconstruire l'arbre si jamais il ne contient pas l'arrivee
 * Paramètre hauteur_racine : valeur de la hauteur de l'arbre à laquelle est placée la racine (le noeud parent) considérée
 * Paramètre nb_connexions : nombre de connexions possibles par rapport au fichier
 */
noeud* determiner_noeud_fils(noeud* parent, char* arrivee_finale, vecteur** matrice_connexions, int* hauteur_racine, int nb_connexions);

/*
 * Fonction qui met à jour l'état du booléen sur la réalisation ou non de l'arrivée à destination
 * Paramètre arrivee: tableau qui contient la ville d'arrivée
 */
void passer_contenance_arrivee_parents(noeud* arrivee);

/*
 * Fonction pour vérifier si la ville proposée dans le noeud suivante a déjà été parcourue durant le trajet
 * Paramètre futur_noeud: pointeur vers le noeud proposé dans le tableau de connexions
 * Paramètre ville: pointeur vers le nom de la ville relative au noeud suivant dans les connexions
 */
bool ville_non_parcourue(noeud* futur_noeud, char* ville);

/*
 * Fonction de construction de l'arbre des trajets possibles entre 2 villes pour une hauteur donnée
 * Paramètre arrivee: tableau qui contient la ville d'arrivée
 * Paramètre hauteur : valeur de la hauteur de l'arbre
 * Paramètre connexions: tableau de vecteurs de connexions qui sert a reconstruire l'arbre si jamais il ne contient pas l'arrivee
 * Paramètre racine: pointeur sur la racine de l'arbre
 * Paramètre nb_connexions : nombre de connexions possibles par rapport au fichier
 */
void construire_arbre(char* arrivee, int hauteur, vecteur** connexions, noeud* racine, int nb_connexions);

/* Fonction qui vérifie que au moins une des feuilles de l'arbre atteint l'arrivee demandee
 * Paramètre racine: pointeur sur la racine de l'arbre
 * Paramètre hauteur : pointeur sur la hauteur de l'arbre
 * Paramètre arrivee: tableau qui contient la ville d'arrivée
 * Paramètre connexions: tableau de vecteurs de connexions qui sert a reconstruire l'arbre si jamais il ne contient pas l'arrivee
 * Paramètre nb_connexions : nombre de connexions possibles par rapport au fichier
 */
void verifier_arbre_contient_arrivee(noeud* racine, int* hauteur, char* arrivee, vecteur** connexions, int nb_connexions);

/*
 * Fonction d'affichage de l'arbre des trajets avec la méthode d'arborescence vue en TD
 * Paramètre racine: pointeur sur le noeud racine de l'arbre
 * Paramètre offset: 
 */
void afficher_arbre_arborescence(noeud* racine, int offset);

/*
 * Fonction qui affiche un seul des trajets 
 * Paramètre racine: pointeur sur le noeud racine de l'arbre
 */
void afficher_trajet(noeud* racine);

/*
 * Fonction qui affiche les uns en dessous des autres tous les trajets possibles entre la ville de départ et la ville d'arrivée fournies avec la hauteur de l'arbre comme contrainte
 * Paramètre racine: pointeur sur le noeud racine de l'arbre
 * Paramètre arrivee: pointeur sur le nom de la ville d'arrivée
 * Paramètre liste_arrivee: pointeur vers le vecteur qui contient les noeuds successifs par lesquels on est passé précédemment pour faire le trajet
 */
void afficher_ensemble_trajets(noeud* racine, char* arrivee, vecteur* liste_arrivee);

/*
 * Fonction avec un affichage des distance et durée lors d'une connexion entre 2 villes
 * Paramètre racine: pointeur sur le noeud racine de l'arbre
 */
void afficher_donnees_intermediaires(noeud* racine);

/*
 * Fonction avec un affichage des distance et durée totales d'un trajet une fois arrivé à une feuille de l'arbre
 * Paramètre racine: pointeur sur le noeud racine de l'arbre
 */
void afficher_donnees_feuille(noeud* racine);

/*
 * Fonction avec un affichage pour résumer un trajet
 * Paramètre racine: pointeur sur le noeud racine de l'arbre
 */
void afficher_trajet_parents(noeud* racine);

/*
 * Fonction qui complète le vecteur des noeuds parcourus lors d'un trajet
 * Paramètre racine: pointeur sur le noeud racine de l'arbre et donc correspondant au départ du trajet
 * Paramètre arrivee: pointeur sur la ville d'arrivée
 * Paramètre liste_arrivee: pointeur vers le vecteur qui contient les noeuds successifs par lesquels on est passé précédemment pour faire le trajet
 */
void remplir_liste_arrivee(noeud* racine, char* arrivee, vecteur* liste_arrivee);

/*
 * Fonction qui affiche la distance totale d'un trajet
 * Paramètre racine: pointeur sur le noeud racine de l'arbre et donc correspondant au départ du trajet
 * Paramètre arrivee: pointeur sur la ville d'arrivée
 * Paramètre liste_arrivee: pointeur vers le vecteur qui contient les noeuds successifs par lesquels on est passé précédemment pour faire le trajet
 */
void afficher_trajet_distance(noeud* racine, char* arrivee, vecteur* liste_arrivee);

/*
 * Fonction qui affiche la durée totale d'un trajet
 * Paramètre racine: pointeur sur le noeud racine de l'arbre et donc correspondant au départ du trajet
 * Paramètre arrivee: pointeur sur la ville d'arrivée
 * Paramètre liste_arrivee: pointeur vers le vecteur qui contient les noeuds successifs par lesquels on est passé précédemment pour faire le trajet
 */
void afficher_trajet_duree(noeud* racine, char* arrivee, vecteur* liste_arrivee);

/*
 * Fonction qui libère l'espace de stockage utilisé pour la construction de l'arbre
 * Paramètre racine: pointeur sur la racine de l'arbre. Au fur et à mesure du parcours de l'arbre, le noeud appelé racine sera modifié jusqu'à remonter à la racine principale de l'arbre
 */
void liberation_arbre(noeud* racine);

/*
 * Fonction qui trie de manière récursive le vecteur de noeud d'arrivées en fonction de leur distance (appelle parition_distance)
 * Paramètre arrivees: vecteur a trier
 * Paramètre debut: index de début du tri
 * Paramètre fin: index de fin du tri
 */
void tri_rapide_distance(vecteur* arrivees, int debut, int fin);

/*
 * Fonction qui trie de manière récursive le vecteur de noeud d'arrivées en fonction de leur duree (appelle parition_duree)
 * Paramètre arrivees: vecteur a trier
 * Paramètre debut: index de début du tri
 * Paramètre fin: index de fin du tri
 */
void tri_rapide_duree(vecteur* arrivees, int debut, int fin);

/*
 * Fonction qui trie les valeurs du vecteur de noeuds (selon le critère de la distance du trajet) en fonction d'un pivot choisi (gauche du pivot = inferieur au pivot) en fonction de leur distance
 * Paramètre arrivees: vecteur a partitionner
 * Paramètre debut: index de début du partitionnage
 * Paramètre fin: index de fin du partitionnage
*/
int partition_distance(vecteur* arrivees, int debut, int fin);

/*
 * Fonction qui trie les valeurs du vecteur de noeuds (selon le critère de la durée du trajet) en fonction d'un pivot choisi (gauche du pivot = inferieur au pivot) en fonction de leur duree
 * Paramètre arrivees: vecteur a partitionner
 * Paramètre debut: index de début du partitionnage
 * Paramètre fin: index de fin du partitionnage
*/
int partition_duree(vecteur* arrivees, int debut, int fin);

/*
 * Fonction qui permute deux noeuds en mémoire
 * Paramètre noeud a : le premier noeud
 * Paramètre noeud a : le second noeud
*/
void permuter(noeud* a, noeud* b);
