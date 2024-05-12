#include "../constantes.h"
#include "jeu.h"
#include "math.h"

void InitialiserFenetreFileTimer(ComposantsJeu *jeu) {
    jeu->fenetre = al_create_display(DISPLAY_WIDTH, DISPLAY_HEIGHT);
    jeu->file = al_create_event_queue();
    jeu->timer = al_create_timer(1.0 / 60.0);
    jeu->DureePartie = 10;
    al_register_event_source(jeu->file, al_get_display_event_source(jeu->fenetre));
    al_register_event_source(jeu->file, al_get_keyboard_event_source());
    al_register_event_source(jeu->file, al_get_mouse_event_source());
    al_register_event_source(jeu->file, al_get_timer_event_source(jeu->timer));
    jeu->enPause = false;
}

void DessinerBoutonMenuPause(BoutonJeu boutonJeu, ComposantsJeu *jeu, ALLEGRO_COLOR couleurRectangle,
                             ALLEGRO_COLOR couleurTexte) {
    al_draw_filled_rounded_rectangle(boutonJeu.x, boutonJeu.y, boutonJeu.x + boutonJeu.width,
                                     boutonJeu.y + boutonJeu.height, 10, 10, couleurRectangle);
    int text_x = boutonJeu.x + (boutonJeu.width - al_get_text_width(jeu->police, boutonJeu.texte)) / 2;
    int text_y = boutonJeu.y + (boutonJeu.height - al_get_font_ascent(jeu->police)) / 2;
    al_draw_text(jeu->police, couleurTexte, text_x, text_y, 0, boutonJeu.texte);
}

bool EstDansLeBoutonMenuPause(BoutonJeu boutonJeu, float x, float y) {
    return (x >= boutonJeu.y && x <= boutonJeu.x + boutonJeu.width && y >= boutonJeu.y &&
            y <= boutonJeu.y + boutonJeu.height);
}

void DessinerMenuPause(ComposantsJeu *jeu, BoutonJeu *bouton) {
    al_draw_filled_rectangle(DISPLAY_WIDTH / 4, DISPLAY_HEIGHT / 4, 3 * DISPLAY_WIDTH / 4, 3 * DISPLAY_HEIGHT / 4,
                             al_map_rgba(0, 0, 0, 200));

    for (int i = 0; i < 2; i++) {
        DessinerBoutonMenuPause(bouton[i], jeu, al_map_rgba(139, 71, 3, 255), NOIR);
    }
}

void DessinerScoresFin(ComposantsJeu *jeu, int scoreJoueur1, int scoreJoueur2, Joueur *joueur1, Joueur *joueur2) {
    ALLEGRO_EVENT event;
    bool fini = false;
    int scoreEquipe = scoreJoueur1 + scoreJoueur2;

    al_draw_filled_rectangle(DISPLAY_WIDTH / 4, DISPLAY_HEIGHT / 4, 3 * DISPLAY_WIDTH / 4, 3 * DISPLAY_HEIGHT / 4,
                             al_map_rgba(0, 0, 0, 200));
    al_draw_bitmap(al_load_bitmap("../images/MACARON SCORE (2).png"), DISPLAY_WIDTH / 4 + 30, DISPLAY_HEIGHT / 4 + 50,
                   0);
    al_draw_bitmap(al_load_bitmap("../images/MACARON SCORE (2).png"), DISPLAY_WIDTH / 4 + 530, DISPLAY_HEIGHT / 4 + 50,
                   0);

    char text[100];
    al_draw_text(jeu->policeTitre, BLANC, DISPLAY_WIDTH / 2, 200, ALLEGRO_ALIGN_CENTER, "SCORES");
    sprintf(text, "%s : %d", joueur1->pseudo, scoreJoueur1);
    al_draw_text(jeu->police, BLANC, DISPLAY_WIDTH / 2, DISPLAY_HEIGHT / 2 - 30,
                 ALLEGRO_ALIGN_CENTER, text);
    sprintf(text, "%s : %d", joueur2->pseudo, scoreJoueur2);
    al_draw_text(jeu->police, BLANC, DISPLAY_WIDTH / 2, DISPLAY_HEIGHT / 2 + 30,
                 ALLEGRO_ALIGN_CENTER, text);
    sprintf(text, "Team : %d", scoreEquipe);
    al_draw_text(jeu->police, BLANC, DISPLAY_WIDTH / 2, DISPLAY_HEIGHT / 2 + 90,
                 ALLEGRO_ALIGN_CENTER, text);
    al_flip_display();
    while (!fini) {
        al_wait_for_event(jeu->file, &event);
        switch (event.type) {
            case ALLEGRO_EVENT_KEY_UP:
                fini = true;
                break;
        }
    }
}

void ChargerFichierTxt1(ComposantsJeu *jeu) {
    FILE *fichier = fopen("../images/FichierTexteNiveau1", "r");
    if (!fichier) {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier.\n");
        exit(EXIT_FAILURE);
    }

    jeu->element = malloc(NB_LIGNES * NB_COLONNES * sizeof(Element));
    jeu->nbElement = 0;
    int TypeElement;

    for (int i = 0; i < NB_LIGNES; ++i) {
        for (int j = 0; j < NB_COLONNES; ++j) {
            fscanf(fichier, "%d", &TypeElement);
            if (TypeElement != -1) {
                jeu->element[jeu->nbElement].type = TypeElement;
                jeu->element[jeu->nbElement].x = MARGE_GAUCHE_DROITE + j * TAILLE_CASE;
                jeu->element[jeu->nbElement].y = MARGE_HAUT_BAS + i * TAILLE_CASE;
                jeu->nbElement++;
            }
        }
    }
    fclose(fichier);
}

