/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anqabbal <anqabbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 16:31:44 by zgtaib            #+#    #+#             */
/*   Updated: 2024/07/23 15:08:34 by anqabbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "./libft/libft.h"
# include <stdio.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <signal.h>
/*to remove */
# ifndef PATH_MAX
#  define PATH_MAX 1024
# endif

typedef struct s_prs
{
	char			*cmd;
	char			**opts;
	char			**arg;
	char			**red;
	int				ex_code;
	struct s_prs	*next;
}	t_prs;

typedef struct s_exec
{
	int				i;
	int				**in;
	int				in_f;
	int				in_l;
	int				**out;
	int				out_l;
	char			**cmd;
	char			*path;
	char			**env;
	char			**here_doc;
	int				in_h_l;
	int				size;
	int				ex;
	struct s_exec	*n;
}	t_exec;

typedef struct s_par
{
	char	*first;
	char	*mid;
	char	*last;
	int		len;
}	t_par;

typedef struct s_all
{
	struct s_exec	*e;
	struct s_prs	*p;
	struct s_list	**envp;
	char			*path;
	int				ret;
	int				out;
	int				i;
	int				indice;
	int				fd[2];
}	t_all;

typedef struct s_sing
{
	int				ret;
	int				out;
	int				in;
	int				save;
	struct s_prs	*lst;
	struct s_list	**envp;
	struct s_exec	*e;
}	t_sing;

typedef struct s_ndx{
	int x;
	int y;
}t_ndx;
/*EXECUTION*/
	/* ----- BUILTINS ----- */
int				ft_export(char **opts, t_list **envp);
t_list			*ex_getenv_ours(char *str, t_list *env);
char			*remove_plus(char *str, char *res);
int				ft_env(char **opts, t_list *node);
int				ft_unset(char **str, t_list **env, char **path);
int				unset1(char *str, t_list **envp, char **path, t_list **new);
unsigned char	ft_exit(t_exec *e, t_list **envp, t_prs **l);
int				ft_echo(t_exec *e, t_list *envp);
int				ft_pwd(t_list *env, char **str);
int				it_is_with_options(char **opts, int ind1, char *cmd);
int				ft_cd(char **str, t_list **env, char *path);
int				to_old_one(t_list **env, char *lastdir);
int				to_home(t_list *env);
int				check_dir_access(char **str);
int				join_and_export(char *str, char *new, t_list **env, char *c);
int				ft_check_dir(char	*str);
void			*add_to_env(char *str, t_list **envp);
void			*export1(char *str, t_list **env);
t_list			*ft_getenv(char *str, t_list *env);
/*check_variavles*/
void			var_error(char *from, char *str, int indice);
int				valid_name(char *from, char *str, t_par *par);
int				valide_par(char *from, char *str);
void			ft_print_export(t_list *envp, int indice);

/*sort_with_ascii*/
int				ft_sort_ascii(t_list *n1);
int				ft_envdup_exept(t_list	*envp, char	*str, t_list	**new);
	/*additional_ft.c*/
char			**to_free(char **s);
int				calcul_args(char **args);
char			**ft_2dstrdup(char **s);
char			**ft_2dstrcpy(char **dst, char **src, int f_len);
char			**ft_2dstrjoin(char **s1, char **s2);
	/*additional_ft2.c*/
int				ft_2dprint(char **str); // remove_it;
int				ft_prssize(t_prs *lst);
	/*env_utils*/
t_list			*ft_envdup(char **env, char **path);
t_list			*ft_getenv_ours(char *str, t_list *env);
int				from_lst_to_2d(t_list **s, char ***env);
char			*nw_vl(t_list *env, int ii, char	*s, char *s1);
t_list			*ft_getenv_ours_special(char *str, t_list *env);
	/*ft_1open_in_files.c "5"*/
int				**to_free_f(int **file, int len);
int				open_in_files(t_exec *e, int len, char *file, char *token);
int				ft_open_files(t_prs *lst, t_exec *e);
int				set_and_open(t_exec *e, char **f, int i);
int				check_file_access(char *file, int indice);
char			*read_from_here_doc(char **red, int i, t_list **env, int *ret);

	/*ft_1open_out_files.c "3"*/
int				ft_restore_input(void);
int				ft_restore_output(int out, int save);
int				creat_open_file(char *f1, int ind, int VAL);
int				open_out_files(t_exec *e, int len, char *file, char *token);
	/*ft_additional_lst.c "2"*/
