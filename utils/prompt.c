#include "../inc/minishell.h"

int	prompt(t_shell *shell)
{
	shell->line = "";
	while (shell->line)
	{
		set_term(shell);
		set_prompt(shell, &shell->cmd.prompt);
		signal(SIGINT, &m_sigkill);
		shell->line = readline(shell->cmd.prompt);
		if (!shell->line)
		{
			printf("exit\n");
			ft_exit(shell, &shell->cmd.parsed);
			//exit point here
			break ;
		}
		if (!quoting(&shell->cmd, shell->line))
			continue ;
		history_save(&shell->cmd, shell->line);
		tokenizer(&shell->cmd, shell->line);
		search_and_sub(&shell->cmd, shell->env);
		if (search_and_escape(&shell->cmd))
			check_cmd(shell);
		else
			printf("Missing quotes\n");
		restore_fd(shell);
		if (shell->line)
			free(shell->line);
		lstclear_pars(&shell->cmd.parsed);
	}
	// if (shell->line)
	// 	free(&shell->cmd.prompt);
	return (0);
}
