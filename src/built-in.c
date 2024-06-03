
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int	main(void)
{
	char	*pwd;

	getcwd(pwd, 0);
	printf("%s", pwd);
	free(pwd);
	return (0);
}
