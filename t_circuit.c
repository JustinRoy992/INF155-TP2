/*
Module: T_CIRCUIT
Description: Définit le type circuit et fournit les fonctions pour manipuler un circuit.

Auteur: Sébastien Hubert, Justin roy, Émile Larochelle
*/

#include "t_circuit.h"

//-------------------------------------------------------------------------------------//
/*Fonction qui crée un nouveau circuit vide.*/
t_circuit* circuit_init(void) 
{
	t_circuit* nouveau_circuit; /*Nouveau circuit dynamique*/

	/*Création du circuit dynamique*/
	nouveau_circuit = (t_circuit*)malloc(sizeof(t_circuit)); 

	nouveau_circuit->nb_sources = 0; /*Initialisation du nombre de sources.*/
	nouveau_circuit->nb_destinations = 0; /*Initialisation du nombre de destinations.*/
	nouveau_circuit->nb_portes = 0; /*Initialisation du nombre de portes.*/

	return nouveau_circuit; /*Retourne le nouveau circuit créé*/
}

//-------------------------------------------------------------------------------------//



//-------------------------------------------------------------------------------------//
/*Fonction qui détruit un circuit et libère la mémoire associée.*/
void circuit_destroy(t_circuit* circuit)
{
	int i; /*Variable pour l'itération*/

	/*Pour toutes les portes du circuit.*/
	for (i = 0; i < circuit->nb_portes; i++)
	{
		porte_destroy(circuit->portes[i]); /*Destruction la porte.*/
	}
	/*Pour toutes les sources du circuit.*/
	for (i = 0; i < circuit->nb_sources; i++)
	{
		source_destroy(circuit->sources[i]); /*Destruction la source.*/
	}
	/*Pour toutes les destinations du circuit.*/
	for (i = 0; i < circuit->nb_destinations; i++)
	{
		dest_destroy(circuit->destinations[i]); /*Destruction la destination.*/
	}

	free(circuit); /*Libère la mémoire du circuit*/
}

//-------------------------------------------------------------------------------------//



//-------------------------------------------------------------------------------------//
/*Fonction qui ajoute une porte au circuit.*/
t_porte* circuit_ajouter_porte(t_circuit* circuit, e_types_portes le_type, int id, char* nom)
{
	/*Vérifie si le nombre de portes n'a pas dépassé la limite maximale.*/
	if (circuit->nb_portes < MAX_PORTES) 
	{
		/*Initialise la nouvelle porte*/
		circuit->portes[circuit->nb_portes] = porte_init(id, le_type, nom);
		circuit->nb_portes++; /*Incrémente le nombre de portes*/

		return circuit->portes[circuit->nb_portes - 1]; /*Retourne la porte ajoutée*/
	}
	return NULL; /*Retourne NULL si la porte n'a pas été ajoutée*/
}

//-------------------------------------------------------------------------------------//



//-------------------------------------------------------------------------------------//
/*Fonction qui ajoute une source au circuit.*/
t_source* circuit_ajouter_source(t_circuit* circuit, int id, char* nom)
{
	/*Vérifie si le nombre de sources n'a pas dépassé la limite maximale.*/
	if (circuit->nb_sources < MAX_SOURCES) 
	{
		/*Initialise la nouvelle source*/
		circuit->sources[circuit->nb_sources] = source_init(id, nom); 
		circuit->nb_sources++; /*Incrémente le nombre de sources*/

		return circuit->sources[circuit->nb_sources - 1]; /*Retourne la source ajoutée*/
	}
	return NULL; /*Retourne NULL si la source n'a pas été ajoutée*/
}

//-------------------------------------------------------------------------------------//



//-------------------------------------------------------------------------------------//
/*Fonction qui ajoute une destination au circuit.*/
t_dest* circuit_ajouter_dest(t_circuit* circuit, int id, char* nom)
{
	/*Vérifie si le nombre de destinations n'a pas dépassé la limite maximale.*/
	if (circuit->nb_destinations < MAX_DEST)
	{
		/*Initialise la nouvelle destination*/
		circuit->destinations[circuit->nb_destinations] = dest_init(id, nom); 
		circuit->nb_destinations++; /*Incrémente le nombre de destinations*/
		
		/*Retourne la destination ajoutée*/
		return circuit->destinations[circuit->nb_destinations - 1];
	}
	return NULL;
}

//-------------------------------------------------------------------------------------//



//-------------------------------------------------------------------------------------//
/*Fonction qui vérifie si un circuit est valide.*/
int circuit_est_valide(t_circuit* circuit)
{
	int i; /*Variable pour l'itération*/
	int valide = 1;
	
	/*Vérification pour toutes les portes.*/
	for (i = 0; i < circuit->nb_portes; i++)
	{
		/*Si la porte n'est pas reliée.*/
		if (!porte_est_reliee(circuit->portes[i]))
		{
			printf("La porte %s n'est pas reliee!\n", porte_get_nom(circuit->portes[i]));
			valide = 0;
		}
	}
	/*Vérification pour tous les sources.*/
	for (i = 0; i < circuit->nb_sources; i++)
	{
		/*Si la source n'est pas reliée.*/
		if (!source_est_reliee(circuit->sources))
		{
			printf("La source %s n'est pas reliee!\n", source_get_nom(circuit->sources[i]));
			valide = 0;
		}
	}
	/*Vérification pour toutes les destinations.*/
	for (i = 0; i < circuit->nb_destinations; i++)
	{
		/*Si la destination n'est pas reliée.*/
		if (!dest_est_reliee(circuit->destinations[i]))
		{
			printf("La destination %s d'est pas reliee!\n", dest_get_nom(circuit->destinations[i]));
			valide = 0;
		}
	}
	return valide;
}

