/*
Module: T_PIN_SORTIE
Description: Définit le type t_pin_sortie. Un t_pin_sortie est un point de connexion appartenant
			 à un élément du circuit qui émet un signal (mais n'en reçoit pas).
			 Les éléments d'un circuit ayant une pin sortie sont les portes (les sorties des portes)
			 ainsi que les entrées du circuit.

			 Pour qu'un pin de sortie émette un signal, ce signal doit être stocké dans le champs
			 valeur.  Un t_pin_sortie qui est inactif (pas alimentée) aura la valeur -1.

			 Un pin de sortie permet relie le composant auquel il appartient à d'autres composants.
			 Il doit être reliée aux "pins d'entrée" des composants auquel on souhaite se connecter.

			 Note: Contrairement à un pin d'entrée, un pin de sortie peut être reliée à plusieurs
			 pins d'entrées : Ceci permet d'émettre le même signal à plusieurs composants.

Auteur: Sébastien Hubert, Justin roy, Émile Larochelle
*/

#include "t_pin_sortie.h"

//justin
t_pin_sortie* pin_sortie_init(void) 
{

}

//emile
void pin_sortie_destroy(t_pin_sortie* pin)
{
	//Libération de toute mémoire occupée par le pin de sortie.
	free(pin->liaisons);
	free(pin->nb_liaisons);
	free(pin->valeur);
	free(pin);

}

//sebas
int pin_sortie_get_valeur(t_pin_sortie* pin)
{

}

//justin
void pin_sortie_set_valeur(t_pin_sortie* pin, int valeur)
{

}


//emile
int pin_sortie_ajouter_lien(t_pin_sortie* pin_sortie, const t_pin_entree* pin_entree)
{
	if(pin_sortie->nb_liaisons >= SORTIE_MAX_LIAISONS) {
		//Nombre maximal de liaisons atteint
		return 0; //faux
	}
	else {
		//On envoie le nom de la pin entree dans le tag liaison de la pin sortie
		pin_sortie->liaisons[(pin_sortie->nb_liaisons) + 1] = pin_entree;
		pin_sortie->nb_liaisons++;
		return 1; //vrai
	}
}


//sebas
void pin_sortie_supprimer_lien(t_pin_sortie* pin_sortie, const t_pin_entree* pin_entree)
{

}


//justin
int pin_sortie_est_reliee(t_pin_sortie* pin)
{

}

//emile
int pin_sortie_propager_signal(t_pin_sortie* pin)
{
	int nombre;
	
//On vérifie si le pin de sortie est actif et qu'il a des liaisons
// si oui on propage la valeur du pin de sortie à tous les pins d'entrées reliés
		if (pin->valeur != -1 && pin->nb_liaisons < 0) {
			for (nombre = 0; nombre < pin->nb_liaisons; nombre++) {
				pin->liaisons[nombre]->valeur = pin->valeur;
			}
			return 1; //vrai
		}
		else return 0; //faux

}


//sebas
void pin_sortie_reset(t_pin_sortie* pin)
{

}