void			*ft_lstremplace(t_list **lst, t_list *s1, t_list *s2);
int				ft_lstget_pos(char *str, t_list *lst);
	/* prepare cmds and args  "5"*/
char			**join_cmd_and_args(char *cmd, char **opts, int len);
char			**prepare_cmd(char *cmd, char **opts, char **args);
	/* prepare_path.c "3"*/
int				check_access(char *cmd, t_exec *p, t_list **env, char *path);
	/*start_exec_00.c "4"*/
int				ft_execve1(t_exec *e, int in, int out);
int				ft_is_pipe(int fd);
int				start_exec(t_prs **lst, t_list **envp, int rett, char **path);
	/* start_exec_mult_cmds.c */
int				the_input(t_prs *lst, t_exec *e);
int				mult_cmds(t_prs *lst, t_list **envp, t_exec *e, char **path);
	/* start_exec_mult_cmdss_utils.c */
int				the_input(t_prs *lst, t_exec *e);
int				set_stdin(t_prs *lst, t_exec *e, int indice, int *fd);
void			set_stdout_and_cmd(t_prs *l, t_exec *e, int *o, int *fd);
int				ft_return(int *ret, int *i);
int				open_files_and_pipe(t_all *a);
	/* start_exec_sing_cmd.c */
int				one_cmd(t_prs **lst, t_list **envp, t_exec *e, char **paht);
int				ft_export_(t_list **env, char **str, t_exec *e);
	/*start_exec_02_blts "1" */
int				it_is_builtin(char *cmd);
int				ft_execve2(t_exec *e, int in, int out, t_list **envp);
int				ft_execve3(int in, int out);
int				execvecmd(t_exec *e, t_list **envp, char **path, t_prs **l);
	/*exec_functions*/
t_exec			*ft_exec_new(void);
void			ft_execadd_back(t_exec	**h, t_exec	*n);
void			ft_print_exec(t_exec *e);
int				set_here_doc(t_prs *l, t_exec **e, t_list **env, int *ret);
/*FT_ERRORS.C*/
int				ft_error_p(char *from, int indice);
int				ft_error_files(int indice, int ret, char *n);
int				ft_error(char *from, int indice);
/*PARSING*/

t_list	*ft_envduppp(char **env);
void	ft_getenv_oursss(char *str, t_list *env, char *path);
int		check_syntax(char *input, t_list *env, t_prs **node, int *ret);
int 	ft_syntax_h2(char *str, int x);
void	replacewihte_s(char *str);
int		check_qts(char *input, int *count, int *qts);
t_prs	*pipe_split(char *cmd, int opp, t_list *env, int *ret);
int		ft_check_quotes(char c, int *sign);
int		arg_count(char **str);
void	turn_back(char *str, int ndx);
void	free_it(char **arg, int count);
void	turn_single(char *str, int ndx);
char	*cmd_expa(char *str, t_list *env, int *ret);
void	ft_strcpy(char *s1, char *s2);
t_prs	*init_prs(void);
void	pipe_split_h(char **splt_pip, t_prs **curr, t_prs **head, char *com);
void	parse_red(char **array, t_prs *node);
void	free_it_h(char **splt_pip, char *com, t_prs **head);
char	*dollar_sign(char *str);
void	ft_handler(int sig);
void	free_list(t_prs *head);
void 	back_turning(char **array);
void	free_node(t_prs *node);
void	free_it_h2(char **splt_pip, char *com, t_prs **head, t_prs *new);
int		error_msg1(char *str, int x);
void	error_msg(char c);
void 	turn_double(char *str, int ndx);
char	*skip_unnecessary_quotes(char *str);
int		error_msg1h3(char *str, int x);
int		turn_dollar(char *str, int y);
char	*expand_variable(char *str, t_list *env, int *ndx);
char	*extract_virable(char *str, int *var_len);
void 	turn_back_dollar(char *str);
char	*blurr_dollar(char *str);
char	*dollar_sign(char *str);
int		calaculate_expan_len(char *str, t_list *env);
void	the_turns(char *str, int ndx);
void	turn_here_do(char *str);
char	*cmd_expa_h(char *str);


/* clear_functions.c */
void			ft_clear_exec(t_exec **e);
void			clear_prs(t_prs **c);
/*to remove*/
void			print_lst(t_list *e);
void			print_prs(t_prs *p);
t_prs			*set_values(int indice);
t_prs			*new_prs(char *cmd, char **opts, char **args);
void			ft_print_prs(t_prs *c);
void			ft_print_exec(t_exec *e);

#endif