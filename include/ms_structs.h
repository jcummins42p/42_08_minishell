/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_structs.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akretov <akretov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 14:23:39 by jcummins          #+#    #+#             */
/*   Updated: 2024/07/29 14:38:57 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_STRUCTS_H
# define MS_STRUCTS_H

typedef struct s_pipex t_pipex;
typedef struct s_envlist t_envlist;
typedef struct s_tokenlist t_tokenlist;
typedef struct s_mshell t_mshell;

typedef enum e_tokentype
{
	GENERIC,
	METACHAR,
	COMMAND
}	t_tokentype;

typedef enum e_comtype
{
	NO_COM,
	ECHO,
	CD,
	PWD,
	EXPORT,
	UNSET,
	ENV,
	EXIT
}	t_comtype;

typedef enum e_mtctype
{
	NO_MTC,
	DOLLAR,		// $ - environment variable
	PIPE,		// |
	SQUOTE,		// '
	DQUOTE,		// "
	RDIN,		// < - redirect input
	RDOUT,		// > - redirect output (overwrite)
	RDAPP,		// >> - redirect output (append)
	DELIMIT		// <<
}	t_mtctype;

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
	char				*token;			// metachar or generic string
	t_tokentype			tokentype; 		// GENERIC, METACHAR, COMMAND
	t_comtype			comtype;		// enum for quick ref tokentype
	t_mtctype			mtctype;		// enum for quick ref tokentype
	int					pos;			// index of first char within string
	int					width;			// width of token in char
	char				*var;			// variable given after $ or between ""
	bool				trail_space;	// for printing env variable with space
	struct s_envlist	*envvar;		// if token is $, pointer to its env var
	struct s_tokenlist	*next;
	struct s_tokenlist	*prev;
}	t_tokenlist;

typedef struct s_token_inf
{
	int			n_dollar;
	int			n_pipe;
	int			n_squote;
	int			n_dquote;
	int			n_rdin;
	int			n_rdout;
	int			n_rdapp;
	int			n_delimit;
}	t_token_inf;

typedef struct s_mshell
{
	t_tokenlist	*tokens;
	t_token_inf	*info;
	t_envlist	*envlist;
	char		**env;
	char		**prompt;
	char		**path;
	char		*lineread;
}	t_mshell;

#endif
