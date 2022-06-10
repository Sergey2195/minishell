/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bultin_utils4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iannmari <iannmari@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 19:12:10 by iannmari          #+#    #+#             */
/*   Updated: 2022/06/10 19:14:32 by iannmari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		check_key2(char *key)
{
	int	i;

	i = 0;
	while (key[i] != '\0' && key[i] != '=')
	{
		if (!ft_isalnum(key[i]) && key[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

void	error_export(t_info *s, t_cmd *cmd, int i)
{
	printf("bash: export: `%s': not a valid identifier\n", cmd->av[i]);
	s->ret = 1;
}

int		parse_export(t_env *tmp, char *str)
{
	int	klen;
	int	vlen;
	int	i;

	klen = 0;
	vlen = 0;
	while (str[klen] != '=')
		klen++;
	if (!ft_calloc(sizeof(char), klen + 1, (void *)&tmp->key))
		exit(1);
	i = -1;
	while (++i < klen)
		tmp->key[i] = str[i];
	tmp->key[i] = '\0';
	if (str[klen + 1] == '\0')
		return (0);
	while (str[klen + 1 + vlen] != '\0')
		vlen++;
	if (!ft_calloc(sizeof(char), vlen + 1, (void *)&tmp->value))
		exit(1);
	i = -1;
	while (++i < vlen)
		tmp->value[i] = str[i + klen + 1];
	tmp->value[i] = '\0';
	return (1);
}