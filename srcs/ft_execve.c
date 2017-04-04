#include "minishell.h"

int32_t	ft_exec_asynchronous_statement(t_btree *tree, char **env, char **path)
{
	char	*bin;
	char	*path_tmp;

	
	if (!(path_tmp = ft_find_command(((t_token*)tree->content)->token.tokens[0], path)))
		return (-1);
	if (!(bin = ft_strjoin(path_tmp, "/")))
		exit(EXIT_FAILURE);
	if (!(bin = ft_strjoin_f(bin, ((t_token*)tree->content)->token.tokens[0], 0)))
			exit(EXIT_FAILURE);
	if (((t_token*)tree->content)->token.tokens[0])
	{
		if (execve(bin, ((t_token*)tree->content)->token.tokens, env))
			ft_putstr("error has occured");
		free(bin);
		exit (EXIT_FAILURE);
	}
	return (-1);
}

int32_t	ft_exec_f(t_btree *tree, char **env, char **path
				  , int32_t (*f)(t_btree*, char**, char**))
{
	if (tree)
	{
		if (((t_token*)tree->content)->type == TYPE_TOKEN_STATEMENT)
			return (f(tree, env, path));
		else
			return (ft_exec_ast(tree, env, path));
	}
	else
	{
		ft_putendl_fd(SHELL_NAME, 2);
		ft_putendl_fd("syntax error detected", 2);
		return (-1);
	}
}

int32_t	ft_exec_statement_no_fork(t_btree *tree, char **env, char **path)
{
	char	*bin;
	char	*path_tmp;

	if (!(path_tmp = ft_find_command(((t_token*)tree->content)->token.tokens[0], path)))
		exit(EXIT_FAILURE);
	if (!(bin = ft_strjoin(path_tmp, "/")))
		exit(EXIT_FAILURE);
	if (!(bin = ft_strjoin_f(bin, ((t_token*)tree->content)->token.tokens[0], 0)))
		exit(EXIT_FAILURE);
	if (((t_token*)tree->content)->token.tokens[0])
	{
		if (execve(bin, ((t_token*)tree->content)->token.tokens, env))
			ft_putstr("error has occured");
		free(bin);
		exit (EXIT_FAILURE);
	}
	return (-1);
}

int32_t	ft_exec_statement(t_btree *tree, char **env, char **path)
{
	char	*bin;
	pid_t	pid;
	char	*path_tmp;
	int		ret;

	pid = fork();
	if (pid > 0)
	{
		wait(&ret);
		return (ret);
	}
	else
	{
		if (!(path_tmp = ft_find_command(((t_token*)tree->content)->token.tokens[0], path)))
			return (-1);
		if (!(bin = ft_strjoin(path_tmp, "/")))
			exit(EXIT_FAILURE);
		if (!(bin = ft_strjoin_f(bin, ((t_token*)tree->content)->token.tokens[0], 0)))
			exit(EXIT_FAILURE);
		if (((t_token*)tree->content)->token.tokens[0])
		{
			if (execve(bin, ((t_token*)tree->content)->token.tokens, env))
				ft_putstr("error has occured");
			free(bin);
			exit (EXIT_FAILURE);
		}
	}
	return (-1);
}

int32_t	ft_exec_token_or(t_btree *tree, char **env, char **path)
{
	int32_t	ret;

	ret = 0;
# if REVERT
	if (((t_token*)tree->left->content)->type == TYPE_TOKEN_STATEMENT)
		ret = ft_exec_statement(tree->left, env, path);
	else
		ret = ft_exec_ast(tree->left, env, path);
# endif
	ret = ft_exec_f(tree->left, env, path, &ft_exec_statement);
	if (!ret)
		return (ret);
# if REVERT
	if (((t_token*)tree->right->content)->type == TYPE_TOKEN_STATEMENT)
		ret = ft_exec_statement(tree->right, env, path);
	else
		ret = ft_exec_ast(tree->right, env, path);
#endif
	ret = ft_exec_f(tree->right, env, path, &ft_exec_statement);
	return (ret);
}

int32_t	ft_exec_token_and(t_btree *tree, char **env, char **path)
{
	int32_t	ret;

	ret = 0;
#if REVERT
	if (((t_token*)tree->left->content)->type == TYPE_TOKEN_STATEMENT)
		ret = ft_exec_statement(tree->left, env, path);
	else
		ret = ft_exec_ast(tree->left, env, path);
#endif
	ret = ft_exec_f(tree->left, env, path, &ft_exec_statement);
	if (ret != 0)
		return (ret);
#if REVERT
	else if (((t_token*)tree->right->content)->type == TYPE_TOKEN_STATEMENT)
		ret &= ft_exec_statement(tree->right, env, path);
	else
		ret &= ft_exec_ast(tree->right, env, path);
#endif
	ret &= ft_exec_f(tree->right, env, path, &ft_exec_statement);
	return (ret);
}

int32_t	ft_exec_token_single_and(t_btree *tree, char **env, char **path)
{
	pid_t	pid;

	pid = fork();
	if (!pid)
	{
		ft_exec_f(tree->left, env, path, &ft_exec_asynchronous_statement);
		exit (0);
	}
	else
	{
		if (tree->right)
			return (ft_exec_f(tree->right, env, path, &ft_exec_statement));
		else
			return (0);
	}
	return (-1);
}

#if 1
int32_t	ft_exec_token_pipe(t_btree *tree, char **env, char **path)
{
	pid_t	pid;
	pid_t	pid_pipe;
	int		fd[2];
	int		ret;

	ret = 0;
	pid = fork();
	if (pid > 0)
	{
		waitpid(pid, &ret, 0);
		return (ret);
	}
	else if (!pid)
	{
		if (pipe(fd) == -1)
			exit(EXIT_FAILURE);
		pid_pipe = fork();
		if (pid_pipe > 0)
		{
			if (dup2(fd[0], 0) < 0)
				exit(EXIT_FAILURE);
			close (fd[1]);
			ft_exec_f(tree->right, env, path, &ft_exec_statement_no_fork);
			exit(EXIT_FAILURE);
		}
		else if (!pid_pipe)
		{
			if (dup2(fd[1], 1) < 0)
				exit (EXIT_FAILURE);
			close (fd[0]);
			exit(ft_exec_f(tree->left, env, path, &ft_exec_statement_no_fork));
		}
		else
			exit(EXIT_FAILURE);
	}
	else
		exit (EXIT_FAILURE);
}
#endif
