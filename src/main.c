
#include "minishell.h"

#include <unistd.h>

// int	main(int ac, char **av, char **env)
// {
// 	char	*line;
// 	char	*user;

// 	(void)ac;
// 	(void)av;
// 	user = get_user(env);
// 	if (user == NULL)
// 		return (-1);
// 	while (1)
// 	{
// 		line = readline(user);
// 		if (!line)
// 			break ;
// 		if (*line)
// 			add_history(line);
// 		free(line);
// 	}
// 	free(user);
// }






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


/*VALGRIND :

valgrind --suppressions=debug/valgrind_ignore_leaks.txt --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --show-mismatched-frees=yes --read-var-info=yes

*/
