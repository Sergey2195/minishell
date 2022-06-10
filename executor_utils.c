/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iannmari <iannmari@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 18:25:34 by iannmari          #+#    #+#             */
/*   Updated: 2022/06/10 18:57:12 by iannmari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_syntax_error(t_info *s, t_cmd *cmd)
{
	if (cmd->type == -1)
		printf("error : quote error\n");
	else if (cmd->type == -2)
		printf("bash: syntax error near unexpected token `|'\n");
	else if (cmd->type == -3)
		printf("bash: syntax error near unexpected token `;'\n");
	else if (cmd->type == -4)
		printf("bash: syntax error near unexpected token `||'\n");
	else if (cmd->type == -5)
		printf("bash: syntax error near unexpected token `;;'\n");
	else if (cmd->type == -6)
		printf("bash: syntax error near unexpected token `newline'\n");
	s->ret = 258;
}

void	set_pipe(t_cmd *cmd)
{
	if (cmd->type == 8
		|| (cmd->next != 0 && cmd->next->type == 8))
	{
		if (cmd->type != 8)
			dup2(cmd->pip[1], 1);
		else if (cmd->next == 0 || cmd->type == 9)
			dup2(cmd->prev->pip[0], 0);
		else
		{
			dup2(cmd->prev->pip[0], 0);
			dup2(cmd->pip[1], 1);
		}
	}
}