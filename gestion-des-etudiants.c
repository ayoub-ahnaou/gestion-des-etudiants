#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define COLOR_RED     "\x1b[31m"
#define COLOR_GREEN   "\x1b[32m"
#define COLOR_YELLOW  "\x1b[33m"
#define COLOR_BLUE    "\x1b[34m"
#define COLOR_VIOLET  "\x1b[35m"
#define COLOR_RESET   "\x1b[0m"

// structure de date (annee, mois, jour)
typedef struct {
    int annee;
    int mois;
    int jour;
} Date;
// structure de Etudiant (identifiant unique, nom, prenom, date de naissance, departement)
typedef struct {
    int uid;
    char nom[25], prenom[25];
    char departement[30];
    float noteGeneral;
    Date date_naiss;
} Etudiant;

Etudiant etudiants[99];
int taille = 0;
static int id_increment = 1;

//TODO ==> prototype des fonctions
// fonction de meu principal
void menu();
// fonction d'ajouter un ou plusieurs etudiant
void ajouterEtudiant();
// modifier ou supprimer un etudiant
void modifierOuSupprimer();
// modifier un etudiant par UID
void modifierEtudiant();
// supprimer un etudiant par UID, avec une confirmation
void supprimerEtudiant();
// afficher les details d'un etudiant, y compris la note generale
void afficherInfosEtudiants();
// calculer et afficher la moyenne generale de chaque departement, ainsi de l'universite entière
void moyenneGeneral();
// afficher:
// le nombre total d'etudiants inscrits
// nombre d'etudiant dans chaque departement
// les etudiants ayant une moyenne generale superieure a un certain seuil
// les trois etudiant ayant la premiere note
// nombre d'etudiant ayant reussi dans chaque departement (note >= 10/20)
void statistiques();
// rechercher un etudiant par son nom
// recherche par departement (etudiant inscris dans un departement specifique)
void rechercherEtudiant();
// tri alphabetique des etudiants (de A à Z ou de Z à A) 
// tri les etudiant par la moyenne generale (asc et desc)
// tri les etudiant avec leur statu de reussite (moyenne superieure ou egale 10/20) 
void triEtudiants();

// prototype des fonctions auxiliere (helpers functions)
void insertDepartement(int indice);
int rechercherParUID(int uid, int low, int high);
void modifierNomEtPrenom(int position);
void modifierDepartement(int position);
void modifierNote(int position);
void modifierDateNaiss(int position);
// ... //

int main(){
    menu();

    printf("\n");
    return 0;
}

void menu(){
    int choice;
    do{
        printf(COLOR_YELLOW "--------------------------------------------------------------\n");
        printf("                      menu principale                         \n");
        printf("--------------------------------------------------------------\n\n");
        printf("\t 1- ajouter un etudiant \n");
        printf("\t 2- modifier ou supprimer un etudiant \n");
        printf("\t 3- rechercher un etudiant \n");
        printf("\t 4- afficher les informations des etudiants \n");
        printf("\t 5- statistiques \n");
        printf("\t 6- quittez le programe \n\n");
        printf("--------------------------------------------------------------\n" COLOR_RESET);
        printf("entrez votre choix: "); scanf("%d", &choice);

        switch(choice){
            case 1: ajouterEtudiant(); break;
            case 2: modifierOuSupprimer(); break;
            case 3: break;
            case 4: break;
            case 5: break;
            case 6: exit(0); break;
            default: break;
        }
    }
    while(choice != 6);
}

