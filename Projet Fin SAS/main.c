#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <math.h>
#include <time.h>

typedef struct{
    int jour;
    int mois;
    int anne;
}date;
typedef enum {
  ToDo,
  Doing,
  Done
}statut;
typedef struct tache {
    int identifiant;
    char titre[20];
    char desc[100];
    date deadline;
    statut st;
    struct tache * suivant;

}tache;



int compareDeadline(date d1, date d2) { //Cette fonction return 1 si d1 = d2, return 1 si d1 > d2 and return -1 si d1 < d2
    if(d1.anne == d2.anne) {
        if(d1.mois == d2.mois) {
            if(d1.jour == d2.jour) return 0;
            if(d1.jour > d2.jour) return 1;
            return -1;
        }
        if(d1.mois > d2.mois) return 1;
        return -1;
    }
    if(d1.anne > d2.anne ) return 1;
    return -1;

}

date dateActuel() {
    time_t currentTime;
    struct tm *timeInfo;

    // Obtenir le temps actuel
    time(&currentTime);

    // Convertir en structure de date et heure
    timeInfo = localtime(&currentTime);

    // Extraire le jour, le mois et l'annee
    date dateActl;
    dateActl.jour = timeInfo->tm_mday;     // Jour du mois (1-31)
    dateActl.mois = timeInfo->tm_mon + 1; // Mois (0-11, donc +1 pour avoir 1-12)
    dateActl.anne = timeInfo->tm_year + 1900; // Annee (compter à partir de 1900)
    return dateActl;
}

