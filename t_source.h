/*
Module: T_SOURCE
Description: Définit le type t_source (source de signal du circuit) et fournit les 
			 fonctions pour le manipuler.
Auteur: Anis Boubaker
Dernière modification: Eric Thé, 2025-11-1
*/

#ifndef source_H_
#define source_H_

#include "t_pin_sortie.h"


typedef struct t_source{
	int id;				//Identifiant numérique de la source.
						//Doit être unique parmi les sources du circuit
	char *nom;			//Nom de la source (ex. "S1")
	t_pin_sortie *pin;  //Pin de sortie (connecteur "out" d'un signal)
} t_source;


/*
Fonction: SOURCE_INIT
Description: Crée une nouvelle source de circuit. Le constrcuteur reçoit un identifiant 
             numérique et un nom qui (on assume) sont uniques dans le circuit.
			 Ex. 1 et "S1"

Paramètres:
- id: Entier représentant l'identifiant numérique de la source (unique dans un circuit)
- nom: Chaine de caractères représentant le nom de la source (unique dans un circuit)
Retour: Pointeur vers la source de circuit créée
Paramètres modifié: Aucun.
*/
t_source * source_init(int id, char *nom);   

/*
Fonction: SOURCE_DESTROY
Description: Libère la mémoire occupée par la source et tous ses composants (i.e. le pin).
NDE: Ne pas oublier de premièrement détruire le t_pin_sortie de cette source.

Paramètres:
- source: Pointeur vers la source à détruire.
Retour: Aucun.
*/
void source_destroy(t_source *source);

/*
Fonction: SOURCE_GET_PIN
Description: Accesseur - Retourne un pointeur vers le t_pin_sortie de la source.

Paramètres:
- source: Pointeur vers la source de circuit dont on veut accéder au pin de sortie.
Retour: Pointeur vers le t_pin_sortie de la source.
*/
t_pin_sortie * source_get_pin(t_source *source);

/*
Fonction: SOURCE_EST_RELIEE
Description: Vérifie si une source de circuit est reliée. Pour qu'elle soit reliée,
			 son pin de sortie doit être relié.
NDE: Il existe une fonction dans t_pin_sortie qui vous permet
	 de vérifier si un pin est relié. Utilisez-la!

Paramètres:
- source: Pointeur vers la source que l'on souhaite vérifier.
Retour: Booléen Vrai si la source est entièrement reliée, faux sinon.
*/
int source_est_reliee(t_source *source);

/*
Fonction: SOURCE_RESET
Description: Réinitialise une source. Pour réinitialiser une source, il suffit
			 de ré-initialiser son t_pin_sortie.
NDE: Il y'a une fonction faite pour ça dans le module t_pin_sortie.

Paramètres:
- source: Pointeur vers la source de circuit à réinitialiser.
Retour: Aucun
*/
void source_reset(t_source *source);

/*
Fonction: SOURCE_PROPAGER_SIGNAL
Description: Propage le signal à partir de la source de circuit reçue en paramètre.
			 Pour que le signal puisse se propager, il faut que le t_pin_sortie de
			 la source ait une valeur valide (i.e. != -1).
NDE: Utilisez la fonction "pin_sortie_propager_signal()" ici.

Paramètres:
- source: Pointeur vers la source de circuit dont on veut propager le signal.
Retour: Booléen: Vrai si le signal a pu se propager (i.e. le t_pin_sortie a une valeur), 
                 Faux sinon.
*/
int source_propager_signal(t_source *source);

/*
Fonction: SOURCE_GET_VALEUR
Description: Retourne la valeur du signal de la source. Ceci correspond à la valeur
			 du signal de son pin_sortie.

Paramètres:
- source: Pointeur vers la source de circuit dont on veut connaitre la valeur.
Retour: Entier: valeur du signal à la source du circuit. 
*/
int source_get_valeur(const t_source *source);

/*
Fonction: SOURCE_GET_ID
Description: Retourne le id (numéro) de la source.

Paramètres:
- source: Pointeur vers la source de circuit dont on veut connaitre son id
Retour: Entier: valeur de l'id de la source (son numéro).
*/
int source_get_id(const t_source *source);

/*
Fonction: SOURCE_GET_NOM
Description: Retourne le nom de la source.

Paramètres:
- source: Pointeur vers la source de circuit dont on veut connaitre son nom
Retour: String: valeur du nom de la source.
*/
char * source_get_nom(const t_source *source);

/*
Fonction: SOURCE_SERIALISER
Description: Transforme en texte les informations d'une source.

Paramètres:
- source: Pointeur vers la source de circuit à sérialiser.
- resultat: Chaine de caractères dans laquelle on copie le texte généré.
*/
void source_serialiser(const t_source *source, char * resultat);    //*** Partie 2 

#endif