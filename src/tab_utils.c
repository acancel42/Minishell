# include "minishell.h"

void	ft_free_tab(char **arr)
{
	int	i;

	i = -1;
	printf("freeing tab%s\n", arr[0]);
	while (arr[++i])
		free(arr[i]);
	free(arr);
}
