/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 11:50:18 by jcummins          #+#    #+#             */
/*   Updated: 2024/08/02 17:51:37 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_string_sq(char *input)
{
	char	*output;
	int		len;
	int		i;
	int		j;

	i = 0;
	j = 0;
	len = ft_strlen(input) - 2;
	output = malloc(sizeof(char) * (len + 1));
	if (output == NULL)
		return (NULL);
	if (input[i] == '\'')
		i++;
	while (j < len)
		output[j++] = input[i++];
	output[j] = '\0';
	return (output);
}

//	reads a variable from input string and returns its length
char	*isolate_param(char *input)
{
	char	*out;
	int		len;
	int		i;

	out = NULL;
	len = 0;
	i = 0;
	if (input[len] == '$')
		len++;
	else
	{
		while (input[len] && !is_whitespace(input[len]) && \
			input[len] != '$' && input[len] != '\"')
		len++;
	}
	out = malloc(sizeof(char) * len + 1);
	if (!out)
		return (NULL);
	while (i < len)
	{
		out[i] = input[i];
		i++;
	}
	out[i] = '\0';
	return (out);
}

char	*expand_generic(char *input)
{
	char	*out;
	int		len;
	int		i;

	out = NULL;
	len = 0;
	i = 0;
	while (input[len] && input[len] != '$' && input[len] != '\"')
		len++;
	out = malloc(sizeof(char) * len + 1);
	if (!out)
		return (NULL);
	while (i < len)
	{
		out[i] = input[i];
		i++;
	}
	out[i] = '\0';
	return (out);
}

//	if encounter a $, save that in temp value var and check env
char	*expand_string_dq(t_mshell *msh, char *input)
{
	char	*output;
	char	*param;
	char	*value;
	int		i;
	int		j;

	i = 0;
	j = 0;
	output = "";
	if (input[i] == '\"')
		i++;
	while (input[i])
	{
		param = NULL;
		value = NULL;
		if (input[i] == '$')
		{
			i++;
			if (input[i] == '\"' ||  is_whitespace(input[i]))
			{
				value = ft_strdup("$");
				i++;
			}
			else if (input[i])
			{
				param = isolate_param(&input[i]);
				i += ft_strlen(param);
				value = env_get_string(&msh->envlist, param);
			}
		}
		else
		{
			value = expand_generic(&input[i]);
			i += ft_strlen(value);
		}
		if (value)
			output = ft_strjoin(output, value);
		if (param)
			free(param);
		free(value);
		if (input[i] == '\"')
			i++;
	}
	return (output);
}
