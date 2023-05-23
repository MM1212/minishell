#include "parsing.h"

t_lexer	*build_lexer(char *str)
{
	t_lexer_builder	b;

	lexer_constructor(&b, str);
	while (str[++b.i])
	{
		while (str[b.i] == ' ' || str[b.i] == 3)
			str[b.i++] = 3;
		b.node = (t_lexer *)malloc(sizeof(t_lexer));
		if (!b.node)
			return (0); // ERROR
		handle_tokens(&b, str);
		if (!b.start->next && b.start->token == 1)
		{
			(parser_error_printer(b.start, b.start, "|", 0)); // ERROR
			return (0);
		}
		if (!str[b.i])
			break ;
	}
	return (b.start);
}

void	create_lexer_node(t_lexer_builder *b, char *str, int token)
{
	if (token == 0)
	{
		b->j = b->i;
		while (b->str[b->j] && b->str[b->j] != ' ')
			b->j++;
		b->node->str = ft_substr(b->str, b->i, b->j - b->i);
	}
	else
		b->node->str = ft_strdup(str);
	b->node->token = token;
	b->node->next = NULL;
	if (!b->start)
		b->start = b->node;
	else
	{
		lexer_lstlast(b->start)->next = b->node;
		b->node->prev = lexer_lstlast(b->start);
	}
	if (token == PIPE)
		b->str[b->i] = 2;
	else if (token == LESS_LESS || token == GREAT_GREAT)
		b->i++;
	else if (token == 0)
		b->i += b->j - b->i - 1;
}

void	handle_double_quotes(t_lexer_builder *b)
{
	b->j = b->i + 1;
	while (b->str[b->j] && b->str[b->j] != '\"')
		b->j++;
	if (b->j - b->i > 1 && b->str[b->j] == '\"')
	{
		b->node->str = ft_substr(b->str, b->i + 1, b->j - b->i - 1);
		if (b->node->str[0])
			b->node->str = ft_strjoin("\"", b->node->str);
		b->node->token = 0;
		b->node->next = NULL;
		b->i += b->j - b->i;
		if (!b->start)
			b->start = b->node;
		else
		{
			lexer_lstlast(b->start)->next = b->node;
			b->node->prev = lexer_lstlast(b->start);
		}
		b->node->i = b->index;
		b->index++;
	}
}

void	handle_quotes(t_lexer_builder *b)
{
	b->j = b->i + 1;
	while (b->str[b->j] && b->str[b->j] != '\'')
		b->j++;
	if (b->j - b->i > 1 && b->str[b->j] == '\'')
	{
		b->node->str = ft_substr(b->str, b->i + 1, b->j - b->i - 1);
		if (b->node->str[0])
			b->node->str = ft_strjoin("'", b->node->str);
		b->node->token = 0;
		b->node->next = NULL;
		b->i += b->j - b->i;
		if (!b->start)
			b->start = b->node;
		else
		{
			lexer_lstlast(b->start)->next = b->node;
			b->node->prev = lexer_lstlast(b->start);
		}
		b->node->i = b->index;
		b->index++;
	}
}

void	handle_tokens(t_lexer_builder *b, char *str)
{
	if (str[b->i] == '\'')
		handle_quotes(b);
	else if (str[b->i] == '\"')
		handle_double_quotes(b);
	else if (str[b->i] == '|')
		create_lexer_node(b, "|", PIPE);
	else if (str[b->i] == '<' && str[b->i + 1] == '<' && str[b->i + 2] == ' ')
		create_lexer_node(b, "<<", LESS_LESS);
	else if (str[b->i] == '>' && str[b->i + 1] == '>' && (str[b->i + 2] == ' ' \
		|| !str[b->i + 2]))
		create_lexer_node(b, ">>", GREAT_GREAT);
	else if (str[b->i] == '<' && str[b->i + 1] == ' ')
		create_lexer_node(b, "<", LESS);
	else if (str[b->i] == '>' && str[b->i + 1] == ' ')
		create_lexer_node(b, ">", GREAT);
	else
		create_lexer_node(b, 0, 0);
}
