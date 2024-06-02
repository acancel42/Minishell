#include "../inc/minishell.h"

void print_type(t_token_types type)
{
	if (type == ARRAY)
		printf("%s : ", "ARRAY");
	if (type == SCO)
		printf("%s : ", "SCO");
	if (type == FLAG)
		printf("%s : ", "FLAG");
	if (type == INT)
		printf("%s : ", "INT");
	if (type == LSQUO)
		printf("%s : ", "LSQUO");
	if (type == RSQUO)
		printf("%s : ", "RSQUO");
	if (type == RDQUO)
		printf("%s : ", "RDQUO");
	if (type == LDQUO)
		printf("%s : ", "LDQUO");
	if (type == EQUAL)
		printf("%s : ", "EQUAL");
	if (type == IRED)
		printf("%s : ", "IRED");
	if (type == ORED)
		printf("%s : ", "ORED");
	if (type == IAPP)
		printf("%s : ", "IAPP");
	if (type == OAPP)
		printf("%s : ", "OAPP");
	if (type == IFILE)
		printf("%s : ", "IFILE");
	if (type == OFILE)
		printf("%s : ", "OFILE");
	if (type == PIPE)
		printf("%s : ", "PIPE");
}

// Afficher les tokens
void	print_lst(t_token *token)
{
	while (token)
	{
		print_type(token->type);
		printf("%s\n", token->value);
		token = token->next;
	}
}

void	print_file(t_file *file, t_token_types type)
{
	while (file)
	{
		if (type == ARRAY)
			printf("arg : %s\n", file->name);
		if (type == IRED)
			printf("input : %s\n", file->name);
		if (type == ORED)
			printf("output : %s\n", file->name);
		file = file->next;
	}
}

void	print_cmds(t_commands *cmds)
{
	while (cmds)
	{
		printf("command : %s\n", cmds->name);
		printf("flags : %s\n", cmds->flags);
		print_file(cmds->args, ARRAY);
		print_file(cmds->input, IRED);
		print_file(cmds->output, ORED);
		printf("%c", '\n');
		cmds = cmds->next;
	}
}
