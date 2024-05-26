/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anqabbal <anqabbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 16:31:44 by zgtaib            #+#    #+#             */
/*   Updated: 2024/05/25 12:51:31 by anqabbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "./libft/libft.h"
# include <stdio.h>
# include <libc.h>
# include <readline/history.h>
# include <readline/readline.h>


typedef struct s_prs{
	char	*cmd;
	char	**opts;
	char	**arg;
	char	**out;
	char	**in;
	char	**out_f;
	char	**in_f;
	int		ex_code;
	struct s_prs *next;
}t_prs;

typedef	struct s_exec{
	int		**in;
	int		in_l;
	int		**out;
	int		out_l;
	char	**cmd;
	char	*path;
	char	**env;
	char	*here_doc;
	int		size;
}t_exec;

typedef struct s_par{
	char *first;
	char *mid;
	char *last;
	int len;
}t_par;

/*errors*/
int 	ft_error(char *from, int indice);

/*ft_additional_lst.c*/
void	*ft_lstremplace(t_list **lst, t_list *s1, t_list *s2);
int		ft_lstget_pos(char *str, t_list *lst);

/*additional_ft.c*/
char	**ft_2dstrdup(char **s);
char	**ft_2dstrcpy(char **dst, char **src, int f_len);
char	**ft_2dstrjoin(char **s1, char **s2);
char	**from_lst_to_2d(t_list *s);
char	**to_free(char **s);


/*env_utils*/
void	*ft_getenv_org(char *str, char **env); /*this functions to get some specific variable in your env*/
t_list	*ft_envdup(char **env); /*duplicate your environment variable*/
t_list	*ft_getenv_ours(char *str, t_list *env);

/*execution functions*/
	/* prepare cmds and args */
char	**join_cmd_and_args(char *cmd, char **opts, int len);
char	**prepare_cmd(char *cmd, char **opts, char **args);
int		calcul_args(char **args);
	/*check accesse and open files*/
int		check_access(char *cmd, t_exec *p, t_list *env);
int		ft_open_files(t_prs *lst, t_exec *e);
int		open_out_files(t_prs *p, t_exec *e);
int		open_in_files(t_prs *p, t_exec *e);
void	to_free_f(int **file, int len);
int 	ft_error(char *from, int indice);
	/*execute commands*/
int		mid_cmds(t_prs *lst, t_list *envp, t_exec *e);
int		last_cmd(t_prs *lst, t_list *envp, t_exec *e);
int		first_cmd(t_prs *lst, t_list *envp, t_exec *e);


/*builtins*/
int		ft_export(char **opts, t_list *envp);
int		ft_env(t_list *node);
int		unset(char **str, t_list **env);
int		ft_exit(t_list *envp);

/*check_variavles*/
int		first_char(char c, int indice);
void	var_error(char *from, char *str, int indice);
int		valid_name(char *from, char *str, t_par *par);

/*sort_with_ascii*/
int	ft_sort_ascii(t_list *n);


int		start_exec(t_prs *lst, t_list *env);
#endif