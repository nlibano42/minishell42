/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlibano- <nlibano-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 17:36:19 by nlibano-          #+#    #+#             */
/*   Updated: 2023/03/09 21:53:54 by nlibano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>
# include <stdlib.h>
# define BUFFER_SIZE 1

char	*get_next_line(int fd);
int		ft_str_pos(char *s, int c);
char	*gnl_strjoin(char *s1, char *s2);
size_t	gnl_strlen(const char *s);
char	*gnl_substr(char const *s, unsigned int start, size_t len);
char	*gnl_strdup(const char *s1);
size_t	gnl_strlcat(char *dst, const char *src, size_t dstsize);
size_t	gnl_strlcpy(char *dst, const char *src, size_t dstsize);
char	*ft_find_nl(char *str, int *find, char **tmp, char *line);
int		ft_find_tmp_nl(char **tmp, char **line);

#endif
