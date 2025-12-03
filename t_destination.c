/*
Module: T_DESTINATION
Description: Définit le type t_dest (destination de sortie de signal du circuit)
			 et fournit les fonctions pour le manipuler.

Auteur: Sébastien Hubert, Justin roy, Émile Larochelle
*/

#include "t_destination.h"

//-------------------------------------------------------------------------------------//
/*Fonction qui initialise une destination.*/
t_dest* dest_init(int id, char* nom)
{
	
	t_dest* nouvelle_destination = NULL; /*Nouvelle destination dynamique.*/
	/*Création de la destination dynamique.*/
	nouvelle_destination = (t_dest*)malloc(sizeof(t_dest)); 

	nouvelle_destination->id = id; /*Initialisation de l'identifiant de la destination.*/
	/*Initialisation du pin d'entrée de la destination.*/
	nouvelle_destination->pin = pin_entree_init();
	
	/*Création de la chaîne dynamique pour le nom de la destination*/
	nouvelle_destination->nom = (char*)calloc(NOM_TAILLE_MAX, sizeof(char));
	strcpy(nouvelle_destination->nom, nom); /*Copie du nom dans la chaîne dynamique.*/

	return nouvelle_destination; /*Retourne la nouvelle destination créée.*/
}

//-------------------------------------------------------------------------------------//



//-------------------------------------------------------------------------------------//
/*Fonction qui détruit une destination et libère la mémoire associée.*/
void dest_destroy(t_dest* destination)
{
	/*Libération de toute mémoire occupée par la destination.*/
	pin_entree_destroy(destination->pin);
	free(destination->nom);
	free(destination);
}

//-------------------------------------------------------------------------------------//



//-------------------------------------------------------------------------------------//
/*Fonction accesseur du champ pin de la destination.*/
t_pin_entree* dest_get_pin(t_dest* destination)
{
	return destination->pin; 	/*Retourne le pin de la destination.*/
}

//-------------------------------------------------------------------------------------//



//-------------------------------------------------------------------------------------//
/*Fonction qui relie le pin d'entrée de la destination au pin de sortie fourni.*/
int dest_relier(t_dest* destination, char* nom_composant, t_pin_sortie* pin_sortie)
{
	/*Relie le pin d'entrée de la destination au pin de sortie fourni.*/
	pin_entree_relier(destination->pin, nom_composant, pin_sortie);

	/*Si le pin de sortie existe.*/
	if (pin_sortie_est_reliee(pin_sortie) == 1)
	{
		return TRUE;  /*Retourne vrai si la liaison est effectuée avec succès.*/
	}
	return FALSE;  /*Retourne faux si le pin de sortie est nul.*/
}

//-------------------------------------------------------------------------------------//



//-------------------------------------------------------------------------------------//
/*Fonction qui vérifie si la destination est reliée.*/
int dest_est_reliee(t_dest* destination)
{
	/*Pour qu'une destination soit reliée, son pin d'entrée doit être relié.*/
	if(pin_entree_est_reliee(destination->pin)==1)
		return TRUE; /*Retourne vrai si la destination est reliée.*/

	return FALSE; /*Retourne faux si la destination n'est pas reliée.*/
}

//-------------------------------------------------------------------------------------//



//-------------------------------------------------------------------------------------//
/*Fonction qui ré-initialise la destination.*/
void dest_reset(t_dest* destination)
{
	/*Ré-initialise le pin d'entrée de la destination.*/
	pin_entree_reset(destination->pin);
}

//-------------------------------------------------------------------------------------//



//-------------------------------------------------------------------------------------//
/*Fonction accesseur du champ valeur du pin d'entrée de la destination.*/
int dest_get_valeur(const t_dest* destination)
{
	//Retourne la valeur du signal de la destination.
	return pin_entree_get_valeur(destination->pin);
}

//-------------------------------------------------------------------------------------//



//-------------------------------------------------------------------------------------//
/*Fonction accesseur du champ id de la destination.*/
int dest_get_id(const t_dest* destination)
{
	return destination->id; /*Retourne l'id de la destination.*/
}

//-------------------------------------------------------------------------------------//



//-------------------------------------------------------------------------------------//
/*Fonction accesseur du champ nom de la destination.*/
char* dest_get_nom(const t_dest* destination)
{
	return destination->nom; /*Retourne le nom de la destination.*/
}

//-------------------------------------------------------------------------------------//



//-------------------------------------------------------------------------------------//
/*Fonction qui sérialise une destination dans une chaîne de caractères.*/
void dest_serialiser(const t_dest* destination, char* resultat)
{
	/*Sérialise les informations de la destination dans une chaîne caractères.*/
	sprintf(resultat, "%d %s", destination->id, destination->nom);
}

//-------------------------------------------------------------------------------------//