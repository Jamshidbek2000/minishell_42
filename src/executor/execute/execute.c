/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zstenger <zstenger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 21:22:11 by zstenger          #+#    #+#             */
/*   Updated: 2023/03/27 09:01:02 by zstenger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	execute(t_shell *shell, t_cmd_tbl *table)
{
	if (tables_have_wrong_redir(table, shell) == true)
	{
		redir_check(shell->trimmed_prompt);
		shell->exit_code = 258;
		free_cmd_tbls(shell->cmd_tbls);
		shell->cmd_tbls = NULL;
		return ;
	}
	handle_heredocs(table, shell);
	if (table != NULL && table->next == NULL && table_size(table) == 1)
		exec_without_pipes(table, shell);
	if (table != NULL && table->next != NULL)
	{
		shell->exec_on_pipe = TRUE;	
		exec_pipes(table, shell);
	}
	free_cmd_tbls(shell->cmd_tbls);
	shell->cmd_tbls = NULL;
}

int	table_size(t_cmd_tbl *table)
{
	int	i;

	i = 0;
	while (table != NULL)
	{
		i++;
		table = table->next;
	}
	return (i);
}
