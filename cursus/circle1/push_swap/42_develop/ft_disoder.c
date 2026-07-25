/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_disoder.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htakumi <htakumi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/13 15:17:28 by hibitakumi        #+#    #+#             */
/*   Updated: 2026/07/19 12:35:35 by htakumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <stdio.h>
#include <stdlib.h>

static void	copy_array(int *dst, int *src, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		dst[i] = src[i];
		i++;
	}
}

static void	copy_back(t_arrs *a, int left, int right)
{
	int	i;

	i = left;
	while (i <= right)
	{
		a->arr[i] = a->temp[i];
		i++;
	}
}

static long long	do_merge(t_arrs *a, int left, int mid, int right)
{
	int			i;
	int			j;
	int			k;
	long long	inversions;

	i = left;
	j = mid + 1;
	k = left;
	inversions = 0;
	while (i <= mid && j <= right)
	{
		if (a->arr[i] <= a->arr[j])
			a->temp[k++] = a->arr[i++];
		else
		{
			a->temp[k++] = a->arr[j++];
			inversions += (mid - i + 1);
		}
	}
	while (i <= mid)
		a->temp[k++] = a->arr[i++];
	while (j <= right)
		a->temp[k++] = a->arr[j++];
	return (inversions);
}

static long long	merge_sort_and_count(int arr[], int temp[], int left,
		int right)
{
	long long	inversions;
	int			mid;
	t_arrs		a;

	inversions = 0;
	if (left < right)
	{
		mid = left + (right - left) / 2;
		a.arr = arr;
		a.temp = temp;
		inversions += merge_sort_and_count(arr, temp, left, mid);
		inversions += merge_sort_and_count(arr, temp, mid + 1, right);
		inversions += do_merge(&a, left, mid, right);
		copy_back(&a, left, right);
	}
	return (inversions);
}

double	calculate_disorder_fast(int a[], int n)
{
	double		total_pairs;
	int			*arr_copy;
	int			*temp;
	long long	mistakes;

	if (n <= 1)
		return (0.0);
	total_pairs = (double)n * (n - 1) / 2.0;
	arr_copy = (int *)malloc(n * sizeof(int));
	if (!arr_copy)
		return (0.0);
	copy_array(arr_copy, a, n);
	temp = (int *)malloc(n * sizeof(int));
	if (!temp)
	{
		free(arr_copy);
		return (0.0);
	}
	mistakes = merge_sort_and_count(arr_copy, temp, 0, n - 1);
	free(arr_copy);
	free(temp);
	return ((double)mistakes / total_pairs);
}
