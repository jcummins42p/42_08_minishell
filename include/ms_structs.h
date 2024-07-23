/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_structs.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akretov <akretov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 14:23:39 by jcummins          #+#    #+#             */
/*   Updated: 2024/07/23 14:57:09 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_STRUCTS_H
# define MS_STRUCTS_H


typedef struct s_pipex t_pipex;
typedef struct s_envlist t_envlist;
typedef struct s_tokenlist t_tokenlist;
typedef struct s_mshell t_mshell;

typedef struct s_pipex
{
	pid_t	*pid;
	int		fd_pipe[2];		// not sure if needed
	int		fd_in;			// this is for re-direction - From 
	int		fd_out;			// this is for re-direction - To
	char	*paths;
	char	**cmd_paths;
	char	**cmd_args;
	char	*cmd;
}	t_pipex;

typedef struct s_envlist
{
	char				*param;	// environment variable
	char				*value; // variable value
	struct s_envlist	*next;
	struct s_envlist	*prev;
}	t_envlist;

typedef struct s_tokenlist
{
	char				*token;	// which token $ | >> etc
	//char				*param;	// the variable following a $
	//char				*value;	// the variable following a $
	int					pos;	// index of first char within string
	int					width;	// width of token in char
	struct	s_envlist	*envvar;	// if token is $, a pointer to is env var
	struct s_tokenlist	*next;
	struct s_tokenlist	*prev;
}	t_tokenlist;

typedef struct s_mshell
{
	t_tokenlist	*tokens;
	t_envlist	*envlist;
	char		*lineread;
	char		*prompt;
}	t_mshell;

#endif