void ChargerFichierTxt2(ComposantsJeu *jeu) {
    FILE *fichier = fopen("../images/FichierTexteNiveau2", "r");
    if (!fichier) {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier.\n");
        exit(EXIT_FAILURE);
    }

    jeu->element = malloc(NB_LIGNES * NB_COLONNES * sizeof(Element));
    jeu->nbElement = 0;
    int TypeElement;

    for (int i = 0; i < NB_LIGNES; ++i) {
        for (int j = 0; j < NB_COLONNES; ++j) {
            fscanf(fichier, "%d", &TypeElement);
            if (TypeElement != -1) {
                jeu->element[jeu->nbElement].type = TypeElement;
                jeu->element[jeu->nbElement].x = MARGE_GAUCHE_DROITE + j * TAILLE_CASE;
                jeu->element[jeu->nbElement].y = MARGE_HAUT_BAS + i * TAILLE_CASE;
                jeu->nbElement++;
            }
        }
    }
    fclose(fichier);
}

void ChargerFichierTxt3(ComposantsJeu *jeu) {
    FILE *fichier = fopen("../images/FichierTexteNiveau3", "r");
    if (!fichier) {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier.\n");
        exit(EXIT_FAILURE);
    }

    jeu->element = malloc(NB_LIGNES * NB_COLONNES * sizeof(Element));
    jeu->nbElement = 0;
    int TypeElement;

    for (int i = 0; i < NB_LIGNES; ++i) {
        for (int j = 0; j < NB_COLONNES; ++j) {
            fscanf(fichier, "%d", &TypeElement);
            if (TypeElement != -1) {
                jeu->element[jeu->nbElement].type = TypeElement;
                jeu->element[jeu->nbElement].x = MARGE_GAUCHE_DROITE + j * TAILLE_CASE;
                jeu->element[jeu->nbElement].y = MARGE_HAUT_BAS + i * TAILLE_CASE;
                jeu->nbElement++;
            }
        }
    }
    fclose(fichier);
}

void AfficherFichierTxt(const ComposantsJeu *jeu) {
    for (int i = 0; i < jeu->nbElement; i++) {
        ALLEGRO_BITMAP *bitmap = NULL;
        switch (jeu->element[i].type) {
            case 0:
                bitmap = jeu->sol1;
                break;
            case 1:
                bitmap = jeu->sol2;
                break;
            case 2:
                bitmap = jeu->frigoCitron;
                break;
            case 3:
                bitmap = jeu->planDeTravail;
                break;
            case 4:
                bitmap = jeu->frigoMenthe;
                break;
            case 5:
                bitmap = jeu->frigoLimonade;
                break;
            case 6:
                bitmap = jeu->poubelle;
                break;
            case 7:
                bitmap = jeu->plaqueDeCuisson;
                break;
            case 8:
                bitmap = jeu->sortie;
                break;
            case 9:
                bitmap = jeu->stationDeDecoupe;
                break;
            case 10:
                bitmap = jeu->presseAgrume;
                break;
            case 11:
                bitmap = jeu->frigoCanneASucre;
                break;
            case 12:
                bitmap = jeu->tapisRoulantDoite;
                break;
            case 13:
                bitmap = jeu->tapisRoulantBas;
                break;
            case 14:
                bitmap = jeu->tapisRoulantHaut;
                break;
            case 15:
                bitmap = jeu->tapisRoulantGauche;
                break;
            case 16:
                bitmap = jeu->distributeurVerres;
                break;
        }
        if (bitmap) {
            al_draw_bitmap(bitmap, jeu->element[i].x, jeu->element[i].y, 0);
        }
    }
}

void InitialiserComposantsJeu(ComposantsJeu *jeu) {
    memset(jeu->elementsLaches, 0, sizeof(jeu->elementsLaches));
    jeu->nbElementsLaches = 0;
}

void DessinerElementsLaches(ComposantsJeu *jeu) {
    //printf("Nombre d'elements a dessiner: %d\n", jeu->nbElementsLaches);

    if (jeu->nbElementsLaches > 0) {
        for (int i = 0; i < jeu->nbElementsLaches; i++) {
            //printf("element %d : x=%d, y=%d, visible=%d\n", i, jeu->elementsLaches[i].x, jeu->elementsLaches[i].y, jeu->elementsLaches[i].estVisible);
            if (jeu->elementsLaches[i].estVisible) {
                al_draw_bitmap(jeu->elementsLaches[i].image, jeu->elementsLaches[i].x, jeu->elementsLaches[i].y, 0);
            }
        }
    }
}

Element *CreerElement(int type, ALLEGRO_BITMAP *image, int ingredientID, int recetteID) {
    Element *nouvElement = malloc(sizeof(Element));
    if (nouvElement != NULL) {
        nouvElement->type = type;
        nouvElement->image = image;
        nouvElement->ingredientID = ingredientID;
        nouvElement->recetteID = recetteID;
    }
    return nouvElement;
}

