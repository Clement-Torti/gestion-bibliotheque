//
//  projet.c
//  Projet Gestion d'une bibliothèque
//
//  Created by Clement TORTI & Florent BECOUZE on 20/12/2017.
//  Copyright © 2017 Clement Torti. All rights reserved.
//

#include "projet.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////
//--------------------------------1- LECTURE données fichiers---------------------------------//
///////////////////////////////////////////////////////////////////////////////////////////////////////

//Lecture lecteur, ouvrage et emprunt

Lecteur lireLecteur(FILE *flot)
{
    Lecteur l;

    fscanf(flot, "%d%*c", &l.numLecteur);


    fgets(l.nom, 28, flot);
    l.nom[strlen(l.nom) - 1] = '\0';

    fgets(l.prenom, 28, flot);
    l.prenom[strlen(l.prenom) - 1] = '\0';

    fgets(l.ville, 48, flot);
    l.ville[strlen(l.ville) - 1] = '\0';

    fgets(l.numTel, 14, flot);
    l.numTel[strlen(l.numTel) - 1] = '\0';

    fscanf(flot, "%d", &l.nbRetard);

    fscanf(flot, "%d", &l.nbEmprunt);

    return l;
}
//----
Ouvrage lireOuvrage(FILE *flot)
{
	Ouvrage o;
	char emprunte;

	fscanf(flot, "%s%*c", &o.cote);

	fgets(o.nomOuvrage, 28, flot);
	o.nomOuvrage[strlen(o.nomOuvrage) -1 ] = '\0';

	fgets(o.categorie, 28, flot);
	o.categorie[strlen(o.categorie) -1 ] = '\0';

	fgets(o.auteur, 28 , flot);
	o.auteur[strlen(o.auteur) -1 ] = '\0';

	fscanf(flot, "%c%*c", &emprunte);

	if(emprunte == 'O')
        o.emprunte = true;
    else
        o.emprunte = false;

	return o;
}
//----
Date lireDate(FILE *flot)
{
    Date d;
    fscanf(flot, "%d/%d/%d%*c", &d.jour, &d.mois, &d.annee);

    return d;
}
//----
Emprunt lireEmprunt(FILE *flot)
{
    Emprunt e;

        fread(&e.numLecteur, sizeof(int), 1, flot);
        fread(e.cote, sizeof(char), 6, flot);

        fread(&e.dateEmprunt.jour, sizeof(int), 1, flot);
        fread(&e.dateEmprunt.mois, sizeof(int), 1, flot);
        fread(&e.dateEmprunt.annee, sizeof(int), 1, flot);

        fread(&e.dateRetour.jour, sizeof(int), 1, flot);
        fread(&e.dateRetour.mois, sizeof(int), 1, flot);
        fread(&e.dateRetour.annee, sizeof(int), 1, flot);

    return e;
}



//Affichage lecteur, article et emprunt

void reduireLongueur(char *nom, char *nouvNom,  int taille)
{
    int i = 0;
    while(i < taille-2 && nom[i] != '\0')
    {
        nouvNom[i] = nom[i];
        i = i + 1;
    }

    if(nom[i] != '\0') //Ajout de 2 petits points à la fin si la chaine est trop longue
    {
        nouvNom[i] = '.';
        nouvNom[i+1] = '.';
        nouvNom[taille] = '\0';
    } else {
        nouvNom[i] = '\0';
    }

}
//----
void ajouterBlanc(char *nom, int taille)
{
    int nbBlanc, nbChar, i;
    nbChar = strlen(nom);
    nbBlanc = taille - nbChar; // Nombre de blanc à ajouter pour harmoniser

    for(i = 0; i<nbBlanc; i++)
        nom[nbChar + i] = ' ';

    nom[taille] = '\0';

}
//----
void afficherLecteur(Lecteur l)
{
    char ville[15], nom[10], prenom[10];

	printf("%d\t", l.numLecteur);

	reduireLongueur(l.nom, nom, 10);
	ajouterBlanc(nom, 10);
	printf("%s", nom);

	reduireLongueur(l.prenom, prenom, 10);
	ajouterBlanc(prenom, 10);
	printf("%s", prenom);

	reduireLongueur(l.ville, ville, 15);
	ajouterBlanc(ville, 15);
	printf("%s\t", ville);

	printf("%s\t", l.numTel);
	printf("%d\t", l.nbRetard);
	printf("%d\n", l.nbEmprunt);
}
//----
void afficherCarteLecteur(Lecteur l)
{
    printf("\n\nNum Lecteur : %d\n", l.numLecteur);
    printf("Nom : %s\n", l.nom);
    printf("Prenom : %s\n", l.prenom);
    printf("Ville : %s\n", l.ville);
    printf("Num Tel : %s\n", l.numTel);
    printf("Nb retard : %d\n", l.nbRetard);
    printf("Nb emprunt : %d\n\n", l.nbEmprunt);
}
//----
void afficherOuvrage(Ouvrage o)
{
    char nom[15], categorie[10], auteur[10];

    printf("%s\t", o.cote);

    reduireLongueur(o.nomOuvrage, nom, 15);
    ajouterBlanc(nom, 15);
    printf("%s\t", nom);

    reduireLongueur(o.categorie, categorie, 10);
    ajouterBlanc(categorie, 10);
    printf("%s\t", categorie);

    reduireLongueur(o.auteur, auteur, 10);
    ajouterBlanc(auteur, 10);
	printf("%s\t", auteur);

	if(o.emprunte == true)
		printf("OUI\t\n");
	else
		printf("NON\t\n");
}
//----
void afficherCarteOuvrage(Ouvrage o)
{
    printf("\nCote : %s\n", o.cote);
    printf("Titre : %s\n", o.nomOuvrage);
    printf("Categorie : %s\n", o.categorie);
    printf("Auteur : %s\n", o.auteur);
    printf("Emprunte ? : ");

    if(o.emprunte == true)
        printf("Oui \n\n");
    else
        printf("Non \n\n");

}
//----
void afficherDate(Date d)
{
    printf("%02d/%02d/%02d", d.jour, d.mois, d.annee);
}
//----
void afficherEmprunt(Emprunt e)
{
    printf("%d\t", e.numLecteur);
    printf("%s\t", e.cote);
    afficherDate(e.dateEmprunt);
    printf("\t");
    afficherDate(e.dateRetour);
    printf("\n");

}



