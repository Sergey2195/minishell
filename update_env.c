/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iannmari <iannmari@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 12:56:11 by iannmari          #+#    #+#             */
/*   Updated: 2022/06/10 12:57:58 by iannmari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*find_env(t_env *head, char *key)
{
	t_env *env;

	env = head;
	while (env)
	{
		if (!ft_strcmp(env->key, key))
			return (env);
		env = env->next;
	}
	return (NULL);
}

void	update_env(t_env *head, char *key, char *value, int flag)
{
	t_env	*env;

	env = find_env(head, key);
	if (env == NULL)
		add_env_back(&head, key, value, flag);
	else
	{
		if (env->value)
		{
			free(env->value);
			if (value)
				env->value = ft_strdup(value);
			else
				env->value = 0;
		}
		else
		{
			if (value)
				env->value = ft_strdup(value);
		}
		env->flag = flag;
	}
}
