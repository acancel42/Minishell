#include "../inc/minishell.h"

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

// Fonction d'allocation de mémoire sécurisée
void *ft_calloc(size_t count, size_t size) {
    void *ptr = calloc(count, size);
    if (!ptr) {
        perror("calloc");
        exit(EXIT_FAILURE);
    }
    return ptr;
}

// Assume ft_strdup and ft_strjoin are defined correctly elsewhere
char *ft_strdup(const char *s) {
    char *dup = strdup(s);
    if (!dup) {
        perror("strdup");
        exit(EXIT_FAILURE);
    }
    return dup;
}

char *ft_strjoin(char const *s1, char const *s2) {
    size_t len1 = strlen(s1);
    size_t len2 = strlen(s2);
    char *joined = malloc(len1 + len2 + 1);
    if (!joined) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    strcpy(joined, s1);
    strcat(joined, s2);
    return joined;
}

// Création d'un nouveau token
t_token *ft_toknew(char *content, t_token_types type) {
    t_token *new = ft_calloc(1, sizeof(t_token));
    new->next = NULL;
    new->value = ft_strdup(content);
    new->type = type;
    return (new);
}

// Trouver le dernier token de la liste
t_token *ft_toklast(t_token *lst) {
    while (lst && lst->next != NULL)
        lst = lst->next;
    return (lst);
}

// Ajouter un token à la fin de la liste
void ft_tokadd_back(t_token **lst, t_token *new) {
    if (!lst || !new)
        return;
    t_token *temp = ft_toklast(*lst);
    if (temp != NULL)
        temp->next = new;
    else
        *lst = new;
}

// Initialiser un token à partir d'une chaîne
int token_init(char *src, t_token **token) {
    int i = 0;
    char c;
    t_token *temp;

    if (src[i] == '=') {
        temp = ft_toknew("=", EQUAL);
        ft_tokadd_back(token, temp);
        return (1);
    } else if (isdigit(src[i])) {
        temp = ft_toknew("", INT);
        ft_tokadd_back(token, temp);
        while (isdigit(src[i])) {
            c = src[i];
            temp->value = ft_strjoin(temp->value, (char[]){c, '\0'});
            i++;
        }
        return (i);
    } else {
        exit(EXIT_FAILURE);
    }
}

// Initialiser le lexer avec une chaîne
void lexer_init(t_token **token, char *src) {
    int i = 0;
    while (src[i]) {
        i += token_init(&src[i], token);
    }
}

// Afficher les tokens
void	print_lst(t_token *token)
{
    while (token)
	{
        printf("%s\n", token->value);
        token = token->next;
    }
}

int main(int argc, char **argv)
{
    t_token *token = NULL;

    if (argc != 2)
	{
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return (1);
    }
    lexer_init(&token, argv[1]);
    print_lst(token);
    // Free allocated memory (tokens list)
    t_token *temp;
    while (token)
	{
        temp = token;
        token = token->next;
        free(temp->value);
        free(temp);
    }

    return (0);
}
