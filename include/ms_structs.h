/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_structs.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akretov <akretov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 14:23:39 by jcummins          #+#    #+#             */
/*   Updated: 2024/08/09 14:22:55 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_STRUCTS_H
# define MS_STRUCTS_H

typedef struct s_pipex		t_pipex;
typedef struct s_envlist	t_envlist;
typedef struct s_tokenlist	t_tokenlist;
typedef struct s_mshell		t_mshell;

typedef struct s_pipex
{
	t_tokenlist	**cmd_tokens;
	pid_t		*pid;
	int			status;
	int			fd_pipe[2];		// needed for pipe
	int			fd_in;			// this is for re-direction - From
	int			fd_out;			// this is for re-direction - To
	char		**cmd_paths;
	char		**cmd_args;
	char		*cmd;
}	t_pipex;

typedef struct s_envlist
{
	struct s_envlist	*next;
	struct s_envlist	*prev;
	t_vscope			scope;
	char				*param;	// environment variable
	char				*value;	// variable value
}	t_envlist;

typedef struct s_tokenlist
{
	struct s_tokenlist	*next;
	struct s_tokenlist	*prev;
	int					index;
	char				*token;			// metachar or generic string
	char				*expand;
	t_tokentype			tokentype;		// GENERIC, METACHAR, COMMAND
	t_comtype			comtype;		// enum for quick ref tokentype
	t_mtctype			mtctype;		// enum for quick ref tokentype
	int					pos;			// index of first char within string
	bool				trail_space;	// for printing env variable with space
}	t_tokenlist;

typedef struct s_token_inf
{
	int			n_pipe;
	int			n_ass;
	int			n_rdin;
	int			n_rdout;
	int			n_rdapp;
	int			n_delimit;
}	t_token_inf;

typedef struct s_mshell
{
	t_pipex		*pipex;
	t_tokenlist	*tokens;
	t_token_inf	*info;
	t_envlist	*envlist;
	char		**env;
	char		**prompt;
	char		**path;
	char		*lineread;
	t_valid_in	valid_input;
	bool		running;
	int			exitcode;
}	t_mshell;

#endif
