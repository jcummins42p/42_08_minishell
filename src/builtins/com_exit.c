/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   com_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 15:05:56 by jcummins          #+#    #+#             */
/*   Updated: 2024/08/19 18:23:00 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	com_exit_error_digit(t_mshell *msh, t_tokenlist *token)
{
	write(2, "msh: ", 5);
	write(2, token->expand, ft_strlen(token->expand));
	write(2, ": ", 2);
	write(2, token->next->expand, ft_strlen(token->next->expand));
	write(2, ": numeric argument required\n", 28);
	msh->exitcode = 2;
}

static void	com_exit_error_args(t_mshell *msh)
{
	write(2, "msh: exit: too many arguments\n", 30);
	msh->exitcode = 1;
}

void	com_exit(t_mshell *msh, t_tokenlist *token)
{
	int	i;

	i = 0;
	msh->running = false;
	if (token->next)
	{
		if (token->next->expand[i])
		{
			if (token->next->next)
			{
				com_exit_error_args(msh);
				return ;
			}
			if (!ft_isdigit(token->next->expand[i++]))
			{
				com_exit_error_digit(msh, token);
				return ;
			}
		}
		msh->exitcode = ft_atoi(token->next->expand);
	}
	if (msh->info->n_pipe == 0)
		printf("exit\n");
}
