/*
Module: T_DESTINATION
Description: Définit le type t_dest (destination de sortie de signal du circuit)
			 et fournit les fonctions pour le manipuler.

Auteur: Sébastien Hubert, Justin roy, Émile Larochelle
*/

#include "t_destination.h"
// justin roy
t_dest* dest_init(int id, char* nom)
{

}
// émile larochelle
void dest_destroy(t_dest* destination)
{
	free(destination->id);
	free(destination->nom);
	free(destination->pin);
	free(destination);
}
//Sébastien Hubert
t_pin_entree* dest_get_pin(t_dest* destination)
{

}
//justin roy
int dest_relier(t_dest* destination, char* nom_composant, t_pin_sortie* pin_sortie)
{

}
//émile larochelle
int dest_est_reliee(t_dest* destination)
{
	if(pin_entree_est_reliee(destination->pin)==1)
	{
		return 1;
	}
	
	return 0;
}
//sébastien hubert
void dest_reset(t_dest* destination)
{

}
//justin roy
int dest_get_valeur(const t_dest* destination)
{

}
//émile larochelle
int dest_get_id(const t_dest* destination)
{
	return destination->id;
}
//sébastien hubert
char* dest_get_nom(const t_dest* destination)
{

}
//émile larochelle
void dest_serialiser(const t_dest* destination, char* resultat)
{
		sprintf(resultat, "Destination ID: %d, Nom: %s, Pin Valeur: %d",
			destination->id, destination->nom, destination->pin->valeur);
}