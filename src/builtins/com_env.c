/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   com_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 16:17:54 by jcummins          #+#    #+#             */
/*   Updated: 2024/08/14 16:18:05 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	com_env(t_envlist **envlist, t_vscope scope)
{
	t_envlist	*curr;

	curr = *envlist;
	while (curr)
	{
		if (curr->value && curr->scope >= scope)
			printf("%s=%s\n", curr->param, curr->value);
		curr = curr->next;
	}
}
