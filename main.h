#include <iostream>
#include <string>
#include <windows.h>
#include <cstdlib>
#include <time.h>
#include <fstream>
//Tout les includes

using namespace std;
//Utile pour �viter de se casser la t�te avec des erreurs de compilation inhabituelles

#define MAJOR_VERSION 2             //Pouh... Enfin la version 2... Que de chemin...
#define MINOR_VERSION 1            //Avant de changer de version, changer aussi le titre dans afficherInfos()!
#define COMP_DAY 24               //Jour de la compilation
#define COMP_MONTH 11            //Mois de la compilation
#define COMP_YEAR 2013          //Ann�e de la compilation
#define MAX 100                //Maximum pour nombreAleatoire()
#define MIN 1                 //Minimum pour nombreAleatoire()
                             //Tout les define n�c�ssaire pour afficherInfos() et ecrireFichier(int)

void afficherInfos(char* chemin);
int afficherMenu();
int nombreAleatoire(int, int);
int comparerNombre(int, int);
int ecrireFichier(int, int, int);
int lireFichier();
int menuNbJoueur();
void demanderNom();
int demanderNbCoups();
int demanderNiveau();
int afficherFin();
void choisirCouleur();
//Prototypes des fonctions

string nomJoueur1, nomJoueur2;
int nbCoupsChoisi, nbJoueurs, limiteMax;
//Variables globales avec un nom assez explicite
