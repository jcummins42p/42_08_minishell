/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 15:42:47 by jcummins          #+#    #+#             */
/*   Updated: 2024/08/02 13:00:07 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		token_parse_quote(t_mshell *msh, int start, char quote)
{
	char	*input;
	char	*token;
	int		end;
	int		i;

	i = 0;
	input = msh->lineread;
	end = start;
	end++;
	while (input[end] && (input[end] != quote))
		end++;
	if (input[end++] != quote)
		msh->valid_input = NO_QUOTE;
	else if ((end - start) > 0)
	{
		token = malloc(sizeof(char) * (end - start + 1));
		while (start < end)
			token[i++] = input[(start)++];
		token[i] = '\0';
		token_new(msh, token, end - i);
		free(token);
	}
	return (i);
}

int		token_parse(t_mshell *msh, int start)
{
	char	*input;
	char	*token;
	int		end;
	int		i;

	i = 0;
	input = msh->lineread;
	end = start;
	while (input[end] && !is_whitespace(input[end]))
		end++;
	if ((end - start) > 0)
	{
		token = malloc(sizeof(char) * (end - start + 1));
		while (start < end)
			token[i++] = input[start++];
		token[i] = '\0';
		token_new(msh, token, end - i);
		free(token);
	}
	if (is_whitespace(input[end]))
		return (i + 1);
	else
		return (i);
}

int	tokenize(t_mshell *msh)
{
	int i;

	i = 0;
	msh->valid_input = VALID_IN;
	if (msh->lineread)
	{
		while (msh->lineread[i] && msh->valid_input == VALID_IN)
		{
			while (msh->lineread[i] && is_whitespace(msh->lineread[i]))
				i++;
			if (msh->lineread[i] == '\'')
				i += token_parse_quote(msh, i, '\'');
			else if (msh->lineread[i] == '\"')
				i += token_parse_quote(msh, i, '\"');
			else
				i += token_parse(msh, i);
		}
	}
	if (!msh->lineread || msh->valid_input)
	{
		printf("input invalid\n");
		free(msh->lineread);
		token_clear(&msh->tokens);
		return (1);
	}
	return (0);
}
