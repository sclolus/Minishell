#include "minishell.h"

uint32_t	ft_get_branches_count(t_token *tokens, uint32_t count)
{
	uint32_t	i;
	uint32_t	branches_count;

	i = 0;
	branches_count = 0;
	while (i < count)
	{
		if (tokens[i].type >= TYPE_TOKEN_OR
			&& tokens[i].type <= TYPE_TOKEN_PIPE)
			branches_count++;
		i++;
	}
	return (branches_count);
}

void		ft_put_ast_level(t_btree *tree, uint32_t level)
{
	char	**tmp;

	tmp = NULL;
	if (level > 0)
	{
		if (tree->left)
			ft_put_ast_level(tree->left, level - 1);
		if (tree->right)
			ft_put_ast_level(tree->right, level - 1);
	}
	else
	{
		if (((t_token*)tree->content)->type == TYPE_TOKEN_STATEMENT)
		{
			tmp = ((t_token*)tree->content)->token.tokens;
			while (*tmp)
			{
				ft_putstr(*tmp++);
				ft_putchar(' ');
			}
		}
		else
			ft_putstr(((t_token*)tree->content)->token.token);
		ft_putchar(' ');
	}
}

uint32_t	ft_get_max_level_tree(t_btree *tree)
{
	uint32_t	left_count;
	uint32_t	right_count;

	left_count = 0;
	right_count = 0;
	if (tree)
	{
		if (tree->left)
			left_count = ft_get_max_level_tree(tree->left);
		if (tree->right)
			right_count = ft_get_max_level_tree(tree->right);
		return (ft_max(left_count, right_count) + 1);
	}
	return (0);
}

void		ft_put_ast(t_btree *tree)
{
	uint32_t	i;
	uint32_t	level_max;

	i = 0;
	level_max = ft_get_max_level_tree(tree);
	while (i < level_max)
	{
		ft_put_ast_level(tree, i);
		ft_putchar('\n');
		i++;
	}
}

t_btree		*ft_add_ast_node(t_token *tokens, t_btree *tree)
{
	t_btree	*tmp;

	tmp = tree;
	if (!tree || !tokens)
		exit (EXIT_FAILURE);
	while (tmp->right && tmp->content)
		tmp = tmp->right;
	tmp->content = tokens;
	return (tree->right);
}

t_btree		*ft_arrange_tree(t_btree *nodes, uint32_t count)
{
	t_btree		*tmp;
	uint32_t	i;

	i = 1;
	ft_memset(nodes, 0, sizeof(t_btree) * (count + 1));
	tmp = nodes;
	while (i < count)
	{
		while (tmp->right)
			tmp = tmp->right;
		tmp->right = nodes + i;
		tmp = nodes;
		i++;
	}
	return (nodes);
}

uint32_t		ft_add_ast_statement(t_token *token, t_btree *tree)
{
	if (tree)
	{
		if (!tree->content)
		{
			tree->content = token;
			return (1);
		}
		if (tree->left)
		{
			if (ft_add_ast_statement(token, tree->left))
				return (1);
		}
		else if (((t_token*)tree->content)->type >= TYPE_TOKEN_OR
				 && ((t_token*)tree->content)->type <= TYPE_TOKEN_PIPE)
		{
			if (!(tree->left = (t_btree*)malloc(sizeof(t_btree))))
				exit (EXIT_FAILURE);
			tree->left->content = token;
			return (1);
		}
		if (tree->right)
		{
			if (ft_add_ast_statement(token, tree->right))
				return (1);
		}
		else if (((t_token*)tree->content)->type >= TYPE_TOKEN_OR
				 && ((t_token*)tree->content)->type <= TYPE_TOKEN_PIPE)
		{
			if (!(tree->right = (t_btree*)malloc(sizeof(t_btree))))
				exit (EXIT_FAILURE);
			tree->right->content = token;
			return (1);
		}
	}
	return (0);
}

t_btree		*ft_get_ast_tree(t_token *tokens, uint32_t count)
{
	uint32_t	i;
	uint32_t	u;
	uint32_t	node_count;
	t_btree		*nodes;
	

	i = 0;
	u = 0;
	node_count = ft_get_branches_count(tokens, count);
	if (!(nodes = malloc(sizeof(t_btree) * node_count + 1)))
		exit (EXIT_FAILURE);
	nodes = ft_arrange_tree(nodes, node_count);
	while (i < count)
	{
		if (tokens[i].type >= TYPE_TOKEN_OR
			&& tokens[i].type <= TYPE_TOKEN_PIPE)
			ft_add_ast_node(tokens + i, nodes);
		i++;
	}
	i = 0;
	while (i < count)
	{
#if 0
		if (!(tokens[i].type >= TYPE_TOKEN_OR
			  && tokens[i].type <= TYPE_TOKEN_PIPE))
#endif
			if (tokens[i].type == TYPE_TOKEN_STATEMENT)
			{
				ft_add_ast_statement(tokens + i, nodes);
				while (tokens[i].type == TYPE_TOKEN_STATEMENT)
					i++;
			}
		i++;
	}
/*	ft_put_ast(nodes);*/
	return (nodes);
}
