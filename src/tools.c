#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>

#define FREE_S1	1
#define FREE_S2	2

int		is_sh(char *name)
{
	struct stat	st;
	int			len = strlen(name);
	int			i = 0;
	int			name_start;

	while (name[i])
	{
		if (name[i] == '/')
			name_start = i + 1;
		++i;
	}
	if (name[name_start] == '.')
		return (0);
	if ((stat(name, &st)) != 0)
	{
		dprintf(2, "wom: %s doesn't exist\n", name);
		return (0);
	}
	if (!S_ISREG(st.st_mode))
	{
		dprintf(2, "wom: %s is not a regular file\n", name);
		return (0);
	}
	return (name[len - 3] == '.'
		&& name[len - 2] == 's'
		&& name[len - 1] == 'h');
}

/*
** extracts the directory path out of a binary path
*/

char	*extract_dir(char *arg)
{
	char	*path = NULL;
	size_t	path_len = 0;
	int		i = 0;

	while (arg[i])
	{
		if (arg[i] == '/')
			path_len = i;
		++i;
	}
	return (path = strndup(arg, path_len + 1));
}

/*
** returns the number of entries to be displayed
*/

int			get_nb_entries(char **entries)
{
	int		nb_entries = 0;

	while (entries[nb_entries])
		++nb_entries;
	return (nb_entries);
}

/*
** concatenate s1 and s2
** frees the strings passed as opt:
** FREE_S1 : free s1
** FREE_S2 : free s2
** can be or'd (FREE_S1 | FREE_S2) to free both
** pass 0 if you don't want to free anything
**
** returns a pointer to a dynaically allocated string
*/

char		*ft_strjoin_f(char *s1, char *s2, int opt)
{
	char	*str;
	int		i;
	int		j;

	i = -1;
	j = -1;
	if (!s1 && !s2)
		return (NULL);
	else if (s1 && !s2)
		return (opt & 1 ? s1 : strdup(s1));
	else if (!s1 && s2)
		return (opt & 2 ? s2 : strdup(s2));
	if (!(str = malloc(strlen(s1) + strlen(s2) + 1)))
		return (NULL);
	str[strlen(s1) + strlen(s2)] = 0;
	while (s1[++i])
		str[i] = s1[i];
	while (s2[++j])
		str[i + j] = s2[j];
	if (opt & 1)
		free(s1);
	if (opt & 2)
		free(s2);
	return (str);
}

/*
** returns the index of the first occurence of c in str.
** if c is not found, -1 is returned
*/

int			get_char_index(char c, char *str)
{
	int	i = 0;

	while (str[i])
	{
		if (str[i] == c)
			return (i);
		++i;
	}
	return (-1);
}

/*
** extracts the name of a file out of its path (the part after the last '/')
**
** returns a pointer to a dynaically allocated string
*/

char		*get_name(char *path)
{
	char	*name;
	int		i = 0;
	int		start_index = 0;
	int		name_len = 0;

	while (path[i])
	{
		if (path[i] == '/')
		{
			name_len = 0;
			start_index = i;
		}
		++name_len;
		++i;
	}
	name_len -= 4;
	++start_index;
	if (!(name = malloc(name_len + 1)))
		return (NULL);
	i = 0;
	while (i < name_len)
	{
		name[i] = path[start_index + i];
		++i;
	}
	name[i] = 0;
	return (name);
}