void ajouterEtudiant(){
    system("cls");
    printf(COLOR_YELLOW "--------------------------------------------------------------\n");
    printf("                    ajouter un etudiant                       \n");
    printf("--------------------------------------------------------------\n" COLOR_RESET);
    int nbre_etudiants;
    printf("combien des etudiants voulez-vous ajoutes ? ");
    scanf("%d", &nbre_etudiants);
    for(int i=0; i<nbre_etudiants; i++){
        etudiants[taille + i].uid = id_increment++;
        printf("-------------------------------------------------------------\n" COLOR_RESET);
        printf("entrer votre nom: "); scanf(" %[^\n]s", etudiants[taille + i].nom);
        printf("entrer votre prenom: "); scanf(" %[^\n]s", etudiants[taille + i].prenom);
        printf("entrer votre date de naisance (JJ/MM/AAAA): "); 
        scanf("%d/%d/%d", &etudiants[taille + i].date_naiss.jour, &etudiants[taille + i].date_naiss.mois, &etudiants[taille + i].date_naiss.annee);
        insertDepartement(i);
        printf("entrer votre notes: "); scanf("%f", &etudiants[taille + i].noteGeneral);
        printf("--------------------------------------------------------------\n");
        printf(COLOR_GREEN "un nouveau etudiant a ete ajoutee sous l'identifiant %d avec success \n" COLOR_RESET, etudiants[taille + i].uid);
    }
    taille = taille + nbre_etudiants;
}
void modifierEtudiant(){
    system("cls");
    printf(COLOR_YELLOW "--------------------------------------------------------------\n");
    printf("                    modifier un etudiant                      \n");
    printf("--------------------------------------------------------------\n" COLOR_RESET);
    if(taille == 0){
        printf(COLOR_RED "aucun etudiant availaible maintenant\n" COLOR_RESET);
        return;
    }
    else{
        int uid;
        printf("entrer l'identifiant de l'etudiant a modifier: "); scanf("%d", &uid);
        int position = rechercherParUID(uid, 0, taille);
        if(position == -1){
            printf(COLOR_RED "etudiant n'existe pas\n" COLOR_RESET);
            return;
        }
        int modification_choix;
        do{
            printf("--------------------------------------------------------------\n");
            printf("1- modifier le nom et prenom\n");
            printf("2- modifier le departement\n");
            printf("3- modifier la note generale\n");
            printf("4- modifier la date de naissance\n");
            printf("--------------------------------------------------------------\n");
            printf("entrer votre choix: "); scanf("%d", &modification_choix);

            switch(modification_choix){
                case 1: modifierNomEtPrenom(position); return; break;
                case 2: modifierDepartement(position); return; break;
                case 3: modifierNote(position); return; break;
                case 4: modifierDateNaiss(position); return; break;
                default:
                    printf(COLOR_RED "choisit un choix valid\n" COLOR_RESET);
                    break;
            }
        }
        while(modification_choix < 1 || modification_choix > 4);
    }
}
void supprimerEtudiant(){
    system("cls");
    printf(COLOR_YELLOW "--------------------------------------------------------------\n");
    printf("                    supprimer un etudiant                      \n");
    printf("--------------------------------------------------------------\n" COLOR_RESET);
    if(taille == 0){
        printf(COLOR_RED "aucun etudiant availaible maintenant\n" COLOR_RESET);
        return;
    }
    else{
        int uid;
        printf("entrer l'identifiant de l'etudiant a supprimer: "); scanf("%d", &uid);
        int position = rechercherParUID(uid, 0, taille);
        if(position == -1){
            printf(COLOR_RED "etudiant n'existe pas\n" COLOR_RESET);
            return;
        }
        else {
            char confirmation[10];
            printf("voulez-vous supprimer ce etudiant (oui/non)? "); scanf(" %[^\n]s", confirmation);
            if(strcmp(confirmation, "oui") == 0){
                for(int i=position; i<taille; i++){
                    etudiants[i] = etudiants[i + 1];
                }
                printf(COLOR_GREEN "un etudiant a ete supprimee\n" COLOR_RESET);
                taille = taille - 1;
            }
            else{
                printf(COLOR_GREEN "operation de suppression annule\n" COLOR_RESET);
                return;
            }
        }        
    }
}
void afficherInfosEtudiants(){}
void moyenneGeneral(){}
void statistiques(){}
void rechercherEtudiant(){}
void triEtudiants(){}

