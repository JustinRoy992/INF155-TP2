/*
Module: T_CIRCUIT
Description: Définit le type circuit et fournit les fonctions pour manipuler un circuit.

Auteur: Sébastien Hubert, Justin roy, Émile Larochelle
*/

#include "t_circuit.h"


t_circuit* circuit_init(void) 
{
	t_circuit* nouveau_circuit;

	nouveau_circuit = (t_circuit*)malloc(sizeof(t_circuit));

	nouveau_circuit->nb_sources = 0;
	nouveau_circuit->nb_destinations = 0;
	nouveau_circuit->nb_portes = 0;

	return nouveau_circuit;
}


void circuit_destroy(t_circuit* circuit)
{
	source_destroy(circuit->sources);
	dest_destroy(circuit->destinations);
	porte_destroy(circuit->portes);

	free(circuit);
}


t_porte* circuit_ajouter_porte(t_circuit* circuit, e_types_portes le_type, int id, char* nom)
{
	if (circuit->nb_portes < MAX_PORTES)
	{
		circuit->portes[circuit->nb_portes] = porte_init(id, le_type, nom);
		circuit->nb_portes++;

		return circuit->portes[circuit->nb_portes - 1];
	}
	return NULL;
}


t_source* circuit_ajouter_source(t_circuit* circuit, int id, char* nom)
{
	if (circuit->nb_sources < MAX_SOURCES)
	{
		circuit->sources[circuit->nb_sources] = source_init(id, nom);
		circuit->nb_sources++;

		return circuit->sources[circuit->nb_sources - 1];
	}
	return NULL;
}


t_dest* circuit_ajouter_dest(t_circuit* circuit, int id, char* nom)
{
	if (circuit->nb_destinations < MAX_DEST)
	{
		circuit->destinations[circuit->nb_destinations] = dest_init(id, nom);
		circuit->nb_destinations++;

		return circuit->destinations[circuit->nb_destinations - 1];
	}
	return NULL;
}


int circuit_est_valide(t_circuit* circuit)
{
	int i;
	
	for (i = 0; i < circuit->nb_portes; i++)
	{
		if (!porte_est_reliee(circuit->portes[i]))
		{
			return 0;
		}
	}
	for (i = 0; i < circuit->nb_sources; i++)
	{
		if (!source_est_reliee(circuit->sources))
		{
			return 0;
		}
	}
	for (i = 0; i < circuit->nb_destinations; i++)
	{
		if (!dest_est_reliee(circuit->destinations))
		{
			return 0;
		}
	}
	return 1;
}


int circuit_appliquer_signal(t_circuit* circuit, int signal[], int nb_bits)
{
	
}


void circuit_reset(t_circuit* circuit)
{
	int i;

	for (i = 0; i < circuit->nb_portes; i++)
	{
		porte_reset(circuit->portes[i]);
	}
	for (i = 0; i < circuit->nb_sources; i++)
	{
		source_reset(circuit->sources[i]);
	}
	for (i = 0; i < circuit->nb_destinations; i++)
	{
		dest_reset(circuit->destinations[i]);
	}
}


int circuit_propager_signal(t_circuit* circuit)
{

}


int circuit_get_nb_portes(const t_circuit* circuit)
{
	return circuit->nb_portes;
}


t_porte* circuit_get_porte(const t_circuit* circuit, int pos)
{
	if (0 < pos && pos < circuit->nb_portes)
	{
		return circuit->portes[pos];
	}
	return NULL;
}


int circuit_get_nb_dest(const t_circuit* circuit)
{
	return circuit->nb_destinations;
}


t_dest* circuit_get_dest(const t_circuit* circuit, int pos)
{
	if (0 < pos && pos < circuit->nb_destinations)
	{
		return circuit->destinations[pos];
	}
	return NULL;
}


int circuit_get_nb_sources(const t_circuit* circuit)
{
	return circuit->nb_sources;
}


t_source* circuit_get_source(const t_circuit* circuit, int pos)
{
	if (0 < pos && pos < circuit->nb_sources)
	{
		return circuit->sources[pos];
	}
	return NULL;
}

// -circuit-intit()
// -circuit_destroy() // 3 boucles
// -circuit_ajouter_porte()
//... _source()
//... _destroy()
// TEST:
//>>>>>> > b8eb6a6