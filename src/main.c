
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

// int	main(void)
// {
// 	char			*line;
// 	struct passwd	*pw;
// 	char			*username;
// 	char			hostname[42];

// 	pw = getpwuid(getuid());
// 	if (pw == NULL)
// 		return (perror("getpwuid"), -2);
// 	username = pw->pw_name;
// 	if (gethostname(hostname, sizeof(hostname)) != 0)
// 		return (perror("gethostname"), -3);
// 	username = ft_strjoin_name(username, hostname);
// 	if (username == NULL)
// 		return (-1);
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


int	main(int ac, char **av,char **env)
{
	int		i;
	char	*host;
	char	*username;
	char	*user;
	char	*line;

	(void)ac;
	(void)av;
	i = 0;
	while (ft_strncmp(env[i], "SESSION_MANAGER=", 16) != 0)
		i++;
	host = ft_substr(env[i], 22, 6);
	if (host == NULL)
		return (-1);
	i = 0;
	while (ft_strncmp(env[i], "LOGNAME=", 8) != 0)
		i++;
	username = ft_substr(env[i], 8, 8);
	if (username == NULL)
		return (-1);
	user = ft_strjoin_name(username, host);
	if (username == NULL)
		return (-1);
	while (1) 
	{
		line = readline(user); // Lire une ligne de texte avec readline
		if (!line) // Vérifier si la ligne est NULL (fin de fichier)
			break ;
		if (*line) // Si la ligne n'est pas vide, l'ajouter à l'historique
			add_history(line);
		free(line);
	}
	free(user);
	free(username);
	free(host);
	return (0);
}


// 	void	build_path(char *path, char *s1, char *s2)
// {
// 	size_t		len_s1;
// 	size_t		len_s2;

// 	if (!s1 || !s2)
// 	{
// 		path = NULL;
// 		return ;
// 	}
// 	len_s1 = ft_strlen(s1);
// 	len_s2 = ft_strlen(s2);
// 	path = ft_calloc(len_s1 + 1 + len_s2 + 1, sizeof(char));
// 	if (path == NULL)
// 	{
// 		ft_putstr_fd("malloc failed\n", 2);
// 		free_all(NULL, cmd);
// 		exit(EXIT_FAILURE);
// 	}
// 	ft_memcpy(path, s1, len_s1);
// 	ft_memcpy(path + len_s1, "/", 1);
// 	ft_memcpy(path + len_s1 + 1, s2, len_s2);
// 	return ;
// }

// void	cmd1_path(char *path, char *data, char **env)
// {
// 	char	**all_paths;
// 	int		i;

// 	i = 0;
// 	while (ft_strncmp(env[i], "PATH=", 5) != 0)
// 		i++;
// 	path = env[i];
// 	all_paths = ft_split(px->path + 5, ':');
// 	if (all_paths == NULL)
// 	{
// 		ft_putstr_fd("malloc failed\n", 2);
// 		clean_all(px, all_paths, 1);
// 	}
// 	px->i = 0;
// 	build_path(px, all_paths[px->i], cmd);
// 	while (access(px->path, F_OK) != 0 && px->path != NULL)
// 	{
// 		free(px->path);
// 		build_path(px, all_paths[px->i++], cmd);
// 	}
// 	if (px->path == NULL)
// 		cmd_not_found(px, all_paths, 0);
// 	free_all(NULL, all_paths);
// }