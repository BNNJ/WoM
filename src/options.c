#include "wom.h"

static int	get_long_opt(char *arg, int *opt)
{
	int		i = 0;
	char	*opt_tab[] = {
		"dir",
		"help",
		NULL
	};

	if (*arg == 0)
		return (2);
	while (opt_tab[i])
	{
		if (strcmp(opt_tab[i], arg) == 0)
		{
			*opt |= (1 << i);
			return (1);
		}
		++i;
	}
	dprintf(2, "wom: invalid option: %s\n", arg);
	return (0);
}

static int	get_opt(char *arg, int *opt)
{
	int		idx;

	if (*arg == '-')
		return (get_long_opt(arg + 1, opt));
	else if (arg[1] != 0)
	{
		dprintf(2, "wom: invalid option: %s\n", arg);
		return (0);
	}
	else if ((idx = get_char_index(*arg, "dh")) >= 0)
	{
		*opt |= (1 << idx);
		return (1);
	}
	else
	{
		dprintf(2, "wom: invalid option: %c\n", *arg);
		return (0);
	}
}

int		parse_options(int argc, char **argv, int *opt)
{
	int	i = 0;
	int	ret;

	while (++i < argc)
	{
		if (*argv[i] == '-')
		{
			if (!(ret = get_opt(argv[i] + 1, opt)))
				return (0);
			else if (ret == 2)
				return (1);
		}
	}
	return (1);
}
