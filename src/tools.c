#include <string.h>
#include <stdlib.h>

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
