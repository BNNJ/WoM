#ifndef WOM_H
# define WOM_H
# include <ncurses.h>
# include <string.h>
# include <stdlib.h>
# include <stdio.h>

# define OFFSET_X	2
# define OFFSET_Y	2

# define SCRIPT_DIR	"./scripts/" /* don't forget the '/' at the end */

/* tools */
char		*get_name(char *path);
char		*ft_strjoin_f(char *s1, char *s2, uint8_t opt);

/* argument handling */
char		**parse_args(int argc, char **argv);

/* directory handling */
int			get_nb_entries(char **entries);
char		**parse_dir();


#endif
