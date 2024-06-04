# include "minishell.h"

void	ft_free_tab(char **arr, int j)
{
	while (j >= 0)
	{
		free(arr[j]);
		j--;
	}
	free(arr);
}
