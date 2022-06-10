/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iannmari <iannmari@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 17:17:17 by iannmari          #+#    #+#             */
/*   Updated: 2022/06/10 17:52:10 by iannmari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*changed_str(char *origin, int start, int end, char *insert)
{
	char	*result;
	char	*front;
	char	*front_insert;
	char	*back;

	front = ft_substr(origin, 0, start);
	front_insert = ft_strjoin2(front, insert);
	back = ft_substr(origin, end + 1, ft_strlen(origin) - (end - start));
	result = ft_strjoin2(front_insert, back);
	free(front);
	free(back);
	free(insert);
	free(front_insert);
	return (result);
}

char	*ft_strjoin2(char *s1, char *s2)
{
	char	*res;
	size_t	len;
	int		i;

	if (!(s1) && !(s2))
		return (0);
	else if (!(s1) || !(s2))
	{
		if (!(s1))
			return (ft_strdup(s2));
		else
			return (ft_strdup(s1));
	}
	len = (ft_strlen(s1)) + (ft_strlen(s2));
	if (!ft_calloc(sizeof(char), len + 1, (void *)&res))
		exit(1);
	i = 0;
	while (*s1)
		res[i++] = *s1++;
	while (*s2)
		res[i++] = *s2++;
	res[i] = '\0';
	return (res);
}

int		is_operator_error(int type)
{
	if ((type >= 4 && type <= 6) || (type >= 8 && type <= 9))
		return (TRUE);
	return (FALSE);
}

void	free_token(t_token *token)
{
	t_token	*tmp;
	t_token	*next;

	tmp = token;
	while (tmp)
	{
		if (tmp->str)
			free(tmp->str);
		next = tmp->next;
		free(tmp);
		tmp = next;
	}
}