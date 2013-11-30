/*
TODO List:
-Re-optimisation
*/

#include "main.h"

int main(int argc, char **argv)
{
    system("cls");                //Histoire que rien ne g�ne si le jeu est lanc� depuis la commande
    nomJoueur1 = "";             //Variable globale pour le nom du premier joueur
    nomJoueur2 = "";            //Variable globale pour le nom du second joueur
    nbCoupsChoisi= 0;          //Variable globale pour le nombre de coups
    limiteMax = 0;            //Variable globale pour le niveau de difficult�
    nbJoueurs = 0;           //Variable globale pour le nombre de joueur
    afficherInfos(argv[0]); //Affichage des infos de versions
    bool continuer = true;
    int continuerMenuFin = 0;

    do
    {
        system("cls");
        afficherMenu();
        system("pause");
        system("cls");

        do
        {
            continuerMenuFin = afficherFin();

            if(continuerMenuFin == 2)
            {
                continuer = false;
            }
              //Si l'utilisateur demande � quitter, afficherFin() retourne 2, et on arr�te la boucle
             //Ca �vite que, si l'utilisateur veut lire le fichier de score, donc que afficherFin()
            //retourne 3 on arr�te la boucle
        }while(continuerMenuFin == 3);

    }while(continuer);

    /*
    Puisque la boucle s'est arr�t�, l'utilisateur a fini.
    On quitte donc le programme
    */
    return 0;
}
//Fonction main(), plut�t ais� � comprendre

void afficherInfos(char* chemin = "Chemin Inconnu")
{
    system("Title Plus ou Moins 2 v2.1"); //Changement du titre
    system("color 0a");                  //Changement de la couleur
    demanderNom();     //On demande le nom � l'utilisateur
    choisirCouleur(); //On lui demande de choisir la couleur
    system("cls");
    cout << "Projet developpe par: Nicolas Fonnier" << endl;
    cout << "Chemin: " << chemin << endl;
    cout << "Numero de version: " << MAJOR_VERSION << "." << MINOR_VERSION << endl;
    cout << "Date de compilation: " << COMP_DAY << "\\" << COMP_MONTH << "\\" << COMP_YEAR << endl;
    system("pause"); //Pour s'assurer que les infos ont bien �t� vues
    system("cls"); //On efface l'�cran pour que ce soit plus lisible

}
//Affiche les informations du projet

int afficherMenu()
{
    int score = 0;
    cout << "Bonjour et bienvenue dans Plus ou Moins dans sa 2eme version en C++!" << endl;
    cout << "Le but est toujours le meme, trouvez le nombre!" << endl;
    cout << "Bonne chance!" << endl;
    //Explication des r�gles

    system("pause"); //Pour s'assurer que l'utilisateur lise bien les r�gles

    cout << endl << endl;

    int nbCoupsMax = demanderNbCoups();
    //C'est assez clair l� non?

    int nombreCherche = menuNbJoueur();
    if(nomJoueur1 == "Nicolas Fonnier" || nomJoueur2 == "Nicolas Fonnier")
    {
        cout << "Hep, vous voulez de l'aide, maitre?" << endl;
        cout << "Voila le nombre : " << nombreCherche << endl;
    }
    //Petit cheat code, pour le fun :)

    int nombreEntre = 0;
    while(nombreEntre != nombreCherche && score < nbCoupsMax)
    {
        cout << "Entrez un nombre pour voir:" << endl;
        cin >> nombreEntre;

        switch (comparerNombre(nombreCherche, nombreEntre)) //On utilise la fonction pour comparer les nombres
        {
            case -1:
                cout << "Ooops! Y a eu une erreur!" << endl;
            break;
            //Freaking useless

            case 0:
                score ++;
                cout << "Bien joue, vous avez gagne en " << score << " coups!" << endl << endl;
                ecrireFichier(score, nombreCherche, limiteMax); //L'utlisateur a fini, on �crit les donn�es

            break;

            case 1:
                score++;
                if((nbCoupsMax - score) == 0)
                {
                    cout << endl;
                    cout << "Vous avez perdu... Dommage!" << endl;
                    cout << "Le chiffre etait: " << nombreCherche << endl << endl;
                }
                else
                {
                    cout << "C'est plus!" << endl;
                    cout << "Il vous reste : " << nbCoupsMax - score << " coups" << endl << endl;
                }

            break;

            case 2:
                score++;
                if((nbCoupsMax - score) == 0)
                //Le fait de mettre "nbCoupsMax - score" permet d'�viter de d�clarer un int coupsRestant qui serait �gal � coupsMax et qui serait d�cr�ment�
                {
                    cout << endl;
                    cout << "Vous avez perdu... Dommage!" << endl;
                    cout << "Le chiffre etait: " << nombreCherche << endl << endl;
                }
                else
                {
                    cout << "C'est moins!" << endl;
                    cout << "Il vous reste : " << nbCoupsMax - score << " coups" << endl << endl;
                    //M�me chose, c'est mieux que de d�clarer un int
                }

            break;
        }

        nombreEntre = 0;
    }

    return 1;
    //Boucle principale, pas besoin d'explication
}
//Fonction de jeu principale, fonctionnement simple.

