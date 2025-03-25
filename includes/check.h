/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalebrun <nalebrun@student.s19.be>        +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 10:15:56 by nalebrun          #+#    #+#             */
/*   Updated: 2025/03/21 10:15:56 by nalebrun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECK_H
# define CHECK_H

int check(int ac, char **av);

// internal
int	check_file(char *file);
int	raise_error(int l, char *error, char *line, int elem);
int	ac_error(int l, char *line, char *exp, int ac);
int	tab_len(char **tab);

int check_ca(char **split, char *line, int l);
int check_li(char **split, char *line, int l);
int check_am(char **split, char *line, int l);
int check_sp(char **split, char *line, int l);
int check_pl(char **split, char *line, int l);
int	check_cn(char **split, char *line, int l);
int	check_cl(char **split, char *line, int l);

int	format_rgb(char *split, int l, char *line, int arg);
int	format_vec(char *split, int l, char *line, int arg);

#endif // !CHECK_H
