#include <stdlib.h>
#include <string.h>
#include "wom.h"

static int	menu_width = 0;

static int	draw_menu(int argc, char **argv)
{
	int		i = 0;
	char	*name;
	int		len;

	while (i < argc - 1)
	{
		if (!(name = get_name(argv[i + 1])))
			return (0);
		if ((len = strlen(name)) > menu_width)
			menu_width = len;
		mvprintw(i + OFFSET_Y, OFFSET_X, "%s", name);
		free(name);
		++i;
	}
	mvprintw(i + OFFSET_Y, OFFSET_X, "Quit");
	mvchgat(OFFSET_Y, OFFSET_X, menu_width, A_REVERSE, 0, NULL);
	refresh();
	return (1);
}

static int	move_choice(int i, int argc, int where)
{
	mvchgat(i + OFFSET_Y, OFFSET_X, menu_width, A_NORMAL, 0, NULL);
	if (where == KEY_DOWN)
		i = (i < argc - 1) ? i + 1 : 0;
	if (where == KEY_UP)
		i = (i > 0) ? i - 1 : argc - 1;
	mvchgat(i + OFFSET_Y, OFFSET_X, menu_width, A_REVERSE, 0, NULL);
	refresh();
	return (i);
}

static int	controls(int argc)
{
	int	c, i = 0;

	while ((c = getch()) != 'q')
	{
		if (c == KEY_DOWN)
			i = move_choice(i, argc, KEY_DOWN);
		else if (c == KEY_UP)
			i = move_choice(i, argc, KEY_UP);
		else if (c == KEY_RIGHT || c == 10) /* 10 = ENTER */
			return (i + 1);
	}
	return (-1);
}

int			main(int argc, char **argv)
{
	int		chosen_script = 0;
	char	*script;

	initscr();
	cbreak();
	noecho();
	keypad(stdscr, true);
	curs_set(0);
	refresh();
	if ((draw_menu(argc, argv)) != 0)
		chosen_script = controls(argc);
	refresh();
	curs_set(1);
	endwin();
	if (chosen_script > 0 && chosen_script < argc)
	{
		if ((script = ft_strjoin_f("sh ", argv[chosen_script], 0)))
		{
			system(script);
			free(script);
		}
	}
	return (EXIT_SUCCESS);
}
