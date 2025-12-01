/*
Module: T_SOURCE
Description: Définit le type t_source (source de signal du circuit) et fournit les
			 fonctions pour le manipuler.

Auteur: Sébastien Hubert, Justin roy, Émile Larochelle
*/

#include "t_source.h"

//-------------------------------------------------------------------------------------//
/*Fonction qui initialise une source.*/
t_source* source_init(int id, char* nom)
{
	t_source* nouvelle_source = NULL; /*Nouvelle source dynamique*/

	/*Création de la source dynamique*/
	nouvelle_source = (t_source*)malloc(sizeof(t_source)); 

	/*Initialisation des champs de la source.*/
	nouvelle_source->id = id;
	nouvelle_source->pin = pin_sortie_init();
	
	/*Création de la chaine dynamique pour le nom de la source*//
	nouvelle_source->nom = (char*)calloc(NOM_TAILLE_MAX, sizeof(char)); 
	strcpy(nouvelle_source->nom, nom); /*Copie du nom dans la chaine dynamique*/
	return nouvelle_source; /*Retourne la nouvelle source créée*/
}

//-------------------------------------------------------------------------------------//



//-------------------------------------------------------------------------------------//
/*Fonction qui détruit une source et libère la mémoire associée.*/
void source_destroy(t_source* source)
{
	/*Libération de toute mémoire occupée par la source.*/
	free(source->nom); 
	pin_sortie_destroy(source->pin);
	free(source);
}

//-------------------------------------------------------------------------------------//




//-------------------------------------------------------------------------------------//
/*Fonction accesseur du champ pin de la source.*/
t_pin_sortie* source_get_pin(t_source* source)
{
	return source->pin;	/*Retourne le pin de sortie de la source.*/
}

//-------------------------------------------------------------------------------------//



//-------------------------------------------------------------------------------------//
/*Fonction qui vérifie si une source de circuit est reliée.*/
int source_est_reliee(t_source* source)
{
	/*Pour qu'une source soit reliée, son pin de sortie doit être relié.*/
	if(pin_sortie_est_reliee(source->pin)==1){
		return TRUE; /*Retourne vrai si la source est reliée.*/
	}
	return FALSE; /*Retourne faux sinon.*/
}

//-------------------------------------------------------------------------------------//



//-------------------------------------------------------------------------------------//
/*Fonction qui réinitialise une source.*/
void source_reset(t_source* source)
{
	/*Ré-initialise le pin de sortie de la source en
	appelant la fonction pin_sortie_reset.*/
	pin_sortie_reset(source->pin);
}

//-------------------------------------------------------------------------------------//



//-------------------------------------------------------------------------------------//
/*Fonction qui propage le signal à partir de la source de circuit.*/
int source_propager_signal(t_source* source)
{
	/*Appelle la fonction pin_sortie_propager_signal et retourne son résultat*/
	if(pin_sortie_propager_signal(source->pin)==1)
		return TRUE; /*Retourne vrai si le signal a été propagé.*/
	return FALSE; /*Retourne faux sinon.*/
}

//-------------------------------------------------------------------------------------//



//-------------------------------------------------------------------------------------//
/*Fonction accesseur du champ valeur de la source.*/
int source_get_valeur(const t_source* source)
{
	return source->pin->valeur; /*Retourne la valeur actuelle du pin de sortie*/
}

//-------------------------------------------------------------------------------------//



//-------------------------------------------------------------------------------------//
/*Fonction accesseur du champ id de la source.*/
int source_get_id(const t_source* source)
{
	return source->id; /*Retourne l'id de la source.*/
}

//-------------------------------------------------------------------------------------//



//-------------------------------------------------------------------------------------//
/*Fonction accesseur du champ nom de la source.*/
char* source_get_nom(const t_source* source)
{
	return source->nom; /*Retourne le nom de la source.*/
}

//-------------------------------------------------------------------------------------//



//-------------------------------------------------------------------------------------//
/*Fonction qui sérialise une source dans une chaîne de caractères.*/
void source_serialiser(const t_source* source, char* resultat)
{
	/*Sérialise les informations de la source dans la chaîne resultat.*/
	sprintf("%d %s", source->id, source->nom);
}

//-------------------------------------------------------------------------------------//