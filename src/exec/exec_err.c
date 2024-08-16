/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_err.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akretov <akretov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 16:05:39 by akretov           #+#    #+#             */
/*   Updated: 2024/08/13 20:15:24 by akretov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	msg(const char *err)
{
	write(2, err, ft_strlen(err));
	return (1);
}

void	msg_error(char *err, t_pipex *pipex)
{
	free(pipex);
	perror(err);
	exit (1);
}

void	handle_exec_error(t_pipex *pipex, char *str, char *arg)
{
	write(STDERR_FILENO, arg, ft_strlen(arg));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, str, ft_strlen(str));
	write(STDERR_FILENO, "\n", 1);
	(void)pipex;
}
