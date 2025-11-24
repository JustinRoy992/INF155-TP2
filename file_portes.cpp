/*
Module: file_portes.h
Description: Librairie qui implémente une file de type
Auteur: Éric Thé
Modifications: Sébastien Hubert, Émile Larochelle, Justin Roy
*/
#include "file_portes.h"

void initfile(t_file* f) //fonction pour initialiser une file, la file sera vide
{
	f->debut = 0;
	f->fin = MAXFILE - 1;
	f->total = 0;
}

int pleine(const t_file* f) //fonction pour vérifier si une file est pleine
{
	return (f->total == MAXFILE);
}

int vide(const t_file* f) //fonction pour vérifier si une file est vide
{
	return (f->total == 0);
}

//fonction pour ajouter un élément de plus à la fin d'une file
void ajouterfin(t_file* f, t_element el)
{
	if (pleine(f))
		printf("ERREUR!!! Débordement de file.\n");
	else {
		//Utilisation d’un modulo pour faire un compteur “circulaire”
		f->fin = (f->fin + 1) % MAXFILE;
		f->items[f->fin] = el;
		f->total++;
	}
}

//fonction pour enlever un élément du début d'une file
void enleverdebut(t_file* f, t_element* el)
{
	if (vide(f))
		printf("ERREUR!!! File vide.\n");
	else {
		*el = f->items[f->debut];
		f->debut = (f->debut + 1) % MAXFILE; //avec compteur “circulaire”
		f->total--;
	}
}
