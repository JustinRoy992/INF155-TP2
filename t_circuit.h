/*
Module: T_CIRCUIT
Description: Définit le type circuit et fournit les fonctions pour manipuler un circuit.
Auteur: Anis Boubaker
Dernière modification: Eric Thé, 2025-11-1
*/


#ifndef CIRCUIT_H_
#define CIRCUIT_H_


#define MAX_SOURCES 10	//Nombre maximal de sources que peut contenir le circuit
#define MAX_DEST   10	//Nombre maximal de destinations que peut contenir le circuit
#define MAX_PORTES 10	//Nombre maximal de portes que peut contenir le circuit

#include "t_source.h"
#include "t_porte.h"
#include "t_destination.h"


//Définit le type t_circuit qui permet de stocker l'information relative à un circuit. 
typedef struct t_circuit {
	//Tableau statique qui stocke des pointeurs vers les sources de signal du circuit
	t_source *sources[MAX_SOURCES];
	
	//Tableau statique qui stocke des pointeurs vers les destinations de signal du circuit
	t_dest  *destinations[MAX_DEST];
	
	//Tableau statique qui stocke des pointeurs vers les portes incluses dans le circuit
	t_porte *portes[MAX_PORTES];

	int nb_sources;			//Nombre de sources dans le tableau d'entrées du circuit
	int nb_destinations;    //Nombre de destinations dans le tableau de sorties du circuit
	int nb_portes;			//Nombre de portes dans le tableau de portes du circuit
} t_circuit;


/*
Fonction: CIRCUIT_INIT
Description: Crée un nouveau circuit vide. 

Paramètres: Aucun
Retour: Pointeur vers le circuit créé
Paramètres modifié: Aucun.
*/
t_circuit* circuit_init(void);

/*
Fonction: CIRCUIT_DESTROY
Description: Libère la mémoire occupée par le circuit et tous ses composants.

Paramètres: 
- circuit: Pointeur vers le circuit à détruire. 
Retour: Aucun.
Paramètres modifié: circuit
*/
void circuit_destroy(t_circuit *circuit);

/*
Fonction: CIRCUIT_AJOUTER_PORTE
Description: Crée une nouvelle porte et l'ajoute au circuit. 
NDE: Il faut s'assurer qu'on ne dépasse pas le nombre de portes permis (CIRCUIT_MAX_PORTES).

Paramètres:
- circuit: Pointeur vers le circuit auquel la porte sera ajoutée
- type: Type de la porte créée parmi les types de portes prédéfinis (e_type_porte, voir t_porte.h)
Retour: Pointeur vers la nouvelle porte créée s'il a été possible de la créer. NULL sinon.
*/
t_porte* circuit_ajouter_porte(t_circuit *circuit, e_types_portes le_type, int id, char *nom);

/*
Fonction: CIRCUIT_AJOUTER_SOURCE
Description: Crée une nouvelle source de circuit et l'ajoute au circuit.
NDE: Il faut s'assurer qu'on ne dépasse pas le nombre de sources permis (MAX_SOURCES).

Paramètres:
- circuit: Pointeur vers le circuit auquel la source sera ajoutée
Retour: Pointeur vers la source créée s'il a été possible de la créer. NULL sinon.
*/
t_source* circuit_ajouter_source(t_circuit *circuit, int id, char *nom);

/*
Fonction: CIRCUIT_AJOUTER_DEST
Description: Crée une nouvelle destination de circuit et l'ajoute au circuit.
NDE: Il faut s'assurer qu'on ne dépasse pas le nombre de destinations permis (MAX_DEST).

Paramètres:
- circuit: Pointeur vers le circuit auquel la destination sera ajoutée
Retour: Pointeur vers la destination créée s'il a été possible de la créer. NULL sinon.
*/
t_dest* circuit_ajouter_dest(t_circuit *circuit, int id, char *nom);

/*
Fonction: CIRCUIT_EST_VALIDE
Description: Vérifie si un circuit donné est un circuit valide. Pour qu'un circuit soit valide
			 toutes les sources, portes et destination du circuit doivent être reliées. 
NDE: Vous utiliserez les fonctions source_est_reliee(), dest_est_reliee() et porte_est_reliee(). 

Paramètres:
- circuit: Pointeur vers le circuit dont on veut vérifier la validité
Retour: (Booléen) Vrai si le circuit est valide, faux sinon.
*/
int circuit_est_valide(t_circuit *circuit);

