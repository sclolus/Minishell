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
	if (((t_token*)tree->left->content)->type == TYPE_TOKEN_STATEMENT)
		ret = ft_exec_statement(tree->left, env, path);
	else
		ret = ft_exec_ast(tree->left, env, path);
	if (!ret)
		return (ret);
	else if (((t_token*)tree->right->content)->type == TYPE_TOKEN_STATEMENT)
		ret = ft_exec_statement(tree->right, env, path);
	else
		ret = ft_exec_ast(tree->right, env, path);
	return (ret);
}

int32_t	ft_exec_token_and(t_btree *tree, char **env, char **path)
{
	int32_t	ret;

	ret = 0;
	if (((t_token*)tree->left->content)->type == TYPE_TOKEN_STATEMENT)
		ret = ft_exec_statement(tree->left, env, path);
	else
		ret = ft_exec_ast(tree->left, env, path);
	if (ret != 0)
		return (ret);
	else if (((t_token*)tree->right->content)->type == TYPE_TOKEN_STATEMENT)
		ret &= ft_exec_statement(tree->right, env, path);
	else
		ret &= ft_exec_ast(tree->right, env, path);
	return (ret);
}

int32_t	ft_exec_token_single_and(t_btree *tree, char **env, char **path)
{
	pid_t	pid;

	pid = fork();
	if (!pid)
	{
		if (((t_token*)tree->left->content)->type == TYPE_TOKEN_STATEMENT)
			ft_exec_asynchronous_statement(tree->left, env, path);
		else
			ft_exec_ast(tree->left, env, path);
		exit (0);
	}
	else
	{
		if (tree->right)
		{
			if (((t_token*)tree->right->content)->type == TYPE_TOKEN_STATEMENT)
				return (ft_exec_statement(tree->right, env, path));
			else
				return (ft_exec_ast(tree->right, env, path));
		}
	}
	return (-1);
}

int32_t	ft_exec_token_pipe(t_btree *tree, char **env, char **path)
{
	pid_t	pid;
	int		fd[2];
	int		stdin;
	int		ret;

	ret = 0;
	pid = fork();
	if (pid > 0)
	{
		wait(&ret);
		return (ret);
	}
	else
	{
		if (pipe(fd) == -1)
			exit (EXIT_FAILURE);
		close(0);
		stdin = dup(fd[1]);
		
	}
}
