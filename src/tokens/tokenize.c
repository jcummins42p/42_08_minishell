/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akretov <akretov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 15:42:47 by jcummins          #+#    #+#             */
/*   Updated: 2024/08/16 11:56:11 by jcummins         ###   ########.fr       */
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
	int		i;

	i = 0;
	if (input[i] == '$' && is_trailspace(input[i + 1]))
	{
		token_new(msh, "$", 1, is_whitespace(input[i + 1]));
		return (1);
	}
	else
	{
		i++;
		while (input[i] && (input[i] != quote))
			i++;
		if (input[i++] != quote)
			msh->valid_input = NO_QUOTE;
		else if (i > 0)
		{
			output = ft_strldup(input, i);
			token_new(msh, output, index, is_trailspace(input[i]));
			free(output);
		}
	}
	return (i);
}

int	token_parse(t_mshell *msh, char *input, int index)
{
	char	*output;
	int		i;

	i = 0;
	if (input[i++] == '$')
		i++;
	while (input[i] && !is_whitespace(input[i]) && !is_metachar(&input[i]))
		i++;
	if (i > 0)
	{
		output = ft_strldup(input, i);
		token_new(msh, output, index, is_trailspace(input[i]));
		free(output);
	}
	if (is_whitespace(input[i]))
		return (i + 1);
	else
		return (i);
}

int	token_parse_selector(t_mshell *msh, char *input, int index)
{
	int	i;

	i = 0;
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
	while (msh->lineread && msh->lineread[i] && msh->valid_input == VALID_IN)
	{
		while (msh->lineread[i] && is_whitespace(msh->lineread[i]))
			i++;
		if (msh->lineread[i])
			i += token_parse_selector(msh, &msh->lineread[i], i);
	}
	if (!msh->lineread || msh->valid_input)
	{
		msh->exitcode = EX_SYNTAX_ERROR;
		return (0);
	}
	return (1);
}