//-------------------------------------------------------------------------------------//



//-------------------------------------------------------------------------------------//
/*Fonction qui applique un signal aux sources du circuit.*/
int circuit_appliquer_signal(t_circuit* circuit, int signal[], int nb_bits)
{
	int nombre;

	if (nb_bits < circuit->nb_sources)
		return FALSE; /*Retourne faux si le nb_bits n'est pas suffisant*/
	for (nombre = 0; nombre < nb_bits; nombre++)
	{
		circuit->sources[nombre]->pin->valeur = signal[nombre]; /*Applique le signal à la source*/
	}
	return TRUE; /*Retourne vrai si le signal a été appliqué*/
}

//-------------------------------------------------------------------------------------//



//-------------------------------------------------------------------------------------//
/*Fonction qui réinitialise un circuit.*/
void circuit_reset(t_circuit* circuit)
{
	int i; /*Variable pour l'itération*/

	/*Pour toutes les portes du circuit.*/
	for (i = 0; i < circuit->nb_portes; i++)
	{
		porte_reset(circuit->portes[i]); /*Réinitialise la porte.*/
	}
	/*Pour toutes les sources du circuit.*/
	for (i = 0; i < circuit->nb_sources; i++)
	{
		source_reset(circuit->sources[i]); /*Réinitialise la source.*/
	}
	/*Pour toutes les destinations du circuit.*/
	for (i = 0; i < circuit->nb_destinations; i++)
	{
		dest_reset(circuit->destinations[i]); /*Réinitialise la destination.*/
	}
}

//-------------------------------------------------------------------------------------//



//-------------------------------------------------------------------------------------//
/*Fonction qui propage le signal dans le circuit.*/
int circuit_propager_signal(t_circuit* circuit)
{
	t_porte* file[MAX_PORTES] = { NULL }; /*File de portes*/
	int nombre,
		nombre_occuper,
		nb_iteration = 0;
	int* porte_courante;

	if (circuit_est_valide(circuit) == FALSE)
		return FALSE; /*Retourne faux si le circuit n'est pas valide*/

	for (nombre = 0; nombre < circuit->nb_sources; nombre++)
	{
		source_propager_signal(circuit->sources[nombre]);
	}

	for (nombre = 0; nombre < circuit->nb_portes; nombre++)
	{
		file[nombre] = circuit->portes[nombre];
	}
	nombre_occuper = circuit->nb_portes;

	for (nombre = 0; file[nombre_occuper] != NULL && nb_iteration < circuit->nb_portes * (circuit->nb_portes + 1) / 2; nombre++)
	{
		porte_courante = &file[nombre];

		if (porte_propager_signal(porte_courante) == 0)
		{
			if (nombre_occuper > MAX_PORTES)
			{
				nombre_occuper = 0;
			}
			porte_courante[nombre_occuper] = porte_courante;
			nombre_occuper++;
		}
		file[nombre] = NULL;
		nb_iteration++;
	}
	/*Retourne faux s'il y a une boucle*/
	if (nb_iteration > circuit->nb_portes * (circuit->nb_portes + 1) / 2) return FALSE;
	return TRUE; /*Retourne vrai si le signal a été propagé*/
}

//-------------------------------------------------------------------------------------//



//-------------------------------------------------------------------------------------//
/*Fonction qui retourne le nombre de portes dans le circuit.*/
int circuit_get_nb_portes(const t_circuit* circuit)
{
	return circuit->nb_portes; /*Retourne le nombre de portes dans le circuit.*/
}

//-------------------------------------------------------------------------------------//



//-------------------------------------------------------------------------------------//
/*Fonction qui retourne une des portes dans le circuit.*/
t_porte* circuit_get_porte(const t_circuit* circuit, int pos)
{
	/*Vérifie si la position est valide.*/
	if (0 <= pos && pos < circuit->nb_portes)
	{
		return circuit->portes[pos]; /*Retourne la porte à la position donnée.*/
	}
	return NULL; /*Retourne NULL si la position n'est pas valide.*/
}

//-------------------------------------------------------------------------------------//



//-------------------------------------------------------------------------------------//
/*Fonction qui retourne le nombre de destinations dans le circuit.*/
int circuit_get_nb_dest(const t_circuit* circuit)
{
	/*Retourne le nombre de destinations dans le circuit.*/
	return circuit->nb_destinations;
}

//-------------------------------------------------------------------------------------//



//-------------------------------------------------------------------------------------//
/*Fonction qui retourne une des destinations dans le circuit.*/
t_dest* circuit_get_dest(const t_circuit* circuit, int pos)
{
	/*Vérifie si la position est valide.*/
	if (0 <= pos && pos < circuit->nb_destinations)
	{
		/*Retourne la destination à la position donnée.*/
		return circuit->destinations[pos]; 
	}
	return NULL; /*Retourne NULL si la position n'est pas valide.*/
}

//-------------------------------------------------------------------------------------//



//-------------------------------------------------------------------------------------//
/*Fonction qui retourne le nombre de sources dans le circuit.*/
int circuit_get_nb_sources(const t_circuit* circuit)
{
	return circuit->nb_sources; /*Retourne le nombre de sources dans le circuit.*/
}

//-------------------------------------------------------------------------------------//




//-------------------------------------------------------------------------------------//
/*Fonction qui retourne une des sources dans le circuit.*/
t_source* circuit_get_source(const t_circuit* circuit, int pos)
{ 
	/*Vérifie si la position est valide.*/
	if (0 <= pos && pos < circuit->nb_sources)
	{
		return circuit->sources[pos]; /*Retourne la source à la position donnée.*/
	}
	return NULL; /*Retourne NULL si la position n'est pas valide.*/
}

//-------------------------------------------------------------------------------------//