int nombreAleatoire(int max, int min)
{
    srand(time(NULL));
    int nombreRenvoye = (rand() % (max - min + 1)) + min;

    return nombreRenvoye;
}
//Ma petite fonction pour les nombres al�atoires

int comparerNombre(int i, int m)
{
    if(i == m)
    {
        return 0;
    }

    else if(i > m)
    {
        return 1;
    }

    else if(i < m)
    {
        return 2;
    }

    else
    {
        return -1;
    }

}
//Fonction simple, pas besoin d'explication

int ecrireFichier(int score, int nombreCherche, int limiteRand)
{
    ofstream fichierScore("Score.txt", ios::out | ios::app);

    if(fichierScore)
    {
        fichierScore << "Cr�� par:  Nicolas Fonnier" << endl;
        fichierScore << "Numero de version:" << MAJOR_VERSION << "." << MINOR_VERSION << endl;
        fichierScore << "Date de compilation: " << COMP_DAY << "\\" << COMP_MONTH << "\\" << COMP_YEAR << endl;
        fichierScore << "Nom: " << nomJoueur1 << endl;
        if(nbJoueurs == 2)
        {
            fichierScore << "2�me joueur: " << nomJoueur2 << endl;
        }
        fichierScore << "Score: " << score << endl;
        fichierScore << "Niveau: " << nbCoupsChoisi << endl;
        fichierScore << "Le nombre �tait: " << nombreCherche << endl;
        fichierScore << "Les limites �tait: 1, " << limiteRand << endl << endl << endl;
        //On �crit les infos de version, le score, le nom et le niveau de difficult�
        fichierScore.close(); //Et on ferme le fichier
        return 1;
    }

    else
    {
        cout << "Un probl�me est survenu durant l'ouverture" << endl;
        return -1;
    }
}

int lireFichier()
{
    ifstream fichierScore("Score.txt", ios::in);

    if(fichierScore)
    {
        int compteurLignes = 0;

        string lignes = "";
        while(getline(fichierScore, lignes))
        {
            compteurLignes ++;
            cout << lignes << endl;

            if(compteurLignes%24 == 0)
            {
                system("pause");
                compteurLignes = 0;
                system("cls");
            }
        }

        fichierScore.close();
    }

    else
    {
        return 0;
    }

    system("pause");
    system("cls");
    return 1;
}