//Affichage tableau lecteur, article, emprunt
void afficherTableauLecteur(Lecteur **tab, int nb)
{
	int i;
	printf("Lecteurs : \n\n");
    printf("Num\tNom\t  Prenom\tVille\t\tNumTel\t\tRetard\tEmprunt\n");
    printf("-------------------------------------------------------------------------------\n");
	for(i = 0; i<nb; i++)
	{
		afficherLecteur(*tab[i]);
		printf("\n");
	}


}
//----
void afficherTableauOuvrage(Ouvrage **tab, int nb)
{
	int i;
    printf("Ouvrages : \n\n");
    printf("Cote\tTitre\t\tCategorie\tAuteur\t\tEmprunte(Oui/Non)\n");
    printf("--------------------------------------------------------------------------\n");
	for(i=0 ; i<nb ; i++)
	{
		afficherOuvrage(*tab[i]);
		printf("\n");
	}
}
//----
void afficherListeEmprunt(ListeEmprunt l)
{
    printf("Num\tCote\tDate Emprunt\tDate Retour\n");
    printf("-------------------------------------------\n");

    while(l != NULL)
    {
        afficherEmprunt(l->e);
        l = l->suiv;
    }
    printf("\n");

}



////////////////////////////////////////////////////////////////////////////////////////////////////////////
//-----------------------------2-CHARGEMENT dans tableau/liste---------------------------------//
///////////////////////////////////////////////////////////////////////////////////////////////////////////


Lecteur **chargementLecteur(char *nomFichier , int *taille, int *tmax)
{
	*taille = 0;
	*tmax = 5;
	Lecteur **tab, **aux, l;
	FILE *flot;

	flot = fopen(nomFichier, "r");
	if(flot == NULL)
	{
		printf("Fichier %s introuvable\n");
		exit(-1);
	}

	tab = (Lecteur **) malloc(sizeof(Lecteur *) * *tmax);
	if(tab == NULL)
	{
		printf("Pb malloc\n");
		exit(1);
	}

	l = lireLecteur(flot);
	while(!feof(flot))
	{
		if(*taille == *tmax)
		{
			*tmax = *tmax + 5;
			aux = (Lecteur **) realloc(tab, sizeof(Lecteur *) * *tmax);
			if(aux == NULL)
			{
				printf("Pb realloc\n");
				exit(1);
			}

			tab = aux;
		}

		tab[*taille] = (Lecteur *) malloc(sizeof(Lecteur));
		if(tab[*taille] == NULL)
		{
			printf("Pb malloc\n");
			exit(1);
		}

		*tab[*taille] = l;
		*taille = *taille + 1;

		l = lireLecteur(flot);
	}

	fclose(flot);

	return tab;
}
//----
Ouvrage **chargementTableauOuvrage(char *nomFichier, int *tmax)
{
    int i;
    Ouvrage **tab;
    FILE *flot;

    flot = fopen(nomFichier, "r");
    if(flot == NULL)
    {
        printf("Fichier %s introuvable\n", nomFichier);
        exit(-1);
    }

    fscanf(flot, "%d", tmax);

    tab = (Ouvrage **) malloc(sizeof(Ouvrage *) * *tmax);
    if(tab == NULL)
    {
        printf("Pb malloc\n");
        exit(1);
    }

    for(i=0; i<*tmax; i++)
    {
        tab[i] = (Ouvrage *) malloc(sizeof(Ouvrage));
        if(tab[i] == NULL)
        {
            printf("Pb malloc\n");
            exit(1);
        }
        *tab[i] = lireOuvrage(flot);
    }

    fclose(flot);
    return tab;

}