/*
Fonction: CIRCUIT_APPLIQUER_SIGNAL
Description: Alimente le circuit avec le signal "signal" passé en paramètre. Le signal est un 
		     ensemble de bits (entiers qui valent 0 ou 1) qui sont appliqués aux entrées du circuit. 
			 Les bits seront appliqués par ordre aux différentes sources du circuit (le premier bit
			 du tableau à la source 0 du circuit, le 2e bit à la source 1, etc.)
NDE: 
- Vous devez vous assurer que le nombre de bits du signal est suffisant pour alimenter le circuit.
  (donc le nombre de bits doit être égal au nombre de sources du circuit)
- Pour appliquer un bit à une la source, il faut changer la valeur du pin de sortie de la la source. 
  (champ .pin dans une t_source).

Paramètres:
- circuit: Pointeur vers le circuit auquel on souhaite appliquer le signal
- signal[]: Tableau de bits qui constituent le signal à appliquer au circuit
- nb_bits: Nombre de bits dans le tableau signal[]. 
Retour: (Booléen) : Vrai si il a été possible d'appliquer le signal (i.e. assez de bits), 
                    Faux sinon.
*/
int circuit_appliquer_signal(t_circuit *circuit, int signal[], int nb_bits);

/*
Fonction: CIRCUIT_RESET
Description: Réinitialise un circuit en "désalimentant" tous ses composants 
             (sources, destinations et portes).
			 Cette fonction fait appel aux fonctions de reset des diverses composants du circuit: 
			 source_reset(), dest_reset() et porte_reset().

Paramètres:
- circuit: Pointeur vers le circuit à réinitialiser.
Retour: Aucun.
*/
void circuit_reset(t_circuit *circuit);

/*
Fonction: CIRCUIT_PROPAGER_SIGNAL
Description: Propage le signal appliqué aux sources du circuit à tous les composants. Le signal est 
             propagé de proche en proche: on part des sources et on envoie leur signal aux pins 
			 auquelles elles sont connectées.  Si la source est connectée à une porte, la porte 
			 calcule sa sortie puis envoie son signal au pin à lequel elle est connectée, etc. 
			 jusqu'à ce que toutes les destinations du circuit reçoivent un signal. 

			 Avant d'appeler cette fonction, on doit avoir appliqué un signal au circuit 
			 (fonction: circuit_appliquer_signal()). 
			 La propagation du signal ne sera faite que si le circuit est valide.
			 
			 La fonction retourne faux s'il a été impossible de propager un signal dans 
			 l'un des cas suivants:
			 - Le circuit est invalide (voir t_circuit_est_valide)
			 - Le circuit n'a pas été préalablement alimenté (voir: circuit_appliquer_signal())
			 - En cas de présence de boucles dans le circuit
NDE: Pour propager le signal de proche en proche, vous utiliserez l'algorithme décrit dans l'énoncé 
     qui utilise une file de portes (module file_portes)

Paramètres:
- circuit: Pointeur vers le circuit à réinitialiser.
Retour: Booléen vrai si le signal s'est correctement propagé jusqu'aux sorties. Faux sinon. 
*/
int circuit_propager_signal(t_circuit *circuit);

/************************** Les ACCESSEURS ************************************/

/*
Fonction: CIRCUIT_GET_NB_PORTES
Description: Retourne le nombre de portes dans le circuit. 

Paramètres:
- circuit: Pointeur vers le circuit
Retour: Entier: le nombre de portes du circuit.
*/
int circuit_get_nb_portes(const t_circuit *circuit);

/*
Fonction: CIRCUIT_GET_PORTE
Description: Retourne une des portes dans le circuit.

Paramètres:
- circuit: Pointeur vers le circuit
- pos: la position de la porte désirée
Retour: Pointeur vers la porte désirée si "pos" est valide. NULL sinon.
*/
t_porte* circuit_get_porte(const t_circuit *circuit, int pos);

/*
Fonction: CIRCUIT_GET_NB_DEST
Description: Retourne le nombre de destinations dans le circuit.

Paramètres:
- circuit: Pointeur vers le circuit
Retour: Entier: le nombre de destinations du circuit.
*/
int circuit_get_nb_dest(const t_circuit *circuit);

/*
Fonction: CIRCUIT_GET_DEST
Description: Retourne une des destinations dans le circuit.

Paramètres:
- circuit: Pointeur vers le circuit
- pos: la position de la destination désirée
Retour: Pointeur vers la destination désirée si "pos" est valide. NULL sinon.
*/
t_dest* circuit_get_dest(const t_circuit *circuit, int pos);

/*
Fonction: CIRCUIT_GET_NB_SOURCES
Description: Retourne le nombre de sources dans le circuit.

Paramètres:
- circuit: Pointeur vers le circuit
Retour: Entier: le nombre de sources du circuit.
*/
int circuit_get_nb_sources(const t_circuit *circuit);

/*
Fonction: CIRCUIT_GET_SOURCE
Description: Retourne une des sources du circuit.

Paramètres:
- circuit: Pointeur vers le circuit
- pos: la position de la source désirée
Retour: Pointeur vers la source désirée si "pos" est valide. NULL sinon.
*/
t_source* circuit_get_source(const t_circuit *circuit, int pos);
 
#endif