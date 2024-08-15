/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   com_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 15:05:56 by jcummins          #+#    #+#             */
/*   Updated: 2024/08/15 13:55:27 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	com_exit(t_mshell *msh, t_tokenlist *token)
{
	int	i;

	i = 0;
	msh->running = false;
	if (token->next)
	{
		while (token->next->expand[i])
		{
			if (!ft_isdigit(token->next->expand[i++]))
			{
				printf("msh: %s: %s: numeric argument required\n", \
						token->expand, token->next->expand);
				msh->exitcode = 2;
				close(msh->pipex->fd_pipe[0]);
				close(msh->pipex->fd_pipe[1]);
				return ;
			}
		}
		msh->exitcode = ft_atoi(token->next->expand);
	}
	if (msh->info->n_pipe == 0)
		printf("exit\n");
}
