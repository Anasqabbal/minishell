/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anqabbal <anqabbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 16:31:44 by zgtaib            #+#    #+#             */
/*   Updated: 2024/07/12 14:45:08 by anqabbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "./libft/libft.h"
# include <stdio.h>
# include <libc.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
#include "errno.h"


typedef struct s_prs{
	char	*cmd;
	char	**opts;
	char	**arg;
	char	**red;
	int		ex_code;
	struct s_prs *next;
}	t_prs;

typedef	struct s_exec{
	int		i;
	int		**in;
	int		in_f;
	int		in_l;
	int		**out;
	int		out_l;
	char	**cmd;
	char	*path;
	char	**env;
	char	**here_doc;
	int		in_h_l;
	int		size;
	int		ex;
	// char	*PATH;
	struct	s_exec *n;
}	t_exec;

typedef struct s_par{
	char *first;
	char *mid;
	char *last;
	int len;
}	t_par;

typedef struct s_all{
	t_exec	**e;
	t_prs	**n;
	t_list	*envp;
	char	*path;
	int		*ret;
	char	*input;
}	t_all;


/*EXECUTION*/

	/*BUILTINS*/
int		ft_export(char **opts, t_list **envp);
int		ft_env(t_list *node);
int		ft_unset(char **str, t_list **env, char **path);
unsigned char 		ft_exit(t_exec *e, t_list **envp, t_prs **l);
int					ft_echo(t_exec *e, t_list *envp);
int					ft_pwd(t_list *env, char **str);
int		ft_cd(char **str , t_list **env, char *path);
int check_dir_access(char **str);
int join_and_export(char *str, char *new, t_list **env, char *c);
int		ft_check_dir(char  *str);

void	*add_to_env(char *str, t_list **envp);
void	*export1(char *str, t_list **env);
t_list	*ft_getenv(char *str, t_list *env);

/*check_variavles*/
void	var_error(char *from, char *str, int indice);
int		valid_name(char *from, char *str, t_par *par);

/*sort_with_ascii*/
int	ft_sort_ascii(t_list *n);
	
	/*additional_ft.c*/
char	**to_free(char **s);
int		calcul_args(char **args);
char	**ft_2dstrdup(char **s);
char	**ft_2dstrcpy(char **dst, char **src, int f_len);
char	**ft_2dstrjoin(char **s1, char **s2);

	/*additional_ft2.c*/
int		ft_2dprint(char **str); // remove_it;
int		ft_prssize(t_prs *lst);

	/*env_utils*/
t_list	*ft_envdup(char **env, char **path); /*duplicate your environment variable*/
t_list	*ft_getenv_ours(char *str, t_list *env);
int		from_lst_to_2d(t_list *s, char ***env);
char	*nw_vl(t_list *env, int ii);
t_list	*ft_getenv_ours_special(char *str, t_list *env);

	/*ft_1open_in_files.c "5"*/
int		**to_free_f(int **file, int len);
int		open_in_files(t_exec *e, int len, char *file, char *token);
int		ft_open_files(t_prs *lst, t_exec *e);
int		set_and_open(t_exec *e, char **f, int i);

	/*ft_1open_out_files.c "3"*/
int		ft_restore_input(void);
int		ft_restore_output(int out, int save);
int		creat_open_file(char *f1, int ind, int VAL);
int		open_out_files(t_exec *e, int len, char *file, char *token);

	/*ft_additional_lst.c "2"*/
void	*ft_lstremplace(t_list **lst, t_list *s1, t_list *s2);
int		ft_lstget_pos(char *str, t_list *lst);

	/* prepare cmds and args  "5"*/ 
char	**join_cmd_and_args(char *cmd, char **opts, int len);
char	**prepare_cmd(char *cmd, char **opts, char **args);

	/* prepare_path.c "3"*/
int		check_access(char *cmd, t_exec *p, t_list *env, char *path);

	/*start_exec_00.c "4"*/
int		ft_execve1(t_exec *e, int in, int out);
int		ft_is_pipe(int fd);
int		start_exec(t_prs **lst, t_list **envp, int rett, char **path);

	/*start_exec_01_cmds.c "3" */
int		the_input(t_prs *lst, t_exec *e);
int		one_cmd(t_prs **lst, t_list **envp, t_exec *e, char **paht);
int		mult_cmds(t_prs *lst, t_list **envp, t_exec *e, char **path);

	/*start_exec_02_blts "1" */
int		it_is_builtin(char *cmd);
int		ft_execve2(t_exec *e, int in, int out, t_list **envp);
int		ft_execve3(int in, int out);
int		execvecmd(t_exec *e, t_list **envp, char **path, t_prs **l);

	/*exec_functions*/
t_exec	*ft_exec_new(void);
void    ft_execadd_back(t_exec **h, t_exec *n);
void	ft_print_exec(t_exec *e);

int 	set_here_doc(t_prs *l, t_exec **e, int i);

/*FT_ERRORS.C*/
int		ft_error_p(char *from, int indice);
int		ft_error_files(int indice, int ret, char *n);
int 	ft_error(char *from, int indice);

/*PARSING*/
// t_list	*ft_envdup(char **env, char *path);
t_list	*ft_getenvza(char *str, t_list *env);
int		check_syntax(char *input, t_list *env, t_prs **node, int *ret);
int 	ft_syntax_h1(char *str, int *x);
int 	ft_syntax_h2(char *str, int x);
char	*replacewihte_s(char *str);
int		check_qts(char *input, int *count, int *qts);
t_prs	*pipe_split(char *cmd, int opp, int qts, t_list *env);
int		ft_check_quotes(char c, int *sign);
int		arg_count(char **str);
void	turn_back(char *str, int ndx);
void	free_it(char **arg, int count);
void	turn_single(char *str, int ndx);
char	*cmd_expa(char *str, t_list *env);
void	ft_strcpy(char *s1, char *s2);
t_prs	*init_prs(void);
void	pipe_split_h(char **splt_pip, t_prs **curr, t_prs **head, char *com);
void	parse_red(char **array, t_prs *node);
void	free_it_h(char **splt_pip, char *com, int ndx);
char	*dollar_sign(char *str);


void	ft_clear_exec(t_exec **e);
void	clear_prs(t_prs **c);


/*to remove*/
void	print_lst(t_list *e);
#endif