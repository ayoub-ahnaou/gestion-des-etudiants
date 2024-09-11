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

Etudiant etudiants[99] = {
    {1, "dupont", "marie", "Mathematiques", 12, {10, 6, 1998}},
    {2, "martin", "jean", "Informatique", 10, {23, 11, 1999}},
    {3, "durand", "sophie", "Physique", 8, {5, 2, 2000}},
    {4, "lemoine", "paul", "Chimie", 9.2, {15, 8, 1997}},
    {5, "fikrri", "hanane", "Chimie", 9.2, {15, 8, 1997}},
    {6, "ahnaou", "ayoub", "Biologie", 16.9, {30, 12, 1999}},
    {7, "mohammed", "amine", "Droit", 18.9, {3, 2, 2003}},
    {8, "zouhri", "jamal", "Economique", 3.95, {1, 8, 1994}},
    {9, "kara", "mohamed", "Chimie", 7.5, {31, 1, 2010}},
    {10, "chaaraoui", "youssef", "Informatique", 14, {6, 5, 2020}},
};

int taille = 10;
static int id_increment = 11;

// variable temporaire de type etudiant
Etudiant tmp_etudiants[99];
char * departements[20] = {"Informatique", "Physique", "Chimie", "Biologie", "Droit", "Mathematiques", "Economique"};
int nombre_departements = sizeof(nombre_departements);

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
void afficherInfosEtudiants(Etudiant tableau[], int size);
// calculer et afficher la moyenne generale de chaque departement, ainsi de l'universite entière
void moyenneGeneral();
// afficher:
void afficherListEtudiants();
// le nombre total d'etudiants inscrits
void etudiantInscris();
// nombre d'etudiant dans chaque departement
void etudiantDansChaqueDepartement();
// les etudiants ayant une moyenne generale superieure a un certain seuil
void etudiantParNoteGeneral();
// les trois etudiant ayant la premiere note
void troisPremiersEtudiant();
// nombre d'etudiant ayant reussi dans chaque departement (note >= 10/20)
void etudiantReussits();

void statistiques();
// rechercher un etudiant par son nom
void rechercherParNom();
// recherche par departement (etudiant inscris dans un departement specifique)
void rechercherParDepartement();
void rechercherEtudiant();
// sous menu des choix de tri
void menuDeTri();
// tri alphabetique des etudiants (de A a Z ou de Z a A) 
void triEtudiantParNomDesc();
void triEtudiantParNomAsc();
// tri les etudiant par la moyenne generale (asc et desc)
void triEtudiantParNoteAsc();
void triEtudiantParNoteDesc();
// tri les etudiant avec leur statu de reussite (moyenne superieure ou egale 10/20) 
void triEtudiantSelonStatusDeReussit();

void triEtudiants();

// prototype des fonctions auxiliere (helpers functions)
void choisitDepartement(int indice);
int rechercherParUID(int uid, int low, int high);
void modifierNomEtPrenom(int position);
void modifierDepartement(int position);
void modifierNote(int position);
void modifierDateNaiss(int position);
int nbreDepartements();
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
        printf("\t 6- trie les etudiants \n");
        printf("\t 7- calcul la moyenne generale \n");
        printf("\t 8- quittez le programe \n\n");
        printf("--------------------------------------------------------------\n" COLOR_RESET);
        printf("entrez votre choix: "); scanf("%d", &choice);
        printf(COLOR_YELLOW "--------------------------------------------------------------\n" COLOR_RESET);

        switch(choice){
            case 1: ajouterEtudiant(); break;
            case 2: modifierOuSupprimer(); break;
            case 3: rechercherEtudiant(); break;
            case 4: afficherListEtudiants(); break;
            case 5: statistiques(); break;
            case 6: menuDeTri(); break;
            case 7: moyenneGeneral(); break;
            case 8:
                exit(0); 
                break;
            default:
                printf(COLOR_RED "choisit un choix valide dans le menu principale\n" COLOR_RESET);
                break;
        }
    }
    while(choice != 8);
}