int differenceEntreDates(date date1, date date2) {
    // Nombre de jours dans chaque mois (non bissextile)
    int joursParMois[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    // Verifier si les annees sont bissextiles
    int anneeBissextile1 = (date1.anne % 4 == 0 && (date1.anne % 100 != 0 || date1.anne % 400 == 0));
    int anneeBissextile2 = (date2.anne % 4 == 0 && (date2.anne % 100 != 0 || date2.anne % 400 == 0));

    // Ajouter un jour à fevrier en cas d'annee bissextile
    if (anneeBissextile1) joursParMois[2] = 29;
    if (anneeBissextile2) joursParMois[2] = 29;

    // Calculer la difference en jours
    int differenceEnJours = 0;

    // Ajouter les jours complets des annees
    for (int annee = date1.anne; annee < date2.anne; annee++) {
        if ((annee % 4 == 0 && (annee % 100 != 0 || annee % 400 == 0))) {
            differenceEnJours += 366; // Annee bissextile (366 jours)
        } else {
            differenceEnJours += 365; // Annee normale (365 jours)
        }
    }

    // Ajouter les jours complets des mois
    for (int mois = date1.mois + 1; mois <= 12; mois++) {
        differenceEnJours += joursParMois[mois];
    }
    for (int mois = 1; mois < date2.mois; mois++) {
        differenceEnJours += joursParMois[mois];
    }

    // Ajouter les jours du mois de depart
    differenceEnJours += joursParMois[date1.mois] - date1.jour;

    // Ajouter les jours du mois d'arrêt
    differenceEnJours += date2.jour;

    return differenceEnJours - 365;
}

int nbrTache(tache *t) {
    int i = 0;
    while(t != NULL) {
        i++;
        t = t->suivant;
    }
    return i;
}


struct tache *ajouteTache(struct tache *t) {
    if(t == NULL) {
        t = (struct tache*)malloc(sizeof(struct tache));
        t->identifiant = 1;

        printf("Entrez un titre pour votre tache :");
        scanf(" %[^\n]", t->titre);

        printf("Entrez une description pour votre tache :");
        scanf(" %[^\n]", t->desc);

         printf("Entrez une deadline pour votre tache sous forme jj/mm/aaaa :");
        scanf("%d/%d/%d", &t->deadline.jour, &t->deadline.mois, &t->deadline.anne);

        while(t->deadline.jour < 0 || t->deadline.jour > 31 || t->deadline.mois < 0 || t->deadline.mois > 12) {
            printf("S\'il vous plait entrez une date valide sous forme jj/mm/aaaa :");
            scanf("%d/%d/%d", &t->deadline.jour, &t->deadline.mois, &t->deadline.anne);
        }
        char c;
        do{
            printf("Entrez le statut de votre tache :\n 0 pour ToDo, 1 pour Doing, 2 pour Done :\n");
            scanf(" %c", &c);
            t->st = (int)c - 48;
        }while(c < 48 || c > 50);
        t->suivant = NULL;






    }
    else {
    tache *temp;
    tache *res;
    res = t;
    temp = (struct tache*)malloc(sizeof(struct tache));
    int nombreTache = nbrTache(t);
    tache *temp1 = t;
    int plusGrandId = temp1->identifiant;
    for(int i = 0; i < nombreTache; i++) {
        if(temp1->identifiant > plusGrandId) plusGrandId = temp1->identifiant;
        temp1 = temp1->suivant;
    }
    temp->identifiant = plusGrandId + 1;

    printf("Entrez un titre pour votre tache :");
    scanf(" %[^\n]", temp->titre);

    printf("Entrez une description pour votre tache :");
    scanf(" %[^\n]", temp->desc);

     printf("Entrez une deadline pour votre tache sous forme jj/mm/aaaa :");
    scanf("%d/%d/%d", &temp->deadline.jour, &temp->deadline.mois, &temp->deadline.anne);

    while(temp->deadline.jour < 0 || temp->deadline.jour > 31 || temp->deadline.mois < 0 || temp->deadline.mois > 12) {
        printf("S\'il vous plait entrez une date valide sous forme jj/mm/aaaa :");
        scanf("%d/%d/%d", &temp->deadline.jour, &temp->deadline.mois, &temp->deadline.anne);
    }
    char c;
    do{
        printf("Entrez le statut de votre tache :\n 0 pour ToDo, 1 pour Doing, 2 pour Done :\n");
        scanf(" %c", &c);
        temp->st = (int)c - 48;
    }while(c < 48 || c > 50);
    temp->suivant = NULL;
    if(t == NULL) return temp;
    while(t->suivant != NULL) {
        t = t->suivant;
    }
    t->suivant = temp;

    return res;

}
}

struct tache *ajoutePlusieursTaches(tache *t) {
    tache *res;
    res = (struct tache*)malloc(sizeof(struct tache));
    res = NULL;
    int nbrTaches;
    printf("Entrez le nombre de taches que vous devez ajouter : ");
    scanf("%d", &nbrTaches);
    int i = 1;
    while(nbrTaches != 0) {
        printf("La tache %d : \n", i);
        t = ajouteTache(t);
        nbrTaches--;
        i++;
    }
    return t;
}



void afficheTache(struct tache* t) {
    if(t == NULL) printf("N'existe pas une tache.\n");
    while(t != NULL) {
        printf("***************************************************\n");
        printf("La tache d'identifiant %d :\n", t->identifiant);
        printf("\tL\'identifiant : %d\n", t->identifiant);
        printf("\tLe titre : %s\n", t->titre);
        printf("\tLa description : %s\n", t->desc);
        printf("\tLe deadline : %d/%d/%d\n", t->deadline.jour, t->deadline.mois, t->deadline.anne);
        printf("\tLe statut : ");
        switch(t->st) {
        case 0: printf("ToDo\n");
                break;
        case 1: printf("Doing\n");
                break;
        case 2: printf("Done\n");
                break;
        }
        printf("***************************************************\n");
        t = t->suivant;
    }




}

void afficheParDeadline(tache *t) {
    struct tache *temp, *temp1;
    temp = t;
    temp1 = t;
    tache Temp;
    while(temp != NULL){
        while(t != NULL && t->suivant != NULL) {
            if(compareDeadline(t->deadline, t->suivant->deadline) > 0 ){
                Temp.deadline = t->deadline;
                t->deadline = t->suivant->deadline;
                t->suivant->deadline = Temp.deadline;

                strcpy(Temp.desc, t->desc);
                strcpy(t->desc, t->suivant->desc);
                strcpy(t->suivant->desc, Temp.desc);

                Temp.identifiant = t->identifiant;
                t->identifiant = t->suivant->identifiant;
                t->suivant->identifiant = Temp.identifiant;

                Temp.st = t->st;
                t->st = t->suivant->st;
                t->suivant->st = Temp.st;

                strcpy(Temp.titre, t->titre);
                strcpy(t->titre, t->suivant->titre);
                strcpy(t->suivant->titre, Temp.titre);
            }
        t = t->suivant;
        }
        t = temp1;
        temp = temp->suivant;
    }

    afficheTache(temp1);


}

void afficheParOrdreAlphab(tache *t) {
    struct tache *temp;
    temp = t;
    struct tache *temp1;
    temp1 = t;
    tache Temp;
    while(temp != NULL){
        while(t != NULL && t->suivant != NULL) {
            char arr1[100];
            char arr2[100];
            strcpy(arr1, t->titre);
            strcpy(arr2, t->suivant->titre);

            if(strcmp(strupr(arr1),strupr(arr2)) > 0 ){
                Temp.deadline = t->deadline;
                t->deadline = t->suivant->deadline;
                t->suivant->deadline = Temp.deadline;

                strcpy(Temp.desc, t->desc);
                strcpy(t->desc, t->suivant->desc);
                strcpy(t->suivant->desc, Temp.desc);

                Temp.identifiant = t->identifiant;
                t->identifiant = t->suivant->identifiant;
                t->suivant->identifiant = Temp.identifiant;

                Temp.st = t->st;
                t->st = t->suivant->st;
                t->suivant->st = Temp.st;

                strcpy(Temp.titre, t->titre);
                strcpy(t->titre, t->suivant->titre);
                strcpy(t->suivant->titre, Temp.titre);
            }
        t = t->suivant;
        }
        t = temp1;
        temp = temp->suivant;
    }

    afficheTache(temp1);

}

void afficheAuMois3Jours(tache *t) {
    if(t == NULL) printf("N'existe pas une tache.\n");
    while(t != NULL) {
        if(differenceEntreDates(t->deadline, dateActuel()) <= 3) {
            printf("***************************************************\n");
            printf("La tache d'identifiant %d :\n", t->identifiant);
            printf("\tL\'identifiant : %d\n", t->identifiant);
            printf("\tLe titre : %s\n", t->titre);
            printf("\tLa description : %s\n", t->desc);
            printf("\tLe deadline : %d/%d/%d\n", t->deadline.jour, t->deadline.mois, t->deadline.anne);
            printf("\tLe statut : ");
            switch(t->st) {
            case 0: printf("ToDo\n");
                    break;
            case 1: printf("Doing\n");
                    break;
            case 2: printf("Done\n");
                    break;

            }
            printf("***************************************************\n");

            }
            t = t->suivant;
    }


}



struct tache *modifierDes(tache *t, char desc[]) {
    if(t == NULL) return NULL;
    int id;
    tache *temp = t;
    printf("Entrez l'indentite de tache que vous modifier : ");
    scanf("%d", &id);
    while(t != NULL) {
        if(t->identifiant == id) strcpy(t->desc, desc);
        t = t->suivant;
    }
    return temp;
}

struct tache *modifierStatut(tache *t, statut st) {
    if(t == NULL) return NULL;
    int id;
    tache *temp = t;
    printf("Entrez l'indentite de tache que vous modifier : ");
    scanf("%d", &id);
    while(t != NULL) {
        if(t->identifiant == id) t->st = st;
        t = t->suivant;
    }
    return temp;
}

struct tache *modifierDeadline(tache *t, date deadline) {
    if(t == NULL) return NULL;
    int id;
    tache *temp = t;
    printf("Entrez l'indentite de tache que vous modifier : ");
    scanf("%d", &id);
    while(t != NULL) {
        if(t->identifiant == id) t->deadline = deadline;
        t = t->suivant;
    }
    return temp;
}



struct tache *supprimeParIdentifiant(tache *t, int id) {
    if(t == NULL) return NULL;
    if(t->identifiant == id) return t->suivant;
    tache * temp, * temp1;
    temp = t;
    while(t->suivant != NULL && t->suivant->identifiant != id) {
        t = t->suivant;
    }
    if(t->suivant != NULL) {
        temp1 = t->suivant;
        t->suivant = t->suivant->suivant;
        free(temp1);
    }

    return temp;



}



void rechercheParIdentifiant(tache *t, int id) {
    int b = 0;
    while(t != NULL) {
        if(t->identifiant == id) {
                b = 1;
                break;
           }
        t = t->suivant;
    }





    if(b == 1){
        printf("La tache recherchee est :\n");
        printf("***************************************************\n");
        printf("La tache d'identifiant %d :\n", t->identifiant);
        printf("\tL\'identifiant : %d\n", t->identifiant);
        printf("\tLe titre : %s\n", t->titre);
        printf("\tLa description : %s\n", t->desc);
        printf("\tLe deadline : %d/%d/%d\n", t->deadline.jour, t->deadline.mois, t->deadline.anne);
        printf("\tLe statut : ");
        switch(t->st) {
        case 0: printf("ToDo\n");
                break;
        case 1: printf("Doing\n");
                break;
        case 2: printf("Done\n");
                break;
        }
        printf("***************************************************\n");
    }
    else
        printf("L'identifiant que vous avez saisi n'existe pas.\n");
}

void rechercheParTitre(tache *t, char titre[]) {
    bool b = true;
    while(t != NULL) {
        char temp1[100], temp2[100];
        strcpy(temp1, t->titre);
        strcpy(temp2, titre);
        if(strcmp(strupr(temp1), strupr(temp2)) == 0) {
            b = false;
            printf("La tache recherchee est :\n");
            printf("***************************************************\n");
            printf("La tache d'identifiant %d :\n", t->identifiant);
            printf("\tL\'identifiant : %d\n", t->identifiant);
            printf("\tLe titre : %s\n", t->titre);
            printf("\tLa description : %s\n", t->desc);
            printf("\tLe deadline : %d/%d/%d\n", t->deadline.jour, t->deadline.mois, t->deadline.anne);
            printf("\tLe statut : ");
            switch(t->st) {
            case 0: printf("ToDo\n");
                    break;
            case 1: printf("Doing\n");
                    break;
            case 2: printf("Done\n");
                    break;
            }
            printf("***************************************************\n");
        }


        t = t->suivant;
}

    if(b == true)
        printf("Le titre que vous avez saisi n'existe pas.\n");
}



int nbrTacheCompl(tache *t) {
    int i = 0;
    while(t != NULL) {
        if(t->st == 2) i++;
        t = t->suivant;
    }
    return i;
}

int nbrTacheInCompl(tache *t) {
    int i = 0;
    while(t != NULL) {
        if(t->st != 2) i++;
        t = t->suivant;
    }
    return i;
}

void nbrJoursRest(tache *t) {
    if(t == NULL) printf("N'existe pas un tache");
    while(t != NULL) {
        printf("Le nombre de jours restants jusqu'au delai de tache %d est :%d\n",t->identifiant, differenceEntreDates(t->deadline, dateActuel()));
        t = t->suivant;
    }

}


struct tache *remplir() {
    tache *t;

    t = (tache*)malloc(sizeof( tache));
    t->identifiant = 1;
    strcpy(t->desc, "Mon tache decription 1");
    t->st = 0;
    strcpy(t->titre, "Lire une livre");
    date d = {dateActuel().jour + 1,dateActuel().mois - 5, dateActuel().anne};
    t->deadline = d;

    t->suivant = (tache*)malloc(sizeof( tache));
    t->suivant->identifiant = 2;
    strcpy(t->suivant->desc, "Mon tache decription 2");
    t->suivant->st = 1;
    strcpy(t->suivant->titre, "faire des courses");
    date d1 = dateActuel();
    t->suivant->deadline = d1;

    t->suivant->suivant = ( tache*) malloc(sizeof( tache));
    t->suivant->suivant->identifiant = 3;
    strcpy(t->suivant->suivant->desc, "Mon tahce description 3");
    t->suivant->suivant->st = 2;
    strcpy(t->suivant->suivant->titre, "Faires les devoirs");
    date d2 = {21, 9, 2023};
    t->suivant->suivant->deadline = d2;

    t->suivant->suivant->suivant = NULL;
    return t;

}
int main()
{

    tache *t;
    //t = (tache*)malloc(sizeof( tache));
    //t = NULL;
    //t = ajouteTache(t);
    //afficheTache(t);

    t = remplir();
    int choix;

    while(choix != 9) {
    printf("\t\t\t***********************Main***********************\n");
    printf("  \t\t\t1-Ajouter une nouvelle tache.\n");
    printf("  \t\t\t2-Ajouter plusieurs nouvelles taches.\n");
    printf("  \t\t\t3-Afficher la liste de toutes les taches.\n");
    printf("  \t\t\t4-Modifier une tache.\n");
    printf("  \t\t\t5-Supprimer une tache par identifiant.\n");
    printf("  \t\t\t6-Rechercher les taches.\n");
    printf("  \t\t\t7-Statistiques de votre taches.\n");
    printf("  \t\t\t8-Effacer l'ecran.\n");
    printf("  \t\t\t9-Sorite de programm.\n");


    printf("Entrez votre choix :");
    scanf("%d", &choix);

    switch(choix) {
        case 1: t = ajouteTache(t);
                break;

        case 2: t = ajoutePlusieursTaches(t);
                break;

        case 3: printf(" 1-Trier les taches par ordre alphabetique.\n");
                printf(" 2-Trier les taches par deadline.\n");
                printf(" 3-Afficher les taches dont le deadline est dans 3 jours ou moins.\n");
                int choix3;
                printf("Entrez votre choix pour triez les taches :");
                scanf("%d", &choix3);
                switch(choix3) {
                    case 1: afficheParOrdreAlphab(t);
                            break;
                    case 2: afficheParDeadline(t);
                            break;
                    case 3: afficheAuMois3Jours(t);
                            break;
                }
                break;

        case 4: printf(" 1-Modifier la description d\'une tache.\n");
                printf(" 2-Modifier le statut d\’une tache.\n");
                printf(" 3-Modifier le deadline d’une tache.\n");
                int choix4;
                printf("Entrez votre choix pour modifier une taches :");
                scanf("%d", &choix4);
                switch(choix4) {
                    case 1: char modfi[200];
                            printf("Entrez la nouvelle description :");
                            scanf(" %[^\n]", modfi);
                            modifierDes(t, modfi);
                            break;

                    case 2:
                            char c;
                            statut st;
                            do{
                                printf("Entrez la nouvelle statut : 0 pour ToDo, 1 pour Doing, 2 pour Done :\n");
                                scanf(" %c", &c);
                                st = (int)c - 48;
                            }while(c < 48 || c > 50);
                            modifierStatut(t, st);
                            break;

                    case 3: date d;
                            printf("Entrez la nouvelle deadline sous forme jj/mm/aaaa :\n");
                            scanf("%d/%d/%d", &d.jour, &d.mois, &d.anne);
                            while(d.jour < 0 || d.jour > 31 || d.mois < 0 || d.mois > 12) {
                                printf("S\'il vous plait entrez une date valide sous forme jj/mm/aaaa :");
                                scanf("%d/%d/%d", &d.jour, &d.mois, &d.anne);
                            }
                            modifierDeadline(t, d);
                            break;

                }
                break;

        case 5: int id;
                printf("Entrez l\'identifiant de la tache que vous souhaitez supprimer : ");
                scanf("%d", &id);
                t = supprimeParIdentifiant(t, id);
                //else printf("L\'identifiant que vous avez saisi n\'existe pas.");
                break;

        case 6: printf("1-Rechercher une tache par son identifiant.\n");
                printf("2-Rechercher une tache par son titre.\n");
                int choix6;
                int id6;
                printf("Entrez votre choix pour rechercher : ");
                scanf("%d", &choix6);
                switch(choix6) {
                    case 1:
                            printf("Entrez l'identifiant que vous souhaitez rechercher : ");
                            scanf("%d", &id6);
                            rechercheParIdentifiant(t, id6);
                            break;

                    case 2: char titre6[200];
                            printf("Entrez l'identifiant que vous souhaitez rechercher : ");
                            scanf(" %[^\n]", titre6);
                            rechercheParTitre(t, titre6);
                            break;

                }
                break;

        case 7: printf("1-Afficher le nombre total des taches.\n");
                printf("2-Afficher le nombre de taches completes et incompletes.\n");
                printf("3-Afficher le nombre de jours restants jusqu'au delai de chaque tache.\n");
                int choix7;
                printf("Entrez votre choix pour les statistiques : ");
                scanf("%d", &choix7);
                switch(choix7) {
                    case 1: printf("Le nombre total des taches est : %d\n", nbrTache(t));
                            break;

                    case 2: printf("Le nombre total des taches completes est : %d\n", nbrTacheCompl(t));
                            printf("le nombre total des taches incompletes est : %d\n", nbrTacheInCompl(t));
                            break;

                    case 3: nbrJoursRest(t);
                            break;

                }
                break;
        case 8: system("cls");
                break;
        default : printf("Entrez un nombre entre  et 0 et 9\n");

    }
}







    return 0;
}
