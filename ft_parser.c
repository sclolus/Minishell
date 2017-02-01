#include "minishell.h"

char		*ft_variable_expansion(char *token, char **env)
{
	uint32_t	i;
	uint32_t	u;
	char		*tmp;
	char		*cpy;

	i = 0;
	u = 0;
	while (token[i])
	{
		if (token[i] == '$' && token[i + 1] != '(')
		{
			u = i;
			while (token[i] && (!ft_strchr(CHARSET_SPECIAL_DELIMITORS, token[i]) || !ft_strchr(" \t\n", token[i])))
				i++;
			if (!(tmp = ft_strsub(token, u + 1, i)))
				exit(EXIT_FAILURE);
			cpy = ft_find_env((char const**)env, (char const*)tmp);
			free(tmp);
			while (*cpy && *cpy != '=')
				cpy++;
			tmp = token;
			if (!(token = ft_strreplace(token, u, i, cpy + 1)))
				exit(EXIT_FAILURE);
			free(tmp);
			i = 0;
		}
		i++;
	}
	return (token);
}

char		**ft_preparse(char **tokens, char **env)
{
	uint32_t	i;

	i = 0;
	while (tokens[i])
	{
		tokens[i] = ft_variable_expansion(tokens[i], env);
		// put command expansion in it
		i++;
	}
	return (tokens);
}

uint32_t	ft_count_abstract_tokens(char **tokens)
{
	uint32_t	i;
	uint32_t	count;

	i = 0;
	count = 0;
	while (tokens[i])
	{
		if (ft_strcmp(tokens[i], "(") && ft_strcmp(tokens[i], ")"))
			count++;
		i++;
	}
	return (count);
}

int32_t		ft_get_token_id(char *token)
{
	static const t_token	tab[TOKEN_COUNT] = {
		{ TYPE_TOKEN_OR, {TOKEN_OR}},
		{ TYPE_TOKEN_AND, {TOKEN_AND}},
		{ TYPE_TOKEN_SINGLE_AND, {TOKEN_SINGLE_AND}},
		{ TYPE_TOKEN_END_OF_STATEMENT, {TOKEN_END_OF_STATEMENT}},
		{ TYPE_TOKEN_LEFT_REDIRECTION, {TOKEN_LEFT_REDIRECTION}},
		{ TYPE_TOKEN_RIGHT_REDIRECTION, {TOKEN_RIGHT_REDIRECTION}},
		{ TYPE_TOKEN_HEREDOC, {TOKEN_HEREDOC}},
		{ TYPE_TOKEN_RIGHT_APPEND, {TOKEN_RIGHT_APPEND}}
	};
	uint32_t	i;

	i = 0;
	while (i < TOKEN_COUNT)
	{
		if (!ft_strcmp(token, tab[i].token.token))
			return (tab[i].type);
		i++;
	}
	return (TYPE_TOKEN_STATEMENT);
}

t_token		*ft_get_tokens_tab(char **tokens, uint32_t count)
{
	t_token		*tab;
	uint32_t	i;
	uint32_t	u;

	i = 0;
	u = 0;
	if (!(tab = (t_token*)malloc(sizeof(t_token) * count + 1)))
		exit(EXIT_FAILURE);
	while (i < count)
	{
		if (ft_strcmp(tokens[i], "(") && ft_strcmp(tokens[i], ")"))
		{
			tab[u].type = ft_get_token_id(tokens[i]);
			tab[u].token.token = tokens[u];
			u++;
		}
		i++;
	}
	return (tab);
}

t_token		*ft_sanitize_tokens(t_token *tokens_tab, uint32_t count)
{
	uint32_t	i;
	uint32_t	u;
	uint32_t	argv_nbr;
	uint32_t	token_nbr;
	char		**tmp;

	i = 0;
	u = 0;
	while (i < count)
	{
		if (tokens_tab[i].type == TYPE_TOKEN_STATEMENT)
		{
			argv_nbr = 0;
			u = i;
			while (tokens_tab[u].type == TYPE_TOKEN_STATEMENT)
				u++;
			if (!(tmp = (char**)malloc(sizeof(char*) * u - i + 2)))
				exit (EXIT_FAILURE);
			tmp[u - i + 1] = 0;
			token_nbr = i;
			while (token_nbr < u)
			{
				tmp[argv_nbr++] = tokens_tab[token_nbr].token.token;
				token_nbr++;
			}
			tokens_tab[i].token.tokens = tmp;
			i = token_nbr;
		}
		else
			i++;
	}
	return (tokens_tab);
}

t_btree		*ft_parser(char **tokens, char **env)
{
	uint32_t	count;
	uint32_t	i;
	t_token		*tokens_tab;

	if (env)
	{};
	count = ft_count_abstract_tokens(tokens);
	if (!(tokens_tab = ft_get_tokens_tab(tokens, count)))
		exit (EXIT_FAILURE);
	ft_sanitize_tokens(tokens_tab, count);
	uint32_t	u;

	i = 0;

	while (i < count)
	{
		u = 0;

		if (tokens_tab[i].type != TYPE_TOKEN_STATEMENT)
		{
			ft_putstr(tokens_tab[i].token.token);
			ft_putchar(' ');
		}
		else
		{
			while (tokens_tab[i].token.tokens[u])
			{
				ft_putstr(tokens_tab[i].token.tokens[u]);
				ft_putchar(' ');
				u++;
			}
			while (tokens_tab[i].type == TYPE_TOKEN_STATEMENT)
				i++;
			continue ;
		}
		i++;
	}
	if (!(tree = ft_get_btree(tokens_tab, count)))
		exit (EXIT_FAILURE);
	return (NULL);
}
