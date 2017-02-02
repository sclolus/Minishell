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


/*void		ft_put_ast(t_btree *tree)
{

}*/

t_btree		*ft_add_ast_node(t_token *tokens, uint32_t index, t_btree *tree)
{
	t_btree	*tmp;

	tmp = tree;
	if (!tree || !tokens)
		exit (EXIT_FAILURE);
	while (tmp && tmp->content)
	{
		ft_putstr(((t_token*)tmp->content)->token.token);
		tmp = tmp->right;
	}
	tmp->content = tokens + index;
//	ft_putendl(((t_token*)tmp->content)->token.token);
	return (tree->right);
}

t_btree		*ft_arrange_tree(t_btree *nodes, uint32_t count)
{
	t_btree		*tmp;
	uint32_t	i;

	i = 1;
	ft_memset(nodes, 0, sizeof(nodes) * count);
	tmp = nodes;
	while (i < count)
	{
		while (tmp->right)
			tmp = tmp->right;
		tmp->right = nodes + i;
		i++;
	}
	return (nodes);
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
	if (!(nodes = malloc(sizeof(t_btree) * node_count)))
		exit (EXIT_FAILURE);
	nodes = ft_arrange_tree(nodes, node_count);
	while (i < count)
	{
		if (tokens[i].type == TYPE_TOKEN_STATEMENT)
		{
			ft_putendl(tokens[i].token.tokens[0]);
			while (tokens[i].type == TYPE_TOKEN_STATEMENT)
				i++;
			continue ;
		}
		else
			ft_putendl(tokens[i].token.token);
		if (tokens[i].type >= TYPE_TOKEN_OR
			&& tokens[i].type <= TYPE_TOKEN_PIPE)
		{
/*			ft_putstr(tokens[i].token.token);
			ft_putchar('\\');*/
			ft_add_ast_node(tokens, u++, nodes);
		}
		i++;
	}
	i = 0;
	while (i < node_count)
	{
		ft_putendl(((t_token*)nodes[i++].content)->token.token);
	}
	return (NULL);
}
