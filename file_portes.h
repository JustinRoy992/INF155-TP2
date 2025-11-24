/*
Module: file_portes.h
Description: Librairie qui implémente une file de type 
Auteur: Éric Thé
Modification: Sébastien Hubert, Émile Larochelle, Justin Roy
*/

#ifndef FILE_PILES_H_
#define FILE_PILES_H_

#include "t_porte.h"

#define MAXFILE 100

typedef struct t_porte* t_element;  //changer cette déclaration pour avoir une file d’un autre type

typedef struct 
{
	t_element items[MAXFILE];
	int debut, fin, total;
} t_file;

//fonction pour initialiser une file, la file sera vide après un appel
//de cette fonction. Peut aussi être utilisé pour vider une file.
void initfile(t_file*);

//fonction pour vérifier si une file est pleine
int pleine(const t_file*);

//fonction pour vérifier si une file est vide
int vide(const t_file*);

//fonction pour ajouter un élément de plus à la fin d'une file
void ajouterfin(t_file*, t_element);

//fonction pour enlever un élément du début d'une file
void enleverdebut(t_file*, t_element*);

#endif