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




//-------------------------------------------------------------------------------------//
/*Fonction qui initialise une porte.*/
t_porte* porte_init(int id, e_types_portes type, char* nom) 
{
	/*Allouer de la mémoire pour une nouvelle porte.*/
	t_porte* porte = (t_porte*)malloc(sizeof(t_porte));

	porte->id = id; /*Initialiser l'identifiant de la porte.*/
	porte->type = type; /*Initialiser le type de la porte.*/
	porte->nom = strdup(nom); /*Allouer de la mémoire et copier le nom de la porte.*/

	/*Vérifier si l'allocation de mémoire a réussi.*/
	if (porte == NULL) {
		return NULL; /*Retourner NULL si l'allocation a échoué.*/
	}
	/* Porte AND ou OR à deux entrées.*/
   if (type == PORTE_ET || type == PORTE_OU) {
	   porte->nb_entrees = 2; /*Initialiser le nombre d'entrées à 2.*/
	   porte->entrees[0] = pin_entree_init(); /*Initialiser la première entrée.*/
	   porte->entrees[1] = pin_entree_init(); /*Initialiser la deuxième entrée.*/
	   porte->sortie = pin_sortie_init();     /*Initialiser la sortie.*/

	/* Porte NOT ou XOR à une entrée.*/
   } else {
	   porte->nb_entrees = 1; /*Initialiser le nombre d'entrées à 1.*/
	   porte->entrees[0] = pin_entree_init(); /*Initialiser la seule entrée.*/
	   porte->sortie = pin_sortie_init();    /*Initialiser la sortie.*/
   }

   return porte; /*Retourner le pointeur vers la nouvelle porte créée.*/

}

//-------------------------------------------------------------------------------------//



//-------------------------------------------------------------------------------------//
/*Fonction qui détruit une porte et libère la mémoire associée.*/
void porte_destroy(t_porte* porte)
{
	/*Vérifier si le pointeur de la porte n'est pas NULL avant de libérer la mémoire.*/
	if (porte != NULL) {
		free(porte->nom); /*Libérer la mémoire du nom de la porte.*/
		free(porte->entrees[0]); /*Libérer la mémoire de la première entrée.*/
		free(porte->entrees[1]); /*Libérer la mémoire de la deuxième entrée.*/
		free(porte->sortie); /*Libérer la mémoire de la sortie.*/
		free(porte); /*Libérer la mémoire de la structure de la porte.*/
	}
}

//-------------------------------------------------------------------------------------//



//-------------------------------------------------------------------------------------//
/*Fonction qui calcule la valeur de la sortie de la porte en fonction 
de son type et de ses entrées.*/
void porte_calculer_sortie(t_porte* porte)
{
	int val; /*Variable pour stocker la valeur calculée de la sortie.*/

	/*Lorsque la porte est de type ET.*/
	if (porte->type == PORTE_ET) {

		/*Calculer la valeur de la sortie en effectuant un ET logique sur les entrées.*/
		val = (pin_entree_get_valeur(porte->entrees[0]) & 
			  pin_entree_get_valeur(porte->entrees[1]));
		/*Mettre à jour la valeur de la sortie de la porte.*/
		pin_sortie_set_valeur(porte->sortie, val);

	/*Lorsque la porte est de type OU.*/
	} else if (porte->type == PORTE_OU) {

		/*Calculer la valeur de la sortie en effectuant un OU logique sur les entrées.*/
		val = (pin_entree_get_valeur(porte->entrees[0]) ||
			   pin_entree_get_valeur(porte->entrees[1]));
		/*Mettre à jour la valeur de la sortie de la porte.*/
		pin_sortie_set_valeur(porte->sortie, val);

	/*Lorsque la porte est de type NOT.*/
	} else if (porte->type == PORTE_NOT) {

		/*Calculer la valeur de la sortie en effectuant un NOT logique sur l'entrée.*/
		val = !(pin_entree_get_valeur(porte->entrees[0]));
		/*Mettre à jour la valeur de la sortie de la porte.*/
		pin_sortie_set_valeur(porte->sortie, val);

	/*Lorsque la porte est de type XOR.*/
	} else if (porte->type == PORTE_XOR) {

		/*Calculer la valeur de la sortie en effectuant un XOR logique sur les entrées.*/
		val = (pin_entree_get_valeur(porte->entrees[0]) ^ 
				pin_entree_get_valeur(porte->entrees[1]));
		/*Mettre à jour la valeur de la sortie de la porte.*/
		pin_sortie_set_valeur(porte->sortie, val);
	}

}

//-------------------------------------------------------------------------------------//



//-------------------------------------------------------------------------------------//
/*Fonction qui relie une entrée de la porte à une source de signal.*/
int porte_relier(t_porte* porte, int num_entree, char* nom_sortie, t_pin_sortie* source)
{
	/*Vérifier si le pointeur de la porte n'est pas NULL.*/
	if (porte == NULL) {
		return 0; /*Retourner faux.*/
	}

	/*Vérifier si l'indice de l'entrée est valide.*/
	if (!(num_entree == 0 || num_entree == 1)) {
		return 0; /*Retourner faux.*/
	}

	/*Relier l'entrée spécifiée au pin de sortie source.*/
	pin_entree_relier(porte->entrees[num_entree], nom_sortie, source);
	return 1; /*Retourner vrai pour indiquer que la liaison a été effectuée.*/
}

//-------------------------------------------------------------------------------------//



