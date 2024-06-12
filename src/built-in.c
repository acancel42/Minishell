
#include "minishell.h"

int	get_pwd(char **pwd)
{
	*pwd = getcwd(NULL, 0);
	if (!*pwd)
		return (-2);
	return (0);
}

int	get_cd(char *path)
{
	printf("%s\n", path);
	if (chdir(path) == -1)
		return (-2);
	return (0);
}
