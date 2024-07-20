/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 17:10:23 by jcummins          #+#    #+#             */
/*   Updated: 2024/07/20 18:47:49 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expand_variable(t_envlist **envlist, char *param)
{
	char	**expand;

	expand = env_get(envlist, param);
	printf("%s\n", *expand);
}
