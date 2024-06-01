
#include "../inc/minishell.h"

#include <stdlib.h>
#include <unistd.h>
// #include <pwd.h>
// #include <sys/types.h>
// #include <limits.h>

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
	dest = malloc(sizeof(char) * len);
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

int	main(int ac, char **av, char **env)
{
	char	*line;
	char	*user;

	(void)ac;
	(void)av;
	user = get_user(env);
	if (user == NULL)
		return (-1);
	while (1)
	{
		line = readline(user);
		if (!line)
			break ;
		if (*line)
			add_history(line);
		free(line);
	}
	free(user);
}

// int	main(int ac, char **av, char **env)
// {
// 	char	*line;
//	char	*user;
// 
// 	(void)ac;
// (void)av;
//	user = get_user(env);
// 	while (1) 
// 	{
// 		line = readline(username); // Lire une ligne de texte avec readline
// 		if (!line) // Vérifier si la ligne est NULL (fin de fichier)
// 			break ;
// 		if (*line) // Si la ligne n'est pas vide, l'ajouter à l'historique
// 			add_history(line);
// 		free(line);
// 	}
// 	free(username);
// 	return (0);
// }