//-------------------------------------------------------------------------------------//
/*Fonction qui vérifie si une porte est entièrement reliée.*/
int porte_est_reliee(t_porte* porte)
{
	int i; /*Variable pour l'itération.*/

	/*Vérifier si le pointeur de la porte est NULL.*/
	if (porte == NULL) {
		return 0; /*Retourner faux.*/
	}

	/*Vérifier si toutes les entrées de la porte sont reliées.*/
	for (i = 0; i < porte->nb_entrees; i++) {
		if (!pin_entree_est_reliee(porte->entrees[i])) {
			return 0; /*Retourner faux si une entrée n'est pas reliée.*/
		}
	}

	/*Vérifier si la sortie de la porte est reliée.*/
	if (!pin_sortie_est_reliee(porte->sortie)) {
		return 0; /*Retourner faux si la sortie n'est pas reliée.*/
	}

	return 1; /*Retourner vrai si la porte est entièrement reliée.*/
}

//-------------------------------------------------------------------------------------//



//-------------------------------------------------------------------------------------//
/*Fonction qui réinitialise une porte.*/
void porte_reset(t_porte* porte)
{

	int i; /*Variable pour l'itération.*/

	/*Réinitialiser les valeurs des entrées.*/
	for (i = 0; i < porte->nb_entrees; i++) {
		pin_entree_reset(porte->entrees[i]);
	}

	/*Réinitialiser la valeur de la sortie.*/
	pin_sortie_reset(porte->sortie);

}

//-------------------------------------------------------------------------------------//



//-------------------------------------------------------------------------------------//
/*Fonction qui propage le signal à partir de la porte.*/
int porte_propager_signal(t_porte* porte)
{
	int i; /*Variable pour l'itération.*/

	/*Vérifier si toutes les entrées de la porte ont des valeurs valides.*/
	for (i = 0; i < porte->nb_entrees; i++) {
		if (pin_entree_get_valeur(porte->entrees[i]) == -1) {
			return 0; /*Retourner faux si une entrée n'a pas de valeur valide.*/
		}
	}

	/*Calculer la valeur de la sortie de la porte.*/
	porte_calculer_sortie(porte);
	/*Propager le signal à partir du pin de sortie de la porte.*/
	pin_sortie_propager_signal(porte->sortie);

	return 1; /*Retourner vrai pour indiquer que le signal a été propagé.*/

}

//-------------------------------------------------------------------------------------//



//-------------------------------------------------------------------------------------//
/*Fonction qui retourne l'identifiant de la porte.*/
int porte_get_id(const t_porte* porte)
{
	/*Vérifier si le pointeur de la porte est NULL.*/
	if (porte == NULL) {
		return -1; /*Retourner une valeur invalide.*/
	}

	return porte->id; /*Retourner l'identifiant de la porte.*/
}

//-------------------------------------------------------------------------------------//



//-------------------------------------------------------------------------------------//
/*Fonction qui retourne le nom de la porte.*/
char* porte_get_nom(const t_porte* porte)
{
	/*Vérifier si le pointeur de la porte est NULL.*/
	if (porte == NULL) {
		return NULL; /*Retourner une valeur invalide.*/
	}

	return porte->nom; /*Retourner le nom de la porte.*/
}

//-------------------------------------------------------------------------------------//



//-------------------------------------------------------------------------------------//
/*Fonction qui retourne le nombre d'entrées de la porte.*/
int porte_get_nb_entrees(const t_porte* porte)
{
	/*Vérifier si le pointeur de la porte est NULL.*/
	if (porte == NULL) {
		return -1; /*Retourner une valeur invalide.*/
	}

	return porte->nb_entrees; /*Retourner le nombre d'entrées de la porte.*/
}

//-------------------------------------------------------------------------------------//



//-------------------------------------------------------------------------------------//
/*Fonction qui retourne le type de la porte.*/
e_types_portes porte_get_type(const t_porte* porte)
{
	/*Vérifier si le pointeur de la porte est NULL.*/
	if (porte == NULL) {
		return -1; /*Retourner une valeur invalide.*/
	}

	return porte->type; /*Retourner le type de la porte.*/
}

//-------------------------------------------------------------------------------------//



//-------------------------------------------------------------------------------------//
/*Fonction qui retourne un pointeur vers un des pins d'entrée de la porte.*/
t_pin_entree* porte_get_pin_entree(const t_porte* porte, int num)
{
	/*Vérifier si le pointeur de la porte est NULL.*/
	if (porte == NULL) {
		return NULL; /*Retourner une valeur invalide.*/
	}

	/*Vérifier si le numéro d'entrée est valide.*/
	if (!(num == 0 || num == 1 )) {
		return NULL; /*Retourner une valeur invalide.*/
	}

	return porte->entrees[num]; /*Retourner le pin d'entrée correspondant.*/
}

//-------------------------------------------------------------------------------------//



//-------------------------------------------------------------------------------------//
/*Fonction qui retourne un pointeur vers le pin de sortie de la porte.*/
t_pin_sortie* porte_get_pin_sortie(const t_porte* porte)
{
	/*Vérifier si le pointeur de la porte est NULL.*/
	if (porte == NULL) {
		return NULL; /*Retourner une valeur invalide.*/
	}

	return porte->sortie; /*Retourner le pin de sortie de la porte.*/
}

//-------------------------------------------------------------------------------------//



//-------------------------------------------------------------------------------------//
/*Fonction qui sérialise les informations de la porte dans une chaîne de caractères.*/
void porte_serialiser(const t_porte* porte, char* resultat)
{
	/*Vérifier si le pointeur de la porte est NULL.*/
	if (porte == NULL || resultat == NULL) {
		return; /*Retourner sans rien faire si une valeur est invalide.*/
	}

	/*Sérialiser les informations de la porte dans la chaîne de caractères fournie.*/
	sprintf(resultat, "Porte ID: %d\nNom: %s\nType: %d\nNombre d'entrées: %d\n",
		porte_get_id(porte), porte_get_nom(porte), porte_get_type(porte), 
		porte_get_nb_entrees(porte));

}

//-------------------------------------------------------------------------------------//

