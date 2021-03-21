/*
** EPITECH PROJECT, 2020
** RPG
** File description:
** fourth battle
*/

#include "../../include/game.h"
#include "../../include/macro.h"
#include "../../include/prototype.h"

int b4_event(gui_t *game)
{
    sfEvent e;

    while (sfRenderWindow_pollEvent(game->window, &e)) {
        if (e.type == sfEvtClosed) {
            sfRenderWindow_close(game->window);
        }
        if (e.type == sfEvtMouseButtonPressed && game->battle4->status
        == PLAYER_TURN) {
            game->info->mouse->click = TRUE;
            b_attack(game, e.mouseButton, game->battle4);
            b_boostattack(game, e.mouseButton, game->battle4);
            b_escape(game, e.mouseButton, game->battle4);
        } else {
            game->info->mouse->click = FALSE;
        }
    }
    return (1);
}

int b4_display(gui_t *game)
{
    if (game->info->trans == TRUE)
        transition(game);
    displayer(game->window, game->object[BG_BATTLE]);
    for (int i = BUTTON_ATTACK; i <= HEAL_GREEN_ENEMIES; i++) {
        displayer(game->window, game->object[i]);
    }
    display_status_4(game);
    if (game->info->trans == TRUE)
        transition(game);
    return (1);
}

int b4_update(gui_t *g)
{
    if (g->battle4->start == 1) {
        g->object[HEAL_GREEN_ENEMIES]->position = (sfVector2f){.x = 1005,
        .y = 56};
        g->object[HEAL_GREEN_ENEMIES]->rect = (sfIntRect){0, 0, 490, 87};
        g->object[HEAL_GREEN_PLAYER]->rect = (sfIntRect){0, 0, 490 *
        (g->player->pv / g->player->pv_max), 87};
        g->player->next_attack = g->player->attack;
        g->battle4->start = 0;
    }
    for (int i = BUTTON_ATTACK; i <= HEAL_GREEN_ENEMIES; i++) {
        sfSprite_setTextureRect(g->object[i]->sprite, g->object[i]->rect);
    }
    if (g->battle4->status == PLAYER_TURN) {
        b_mouse(g, g->object[BUTTON_ATTACK]);
        b_mouse(g, g->object[BUTTON_BOOSTATTACK]);
        b_mouse(g, g->object[BUTTON_ESCAPE]);
        update_player_turn_4(g);
    }
    update_different_status_4(g);
    return (1);
}

int loop_battle4_2(gui_t *game)
{
    double elapsed2 = 0;
    elapsed2 = sfTime_asMilliseconds(sfClock_getElapsedTime(game->dispTimer));
    if (elapsed2 >= (1.0 / 30.0) * 1000.0) {
        sfRenderWindow_clear(game->window, sfBlack);
        sfClock_restart(game->dispTimer);
        if (!b4_display(game))
            return (0);
        sfRenderWindow_display(game->window);
    }
    return (1);
}

int loop_battle_4(gui_t *game)
{
    double elapsed1 = 0;

    sfRenderWindow_setMouseCursorVisible(game->window, sfTrue);
    sfRenderWindow_setView(game->window, game->info->view);
    if (!b4_event(game))
        return (0);
    elapsed1 = sfTime_asMicroseconds(sfClock_getElapsedTime(game->updateTimer))
                    + game->info->updateRest;
    sfClock_restart(game->updateTimer);
    while (elapsed1 >= (1.0 / 60.0) * 100000.0) {
        if (!b4_update(game))
            return (0);
        elapsed1 -= (1.0 / 60.0) * 100000.0;
    }
    game->info->updateRest = elapsed1;
    if (!loop_battle4_2(game)) {
        return (0);
    }
    return (1);
}