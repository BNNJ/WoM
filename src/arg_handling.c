#include <wom.h>

char	**parse_args(int argc, char **argv)
{
	char	**entries;
	int		i = 0;

	if (!(entries = malloc(argc * sizeof(char*))))
		return (NULL);
	while (i < argc - 1)
	{
		if (!(entries[i] = strdup(argv[i + 1])))
			return (NULL);
		++i;
	}
	return (entries);
}
