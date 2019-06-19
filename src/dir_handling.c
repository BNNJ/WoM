#include <dirent.h>
#include "wom.h"

#ifdef _DIRENT_HAVE_D_TYPE
static int	is_sh(char *name, int len, unsigned char type)
{
	return (type == DT_REG
		&& name[len - 3] == '.'
		&& name[len - 2] == 's'
		&& name[len - 1] == 'h');
}
#else
static int	is_sh(char *name, int len)
{
	return (name[len - 3] == '.'
		&& name[len - 2] == 's'
		&& name[len - 1] == 'h');
}
#endif

static char	*get_script_dir(int argc, char **argv, int opt)
{
	char	*dir = NULL;
	int		i = 0;

	if (opt & F_D)
	{
		if (argc >= 3)
			dir = strdup(argv[2]);
		else
			dprintf(2, "wom: no directory specified\n");
	}
	else
	{
		dir = extract_dir(argv[0]);
		dir = ft_strjoin_f(dir, DEFAULT_DIR, 1);
	}
	if (dir == NULL)
		return (NULL);
	while (dir[i])
		++i;
	if (dir[i - 1] != '/')
		dir = ft_strjoin_f(dir, "/", 1);
	return (dir);
}

char		**parse_dir(int argc, char **argv, int opt)
{
	struct dirent	*de = NULL;
	DIR				*dp = NULL;
	int				nb_entries = 0;
	char			**entries = NULL;
	int				name_len = 0;
	int				i = 0;
	char			*script_dir = NULL;

	if (!(script_dir = get_script_dir(argc, argv, opt)))
		return (NULL);
	if (!(dp = opendir(script_dir)))
	{
		dprintf(2, "wom: invalid directory: %s\n", script_dir);
		return (NULL);
	}
	while ((de = readdir(dp)))
		++nb_entries;
	if (!(entries = malloc((nb_entries + 1) * sizeof(char*))))
	{
		closedir(dp);
		return (NULL);
	}
	rewinddir(dp);
	while ((de = readdir(dp)))
	{
		name_len = 0;
		while (de->d_name[name_len])
			++name_len;
#ifdef _DIRENT_HAVE_D_TYPE
		if (is_sh(de->d_name, name_len, de->d_type))
#else
		if (is_sh(de->d_name, name_len))
#endif
		{
			if (!(entries[i] = ft_strjoin_f(script_dir, de->d_name, 0)))
			{
				closedir(dp);
				return (NULL);
			}
			++i;
		}
	}
	entries[i] = NULL;
	free(script_dir);
	closedir(dp);
	return (entries);
}