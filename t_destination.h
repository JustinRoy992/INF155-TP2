/*
Module: T_DESTINATION
Description: Définit le type t_dest (destination de sortie de signal du circuit) 
			 et fournit les fonctions pour le manipuler.
Auteur: Anis Boubaker
Dernière modification: Eric Thé, 2025-11-1
*/


#ifndef destination_H_
#define destination_H_

#include "t_pin_entree.h"


typedef struct t_dest{
	int id;				//Identifiant numérique de la destination de circuit.
						//Doit être unique parmi les destinations du circuit
	char *nom;			//Nom de la destination (ex. "D1")
	t_pin_entree *pin;  //Pin d'entrée du signal (connecteur "in" d'un signal)
} t_dest;


/*
Fonction: DEST_INIT
Description: Crée une nouvelle destination de circuit. Le constrcuteur reçoit un identifiant 
             numérique et un nom qui (on assume) sont uniques dans le circuit.
			 Ex. 1 et "D1"
		
Paramètres:
- id: Entier représentant l'identifiant numérique de la destination (unique dans un circuit)
- nom: Chaine de caractères représentant le nom de l'entrée du signal (unique dans un circuit)
Retour: Pointeur vers la destination de circuit dynamique créée
Paramètres modifié: Aucun.
*/
t_dest * dest_init(int id, char *nom);

/*
Fonction: DEST_DESTROY
Description: Libère la mémoire occupée par la destination et tous ses composants (i.e. le pin).
NDE: Ne pas oublier de premièrement détruire le t_pin_entree de la destination.

Paramètres:
- destination: Pointeur vers la destination à détruire.
Retour: Aucun.
*/
void dest_destroy(t_dest *destination);

/*
Fonction: DEST_GET_PIN
Description: Accesseur - Retourne un pointeur vers le pin_entree de la destination de circuit.

Paramètres:
- destination: Pointeur vers la destination de circuit dont on veut accéder au t_pin_entree.
Retour: Pointeur vers le t_pin_entree de la destination de circuit.
*/
t_pin_entree * dest_get_pin(t_dest *destination);


/*
Fonction: DEST_RELIER
Description: Relie une destination de circuit à un autre composant du circuit (une source ou porte)
			 On note ici qu'on relie le t_pin_entree de la destination vers un t_pin_sortie
			 d'un autre composant. Les seuls autres composants disposant d'un t_pin_sortie sont
			 les sources et les portes du circuit. 
			 Si la destination a déjà été reliée, le nouveau lien va écraser l'ancien. 
NDE: Pour faire la liaison, la fonction pin_entree_relier() vous sera très utile!

Paramètres:
- destination: Pointeur vers la destination de circuit à relier.
- nom_composant: Le nom du composant de circuit à lequel ont relie la destination.
- pin_sortie: Le t_pin_sortie vers lequel nous allons relier la destination de circuit. 
Retour: Booléen : Vrai si la liaison a bien été effectuée. Faux sinon. 
*/
int dest_relier(t_dest *destination, char* nom_composant, t_pin_sortie *pin_sortie);

/*
Fonction: DEST_EST_RELIEE
Description: Vérifie si une destination de circuit est reliée. Pour qu'elle soit reliée,
			 son t_pin_entree doit être relié.
NDE: Il existe une fonction dans t_pin_entree qui vous permet
	 de vérifier si un pin est relié. Utilisez-la!

Paramètres:
- destination: Pointeur vers la destination que l'on souhaite vérifier.
Retour: Booléen : Vrai si la destination de sortie de signal est entièrement reliée, 
                  Faux sinon.
*/
int dest_est_reliee(t_dest *destination);

/*
Fonction: DEST_RESET
Description: Réinitialise une destination. Pour réinitialiser une destination, il suffit
de ré-initialiser son t_pin_entree.
NDE: Il y'a une fonction faite pour ça dans le module t_pin_entree.

Paramètres:
- destination: Pointeur vers la destination de circuit à réinitialiser.
Retour: Aucun
*/
void dest_reset(t_dest *destination);

/*
Fonction: DEST_GET_VALEUR
Description: Retourne la valeur du signal de la destination. Ceci correspond à la valeur
			 du signal de son t_pin_entree.
NDE: Il y'a une fonction faite pour ça dans le module t_pin_entree.

Paramètres:
- destination: Pointeur vers la destination de circuit dont on veut connaitre la valeur.
Retour: Entier: valeur du signal à la destination
*/
int dest_get_valeur(const t_dest *destination);

/*
Fonction: DEST_GET_ID
Description: Retourne le id (numéro) de la destination.

Paramètres:
- destination: Pointeur vers la destination de circuit dont on veut connaitre son id
Retour: Entier: valeur de l'id de la destination (son numéro).
*/
int dest_get_id(const t_dest *destination);

/*
Fonction: DEST_GET_NOM
Description: Retourne le nom de la destination.

Paramètres:
- destination: Pointeur vers la destination de circuit dont on veut connaitre son nom
Retour: String: valeur du nom de la destination.
*/
char* dest_get_nom(const t_dest *destination);

/*
Fonction: DEST_SERIALISER
Description: Transforme en texte les informations d'une destination.

Paramètres:
- destination: Pointeur vers la destination de circuit à sérialiser.
- resultat: Chaine de caractères dans laquelle on copie le texte généré.
*/
void dest_serialiser(const t_dest *destination, char *resultat);     //*** Partie 2


#endif