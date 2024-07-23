/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envsets.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 15:31:31 by jcummins          #+#    #+#             */
/*   Updated: 2024/07/23 15:37:43 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_unset(t_envlist **envlist, const char *search)
{
	t_envlist	*find;

	find = env_search(envlist, search);
	if (find)
		env_del(&find);
	else
		ft_printf("Error, no parameter of that name found in env\n");
}

void	env_set(t_envlist **envlist, const char *search, const char *newval)
{
	t_envlist	*find;

	find = env_search(envlist, search);
	if (find)
	{
		free (find->value);
		find->value = ft_strdup(newval);
	}
	else
		ft_printf("Error, no parameter of that name found in env\n");
}

