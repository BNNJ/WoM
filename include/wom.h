#ifndef WOM_H
# define WOM_H
# include <ncurses.h>
# include <string.h>
# include <stdlib.h>
# include <stdio.h>

# define DEFAULT_DIR	"./scripts/"	/* don't forget the '/' at the end */
# define SPLASH			"./splash.txt"	/* splash screen to be displayed */

# define F_D			1				/* directory option */
# define F_H			2				/* help */

/*
** Displays the scripts given as arguments in a menu, and executes the
** selected one
** If no arguments are given, the scripts in SCRIPT_DIR are used instead.
** Scripts need to end in .sh.
** The menu entry will use the file name, without .sh
**
** TO DO:
** Add submenu for RAM and core number selection
*/

/* tools */
char		*get_name(char *path);
char		*ft_strjoin_f(char *s1, char *s2, uint8_t opt);
int			get_char_index(char c, char *str);
char		*extract_dir(char *arg);
int			is_sh(char *name);

/* argument handling */
char		**parse_args(int argc, char **argv);

/* directory handling */
int			get_nb_entries(char **entries);
char		**parse_dir();

/* Splash screen */
int			splash(void);

/* options */
int			parse_options(int argc, char **argv, int *opt);

#endif
