/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmilek <pmilek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 10:00:00 by pmilek            #+#    #+#             */
/*   Updated: 2025/01/15 18:03:39 by pmilek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	handle_word_token(t_token **tokens, int *count, char *line, int *i)
{
	tokens[*count] = malloc(sizeof(t_token));
	if (!tokens[*count])
		return ;
	tokens[*count]->value = extract_word(line, i);
	if (!tokens[*count]->value)
	{
		free(tokens[*count]);
		return ;
	}
	tokens[*count]->type = determine_token_type(tokens, *count);
	(*count)++;
}

static void	handle_quoted_token(t_token **tokens,
			int *count, char *line, int *i)
{
	tokens[*count] = malloc(sizeof(t_token));
	if (!tokens[*count])
		return ;
	tokens[*count]->value = extract_quoted_word(line, i);
	tokens[*count]->type = determine_token_type(tokens, *count);
	(*count)++;
}

static void	handle_assignment_token(t_token **tokens,
		int *count, char *line, int *i)
{
	int		start;
	char	*assignment;

	start = *i;
	while (line[*i] && (line[*i] != ' ' || line[start] == '='))
	{
		if (line[*i] == '"' || line[*i] == '\'')
			extract_quoted_word(line, i);
		else
			(*i)++;
	}
	assignment = ft_substr(line, start, *i - start);
	tokens[*count] = malloc(sizeof(t_token));
	if (!tokens[*count])
		return ;
	tokens[*count]->type = ARGUMENT;
	tokens[*count]->value = assignment;
	(*count)++;
}

static void	process_line(char *line, t_token **tokens, int *count, int *i)
{
	while (line[*i])
	{
		if (line[*i] == ' ')
			(*i)++;
		else if (is_assignment(line, *i))
			handle_assignment_token(tokens, count, line, i);
		else if (line[*i] == '"' || line[*i] == '\'')
			handle_quoted_token(tokens, count, line, i);
		else if (is_special_char(line[*i]))
			add_special_token(tokens, count, line, i);
		else
			handle_word_token(tokens, count, line, i);
	}
}

t_token	**tokenize_input(char *line)
{
	t_token	**tokens;
	int		i;
	int		count;

	i = 0;
	count = 0;
	tokens = malloc(sizeof(t_token *) * 1024);
	if (!tokens)
		return (NULL);
	if (!validate_line_start(line, tokens, count))
	{
		free_token_array(tokens, count);
		return (NULL);
	}
	process_line(line, tokens, &count, &i);
	if (count == 0)
	{
		free(tokens);
		return (NULL);
	}
	tokens[count] = NULL;
	link_tokens(tokens);
	return (tokens);
}
