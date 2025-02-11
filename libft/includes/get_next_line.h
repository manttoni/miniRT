/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzharkev <nzharkev@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 17:40:50 by amaula            #+#    #+#             */
/*   Updated: 2025/01/24 16:49:45 by nzharkev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1000
# endif

# include <stdlib.h>
# include <unistd.h>

char	*get_next_line(int fd);
// size_t	ft_strlen(char *s);
char	*gnl_join(char *dst, char *src, size_t len);
// char	*ft_strchr(char *str, char chr);
void	gnl_copy(char *dst, char *src);
// void	ft_bzero(char *buffer, size_t size);

#endif
