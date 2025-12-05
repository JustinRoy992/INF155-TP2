/*
	TP2 - INF155
	Résolution de CLC

Description:

Auteurs: Sébastien Hubert, Justin Roy et Émile Larochelle
Remise: 2025-12-12
*/

#include "circuit_io.h"
#define _CRT_SECURE_NO_WARNINGS


//*************************************************************************************//
//	Constantes et Macro
//*************************************************************************************//

/*Mode de création de circuit*/
#define CREATION_MANUELLE 1
#define A_PARTIR_FICHIER 2

/*Macro qui emêche de planter si un imput est mauvais*/
#define FLUSH() while (getchar() != '\n') {}



//*************************************************************************************//
//	Déclaration des foncitons
//*************************************************************************************//

/*
Fonction: MENU_CREATION
Description: Cette fonction affiche un menu et lit la réponse. Selon le choix :
1 - Création manuelle: le chargement se fait dans le code
2 - Création à partir d'un fichier: demande du nom de fichier, ouverture du fichier et
	chargement du circuit
Il y a aussi une vérification de la validitée du circuit.

Paramètres:
- circuit: Le circuit a créer
Retour: Aucun
Paramètres modifié: Circuit.
*/
void menu_creation(t_circuit*);


/*
Fonction: DEMANDER_FICHIER
Description: Cette fonction demande un nom de fichier à ouvrir. Demande un nouveaux si
impossible de l'ouvrir.

Paramètres:
- nom_fichier: nom du fichier valide
Retour: Aucun
Paramètres modifié: nom_fichier.
*/
void demander_fichier(char*);


/*
Fonction: CREATION_MANUELLE
Description: Cette fonction crée un circuit avec des lignes de codes.

Paramètres:
- circuit: circuit à crér
Retour: Aucun
Paramètres modifié: circuit.
*/
void creation_manuelle(t_circuit*);


/*
Fonction: CREATION_A_PARTIR_FICHIER
Description: Cette fonction crée un à partir d'un fichier qui est demandé avec la fonctio
demander_fichier.

Paramètres:
- circuit: circuit à crér
Retour: Aucun
Paramètres modifié: circuit.
*/
void creation_a_partir_fichier(t_circuit*);

//-------------------------------------------------------------------------------------//



//*************************************************************************************//
//	Fonction Main
//*************************************************************************************//

void main(void)
{
	t_circuit* circuit;

	circuit = circuit_init();		/*Initialisation du circuit*/

	menu_creation(circuit);			/*Création du circuit*/

	//**** Fonction de résolution *****//

	circuit_IO_sauvegarder("circuittest.txt", circuit);		/*Sauvegarde du circuit*/

	system("pause");
}

//-------------------------------------------------------------------------------------//



//*************************************************************************************//
//	Définition des foncitons
//*************************************************************************************//



//-------------------------------------------------------------------------------------//
/*Fonction qui demande le mode de chargement*/
void menu_creation(t_circuit* circuit)
{
	int choix = 0;		/*Choux de création*/

	printf("*********************************\n");
	printf("\tTP2 - INF155\n");
	printf("\tResolution de CLC\n");
	printf("*********************************\n\n");

	printf("Choisissez un mode de creation :\n");
	printf("1 - Creation manuelle\n");
	printf("2 - Creation d'un fichier\n");

	/*Tant qu'on a pas de choix valide*/
	while (!(choix == CREATION_MANUELLE || choix == A_PARTIR_FICHIER))
	{
		/*Lire le choix*/
		scanf("%d", &choix);
		FLUSH();

		/*Message si invalide*/
		if (!(choix == CREATION_MANUELLE || choix == A_PARTIR_FICHIER))
		{
			printf("Choix invalide!\n");
		}
	}
	
	/*Création du circuit*/
	switch (choix)
	{
		case CREATION_MANUELLE:
		{
			creation_manuelle(circuit);
			break;
		}
		case A_PARTIR_FICHIER:
		{
			creation_a_partir_fichier(circuit);
			break;
		}
	}
	/*Validation du circuit*/
	if (circuit_est_valide(circuit))
	{
		printf("\nCircuit est valide!\n\n");
	}
	else
	{
		printf("\nCircuit n'est pas valide!\n\n");
	}
}

//-------------------------------------------------------------------------------------//



//-------------------------------------------------------------------------------------//
/*Fonction qui demande un fichier existant.*/
void demander_fichier(char* nom_fichier) {

	/*Initialisation de la variable du fichier.*/
	FILE* f_circuit;

	/*Tant que le fichier ouvert n'est pas valide.*/
	do {

		/*Demande le nom du fichier à ouvrir.*/
		printf("Entrez le nom du fichier : ");
		scanf("%s", nom_fichier);

		/*Tente d'ouvrir le fichier.*/
		f_circuit = fopen(nom_fichier, "r");

		/* Affiche un message d'erreur si non valide.*/
		if (f_circuit == NULL) printf("Fichier inexistant!\n");

	} while (f_circuit == NULL);

	/* Ferme le fichier. */
	fclose(f_circuit);
}

//-------------------------------------------------------------------------------------//



//-------------------------------------------------------------------------------------//
/*Création manuelle d'un circuit*/
void creation_manuelle(t_circuit* circuit)
{
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
	assert(porte_relier(porte_ou, 0, source_get_nom(source0), source_get_pin(source0)));
	assert(porte_relier(porte_ou, 1, source_get_nom(source1), source_get_pin(source1)));
	assert(porte_relier(porte_et, 0, source_get_nom(source1), source_get_pin(source1)));
	assert(porte_relier(porte_et, 1, source_get_nom(source2), source_get_pin(source2)));
	assert(porte_relier(porte_not, 0, porte_get_nom(porte_ou), porte_get_pin_sortie(porte_ou)));
	assert(porte_relier(porte_xor, 0, porte_get_nom(porte_not), porte_get_pin_sortie(porte_not)));
	assert(porte_relier(porte_xor, 1, porte_get_nom(porte_et), porte_get_pin_sortie(porte_et)));
	assert(dest_relier(dest0, porte_get_nom(porte_not), porte_get_pin_sortie(porte_not)));
	assert(dest_relier(dest1, porte_get_nom(porte_xor), porte_get_pin_sortie(porte_xor)));
}

//-------------------------------------------------------------------------------------//



//-------------------------------------------------------------------------------------//
/*Création à partir d'un fichier*/
void creation_a_partir_fichier(t_circuit* circuit)
{
	char nom_fichier[50];		/*Nom du fichier */

	/*Demander et charger le circuit*/
	demander_fichier(nom_fichier);
	circuit_IO_charger(nom_fichier, circuit);
}