/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elanson <elanson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 16:03:26 by elanson           #+#    #+#             */
/*   Updated: 2024/05/08 14:48:18 by elanson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/wait.h>
# include <signal.h>
# include <limits.h>
# include <errno.h>
# include "../libft/libft.h"
# include <sys/types.h>
# include <dirent.h>
# include <fcntl.h>
# include <stdbool.h>
# include <sys/stat.h>

/*Color Definition*/
# define RED     "\x1b[31;1m"
# define GREEN   "\x1b[32m"
# define YELLOW  "\x1b[33m"
# define BLUE    "\x1b[34m"
# define MAGENTA "\x1b[35m"
# define CYAN    "\x1b[36m"
# define RESET   "\x1b[0m"

/**MESSAGE DEFINITION**/
# define ARGS_ERR_MSG "Error : Invalid number of arguments.\n"
# define UNAVAILABLE_ENV "Minishell: Environment unavailable.\n"
# define MALLOC_ERR_MSG "Minishell: Allocation error\n"
# define QUOTES_ERR_MSG "Minishell: open quotes are not interpreted.\n"
# define INFILE_ERR_MSG "Minishell: open quotes are not interpreted.\n"
# define PARENTHESIS_ERR_MSG "Minishell: \
parenthesis are not interpreted.\n"
# define OPEN_PIPE_ERR_MSG "Minishell: open pipe are not interpreted.\n"
# define WRONG_CHAR_ERR_MSG "Minishell: uninterpreted token \
present outside quotes.\n"
# define NEAR_TOKEN_ERR_MSG "Minishell: syntax error near unexpected token"
# define STAR_TOKEN_ERR_MSG "Minishell: *: ambiguous redirect\n"
# define UNEXPECTED_EOF "Minishell: syntax error: unexpected end of file.\n"
# define EOF_HEREDOC "Minishell:\
 warning: here-document at line 1 delimited by end-of-file"
