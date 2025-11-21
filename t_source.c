/*
Module: T_SOURCE
Description: Définit le type t_source (source de signal du circuit) et fournit les
			 fonctions pour le manipuler.

Auteur: Sébastien Hubert, Justin roy, Émile Larochelle
*/

#include "t_source.h"
// justin roy
t_source* source_init(int id, char* nom)
{

}
// émile larochelle
void source_destroy(t_source* source)
{
	/*Libération de toute mémoire occupée par la source.*/
	free(source->pin);
	free(source->nom);
	free(source->id);
	free(source);
}
//Sébastien Hubert
t_pin_sortie* source_get_pin(t_source* source)
{

}
//justin roy
int source_est_reliee(t_source* source)
{

}
//émile larochelle
void source_reset(t_source* source)
{
	/*Ré-initialise le pin de sortie de la source en
	appelant la fonction pin_sortie_reset.*/
	pin_sortie_reset(source->pin);

}
//sébastien hubert
int source_propager_signal(t_source* source)
{

}
//justin roy
int source_get_valeur(const t_source* source)
{

}
//émile larochelle
int source_get_id(const t_source* source)
{
	int id_source;

	id_source = source->id;

	return id_source;
}
//sébastien hubert
char* source_get_nom(const t_source* source)
{

}
//justin roy
void source_serialiser(const t_source* source, char* resultat)
{

}