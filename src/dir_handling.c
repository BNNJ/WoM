#include <dirent.h>
#include <sys/stat.h>
#include "wom.h"

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
		if (!(dir = extract_dir(argv[0])))
			return (NULL);
		dir = ft_strjoin_f(dir, DEFAULT_DIR, 1);
	}
	if (dir)
	{
		while (dir[i])
			++i;
		if (dir[i - 1] != '/')
			dir = ft_strjoin_f(dir, "/", 1);
	}
	return (dir);
}

char		**parse_dir(int argc, char **argv, int opt)
{
	struct dirent	*de = NULL;
	DIR				*dp = NULL;
	int				nb_entries = 0;
	char			**entries = NULL;
	char			*entry;
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
		if (!(entry = ft_strjoin_f(script_dir, de->d_name, 0)))
		{
			closedir(dp);
			return (NULL);
		}
		if (is_sh(entry))
		{
			entries[i] = entry;
			++i;
		}
		else
			free(entry);
	}
	entries[i] = NULL;
	free(script_dir);
	closedir(dp);
	return (entries);
}