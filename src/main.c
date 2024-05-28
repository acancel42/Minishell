
#include "../inc/minishell.h"

#include <stdlib.h>
#include <unistd.h>
#include <pwd.h>
#include <sys/types.h>
#include <limits.h>

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

int	main(void)
{
	char			*line;
	struct passwd	*pw;
	char			*username;
	char			hostname[42];

	pw = getpwuid(getuid());
	if (pw == NULL)
		return (perror("getpwuid"), -2);
	username = pw->pw_name;
	if (gethostname(hostname, sizeof(hostname)) != 0)
		return (perror("gethostname"), -3);
	username = ft_strjoin_name(username, hostname);
	if (username == NULL)
		return (-1);
	while (1) 
	{
		line = readline(username); // Lire une ligne de texte avec readline
		if (!line) // Vérifier si la ligne est NULL (fin de fichier)
			break ;
		if (*line) // Si la ligne n'est pas vide, l'ajouter à l'historique
			add_history(line);
		free(line);
	}
	free(username);
	return (0);
}
