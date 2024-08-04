/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_err.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akretov <akretov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 16:05:39 by akretov           #+#    #+#             */
/*   Updated: 2024/08/04 19:02:35 by akretov          ###   ########.fr       */
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

void	handle_exec_error(t_pipex *pipex, char *str)
{
	printf("%s", str);
	(void)pipex;
}
