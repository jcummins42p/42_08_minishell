/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akretov <akretov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 15:42:47 by jcummins          #+#    #+#             */
/*   Updated: 2024/08/08 20:02:02 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	token_parse_meta(t_mshell *msh, char *input, int index)
{
	t_mtctype	token;
	int			width;

	width = 0;
	token = is_metachar(input);
	if (token == PIPE)
		width = token_new(msh, "|", index, is_trailspace(input[1]));
	else if (token == RDIN)
		width = token_new(msh, "<", index, is_trailspace(input[1]));
	else if (token == ASS)
		width = token_new(msh, "=", index, is_trailspace(input[1]));
	else if (token == RDOUT)
		width = token_new(msh, ">", index, is_trailspace(input[1]));
	else if (token == RDAPP)
		width = token_new(msh, ">>", index, is_trailspace(input[2]));
	if (token == DELIMIT)
		width = token_new(msh, "<<", index, is_trailspace(input[2]));
	return (width);
}

int	token_parse_quote(t_mshell *msh, char *input, char quote, int index)
{
	char	*output;
	int		len;
	int		i;

	i = -1;
	len = 0;
	if (input[len] == '$' && is_trailspace(input[len + 1]))
	{
		token_new(msh, "$", 1, is_whitespace(input[len + 1]));
		return (1);
	}
	else
	{
		len++;
		while (input[len] && (input[len] != quote))
			len++;
		if (input[len++] != quote)
			msh->valid_input = NO_QUOTE;
		else if (len > 0)
		{
			output = malloc(sizeof(char) * (len + 1));
			while (++i < len)
				output[i] = input[i];
			output[i] = '\0';
			token_new(msh, output, index, is_whitespace(input[len]));
			free(output);
		}
	}
	return (len);
}

int	token_parse(t_mshell *msh, char *input, int index)
{
	char	*output;
	int		len;
	int		i;

	i = 0;
	len = 0;
	if (input[len++] == '$')
		len++;
	while (input[len] && !is_whitespace(input[len]) && !is_metachar(&input[len]))
		len++;
	if (len > 0)
	{
		output = malloc(sizeof(char) * (len + 1));
		while (i < len)
		{
			output[i] = input[i];
			i++;
		}
		output[i] = '\0';
		token_new(msh, output, index, is_trailspace(input[len]));
		free(output);
	}
	if (is_whitespace(input[len]))
		return (len + 1);
	else
		return (len);
}

int	token_parse_selector(t_mshell *msh, char *input, int index)
{
	int i;

	i = 0;
	while (input[i] && is_whitespace(input[i]))
		i++;
	if (is_metachar(&input[i]) >= ASS)
		i += token_parse_meta(msh, &input[i], index);
	else if (input[i] == '\'')
		i += token_parse_quote(msh, &input[i], '\'', index);
	else if (input[i] == '\"')
		i += token_parse_quote(msh, &input[i], '\"', index);
	else
		i += token_parse(msh, &input[i], index);
	return (i);
}

int	tokenize(t_mshell *msh)
{
	int	i;

	i = 0;
	msh->valid_input = VALID_IN;
	if (msh->lineread)
		while (msh->lineread[i] && msh->valid_input == VALID_IN)
			i += token_parse_selector(msh, &msh->lineread[i], i);
	if (!msh->lineread || msh->valid_input)
		return (0);
	return (1);
}
