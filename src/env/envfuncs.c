/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envfuncs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 18:25:53 by jcummins          #+#    #+#             */
/*   Updated: 2024/07/20 18:47:16 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	env_unset(t_envlist **envlist, const char *search)
{
	t_envlist	*curr;
	int			i;

	curr = *envlist;
	while (curr)
	{
		i = 0;
		while (curr->param[i] == search[i])
		{
			if (curr->param[i] == '\0' && search[i] == '\0')
			{
				env_del(&curr);
				return ;
			}
			i++;
		}
		curr = curr->next;
	}
	ft_printf("Error, no parameter of that name found in env\n");
}

void	env_set(t_envlist **envlist, const char *search, const char *newval)
{
	t_envlist	*curr;
	int			i;

	curr = *envlist;
	while (curr)
	{
		i = 0;
		while (curr->param[i] == search[i])
		{
			if (curr->param[i] == '\0' && search[i] == '\0')
			{
				free (curr->value);
				curr->value = ft_strdup(newval);
				return ;
			}
			i++;
		}
		curr = curr->next;
	}
	ft_printf("Error, no parameter of that name found in env\n");
}

char	**env_get(t_envlist **envlist, const char *search)
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
				return (&curr->value);
			}
			i++;
		}
		curr = curr->next;
	}
	return (NULL);
}

void	env_print(t_envlist **envlist)
{
	t_envlist	*curr;

	curr = *envlist;
	while (curr)
	{
		printf("%s=%s\n", curr->param, curr->value);
		curr = curr->next;
	}
}