//  *************************** //

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
        choisitDepartement(i);
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
void afficherInfosEtudiants(Etudiant tableau[], int size){
    // printf(COLOR_GREEN "%d etudiant trouvee \n" COLOR_RESET, size);
    printf(COLOR_VIOLET "--------------------------------------------------------------\n" COLOR_RESET);
    for(int i=0; i<size; i++){
        printf(COLOR_VIOLET "etudiant avec l'identifiant %d \n" COLOR_RESET, tableau[i].uid);
        printf("    nom: %s\n", tableau[i].nom);
        printf("    prenom: %s\n", tableau[i].prenom);
        printf("    date de naissance: %d/%d/%d \n", tableau[i].date_naiss.jour, tableau[i].date_naiss.mois, tableau[i].date_naiss.annee);
        printf("    departement: %s \n", tableau[i].departement);
        printf("    note general: %.2f \n", tableau[i].noteGeneral);
        printf(COLOR_VIOLET "--------------------------------------------------------------\n" COLOR_RESET);
    }
    return;
}
void moyenneGeneral(){
    system("cls");
    printf(COLOR_YELLOW "--------------------------------------------------------------\n");
    printf("                      moyenne generale                        \n");
    printf("--------------------------------------------------------------\n" COLOR_RESET);
    if(taille == 0){
        printf(COLOR_RED "aucun etudiant availaible maintenant\n" COLOR_RESET);
        return;
    }
    else{
        printf(COLOR_VIOLET "--------------------------------------------------------------\n");
        int nbre_departements = nbreDepartements();
        float moyenneGlobale = 0, sommeGlobale = 0;
        for(int i=0; i<nbre_departements; i++){
            float moyenne = 0, somme = 0;
            int counter = 0; // stocker le nombre d'etudiant dans un departement commun
            for(int j=0; j<taille; j++){
                if(strcmp(departements[i], etudiants[j].departement) == 0){
                    somme = somme + etudiants[j].noteGeneral;
                    counter++;
                }
            }
            sommeGlobale += somme;
            moyenne = somme / counter;
            printf(COLOR_VIOLET "Departement %s: " COLOR_RESET, departements[i]);
            printf("moyenne generale %.2f \n", moyenne);
        }
        moyenneGlobale = sommeGlobale / taille;
        printf("\nla moyenne globale de l'universite: %.2f\n", moyenneGlobale);
        printf(COLOR_VIOLET "--------------------------------------------------------------\n");
    }
}
void statistiques(){
    system("cls");
    printf(COLOR_YELLOW "--------------------------------------------------------------\n");
    printf("                         statistique                          \n");
    printf("--------------------------------------------------------------\n");
    if(taille == 0){
        printf(COLOR_RED "aucun statistique availaible\n" COLOR_RESET);
        return;
    }
    else{
        int statistique_choix;
        do{
            printf(COLOR_YELLOW "--------------------------------------------------------------\n");
            printf("1- nombre total d'etudiants inscrits.\n");
            printf("2- nombre d'etudiants dans chaque departement.\n");
            printf("3- etudiants ayant une moyenne generale superieure a un certain seuil.\n");
            printf("4- les 3 etudiants ayant les meilleures notes.\n");
            printf("5- nombre d'etudiants ayant reussi dans chaque departement (ceux ayant une note superieure ou egale a 10/20).\n");
            printf("6- retour au menu principale.\n");
            printf("--------------------------------------------------------------\n" COLOR_RESET);
            printf("entrer votre choix: "); scanf("%d", &statistique_choix);

            switch(statistique_choix){
                case 1: etudiantInscris(); break;
                case 2: etudiantDansChaqueDepartement(); break;
                case 3: etudiantParNoteGeneral(); break;
                case 4: troisPremiersEtudiant(); break;
                case 5: etudiantReussits(); break;
                case 6: return; break;
                default: 
                    printf(COLOR_RED "choisit un choix valid.\n" COLOR_RESET);
                    break;
            }
        }
        while(statistique_choix < 1 || statistique_choix > 6);
    }


}
void rechercherEtudiant(){
    system("cls");
    printf(COLOR_YELLOW "--------------------------------------------------------------\n");
    printf("                   rechercher un etudiant                     \n");
    printf("--------------------------------------------------------------\n" COLOR_RESET);
    if(taille == 0){
        printf(COLOR_RED "aucun etudiant availaible maintenant\n" COLOR_RESET);
        return;
    }
    else{
        int rechercher_choix;
        do{
            printf(COLOR_YELLOW "--------------------------------------------------------------\n");
            printf("1- rechercher un etudiant par son nom\n");
            printf("2- rechercher un etudiant par departement\n");
            printf("3- retour au menu principale\n");
            printf("--------------------------------------------------------------\n" COLOR_RESET);
            printf("entrer votre choix: "); scanf("%d", &rechercher_choix);

            switch(rechercher_choix){
                case 1: rechercherParNom(); break;
                case 2: rechercherParDepartement(); break;
                case 3: return; break;
                default: 
                    printf(COLOR_RED "choisit un choix valid.\n" COLOR_RESET);
                    break;
            }
        }
        while(rechercher_choix < 1 || rechercher_choix > 3);
    }
}
void triEtudiants(){}

