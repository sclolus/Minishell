#include "minishell.h"

t_list		*ft_completion_add_directory_bin(char *path)
{
	DIR				*curr_dir;
	struct dirent	*curr_entry;
	char			*tmp;
	char			*tmp_curr_name;
	t_list			*lst;
	t_list			*list_dir;

	list_dir = NULL;
	path = ft_get_path_name(path);
	if (!(curr_dir = opendir(path)))
		ft_error_exit(1, (char*[]){"Failed to open completion directory"}, 4);
	while ((curr_entry = readdir(curr_dir)))
	{
		if (!(tmp = ft_strjoin(path, curr_entry->d_name)))
			exit(EXIT_FAILURE);
		if (ft_check_exec_perm(tmp) && ft_strcmp("..", curr_entry->d_name)
			&& ft_strcmp(".", curr_entry->d_name))
			ft_fuk_norminette(&tmp_curr_name, curr_entry);
		if (!(tmp_curr_name = ft_strjoin_f(path, tmp_curr_name, 1)))
			exit(EXIT_FAILURE);
		if (!(lst = ft_lstnew(0, 0)))
			exit(EXIT_FAILURE);
		lst->content = tmp_curr_name;
		ft_lstadd(&list_dir, lst);
		free(tmp);
	}
	if (closedir(curr_dir) == -1)
		ft_error_exit(1, (char*[]){"Failed to close completion directory"}, 4);
	return (list_dir);
}
