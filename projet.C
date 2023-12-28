#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure pour stocker les informations sur un voyageur
typedef struct {
    char nom[20];
    char prenom[20];
    char adresse[100];
} Voyageur;

// Structure pour stocker les informations sur un bus
typedef struct {
    int numero;
    char destination[20];
    int placesDisponibles;
} Bus;

// Structure pour stocker les informations sur une réservation
typedef struct {
    int numeroBus;
    Voyageur voyageur;
    int nombrePlaces;
} Reservation;

// Fonction pour créer un nouveau compte voyageur
Voyageur creerVoyageur() {
    Voyageur nouveauVoyageur;
    printf("Nom: ");
    scanf("%s", nouveauVoyageur.nom);
    printf("Prénom: ");
    scanf("%s", nouveauVoyageur.prenom);
    printf("Adresse: ");
    scanf(" %[^\n]s", nouveauVoyageur.adresse);
    return nouveauVoyageur;
}

// Fonction pour créer une nouvelle réservation
Reservation creerReservation(Bus *buses, int nbBuses) {
    Reservation nouvelleReservation;
    printf("Numéro du bus (1-%d): ", nbBuses);
    scanf("%d", &nouvelleReservation.numeroBus);
    printf("Nombre de places: ");
    scanf("%d", &nouvelleReservation.nombrePlaces);

    // Vérifier si le bus existe et s'il y a suffisamment de places disponibles
    if (nouvelleReservation.numeroBus < 1 || nouvelleReservation.numeroBus > nbBuses ||
        nouvelleReservation.nombrePlaces > buses[nouvelleReservation.numeroBus - 1].placesDisponibles) {
        printf("Erreur: Bus invalide ou places insuffisantes.\n");
        exit(EXIT_FAILURE);
    }

    // Demander les informations du voyageur
    printf("---- Informations du voyageur ----\n");
    nouvelleReservation.voyageur = creerVoyageur();

    return nouvelleReservation;
}

// Fonction pour afficher les détails des bus
void afficherDetailsBus(Bus *buses, int nbBuses) {
    printf("---- Détails des bus ----\n");
    for (int i = 0; i < nbBuses; ++i) {
        printf("Bus #%d - Destination: %s | Places disponibles: %d\n",
               buses[i].numero, buses[i].destination, buses[i].placesDisponibles);
    }
    printf("\n");
}

// Fonction pour annuler une réservation
void annulerReservation(Bus *buses, int nbBuses) {
    int numeroReservation;
    printf("Numéro de la réservation à annuler: ");
    scanf("%d", &numeroReservation);

    // Vérifier si la réservation existe
    if (numeroReservation < 1 || numeroReservation > nbBuses) {
        printf("Erreur: Numéro de réservation invalide.\n");
        return;
    }

    // Retrouver le bus associé à la réservation
    Bus *bus = &buses[numeroReservation - 1];



    printf("Réservation #%d annulée avec succès.\n", numeroReservation);
}


// Fonction principale
int main() {
    
    // Initialiser quelques bus 
    Bus buses[] = {
        {1, "Tunis", 25},
        {2, "Sousse", 20},
        {3, "Hammamet", 30},
    };
    int nbBuses = sizeof(buses) / sizeof(Bus);

    while (1) {
        printf("---- E-Bus Application ----\n");
        printf("1. Créer un nouveau compte voyageur\n");
        printf("2. Créer une nouvelle réservation\n");
        printf("3. Afficher les détails des bus\n");
        printf("4. Annuler une réservation\n");

        int choix;
        printf("Votre choix: ");
        scanf("%d", &choix);

        switch (choix) {
            case 1: {
                Voyageur nouveauVoyageur = creerVoyageur();
                break;
            }
            case 2: {
                Reservation nouvelleReservation = creerReservation(buses, nbBuses);
                buses[nouvelleReservation.numeroBus - 1].placesDisponibles -= nouvelleReservation.nombrePlaces;
                break;
            }
            case 3: {
                afficherDetailsBus(buses, nbBuses);
                break;
            }
            case 4: {
                annulerReservation(buses, nbBuses);
                break;
            }
            default:
                printf("Choix invalide. Veuillez réessayer.\n");
        }
    }

    return 0;
}
