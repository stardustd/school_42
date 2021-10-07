/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_foreach_if.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbaatar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 12:33:52 by bbaatar           #+#    #+#             */
/*   Updated: 2021/10/07 12:33:53 by bbaatar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"

t_list  *create_elem(int *data)
{
    t_list *elem;

    if (!(elem = malloc(sizeof(t_list))))
        return (0);
    elem->data = data;
    elem->next = NULL;

    return (elem);
}

void ft_list_reverse(t_list **begin_list)
{
    t_list  *curr= NULL, *prev = NULL, *suiv = NULL;

    curr = *begin_list;
    while (curr)
    {
        suiv = curr->next;
        curr->next = prev;
        prev = curr;
        curr = suiv;
    }
    *begin_list = prev;
}

void f(int  *nbr)
{
    printf("%d", *(int *)nbr);
}

int *ft_intcmp (int *data, int *data_ref)
{
    if (*data < *data_ref)
        return (1);
    else
        return (0);
}

void ft_list_foreach_if(t_list *begin_list, void (*f)(void *), void *data_ref, int (*ft_intcmp)())
{
    
}

int main(void)
{
    t_list *a;
    int nbrs[4] = {12, 34, 56, 78};
    int i = 1;

    a = create_elem(nbrs[0]);
    while (i < 4)
    {
        a->next = create_elem(nbrs[i]);
        a = a->next;
        i++;
    }
    
}