// **************************** //
// calcule le nombre de departement d'une maniere dynamique
int nbreDepartements(){
    int counter = 0;
    while(departements[counter] != NULL){
        counter++;
    }    
    return counter;
}
void choisitDepartement(int indice){
    int departement_choisi;
    int nbre_departements = nbreDepartements();
    printf("--------------------------------------------------------------\n");
    for(int i=0; i<nbre_departements; i++){
        printf("%d- %s\n", i+1, departements[i]);
    }
    do{
        printf("--------------------------------------------------------------\n");
        printf("selectioner votre departement: "); scanf("%d", &departement_choisi);
    }
    while(departement_choisi < 1 || departement_choisi > 5);

    strcpy(etudiants[indice].departement, departements[departement_choisi - 1]);
    
}
void modifierOuSupprimer(){
    system("cls");
    printf(COLOR_YELLOW "--------------------------------------------------------------\n");
    printf("             supprimer ou modifier un etudiant                \n");
    printf("--------------------------------------------------------------\n");
    int suppression_choix;
    do{
        printf(COLOR_YELLOW "--------------------------------------------------------------\n");
        printf("1- modifier un etudiant\n");
        printf("2- supprimer un etudiant\n");
        printf("3- retour au menu principale\n");
        printf("--------------------------------------------------------------\n" COLOR_RESET);
        printf("entrer votre choix: "); scanf("%d", &suppression_choix);

        switch(suppression_choix){
            case 1: modifierEtudiant(); break;
            case 2: supprimerEtudiant(); break;
            case 3: return; break;
            default: 
                printf(COLOR_RED "choisit un choix valid.\n" COLOR_RESET);
                break;
        }
    }
    while(suppression_choix < 1 || suppression_choix > 3);
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
    choisitDepartement(position);
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
void rechercherParNom(){
    system("cls");
    printf(COLOR_YELLOW "--------------------------------------------------------------\n");
    printf("               rechercher un etudiant par nom                 \n");
    printf("--------------------------------------------------------------\n" COLOR_RESET);

    char nom[35];
    int counter = 0;
    printf("entrer le nom d'etudiant: "); scanf(" %[^\n]s", nom);
    for(int i=0; i<taille; i++){
        if(strcmp(nom, etudiants[i].nom) == 0){
            tmp_etudiants[counter] = etudiants[i];
            counter++;
        }
    }
    afficherInfosEtudiants(tmp_etudiants, counter);
}
void rechercherParDepartement(){
    system("cls");
    printf(COLOR_YELLOW "--------------------------------------------------------------\n");
    printf("           rechercher un etudiant par departement             \n");
    printf("--------------------------------------------------------------\n" COLOR_RESET);

    char departement[35];
    int counter = 0;
    printf("entrer le nom de departement: "); scanf(" %[^\n]s", departement);
    for(int i=0; i<taille; i++){
        if(strcmp(departement, etudiants[i].departement) == 0){
            tmp_etudiants[i] = etudiants[i];
            counter++;
        }
    }
    afficherInfosEtudiants(tmp_etudiants, counter);
}

void afficherListEtudiants(){
    system("cls");
    printf(COLOR_YELLOW "--------------------------------------------------------------\n");
    printf("                 afficher lisr des etudiants                  \n");
    printf("--------------------------------------------------------------\n" COLOR_RESET);
    if(taille == 0){
        printf(COLOR_RED "aucun etudiant availaible maintenant\n" COLOR_RESET);
        return;
    }
    else{
        afficherInfosEtudiants(etudiants, taille);
    }
}

void etudiantInscris(){
    printf(COLOR_VIOLET "Le nombre total des etudiants inscrits: %d etudiants\n" COLOR_RESET, taille);
}
void etudiantDansChaqueDepartement(){
    int nbre_departements = nbreDepartements();
    printf(COLOR_VIOLET "Le nombre des etudiants dans chaque departement\n" COLOR_RESET);
    for(int i=0; i<nbre_departements; i++){
        int counter = 0;
        for(int j=0; j<taille; j++){
            if(strcmp(etudiants[j].departement, departements[i]) == 0){
                counter++;
            }
        }
        printf("    departement %s: %d etudiant(s) \n", departements[i], counter);
    }
}
void etudiantParNoteGeneral(){
    system("cls");
    float seuil;
    int counter = 0;
    printf("entrer la seuille: "); scanf("%f", &seuil);
    for(int i=0; i<taille; i++){
        if(etudiants[i].noteGeneral >= seuil){
            tmp_etudiants[counter] = etudiants[i];
            counter++;
        }
    }
    printf("les etudiant ayant une note superieure a la seuille %.2f\n", seuil);
    afficherInfosEtudiants(tmp_etudiants, counter);
}
void troisPremiersEtudiant(){
    triEtudiantParNoteAsc();
    for(int i=0; i<3; i++){
        tmp_etudiants[i] = etudiants[i];
    }
    system("cls");
    printf(COLOR_YELLOW "--------------------------------------------------------------\n");
    printf("                     list des etudiants                       \n");
    printf("--------------------------------------------------------------\n");
    printf("les trois etudiant ayant la premiere note.\n" COLOR_RESET);
    afficherInfosEtudiants(tmp_etudiants, 3);
}
void etudiantReussits(){
    int counter = 0;
    for(int i=0; i<taille; i++){
        if(etudiants[i].noteGeneral >= 10){
            tmp_etudiants[counter] = etudiants[i];
            counter++;
        }
    }
    printf("les etudiant ayant reussi sont %d etudiants\n", counter);
    if(counter == 0){
        printf(COLOR_RED "aucun etudiant a reussi...\n" COLOR_RESET);
        return;
    }
    afficherInfosEtudiants(tmp_etudiants, counter);
}

Etudiant tmp;

void menuDeTri(){
    system("cls");
    printf(COLOR_YELLOW "--------------------------------------------------------------\n");
    printf("                     trie les etudiants                       \n");
    printf("--------------------------------------------------------------\n" COLOR_RESET);
    if(taille == 0){
        printf(COLOR_RED "aucun etudiant availaible maintenant\n" COLOR_RESET);
        return;
    }
    else{
        int tri_choix;
        do{
            printf(COLOR_YELLOW "--------------------------------------------------------------\n");
            printf("1- afficher les etudiant par nom en ordre croissant. \n");
            printf("2- afficher les etudiant par nom en ordre decroissant. \n");
            printf("3- afficher les etudiant par note en ordre decroissant. \n");
            printf("4- afficher les etudiant par note en ordre croissant. \n");
            printf("5- afficher les etudiant selon le status de reussite. \n");
            printf("6- retour au menu principale\n");
            printf("--------------------------------------------------------------\n" COLOR_RESET);
            printf("entrer votre choix: "); scanf("%d", &tri_choix);

            switch(tri_choix){
                case 1: triEtudiantParNomAsc(); break;
                case 2: triEtudiantParNomDesc(); break;
                case 3: triEtudiantParNoteAsc(); break;
                case 4: triEtudiantParNoteDesc(); break;
                case 5: triEtudiantSelonStatusDeReussit(); break;
                case 6: return; break;
                default: 
                    printf(COLOR_RED "choisit un choix valid.\n" COLOR_RESET);
                    break;
            }
        }
        while(tri_choix != 6);
    }
}

void triEtudiantParNoteDesc(){
    for (int i = 0; i < taille - 1; i++) {
        for (int j = 0; j < taille - i - 1; j++) {
            if (etudiants[j].noteGeneral > etudiants[j + 1].noteGeneral) {
                // Échange des éléments
                tmp_etudiants[0] = etudiants[j];
                etudiants[j] = etudiants[j + 1];
                etudiants[j + 1] = tmp_etudiants[0];
            }
        }
    }
    system("cls");
    printf(COLOR_YELLOW "--------------------------------------------------------------\n");
    printf("                     list des etudiants                       \n");
    printf("--------------------------------------------------------------\n" COLOR_RESET);
    printf("list trie par ordre croissant de note general\n");
    afficherInfosEtudiants(etudiants, taille);
}
void triEtudiantParNoteAsc(){
    for (int i = 0; i < taille - 1; i++) {
        for (int j = 0; j < taille - i - 1; j++) {
            if (etudiants[j].noteGeneral < etudiants[j + 1].noteGeneral) {
                // Échange des éléments
                tmp_etudiants[0] = etudiants[j];
                etudiants[j] = etudiants[j + 1];
                etudiants[j + 1] = tmp_etudiants[0];
            }
        }
    }
    system("cls");
    printf(COLOR_YELLOW "--------------------------------------------------------------\n");
    printf("                     list des etudiants                       \n");
    printf("--------------------------------------------------------------\n");
    printf("list trie par ordre decroissant de note general\n" COLOR_RESET);
    afficherInfosEtudiants(etudiants, taille);
}

void triEtudiantParNomDesc(){
    for (int i = 0; i < taille - 1; i++) {
        for (int j = 0; j < taille - i - 1; j++) {
            if (strcmp(etudiants[j].nom, etudiants[j + 1].nom) > 0) {
                // Échange des éléments
                tmp_etudiants[0] = etudiants[j];
                etudiants[j] = etudiants[j + 1];
                etudiants[j + 1] = tmp_etudiants[0];
            }
        }
    }
    system("cls");
    printf(COLOR_YELLOW "--------------------------------------------------------------\n");
    printf("                     list des etudiants                       \n");
    printf("--------------------------------------------------------------\n" COLOR_RESET);
    printf("list trie par ordre croissant de note general\n");
    afficherInfosEtudiants(etudiants, taille);
}
void triEtudiantParNomAsc(){
    for (int i = 0; i < taille - 1; i++) {
        for (int j = 0; j < taille - i - 1; j++) {
            if (strcmp(etudiants[j].nom, etudiants[j + 1].nom) < 0) {
                // Échange des éléments
                tmp_etudiants[0] = etudiants[j];
                etudiants[j] = etudiants[j + 1];
                etudiants[j + 1] = tmp_etudiants[0];
            }
        }
    }
    system("cls");
    printf(COLOR_YELLOW "--------------------------------------------------------------\n");
    printf("                     list des etudiants                       \n");
    printf("--------------------------------------------------------------\n");
    printf("list trie par ordre decroissant de note general\n" COLOR_RESET);
    afficherInfosEtudiants(etudiants, taille);
}

void triEtudiantSelonStatusDeReussit(){
    int counter = 0;
    for(int i=0; i<taille; i++){
        if(etudiants[i].noteGeneral >= 10){
            tmp_etudiants[counter] = etudiants[i];
            counter++;
        }
    }
    Etudiant tmp;
    for (int i = 0; i < counter - 1; i++) {
        for (int j = 0; j < counter - i - 1; j++) {
            if (tmp_etudiants[j].noteGeneral < tmp_etudiants[j + 1].noteGeneral) {
                tmp = tmp_etudiants[j];
                tmp_etudiants[j] = tmp_etudiants[j + 1];
                tmp_etudiants[j + 1] = tmp;
            }
        }
    }
    system("cls");
    printf(COLOR_YELLOW "--------------------------------------------------------------\n");
    printf("                     list des etudiants                       \n");
    printf("--------------------------------------------------------------\n");
    printf("list trie selon le status de reussit\n" COLOR_RESET);
    afficherInfosEtudiants(tmp_etudiants, counter);
}

