/*
Module: T_DESTINATION
Description: Définit le type t_dest (destination de sortie de signal du circuit)
			 et fournit les fonctions pour le manipuler.

Auteur: Sébastien Hubert, Justin roy, Émile Larochelle
*/

#include "t_destination.h"

/**********************************************************************************/

t_dest* dest_init(int id, char* nom)
{
	//Création de la nouvelle destination dynamique
	t_dest *nouvelle_destination = NULL;

	nouvelle_destination = (t_dest*)malloc(sizeof(t_dest));

	//Initialisation du champ id
	nouvelle_destination->id= id;

	//Création du pin d'entrée de la destination
	nouvelle_destination->pin = pin_entree_init();
	
	//Création de la chaine dynamique pour le nom de la destination
	nouvelle_destination->nom = (char*)calloc(NOM_TAILLE_MAX, sizeof(char));
	
	//on copie le nom dans la chaine dynamique
	strcpy(nouvelle_destination->nom, nom);

	return nouvelle_destination;
}

/**********************************************************************************/

void dest_destroy(t_dest* destination)
{
	//Libération de toute mémoire occupée par la destination.
	pin_entree_destroy(destination->pin);
	free(destination->nom);
	free(destination);
}

/**********************************************************************************/

t_pin_entree* dest_get_pin(t_dest* destination)
{
	//Retourne le pin d'entrée de la destination.
	return destination->pin;
}

/**********************************************************************************/

int dest_relier(t_dest* destination, char* nom_composant, t_pin_sortie* pin_sortie)
{
	//Relie le pin d'entrée de la destination au pin de sortie fourni en paramètre.
	if (pin_sortie != NULL)
	{
		pin_entree_relier(destination->pin, nom_composant, pin_sortie);
		return 1;
	}
	return 0;

}

/**********************************************************************************/

int dest_est_reliee(t_dest* destination)
{
	//Vérifie si le pin d'entrée de la destination est reliée.
	if(pin_entree_est_reliee(destination->pin)==1)
		return 1;
	
	return 0;
}

/**********************************************************************************/

void dest_reset(t_dest* destination)
{
	//Ré-initialise le pin d'entrée de la destination en le mettant à INACTIF.
	pin_entree_reset(destination->pin);

}

/**********************************************************************************/

int dest_get_valeur(const t_dest* destination)
{
	//Retourne la valeur du signal à la destination en utilisant l'accesseur du pin d'entrée.
	return pin_entree_get_valeur(destination->pin);

}

/**********************************************************************************/

int dest_get_id(const t_dest* destination)
{
	//Retourne l'identifiant de la destination.
	return destination->id;
}

/**********************************************************************************/

char* dest_get_nom(const t_dest* destination)
{
	//Retourne le nom de la destination.
	return destination->nom;
}

/**********************************************************************************/

void dest_serialiser(const t_dest* destination, char* resultat)
{
	//Sérialise les informations de la destination dans la chaîne resultat.
		sprintf(resultat, "Destination ID: %d, Nom: %s, Pin Valeur: %d",
			destination->id, destination->nom, destination->pin->valeur);
}