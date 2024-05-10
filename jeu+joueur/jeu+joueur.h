
#ifndef ESCOOKED_JEU_JOUEUR_H
#define ESCOOKED_JEU_JOUEUR_H

#include "../constantes.h"

typedef enum {
    NIVEAU_INCONNU = 0,
    NIVEAU_1,
    NIVEAU_2,
    NIVEAU_3
} Niveau;

typedef enum {
    CITRON_PRESSE,
    MENTHE_DECOUPE,
    LIMONADE,
    CANNE_A_SUCRE,
    INGREDIENT_NULL
} Ingredients;

typedef enum {
    MOJITO,
    CAIPIRINHA,
    HINTZY,
    PLAZA,
    RECETTE_NULL
} RecetteID;

typedef struct {
    int x, y, width, height;
    char *texte;
} BoutonJeu;

typedef struct {
    int x, y;
    ALLEGRO_BITMAP *image;
    bool estVisible;
    Ingredients ingredientID;
    RecetteID recetteID;
} ElementsLaches;

typedef struct {
    int type, x, y;
    ALLEGRO_BITMAP *image;
    Ingredients ingredientID;
    RecetteID recetteID;
} Element;

typedef struct {
    char pseudo[13];
    ALLEGRO_BITMAP *image;
    int score, x, y, vx, vy;
    float angle;
    Element *element;
} Joueur;

typedef struct {
    RecetteID id;
    int ingredients[5];
    ALLEGRO_BITMAP *image;
    char nom[20];
} Recette;

typedef struct {
    ALLEGRO_BITMAP *imagesVerres[10];
    ALLEGRO_BITMAP *imagesIngredients[5];
    ALLEGRO_BITMAP *imageFondCommande;
} ImagesCommandes;

typedef struct Commande {
    Recette *recette;
    int *ingredients;
    int nombre_ingredients;
    int timer;
    int timerInitial;
    int score;
    bool estCompletee;
    struct Commande *suivant;
} Commande;

typedef struct {
    ALLEGRO_DISPLAY *fenetre;
    ALLEGRO_EVENT_QUEUE *file;
    ALLEGRO_TIMER *timer;
    int DureePartie;
    ALLEGRO_BITMAP *Z;
    ALLEGRO_BITMAP *Q;
    ALLEGRO_BITMAP *S;
    ALLEGRO_BITMAP *D;
    ALLEGRO_BITMAP *C;
    ALLEGRO_BITMAP *V;
    ALLEGRO_BITMAP *L;
    ALLEGRO_BITMAP *M;
    ALLEGRO_BITMAP *P;
    ALLEGRO_BITMAP *FlecheHaut;
    ALLEGRO_BITMAP *FlecheGauche;
    ALLEGRO_BITMAP *FlecheBas;
    ALLEGRO_BITMAP *FlecheDroite;
    ALLEGRO_BITMAP *ImageMenu;
    ALLEGRO_BITMAP *ImageFondDeJeu;
    ALLEGRO_BITMAP *decor;
    ALLEGRO_BITMAP *sol1;
    ALLEGRO_BITMAP *sol2;
    ALLEGRO_BITMAP *plaqueDeCuisson;
    ALLEGRO_BITMAP *stationDeDecoupe;
    ALLEGRO_BITMAP *planDeTravail;
    ALLEGRO_BITMAP *presseAgrume;
    ALLEGRO_BITMAP *poubelle;
    ALLEGRO_BITMAP *sortie;
    ALLEGRO_BITMAP *sablier;
    ALLEGRO_BITMAP *tomate;
    ALLEGRO_BITMAP *citron;
    ALLEGRO_BITMAP *menthe;
    ALLEGRO_BITMAP *limonade;
    ALLEGRO_BITMAP *canneASucre;
    ALLEGRO_BITMAP *frigoCitron;
    ALLEGRO_BITMAP *frigoLimonade;
    ALLEGRO_BITMAP *frigoMenthe;
    ALLEGRO_BITMAP *frigoCanneASucre;
    ALLEGRO_BITMAP *mojito;
    ALLEGRO_BITMAP *caipirinha;
    ALLEGRO_BITMAP *hintzy;
    ALLEGRO_FONT *police;
    ALLEGRO_FONT *policeTitre;
    ALLEGRO_FONT *policePseudo;
    ALLEGRO_FONT *policeRegle;
    ALLEGRO_SAMPLE *musiqueFond;
    ALLEGRO_SAMPLE_INSTANCE *instanceMusique;
    ALLEGRO_SAMPLE *sonBoutonClique;
    Element *element;
    int nbElement;
    ElementsLaches elementsLaches[100];
    int nbElementsLaches;
    bool enPause;
} ComposantsJeu;


#endif //ESCOOKED_JEU_JOUEUR_H
