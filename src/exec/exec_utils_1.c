/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akretov <akretov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 14:51:39 by akretov           #+#    #+#             */
/*   Updated: 2024/08/04 18:10:47 by akretov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void populate_args(t_pipex *pipex, t_tokenlist **tokens, char **arg)
{
	int i = 0;
	while (*tokens && (*tokens)->mtctype != PIPE)
	{
		if ((*tokens)->mtctype == RDIN || (*tokens)->mtctype == RDOUT || (*tokens)->mtctype == RDAPP)
			ft_handle_redirection(pipex, tokens);
		else
		{
			if ((*tokens)->expand)
				arg[i] = ft_strdup((*tokens)->expand);
			else if ((*tokens)->var)
				arg[i] = ft_strdup((*tokens)->var);
			else
				arg[i] = ft_strdup((*tokens)->token);
			i++;
			*tokens = (*tokens)->next;
		}
	}
	arg[i] = NULL;
}

void handle_exec_error(t_pipex *pipex, char *str)
{
	printf("%s", str);
	(void)pipex;
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

int count_args(t_tokenlist *tokens)
{
	int	i;
	
	i  = 0;
	while (tokens && tokens->mtctype != PIPE)
	{
		if (tokens->mtctype != RDIN && tokens->mtctype != RDOUT && tokens->mtctype != RDAPP)
			i++;
		tokens = tokens->next;
	}
	return i;
}

void	cleanup(t_pipex *pipex, int n_pipes)
{
	int	k;

	k = 0;
	while (k < n_pipes + 1)
	{
		waitpid(pipex->pid[k], NULL, 0);
		k++;
	}
	close(pipex->fd_in);
	close(pipex->fd_out);
	// free(pipex->pid);
	// free_pipex(pipex);
}
