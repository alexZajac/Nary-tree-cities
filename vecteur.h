#include <stdio.h>
#include <stdbool.h>
//on crée cette structure en tant que tableau dynamique pouvant contenir n'importe quel type de donnees (void**), on peut ainsi faire caster n'importer quel type de pointeur vers ce pointeur void, et stocker dans un vecteur le type de données souhaité 
typedef struct {
	void** donnees;
	int taille;
} vecteur;


/*
 * Fonction qui crée dynamiquement vecteur, dont le contenu est vide (i.e. sans élément).
 * Retour : un pointeur sur le vecteur créé
 */
vecteur* creation_vecteur();

/*
 * Fonction qui donne (d'un point de vu logique) le nombre d'éléments contenu dans un vecteur
 * Paramètre p_vec : le pointeur en accès en lecture seule sur le vecteur 
 */
int taille_vecteur(vecteur* p_vec);


/*
 * Fonction qui redimensionne le vecteur, dynamiquement
 * Paramètre taille : nouvelle taille du vecteur
 * Paramètre p_vec : le pointeur sur le vecteur dans lequel ajouter
 */
void redimensionner_vecteur(vecteur* p_vec, int taille);


/*
 * Fonction qui ajoute un élément à un vecteur à la fin
 * Paramètre elem : l'élément à ajouter
 * Paramètre p_vec : le pointeur sur le vecteur dans lequel ajouter
 */
void ajouter_vecteur(vecteur* p_vec, void* elem);

/*
 * Fonction qui ajoute un élément à un vecteur à une position donnée
 * Paramètre elem : l'élément à ajouter
 * Paramètre p_vec : le pointeur sur le vecteur dans lequel ajouter
 * Paramètre position: index dans le vecteur ou ajouter l'élément
 */
void ajouter_element_position(vecteur* p_vec, void* elem, int position);


/*
 * Fonction qui accède à un élément dans un vecteur selon sa position
 * Paramètre position : la position de l'élément à accéder (1ère position : index 0)
 * Paramètre p_vec : le pointeur en accès en lecture seule sur le vecteur dans lequel accéder à l'élément
 */
void* obtenir_element_position(vecteur* p_vec, int position);



/*
 * Fonction qui accède au dernier element d'un vectueur
 * Paramètre p_vec : le pointeur en accès en lecture seule sur le vecteur dans lequel accéder à l'élément
 */
void* obtenir_dernier_element(vecteur* p_vec);

/*
 * Fonction qui détruit le vecteur et libère toute la mémoire associée.
 * Paramètre p_vec : le pointeur sur le vecteur à détruire
 * Note : penser à mettre à NULL la variable passée en paramètre après utilisation de cette fonction dans le code appelant.
 */
void liberation_vecteur(vecteur** p_vec);

/*
 * Fonction qui détruit le tableau de vecteurs et libère toute la mémoire associée.
 * Paramètre p_vec : le pointeur sur le vecteur à détruire
 * Paramètre nb_lignes : le nombre d'elements du tableau (que l'on peut voir comme un nombre de lignes)
 * Note : penser à mettre à NULL la variable passée en paramètre après utilisation de cette fonction dans le code appelant.
 */
void liberation_tableau_vecteurs(vecteur*** p_vec, int nb_lignes);

/*
 * Fonction qui affiche les éléments d'un vecteur d'entiers
 * Paramètre p_vec : le pointeur sur le vecteur
 */
void afficher_vecteur_entier(vecteur* p_vec);

/*
 * Fonction qui affiche les éléments d'un vecteur de char*
 * Paramètre p_vec : le pointeur sur le vecteur
 */
void afficher_vecteur_char(vecteur* p_vec);

/*
 * Fonction qui affiche les éléments d'un tableau de vecteurs
 * Paramètre p_vec : le pointeur sur le tableau de vecteurs
 * Paramètre ligne : nombre de lignes du tableau de vecteurs
 */
void afficher_tableau_vecteurs(vecteur** p_vec, int lignes);

/*
 * Fonction qui récupère le maximum dans un vecteur d'entier
 * Paramètre p_vec : le pointeur sur le vecteur
 * Retour : maximum des element de p_vec
 */
int maximum_vecteur_entier(vecteur* p_vec);


/*
 * Fonction qui creer et renvoie un vecteur qui contient dans chaque case le nombre de caractères de ligne d'un fichier passe en paramatre
 * Paramètre fichier: le pointeur sur le fichier
 * Retour: un vecteur d'entiers
 */
vecteur* nombre_caracteres_par_ligne(FILE* fichier);


/*
 * Fonction qui ouvre et charge en mémoire les connexions entre les villes
 * Paramètre nom_ficher: le nom du ficher a ouvrir
 * Paramètre nb_caracteres : un pointeur entier vers le nombre de connexions possibles
 * Retour: un tableau de vecteurs, ou chaque vecteur comporte 4 elements (ville1, ville2, distance, duree)
 */
vecteur** ouvrir_charger_connexions(char nom_fichier[], int* nb_connexions);

/*
 * Fonction qui ouvre et charge en mémoire les villes 
 * Paramètre nom_ficher: le nom du ficher a ouvrir
 * Retour: un vecteur, ou chaque element est une ville
 */
vecteur* ouvrir_charger_villes(char nom_fichier[]);

/*
 * Fonction qui vérifie la contenance d'une certaine ville dans le vecteur passé en paramètre
 * Paramètre ville : la ville recherchee
 * Paramètre p_vec : le pointeur sur le vecteur a tester
 * Retour:  vrai si le vecteur contient la ville, false sinon
 */
bool verifier_contenance(vecteur* p_vec, char ville[]);