ElementsLaches *TrouverElementProche(Joueur *joueur, ComposantsJeu *jeu) {

    float cx = al_get_bitmap_width(joueur->image) / 2 + joueur->x;
    float cy = al_get_bitmap_height(joueur->image) / 2 + joueur->y;
    float xCurseur = cx + cos(joueur->angle) * DISTANCEINTERACTION;
    float yCurseur = cy + sin(joueur->angle) * DISTANCEINTERACTION;

    for (int j = 0; j < jeu->nbElementsLaches; j++) {
        ElementsLaches *lache = &jeu->elementsLaches[j];
        if (lache->estVisible && xCurseur >= lache->x && xCurseur <= lache->x + TAILLE_CASE &&
            yCurseur >= lache->y && yCurseur <= lache->y + TAILLE_CASE) {
            return lache;
        }
    }
    return NULL;
}

bool EstSurPoubelle(ComposantsJeu *jeu, float x, float y) {
    for (int i = 0; i < jeu->nbElement; i++) {
        if (jeu->element[i].type == TYPE_POUBELLE &&
            x >= jeu->element[i].x && x <= jeu->element[i].x + TAILLE_CASE &&
            y >= jeu->element[i].y && y <= jeu->element[i].y + TAILLE_CASE) {
            return true;
        }
    }
    return false;
}

bool EstSurSortie(ComposantsJeu *jeu, float x, float y) {
    for (int i = 0; i < jeu->nbElement; i++) {
        if ((jeu->element[i].type == TYPE_SORTIE) &&
            x >= jeu->element[i].x && x <= jeu->element[i].x + TAILLE_CASE &&
            y >= jeu->element[i].y && y <= jeu->element[i].y + TAILLE_CASE) {
            return true;
        }
    }
    return false;
}

int EstSurTapisRoulant(ComposantsJeu *jeu, float x, float y) {
    for (int i = 0; i < jeu->nbElement; i++) {
        if ((jeu->element[i].type == 12 || jeu->element[i].type == 13 || jeu->element[i].type == 14 ||
             jeu->element[i].type == 15) &&
            x >= jeu->element[i].x && x <= jeu->element[i].x + TAILLE_CASE &&
            y >= jeu->element[i].y && y <= jeu->element[i].y + TAILLE_CASE) {
            if (jeu->element[i].type == 12) return DIRECTION_DROITE;
            if (jeu->element[i].type == 13) return DIRECTION_BAS;
            if (jeu->element[i].type == 14) return DIRECTION_HAUT;
            if (jeu->element[i].type == 15) return DIRECTION_GAUCHE;
        }
    }
    return -1;
}

void mettreAJourTapisRoulant(ComposantsJeu *jeu, bool *maj) {
    for (int i = 0; i < jeu->nbElementsLaches; i++) {
        ElementsLaches *elem = &jeu->elementsLaches[i];
        int directionActuelle = EstSurTapisRoulant(jeu, elem->x, elem->y);
        if (directionActuelle != -1 && elem->estVisible) {
            float originalX = elem->x, originalY = elem->y;
            switch (directionActuelle) {
                case DIRECTION_HAUT:
                    elem->y -= VITESSE_TAPIS_ROULANT;
                    break;
                case DIRECTION_BAS:
                    elem->y += VITESSE_TAPIS_ROULANT;
                    break;
                case DIRECTION_GAUCHE:
                    elem->x -= VITESSE_TAPIS_ROULANT;
                    break;
                case DIRECTION_DROITE:
                    elem->x += VITESSE_TAPIS_ROULANT;
                    break;
                default:
                    break;
            }
            *maj = true;
            int nouvelleDirection = EstSurTapisRoulant(jeu, elem->x, elem->y);
            if (nouvelleDirection == -1) {
                if (EstSurPoubelle(jeu, elem->x, elem->y)) {
                    elem->estVisible = false;
                } else {
                    elem->x = originalX;
                    elem->y = originalY;
                }
            }
        }
    }
}

bool VerifierEtTraiterSortie(Commande **listeDeCommandes, Joueur *joueur, ComposantsJeu *jeu) {
    if (joueur->element == NULL) {
        return false;
    }

    if (EstSurSortie(jeu, joueur->element->x, joueur->element->y)) {
        Commande *current = *listeDeCommandes;
        while (current) {
            if (current->recette->id == joueur->element->recetteID && !current->estCompletee) {

                float tempsRestantRatio = (float) current->timer / (float) current->timerInitial;
                int scoreAdditionnel = (int) (current->score * tempsRestantRatio);
                current->estCompletee = true;
                joueur->score += scoreAdditionnel;
                free(joueur->element);
                joueur->element = NULL;
                return true;
            }
            current = current->suivant;
        }
    }
    return false;
}

void centrerObjetSurPlan(Element *element, ComposantsJeu *jeu) {
    int posX, posY;

    for (int i = 0; i < jeu->nbElement; i++) {
        if (jeu->element[i].type == TYPE_PLANDETRAVAIL || jeu->element[i].type == TYPE_STATIONDEDECOUPE ||
            jeu->element[i].type == TYPE_PLAQUEDECUISSON || jeu->element[i].type == TYPE_SORTIE) {
            posX = jeu->element[i].x + TAILLE_CASE / 2;
            posY = jeu->element[i].y + TAILLE_CASE / 2;

            if (element->x >= jeu->element[i].x && element->x <= jeu->element[i].x + TAILLE_CASE &&
                element->y >= jeu->element[i].y && element->y <= jeu->element[i].y + TAILLE_CASE) {
                element->x = posX;
                element->y = posY;
                break;
            }
        }
    }
}

