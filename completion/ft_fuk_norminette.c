#include "ft_completion.h"
#include "minishell.h"

void	ft_fuk_norminette(char *tmp, t_ltree **ltree, struct dirent *curr_entry)
{
	char    *tmp_curr_name;

	if (ft_is_dir(tmp))
	{
		if (!(tmp_curr_name = ft_strjoin(curr_entry->d_name, "/")))
			exit(EXIT_FAILURE);
		ft_sanitize_completion(&tmp_curr_name);
		ft_ltree_add_word(ltree, tmp_curr_name);
	}
	else
	{
		if (!(tmp_curr_name = ft_strdup(curr_entry->d_name)))
			exit(EXIT_FAILURE);
		ft_sanitize_completion(&tmp_curr_name);
		ft_ltree_add_word(ltree, tmp_curr_name);
	}
	free(tmp_curr_name);
}
