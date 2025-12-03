/*
Module: CIRCUIT_IO
Description: Module de charge et de création de fichier pour ouvrir une circuit préfait
ou pour enregistrer le circuit.

Auteur: Sébastien Hubert, Justin roy, Émile Larochelle
*/

#ifndef CIRCUIT_IO_
#define CIRCUIT_IO_
#define _CRT_SECURE_NO_WARNINGS
#include <assert.h>
#include "t_circuit.h"

void demander_fichier(char* nom_fichier);

/*
Fonction: CIRCUIT_IO_SAUVEGARDER	
Description: Cette fonction écrit dans un fichier le nombre de sources, destinations 
et portes, et les id et nom des sources, destinations et portes ainsi que des liens

Paramètres:
- nom_fichier: ne nom du fichier
- circuit: Le circuit a sauvegarder
Retour: Aucun
Paramètres modifié: Aucun.
*/
void circuit_IO_sauvegarder(const char* nom_fichier, const  t_circuit* circuit);

/*
Fonction: CIRCUIT_IO_CHARGER
Description: Cette fonction

Paramètres:
- chemin_acces: ne nom du fichier a ouvrir
- circuit: Le circuit dans le quel on charge
Retour: Aucun
Paramètres modifié: Aucun.
*/
void circuit_IO_charger(const char* chemin_acces, t_circuit* circuit);
#endif