void PrendreOuLacherElement(Joueur *joueur, ComposantsJeu *jeu) {
    if (joueur->element == NULL) {
        ElementsLaches *elementProche = TrouverElementProche(joueur, jeu);
        if (elementProche != NULL && elementProche->estVisible) {
            joueur->element = malloc(sizeof(Element));
            if (joueur->element) {
                joueur->element->x = elementProche->x;
                joueur->element->y = elementProche->y;
                joueur->element->image = elementProche->image;
                joueur->element->ingredientID = elementProche->ingredientID;
                joueur->element->recetteID = elementProche->recetteID;
                elementProche->estVisible = false;
                int index = elementProche - jeu->elementsLaches;
                for (int i = index; i < jeu->nbElementsLaches - 1; i++) {
                    jeu->elementsLaches[i] = jeu->elementsLaches[i + 1];
                }
                jeu->nbElementsLaches--;
            }
        }
    } else {
        float cx = al_get_bitmap_width(joueur->image) / 2 + joueur->x;
        float cy = al_get_bitmap_height(joueur->image) / 2 + joueur->y;
        float xCurseur = cx + cos(joueur->angle) * DISTANCEINTERACTION;
        float yCurseur = cy + sin(joueur->angle) * DISTANCEINTERACTION;

        if (EstSurPoubelle(jeu, xCurseur, yCurseur)) {
            free(joueur->element);
            joueur->element = NULL;
        } else {
            joueur->element->x = xCurseur;
            joueur->element->y = yCurseur;
            centrerObjetSurPlan(joueur->element, jeu);
            jeu->elementsLaches[jeu->nbElementsLaches++] = (ElementsLaches) {
                    joueur->element->x - al_get_bitmap_width(joueur->element->image) / 2,
                    joueur->element->y - al_get_bitmap_height(joueur->element->image) / 2,
                    joueur->element->image, true, joueur->element->ingredientID, joueur->element->recetteID};
            free(joueur->element);
            joueur->element = NULL;

        }
    }
}

int VerifierCoffreDevant(ComposantsJeu *jeu, Joueur *joueur) {

    float cx = al_get_bitmap_width(joueur->image) / 2 + joueur->x;
    float cy = al_get_bitmap_height(joueur->image) / 2 + joueur->y;
    float xCurseur = cx + cos(joueur->angle) * DISTANCEINTERACTION;
    float yCurseur = cy + sin(joueur->angle) * DISTANCEINTERACTION;

    for (int i = 0; i < jeu->nbElement; ++i) {
        if ((jeu->element[i].type == TYPE_FRIGOCITRON || jeu->element[i].type == TYPE_FRIGOMENTHE ||
             jeu->element[i].type == TYPE_FRIGOLIMONADE ||
             jeu->element[i].type == TYPE_POUBELLE || jeu->element[i].type == TYPE_FRIGOCANNEASUCRE ||
             jeu->element[i].type == TYPE_SORTIE || jeu->element[i].type == 16) &&
            xCurseur >= jeu->element[i].x &&
            xCurseur <= jeu->element[i].x + TAILLE_CASE &&
            yCurseur >= jeu->element[i].y && yCurseur <= jeu->element[i].y + TAILLE_CASE) {
            //printf("Interaction avec un coffre de type %d\n", jeu->element[i].type);
            return jeu->element[i].type;
        }
    }
    //printf("Aucun coffre trouve\n");
    return -1;
}

void PrendreDansLeCoffre(Joueur *joueur, ComposantsJeu *jeu) {
    int typeCoffre = VerifierCoffreDevant(jeu, joueur);

    if (joueur->element == NULL || typeCoffre == 6) {
        switch (typeCoffre) {
            case 2:
                joueur->element = CreerElement(TYPE_FRIGOCITRON, jeu->citron, CITRON_PRESSE, RECETTE_NULL);
                break;
            case 4:
                joueur->element = CreerElement(TYPE_FRIGOMENTHE, jeu->menthe, MENTHE_DECOUPE, RECETTE_NULL);
                break;
            case 5:
                joueur->element = CreerElement(TYPE_FRIGOLIMONADE, jeu->limonade, LIMONADE, RECETTE_NULL);
                break;
            case 11:
                joueur->element = CreerElement(TYPE_FRIGOCANNEASUCRE, jeu->canneASucre, CANNE_A_SUCRE, RECETTE_NULL);
                break;
            case 16:
                joueur->element = CreerElement(16, jeu->verres, VERRE, RECETTE_NULL);
                break;
            default:
                break;
        }
    }
}

bool sontProches(ElementsLaches a, ElementsLaches b) {
    float distance = sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
    return distance <= RAYON_PROXIMITE;
}

