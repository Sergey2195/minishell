/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iannmari <iannmari@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 12:32:55 by iannmari          #+#    #+#             */
/*   Updated: 2022/06/12 12:18:46 by iannmari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_key_value(char *key, char *value)
{
	if (key)
		free(key);
	if (value)
		free(value);
}

t_env	*create_env(char *key, char *value, int flag)
{
	t_env	*env;

	if (!ft_calloc(1, sizeof(t_env), (void *)&env))
		exit(1);
	env->key = ft_strdup(key);
	env->flag = flag;
	env->next = 0;
	if (value)
		env->value = ft_strdup(value);
	else
		env->value = ft_strdup("");
	return (env);
}

void	add_env_back(t_env **head, char *key, char *value, int flag)
{
	t_env	*env;

	if (*head == NULL)
		*head = create_env(key, value, flag);
	else
	{
		env = *head;
		while (env->next)
			env = env->next;
		env->next = create_env(key, value, flag);
	}
}

int	find_equal(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (i);
		i++;
	}
	return (-1);
}

void	init_env(char **envp, t_info *info)
{
	int		i;
	int		j;
	char	*key;
	char	*value;
	int		eq;

	i = 0;
	while (envp[i])
	{
		j = 0;
		eq = find_equal(envp[i]);
		if (eq == -1)
		{
			printf("envp error\n");
			exit(EXIT_FAILURE);
		}
		key = ft_substr(envp[i], 0, eq);
		value = ft_substr(envp[i], eq++, ft_strlen(envp[i]));
		add_env_back(&(info->env_head), key, value, 1);
		free_key_value(key, value);
		i++;
	}
	update_env(info->env_head, "OLDPWD", "", 0);
}