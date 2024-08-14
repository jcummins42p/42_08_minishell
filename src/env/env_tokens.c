/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_tokens.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 15:11:42 by jcummins          #+#    #+#             */
/*   Updated: 2024/08/14 15:17:22 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*strcat_from_tokens(t_tokenlist *token, t_mtctype terminate)
{
	char		*output;
	char		*swap;

	swap = NULL;
	output = strdup("");
	while (token && token->mtctype < terminate)
	{
		swap = ft_strjoin(output, token->expand);
		free (output);
		output = swap;
		if (token->trail_space)
			break ;
		token = token->next;
	}
	return (output);
}

void	env_from_tokens(t_envlist **envlist, t_tokenlist **token, int scope)
{
	t_tokenlist	*curr;
	char		*value;
	char		*param;

	curr = *token;
	if (!curr
		|| !curr->next
		|| curr->trail_space
		|| curr->next->mtctype >= PIPE)
		return ;
	param = strcat_from_tokens(curr, ASS);
	while (curr && !curr->trail_space && curr->mtctype != ASS)
		curr = curr->next;
	if (!curr || (curr && curr->mtctype != ASS))
		;
	else
	{
		curr = curr->next;
		value = strcat_from_tokens(curr, PIPE);
		env_set(envlist, param, value, scope);
		free(value);
	}
	free(param);
}
