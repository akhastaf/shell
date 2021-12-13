#include "../../includes/minishell.h"

// static char	*ft_strdup(const char *s1)
// {
// 	int		i;
// 	char	*str;

// 	i = 0;
// 	if (!(str = (char*)malloc((ft_strlen(s1) * sizeof(char)) + 1)))
// 		return (NULL);
// 	while (s1[i] != '\0')
// 	{
// 		str[i] = s1[i];
// 		i++;
// 	}
// 	str[i] = s1[i];
// 	return (str);
// }

// static char	*ft_strndup(const char *s1, size_t n)
// {
// 	size_t	i;
// 	char	*str;

// 	i = 0;
// 	if (!(str = (char*)malloc((n * sizeof(char)) + 1)))
// 		return (NULL);
// 	while (s1[i] != '\0' && i < n)
// 	{
// 		str[i] = s1[i];
// 		i++;
// 	}
// 	str[i] = '\0';
// 	return (str);
// }

// static size_t	ft_strlen(const char *s)
// {
// 	int i;

// 	i = 0;
// 	while (s[i] != '\0')
// 		i++;
// 	return (i);
// }

// static char	*ft_strchr(const char *s, int c)
// {
// 	char *str;

// 	str = (char*)s;
// 	if (!s)
// 		return (NULL);
// 	if (!c)
// 		return (str + ft_strlen(s));
// 	while (*str)
// 	{
// 		if (*str == c)
// 			return (str);
// 		str++;
// 	}
// 	return (NULL);
// }

// static char	*ft_strjoin(char *s1, char *s2)
// {
// 	char	*str;
// 	int		i;
// 	int		j;

// 	if (!s1 && s2)
// 		return (ft_strdup(s2));
// 	if (s1 && !s2)
// 		return (ft_strdup(s1));
// 	if (!(str = malloc(sizeof(char) * ((ft_strlen(s1) + ft_strlen(s2) + 1)))))
// 		return (NULL);
// 	i = 0;
// 	while (s1[i] != '\0')
// 	{
// 		str[i] = s1[i];
// 		i++;
// 	}
// 	j = 0;
// 	while (s2[j] != '\0')
// 	{
// 		str[i + j] = s2[j];
// 		j++;
// 	}
// 	str[i + j] = '\0';
// 	return (str);
// }

char	*ft_checkerror(int fd, char **buff)
{
	if (!(BUFFER_SIZE >= 1) || (read(fd, *buff, 0) < 0))
		return (NULL);
	return (*buff);
}

int		ft_readline(int fd, char **str)
{
	char	*tmp;
	char	*buff;
	int		n;

	if ((!(buff = malloc(BUFFER_SIZE + 1))) || (!ft_checkerror(fd, &buff)))
	{
		free(buff);
		return (-1);
	}
	while ((n = read(fd, buff, BUFFER_SIZE)) > 0)
	{
		buff[n] = '\0';
		tmp = *str;
		*str = ft_strjoin(*str, buff);
		free(tmp);
		if (ft_strchr(*str, '\n'))
			break ;
	}
	free(buff);
	return (n);
}

int		get_next_line(int fd, char **line)
{
	static char	*str[ULIMIT];
	char		*tmp;
	char		*s;
	int			n;

	if ((n = ft_readline(fd, &str[fd]) < 0 || !line))
		return (-1);
	if ((s = ft_strchr(str[fd], '\n')))
	{
		*line = ft_strndup(str[fd], s - str[fd]);
		tmp = str[fd];
		str[fd] = ft_strdup(s + 1);
		free(tmp);
		return (1);
	}
	if (!n && str[fd])
	{
		*line = ft_strdup(str[fd]);
		free(str[fd]);
		str[fd] = NULL;
		return (0);
	}
	*line = ft_strdup("");
	return (0);
}

