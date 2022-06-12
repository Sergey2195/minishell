/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iannmari <iannmari@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 12:02:45 by iannmari          #+#    #+#             */
/*   Updated: 2022/06/12 11:59:19 by iannmari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	prepare_token_and_cmd(t_info *state)
{
	free_cmd(state->cmd_head);
	state->token_head = 0;
	state->cmd_head = 0;
	state->path_head = 0;
	free(state->input);
	state->input = 0;
	free(state->input2);
	state->input2 = 0;
	reset_buffer(state);
}

void	start(t_info *s)
{
	write(1, "bash", 4);
	init_terminal(s);
	while (1)
	{
		write(1, "> ", 2);
		if (!term_loop(s))
		{
			reset_buffer(s);
			if (g_info.input)
				g_info.input2 = ft_strdup(g_info.input);
			break ;
		}
	}
	tcsetattr(0, TCSANOW, &g_info.term.save);
	tokenizer(0, 1);
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	init_info(&g_info);
	signal(SIGINT, (void *)sig);
	signal(SIGQUIT, (void *)sig);
	init_env(envp, &g_info);
	while (1)
	{
		start(&g_info);
		executor(&g_info, g_info.cmd_head, envp);
		prepare_token_and_cmd(&g_info);
	}
}


