#include <dirent.h>
#include "wom.h"

static int	is_sh(char *name, int len)
{
	return (name[len - 3] == '.' && name[len - 2] == 's' && name[len - 1] == 'h');
}

int			get_nb_entries(char **entries)
{
	int		nb_entries = 0;

	while (entries[nb_entries])
		++nb_entries;
	return (nb_entries);
}

char		**parse_dir(void)
{
	struct dirent	*de;
	DIR				*dp;
	int				nb_entries = 0;
	char			**entries;
	int				name_len;
	int				i = 0;

	if (!(dp = opendir(SCRIPT_DIR)))
		return (NULL);
	while ((de = readdir(dp)))
		++nb_entries;
	if (!(entries = malloc((nb_entries + 1) * sizeof(char*))))
		return (NULL);
	rewinddir(dp);
	while ((de = readdir(dp)))
	{
		name_len = 0;
		while (de->d_name[name_len])
			++name_len;
		if (is_sh(de->d_name, name_len))
		{
			if (!(entries[i] = ft_strjoin_f(SCRIPT_DIR, de->d_name, 0)))
				return (NULL);
			++i;
		}
	}
	entries[i] = NULL;
	closedir(dp);
	return (entries);
}