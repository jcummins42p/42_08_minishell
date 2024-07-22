/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_0.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akretov <akretov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 14:58:16 by akretov           #+#    #+#             */
/*   Updated: 2024/07/22 15:19:47 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	pipe_args_fill(int num_pipes, int *pipe_pos, char **pipe_arg[], char *ptr)
{
	int start = 0;
	int	i;

	start = 0;
	i = 0;
	while (i <= num_pipes)
	{
		int length = pipe_pos[i] - start;
		(*pipe_arg)[i] = (char *)malloc(sizeof(char) * (length + 1));
		strncpy((*pipe_arg)[i], ptr + start, length);
		(*pipe_arg)[i][length] = '\0';
		 printf("Argument for pipe %i is %s\n", i, (*pipe_arg)[i]);
		start = pipe_pos[i] + 1; // Move start to character after '|'
		i++;
	}
}

void	ft_pipe_init(t_tokenlist *tokens, char *ptr, char *env[])
{
	char	**pipe_arg;
	int		*pipe_pos;
	int		num_pipes;

	num_pipes = token_count_type(&tokens, "|");
	pipe_pos = (int *)malloc(sizeof(int) * (num_pipes + 1));		  // +1 because for input test | arg   we have 2 arguments test and arg.
	pipe_arg = (char **)malloc(sizeof(char *) * (num_pipes + 1 + 1)); // +1 for NULL termination

	// Get pipe positions
	// printf("Number of pipes: %i\n", num_pipes);
	token_pos_type(&tokens, &pipe_pos, "|");
	// Get end of the line positions           || the re-direction
	pipe_pos[num_pipes] = ft_strlen(ptr);

	pipe_args_fill(num_pipes, pipe_pos, &pipe_arg, ptr);
	pipe_arg[num_pipes + 1] = NULL;

	ft_pipe(num_pipes, pipe_arg, env);

	//free
	free(pipe_pos);	
	for (int i = 0; i <= num_pipes; i++)
		free(pipe_arg[i]);
	free(pipe_arg);
}
