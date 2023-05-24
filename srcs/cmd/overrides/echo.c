/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogpere <diogpere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 14:22:23 by diogpere          #+#    #+#             */
/*   Updated: 2023/05/24 14:22:27 by diogpere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd/overrides.h"

void cmds_overrides_echo_cmd(char** args) {
    int i;
    bool suppressNewline;

    i = 1;
    suppressNewline = false;
    if (args[i] != NULL && ft_strncmp(args[i], "-n", 3) == 0) {
        suppressNewline = true;
        i++;
    }
    while (args[i] != NULL) {
        printf("%s", args[i]);
        if (args[i + 1] != NULL) {
            printf(" ");
        }
        i++;
    }
    if (!suppressNewline) {
        printf("\n");
    }
}