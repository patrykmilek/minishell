#include "../includes/minishell.h"
#include <stdio.h>
#include <fcntl.h>


void print_tokens(t_token **tokens)
{
	int i;

	i = 0;
	printf("=== Tokenized Input ===\n");
	while (tokens[i])
	{
		printf("Token %d: Type = %d, Value = \"%s\"\n", i, tokens[i]->type, tokens[i]->value);
		free(tokens[i]->value);
		free(tokens[i]);
		i++;
	}
	free(tokens);
}

int main(void)
{
	char	*input;
	t_token	**tokens;

	printf("Welcome to MiniShell Tokenizer Test!\n");
	while (1)
	{
		// Wyświetlenie prompta i pobranie inputu
		write(1, "minishell> ", 11);
		input = get_next_line(STDIN_FILENO);
		if (!input) // Obsługa EOF (ctrl-D)
		{
			write(1, "exit\n", 5);
			break ;
		}
		trim_newline(input); // Usunięcie znaku nowej linii

		// Tokenizacja inputu
		tokens = tokenize_input(input);
		if (tokens)
			print_tokens(tokens); // Wyświetlenie tokenów
		else
			printf("Error: Tokenization failed\n");

		free(input); // Zwolnienie inputu
	}
	return (0);
}