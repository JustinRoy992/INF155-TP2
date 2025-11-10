/*
  TESTER Les sources et les destinations
  Auteur: Eric Thé, 3-11-2025

  Programme qui teste l'utilisation des librairies de circuits logique "t_source" 
  (avec "t_pin_sortie") et "t_dest" (avec "t_pin_entree").  
  Plusieurs tests unitaires sont faits avec "assert()".
*/
#include <assert.h>
#include "t_source.h"
#include "t_dest.h"

int main(void)
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
}