/*
  TESTER Les sources et les destinations
  Auteur: Eric Thé, 3-11-2025

  Programme qui teste l'utilisation des librairies de circuits logique "t_source" 
  (avec "t_pin_sortie") et "t_dest" (avec "t_pin_entree").  
  Plusieurs tests unitaires sont faits avec "assert()".
*/
#include <assert.h>
#include "t_circuit.h"

/*int main(void)
{
	//Déclaration des variables
	t_source * source0;      //les 2 entrées
	t_source * source1;
	t_dest * dest0; 		 //les 2 destinations
	t_dest * dest1;
	t_pin_sortie * pin;      //pointeur vers un des pins de sortie (de source0 ou source1)
	t_pin_entree * pin_in;   //pointeur vers un des pins d'entrée (de dest0 ou dest1)

	//Créer tous les éléments dynamiques
	source0 = source_init(0, "S0");
	source1 = source_init(1, "S1");
	dest0 = dest_init(0, "D0");
	dest1 = dest_init(1, "D1");

	//on teste si les entrées/dests sont reliées
	if (source_est_reliee(source0) == 0)
		printf("La source %s n'est pas reliee!\n", source_get_nom(source0));

	if (source_est_reliee(source1) == 0)
		printf("La source %s n'est pas reliee!\n", source_get_nom(source1));

	if (dest_est_reliee(dest0) == 0)
		printf("La destination %s n'est pas reliee!\n", dest_get_nom(dest0));

	if (dest_est_reliee(dest1) == 0)
		printf("La destination %s n'est pas reliee!\n", dest_get_nom(dest1));

	//on récupère une référence sur le pin de sortie de source0
	pin = source_get_pin(source0);

	//on connecte source0 à la dest0
	dest_relier(dest0, source_get_nom(source0), pin);
	assert(source_est_reliee(source0) == 1);		//test unitaire rapide avec assert()
	assert(dest_est_reliee(dest0) == 1);			//test unitaire rapide avec assert()

	//on récupère une référence sur le pin d'entrée de dest0
	pin_in = dest_get_pin(dest0);
	printf("\nLa destination %s est connectee a la source %s\n", dest_get_nom(dest0), 
		                                                         pin_entree_get_lien(pin_in));

	//on connecte source0 à la dest1
	dest_relier(dest1, source_get_nom(source0), pin);
	assert(dest_est_reliee(dest1) == 1);			//test unitaire rapide avec assert()

	//on récupère une référence sur le pin d'entrée de dest1
	pin_in = dest_get_pin(dest1);
	printf("\nLa destination %s est connectee a la source %s\n", dest_get_nom(dest1),
		                                                         pin_entree_get_lien(pin_in));

	//mettre le signal à 1 dans le pin de sortie de source0 et propager le signal
	pin_sortie_set_valeur(pin, 1);
	source_propager_signal(source0);

	//TEST 1: on confirme la réception du signal (1) dans les deux destinations
	printf("\nTEST 1: %s (%d) -> %s et %s\n", source_get_nom(source0), source_get_valeur(source0),
		                                      dest_get_nom(dest0), dest_get_nom(dest1));

	printf("dest %d = %d\n", dest_get_id(dest0), dest_get_valeur(dest0));
	printf("dest %d = %d\n", dest_get_id(dest1), dest_get_valeur(dest1));

	//on efface les valeurs des deux destinations
	dest_reset(dest0);
	assert(dest_get_valeur(dest0) == INACTIF);   //test unitaire rapide avec assert()

	dest_reset(dest1);
	assert(dest_get_valeur(dest1) == INACTIF);   //test unitaire rapide avec assert()

	//on récupère une référence sur le pin de sortie de source1
	pin = source_get_pin(source1);

	//on connecte source1 à la dest1
	dest_relier(dest1, source_get_nom(source1), pin);
	assert(source_est_reliee(source1) == 1);	 //test unitaire rapide avec assert()
	assert(dest_est_reliee(dest1) == 1);		 //test unitaire rapide avec assert()

	pin_in = dest_get_pin(dest1);
	printf("\nLa destination %s est connectee a la source %s\n", dest_get_nom(dest1),
		                                                         pin_entree_get_lien(pin_in));

	//mettre le signal à 1 dans le pin de sortie de source1 et propager le signal
	pin_sortie_set_valeur(pin, 1);
	source_propager_signal(source1);

	//mettre le signal à -1 dans le pin de sortie de source0
	source_reset(source0);
	assert(source_get_valeur(source0) == INACTIF);    //test unitaire rapide avec assert()

	//mettre le signal à 0 dans le pin de sortie de source0 et propager le signal
	pin = source_get_pin(source0);
	pin_sortie_set_valeur(pin, 0);
	source_propager_signal(source0);

	//TEST 2: on confirme la réception du signal (0) dans dest0 et (1) dans dest1
	printf("\nTEST 2: %s (%d) -> %s, %s (%d) -> %s\n", 
		   source_get_nom(source0), source_get_valeur(source0), dest_get_nom(dest0),
		   source_get_nom(source1), source_get_valeur(source1), dest_get_nom(dest1));

	printf("dest %d = %d\n", dest_get_id(dest0), dest_get_valeur(dest0));
	printf("dest %d = %d\n", dest_get_id(dest1), dest_get_valeur(dest1));
	system("pause");

	//libérer les 4 allocations dynamiques
	source_destroy(source0);
	source_destroy(source1);
	dest_destroy(dest0);
	dest_destroy(dest1);

	return 0;
}*/
void construire_circuit(t_circuit* circuit);

