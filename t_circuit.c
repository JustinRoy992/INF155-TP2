/*
Module: T_CIRCUIT
Description: Définit le type circuit et fournit les fonctions pour manipuler un circuit.

Auteur: Sébastien Hubert, Justin roy, Émile Larochelle
*/

#include "t_circuit.h"

t_circuit* circuit_init(void)
{

}

void circuit_destroy(t_circuit* circuit)
{

}

t_porte* circuit_ajouter_porte(t_circuit* circuit, e_types_portes le_type, int id, char* nom)
{

}

t_source* circuit_ajouter_source(t_circuit* circuit, int id, char* nom)
{

}

t_dest* circuit_ajouter_dest(t_circuit* circuit, int id, char* nom)
{

}

int circuit_est_valide(t_circuit* circuit)
{

}

int circuit_appliquer_signal(t_circuit* circuit, int signal[], int nb_bits)
{

}

void circuit_reset(t_circuit* circuit)
{

}

int circuit_propager_signal(t_circuit* circuit)
{

}

int circuit_get_nb_portes(const t_circuit* circuit)
{

}

t_porte* circuit_get_porte(const t_circuit* circuit, int pos)
{

}

int circuit_get_nb_dest(const t_circuit* circuit)
{

}

t_dest* circuit_get_dest(const t_circuit* circuit, int pos)
{

}

int circuit_get_nb_sources(const t_circuit* circuit)
{

}

t_source* circuit_get_source(const t_circuit* circuit, int pos)
{

}