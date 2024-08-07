/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 17:53:00 by jcummins          #+#    #+#             */
/*   Updated: 2024/08/07 15:52:36 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//	initialises and assigns value to a node in env linked list
static int	env_init_value(char **value, char *envline, int start)
{
	int		len;
	int		i;

	len = 0;
	start++;
	i = start;
	while (envline[i++])
		len++;
	*value = malloc(sizeof(char) * (len + 1));
	if (*value == NULL)
		return (-1);
	i = 0;
	while (i < len)
		(*value)[i++] = envline[start++];
	(*value)[i] = '\0';
	return (len);
}

//	initialises and assigns parameter to a node in env linked list. Returns
//	length of that string so that the init value function can start at the
//	correct place in that line to retreive the following value
static int	env_init_param(char **param, char *envline)
{
	int		i;
	int		len;

	i = 0;
	while (envline[i] && envline[i] != '=')
		i++;
	len = i;
	*param = malloc(sizeof(char) * (len + 1));
	(*param)[i--] = '\0';
	while (i >= 0)
	{
		(*param)[i] = envline[i];
		i--;
	}
	return (len);
}

//	creates new node of env linked list. Parameter and value have already been
//	created when this is called.
int	env_new(t_envlist **env, const char *param, const char *val, t_vscope scope)
{
	t_envlist	*curr;
	t_envlist	*new;

	if (*param == '\0' || *val == '\0')
		return (0);
	new = malloc(sizeof(t_envlist));
	if (new == NULL)
		return (0);
	new->next = NULL;
	new->param = ft_strdup(param);
	new->value = ft_strdup(val);
	new->scope = scope;
	curr = *env;
	if (curr == NULL)
	{
		*env = new;
		new->prev = NULL;
	}
	else
	{
		curr = env_last(env);
		curr->next = new;
		new->prev = curr;
	}
	return (1);
}

//	makes new env node from a single string assignation that includes a '='
//	checks for validity done within the env_set function
void	env_from_str(t_envlist **envlist, char *str, t_vscope scope)
{
	char		*param;
	char		*value;
	int			len;

	param = NULL;
	value = NULL;
	len = env_init_param(&param, str);
	env_init_value(&value, str, len);
	env_set(envlist, param, value, scope);
	free(param);
	free(value);
}

char	*strcat_from_tokens(t_tokenlist *token)
{
	t_tokenlist	*curr;
	char		*output;
	char		*swap;

	swap = NULL;
	output = strdup("");
	curr = token;
	while (curr && curr->mtctype < PIPE)
	{
		swap = ft_strjoin(output, curr->expand);
		free (output);
		output = swap;
		if (curr->trail_space)
			break;
		curr = curr->next;
	}
	return (output);
}

void	env_from_tokens(t_envlist **envlist, t_tokenlist *token, int scope)
{
	char	*value;

	if (!token)
		return ;
	if (!token->trail_space && token->next)
		value = strcat_from_tokens(token->next);
	env_set(envlist, token->expand, value, scope);
}

//	takes *env[] input and creates env linked list
void	env_init(t_envlist **envlist, char *env[])
{
	int		i;
	char	*pid;
	char	*status;

	i = 0;
	status = ft_strdup("0");
	pid = ft_itoa(getpid());
	while (env[i])
		env_from_str(envlist, env[i++], ENVVAR);
	env_set(envlist, "$", pid, SHLVAR);
	env_set(envlist, "?", status, SHLVAR);
	env_set(envlist, "SHELL", "./minishell", ENVVAR);
	env_set(envlist, "PS1", "$ ", SHLVAR);
	free(pid);
	free(status);
}
