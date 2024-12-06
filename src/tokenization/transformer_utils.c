/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformer_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 22:57:48 by ccodere           #+#    #+#             */
/*   Updated: 2024/12/05 22:59:42 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_bool  is_heredoc_delim(t_minishell *ms, char **tokens, int k)
{
    if (k > 0 && (is_heredoc(tokens[k - 1]) && ms->token.quoted[k - 1] == 0) && tokens[k])
        return (TRUE);
    return (FALSE);
}
