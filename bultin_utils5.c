/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bultin_utils5.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iannmari <iannmari@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 19:15:44 by iannmari          #+#    #+#             */
/*   Updated: 2022/06/10 19:16:52 by iannmari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_one_env(t_env *env)
{
	free(env->key);
	free(env->value);
	free(env);
}

void	delete_env(t_env *head, char *key)
{
	t_env	*env;
	t_env	*pre;

	env = head;
	while (env)
	{
		if (!ft_strncmp(key, env->key, ft_strlen(env->key)))
		{
			pre->next = env->next;
			free_one_env(env);
			return ;
		}
		else
			pre = env;
		env = env->next;
	}
}

int		check_key(char *key)
{
	int	i;

	i = 0;
	while (key[i])
	{
		if (!ft_isalnum(key[i]) && key[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

void	ft_unset(t_info *s, t_cmd *cmd)
{
	int		i;

	s->ret = 0;
	if (cmd->ac > 1)
	{
		i = 1;
		while (i < cmd->ac)
		{
			if (!check_key(cmd->av[i]))
			{
				printf("bash: unset: `%s': not a valid identifier\n",
					cmd->av[i]);
				s->ret = 1;
			}
			else
				delete_env(s->env_head, cmd->av[i]);
			i++;
		}
	}
}