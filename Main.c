#include "circuit_io.h"

#define CREATION_MANUELLE 1
#define A_PARTIR_FICHIER 2

/*Macro qui emêche de planter si un imput est mauvais*/
#define FLUSH() while (getchar() != '\n') {}


void menu_creation(t_circuit*);

void demander_fichier(char*);

void creation_manuelle(t_circuit*);

void creation_a_partir_fichier(t_circuit*);

void main(void)
{
	t_circuit* circuit;

	circuit = circuit_init();

	menu_creation(circuit);

	system("pause");
}

//-------------------------------------------------------------------------------------//

void menu_creation(t_circuit* circuit)
{
	int choix = 0;

	printf("*********************************\n");
	printf("\tTP2 - INF155\n");
	printf("\tResolution de CLC\n");
	printf("*********************************\n\n");

	printf("Choisissez un mode de creation :\n");
	printf("1 - Creation manuelle\n");
	printf("2 - Creation d'un fichier\n");

	while (!(choix == CREATION_MANUELLE || choix == A_PARTIR_FICHIER))
	{
		scanf("%d", &choix);
		FLUSH();

		if (!(choix == CREATION_MANUELLE || choix == A_PARTIR_FICHIER))
		{
			printf("Choix invalide!\n");
		}
	}

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

	if (circuit_est_valide(circuit))
	{
		printf("Circuit est valide!\n");
	}
	else
	{
		printf("Circuit n'est pas valide!\n");
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

void creation_manuelle(t_circuit* circuit)
{
	
}

//-------------------------------------------------------------------------------------//



//-------------------------------------------------------------------------------------//
void creation_a_partir_fichier(t_circuit* circuit)
{
	char nom_fichier[50];

	demander_fichier(nom_fichier);
	circuit_IO_charger(nom_fichier, circuit);
}