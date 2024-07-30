/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akretov <akretov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 16:05:39 by akretov           #+#    #+#             */
/*   Updated: 2024/07/30 16:06:48 by jcummins         ###   ########.fr       */
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

// can be used to find any value based on the param - if we add additional arg char *value
char	*find_path(t_envlist *env)
{
	while (env->next != NULL)
	{
		if (ft_strncmp("PATH", env->param, 4) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

char	*get_cmd(char **paths, char *cmd)
{
	char	*tmp;
	char	*command;

	while (*paths)
	{
		tmp = ft_strjoin(*paths, "/");
		command = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(command, 0) == 0)
			return (command);
		free(command);
		paths++;
	}
	return (NULL);
}

// in the future create a function that frees char **av
void	free_pipex(t_pipex *pipex)
{
	int	i;

	if (pipex == NULL)
		return ;
	i = 0;
	if (pipex->cmd_args != NULL)
	{
		while (pipex->cmd_args[i])
		{
			free(pipex->cmd_args[i]);
			i++;
		}
		free(pipex->cmd_args);
	}
	i = 0;
	if (pipex->cmd_paths != NULL)
	{
		while (pipex->cmd_paths[i])
		{
			free(pipex->cmd_paths[i]);
			i++;
		}
		free(pipex->cmd_paths);
	}
	if (pipex->cmd != NULL)
		free(pipex->cmd);
	/*if (pipex->pid != NULL)*/
		/*free(pipex->pid);*/
	free(pipex);
}
