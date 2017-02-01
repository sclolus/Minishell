#include "minishell.h"

t_btree	*ft_btreenew(void *content, uint32_t content_size)
{
	t_btree	*new;
	void	*mem;

	if (!(new = (t_btree*)malloc(sizeof(t_btree*))))
		exit (EXIT_FAILURE);
	if (!content)
		new->content = NULL;
	else if (content_size)
	{
		if (!(mem = malloc(content_size)))
			exit (EXIT_FAILURE);
		ft_memcpy(mem, content, content_size);
		new->content = mem;
	}
	else
		exit (EXIT_FAILURE);
	return (new);
}

/*t_btree	*ft_btree_addone(void *content, t_btree *root, uint32_t content_size
						 , int32_t (*f)(t_btree *, t_btree *))
{
	t_btree	*new;

	new = ft_btreenew(content, content_size);
	if (f(
	}*/
