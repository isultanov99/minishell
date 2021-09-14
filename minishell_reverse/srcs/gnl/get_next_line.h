/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpablo <cpablo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 21:06:10 by cpablo            #+#    #+#             */
/*   Updated: 2021/04/29 22:27:25 by cpablo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define BUFFER_SIZE 32

# include <stdlib.h>
# include <unistd.h>

typedef struct s_gnl
{
	char			buf[BUFFER_SIZE + 1];
	int				bytes_read;
	char			*ptr_n;
	char			*tmp;
}	t_gnl;

size_t	ft_strlen(const char *s);
char	*ft_strjoin(char const *s1, char const *s2);
void	*ft_memset(void *destination, int c, size_t n);
char	*ft_strnew(size_t size);
char	*ft_strchr(const char *str, int ch);
char	*ft_strdup(const char *str);
char	*ft_strcpy(char *dest, char *src);
void	find_new_line(char **ptr_n, char **remainder, char *buf);
char	*check_remainder(char **remainder, char **line);
int		get_next_line(int fd, char **line);
void	gnl_free(char **line);
void	gnl_tmp(t_gnl *gnl, char **line);

#endif
