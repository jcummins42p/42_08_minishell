/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 11:50:18 by jcummins          #+#    #+#             */
/*   Updated: 2024/08/06 13:35:21 by jcummins         ###   ########.fr       */
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
	if (input[len] == '$' || input[len] == '?')
		len++;
	else
	{
		while (ft_isalnum(input[len]))
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

int	expand_generic(char *input, char **output)
{
	int		len;
	int		i;

	*output = NULL;
	len = 0;
	i = 0;
	while (input[len] && input[len] != '$' && input[len] != '\"')
		len++;
	*output = malloc(sizeof(char) * len + 1);
	if (!(*output))
		return (0);
	while (i < len)
	{
		(*output)[i] = input[i];
		i++;
	}
	(*output)[i] = '\0';
	return (len);
}

int	expand_variable(t_mshell *msh, char *input, char **output)
{
	char	*param;
	int		len;

	len = 1;
	param = NULL;
	*output = NULL;
	if (input[len] == '\"' || is_whitespace(input[len]))
		(*output) = ft_strdup("$");
	else if (input[len])
	{
		param = isolate_param(&input[len]);
		len += ft_strlen(param);
		*output = env_get_string(&msh->envlist, param);
	}
	if (param)
		free(param);
	return (len);
}

//	if encounter a $, save that in temp value var and check env
char	*expand_string_dq(t_mshell *msh, char *input)
{
	char	*tmp;
	char	*output;
	char	*value;
	int		i;

	i = 0;
	output = ft_strdup("");
	if (input[i] == '\"')
		i++;
	while (input[i])
	{
		tmp = ft_strdup(output);
		free (output);
		if (input[i] == '$')
			i += expand_variable(msh, &input[i], &value);
		else
			i += expand_generic(&input[i], &value);
		if (value)
			output = ft_strjoin(tmp, value);
		free(value);
		free(tmp);
		if (input[i] == '\"')
			i++;
	}
	return (output);
}
