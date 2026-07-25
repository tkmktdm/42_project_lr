/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_disorder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htakumi <htakumi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/13 15:23:47 by htakumi           #+#    #+#             */
/*   Updated: 2026/06/13 15:23:48 by htakumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

long long	merge_and_count(int arr[], int temp[], int left, int mid, int right)
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
		if (arr[i] <= arr[j])
		{
			temp[k] = arr[i];
			i++;
		}
		else
		{
			temp[k] = arr[j];
			j++;
			inversions += (mid - i + 1);
		}
		k++;
	}
	while (i <= mid)
	{
		temp[k] = arr[i];
		i++;
		k++;
	}
	while (j <= right)
	{
		temp[k] = arr[j];
		j++;
		k++;
	}
	i = left;
	while (i <= right)
	{
		arr[i] = temp[i];
		i++;
	}
	return (inversions);
}

long long	merge_sort_and_count(int arr[], int temp[], int left, int right)
{
	long long	inversions;
	int			mid;

	inversions = 0;
	if (left < right)
	{
		mid = left + (right - left) / 2;
		inversions += merge_sort_and_count(arr, temp, left, mid);
		inversions += merge_sort_and_count(arr, temp, mid + 1, right);
		inversions += merge_and_count(arr, temp, left, mid, right);
	}
	return (inversions);
}

double	calculate_disorder_fast(int a[], int n)
{
	double		total_pairs;
	int			*arr_copy;
	int			*temp;
	long long	mistakes;
	int			i;

	if (n <= 1)
		return (0.0);
	total_pairs = (double)n * (n - 1) / 2.0;
	arr_copy = (int *)malloc(n * sizeof(int));
	if (!arr_copy)
		return (0.0);
	i = 0;
	while (i < n)
	{
		arr_copy[i] = a[i];
		i++;
	}
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

int	main(void)
{
	int array[4];
	int n;
	double disorder;

	array[0] = 3;
	array[1] = 1;
	array[2] = 4;
	array[3] = 2;
	n = 4;
	disorder = calculate_disorder_fast(array, n);
	printf("不整合度 (Disorder): %.4f\n", disorder);
	return (0);
}
