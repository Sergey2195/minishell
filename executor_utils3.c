/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iannmari <iannmari@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 19:20:46 by iannmari          #+#    #+#             */
/*   Updated: 2022/06/10 19:25:12 by iannmari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_path	*create_path(char *path_str)
{
	t_path	*path;

	if (!ft_calloc(1, sizeof(t_path), (void *)&path))
		exit(1);
	path->path = ft_strdup(path_str);
	path->next = 0;
	return (path);
}

void	add_path_back(t_path **head, char *path_str)
{
	t_path	*path;

	if (*head == NULL)
		*head = create_path(path_str);
	else
	{
		path = *head;
		while (path->next)
			path = path->next;
		path->next = create_path(path_str);
	}
}

void	parse_path(t_info *s)
{
	char	*path_env;
	char	**path_list;
	t_path	*path;
	int		i;

	(void)path;
	path_env = find_env_val(s->env_head, "PATH");
	path_list = ft_split(path_env, ':');
	path = s->path_head;
	i = 0;
	while (path_list[i])
	{
		add_path_back(&s->path_head, path_list[i]);
		i++;
	}
	free_2d(path_list);
}

int		find_success_cmd(t_info *s, t_cmd *cmd, char *path, DIR *dir_ptr)
{
	make_path(cmd, path);
	closedir(dir_ptr);
	free_path(s->path_head);
	s->path_head = 0;
	return (1);
}

int		find_command(t_info *s, t_cmd *cmd)
{
	DIR				*dir_ptr;
	struct dirent	*f;
	t_path			*p;

	parse_path(s);
	p = s->path_head;
	while (p)
	{
		dir_ptr = opendir(p->path);
		while (dir_ptr)
		{
			f = readdir(dir_ptr);
			if (f == 0)
				break ;
			else if (!ft_strcmp(f->d_name, ".") || !ft_strcmp(f->d_name, ".."))
				continue ;
			else if (!ft_strcmp(cmd->av[0], f->d_name))
				return (find_success_cmd(s, cmd, p->path, dir_ptr));
		}
		p = p->next;
		closedir(dir_ptr);
	}
	free_path(s->path_head);
	s->path_head = 0;
	return (0);
}