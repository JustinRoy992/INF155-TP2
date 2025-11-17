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

t_pin_sortie* pin_sortie_init(void) 
{

}

void pin_sortie_destroy(t_pin_sortie* pin)
{

}

int pin_sortie_get_valeur(t_pin_sortie* pin)
{

}

void pin_sortie_set_valeur(t_pin_sortie* pin, int valeur)
{

}

int pin_sortie_ajouter_lien(t_pin_sortie* pin_sortie, const t_pin_entree* pin_entree)
{

}

void pin_sortie_supprimer_lien(t_pin_sortie* pin_sortie, const t_pin_entree* pin_entree)
{

}

int pin_sortie_est_reliee(t_pin_sortie* pin)
{

}

int pin_sortie_propager_signal(t_pin_sortie* pin)
{

}

void pin_sortie_reset(t_pin_sortie* pin)
{

}