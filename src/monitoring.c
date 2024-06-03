
#include "minishell.h"

#include <unistd.h>

char	*ft_strjoin_name(char *s1, char *s2)
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
	dest = ft_calloc(len, sizeof(char));
	if (dest == NULL)
		return (NULL);
	while (s1[++i])
		dest[i] = s1[i];
	dest[i++] = '@';
	while (s2[j] != '.' && s2[j] != '\0')
		dest[i++] = s2[j++];
	dest[i++] = ':';
	dest[i] = '\0';
	return (dest);
}

char	*get_user(char **env)
{
	int		i;
	char	*host;
	char	*username;
	char	*user;

	i = 0;
	while (ft_strncmp(env[i], "SESSION_MANAGER=", 16) != 0)
		i++;
	host = ft_substr(env[i], 22, 6);
	if (host == NULL)
		return (NULL);
	i = 0;
	while (ft_strncmp(env[i], "LOGNAME=", 8) != 0)
		i++;
	username = ft_substr(env[i], 8, 8);
	if (username == NULL)
	{
		free(host);
		return (NULL);
	}
	user = ft_strjoin_name(username, host);
	free(username);
	free(host);
	return (user);
}
