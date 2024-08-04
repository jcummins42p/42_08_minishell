/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_file_d.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akretov <akretov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 18:49:01 by akretov           #+#    #+#             */
/*   Updated: 2024/08/04 18:57:01 by akretov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_handle_redirection(t_pipex *pipex, t_tokenlist **tokens)
{
	if ((*tokens)->mtctype == RDIN)
	{
		*tokens = (*tokens)->next;
		pipex->fd_in = ft_open_file((*tokens)->token, O_RDONLY, 0);
	}
	else if ((*tokens)->mtctype == RDOUT)
	{
		*tokens = (*tokens)->next;
		pipex->fd_out = ft_open_file((*tokens)->token, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	}
	else if ((*tokens)->mtctype == RDAPP)
	{
		*tokens = (*tokens)->next;
		pipex->fd_out = ft_open_file((*tokens)->token, O_WRONLY | O_CREAT | O_APPEND, 0644);
	}
	*tokens = (*tokens)->next;
}

int	ft_open_file(const char *filename, int flags, mode_t mode)
{
	int	fd;
	
	fd = open(filename, flags, mode);
	if (fd == -1)
	{
		write(STDERR_FILENO, "Couldn't open the file\n", 23);
	}
	return (fd);
}