/*****************************************************************************************/

int main(void)

{	//déclaration des variables 

	int signal[MAX_SOURCES]; 	 //les valeurs (0/1) pour les sources du circuit 

	t_circuit* circuit;   	 //le circuit complet 

	circuit = circuit_init();     //Création d’un circuit dynamique 

	construire_circuit(circuit);



	//Vérification de la validité du circuit 

	if (circuit_est_valide(circuit)) {

		printf("Circuit valide!\n");

	}

	else {

		printf("Circuit invalide!\n");

	}



	//On définit un signal de 3 bits (eg. 111) 

	for (int i = 0; i < circuit_get_nb_sources(circuit); i++) {

		printf("Quel est la valeur du signal de la source %d (0 ou 1) ? ", i);

		scanf_s("%d", &signal[i]);		//assignation du signal d'entrée pour la source #i 

	}

	circuit_reset(circuit);

	circuit_appliquer_signal(circuit, signal, circuit_get_nb_sources(circuit));



	if (circuit_propager_signal(circuit)) {

		printf("Signal propage avec succes.\n");



		for (int i = 0; i < circuit_get_nb_dest(circuit); i++)

			printf("Sortie %d: %d\n", i, dest_get_valeur(circuit_get_dest(circuit, i)));

	}

	else  printf("Erreur lors de la propagation du signal.\n");



	circuit_destroy(circuit);    //Libérer le circuit dynamique 

	system("pause");
	return EXIT_SUCCESS;

}

void construire_circuit(t_circuit* circuit)

{  //variables locales pour les composantes du circuit 

	t_porte* porte_ou;	//les 4 portes 

	t_porte* porte_et;

	t_porte* porte_not;

	t_porte* porte_xor;

	t_source* source0;	//les 3 sources 

	t_source* source1;

	t_source* source2;

	t_dest* dest0;		//les 2 destinations 

	t_dest* dest1;



	//Ajout des sources 

	source0 = circuit_ajouter_source(circuit, 0, "S0");

	source1 = circuit_ajouter_source(circuit, 1, "S1");

	source2 = circuit_ajouter_source(circuit, 2, "S2");

	//Ajout des destinations 

	dest0 = circuit_ajouter_dest(circuit, 0, "D0");

	dest1 = circuit_ajouter_dest(circuit, 1, "D1");



	//Ajout des portes 

	porte_ou = circuit_ajouter_porte(circuit, PORTE_OU, 0, "P0");

	porte_et = circuit_ajouter_porte(circuit, PORTE_ET, 1, "P1");

	porte_xor = circuit_ajouter_porte(circuit, PORTE_XOR, 2, "P2");

	porte_not = circuit_ajouter_porte(circuit, PORTE_NOT, 3, "P3");

	//Ajout des liens 

	porte_relier(porte_ou, 0, source_get_nom(source0), source_get_pin(source0));

	porte_relier(porte_ou, 1, source_get_nom(source1), source_get_pin(source1));

	porte_relier(porte_et, 0, source_get_nom(source1), source_get_pin(source1));

	porte_relier(porte_et, 1, source_get_nom(source2), source_get_pin(source2));

	porte_relier(porte_not, 0, porte_get_nom(porte_ou), porte_get_pin_sortie(porte_ou));

	porte_relier(porte_xor, 0, porte_get_nom(porte_not), porte_get_pin_sortie(porte_not));

	porte_relier(porte_xor, 1, porte_get_nom(porte_et), porte_get_pin_sortie(porte_et));

	dest_relier(dest0, porte_get_nom(porte_not), porte_get_pin_sortie(porte_not));

	dest_relier(dest1, porte_get_nom(porte_xor), porte_get_pin_sortie(porte_xor));

}