void CombinaisonElementsRecette(ComposantsJeu *jeu, Recette recettes[], int nbRecettes) {
    bool combine[100] = {false};

    for (int i = 0; i < jeu->nbElementsLaches; i++) {
        if (!jeu->elementsLaches[i].estVisible || combine[i]) continue;

        for (int r = 0; r < nbRecettes; r++) {
            Recette *recette = &recettes[r];
            int count[5] = {0};
            int idxCombinables[100];
            int nbCombinables = 0;

            for (int j = 0; j < jeu->nbElementsLaches; j++) {
                if (jeu->elementsLaches[j].estVisible && !combine[j] &&
                    sontProches(jeu->elementsLaches[i], jeu->elementsLaches[j])) {
                    for (int ing = 0; ing < 5; ing++) {
                        if (recette->ingredients[ing] == jeu->elementsLaches[j].ingredientID && count[ing] < 1) {
                            count[ing]++;
                            idxCombinables[nbCombinables++] = j;
                            break;
                        }
                    }
                }
            }

            bool tousIngredientsTrouves = true;
            for (int ing = 0; ing < 5; ing++) {
                if (recette->ingredients[ing] != INGREDIENT_NULL && count[ing] < 1) {
                    tousIngredientsTrouves = false;
                    break;
                }
            }

            if (tousIngredientsTrouves) {
                for (int k = 0; k < nbCombinables; k++) {
                    combine[idxCombinables[k]] = true;
                    jeu->elementsLaches[idxCombinables[k]].estVisible = false;
                    for (int j = idxCombinables[k]; j < jeu->nbElementsLaches - 1; j++) {
                        jeu->elementsLaches[j] = jeu->elementsLaches[j + 1];
                    }
                    jeu->nbElementsLaches--;
                }

                ElementsLaches nouvelElement = {
                        .x = jeu->elementsLaches[i].x,
                        .y = jeu->elementsLaches[i].y,
                        .image = recette->image,
                        .estVisible = true,
                        .ingredientID = INGREDIENT_NULL,
                        .recetteID = recette->id
                };
                if (jeu->nbElementsLaches < 100) {
                    jeu->elementsLaches[jeu->nbElementsLaches++] = nouvelElement;
                }
                break;
            }
        }
    }
}

void DessinerTempsRestant(int tempsRestant, ComposantsJeu *jeu) {
    char text[10];
    sprintf(text, "%02d:%02d", tempsRestant / 60, tempsRestant % 60);

    float cx = al_get_bitmap_width(jeu->sablier) / 2.0;
    float cy = al_get_bitmap_height(jeu->sablier) / 2.0;
    float x = 1090 + cx;
    float y = 10 + cy;

    int secondesEcoulees = jeu->DureePartie - tempsRestant;
    float angle = (secondesEcoulees % 2) * M_PI;

    al_draw_rotated_bitmap(jeu->sablier, cx, cy, x, y, angle, 0);
    static bool couleurRouge = false;
    static int derniereSeconde = -1;

    if (tempsRestant > 30) {
        al_draw_text(jeu->policeRegle, NOIR, 1050, 20, ALLEGRO_ALIGN_CENTER, text);
        couleurRouge = false;
    } else {
        if (derniereSeconde != secondesEcoulees) {
            couleurRouge = !couleurRouge;
            derniereSeconde = secondesEcoulees;
        }
        ALLEGRO_COLOR couleurTexte = couleurRouge ? ROUGE : NOIR;
        al_draw_text(jeu->policeRegle, couleurTexte, 1050, 20, ALLEGRO_ALIGN_CENTER, text);
    }
}

void InitialiserPosJoueurs(Joueur *joueur1, Joueur *joueur2, int x1, int y1, int x2, int y2) {
    joueur1->x = x1;
    joueur1->y = y1;
    joueur2->x = x2;
    joueur2->y = y2;
}

void VerifierPosJoueur(Joueur *joueur) {
    int joueur_width = al_get_bitmap_width(joueur->image);
    int joueur_height = al_get_bitmap_height(joueur->image);

    if (joueur->x < MARGE_GAUCHE_DROITE) { joueur->x = MARGE_GAUCHE_DROITE; }
    if (joueur->x + joueur_width > DISPLAY_WIDTH - MARGE_GAUCHE_DROITE) {
        joueur->x =
                DISPLAY_WIDTH - MARGE_GAUCHE_DROITE -
                joueur_width;
    }
    if (joueur->y < MARGE_HAUT_BAS) { joueur->y = MARGE_HAUT_BAS; }
    if (joueur->y + joueur_height > DISPLAY_HEIGHT - MARGE_HAUT_BAS) {
        joueur->y = DISPLAY_HEIGHT - MARGE_HAUT_BAS -
                    joueur_height;
    }
}

bool VerifierCollisionJoueur(Joueur *joueur, ComposantsJeu *jeu) {
    int joueur_width = al_get_bitmap_width(joueur->image);
    int joueur_height = al_get_bitmap_height(joueur->image);

    for (int i = 0; i < jeu->nbElement; i++) {
        if (jeu->element[i].type != TYPE_SOL1 && jeu->element[i].type != TYPE_SOL2) {
            if (joueur->x <= jeu->element[i].x + TAILLE_CASE &&
                joueur->x + joueur_width >= jeu->element[i].x &&
                joueur->y <= jeu->element[i].y + TAILLE_CASE &&
                joueur->y + joueur_height >= jeu->element[i].y) {
                return true;
            }
        }
    }
    return false;
}

void MAJAngleJoueur(Joueur *joueur) {
    if (joueur->vx != 0 || joueur->vy != 0) {
        joueur->angle = atan2(joueur->vy, joueur->vx);
    }
}

void MAJPosJoueurs(Joueur *joueur1, Joueur *joueur2, ComposantsJeu *jeu, bool *maj) {
    int ancienXjoueur1 = joueur1->x, ancienYjoueur1 = joueur1->y;
    int ancienXjoueur2 = joueur2->x, ancienYjoueur2 = joueur2->y;

    if (joueur1->vx != 0 || joueur1->vy != 0) {
        joueur1->x += joueur1->vx;
        joueur1->y += joueur1->vy;
        MAJAngleJoueur(joueur1);
        if (VerifierCollisionJoueur(joueur1, jeu)) {
            joueur1->x = ancienXjoueur1;
            joueur1->y = ancienYjoueur1;
        }
        VerifierPosJoueur(joueur1);
        *maj = true;
    }
    if (joueur2->vx != 0 || joueur2->vy != 0) {
        joueur2->x += joueur2->vx;
        joueur2->y += joueur2->vy;
        MAJAngleJoueur(joueur2);
        if (VerifierCollisionJoueur(joueur2, jeu)) {
            joueur2->x = ancienXjoueur2;
            joueur2->y = ancienYjoueur2;
        }
        VerifierPosJoueur(joueur2);
        *maj = true;
    }
}

