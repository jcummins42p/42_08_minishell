/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akretov <akretov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 15:42:47 by jcummins          #+#    #+#             */
/*   Updated: 2024/08/07 16:08:28 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	token_parse_meta(t_mshell *msh, int start)
{
	t_mtctype	token;
	char		*input;
	int			width;

	input = &msh->lineread[start];
	width = 0;
	token = is_metachar(input);
	if (token == PIPE)
		width = token_new(msh, "|", start, is_whitespace(input[start + 1]));
	else if (token == RDIN)
		width = token_new(msh, "<", start, is_whitespace(input[start + 1]));
	else if (token == RDOUT)
		width = token_new(msh, ">", start, is_whitespace(input[start + 1]));
	else if (token == RDAPP)
		width = token_new(msh, ">>", start, is_whitespace(input[start + 2]));
	if (token == DELIMIT)
		width = token_new(msh, "<<", start, is_whitespace(input[start + 2]));
	return (width);
}

int	token_parse_quote(t_mshell *msh, int start, char quote)
{
	char	*input;
	char	*token;
	int		end;
	int		i;

	i = 0;
	input = msh->lineread;
	end = start;
	if (input[end] == '$')
	{
		token_new(msh, "$", 1, is_whitespace(input[end]));
		return (1);
	}
	else
	{
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
			token_new(msh, token, end - i, is_whitespace(input[start]));
			free(token);
		}
	}
	return (i);
}

int	token_parse_assign(t_mshell *msh, int start)
{
	char	*input;
	char	*output;
	char	len;
	int		i;

	i = 0;
	input = msh->lineread;
	len = is_assign(&input[start]);
	output = malloc(sizeof(char) * (len + 1));
	while (i <= len)
		output[i++] = input[start++];
	output[i] = '\0';
	token_new(msh, output, start - i, is_whitespace(input[start]));
	return (i);
}

int	token_parse(t_mshell *msh, int start)
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
		token_new(msh, token, end - i, is_whitespace(input[end]));
		free(token);
	}
	if (is_whitespace(input[end]))
		return (i + 1);
	else
		return (i);
}

int	tokenize(t_mshell *msh)
{
	int	i;

	i = 0;
	msh->valid_input = VALID_IN;
	if (msh->lineread)
	{
		while (msh->lineread[i] && msh->valid_input == VALID_IN)
		{
			while (msh->lineread[i] && is_whitespace(msh->lineread[i]))
				i++;
			if (is_metachar(&msh->lineread[i]) >= PIPE)
				i += token_parse_meta(msh, i);
			else if (msh->lineread[i] == '\'')
				i += token_parse_quote(msh, i, '\'');
			else if (msh->lineread[i] == '\"')
				i += token_parse_quote(msh, i, '\"');
			else if (is_assign(&msh->lineread[i]))
				i += token_parse_assign(msh, i);
			else
				i += token_parse(msh, i);
		}
	}
	if (!msh->lineread || msh->valid_input)
		return (0);
	return (1);
}
