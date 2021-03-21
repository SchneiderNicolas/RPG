/*
** EPITECH PROJECT, 2020
** my_defender
** File description:
** menu.c
*/

#include "../../include/game.h"
#include "../../include/macro.h"
#include "../../include/prototype.h"

int which_dialogue_3(gui_t *g, unsigned int x, unsigned int y)
{
    g->map_check = sfImage_getPixel(g->map, x, y);
    if (g->map_check.r == 254 && g->map_check.g == 255 && g->map_check.b == 1)
        return (7);
    if (g->map_check.r == 96 && g->map_check.g == 57 && g->map_check.b == 18)
        return (8);
    if (g->map_check.r == 0 && g->map_check.g == 84 && g->map_check.b == 165 &&
        g->adv >= 1)
        return (10);
    if (g->map_check.r == 0 && g->map_check.g == 84 && g->map_check.b == 165)
        return (9);
    if (g->map_check.r == 167 && g->map_check.g == 0 && g->map_check.b == 254)
        return (11);
    if (g->map_check.r == 154 && g->map_check.g == 135 && g->map_check.b == 120)
        return (12);
    else
        return (0);
}

int which_dialogue_2(gui_t *g, unsigned int x, unsigned int y)
{
    g->map_check = sfImage_getPixel(g->map, x, y);
    if (g->map_check.r == 255 && g->map_check.g == 0 && g->map_check.b == 216)
        return (1);
    if (g->map_check.r == 243 && g->map_check.g == 101 && g->map_check.b == 35
        && g->adv >= 2)
        return (3);
    if (g->map_check.r == 243 && g->map_check.g == 101 && g->map_check.b == 35)
        return (2);
    if (g->map_check.r == 0 && g->map_check.g == 255 && g->map_check.b == 244)
        return (4);
    if (g->map_check.r == 255 && g->map_check.g == 193 && g->map_check.b == 0
        && g->inventory->nb_iron >= 6) {
        g->inventory->armor2 = TRUE;
        g->inventory->iron = FALSE;
        return (6);
    }
    if (g->map_check.r == 255 && g->map_check.g == 193 && g->map_check.b == 0)
        return (5);
    else
        return (0);
}

int which_dialogue(gui_t *g, unsigned int x, unsigned int y)
{
    int save = which_dialogue_2(g, x, y);
    g->map_check = sfImage_getPixel(g->map, x, y);
    if (save != 0)
        return (save);
    save = which_dialogue_3(g, x, y);
    if (save != 0)
        return (save);
    if ((g->map_check.r == 147 && g->map_check.g == 38 && g->map_check.b == 143
        || g->map_check.r == 237 && g->map_check.g == 22 && g->map_check.b == 90
        || g->map_check.r == 0 && g->map_check.g == 166 && g->map_check.b == 80)
        && g->inventory->nb_iron >= 6)
        return (14);
    if (g->map_check.r == 147 && g->map_check.g == 38 && g->map_check.b == 143
        || g->map_check.r == 237 && g->map_check.g == 22 && g->map_check.b == 90
        || g->map_check.r == 0 && g->map_check.g == 166 && g->map_check.b == 80)
        return (13);
    else {
        return (0);
    }
}

int chose_diag(gui_t *g)
{
    int index = 0;

    if (g->player->sprite[g->player->status + (g->player->lvl * 2)]->rect.top
        == 720 && index == 0) {
        index = which_dialogue(g, g->player->pos_x + 50, g->player->pos_y);
    }
    if (g->player->sprite[g->player->status + (g->player->lvl * 2)]->rect.top
        == 480 && index == 0) {
        index = which_dialogue(g, g->player->pos_x - 50, g->player->pos_y);
    }
    if (g->player->sprite[g->player->status + (g->player->lvl * 2)]->rect.top
        == 0 && index == 0) {
        index = which_dialogue(g, g->player->pos_x, g->player->pos_y - 50);
    }
    if (g->player->sprite[g->player->status + (g->player->lvl * 2)]->rect.top
        == 240 && index == 0) {
        index = which_dialogue(g, g->player->pos_x, g->player->pos_y + 50);
    }
    return (index);
}

int speak_to_pnj(gui_t *g)
{
    int com[] = {PNJ_BEGIN, PNJ_ARMOR_BEFORE, PNJ_ARMOR_AFTER, PNJ_ENTRY_VILLAGE
        , FORGERON_MISSION, FORGERON_MISSION_COMPLETE, MARCHAND,
        PNJ_FORET_BRULEE, FIRST_BATTLE_BEFORE, FIRST_BATTLE_AFTER,
        ALWAYS_BATTLE, BOSS_FINAL, MINEUR, END_MINEUR};
    int index = chose_diag(g);
    static int j = 0;

    if (j == 0 && g->info->sound == TRUE) {
        sfMusic_stop(g->music[PNJ_SOUND]);
        sfMusic_play(g->music[PNJ_SOUND]);
        j = 1;
    }
    for (int i = 0; i < 14; i++) {
        if (index == com[i]) {
            g->diag = com[i] + (g->lang * 15);
            j = 0;
            return (1);
        }
    }
}