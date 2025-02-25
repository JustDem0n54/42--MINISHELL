/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrontard <nrontard@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 14:36:14 by nrontard          #+#    #+#             */
/*   Updated: 2025/02/13 14:57:58 by nrontard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <errno.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1000
# endif

# if BUFFER_SIZE > 1000000
#  undef BUFFER_SIZE
#  define BUFFER_SIZE 1000000
# endif

void	ft_bzerognl(void *s, size_t n);
void	*ft_callocgnl(size_t count, size_t size);
int		ft_strchrgnl(char *str, int c);
size_t	ft_strlengnl(char *s);
char	*ft_strjoingnl(char *storage, char *buff, int size);
char	*read_check(char *str, int fd, char *buff);
char	*get_next_line(int fd);
char	*create_storage(char *str);
char	*ft_strcpy(char *str);

#endif