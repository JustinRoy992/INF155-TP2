/*
Module: CIRCUIT_IO
Description: Module de charge et de création de fichier pour ouvrir une circuit préfait
ou pour enregistrer le circuit.

Auteur: Sébastien Hubert, Justin roy, Émile Larochelle
*/

#include "circuit_io.h"

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
		if (f_circuit == NULL) printf("ERREUR : Nom de fichier invalide!\n");

	} while (f_circuit == NULL);

	/* Ferme le fichier. */
	fclose(f_circuit);
}

//-------------------------------------------------------------------------------------//



//-------------------------------------------------------------------------------------//
/*Fonction qui sauvegarde un circuit dans un nouveau fichier*/
void circuit_IO_sauvegarder(const char* nom_fichier, const  t_circuit* circuit)
{
	int i, j;				/*Compteurs*/
	int nb_sources,			/*Nombre de sources dans le circuit*/
		nb_dest,			/*Nombre de destinations dans le circuit*/
		nb_portes,			/*Nombre de portes dans le circuit*/
		nb_entree;			/*Nombre de entrées dans une porte*/

	FILE* f_circuit;		/*Initialisation de la variable du fichier.*/

	char s_resultat[50];	/*String de resultat de sérialisation*/

	f_circuit = fopen(nom_fichier, "wt");	/*Ouvre le fichier*/
	assert(!(f_circuit == NULL));			/*Check si le fichier est bien ouvert*/

	/*Lit le nombre de sources, destinations et portes*/
	nb_sources = circuit_get_nb_sources(circuit);
	nb_dest = circuit_get_nb_dest(circuit);
	nb_portes = circuit_get_nb_portes(circuit);

	/*Écrit au fichier*/
	fprintf(f_circuit, "%d %d %d\n", 
		nb_sources,
		nb_dest,
		nb_portes);

	/*Écrit à l'écran*/
	printf("Source|Dest. |Porte\n");
	printf("%d %6d %6d\n\n",
		nb_sources,
		nb_dest,
		nb_portes);

	/*Sauvegarde de composantes*/
	printf("~~~~~~ Composantes ~~~~~~\n");
	printf("Sources (ID, Nom) :\n");

	/*Pour chaques sources : sérialiser, écrir au ficher et à l'écran*/
	for (i = 0; i < nb_sources; i++)
	{
		source_serialiser(circuit_get_source(circuit, i), s_resultat);
		fprintf(f_circuit, "%s\n", s_resultat);
		printf("%s\n", s_resultat);
	}

	printf("\nDestinations (ID, Nom) :\n");

	/*Pour chaques destination : sérialiser, écrir au ficher et à l'écran*/
	for (i = 0; i < nb_dest; i++)
	{
		dest_serialiser(circuit_get_dest(circuit, i), s_resultat);
		fprintf(f_circuit, "%s\n", s_resultat);
		printf("%s\n", s_resultat);
	}

	printf("\nPortes (ID, Type, Nom) :\n");

	/*Pour chaques portes : sérialiser, écrir au ficher et à l'écran*/
	for (i = 0; i < nb_portes; i++)
	{
		porte_serialiser(circuit_get_porte(circuit, i), s_resultat);
		fprintf(f_circuit, "%s\n", s_resultat);
		printf("%s\n", s_resultat);
	}

	/*Sauvegarde des liens*/
	printf("\n~~~~~~~~~ Liens ~~~~~~~~~\n");
	printf("\nPortes :\n");

	/*Pour chaque portes*/
	for (i = 0; i < nb_portes; i++)
	{
		/*Écrire le nom de la porte*/
		fprintf(f_circuit, "%s", porte_get_nom(circuit_get_porte(circuit, i)));
		printf("%s\t", porte_get_nom(circuit_get_porte(circuit, i)));

		/*Lit le nombre d'entrées de la porte (1 ou 2)*/
		nb_entree = porte_get_nb_entrees(circuit_get_porte(circuit, i));

		/*Pour chaques entrées*/
		for (j = 0; j < nb_entree; j++)
		{
			/*Vérifie si la pin d'entrée est reliée*/
			if (pin_entree_est_reliee(
					porte_get_pin_entree(
						circuit_get_porte(circuit, i), 
						j)))
			{
				/*Écrit à qui la pin est reliée*/
				fprintf(f_circuit, " %s", 
					pin_entree_get_lien(
						porte_get_pin_entree(
							circuit_get_porte(circuit, i), 
							j))
				);
				printf(" %s", 
					pin_entree_get_lien(
						porte_get_pin_entree(
							circuit_get_porte(circuit, i), 
							j))
				);
			}

			/*Si elle n'est pas reliée : écrire "XX"*/
			else
			{
				fprintf(f_circuit, " XX");
				printf(" XX");
			}
		}

		/*Passe à la prichaine ligne*/
		fprintf(f_circuit, "\n");
		printf("\n");
	}

	printf("\nDestinations :\n");

	/*Pour chaque destinations*/
	for (i = 0; i < nb_dest; i++)
	{
		/*Écrire le nom de la destination*/
		fprintf(f_circuit, "%s", dest_get_nom(circuit_get_dest(circuit, i)));
		printf("%s\t", dest_get_nom(circuit_get_dest(circuit, i)));

		/*Vérifie si la pin d'entrée est reliée*/
		if (pin_entree_est_reliee(dest_get_pin(circuit_get_dest(circuit, i))))
		{
			/*Écrit à qui la pin est reliée*/
			fprintf
			(
				f_circuit, 
				" %s",
				pin_entree_get_lien(
					dest_get_pin(
						circuit_get_dest(circuit, i)))
			);
			printf
			(
				" %s",
				pin_entree_get_lien(
					dest_get_pin(
						circuit_get_dest(circuit, i)))
			);
		}

		/*Si elle n'est pas reliée : écrire "XX"*/
		else
		{
			fprintf(f_circuit, " XX");
			printf(" XX");
		}

		/*Passe à la prichaine ligne*/
		fprintf(f_circuit, "\n");
		printf("\n");
	}

	/*Ferme le fichier*/
	fclose(f_circuit);
}

