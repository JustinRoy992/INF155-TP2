/*
Module: T_PORTE
Description: Définit le type porte et fournit les fonctions pour manipuler une porte.
Note: Ce module a été conçu de sorte à ce qu'il soit facielement extensible pour traiter
	  des portes peronnalisées (i.e. des circuits qu'on réutilise comme des portes dans
	  d'autres circuits. Pour limiter le travail des étudiants, cette fonctionnalité a été
	  abandonnée mais il n'en demeure pas moins un point d'évolution potentiel du projet.
	  Les étudiants courageux sont encouragés à considérer, voir implémenter cette évolution.

Auteur: Sébastien Hubert, Justin roy, Émile Larochelle

*/

#include "t_porte.h"

t_porte* porte_init(int id, e_types_portes type, char* nom)
{

}

void porte_destroy(t_porte* porte)
{

}

void porte_calculer_sortie(t_porte* porte)
{

}

int porte_relier(t_porte* porte, int num_entree, char* nom_sortie, t_pin_sortie* source)
{

}

int porte_est_reliee(t_porte* porte)
{

}

void porte_reset(t_porte* porte)
{

}

int porte_propager_signal(t_porte* porte)
{

}

int porte_get_id(const t_porte* porte)
{

}

char* porte_get_nom(const t_porte* porte)
{

}

int porte_get_nb_entrees(const t_porte* porte)
{

}

e_types_portes porte_get_type(const t_porte* porte)
{

}

t_pin_entree* porte_get_pin_entree(const t_porte* porte, int num)
{

}

t_pin_sortie* porte_get_pin_sortie(const t_porte* porte)
{

}

void porte_serialiser(const t_porte* porte, char* resultat)
{

}

//t_porte*porte_init(id,type,nom)
//tporte*porte=...mallo (1 seul)
//copier le 'Id' recu
//allouer l'espace - mémoire pour le 'nom' et y copier le 'Nom' reçu
//selon le 'type' reçu;
 //créer les 2 (ou une) pin-entrée(s)
//créer la pin-sortie (pin_sortie_init())
//nb_entrée = 1 ou 2
//retun porte;
