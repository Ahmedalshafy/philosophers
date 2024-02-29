/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalshafy <aalshafy@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 13:29:07 by aalshafy          #+#    #+#             */
/*   Updated: 2024/02/28 09:40:04 by aalshafy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../philosopher.h"

int main(int argc, char **argv)
{
    t_data data;
    int i;

    if (argc != 6)
    {
        printf("Error: wrong number of arguments\n");
        return (1);
    }
    if (!init_data(&data, argv))
    {
        printf("Error: wrong arguments\n");
        return (1);
    }
    i = init_philosophers(&data);
    if (i != 0)
    {
        printf("Error: %d\n", i);
        return (1);
    }
}