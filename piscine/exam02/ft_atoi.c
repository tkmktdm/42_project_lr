int ft_atoi(char *str);

int ft_atoi(char *str) {
    int i;
    int sign;
    long n;
    i = 0;
    sign = 1;
    n = 0;
    while (str[i] == ' ' || str[i] <= '\r' && str[i] >= '\t') {
        i++;
    }
    if (str[i] == '+' || str[i] == '-') {
        if (str[i] == '-') {
            sign = -1;
        }
        i++;
    }
    while (str[i] >= '0' && str[i] <= '9') {
        n = n * 10 + str[i] - '0';
        i++;
    }
    return n * sign;
}

#include <stdlib.h>
#include <stdio.h>
int main() {
    printf("A%d\n", atoi("+123aa"));
    printf("A%d\n", atoi("-123a"));
    printf("A%d\n", atoi(" 123a"));
    printf("A%d\n", atoi(" +123a"));
    printf("A%d\n", atoi(" -123a"));
    printf("A%d\n", atoi("  -123a"));
    printf("A%d\n", atoi("  +-123a"));
    printf("A%d\n", atoi("  ++123a"));

    printf("ft_atoi------------------\n");
    printf("A%d\n", ft_atoi("+123a"));
    printf("A%d\n", ft_atoi("-123a"));
    printf("A%d\n", ft_atoi(" 123a"));
    printf("A%d\n", ft_atoi(" +123a"));
    printf("A%d\n", ft_atoi(" -123a"));
    printf("A%d\n", ft_atoi("  -123a"));
    printf("A%d\n", ft_atoi("  +-123a"));
    printf("A%d\n", ft_atoi("  ++123a"));
    return 0;
}