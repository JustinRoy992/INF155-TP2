/*
Module: T_CIRCUIT
Description: Définit le type circuit et fournit les fonctions pour manipuler un circuit.

Auteur: Sébastien Hubert, Justin roy, Émile Larochelle
*/

#include "t_circuit.h"

//justin
t_circuit* circuit_init(void) 
{

}

//emile
void circuit_destroy(t_circuit* circuit)
{

}

//sebas
t_porte* circuit_ajouter_porte(t_circuit* circuit, e_types_portes le_type, int id, char* nom)
{

}

//justin
t_source* circuit_ajouter_source(t_circuit* circuit, int id, char* nom)
{

}

//emile
t_dest* circuit_ajouter_dest(t_circuit* circuit, int id, char* nom)
{

}


//sebas
int circuit_est_valide(t_circuit* circuit)
{

}


//justin
int circuit_appliquer_signal(t_circuit* circuit, int signal[], int nb_bits)
{

}


//emile
void circuit_reset(t_circuit* circuit)
{

}


//sebas
int circuit_propager_signal(t_circuit* circuit)
{

}


//justin
int circuit_get_nb_portes(const t_circuit* circuit)
{

}


//emile
t_porte* circuit_get_porte(const t_circuit* circuit, int pos)
{

}


//sebas
int circuit_get_nb_dest(const t_circuit* circuit)
{

}

//justin
t_dest* circuit_get_dest(const t_circuit* circuit, int pos)
{

}

//emile
int circuit_get_nb_sources(const t_circuit* circuit)
{

}


//sebas
t_source* circuit_get_source(const t_circuit* circuit, int pos)
{

}
// -circuit-intit()
// -circuit_destroy() // 3 boucles
// -circuit_ajouter_porte()
//... _source()
//... _destroy()
// TEST:
//>>>>>> > b8eb6a6