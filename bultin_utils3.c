/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bultin_utils3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iannmari <iannmari@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 19:04:53 by iannmari          #+#    #+#             */
/*   Updated: 2022/06/10 19:07:46 by iannmari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		check_env_length(t_env *head)
{
	int		len;
	t_env	*env;

	env = head;
	len = 0;
	while (env)
	{
		len++;
		env = env->next;
	}
	return (len);
}

char	*make_env_string(char *key, char *value, int has_equal)
{
	char	*result;
	int		len;
	int		i;
	int		j;

	len = check_len(key, value, has_equal);
	if (!ft_calloc(len, sizeof(char), (void *)&result))
		exit(1);
	i = 0;
	j = 0;
	while (key[i])
		result[j++] = key[i++];
	if (has_equal == TRUE)
	{
		result[j++] = '=';
		if (value)
		{
			result[j++] = '\"';
			while (*value)
				result[j++] = *value++;
			result[j++] = '\"';
		}
	}
	result[j] = '\0';
	return (result);
}

void	sorted_list(char **list, int size)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	while (i < size - 1)
	{
		j = 0;
		while (j < size - 1 - i)
		{
			if (ft_strncmp(list[j], list[j + 1], ft_strlen(list[j])) > 0)
			{
				temp = list[j];
				list[j] = list[j + 1];
				list[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
}

void	print_export(t_env *env_head)
{
	char	**env_list;
	t_env	*env;
	int		len;
	int		i;

	env = env_head;
	len = check_env_length(env_head);
	if (!ft_calloc(len + 1, sizeof(char *), (void **)&env_list))
		exit(1);
	env_list[len] = 0;
	i = 0;
	while (env)
	{
		env_list[i] = make_env_string(env->key,
						env->value, env->flag);
		env = env->next;
		i++;
	}
	sorted_list(env_list, len);
	i = 0;
	while (i < len)
		printf("declare -x %s\n", env_list[i++]);
	free_2d(env_list);
}