/*
Module: T_SOURCE
Description: Définit le type t_source (source de signal du circuit) et fournit les
			 fonctions pour le manipuler.

Auteur: Émile Larochelle
*/

#include "t_source.h"

/**********************************************************************************/

t_source* source_init(int id, char* nom)
{
	t_source* nouvelle_source = NULL;

	nouvelle_source = (t_source*) malloc(sizeof(t_source));

	nouvelle_source->id = id;
	nouvelle_source->pin = pin_sortie_init();
	
	nouvelle_source->nom = (char*)calloc(NOM_TAILLE_MAX, sizeof(char));
	strcpy(nouvelle_source->nom, nom);
	return nouvelle_source;

}

/**********************************************************************************/

void source_destroy(t_source* source)
{
	/*Libération de toute mémoire occupée par la source.*/
	free(source->nom);
	pin_sortie_destroy(source->pin);
	free(source);
}

/**********************************************************************************/

t_pin_sortie* source_get_pin(t_source* source)
{
	//Retourne le pin de sortie de la source.
	return source->pin;

}

/**********************************************************************************/

int source_est_reliee(t_source* source)
{
	//Vérifie si le pin de sortie de la source est reliée.
	if(pin_sortie_est_reliee(source->pin)==1){
		return 1;
	}
	return 0;
}

/**********************************************************************************/

void source_reset(t_source* source)
{
	/*Ré-initialise le pin de sortie de la source en
	appelant la fonction pin_sortie_reset.*/
	pin_sortie_reset(source->pin);

}

/**********************************************************************************/

int source_propager_signal(t_source* source)
{
	//Propage le signal à partir du pin de sortie de la source.
	if(pin_sortie_propager_signal(source->pin)==1)
		return 1;
	return 0;
}

/**********************************************************************************/

int source_get_valeur(const t_source* source)
{
	//Retourne la valeur du pin de sortie de la source.
	return source->pin->valeur;
}

/**********************************************************************************/

int source_get_id(const t_source* source)
{
	//Retourne l'identifiant de la source.
	return source->id;
}

/**********************************************************************************/

char* source_get_nom(const t_source* source)
{
	//Retourne le nom de la source.
	return source->nom;
}

/**********************************************************************************/

void source_serialiser(const t_source* source, char* resultat)
{
	//Sérialise les informations de la source dans la chaîne resultat.
	sprintf(resultat, "Source ID: %d, Nom %s, Pin Valeur: %d",
		source->id, source->nom, source->pin->valeur);
}