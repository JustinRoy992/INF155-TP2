/*
Module: T_DESTINATION
Description: Définit le type t_dest (destination de sortie de signal du circuit)
			 et fournit les fonctions pour le manipuler.

Auteur: Sébastien Hubert, Justin roy, Émile Larochelle
*/

#include "t_destination.h"

t_dest* dest_init(int id, char* nom)
{

}

void dest_destroy(t_dest* destination)
{

}

t_pin_entree* dest_get_pin(t_dest* destination)
{

}

int dest_relier(t_dest* destination, char* nom_composant, t_pin_sortie* pin_sortie)
{

}

int dest_est_reliee(t_dest* destination)
{

}

void dest_reset(t_dest* destination)
{

}

int dest_get_valeur(const t_dest* destination)
{

}

int dest_get_id(const t_dest* destination)
{

}

char* dest_get_nom(const t_dest* destination)
{

}

void dest_serialiser(const t_dest* destination, char* resultat)
{

}