void insertDepartement(int indice){
    printf("--------------------------------------------------------------\n");
    printf("1- Informatique\n");
    printf("2- physique\n");
    printf("3- economique\n");
    printf("4- biologie\n");
    printf("5- droit\n");
    printf("--------------------------------------------------------------\n");
    int departement_choisi;
    
    do{
        printf("selectioner votre departement: "); scanf("%d", &departement_choisi);
        switch(departement_choisi){
            case 1: 
                strcpy(etudiants[taille + indice].departement, "informatique");
                printf("--------------------------------------------------------------\n");
                break;
            case 2: 
                strcpy(etudiants[taille + indice].departement, "physique");
                printf("--------------------------------------------------------------\n");
                break;
            case 3: 
                strcpy(etudiants[taille + indice].departement, "economique");
                printf("--------------------------------------------------------------\n");
                break;
            case 4: 
                strcpy(etudiants[taille + indice].departement, "biologie");
                printf("--------------------------------------------------------------\n");
                break;
            case 5: 
                strcpy(etudiants[taille + indice].departement, "droit");
                printf("--------------------------------------------------------------\n");
                break;
            default: 
                printf(COLOR_RED "choisit une filiere valide\n" COLOR_RESET);
                break;
        }
    }
    while(departement_choisi < 1 || departement_choisi > 5);
}
void modifierOuSupprimer(){
    system("cls");
    printf(COLOR_YELLOW "--------------------------------------------------------------\n");
    printf("             supprimer ou modifier un etudiant                \n");
    printf("--------------------------------------------------------------\n");
    int del_or_upd;
    do{
        printf(COLOR_YELLOW "--------------------------------------------------------------\n");
        printf("1- modifier un etudiant\n");
        printf("2- supprimer un etudiant\n");
        printf("3- retour au menu principale\n");
        printf("--------------------------------------------------------------\n" COLOR_RESET);
        printf("entrer votre choix: "); scanf("%d", &del_or_upd);

        switch(del_or_upd){
            case 1: modifierEtudiant(); break;
            case 2: supprimerEtudiant(); break;
            case 3: return; break;
            default: 
                printf(COLOR_RED "choisit un choix valid (1 ou 2) \n" COLOR_RESET);
                break;
        }
    }
    while(del_or_upd <= 1 || del_or_upd >= 2);
}
int rechercherParUID(int uid, int low, int high){
    if(low > high){
        return -1;
    }
    int position_mid = (low + high) / 2;
    if(etudiants[position_mid].uid == uid){
        return position_mid;
    }
    else if(etudiants[position_mid].uid < uid){
        rechercherParUID(uid, position_mid + 1, high);
    }
    else{
        rechercherParUID(uid, low, position_mid - 1);
    }
}
void modifierNomEtPrenom(int position){
    printf("entrer votre nouveau nom: "); scanf(" %[^\n]s", etudiants[position].nom);
    printf("entrer votre nouveau prenom: "); scanf(" %[^\n]s", etudiants[position].prenom);

    printf(COLOR_GREEN "votre informations a ete change\n" COLOR_RESET);
}
void modifierDepartement(int position){
    insertDepartement(position);
}
void modifierNote(int position){
    printf("entrer votre nouvelle note: ");
    scanf("%f", &etudiants[position].noteGeneral);

    printf(COLOR_GREEN "votre informations a ete change\n" COLOR_RESET);
}
void modifierDateNaiss(int position){
    printf("entrer votre date de naisance (JJ/MM/AAAA): "); 
    scanf("%d/%d/%d", &etudiants[position].date_naiss.jour, &etudiants[position].date_naiss.mois, &etudiants[position].date_naiss.annee);

    printf(COLOR_GREEN "votre informations a ete change\n" COLOR_RESET);
}