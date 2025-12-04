/*
Module: T_PIN_ENTREE
Description: Définit le type t_pin_entree. Un t_pin_entree est un point de connexion appartenant
			 à un élément du circuit qui reçoit un signal (mais n'en émet pas). 
			 Les éléments d'un circuit ayant un pin d'entrée de signal sont les portes (les 
			 entrées des portes) ainsi que les sorties du circuit.

			 Si un pin d'entrée reçoit un signal, ce signal est stocké dans le champs valeur.  
			 Un t_pin_entree qui est inactif (pas alimenté) a la valeur -1. 

			 Un pin d'entree relie le composant auquel il appartient à un autre composant. 
			 Il doit être relié à un "pin de sortie" du composant auquel on souhaite se connecter.

Auteur: Anis Boubaker
Dernière modification: Eric Thé, 2025-01-11
*/

#include "t_pin_entree.h"

//Crée un nouveau pin d'entrée qui contient aucune valeur et pas de liaison.
t_pin_entree *pin_entree_init()
{
	t_pin_entree *nouv_pin = NULL;		//le nouveau pin d'entrée dynamique

	//Création du pin dynamique
	nouv_pin = (t_pin_entree*) malloc(sizeof(t_pin_entree));

	//Init: ce pin contient aucune valeur et pas de liaison.
	nouv_pin->valeur = INACTIF;
	nouv_pin->liaison = NULL;

	//Créer la chaine dynamique pour le nom de la connexion (toute à zéro)
	nouv_pin->nom_liaison = (char*) calloc(NOM_TAILLE_MAX, sizeof(char));

	return nouv_pin;
}

/*****************************************************************************/
//Accesseur du champ valeur.
int pin_entree_get_valeur(const t_pin_entree *pin)
{
	return pin->valeur;
}

/*****************************************************************************/
//Accesseur du champ liaison.
char* pin_entree_get_lien(const t_pin_entree *pin)
{
	return pin->nom_liaison;
}

/*****************************************************************************/
//Mutateur du champ valeur.
void pin_entree_set_valeur(t_pin_entree *pin, int valeur)  //soit -1, 0, 1
{
	if (valeur < INACTIF || valeur > 1) {
		//Valeur erronée
		return;
	}
	pin->valeur = valeur;
}

/*****************************************************************************/
//Relie le pin d'entrée à un pin de sortie.
void pin_entree_relier(t_pin_entree * pin_entree, char * nom_sortie, t_pin_sortie * pin_sortie)
{
	//On vérifie d'abord si on avait un lien existant
	if (pin_entree->liaison != NULL) {
		//On supprime la liaison du pin de sortie à lequel on est présentement liés
		pin_sortie_supprimer_lien(pin_entree->liaison, pin_entree);
	}
	pin_entree->liaison = pin_sortie;

	strcpy(pin_entree->nom_liaison, nom_sortie);      //on copie le nom de la connexion

	pin_sortie_ajouter_lien(pin_sortie, pin_entree);
	
	pin_entree->liaison->nb_liaisons;
}

/*****************************************************************************/
//Permet de vérifier si un pin d'entrée est reliée à un pin de sortie.
int pin_entree_est_reliee(t_pin_entree *pin)
{
	if (pin->liaison == NULL)
		return 0;
	else return 1;
	//return pin->liaison != NULL;
} 

/*****************************************************************************/
//Ré-initialise la valeur du pin d'entree à INACTIF.
void pin_entree_reset(t_pin_entree *pin)
{
	pin->valeur = INACTIF;
}

/*****************************************************************************/
//Libère la mémoire occupée par le pin d'entree.
void pin_entree_destroy(t_pin_entree * pin)
{
	free(pin->nom_liaison);
	free(pin);
}

/*****************************************************************************/
/*****************************************************************************/