# define PWD_ERR_MSG "pwd: error retrieving current directory: getcwd: \
cannot access parent directories: No such file or directory"
# define SHLVL_ERR_MSG "minishell: warning: shell level (%d) too high, \
resetting to 1"
# define HEREDOC_MSG "%sMinishell: warning: here-document \
at line %d delimited by end-of-file (wanted `%s')%s\n"
# define DOT_MSG_ERR ": filename argument required\n.: \
usage: . filename [arguments]\n"

extern int	g_status;

typedef enum e_id_gc
{
	TKN_LIST,
	ENV,
	TMP,
	CMDS_LIST
}			t_id_gc;

typedef enum e_tkntype
{
	WORD,
	IN,
	OUT,
	HEREDOC,
	APPEND,
	PIPE,
	QUOTE,
	DOUBLE_QUOTE
}			t_tkntype;

typedef enum e_error
{
	NOTHING = -1,
	MALLOC_E,
	FILE_E,
	TYPE_E
}	t_error;

typedef struct s_io
{
	int	fd_in;
	int	fd_out;
}				t_io;

typedef struct s_token
{
	t_tkntype		type;
	char			*content;
	bool			linked;
	size_t			index;
	bool			quotes;
	struct s_token	*next;
	struct s_token	*previous;
}				t_token;

typedef struct s_redir
{
	t_tkntype			type;
	char				*filename;
	int					fd;
	int					pipe_fd[2];
	bool				is_open;
	struct s_redir		*next;
}				t_redir;

typedef struct s_redirlst
{
	struct s_redir	*head;	
	struct s_redir	*tail;
}				t_redirlst;

typedef struct s_cmds
{
	char			**cmds;
	int				io[2];
	t_redirlst		*redir;
	int				pipe_fd[2];
	bool			is_open;
	bool			is_pipe;
	bool			quotes;
	struct s_cmds	*next;
}				t_cmds;

typedef struct s_tknlist
{
	struct s_token	*head;
	struct s_token	*tail;
}				t_tknlist;

typedef struct s_cmds_list
{
	struct s_cmds	*head;
	struct s_cmds	*tail;
}				t_cmds_list;

typedef struct s_env
{
	char			*value;
	bool			secret;
	struct s_env	*next;
}				t_env;

typedef struct s_mini
{
	t_env			*env;
	t_tknlist		*tknlist;
	t_io			io_global;
	t_cmds_list		*cmd_list;
	int				last_gstatus;
}			t_mini;

/*****error*****/
int			error_handler_lexer(int id_gc, char *msg);
void		free_and_exit(int exit_code);
void		print_and_exit(char *msg, char *color, int exit_status);
void		print_without_exit(char *msg, char *color, int exit_status);

/*****lexer*****/

char		*ft_strndup(char *buffer, int len, t_id_gc id);
int			detect_error_type(const char c);
t_tknlist	*lexer(char *buffer);
int			double_quote_handler(char *buffer, t_tknlist *list);
int			is_special_char(char c);
int			simple_quote_handler(char *buffer, t_tknlist *list);
int			pipe_handler(char *buffer, t_tknlist *list);
int			file_handler(char *buffer, t_tknlist *list, t_tkntype type);
int			cmd_handler(char *buffer, t_tknlist *list);

/*****utils*****/
void		init_list(t_tknlist **list);
t_token		*create_node(t_tkntype typed, char *value, int linked);
int			add_node(t_tknlist *list, t_token *node);
int			is_cmd_tkn(t_tkntype tkntype);
int			is_redir_tkn(t_tkntype tkntype);
int			is_pipe_tkn(t_tkntype tkntype);
void		pop_token_in_place(t_tknlist *list_tkn, t_token *to_pop);
void		add_tknlst_in_tknlst_after_target(t_tknlist *lst1 \
				, t_token *tkn_flag, t_tknlist *lst2);
void		swap_tokens(t_tknlist	*lst, t_token *tkn1, t_token *tkn2);
size_t		tknlst_size(t_tknlist *tknlst);
void		init_list_cmds(t_cmds_list **list);
t_cmds_list	*create_cmd_list(t_tknlist *tkn_lst);
void		init_all_redirs_lst(t_tknlist *tkn_lst, t_cmds_list *cmds);
void		init_pipes(t_cmds_list **lst);
bool		cmd_is_inside_pipe(t_mini *mini);
void		print_path_error(char *arg, int exit_status, int error);
char		*get_cmd_path(char *cmd, t_env *env);
void		check_path(char *command, char *path);
int			get_fork_number(t_cmds *cmd);
size_t		get_cmd_lst_length(t_cmds *cmd);
bool		is_in_quotes_heredoc(t_token *tkn);
t_redirlst	*create_redir_list(void);
void		init_node_redir(t_redir *node, t_redirlst *list);
void		add_node_redirs(t_token *tkn, t_redirlst *redir_lst);
void		init_all_redirs_lst(t_tknlist *tkn_lst, t_cmds_list *cmd_lst);
void		init_redir_list(t_cmds *cmds, t_token *tkn);
void		handle_redir(t_token *tkn, t_cmds *cmds, int *flag);
void		check_alphanum_loop(char *str, char *var, int i, int j);

/*****env*****/
void		env_add_back(t_env **env, t_env *new);
void		*get_env_name_var(char *dest, char *src);
t_env		*init_env(char **env_array);
size_t		strlen_env(t_env *env);
char		*get_env_value(t_env *env, const char *var, size_t len);
char		*env_to_str(t_env *lst);
int			is_in_env(t_env *env, char *args);
void		print_sorted_env(t_env *env, t_cmds *cmd);
int			env_add(char *value, t_env **env, int mod);

/*****libft_extension*****/

char		*strcut_gc(char const *str, size_t cut_begin,	
				size_t cut_end, int id_gc);
char		*ft_strcut(char const *str, size_t cut_begin, size_t cut_end);
char		*replace_substr(char *str, char *replacement,	
				size_t start, size_t len);
char		*remove_substr(char *str, size_t start, size_t len_toremove);
size_t		ft_strlen_until(const char *str, int (*f)(char));
size_t		ft_strlen_until_char(const char *str, char c);
size_t		ft_strlen_until_not(const char *str, int (*f)(char));
size_t		ft_strlen_until_not_char(const char *str, char c);
int			str_contains_all_subs_ordered(char *str, char **subs);
int			char_is_in_str(char c, char *str);
int			ft_strcmp_case_insensitive(char *s1, char *s2);
int			s1_is_s2_suffix(char *s1, char *s2);
bool		s1_is_s2_prefix(char *s1, char *s2);

/*****terminal*****/

char		*create_prompt(t_mini *mini);
void		clear_loop(void);
void		prompt_loop(t_mini *mini);

/*****parser*****/

void		reducer(t_mini	*mini);
void		linker(t_tknlist *tkn_lst);
void		expander(t_mini *mini, t_tknlist *tkn_lst);
t_token		*expand_dollar(t_mini *mini, t_token *tkn_toexpand,	
				t_tknlist *tkn_lst);
t_tknlist	*parser(t_mini *mini);
void		verify_syntax_tknlist(t_tknlist *lst);
t_mini		*singleton_mini(t_mini *address_mini);

/*****exec*****/

int			browse_list(t_mini *mini);
int			exec_handler(t_cmds *cmd, t_mini *mini);
int			exec_builtin( t_env **env, t_cmds *cmd);
int			exec_bin(t_env *env, t_cmds *cmd);
int			fork_builtin(t_env **env, t_cmds *cmd);
int			is_builtin(char *command);
void		open_pipe(t_cmds *cmd);
void		exec_process(t_cmds *cmd, t_env *env);
void		close_pipe(t_cmds *cmd);
void		handle_sigterm(int sig);
void		handle_child_process(t_cmds *cmd, t_mini *mini);
void		close_unused_pipes(t_cmds *cmd);
int			*fork_processes(t_cmds *cmd, int size, t_mini *mini);
int			pre_exec(t_cmds *cmd, int size, t_mini *mini);
int			waitlist(int *pid, int size);
void		redir_handler(t_redir *redir, t_cmds *cmds, t_mini *mini);
int			browse_list(t_mini *mini);
char		*copy_until_dollar(char *str, char *result, int *i);
void		append_suffix(char *str, char *result, int *i);
char		*replace_extend_var(char *str, char *var);
char		*expand_heredoc(char *str, t_mini *mini);
void		set_open_pipe(int fd_pipe[2]);
void		handle_heredoc_line(char **line, size_t *nb_lines,
				t_cmds *cmds, t_mini *mini);
void		process_heredoc_lines(t_cmds *cmds, t_redir *redir,
				t_mini *mini, int fd_pipe[2]);
int			exec_heredoc(t_cmds *cmds, t_redir *redir, t_mini *mini, int *fd_p);
void		handle_signals_heredoc(char *input, size_t	nb_lines, char *delim);
int			readline_heredoc(char *delim, char *line,
				size_t *nb_lines, int fd_pipe[2]);
char		*get_env_value2(t_env *env, const char *var, size_t len);
char		*extract_variable(char *str, int *i, int *j);
void		end_here(char *line, size_t nb_lines, t_redir *redir, int *fdp);
void		start_heredoc(int *fd_pipe, char **line, size_t *nb_lines);
void		start_heredoc2(char **line, t_cmds *cmds, t_mini *mini,
				size_t nb_lines);

/*****builtins*****/

int			cd(char **cmds, t_env **env);
int			echo(char **cmds, t_cmds *cmd);
int			env(t_env *env, t_cmds *cmd);
int			builtin_exit(t_mini *mini, char **cmds);
int			ft_export(char **args, t_env **envt, t_cmds *cmd);
int			ft_pwd(t_cmds *cmd, t_env *env);
int			unset(char **value, t_env **env);

#endif