//-------------------------------------------------------------------------------------//



//-------------------------------------------------------------------------------------//
/*Fonction qui charge un circuit à partir d'un fichier existant*/
void circuit_IO_charger(const char* chemin_acces, t_circuit* circuit)
{
	int nb_source,			/*Nombre de source dans le circuit*/
		nb_dest,			/*Nombre de destination dans le circuit*/
		nb_porte,			/*Nombre de porte dans le circuit*/
		nb_entree,			/*Nombre de entrées dans une porte*/
		i,					/*Compteur*/
		id,					/*Identification des composantes*/
		pos_actuelle,		/*Position de la composante actuelle*/
		pos_a_relier;		/*Position de la composante à relier*/

	char nom_actuelle[NOM_TAILLE_MAX];	/*Nom de la composante actuelle*/
	char nom_a_relier[NOM_TAILLE_MAX];	/*Nom de la composante à relier*/

	e_types_portes type;	/*Type de porte*/

	FILE* f_circuit;		/*Initialisation de la variable du fichier.*/

	f_circuit = fopen(chemin_acces, "r");	/*Ouvre le fichier*/
	assert(!(f_circuit == NULL));			/*Check si le fichier est bien ouvert*/

	/*Lit les premier termes de nombre de composantes*/
	fscanf(f_circuit, "%d%d%d\n", &nb_source, &nb_dest, &nb_porte);

	/*Pour chaques sources : Lire et ajouter au circuit*/
	for (i = 0; i < nb_source; i++)
	{
		fscanf(f_circuit, "%d%s", &id, nom_actuelle);
		circuit_ajouter_source(circuit, id, nom_actuelle);
	}

	/*Pour chaques destinations : Lire et ajouter au circuit*/
	for (i = 0; i < nb_dest; i++)
	{
		fscanf(f_circuit, "%d%s", &id, nom_actuelle);
		circuit_ajouter_dest(circuit, id, nom_actuelle);
	}

	/*Pour chaques portes : Lire et ajouter au circuit*/
	for (i = 0; i < nb_porte; i++)
	{
		fscanf(f_circuit, "%d%d%s", &id, &type, nom_actuelle);
		circuit_ajouter_porte(circuit, type, id, nom_actuelle);
	}

	/*Tant que pas à la fin du fichier*/
	while (!feof(f_circuit))
	{
		/*Lire le nom de la composante*/
		fscanf(f_circuit, "%s", nom_actuelle);

		/*Si c'est une porte*/
		if (nom_actuelle[0] == 'P')
		{
			/*Trouver son ID*/
			pos_actuelle = (nom_actuelle[1] - 48);

			/*Touver le nombre de pin d'entrées (1 ou 2)*/
			nb_entree = porte_get_nb_entrees(circuit_get_porte(circuit, pos_actuelle));
			
			/*Répette selon le nombre de pin d'entrées*/
			for (i = 0; i < nb_entree; i++)
			{
				/*Lire la composante à relier*/
				fscanf(f_circuit, "%s", nom_a_relier);

				/*Trouver son ID*/
				pos_a_relier = (nom_a_relier[1] - 48);

				/*Si c'est une porte*/
				if (nom_a_relier[0] == 'P')
				{
					/*Relie la porte actuelle à la porte à relier*/
					assert(porte_relier
					(
						circuit_get_porte(circuit, pos_actuelle),
						i,
						nom_a_relier,
						porte_get_pin_sortie(circuit_get_porte(circuit, pos_a_relier))
					));
				}

				/*Si c'est une source à relier*/
				else if (nom_a_relier[0] == 'S')
				{
					/*Relie la porte actuelle à la source à relier*/
					assert(porte_relier
					(
						circuit_get_porte(circuit, pos_actuelle),
						i,
						nom_a_relier,
						source_get_pin(circuit_get_source(circuit, pos_a_relier))
					));
				}

				/*Si c'est XX ou autre : rien faire*/
			}
		}

		/*Si c'est une destination*/
		else if (nom_actuelle[0] == 'D')
		{
			/*Trouver son ID*/
			pos_actuelle = (nom_actuelle[1] - 48);

			/*Lire la composante à relier*/
			fscanf(f_circuit, "%s", nom_a_relier);

			/*Si c'est une porte*/
			if (nom_a_relier[0] == 'P')
			{
				/*Trouver son ID*/
				pos_a_relier = (nom_a_relier[1] - 48);

				/*Relier la destination à la porte à relier*/
				assert(dest_relier
				(
					circuit_get_dest(circuit, pos_actuelle),
					nom_a_relier,
					porte_get_pin_sortie(circuit_get_porte(circuit, pos_a_relier))
				));
			}

			/*Si c'est XX ou autre : rien faire*/
		}

		fscanf(f_circuit, "\n");
	}
}

//-------------------------------------------------------------------------------------//