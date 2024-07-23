/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envget.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 15:31:58 by jcummins          #+#    #+#             */
/*   Updated: 2024/07/23 16:04:51 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_envlist	*env_search(t_envlist **envlist, const char *search)
{
	t_envlist	*curr;
	int			i;

	curr = *envlist;
	if (search == NULL)
		return (NULL);
	while (curr)
	{
		i = 0;
		while (curr->param[i] == search[i])
		{
			if (curr->param[i] == '\0' && search[i] == '\0')
			{
				return (curr);
			}
			i++;
		}
		curr = curr->next;
	}
	return (NULL);
}

char	**env_get_val(t_envlist **envlist, const char *search)
{
	t_envlist	*find;

	find = env_search(envlist, search);
	if (find)
		return (&find->value);
	else
		return (NULL);
}
