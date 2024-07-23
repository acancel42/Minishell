#include "minishell.h"

static char	*ft_strjoin_name(char *s1, char *s2, char c1, char c2)
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

static char	*ft_get_host(t_data *data)
{
	int		i;
	char	*host;

	i = 0;
	while (ft_strncmp(data->my_env[i], "SESSION_MANAGER=", 16) != 0)
		i++;
	host = ft_substr(data->my_env[i], 22, 7);
	if (host == NULL)
		return (NULL);
	return (host);
}

static char	*ft_get_user(t_data *data, char *host, char	**username)
{
	int		i;
	char	*user;

	i = 0;
	while (ft_strncmp(data->my_env[i], "LOGNAME=", 8) != 0)
		i++;
	*username = ft_substr(data->my_env[i], 8, 8);
	if (*username == NULL)
	{
		free(host);
		return (NULL);
	}
	user = ft_strjoin_name(*username, host, '@', ':');
	if (!user)
		return (NULL);
	return (user);
}

static char	*ft_get_pwd(t_data *data)
{
	int		i;
	char	*pwd;

	i = 0;
	while (ft_strncmp(data->my_env[i], "PWD=", 4))
		i++;
	pwd = ft_substr(data->my_env[i], 4, ft_strlen(data->my_env[i]) - 4);
	if (!pwd)
	{
		printf("getcwd: cannot access \
	parent directories: No such file or directory\n");
		ft_cd(data->home, data);
	}
	return (pwd);
}

char	*get_user(t_data *data)
{
	char	*host;
	char	*user;
	char	*username;
	char	*pwd;

	username = NULL;
	host = ft_get_host(data);
	if (!host)
		return (NULL);
	user = ft_get_user(data, host, &username);
	printf("username : %s\n", username);
	if (!user)
		return (NULL);
	pwd = ft_get_pwd(data);
	if (!pwd)
		return (NULL);
	pwd = ft_substr(pwd, ft_strlen(username) + 6, \
		ft_strlen(username) + 6 - ft_strlen(pwd));
	if (!ft_strncmp(username, pwd, 4))
		pwd = NULL;
	// printf("pwd %s\n" , pwd);
	user = ft_strjoin_name(user, pwd, '~', '$');
	user = ft_strjoin(user, " ", 1);
	free(pwd);
	free(host);
	free(username);
	if (!user)
		return (NULL);
	return (user);
}
