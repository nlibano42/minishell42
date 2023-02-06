/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_params.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlibano- <nlibano-@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 22:05:45 by nlibano-          #+#    #+#             */
/*   Updated: 2023/02/03 22:05:50 by nlibano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void    free_split(char **s)
{
    int i;

    i = -1;
    while (s[++i])
        free(s[i]);
    free(s);
}