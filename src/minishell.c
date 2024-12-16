#include "../includes/minishell.h"
#include <stdio.h>
#include <fcntl.h>

// Pomocnicza funkcja do wyświetlania tokenów
void display_tokens(t_token **tokens)
{
	int i;

	i = 0;
	printf("=== Tokenized Input ===\n");
	while (tokens[i])
	{
		printf("Token %d: Type = %d, Value = \"%s\"\n",
			i, tokens[i]->type, tokens[i]->value);
		i++;
	}
}

int main(void)
{
	char	*input;
	t_token	**tokens;

	printf("Welcome to MiniShell Tokenizer Test!\n");
	while (1)
	{
		// Wyświetlenie prompta
		write(1, "minishell> ", 11);
		input = get_next_line(STDIN_FILENO);
		if (!input)
		{
			write(1, "exit\n", 5);
			break ;
		}
		trim_newline(input); // Usunięcie znaku nowej linii

		// Tokenizacja inputu
		tokens = tokenize_input(input);
		if (tokens)
		{
			display_tokens(tokens); // Wyświetlenie tokenów
		}
		else
		{
			printf("Error: Tokenization failed\n");
		}

		// Zwolnienie pamięci
		free(input);
		
	}
	return (0);
}
