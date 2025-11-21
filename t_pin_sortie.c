/*
Module: T_PIN_SORTIE
Description: D�finit le type t_pin_sortie. Un t_pin_sortie est un point de connexion appartenant
			 � un �l�ment du circuit qui �met un signal (mais n'en re�oit pas).
			 Les �l�ments d'un circuit ayant une pin sortie sont les portes (les sorties des portes)
			 ainsi que les entr�es du circuit.

			 Pour qu'un pin de sortie �mette un signal, ce signal doit �tre stock� dans le champs
			 valeur.  Un t_pin_sortie qui est inactif (pas aliment�e) aura la valeur -1.

			 Un pin de sortie permet relie le composant auquel il appartient � d'autres composants.
			 Il doit �tre reli�e aux "pins d'entr�e" des composants auquel on souhaite se connecter.

			 Note: Contrairement � un pin d'entr�e, un pin de sortie peut �tre reli�e � plusieurs
			 pins d'entr�es : Ceci permet d'�mettre le m�me signal � plusieurs composants.

Auteur: S�bastien Hubert, Justin roy, �mile Larochelle
*/

#include "t_pin_sortie.h"

//-------------------------------------------------------------------------------------//

/*Cr�e un nouveau pin de sortie qui contient aucune valeur et pas de liaison.*/
t_pin_sortie* pin_sortie_init(void) {

	t_pin_sortie* nouv_pin = NULL; /*Nouveau pin de sortie dynamique*/

	nouv_pin = (t_pin_sortie*)malloc(sizeof(t_pin_sortie)); /*Cr�ation du pin dynamique*/

	/*Initiation: ce pin contient aucune valeur et pas de liaison.*/
	nouv_pin->valeur = INACTIF;
	nouv_pin->nb_liaisons = NULL;

	return nouv_pin; /*Retourne le nouveau pin de sortie*/

}

//-------------------------------------------------------------------------------------//



//-------------------------------------------------------------------------------------//

/*Lib�re la m�moire occup�e par le pin de sortie.*/
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

	return pin->valeur;
}

//-------------------------------------------------------------------------------------//

/*Mutateur du champ valeur.*/
void pin_sortie_set_valeur(t_pin_sortie* pin, int valeur){

	/*Valeur = � soit - 1, 0, 1*/
	if (valeur < INACTIF || valeur > 1) { 
	
		return;  /*Valeur erron�e*/

	}
	pin->valeur = valeur; /*Assigne la valeur au pin*/

}

//-------------------------------------------------------------------------------------//


//-------------------------------------------------------------------------------------//

/*Relie le pin de sortie � un pin d'entr�e re�u en param�tre.*/
int pin_sortie_ajouter_lien(t_pin_sortie* pin_sortie, const t_pin_entree* pin_entree) {

	/*V�rifie si le nombre maximal de liaisons est atteint*/
	if (pin_sortie->nb_liaisons >= SORTIE_MAX_LIAISONS) {

		return 0; /*Nombre maximal de liaisons atteint*/

	}

	else {

		/*Renvoie du nom de la pin entree dans le tag liaison de la pin sortie*/
		pin_sortie->liaisons[pin_sortie->nb_liaisons] = pin_entree;
		pin_sortie->nb_liaisons++;
		return 1; /*Retourne vrai*/
	}
}

//-------------------------------------------------------------------------------------//


//-------------------------------------------------------------------------------------//

/*Supprime un lien existant entre le pin de sortie et un pin d'entree re�u en param�tre.*/
void pin_sortie_supprimer_lien(t_pin_sortie* pin_sortie, const t_pin_entree* pin_entree) {
	int i, trouvee = 0;

	for (i = 0; i < pin_sortie->nb_liaisons; i++)
	{
		if (pin_sortie->liaisons[i] == pin_entree || trouvee)
		{
			trouvee == 1;
			pin_sortie->liaisons[i] == pin_sortie->liaisons[i + 1];
		}
	}
	pin_sortie->nb_liaisons--;
}

//-------------------------------------------------------------------------------------//


//-------------------------------------------------------------------------------------//

/*Permet de v�rifier si un pin de sortie est reli�e � un pin d'entr�e.*/
int pin_sortie_est_reliee(t_pin_sortie* pin){

	return pin->nb_liaisons != NULL; /*Retourne vrai si le pin est reli�*/

}

//-------------------------------------------------------------------------------------//


//-------------------------------------------------------------------------------------//

/*Propage le signal � partir du pin de sortie pass� en param�tre.*/
int pin_sortie_propager_signal(t_pin_sortie* pin) {

	int nombre; /*Compteur pour les liaisons*/

	/*V�rification si le pin de sortie est actif et qu'il a des liaisons*/
	if (pin->valeur != -1 && pin->nb_liaisons < 0) {

		/*Propager la valeur du pin de sortie � tous les pins d'entr�es reli�s*/
		for (nombre = 0; nombre < pin->nb_liaisons; nombre++) {
			pin->liaisons[nombre]->valeur = pin->valeur;
		}

		return 1; /*Retourne vrai*/
	}
	else return 0; /*Retourne faux*/


}

//-------------------------------------------------------------------------------------//


//-------------------------------------------------------------------------------------//

/*R�initialise un pin de sortie.*/
void pin_sortie_reset(t_pin_sortie* pin) {

	pin->valeur = INACTIF;

}

//-------------------------------------------------------------------------------------//