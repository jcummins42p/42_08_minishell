/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 15:32:23 by jcummins          #+#    #+#             */
/*   Updated: 2024/08/16 15:51:24 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_final_fd(void)
{
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
}

void	shell_free(t_mshell *msh)
{
	if (msh->tokens)
		token_clear(&msh->tokens);
	env_list_clear(&msh->envlist);
	env_string_clear(msh->env);
	if (msh->lineread)
		free(msh->lineread);
	free(msh->info);
	close_final_fd();
}

void	shell_set_envptrs(t_mshell *msh)
{
	char	buff[2048];
	msh->prompt = env_get_value(&msh->envlist, "PS1");
	msh->path = env_get_value(&msh->envlist, "PATH");
	env_set(&msh->envlist, "OLDPWD", getcwd(buff, 2048), ENVVAR);
}

void	shell_disable_echo()
{
	struct termios mterm;

	tcgetattr(STDIN_FILENO, &mterm);
	mterm.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &mterm);
}

void	shell_init(t_mshell *msh)
{
	/*int g_siginfo = 0;*/
	shell_disable_echo();
	msh->pipex = NULL;
	msh->tokens = NULL;
	msh->info = malloc(sizeof(t_token_inf));
	msh->envlist = NULL;
	msh->env = NULL;
	msh->prompt = NULL;
	msh->path = NULL;
	msh->lineread = NULL;
	msh->running = true;
	msh->exitcode = 0;
}
