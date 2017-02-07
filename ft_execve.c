#include "minishell.h"

int32_t	ft_execve(char *filename, char *path, char **argv, char **env)
{
	char	*bin;

	if (!(bin = ft_strjoin(path, "/")))
		exit(EXIT_FAILURE);
	if (!(bin = ft_strjoin_f(bin, filename, 0)))
		exit(EXIT_FAILURE);
	if (filename)
	{
		if (execve(bin, argv, env))
			ft_putstr("error has occured");
		exit (EXIT_FAILURE);
	}
	return (-1);
}

int32_t	ft_exec_statement(t_btree *tree, char **env, char *path)
{
	char	*bin;
	pid_t	pid;
	int		ret;

	pid = fork();
	if (pid > 0)
	{
		wait(&ret);
		return (ret);
	}
	else
	{
		if (!(bin = ft_strjoin(path, "/")))
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

int32_t	ft_exec_token_or(t_btree *tree, char **env, char *path)
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

int32_t	ft_exec_token_and(t_btree *tree, char **env, char *path)
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

