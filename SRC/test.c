/*
** EPITECH PROJECT, 2017
** test CSML
** File description:
** test
*/

#include <SFML/Graphics.h>
#include <SFML/Audio.h>
#include <SFML/System.h>
#include <SFML/Window.h>
#include <stdlib.h>
#include "my.h"
#define TRUE 1
#define ERROR 84

int my_putstr(char *str);
void help();

int main(int ac, char **av)
{
	if (av[1] != NULL) {
		help();
		return(0);
	}

	int a;
	int b = 0;
	int z = 0;
	int end = 0;
	sfRenderWindow *window;
	sfEvent event;
	sfVideoMode video_mode;
	sfTexture *texture;
	sfTexture *texturePeng;
	sfSprite *sprite;
	sfSprite *spritePeng;
	sfMusic *music;
	sfVector2f vitesse;
	sfVector2f position;
	sfClock *clock;
	sfTime time;
	float seconds;
	float x = 0;
	sfIntRect rect = {0, 0, 128, 128};

	sfTexture *cursor_texture;
	sfSprite *cursor;
	sfVector2i mouse;
	sfVector2f position_cursor;
	int cursor_x;
	int cursor_y;

	sfVector2f position_sprite;
	int score = 0;
	int sprite_x_max;
	int sprite_x_min;
	int sprite_y_max;
	int sprite_y_min;

	video_mode.width = 800;
	video_mode.height = 600;
	video_mode.bitsPerPixel = 32;
	window = sfRenderWindow_create(video_mode,"Space Ship",sfDefaultStyle, NULL);
	sfRenderWindow_setMouseCursorVisible(window, sfFalse);
	sfRenderWindow_setFramerateLimit(window, 10000);

	vitesse.x = 0.5;
	position.x = 0;

	music = sfMusic_createFromFile("msc/MattashiTheFinalBattle.wav");
	if (!music) {
		my_putstr("music no found");		
		return (ERROR);
	}
	sfMusic_play(music);
	sfMusic_setLoop(music, sfTrue);

	texture = sfTexture_createFromFile("img/Island.png", NULL);
	if (!texture) {
		my_putstr("texture no found");		
		return (ERROR);
	}
	sprite = sfSprite_create();

	texturePeng = sfTexture_createFromFile("img/SpaceShip2.png", NULL);
	if (!texturePeng) {
		my_putstr("texturePeng no found");		
		return (ERROR);
	}
	spritePeng = sfSprite_create();
	sfSprite_setTexture(spritePeng, texturePeng, sfTrue);

	clock = sfClock_create();

	cursor_texture = sfTexture_createFromFile("img/Cursor2.png",NULL);
	if (!cursor_texture) {
		my_putstr("cursor_texture no found");
		return (ERROR);
	}

	cursor = sfSprite_create();
	sfSprite_setTexture(cursor,cursor_texture, sfTrue);
	sfRenderWindow_setMouseCursorVisible(window, sfFalse);

	position_sprite = sfSprite_getPosition(spritePeng);
	
	while (sfRenderWindow_isOpen(window))
	{
		while (sfRenderWindow_pollEvent(window, &event)) {
			if (event.type == sfEvtClosed) {
				sfRenderWindow_close(window);
				my_putstr("RAGE QUIT ?\n");
				my_putstr("score = ");
				my_put_nbr(score);
			}
			if (sfKeyboard_isKeyPressed(sfKeyEscape) == TRUE)
				sfRenderWindow_close(window);
		}

		sfSprite_setTexture(sprite, texture, sfTrue);
		sfRenderWindow_drawSprite(window, sprite, NULL);
		sfRenderWindow_drawSprite(window, spritePeng, NULL);
		sfSprite_move(spritePeng, vitesse);

		x++;
		if (x == 1920) {
			sfSprite_setPosition(spritePeng, position);
			x = 0;
			end++;
		}
		time = sfClock_getElapsedTime(clock);
		seconds = time.microseconds /1000000.0;
		if (seconds > 0.3) {
			a = a + 128;
			sfIntRect rect = {a, 0, 128, 128};
			if (a >= 620) {
				a = 0;
			}
			sfSprite_setTextureRect(spritePeng, rect);
			sfClock_restart(clock);
		}

		mouse = sfMouse_getPositionRenderWindow(window);
		cursor_x = mouse.x;
		cursor_y = mouse.y;
		position_cursor.x = cursor_x - 25;
		position_cursor.y = cursor_y - 25;
		sfSprite_setPosition(cursor,position_cursor);
		sfRenderWindow_drawSprite(window, cursor, NULL);
		while (sfRenderWindow_pollEvent(window, &event)) {
			if (event.type == sfEvtMouseButtonPressed && b == 0) {
				position_sprite = sfSprite_getPosition(spritePeng);
				sprite_x_max = position_sprite.x + 128;
				sprite_x_min = position_sprite.x + 0;
				sprite_y_max = position_sprite.y + 128;
				sprite_y_min = position_sprite.y + 0;
				if ((mouse.x > sprite_x_min && mouse.x < sprite_x_max) &&
				    (mouse.y > sprite_y_min && mouse.y < sprite_y_max)) {
					score ++;
					z = rand()%(300 - 100 + 1) + 100;
					position.y = z;
					vitesse.x = vitesse.x + 0.1;
					sfSprite_setPosition(spritePeng, position);
					b = 1;
				}
			}
			if (event.type == sfEvtMouseButtonReleased) {
				b = 0;
			}
			if (end == 3) {
				sfRenderWindow_close(window);
				my_putstr("GAME OVER !\n");
				my_putstr("score = ");
				my_put_nbr(score);
			}
		}
		sfRenderWindow_display(window);
	}

	sfRenderWindow_destroy(window);
	sfMusic_destroy(music);
	sfSprite_destroy(sprite);
	sfSprite_destroy(spritePeng);
	sfSprite_destroy(cursor);
	sfTexture_destroy(texture);
	sfTexture_destroy(texturePeng);
	sfTexture_destroy(cursor_texture);
	sfClock_destroy(clock);
	return(0);
}
