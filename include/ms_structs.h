/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_structs.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akretov <akretov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 14:23:39 by jcummins          #+#    #+#             */
/*   Updated: 2024/07/24 17:07:51 by jcummins         ###   ########.fr       */
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
	char				*token;	// which token $ | >>, command or generic string
	t_tokentype			tokentype; // GENERIC, METACHAR, COMMAND
	t_comtype			comtype;	// enum for quick ref tokentype
	t_mtctype			mtctype;	// enum for quick ref tokentype
	int					pos;	// index of first char within string
	int					width;	// width of token in char
	char				*var;	// variable given following $
	struct s_envlist	*envvar;	// if token is $, a pointer to is env var
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
