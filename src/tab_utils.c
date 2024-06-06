# include "minishell.h"

void	ft_free_tab(char **arr)
{
	size_t	j;

	j = 0;
	while (arr[j])
	{
		free(arr[j]);
		j++;
	}
	free(arr);
}