void DessinerCurseurP(Joueur *joueur) {

    float cx = al_get_bitmap_width(joueur->image) / 2 + joueur->x;
    float cy = al_get_bitmap_height(joueur->image) / 2 + joueur->y;
    float xCurseur = cx + cos(joueur->angle) * DISTANCEINTERACTION;
    float yCurseur = cy + sin(joueur->angle) * DISTANCEINTERACTION;

    ALLEGRO_COLOR couleurCurseur = al_map_rgb(0, 255, 0);
    al_draw_filled_circle(xCurseur, yCurseur, 5, couleurCurseur);

    al_draw_line(cx, cy, xCurseur, yCurseur, couleurCurseur, 2.0);
}

void DessinerJoueur(Joueur *joueur, ComposantsJeu *jeu) {
    float cx = al_get_bitmap_width(joueur->image) / 2;
    float cy = al_get_bitmap_height(joueur->image) / 2;
    al_draw_rotated_bitmap(joueur->image, cx, cy, joueur->x + cx, joueur->y + cy, joueur->angle, 0);

    //DessinerCurseurP(joueur);

    if (joueur->element) {
        float xCurseur =
                joueur->x + cx + cos(joueur->angle) * DISTANCEINTERACTION;
        float yCurseur = joueur->y + cy + sin(joueur->angle) * DISTANCEINTERACTION;
        al_draw_bitmap(joueur->element->image, xCurseur - al_get_bitmap_width(joueur->element->image) / 2, yCurseur -
                                                                                                           al_get_bitmap_height(
                                                                                                                   joueur->element->image) /
                                                                                                           2, 0);
    }

    float text_x = joueur->x + cx;
    float text_y = joueur->y - al_get_font_ascent(jeu->policePseudo);
    al_draw_text(jeu->policePseudo, BLANC, text_x, text_y, ALLEGRO_ALIGN_CENTER, joueur->pseudo);
}

void GestionKeyDown(ComposantsJeu *jeu, Joueur *joueur1, Joueur *joueur2, ALLEGRO_EVENT *event, bool *maj) {
    if (!jeu->enPause) {
        switch (event->keyboard.keycode) {
            case ALLEGRO_KEY_Z:
                joueur1->vy = -2;
                *maj = true;
                break;
            case ALLEGRO_KEY_S:
                joueur1->vy = 2;
                *maj = true;
                break;
            case ALLEGRO_KEY_Q:
                joueur1->vx = -2;
                *maj = true;
                break;
            case ALLEGRO_KEY_D:
                joueur1->vx = 2;
                *maj = true;
                break;
            case ALLEGRO_KEY_UP:
                joueur2->vy = -2;
                *maj = true;
                break;
            case ALLEGRO_KEY_DOWN:
                joueur2->vy = 2;
                *maj = true;
                break;
            case ALLEGRO_KEY_LEFT:
                joueur2->vx = -2;
                *maj = true;
                break;
            case ALLEGRO_KEY_RIGHT:
                joueur2->vx = 2;
                *maj = true;
                break;
            case ALLEGRO_KEY_C:
            case ALLEGRO_KEY_L:
                //bool vérifie la collision entre objet et joeur si true prendre
                break;

            case ALLEGRO_KEY_V:
            case ALLEGRO_KEY_M:
                //bool vérifie la collision entre objet et joeur si true lacher
                break;
        }
    }
}

void GestionKeyUP(ComposantsJeu *jeu, Joueur *joueur1, Joueur *joueur2, ALLEGRO_EVENT *event, bool *maj) {
    if (!jeu->enPause) {

        switch (event->keyboard.keycode) {
            case ALLEGRO_KEY_Z:
            case ALLEGRO_KEY_S:
                joueur1->vy = 0;
                *maj = true;
                break;
            case ALLEGRO_KEY_Q:
            case ALLEGRO_KEY_D:
                joueur1->vx = 0;
                *maj = true;
                break;
            case ALLEGRO_KEY_UP:
            case ALLEGRO_KEY_DOWN:
                joueur2->vy = 0;
                *maj = true;
                break;
            case ALLEGRO_KEY_RIGHT:
            case ALLEGRO_KEY_LEFT:
                joueur2->vx = 0;
                *maj = true;
                break;
            case ALLEGRO_KEY_P:
                jeu->enPause = !jeu->enPause;
                *maj = true;
                break;
            case ALLEGRO_KEY_C:
                PrendreOuLacherElement(joueur1, jeu);
                PrendreDansLeCoffre(joueur1, jeu);
                *maj = true;
                break;
            case ALLEGRO_KEY_L:
                PrendreOuLacherElement(joueur2, jeu);
                PrendreDansLeCoffre(joueur2, jeu);
                *maj = true;
                break;
        }
    } else {
        switch (event->keyboard.keycode) {
            case ALLEGRO_KEY_P:
                jeu->enPause = !jeu->enPause;
                *maj = true;
                break;
        }
    }
}

