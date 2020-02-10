//
//  projet.h
//  Projet Gestion d'une bibliothèque
//
//  Created by Clement TORTI & Florent BECOUZE on 20/12/2017.
//  Copyright © 2017 Clement Torti. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>


//----------------------------Définition des structures----------------------------------//

typedef enum {false, true} Bool;
//----
typedef struct {

    int numLecteur; // Clef

    char nom[30];   //
    char prenom[30];// informations lecteur
    char ville[50]; //
    char numTel[16];//

    int nbRetard;   // informations complémentaires
    int nbEmprunt;  //

} Lecteur;
//----
typedef struct {

    char cote[6]; // Clef

    char nomOuvrage[30];//
    char categorie[30]; // informations ouvrage
    char auteur[30];    //

    Bool emprunte;      // informations complémentaire

} Ouvrage;
//----
typedef struct {
    int jour;
    int mois;
    int annee;
} Date;
//----
typedef struct Emprunt {

    int numLecteur; // Clef composée
    char cote[6];   //

    Date dateEmprunt;// informations complémentaires
    Date dateRetour;//

} Emprunt;
//----
typedef struct maillon
{
    Emprunt e;
    struct maillon *suiv;

} Maillon, *ListeEmprunt;



//--------------------------------------FONCTIONS----------------------------------------//
//Lecture de structure
Lecteur lireLecteur(FILE *flot);
Ouvrage lireOuvrage(FILE *flot);

//Affichage structure
void reduireLongueur(char *nom, char *nouvNom,  int taille);
void ajouterBlanc(char *nom, int taille);
void afficherLecteur(Lecteur l);
void afficherCarteLecteur(Lecteur l);
void afficherOuvrage(Ouvrage o);
void afficherEmprunt(Emprunt e);

//Affichage tableau de pointeur vers des structures
void afficherTableauLecteur(Lecteur **tab, int nb);
void afficherTableauOuvrage(Ouvrage **tab, int nb);

//chargement dans tableau / une liste
Lecteur **chargementLecteur(char *nomFichier , int *taille, int *tmax);
Ouvrage **chargementTableauOuvrage(char *nomFichier, int *tmax);
ListeEmprunt chargementListeEmprunt(char *nomFichier);
ListeEmprunt chargementListeEmprunt2(char *nomFichier);//-------------------->>>>>>>>>>>>>>>>>>>>A SUPPRIMER

//insertion d'un élément dans le tableau
//tri par fusion
void copierLecteur(Lecteur **R, int i, int j, Lecteur **tab);
void fusionLecteur(Lecteur **R, int n, Lecteur **S, int m, Lecteur **tab);
void triDicoLecteur(Lecteur **tab, int nb);
//tri par échange
void echangerOuvrage(Ouvrage **tab, int i, int j);
void triEchangeOuvrage(Ouvrage **tab, int nb);
//recherche dichotomique
int rechercheDicoLecteur(Lecteur **tab, int numLect, char *nom, char *prenom, int nb, int *trouve);  //recherche basée sur le nom,prenom et num
int rechercheDicoOuvrage(Ouvrage **tab, char *cote, int nb, int *trouve); //recherche basée sur la cote
//Création du lecteur à afficher
Bool verificationNumTel(char *numTel);
Lecteur creerLecteur(int numLect);
Ouvrage creerOuvrage(Ouvrage **tab, int nb);
//insertion
void decalageADroiteLecteur(Lecteur **tab, int pos, int nb);
void decalageADroiteOuvrage(Ouvrage **tab, int pos, int nb);
void insertionLecteur(Lecteur l, Lecteur **tab, int *nb, int *tmax);
void insertionOuvrage(Ouvrage o, Ouvrage **tab, int *nb);

//Suppression d'un élément dans le tableau
void decalageAGaucheLecteur(Lecteur **tab, int pos, int nb);
void supprimerLecteur(Lecteur **tab, int numLect, char *nom, char *prenom,  int *nb);
void supprimerOuvrage(Ouvrage **tab, char *cote, int *nb);

//Modification d'un lecteur
void modifierLecteur(Lecteur **tab, int numLect, char *nom, char *prenom, int nb);


//Sauvegarde des tableaux
void sauvegarderTableauLecteur(char *nomFichier, Lecteur **tab, int nb);
void sauvegarderTableauOuvrage(char *nomFichier, Ouvrage **tab, int nb);
void sauvegarderListeEmprunt(char *nomFichier, ListeEmprunt l);
void sauvegarder(char *nomFichierLecteur, Lecteur **tabLect, int nbLect, char *nomFichierOuvrage, Ouvrage **tabOuv, int nbOuv, char *nomFichierEmprunt, ListeEmprunt l);

//Fonction Liste Emprunt
int comparerDate(Date d1, Date d2);
int comparerEmprunt(Emprunt e1, Emprunt e2);
ListeEmprunt listeVide();

ListeEmprunt insererEnTete(ListeEmprunt l , Emprunt e);
ListeEmprunt inserer(ListeEmprunt l, Emprunt e);

ListeEmprunt supprimerEnTete(ListeEmprunt l);
ListeEmprunt supprimer(ListeEmprunt l, Emprunt e, int *codeRetour);

ListeEmprunt modifierEmprunt(ListeEmprunt l, Emprunt e);
void sauvegarderListeEmprunt(char *nomFichier, ListeEmprunt l);

//Menus de sélection
void afficherMenu();
int choixMenu();

//Test
void global(void);






