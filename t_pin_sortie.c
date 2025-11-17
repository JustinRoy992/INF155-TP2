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

//-------------------------------------------------------------------------------------//

/*Crée un nouveau pin de sortie qui contient aucune valeur et pas de liaison.*/
t_pin_sortie* pin_sortie_init(void) {

	t_pin_sortie* nouv_pin = NULL; /*Nouveau pin de sortie dynamique*/

	nouv_pin = (t_pin_sortie*)malloc(sizeof(t_pin_sortie)); /*Création du pin dynamique*/

	/*Initiation: ce pin contient aucune valeur et pas de liaison.*/
	nouv_pin->valeur = INACTIF;
	nouv_pin->nb_liaisons = NULL;

	return nouv_pin; /*Retourne le nouveau pin de sortie*/

}

//-------------------------------------------------------------------------------------//



//-------------------------------------------------------------------------------------//

/*Libère la mémoire occupée par le pin de sortie.*/
void pin_sortie_destroy(t_pin_sortie* pin) {

	/*Libération de toute mémoire occupée par le pin de sortie.*/
	free(pin->liaisons);
	free(pin->nb_liaisons);
	free(pin->valeur);
	free(pin);

}

//-------------------------------------------------------------------------------------//


//-------------------------------------------------------------------------------------//

/*Accesseur du champ valeur.*/
int pin_sortie_get_valeur(t_pin_sortie* pin) {


}

//-------------------------------------------------------------------------------------//

/*Mutateur du champ valeur.*/
void pin_sortie_set_valeur(t_pin_sortie* pin, int valeur){

	/*Valeur = à soit - 1, 0, 1*/
	if (valeur < INACTIF || valeur > 1) { 
	
		return;  /*Valeur erronée*/

	}
	pin->valeur = valeur; /*Assigne la valeur au pin*/

}

//-------------------------------------------------------------------------------------//


//-------------------------------------------------------------------------------------//

/*Relie le pin de sortie à un pin d'entrée reçu en paramètre.*/
int pin_sortie_ajouter_lien(t_pin_sortie* pin_sortie, const t_pin_entree* pin_entree) {

	/*Vérifie si le nombre maximal de liaisons est atteint*/
	if (pin_sortie->nb_liaisons >= SORTIE_MAX_LIAISONS) {

		return 0; /*Nombre maximal de liaisons atteint*/

	}

	else {
<<<<<<< Updated upstream
		//On envoie le nom de la pin entree dans le tag liaison de la pin sortie
		pin_sortie->liaisons[pin_sortie->nb_liaisons] = pin_entree;
=======
		/*Renvoie du nom de la pin entree dans le tag liaison de la pin sortie*/
		pin_sortie->liaisons[pin_sortie->nb_liaisons] = pin_entree;
>>>>>>> Stashed changes
		pin_sortie->nb_liaisons++;
		return 1; /*Retourne vrai*/
	}
}

//-------------------------------------------------------------------------------------//


//-------------------------------------------------------------------------------------//

/*Supprime un lien existant entre le pin de sortie et un pin d'entree reçu en paramètre.*/
void pin_sortie_supprimer_lien(t_pin_sortie* pin_sortie, const t_pin_entree* pin_entree) {

}

//-------------------------------------------------------------------------------------//


//-------------------------------------------------------------------------------------//

/*Permet de vérifier si un pin de sortie est reliée à un pin d'entrée.*/
int pin_sortie_est_reliee(t_pin_sortie* pin){

	return pin->nb_liaisons != NULL; /*Retourne vrai si le pin est relié*/

}

//-------------------------------------------------------------------------------------//


//-------------------------------------------------------------------------------------//

/*Propage le signal à partir du pin de sortie passé en paramètre.*/
int pin_sortie_propager_signal(t_pin_sortie* pin) {

	int nombre; /*Compteur pour les liaisons*/

	/*Vérification si le pin de sortie est actif et qu'il a des liaisons*/
	if (pin->valeur != -1 && pin->nb_liaisons < 0) {

		/*Propager la valeur du pin de sortie à tous les pins d'entrées reliés*/
		for (nombre = 0; nombre < pin->nb_liaisons; nombre++) {
			pin->liaisons[nombre]->valeur = pin->valeur;
		}

		return 1; /*Retourne vrai*/
	}
	else return 0; /*Retourne faux*/


}

//-------------------------------------------------------------------------------------//


//-------------------------------------------------------------------------------------//

/*Réinitialise un pin de sortie.*/
void pin_sortie_reset(t_pin_sortie* pin) {



}

//-------------------------------------------------------------------------------------//