void ChargerImagesCommandes(ImagesCommandes *images) {
    images->imagesVerres[MOJITO] = al_load_bitmap("../images/mojito.png");
    images->imagesVerres[CAIPIRINHA] = al_load_bitmap("../images/caipirinha.png");
    images->imagesVerres[HINTZY] = al_load_bitmap("../images/hintzy.png");
    images->imagesVerres[PLAZA] = al_load_bitmap("../images/plaza.png");

    images->imageFondCommande = al_load_bitmap("../images/pierre.png");

    images->imagesIngredients[MOJITO] = al_load_bitmap("../images/MOJITO_COMMANDE.png");
    images->imagesIngredients[CAIPIRINHA] = al_load_bitmap("../images/CAIPIRINHA_COMMANDE.png");
    images->imagesIngredients[HINTZY] = al_load_bitmap("../images/HINTZY_COMMANDE.png");

    images->imagesIngredients[INGREDIENT_NULL] = NULL;
}

void InitialiserRecettes(Recette recettes[], ComposantsJeu *jeu) {
    recettes[MOJITO].id = MOJITO;
    recettes[MOJITO].ingredients[0] = CITRON_PRESSE;
    recettes[MOJITO].ingredients[1] = CANNE_A_SUCRE;
    recettes[MOJITO].ingredients[2] = MENTHE_DECOUPE;
    recettes[MOJITO].ingredients[3] = LIMONADE;
    recettes[MOJITO].ingredients[4] = VERRE;
    recettes[MOJITO].ingredients[5] = INGREDIENT_NULL;
    recettes[MOJITO].image = jeu->mojito;
    strcpy(recettes[MOJITO].nom, "Mojito");

    recettes[CAIPIRINHA].id = CAIPIRINHA;
    recettes[CAIPIRINHA].ingredients[0] = CITRON_PRESSE;
    recettes[CAIPIRINHA].ingredients[1] = CANNE_A_SUCRE;
    recettes[CAIPIRINHA].ingredients[2] = VERRE;
    recettes[CAIPIRINHA].ingredients[3] = LIMONADE;
    recettes[CAIPIRINHA].ingredients[4] = INGREDIENT_NULL;
    recettes[MOJITO].ingredients[5] = INGREDIENT_NULL;
    recettes[CAIPIRINHA].image = jeu->caipirinha;
    strcpy(recettes[CAIPIRINHA].nom, "Caipirinha");

    recettes[HINTZY].id = HINTZY;
    recettes[HINTZY].ingredients[0] = LIMONADE;
    recettes[HINTZY].ingredients[1] = MENTHE_DECOUPE;
    recettes[HINTZY].ingredients[2] = CITRON_PRESSE;
    recettes[HINTZY].ingredients[3] = VERRE;
    recettes[HINTZY].ingredients[4] = INGREDIENT_NULL;
    recettes[MOJITO].ingredients[5] = INGREDIENT_NULL;
    recettes[HINTZY].image = jeu->hintzy;
    strcpy(recettes[CAIPIRINHA].nom, "Hintzy");
}

void InitialiserCommandes(Commande **listeDeCommandes, Recette recettes[]) {
    Commande *premiereCommande = (Commande *) malloc(sizeof(Commande));
    if (premiereCommande == NULL) return;

    premiereCommande->recette = &recettes[MOJITO];
    premiereCommande->nombre_ingredients = 4;
    premiereCommande->timer = 45;
    premiereCommande->timerInitial = 45;
    premiereCommande->score = 20;
    premiereCommande->estCompletee = false;
    premiereCommande->suivant = NULL;

    Commande *deuxiemeCommande = (Commande *) malloc(sizeof(Commande));
    if (deuxiemeCommande == NULL) return; // Échec de l'allocation

    deuxiemeCommande->recette = &recettes[CAIPIRINHA];
    deuxiemeCommande->nombre_ingredients = 2;
    deuxiemeCommande->timer = 35;
    deuxiemeCommande->timerInitial = 35;
    deuxiemeCommande->score = 15;
    deuxiemeCommande->estCompletee = false;
    deuxiemeCommande->suivant = NULL;

    Commande *troisiemeCommande = (Commande *) malloc(sizeof(Commande));
    if (troisiemeCommande == NULL) return;

    troisiemeCommande->recette = &recettes[HINTZY];
    troisiemeCommande->nombre_ingredients = 3; // Supposons qu'il y a 3 ingrédients pour simplifier
    troisiemeCommande->timer = 45;
    troisiemeCommande->timerInitial = 45;
    troisiemeCommande->score = 25;
    troisiemeCommande->estCompletee = false;
    troisiemeCommande->suivant = NULL;

    premiereCommande->suivant = deuxiemeCommande;
    deuxiemeCommande->suivant = troisiemeCommande;

    *listeDeCommandes = premiereCommande;
}

void AjouterCommande(Commande **liste, Commande *nouvelle) {
    Commande *temp = *liste;
    if (temp == NULL) {
        *liste = nouvelle;
    } else {
        while (temp->suivant != NULL) {
            temp = temp->suivant;
        }
        temp->suivant = nouvelle;
    }
}

