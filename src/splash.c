#include <fcntl.h>
#include <unistd.h>
#include "wom.h"

static int	get_xy(int fd, int *x, int *y)
{
	char	c = 1;
	int		max_x;
	int		max_y;

	getmaxyx(stdscr, max_y, max_x);
	while ((c && c != '\n'))
	{
		if (read(fd, &c, 1) <= 0)
			return (0);
		++*x;
	}
	*y = lseek(fd, 0, SEEK_END) / *x;
	lseek(fd, 0, SEEK_SET);
	*x = (max_x - *x) / 2;
	*y = (max_y - *y) / 2;
	return (1);
}

static int	display(int fd, int x, int y)
{
	int		i;
	int		j;
	char	c;

	i = x;
	j = y;
	c = 1;
//	attron(COLOR_PAIR(2));
	while (c != 0)
	{
		if (read(fd, &c, 1) <= 0)
			return (1);
		if (c == '\n')
		{
			i = x;
			++j;
			usleep(20000 / y);
		}
		else
		{
			mvprintw(j, i, "%c", c);
			usleep(20000 / x);
			refresh();
			++i;
		}
	}
//	attroff(COLOR_PAIR(2));
	return (1);
}

static int	exit_splash(int fd, int exit_status)
{
	close(fd);
	nodelay(stdscr, false);
	if (exit_status == 1)
		getch();
	nodelay(stdscr, true);
	clear();
	refresh();
	return (exit_status);
}

int			splash(void)
{
	int		fd;
	int		x = 0;
	int		y = 0;

	if ((fd = open(SPLASH, O_RDONLY)) < 0)
		return (exit_splash(fd, 0));
	if (!get_xy(fd, &x, &y))
		return (exit_splash(fd, 0));
	if (!(display(fd, x, y)))
		return (exit_splash(fd, 0));
	return (exit_splash(fd, 1));
}
