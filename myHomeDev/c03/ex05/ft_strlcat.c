/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htakumi <htakumi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/29 11:47:39 by htakumi           #+#    #+#             */
/*   Updated: 2026/03/31 21:04:57 by htakumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <bsd/string.h>
// #include <stdio.h>

unsigned int	ft_strlcat(char *dest, char *src, unsigned int size);

int	ft_strlen(char *str)
{
	int	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

unsigned int	ft_strlcat(char *dest, char *src, unsigned int size)
{
	unsigned int	dlen;
	unsigned int	slen;
	unsigned int	i;

	dlen = 0;
	slen = 0;
	i = 0;
	dlen = ft_strlen(dest);
	slen = ft_strlen(src);
	if (size <= dlen)
		return (size + slen);
	while (src[i] != '\0' && dlen + i < size - 1)
	{
		dest[dlen + i] = src[i];
		i++;
	}
	dest[dlen + i] = '\0';
	return (dlen + slen);
}

// int	main(void)
// {
// 	char	buf1[10] = "Hello";
// 	char	buf2[10] = "Hello";
// 	char	buf3[10] = "Hello";
// 	char	buf4[10] = "";
// 	char	duf1[10] = "Hello";
// 	char	duf2[10] = "Hello";
// 	char	duf3[10] = "Hello";
// 	char	duf4[10] = "";
// 	int		len;

// 	// /**
// 	// 	* 結合後の文字数がサイズ(10)を超える場合、9文字+NULLが格納される
// 	// 	*/
// 	len = strlcat(buf1, "defghij", 10);
// 	printf("%s: %d\n", buf1, len);
// 	len = strlcat(buf2, "a", 10);
// 	printf("%s: %d\n", buf2, len);
// 	len = strlcat(buf3, "a", 4);
// 	printf("%s: %d\n", buf3, len);
// 	len = strlcat(buf4, "a", 0);
// 	printf("%s: %d\n", buf4, len);
// 	len = strlcat("", "", 0);
// 	printf("%s: %d\n", "", len);
// 	len = ft_strlcat(duf1, "defghij", 10);
// 	printf("%s: %d\n", duf1, len);
// 	len = ft_strlcat(duf2, "a", 10);
// 	printf("%s: %d\n", duf2, len);
// 	len = ft_strlcat(duf3, "a", 4);
// 	printf("%s: %d\n", duf3, len);
// 	len = ft_strlcat(duf4, "a", 0);
// 	printf("%s: %d\n", duf4, len);
// 	len = ft_strlcat("", "", 0);
// 	printf("%s: %d\n", "", len);
// }