Commande *CreerCommandeAleatoire(Recette recettes[]) {
    Commande *nouvelle = (Commande *) malloc(sizeof(Commande));
    if (nouvelle == NULL) return NULL;

    // Choisir une recette aléatoire parmi les recettes disponibles
    int recette_index = rand() % 3;  // Adaptez ce nombre au nombre de recettes que vous avez
    nouvelle->recette = &recettes[recette_index];

    // Compter le nombre d'ingrédients non-nuls
    int count = 0;
    for (int i = 0; i < 5; i++) {
        if (nouvelle->recette->ingredients[i] != INGREDIENT_NULL) {
            count++;
        }
    }

    nouvelle->nombre_ingredients = count;
    nouvelle->timer = (rand() % (40 - 30 + 1)) + 10;
    nouvelle->timerInitial = nouvelle->timer;
    nouvelle->score = 10 + rand() % 31;
    nouvelle->estCompletee = false;
    nouvelle->suivant = NULL;

    return nouvelle;
}

void TraiterCommandes(Commande **listeDeCommandes, Recette recettes[]) {
    Commande *current = *listeDeCommandes, *prev = NULL;
    while (current != NULL) {
        if (current->timer > 0) {
            current->timer--;  // Décrémenter le timer seulement si la commande n'est pas encore complétée
        }
        if (current->timer <= 0 || current->estCompletee) {  // Temps écoulé ou commande complétée
            Commande *aSupprimer = current;
            if (prev == NULL) {
                *listeDeCommandes = current->suivant;
            } else {
                prev->suivant = current->suivant;
            }
            current = current->suivant;

            //free(aSupprimer->recette->ingredients);  // Supposer que vous avez besoin de libérer cela, sinon ignorez
            free(aSupprimer);

            // Ajouter une nouvelle commande aléatoire
            Commande *nouvelleCommande = CreerCommandeAleatoire(recettes);
            AjouterCommande(listeDeCommandes, nouvelleCommande);
        } else {
            prev = current;
            current = current->suivant;
        }
    }
}

void DessinerCommande(ComposantsJeu *jeu, Commande *commande, ImagesCommandes *images, float x, float y) {
    if (!commande || !images) { return; }
    if (images->imageFondCommande) {
        al_draw_bitmap(images->imageFondCommande, x, y, 0);
    }

    ALLEGRO_BITMAP *image = images->imagesVerres[commande->recette->id];
    if (image) {
        al_draw_bitmap(image, x, y, 0);
    }

    ALLEGRO_BITMAP *imageIngredients = images->imagesIngredients[commande->recette->id];
    if (imageIngredients) {
        al_draw_bitmap(imageIngredients, x + al_get_bitmap_width(image) + 10, -15, 0);
    }

    float barWidth = al_get_bitmap_width(image);
    float barHeight = 10;
    float barX = x;
    float barY = y + al_get_bitmap_height(image) + 5;
    float proportion = (float) commande->timer / (float) commande->timerInitial;
    al_draw_filled_rectangle(barX, barY, barX + barWidth * proportion, barY + barHeight, al_map_rgb(255, 0, 0));
    al_draw_rectangle(barX, barY, barX + barWidth, barY + barHeight, BLANC, 1.0);
}

void DessinerToutesLesCommandes(ComposantsJeu *jeu, Commande *listeDeCommandes, ImagesCommandes *images) {
    float x = 20;
    float y = 5;
    float espacement = 180;

    Commande *current = listeDeCommandes;
    while (current) {
        DessinerCommande(jeu, current, images, x, y);
        x += al_get_bitmap_width(images->imagesVerres[current->recette->id]) + espacement;
        current = current->suivant;
    }
}

void SauvegarderScores(const Scores *scores) {
    FILE *f = fopen("../images/scores", "w");
    if (f == NULL) {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier de scores pour écriture.\n");
        return;
    }
    for (int i = 0; i < NOMBRE_NIVEAUX; i++) {
        fprintf(f, "%d, %d, %d\n", i + 1, scores->niveaux[i].meilleurScoreJoueur,
                scores->niveaux[i].meilleurScoreEquipe);
    }
    fclose(f);
}

void ChargerScores(Scores *scores) {
    FILE *f = fopen("../images/scores", "r");
    if (f == NULL) {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier de scores.\n");
        return;
    }
    int niveau, scoreJoueur, scoreEquipe;
    while (fscanf(f, "%d, %d, %d", &niveau, &scoreJoueur, &scoreEquipe) == 3) {
        if (niveau >= 1 && niveau <= NOMBRE_NIVEAUX) {
            scores->niveaux[niveau - 1].meilleurScoreJoueur = scoreJoueur;
            scores->niveaux[niveau - 1].meilleurScoreEquipe = scoreEquipe;
        }
    }

    fclose(f);
}

void VerifierEtMAJScores(Scores *scores, int niveauIndex, Joueur *joueur1, Joueur *joueur2) {
    bool doitSauvegarder = false;
    int meilleurScoreJoueur = (joueur1->score > joueur2->score) ? joueur1->score : joueur2->score;

    if (meilleurScoreJoueur > scores->niveaux[niveauIndex].meilleurScoreJoueur) {
        scores->niveaux[niveauIndex].meilleurScoreJoueur = meilleurScoreJoueur;
        doitSauvegarder = true;
    }

    int scoreEquipe = joueur1->score + joueur2->score;
    if (scoreEquipe > scores->niveaux[niveauIndex].meilleurScoreEquipe) {
        scores->niveaux[niveauIndex].meilleurScoreEquipe = scoreEquipe;
        doitSauvegarder = true;
    }

    if (doitSauvegarder) {
        SauvegarderScores(scores);
    }
}

void libererCommandes(Commande *liste) {
    while (liste != NULL) {
        Commande *temp = liste;
        liste = liste->suivant;
        free(temp->ingredients);
        free(temp);
    }
}
