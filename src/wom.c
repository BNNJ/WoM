#include "wom.h"

static int	menu_width;
static int	offset_x;
static int	offset_y;

static int	get_sizes(char **entries, int nb_entries)
{
	int		i = 0;
	char	*name;
	int		len;

	getmaxyx(stdscr, offset_y, offset_x);
	menu_width = 0;
	while (i < nb_entries)
	{
		if (!(name = get_name(entries[i])))
			return (0);
		if ((len = strlen(name)) > menu_width)
			menu_width = len;
		free(name);
		++i;
	}
	offset_x = (offset_x - menu_width) / 2;
	offset_y = (offset_y - nb_entries + 1) / 2;
	return (1);
}

static int	draw_menu(char **entries, int nb_entries)
{
	int		i = 0;
	char	*name;

	while (i < nb_entries)
	{
		if (!(name = get_name(entries[i])))
			return (0);
		mvprintw(i + offset_y, offset_x, "%s", name);
		free(name);
		++i;
	}
	mvprintw(i + offset_y, offset_x, "Quit");
	mvchgat(offset_y, offset_x, menu_width, A_REVERSE, 0, NULL);
	refresh();
	return (1);
}

static int	move_choice(int i, int nb_entries, int where)
{
	mvchgat(i + offset_y, offset_x, menu_width, A_NORMAL, 0, NULL);
	if (where == KEY_DOWN)
		i = (i < nb_entries) ? i + 1 : 0;
	if (where == KEY_UP)
		i = (i > 0) ? i - 1 : nb_entries;
	mvchgat(i + offset_y, offset_x, menu_width, A_REVERSE, 0, NULL);
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
			return (i);
	}
	return (-1);
}

static void	init_ncurses(void)
{
	initscr();
	cbreak();
	noecho();
	keypad(stdscr, true);
	curs_set(0);
	refresh();
}

static void	exit_ncurses(void)
{
	curs_set(1);
	endwin();
}

static void	free_entries(char **entries, int nb_entries)
{
	int	i = 0;

	while (i < nb_entries)
	{
		free(entries[i]);
		++i;
	}
	free(entries);
}

int			main(int argc, char **argv)
{
	int		chosen_script = 0;
	char	*script;
	char	**entries;
	int		nb_entries;

	if (argc > 1)
	{
		if (!(entries = parse_args(argc, argv)))
			return (EXIT_FAILURE);
		nb_entries = argc - 1;
	}
	else
	{
		if (!(entries = parse_dir()))
			return (EXIT_FAILURE);
		nb_entries = get_nb_entries(entries);
	}
	init_ncurses();
	splash();
	if (!(get_sizes(entries, nb_entries)))
		return (EXIT_FAILURE);
	if ((draw_menu(entries, nb_entries)) != 0)
		chosen_script = controls(nb_entries);
	exit_ncurses();
	if (chosen_script >= 0 && chosen_script < nb_entries)
	{
		if ((script = ft_strjoin_f("sh ", entries[chosen_script], 0)))
		{
			system(script);
			free(script);
		}
	}
	free_entries(entries, nb_entries);
	return (EXIT_SUCCESS);
}
