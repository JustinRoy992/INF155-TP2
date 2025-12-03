
#include "t_circuit.h"
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
	porte_relier(porte_et, 1, source_get_nom(source2), source_get_pin(source2));	porte_relier(porte_not, 0, porte_get_nom(porte_ou), porte_get_pin_sortie(porte_ou));
	porte_relier(porte_xor, 0, porte_get_nom(porte_not), porte_get_pin_sortie(porte_not));
	porte_relier(porte_xor, 1, porte_get_nom(porte_et), porte_get_pin_sortie(porte_et));
	dest_relier(dest0, porte_get_nom(porte_not), porte_get_pin_sortie(porte_not));
	dest_relier(dest1, porte_get_nom(porte_xor), porte_get_pin_sortie(porte_xor));
}
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
		scanf("%d", &signal[i]);		//assignation du signal d'entrée pour la source #i
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
