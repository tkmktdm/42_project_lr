
char	*ft_strpbrk(const char *s1, const char *s2) {
	int i, j;
	i = 0;
	j = 0;
	while(s1[i]) {
		while(s2[j]) {
			if (s1[i] == s2[j]) {
				return ((char*)&s1[i]);
			}
			j++;
		}
		j = 0;
		i++;
	}
	return 0;
}

// #include <string.h>
// #include<stdio.h>
// int main () {
// 	char s1[6] = "hello";
// 	char s2[6] = "orz";
// 	// printf("%s", strpbrk(s1, s2));
// 	printf("%s", ft_strpbrk(s1, s2));
// 	return 0;
// }
