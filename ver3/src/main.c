/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalshafy <aalshafy@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 13:29:07 by aalshafy          #+#    #+#             */
/*   Updated: 2024/03/06 12:09:15 by aalshafy         ###   ########.fr       */
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
    printf("argc: %d\n", argc); 
    i = init_philosophers(&data);
    if (i != 0)
    {
        if (i == 1)
            printf("Error: pthread_mutex_init\n");
        else if (i == 2)
            printf("Error: pthread_mutex_init\n");
        else if (i == 3)
            printf("Error: pthread_mutex_init\n");
        else if (i == 4)
            printf("Error: pthread_create\n");
        else if (i == 5)
            return (0);
        return (1);
    }
}