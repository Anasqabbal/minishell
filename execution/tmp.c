int	ft_lstget_pos(char *str, t_list *lst)
{
	char	*tmp1;
	int		j;
	int		i;

	tmp1 = NULL;
	if (ft_strchr(str, '+'))
		tmp1 = remove_plus(str, tmp1);
	if (tmp1)
		printf("after remove + your content became === %s\n", tmp1);
	i = 0;
	while (lst)
	{
		j = -1;
		if (!tmp1)
		{
			while(str[++j] && str[j] != '=')
				;
			if (!ft_strncmp(lst->content, str, j))
				return (i);
		}
		else if (tmp1)
		{
			while(tmp1[++j] && tmp1[j] != '=')
				;
			 if (!ft_strncmp(lst->content, tmp1, j))
				return (i);
		}
		lst = lst->next;
		i++;
	}
	return (-1);
}

int	unset1(char *str, t_list **envp, char **path, t_list **new)
{
	char	*tmp;
	int		pos;
	t_list	*head;
	t_list	*env;

	env = *envp;
	tmp = ft_strjoin(str, "=");
	if (!tmp)
		return (1);
	if (*path && !ft_strncmp(tmp, "PATH=", 5))
		return (*path = NULL, *new = env, 1);
	pos = ft_lstget_pos(tmp, env);
	if (pos == -1)
		return (free(tmp), *new = env, 1);
	if (ft_envdup_exept(env, tmp, &head))
		return (free(tmp), 1);
	free(tmp);
	return (*new = head, 0);
}