//----
ListeEmprunt listeVide(void)
{
    return NULL;
}
//----
ListeEmprunt chargementListeEmprunt(char *nomFichier)
{
    FILE *flot;
    ListeEmprunt l;
    Emprunt e;

    l = listeVide();

    flot = fopen(nomFichier, "rb");
    if(flot == NULL)
    {
        printf("L'ouverture du fichier %s a echouee\n", nomFichier);
        exit(-1);
    }

    e = lireEmprunt(flot);

    while(!feof(flot))
    {
        l = inserer(l, e);
        e = lireEmprunt(flot);
    }

    fclose(flot);

    return l;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////
//-----------------------3-INSERTION d'un élément dans le tableau------------------------//
//////////////////////////////////////////////////////////////////////////////////////////////////////


//Création du lecteur, ouvrage, emprunt à afficher
Bool verificationNumTel(char *numTel)
{
    int i = 0, cpt = 0;
    while(numTel[i] != '\0')
    {
        if(numTel[i] == '0' || numTel[i] == '1' || numTel[i] == '2' ||
           numTel[i] == '3' || numTel[i] == '4' || numTel[i] == '5' ||
           numTel[i] == '6' || numTel[i] == '7' || numTel[i] == '8' ||
           numTel[i] == '9' )
           {
                cpt = cpt + 1;
                i = i + 1;
           } else if (numTel[i] == " ") {
                i = i + 1;
           } else { // charactere interdit
               printf("%c", numTel[i]);
                return false;
           }
    }

    if(cpt == 10) //bon nombre de chiffre
        return true;
    else
        return false;

}

Lecteur creerLecteur(int numLect)
{
    Lecteur l;
    char nom[30], prenom[30], ville[30], numTel[16];

    printf("Tapez d'abord un nom :\n");
    fgets(nom, 28, stdin);
    nom[strlen(nom) - 1] = '\0';

    printf("Entrez la prenom :\n");
    fgets(prenom, 28, stdin);
    prenom[strlen(prenom) - 1] = '\0';

    printf("Entrez la ville :\n");
    fgets(ville, 28, stdin);
    ville[strlen(ville) - 1] = '\0';

    printf("Entrez un numero de telephone :\n");
    fgets(numTel, 16, stdin);
    numTel[strlen(numTel) - 1] = '\0';

    while(!verificationNumTel(numTel))
    {
        printf("Numéro de téléphone invalide, retapez :\n");
        fgets(numTel, 16, stdin);
        numTel[strlen(numTel) - 1] = '\0';
    }

    l.numLecteur = numLect;
    strcpy(l.nom, nom);
    strcpy(l.prenom, prenom);
    strcpy(l.ville, ville);
    strcpy(l.numTel, numTel);
    l.nbRetard = 0;
    l.nbEmprunt = 0;

    return l;
}
//----
Ouvrage creerOuvrage(Ouvrage **tab, int nb)
{
    int pos, trouve;
    Ouvrage o;


    printf("Entrez la cote :\n");
    scanf("%s%*c" ,o. cote);

    pos = rechercheDicoOuvrage(tab, o.cote,  nb, &trouve);
    while(trouve == 1) // la cote est déjà prise
    {
        printf("Cette cote existe deja pour le livre :\n");
        afficherCarteOuvrage(*tab[pos]);
        printf("Entrer une nouvelle cote :\n");
        scanf("%s%*c", o.cote);
        pos = rechercheDicoOuvrage(tab, o.cote, nb, &trouve);
    }

    printf("Entrez un titre :\n");
    fgets(o.nomOuvrage, 28, stdin);
    o.nomOuvrage[strlen(o.nomOuvrage) - 1] = '\0';

    printf("Entrez une catégorie parmie la liste (BD, Fantaisie, SF, Policier, Revue, Magazine, Manga) :\n");
    fgets(o.categorie, 28, stdin);
    o.categorie[strlen(o.categorie) - 1] = '\0';

    while (strcmp(o.categorie, "BD") != 0 && strcmp(o.categorie, "Fantaisie") != 0 &&
           strcmp(o.categorie, "SF") != 0 && strcmp(o.categorie, "Policier") != 0 &&
           strcmp(o.categorie, "Revue") != 0 && strcmp(o.categorie, "Magazine") != 0 &&
           strcmp(o.categorie, "Manga") != 0 )
    {

        printf("Categorie invalide, veuillez retapez parmie la liste (BD, Fantaisie, SF, Policier, Revue, Magazine, Manga) :\n");
        fgets(o.categorie, 28, stdin);
        o.categorie[strlen(o.categorie) - 1] = '\0';
    }

    printf("Entrez l'auteur :\n");
    fgets(o.auteur, 28, stdin);
    o.auteur[strlen(o.auteur) - 1] = '\0';

    o.emprunte = false;

    return o;

}
//----
Emprunt creerEmprunt(Lecteur **tab, int nb,  Ouvrage **tabOuv, int nbOuv, int *codeRetour)
{
    int pos, pos2, trouve;
    char nom[30], prenom[30];
    Emprunt e;

    printf("Entrez le numero de lecteur qui emprunte :\n");
    scanf("%d%*c", &e.numLecteur);

    printf("Entrez son nom :\n");
    fgets(nom, 28, stdin);
    nom[strlen(nom) - 1] = '\0';

    printf("Entrez son prenom :\n");
    fgets(prenom, 28, stdin);
    prenom[strlen(prenom) - 1] = '\0';

    pos = rechercheDicoLecteur(tab, e.numLecteur, nom, prenom, nb, &trouve);
    if(trouve != 1 || tab[pos]->nbEmprunt >= 10) // Le lecteur n'existe pas ou a déjà emprunter 10 ouvrages
    {
        printf("Le lecteur ne peut pas emprunter d'ouvrage\n");
        *codeRetour = -1;
        return e;
    }

    printf("Entrez la cote de l'ouvrage :\n");
    scanf("%s%*c", e.cote);

    pos2 = rechercheDicoOuvrage(tabOuv, e.cote, nbOuv, &trouve);
    if(trouve == -1 || tabOuv[pos2]->emprunte == true) //L'ouvrage n'existe pas ou n'est pas disponible
    {
        printf("L'ouvrage est indisponible\n");
        *codeRetour = -1;
        return e;
    }

    //Mise à jour des informations relatives au lecteur et à l'ouvrage
    tab[pos]->nbEmprunt ++;
    tabOuv[pos2]->emprunte = true;

    printf("Entrez la date actuelle (jj/mm/aa):\n");
    scanf("%d/%d/%d%*c", &e.dateEmprunt.jour, &e.dateEmprunt.mois, &e.dateEmprunt.annee);

    if(e.dateEmprunt.mois % 12 == 0) //Le retour se fera l'annee prochaine
    {
        e.dateRetour.jour = e.dateEmprunt.jour;
        e.dateRetour.mois = 1;
        e.dateRetour.annee = e.dateEmprunt.annee + 1;
    } else {
        e.dateRetour.jour = e.dateEmprunt.jour;
        e.dateRetour.mois = e.dateEmprunt.mois + 1;
        e.dateRetour.annee = e.dateEmprunt.annee;
    }

        *codeRetour = 1;
        return e;

}

//trie par fusion (tableau lecteur)
void copierLecteur(Lecteur **R, int i, int j, Lecteur **tab)
{
    int k = 0;
    while (i<j)
    {
        R[k] = tab[i];
        k = k + 1;
        i = i + 1;
    }

}
//----
void fusionLecteur(Lecteur **R, int n, Lecteur **S, int m, Lecteur **tab)
{
    int i = 0, j = 0, k = 0;

    while(i<n && j<m)
    {
       if(comparerNomPrenom(R[i]->nom, R[i]->prenom, S[j]->nom, S[j]->prenom) < 0)
       {
           tab[k] = R[i];
           k = k + 1;
           i = i + 1;

       } else if(comparerNomPrenom(R[i]->nom, R[i]->prenom, S[j]->nom, S[j]->prenom) > 0) {

            tab[k] = S[j];
            k = k + 1;
            j = j + 1;

       } else {

           if(R[i]->numLecteur < S[j]->numLecteur)  //Ici les des lecteurs ont le même nom et prénom, on regarde leur numLecteur
           {
                tab[k] = R[i];
                k = k + 1;
                i = i + 1;
           } else {
                tab[k] = S[j];
                k = k + 1;
                j = j + 1;
           }

       }
    }



    while(i<n)
    {
        tab[k] = R[i];
        k = k + 1;
        i = i + 1;
    }

    while(j<m)
    {
        tab[k] = S[j];
        k = k + 1;
        j = j + 1;
    }

}
//----
int comparerNomPrenom(char *nom1, char *prenom1, char *nom2, char *prenom2)
{
    if(strcmp(nom1, nom2) != 0) // Les noms sont différents
        return strcmp(nom1, nom2);

    //Les noms sont identiques
    return strcmp(prenom1, prenom2);

}
//----
void triDicoLecteur(Lecteur **tab, int nb)
{
	if(nb == 1)
		return;

	Lecteur **R, **S;

	R = (Lecteur **) malloc(sizeof(Lecteur *) * nb/2);
	S = (Lecteur **) malloc(sizeof(Lecteur *) * (nb - nb/2));

	if(R == NULL || S == NULL)
	{
		printf("Pb malloc\n");
		exit(1);
	}

	copierLecteur(R, 0, nb/2, tab);
	copierLecteur(S, nb/2, nb, tab);

	triDicoLecteur(R, nb/2);
	triDicoLecteur(S, nb - nb/2);

	fusionLecteur(R, nb/2, S, nb - nb/2, tab);

	free(R);
	free(S);

}


//Tri par échange (tableau ouvrage)
void echangerOuvrage(Ouvrage **tab, int i, int j)
{
    Ouvrage *aux;

    aux = tab[i];
    tab[i] = tab[j];
    tab[j] = aux;

}
//----
int plusGrand(Ouvrage **tab, int nb)
{
    int pge = 0, i;
    for(i = 1; i<nb; i++)
        if(strcmp(tab[i]->cote, tab[pge]->cote) > 0)// Le plus grand est le dernier par ordre alphabétique
            pge = i;

    return pge;
}
//----
void triEchangeOuvrage(Ouvrage **tab, int nb)
{
    int pge ;

    while (nb > 1)
    {
        pge = plusGrand(tab , nb);
        echangerOuvrage(tab, pge, nb-1);
        nb = nb - 1;
    }

}

//recherche dichotomique
int rechercheDicoLecteur(Lecteur **tab, int numLect, char *nom, char *prenom, int nb, int *trouve)
{
	int inf, m, sup;
	inf = 0;
	sup = nb - 1;

	while(inf <= sup)
	{
		m = (inf + sup) / 2;

		if(comparerNomPrenom(tab[m]->nom, tab[m]->prenom, nom, prenom) == 0)
        {
            if(tab[m]->numLecteur == numLect)
            {
                *trouve = 1;
                return m;
            } else if (tab[m]->numLecteur < numLect) {
                *trouve = -2; // Meme nom et prenom mais numero de lecteur different
                inf = m + 1;
            } else {
                *trouve = -2;
                sup = m - 1;
            }
        } else if (comparerNomPrenom(tab[m]->nom, tab[m]->prenom, nom, prenom) < 0) {
            inf = m + 1;
        } else {
            sup = m - 1;
        }

	}

    if(*trouve != -2)
        *trouve = -1;

	return inf;
}
//----
int rechercheDicoOuvrage(Ouvrage **tab, char *cote, int nb, int *trouve)
{
        int inf, m, sup;
        inf = 0;
        sup = nb - 1;

        while(inf <= sup)
        {
            m = (inf + sup) / 2;
            if(strcmp(tab[m]->cote, cote) == 0)
            {
                *trouve = 1;
                return m;
            } else if (strcmp(cote, tab[m]->cote) < 0) {
                sup = m - 1;
            } else {
                inf = m + 1;
            }
        }

        *trouve = -1;
        return inf;
}

//insertion
void decalageADroiteLecteur(Lecteur **tab, int pos, int nb)
{
    int i;

    for(i = nb; i>pos; i--)
        tab[i] = tab[i-1];

}
//----
void insertionLecteur(Lecteur l, Lecteur **tab, int *nb, int *tmax)
{
    int pos, trouve, reponse;
    Lecteur **aux;

    pos = rechercheDicoLecteur(tab, l.numLecteur, l.nom, l.prenom, *nb, &trouve);
    if (trouve == 1)
    {
        printf("Le lecteur %s %s existe deja, insertion impossible\n", l.prenom, l.nom);
        return;
    }

    if(trouve == -2)
    {
        afficherCarteLecteur(*tab[pos -1]); //Le lecteur existant est à l'index placer juste avant
        printf("Un lecteur %s %s existe déjà, souhaitez-vous quand même l'insérer ?(Oui: 1 - Non: 2) : ", l.prenom, l.nom);
        scanf("%d%*c", &reponse);
        if(reponse == 2 )
        {
            printf("insertion annulee\n\n");
            return;
        }

    }

    if(*nb == *tmax) // Plus de place pour une insertion
    {
       *tmax = *tmax + 1;
        aux = (Lecteur **) realloc(tab, sizeof(Lecteur *) * *tmax);
        if(aux == NULL)
        {
            printf("Pb realloc\n");
            return;
        }

			tab = aux;
    }

    decalageADroiteLecteur(tab, pos, *nb);
    *nb = *nb + 1;
    tab[pos] = (Lecteur *) malloc(sizeof(Lecteur));
    if(tab[pos] == NULL)
    {
        printf("Pb malloc\n");
        return;
    }

    *tab[pos] = l;

}
//----
void decalageADroiteOuvrage(Ouvrage **tab, int pos, int nb)
{
    int i;
    for(i = nb; i>pos; i--)
        tab[i] = tab[i-1];
}
//----
void insertionOuvrage(Ouvrage o, Ouvrage **tab, int *nb)
{
    int pos, trouve;
    Ouvrage **aux;

    pos = rechercheDicoOuvrage(tab, o.cote, *nb, &trouve);
    if(trouve == 1)
    {
        printf("Insertion impossible, l'ouvrage existe deja\n");
        return;
    }

    aux = (Ouvrage **) realloc(tab, sizeof(Ouvrage *) * *nb);
    if(aux == NULL)
    {
        printf("Pb realloc\n");
        return;
    }
    tab = aux;

    decalageADroiteOuvrage(tab, pos, *nb);
    *nb = *nb + 1;

    tab[pos] = (Ouvrage *) malloc(sizeof(Ouvrage));
    if(tab[pos] == NULL)
    {
        printf("Pb malloc\n");
        return;
    }

    *tab[pos] = o;

}

//Insertion dans liste
ListeEmprunt insererEnTete(ListeEmprunt l , Emprunt e)
{
        Maillon *m;
        m = (Maillon *) malloc(sizeof(Maillon));

        if(m == NULL)
        {
            printf("Pb malloc\n");
            return l;
        }

        m->e = e;
        m->suiv = l;

        return m;
}
//----
int comparerEmprunt(Emprunt e1, Emprunt e2) //Comparaison basée d'abord sur le num Lecteur puis la cote
{
    if(e1.numLecteur == e2.numLecteur)
        return strcmp(e1.cote, e2.cote);

    return e1.numLecteur - e2.numLecteur;
}
//----
ListeEmprunt inserer(ListeEmprunt l, Emprunt e)
{
    if(l == NULL)
        return insererEnTete(l, e);

    if(comparerEmprunt(e, l->e) == 0)
    {
        printf("L'emprunt existe deja, insertion impossible\n");
        return l;
    }


    if (comparerEmprunt(e, l->e) < 0)
        return insererEnTete(l, e);

    l->suiv = inserer(l->suiv, e);

    return l;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------4-SUPPRESSION d'un élément --------------------------------//
//////////////////////////////////////////////////////////////////////////////////////////////////////////


//Suppression d'un élément dans le tableau
void decalageAGaucheLecteur(Lecteur **tab, int pos, int nb)
{
    int i;
    for(i=pos; i<nb-1; i++)
        tab[i] = tab[i + 1];

}
//----
void supprimerLecteur(Lecteur **tab, int numLect, char *nom, char *prenom,  int *nb)
{
    int pos, trouve;

    pos = rechercheDicoLecteur(tab, numLect, nom, prenom, *nb, &trouve);

    if(trouve != 1) // Le lecteur n'existe pas
    {
        printf("Suppression impossible, le lecteur %s %s n'existe pas.\n", prenom, nom);
        return;
    }

    if(tab[pos]->nbEmprunt != 0) //Suppression impossible car le lecteur a emprunté des livres
    {
        printf("\nSuppression du lecteur %s %s impossible car celui-ci a emprunte %d livre(s)\n\n", tab[pos]->prenom, tab[pos]->nom, tab[pos]->nbEmprunt);
        return;
    }

    afficherCarteLecteur(*tab[pos]);
    free(tab[pos]);
    decalageAGaucheLecteur(tab, pos, *nb);
    *nb = *nb - 1;
    printf("Suppression effectuee\n\n");

}
//----
void decalageAGaucheOuvrage(Ouvrage **tab, int pos, int nb)
{
    int i;
    for(i = pos; i<nb-1; i++)
        tab[i] = tab[i + 1];
}
void supprimerOuvrage(Ouvrage **tab, char *cote, int *nb)
{
    int pos, trouve;

    pos = rechercheDicoOuvrage(tab, cote, *nb, &trouve);

    if(trouve == -1)
    {
        printf("Ouvrage introuvable, suppression impossible\n");
        return;
    }

    if(tab[pos]->emprunte == true) //Suppression impossible, le livre est en cours d'emprunt
    {
        printf("L'ouvrage %s ne peut pas etre supprime car il est emprunte\n\n", tab[pos]->nomOuvrage);
        return;
    }

    afficherCarteOuvrage(*tab[pos]);
    free(tab[pos]);
    decalageAGaucheOuvrage(tab, pos, *nb);
    *nb = *nb - 1;
    printf("Suppression effectuée\n\n");

}
//----
ListeEmprunt supprimerEnTete(ListeEmprunt l)
{
    ListeEmprunt aux;
    if(l == NULL)
    {
        printf("Op. interdite\n");
        return l;
    }
    aux = l;
    l = l->suiv;
    free(aux);

    return l;

}
//----
int comparerDate(Date d1, Date d2)
{
    if((d1.annee - d2.annee) != 0)
        return d1.annee - d2.annee;
    if((d1.mois -d2.mois) != 0)
        return d1.mois - d2.mois;

    return d1.jour -d2.jour;
}
//----
ListeEmprunt supprimer(ListeEmprunt l, Emprunt e, int *codeRetour)
{
    if(l == NULL)
    {
        printf("Op. interdite\n");
        *codeRetour = -1;
        return l;
    }

    if(comparerEmprunt(e, l->e) == 0)
    {
            //Le livre a t'il était rendu en retard ?
            printf("Entrez la date du jour (jj/mm/yy) :\n");
            Date date = lireDate(stdin);

            if(comparerDate(date,l->e.dateRetour) > 0)
                *codeRetour = 2; // Oui
             else
                *codeRetour = 1; // Non

         return supprimerEnTete(l);
    }

    if(comparerEmprunt(e, l->e) < 0)
    {
        *codeRetour = -1;
        printf("L'emprunt n'existe pas\n");
        return l;
    }

    l->suiv = supprimer(l->suiv, e, codeRetour);

    return l;
}

//////////////////////////////////////////////////////////////////////////////////////////////////
//---------------------------5-MODIFICATION d'une structure--------------------------//
/////////////////////////////////////////////////////////////////////////////////////////////////

void modifierLecteur(Lecteur **tab, int numLect, char *nom, char *prenom, int nb)
{
    Lecteur l;
    int pos, trouve;

    pos = rechercheDicoLecteur(tab, numLect, nom, prenom, nb, &trouve);
    if(trouve != 1)
    {
        printf("Le lecteur %s %s n'existe pas \n", nom, prenom);
        return;
    }

    printf("Pour modifier le lecteur, ");
    l = creerLecteur(tab[pos]->numLecteur); //Le lecteur existe, on le réécrit
    l.nbEmprunt = tab[pos]->nbEmprunt;
    l.nbRetard = tab[pos]->nbRetard;
    *tab[pos] = l;

    triDicoLecteur(tab, nb); // Il faut eventuellement trier le tableau en cas de changement de nom et prenom

    printf("Modification effectuee\n\n");
}
//----
void modifierOuvrage(Ouvrage **tab, char *cote, int nb)
{
    Ouvrage o;
    int pos, trouve;

    pos = rechercheDicoOuvrage(tab, cote, nb, &trouve);

    if(trouve == -1)
    {
        printf("Modification impossible, l'ouvrage %s n'existe pas\n", cote);
        return;
    }

    printf("Pour effectuer la modification, ");
    strcpy(tab[pos]->cote , ""); // On remplace temporairement la cote du livre pour permettre la creation du nouvel ouvrage
    o = creerOuvrage(tab, nb);
    o.emprunte = tab[pos]->emprunte;
    *tab[pos] = o;

    triEchangeOuvrage(tab, nb); // Il faut eventuellement trier le tableau en cas de changement de cote

    printf("Modification effectuee\n\n");

}
//----
ListeEmprunt modifierEmprunt(ListeEmprunt l, Emprunt e)
{
    if(l == NULL)
    {
        printf("\nEmprunt introuvable\n\n");
        return l;
    }

    if(comparerEmprunt(e, l->e) == 0)
    {
        printf("Saisir une nouvelle date de retour (jj/mm/aa) :\n");
        Date date = lireDate(stdin);
        while(comparerDate(date, l->e.dateEmprunt) < 0)
        {
            printf("Le date de retour doit etre superieur a la date d'emprunt, retapez(jj/mm/aa) :\n");
            date = lireDate(stdin);
        }
        (l->e.dateRetour).jour = date.jour;
        (l->e.dateRetour).mois = date.mois;
        (l->e.dateRetour).annee = date.annee;

        return l;
    }

    if(comparerEmprunt(e, l->e) < 0) //l'emprunt n'existe pas
    {
        printf("Emprunt introuvable\n");
        return l;
    }

    l->suiv = modifierEmprunt(l->suiv, e);

    return l;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////
//------------------------------6-SAUVEGARDE dans un fichier------------------------------//
/////////////////////////////////////////////////////////////////////////////////////////////////////

//Sauvegarde dans fichier texte
void sauvegarderTableauLecteur(char *nomFichier, Lecteur **tab, int nb)
{
    int i;
    FILE *flot;

    flot = fopen(nomFichier, "w");
    if(flot == NULL)
    {
        printf("Problème lors de la création du fichier %s\n", nomFichier);
    }

    for (i = 0; i<nb; i++)
    {
        fprintf(flot, "%d\n", tab[i]->numLecteur);
        fprintf(flot, "%s\n", tab[i]->nom);
        fprintf(flot, "%s\n", tab[i]->prenom);
        fprintf(flot, "%s\n", tab[i]->ville);
        fprintf(flot, "%s\n", tab[i]->numTel);
        fprintf(flot, "%d\n", tab[i]->nbRetard);
        fprintf(flot, "%d\n", tab[i]->nbEmprunt);

    }

    fclose(flot);

}
//----
void sauvegarderTableauOuvrage(char *nomFichier, Ouvrage **tab, int nb)
{
    int i;
    FILE *flot;
    flot = fopen(nomFichier, "w");

    if(flot == NULL)
    {
        printf("Problème lors de la création du fichier %s en mode ecriture\n", nomFichier);
        exit(-1);
    }

    fprintf(flot, "%d\n", nb);

    for (i=0; i<nb; i++)
    {
        fprintf(flot, "%s\n", tab[i]->cote);
        fprintf(flot, "%s\n", tab[i]->nomOuvrage);
        fprintf(flot, "%s\n", tab[i]->categorie);
        fprintf(flot, "%s\n", tab[i]->auteur);

        if(tab[i]->emprunte == true)
            fprintf(flot, "O\n");
        else
            fprintf(flot, "N\n");
    }


    fclose(flot);


}
//Fichier binaire
void sauvegarderListeEmprunt(char *nomFichier, ListeEmprunt l)
{
    FILE *flot;
    flot = fopen(nomFichier, "wb");
    if(flot == NULL)
    {
        printf("Pb lors de l'ouverture du fichier %s en mode ecriture", nomFichier);
        return;
    }

    while(l != NULL)
    {
        fwrite(&(l->e.numLecteur), sizeof(int), 1, flot);
        fwrite(l->e.cote, sizeof(char), 6, flot);

        fwrite(&(l->e.dateEmprunt.jour), sizeof(int), 1, flot);
        fwrite(&(l->e.dateEmprunt).mois, sizeof(int), 1, flot);
        fwrite(&(l->e.dateEmprunt).annee, sizeof(int), 1, flot);

        fwrite(&(l->e.dateRetour).jour, sizeof(int), 1, flot);
        fwrite(&(l->e.dateRetour).mois, sizeof(int), 1, flot);
        fwrite(&(l->e.dateRetour).annee, sizeof(int), 1, flot);

        l = l->suiv;
    }

    fclose(flot);
}

//Globale
void sauvegarder(char *nomFichierLecteur, Lecteur **tabLect, int nbLect, char *nomFichierOuvrage, Ouvrage **tabOuv, int nbOuv, char *nomFichierEmprunt, ListeEmprunt l)
{
    sauvegarderTableauLecteur(nomFichierLecteur, tabLect, nbLect);
    sauvegarderTableauOuvrage(nomFichierOuvrage, tabOuv, nbOuv);
    sauvegarderListeEmprunt(nomFichierEmprunt, l);
}




//////////////////////////////////////////////////////////////////////////////////////////////////
//------------------------------------------7-MENU------------------------------------------//
/////////////////////////////////////////////////////////////////////////////////////////////////


void afficherMenu(void)
{
    printf("Menus :\n\n");

    printf("Fonctions Lecteurs: \n");
    printf("\t1-Afficher tous les lecteurs\n");
    printf("\t2-Inserer un nouveau lecteur\n");
    printf("\t3-Supprimer un lecteur\n");
    printf("\t4-Modifier les informations d'un lecteur\n\n");

    printf("Fonctions Ouvrages: \n");
    printf("\t5-Afficher tous les ouvrages\n");
    printf("\t6-Inserer un nouvel ouvrage\n");
    printf("\t7-Supprimer un ouvrage\n");
    printf("\t8-Modifier les informations d'un ouvrage\n\n");

    printf("Fonctions emprunts: \n");
    printf("\t9-Afficher tous les emprunts\n");
    printf("\t10-Inserer un nouvel emprunt\n");
    printf("\t11-Supprimer un emprunt\n");
    printf("\t12-Modifier un emprunt\n\n");

    printf("\t13-Recherches diverses\n\n");

    printf("\t14-Sauvegarder et quitter\n\n");

}
//----
void afficherSousMenu(void)
{
    printf("Fonctions de recherche :\n\n");
    printf("\t1-Rechercher les ouvrages empruntes par un lecteur\n");
    printf("\t2-Rechercher la liste des ouvrages non rendu a la date limite\n");
    printf("\t3-Rechercher les lecteurs d'une ville\n");
    printf("\t4-Rechercher les ouvrages d'une certaine categorie\n\n");

    printf("Fonctions d'affichage :\n\n");
    printf("\t5-Afficher un lecteur\n");
    printf("\t6-Afficher un ouvrage\n");
    printf("\t7-Afficher un emprunt\n\n");

}
//----
int choixMenu(int nbPossibilite)
{
    int choix;
    printf("Entrez un numéro d'action à effectuer (-1 pour quitter) : ");
    scanf("%d%*c", &choix);

    while((choix < 1 && choix != -1) || choix > nbPossibilite)
    {
        printf("Choix inconnu, retapez : ");
        scanf("%d%*c", &choix);
    }

    return choix;
}



//////////////////////////////////////////////////////////////////////////////////////////////////
//------------------------8-FONCTION DE RECHERCHE diverses-----------------------//
/////////////////////////////////////////////////////////////////////////////////////////////////

void rechercher(Lecteur **tab, int nb,  Ouvrage **tabOuv, int nbOuv, ListeEmprunt l)
{
    int choix, numLect, pos, trouve, i;
    char continuer ='O', nom[30], prenom[30], cote[6], ville[30], categorie[20];
    Date d;


        system("cls");
        afficherSousMenu();
        choix = choixMenu(7);

        switch (choix) {
        case -1:
        return;
        //----------------------------------Fonctions de recherche-------------------------------------//
        case 1:
            system("cls");
            printf("Entrez le numero de lecteur :\n");
            scanf("%d%*c", &numLect);
            printf("Num\t Cote\tDate Emprunt\tDate Retour\n");
            while(l != NULL)
            {
               if(numLect == l->e.numLecteur)
               {
                   trouve = 2;
                   afficherEmprunt(l->e);
               }

               if(numLect < l->e.numLecteur)
                    break;

                l = l->suiv;
            }

            if(trouve != 2)
                printf("Aucun emprunt effectuer\n\n");

            break;
        case 2:
            system("cls");
            printf("Entrez la date actuelle(jj/mm/yy) :\n");
            scanf("%d/%d/%d%*c",&d.jour, &d.mois, &d.annee);

            while(l != NULL)
            {
                if(comparerDate( l->e.dateRetour, d) < 0 )
                {
                    pos = rechercheDicoOuvrage(tabOuv, l->e.cote, nbOuv, &trouve);
                    afficherOuvrage(*tabOuv[pos]);
                }
                l = l->suiv;
            }

            break;
        case 3:
            system("cls");
            printf("Rentrez la ville :\n");
            fgets(ville, 28, stdin);
            ville[strlen(ville) - 1] = '\0';

            for(i = 0; i<nb; i++)
                if(strcmp(tab[i]->ville, ville) == 0)
                    afficherLecteur(*tab[i]);

            break;
        case 4:
            system("cls");
            printf("Rentrez la categorie rechercher parmis les suivantes (BD, Fantaisie, SF, Policier, Revue, Magazine, Manga) :\n");
            scanf("%s%*c", categorie);

            for(i = 0; i<nbOuv; i++)
                if(strcmp(categorie, tabOuv[i]->categorie) == 0)
                    afficherOuvrage(*tabOuv[i]);

            break;
        //-----------------------------------Fonctions d'affichage-------------------------------------//
        case 5:
            system("cls");
            printf("Entrez le numero du lecteur a afficher :\n");
            scanf("%d%*c", &numLect);

            printf("Entrez son nom :\n");
            fgets(nom, 28, stdin);
            nom[strlen(nom) - 1] = '\0';

            printf("Entrez son prenom :\n");
            fgets(prenom, 28, stdin);
            prenom[strlen(prenom) - 1] = '\0';

            pos = rechercheDicoLecteur(tab, numLect, nom, prenom, nb, &trouve);
            if(trouve == 1)
                afficherCarteLecteur(*tab[pos]);
            else
                printf("Lecteur introuvable\n");

            break;
        case 6:
            system("cls");
            printf("Entrez la cote de l'ouvrage a afficher :\n");
            scanf("%s%*c", cote);

            pos = rechercheDicoOuvrage(tabOuv, cote, nbOuv, &trouve);
            if(trouve == 1)
                afficherCarteOuvrage(*tabOuv[pos]);
            else
                printf("Ouvrage introuvable\n");

            break;
        case 7:
                system("cls");
                printf("Entrez la cote du livre emprunte :\n");
                scanf("%s%*c", cote);

                while(l !=NULL)
                {
                    if(strcmp(cote, l->e.cote) == 0)
                    {
                        printf("Num\t Cote\tDate Emprunt\tDate Retour\n");
                        afficherEmprunt(l->e);
                        return;
                    }

                    l = l->suiv;
                }
            printf("Emprunt introuvable\n");
            break;

        }




}




//////////////////////////////////////////////////////////////////////////////////////////////
//---------------------------------------------9-Global----------------------------------//
/////////////////////////////////////////////////////////////////////////////////////////////



void global(void)
{
    //variables Lecteur
	Lecteur **tab, l;
	int nb, tmax, pos, trouve, choix, numLect, codeRetour, max;
	char continuer = 'O', nom[30], prenom[30];
	//variables Ouvrage
    Ouvrage **tabOuv, o;
    int nbOuv;
    char cote[6];
    //variables Emprunt
    ListeEmprunt le;
    Emprunt e;
    Date date;

    le = listeVide();
    le = chargementListeEmprunt("Emprunt");

	tabOuv = chargementTableauOuvrage("Ouvrage", &nbOuv);
	triEchangeOuvrage(tabOuv, nbOuv);

	tab = chargementLecteur("Lecteur", &nb, &tmax);
	triDicoLecteur(tab, nb);

    max = nb + 1;

    while(continuer == 'O')
    {
        system("cls");
        afficherMenu();
        choix = choixMenu(14);

        switch (choix) {
        //-----------------------------------------Fonctionnalité des Lecteurs------------------------------------------//
        case 1://Affichage tableau Lecteur
            afficherTableauLecteur(tab, nb);
            break;
        case 2: //Insertion d'un lecteur
            system("cls");

            l = creerLecteur(max);
            afficherCarteLecteur(l);

            printf("inserer le lecteur ? (Oui: 1 - Non: 2) : ");
            scanf("%d%*c", &choix);
            system("cls");

            if(choix == 1)
            {
                max = max + 1;
                insertionLecteur(l, tab, &nb, &tmax);
                afficherTableauLecteur(tab, nb);
            } else {
                printf("Insertion annulee \n\n");
            }

            break;
        case 3://Suppression d'un lecteur
            system("cls");
            //Saisie du lecteur à supprimer
            printf("Entrez le numero du lecteur a supprimer:\n");
            scanf("%d%*c", &numLect);

            printf("Entrez son nom :\n");
            fgets(nom, 28, stdin);
            nom[strlen(nom) - 1] = '\0';

            printf("Entrez son prenom :\n");
            fgets(prenom, 28, stdin);
            prenom[strlen(prenom) - 1] = '\0';
            supprimerLecteur(tab, numLect, nom, prenom, &nb);
            break;

        case 4:
            system("cls");
            printf("Entrer le numero de lecteur du lecteur a modifier :\n");
            scanf("%d%*c", &numLect);

            printf("Entrez son nom :\n");
            fgets(nom, 28, stdin);
            nom[strlen(nom) - 1] = '\0';

            printf("Entrez son prenom :\n");
            fgets(prenom, 28, stdin);
            prenom[strlen(prenom) - 1] = '\0';

            system("cls");
            modifierLecteur(tab, numLect, nom, prenom, nb);
            afficherTableauLecteur(tab, nb);
                break;

        //---------------------------------------Fonctionnalités des Ouvrages---------------------------------------//
        case 5:
            afficherTableauOuvrage(tabOuv, nbOuv);
            break;
        case 6:
            system("cls");
            o = creerOuvrage(tabOuv, nbOuv);
            afficherCarteOuvrage(o);
            printf("inserer l'ouvrage ? (Oui: 1 - Non: 2) : ");
            scanf("%d%*c", &choix);
            system("cls");

            if(choix == 1)
            {
                insertionOuvrage(o, tabOuv, &nbOuv);
                afficherTableauOuvrage(tabOuv, nbOuv);
            } else {
                printf("Insertion annulee \n\n");
            }
            break;
        case 7:
            system("cls");
            printf("Entrez la cote de l'ouvrage a supprimer :\n");
            scanf("%s%*c", cote);
            supprimerOuvrage(tabOuv, cote, &nbOuv);
            afficherTableauOuvrage(tabOuv, nbOuv);
            break;
        case 8:
            system("cls");
            printf("Entrez la cote de l'ouvrage a modifier :\n");
            scanf("%s%*c", cote);
            modifierOuvrage(tabOuv, cote, nbOuv);
            afficherTableauOuvrage(tabOuv, nbOuv);
            break;
        //---------------------------------------Fonctionnalités des Emprunts---------------------------------------//
        case 9:
            system("cls");
            afficherListeEmprunt(le);
            break;
        case 10:
            system("cls");
            e = creerEmprunt(tab, nb, tabOuv, nbOuv, &codeRetour);
            if(codeRetour == -1) //Impossible de la creer car ouvrage deja emprunte, ou probleme le lecteur
                break;
            inserer(le, e);
            afficherListeEmprunt(le);
            break;
        case 11:
            system("cls");
            printf("Entrez le numero de l'emprunteur :\n");
            scanf("%d%*c", &numLect);

            printf("Entrez son nom :\n");
            fgets(nom, 28, stdin);
            nom[strlen(nom) - 1] = '\0';

            printf("Entrez son prenom :\n");
            fgets(prenom, 28, stdin);
            prenom[strlen(prenom) - 1] = '\0';

            printf("Entrez la cote de l'ouvrage :\n");
            scanf("%s%*c", cote);

            e.numLecteur = numLect;
            strcpy(e.cote, cote);

            le = supprimer(le, e, &codeRetour);
            if(codeRetour == 1 || codeRetour == 2)
            {
                pos = rechercheDicoLecteur(tab, numLect, nom,prenom, nb, &trouve);
                tab[pos]->nbEmprunt --;
                if(codeRetour == 2)
                {
                     tab[pos]->nbRetard ++;// le livre a été rendu en retard
                     printf("Le livre a été rendu en retard\n\n");
                     if(tab[pos]->nbRetard >= 10) // Le lecteur a atteind le nombre de retard passible d'une amende
                     {
                         afficherCarteLecteur(*tab[pos]);
                         printf("%s %s doit payer une amende de 5€ pour ses 10 retards\n\n", tab[pos]->prenom, tab[pos]->nom);
                         tab[pos]->nbRetard = 0;
                     }
                }

                pos = rechercheDicoOuvrage(tabOuv, cote, nbOuv, &trouve);
                tabOuv[pos]->emprunte = false;

                printf("Suppression effectuee\n\n");
                afficherListeEmprunt(le);
            }
            break;
        case 12:
            system("cls");
            printf("Pour modifier un emprunt, entrez le numero de l'emprunteur :\n");
            scanf("%d%*c", &numLect);

            printf("Entrez son nom :\n");
            fgets(nom, 28, stdin);
            nom[strlen(nom) - 1] = '\0';

            printf("Entrez son prenom :\n");
            fgets(prenom, 28, stdin);
            prenom[strlen(prenom) - 1] = '\0';

            printf("Entrez la cote de l'ouvrage :\n");
            scanf("%s%*c", cote);

            e.numLecteur = numLect;
            strcpy(e.cote, cote);

            le = modifierEmprunt(le, e);
            afficherListeEmprunt(le);

            break;
        case 13:
            system("cls");
            rechercher(tab, nb, tabOuv, nbOuv, le);
            break;
        case 14: //sauvegarde d'un tableau
            sauvegarder("Lecteur", tab, nb, "Ouvrage", tabOuv, nbOuv, "Emprunt", le);
            printf("Tableaux sauvegardes\n");
            exit(0);
        case -1:

            break;
        default:
            printf("indisponible\n");
        }

        printf("Souhaitez-vous continuer ? (O:N) : ");
        scanf("%c%*c", &continuer);
    }

        sauvegarder("Lecteur", tab, nb, "Ouvrage", tabOuv, nbOuv, "Emprunt", le);
        exit(0);

}




