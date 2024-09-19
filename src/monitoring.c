#include "minishell.h"

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
	char	*pwd_temp;
	char	*user_temp;

	username = NULL;
	host = ft_get_host(data);
	if (!host)
		return (NULL);
	user_temp = ft_get_user(data, host, &username);
	if (!user_temp)
	{
		free(host);
		return (NULL);
	}
	pwd_temp = ft_get_pwd(data);
	if (!pwd_temp)
	{
		free_monitoring(host, user_temp, NULL);
		return (NULL);
	}
	pwd = ft_substr(pwd_temp, ft_strlen(username) + 6, \
		ft_strlen(username) + 6 - ft_strlen(pwd_temp));
	free(pwd_temp);
	if (ft_strncmp(username, pwd, ft_strlen(username)) == 0)
	{
		free(pwd);
		pwd = NULL;
	}
	user = ft_strjoin_name(user_temp, pwd, '~', '$');
	if (!user)
	{
		free_monitoring(host, user_temp, pwd);
		return (NULL);
	}
	free(user_temp);
	user_temp = ft_strjoin(user, " ", 1);
	if (!user_temp)
	{
		free_monitoring(host, user, pwd);
		return (NULL);
	}
	free_monitoring(host, username, pwd);
	return (user_temp);
}
