#include "minishell.h"

char	*ft_strjoin_name(char *s1, char *s2, char c1, char c2)
{
	int		len;
	int		i;
	int		j;
	char	*dest;

	i = 0;
	j = 0;
	while (s2[i] != '.' && s2[i] != '\0')
		i++;
	len = ft_strlen(s1) + 1 + i + 1 +1;
	i = -1;
	dest = ft_calloc(len + 1, sizeof(char));
	if (dest == NULL)
		return (NULL);
	while (s1[++i])
		dest[i] = s1[i];
	dest[i++] = c1;
	while (s2[j] != '.' && s2[j] != '\0')
		dest[i++] = s2[j++];
	dest[i++] = c2;
	dest[i] = '\0';
	return (dest);
}

void	free__monitoring(char *host, char *username, char *pwd)
{
	if (pwd)
		free(pwd);
	if (host)
		free(host);
	if (username)
		free(username);
	return ;
}