int menuNbJoueur()
{
    system("cls");
    bool choixNbJoueur = false; //Bool�en pour la boucle principale
    int nombreCherche = 0;
    //Initialisation des 2 int

    do
    {
        cout << "Veuillez selectionner le nombre de joueur." << endl;
        cout << "1.Solo" << endl << "2.2 joueurs" << endl;
        cin >> nbJoueurs;
        if(nbJoueurs == 1)
        {
            limiteMax = demanderNiveau();
            cout << "Mode solo actif! Nombre aleatoire genere!" << endl;
            nombreCherche = nombreAleatoire(limiteMax, MIN); //G�n�ration du nombre
            system("cls"); //On pr�pare l'�cran pour le jeu
            choixNbJoueur = true; //Et on arr�te la boucle
        }

        else if(nbJoueurs == 2)
        {
            cout << "Mode multi active!" << endl;
            cout << "Entrez le nom du 2eme joueur:" << endl;
            cin.ignore(); //Vidage du buffer
            getline(cin, nomJoueur2);
            cout << "Entrez un nombre!" << endl;
            cin >> nombreCherche; //L'utilisateur 2 rentre un nombre
            system("cls"); //On pr�pare l'�cran
            choixNbJoueur = true;
        }

        else
        {
            choixNbJoueur = false;
        }
    }while(choixNbJoueur == false);

    return nombreCherche; //Et on revoie le nombre � chercher
}

void demanderNom()
{
    cout << "Entrez votre nom:" << endl;
    getline(cin, nomJoueur1);

    if(nomJoueur1 == "Nicolas Fonnier")
    {
        cout << "Welcome, master of C++! Have fun!" << endl;
        system("pause");
    }
    //Pas vraiment un cheat code, mais c'est toujours marrant � faire :)
    system("cls");
}
//Y a s�rieusement besoin d'explication ?

int demanderNbCoups()
{
    system("cls"); //On vide l'�cran
    cout << "Choisissez le nombre de coups:" << endl;
    cout << "1. 1000 essais" << endl;
    cout << "2. 10 essais" << endl;
    cout << "3. 5 essais" << endl;
    cout << "4. HARD-CORE! (1 essai)" << endl;
    //Pr�sentation des niveaux de difficult�
    cin >> nbCoupsChoisi;

    switch (nbCoupsChoisi)
    {
        case 1:
            cout << endl << endl;
            return 1000;
        break;

        case 2:
            cout << endl << endl;
            return 10;
        break;

        case 3:
            cout << endl << endl;
            return 5;
        break;

        case 4:
            cout << endl << endl;
            return 1;
        break;

        default:
            cout << endl << endl;
            return 1;
        break;
    }
    //S�rieusement, faut que j'explique?
}
//Reglage du nombre de coups. Le nombre max de coup (nbCoupsMax) est d�fini par le return

int demanderNiveau()
{
    int nvDiffChoisi = 0;
    system("cls"); //On vide l'�cran
    cout << "Choisissez les limites!" << endl;
    cout << "1.Easy: de 1 a 50" << endl;
    cout << "2.Normal: de 1 a 100" << endl;
    cout << "3.Hard: de 1 a 200" << endl;
    cout << "4.Master Mode: de 1 a 1000" << endl;
    cin.ignore();
    cin >> nvDiffChoisi;

    switch(nvDiffChoisi)
    {
        case 1:
            return 50;
        break;

        case 2:
            return MAX;
        break;

        case 3:
            return 200;
        break;

        case 4:
            return 1000;
        break;

        default:
            return MAX;
        break;
    }
    //La limite est d�finie par le return

}

int afficherFin()
{
    int choixContinue = 0;
    cout << "Voulez-vous recommencer?" << endl;
    cout << "1.Recommencer" << endl;
    cout << "2.Arreter" << endl;
    cout << "3.Lire le fichier de score" << endl;
    cin >> choixContinue;

    if (choixContinue == 3)
    {
        system("cls");
        lireFichier();
    }

    return choixContinue;
}

void choisirCouleur()
{
    system("color 0A"); //Couleur verte sur fond noir, pour d�buter
    int choixCouleur = 0;

    cout << "Choisissez votre couleur:" << endl;
    cout << "1.Texte vert sur fond noir (actuel)" << endl;
    cout << "2.Texte rouge sur fond blanc" << endl;
    cout << "3.Texte bleu sur fond rouge" << endl;

    cin >> choixCouleur;

    switch(choixCouleur)
    {
        case 1:
            system("color 0A");
        break;

        case 2:
            system("color fc");
        break;

        case 3:
            system("color c1");
        break;

        default:
            system("color 0a");
        break;
    }

    cin.clear();
}
