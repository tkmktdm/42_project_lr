#include<ctype.h>
#include<stdio.h>
#include<unistd.h>

int ft_isalpha(int c) {
    if (c >= 'A' && c <= 'Z' || c >= 'a' && c <= 'z')
        return 1;
    return 0;
}
int main() {
    printf("ft %d\n", ft_isalpha('a'));
    printf("ft %d\n", ft_isalpha(9));
    printf("%d\n", isalpha('a'));
    printf("%d\n", isalpha(9));
    return 0;
}