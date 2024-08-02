/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_get.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 15:31:58 by jcummins          #+#    #+#             */
/*   Updated: 2024/08/02 17:31:35 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//	last node in linked list
t_envlist	*env_last(t_envlist **envlist)
{
	t_envlist	*curr;

	curr = *envlist;
	if (curr == NULL)
		return (NULL);
	while (curr->next)
	{
		curr = curr->next;
	}
	return (curr);
}

//	search env list for parameter by search string and return node
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

//	search env list for parameter by search string and return pointer to string
char	**env_get_value(t_envlist **envlist, const char *search)
{
	t_envlist	*find;

	find = env_search(envlist, search);
	if (find)
		return (&find->value);
	else
		return (NULL);
}

//	search env list for parameter by search string and return 'value' string
char	*env_get_string(t_envlist **envlist, const char *search)
{
	t_envlist	*find;

	find = env_search(envlist, search);
	if (find)
		return (ft_strdup(find->value));
	else
		return (ft_strdup(""));
}
