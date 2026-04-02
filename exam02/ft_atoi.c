int ft_atoi(char *str);

// int ft_atoi(char *str) {
//     int pf;
//     int mf;
//     long res;

//     pf = 0;
//     mf = 0;
//     res = 0;
//     while (*str) {
//         if (!(*str >= '0' && *str <= '9' || *str == ' ' || *str >= 9 && *str <= 13 || *str == '+' || *str == '-')) {
//             if (mf) {
//                 res = -res;
//             }
//             return res;
//         }
//         if (*str == '+') {
//             pf += 1;
//         } else if (*str == '-') {
//             mf += 1;
//         }
//         if (pf > 1 || mf > 1) {
//             return 0;
//         }
//         if (*str >= '0' && *str <= '9') {
//             res = res * 10 + (*str - '0');
//         }
//         str++;
//     }
//     if (mf) {
//         res = -res;
//     }
//     return res;
// }

int ft_atoi(char *str)
{
    int sign = 1;
    long res = 0;

    // 空白スキップ
    while (*str == ' ' || (*str >= 9 && *str <= 13))
        str++;

    // 符号
    if (*str == '+' || *str == '-')
    {
        if (*str == '-')
            sign = -1;
        str++;
    }

    // 数字
    while (*str >= '0' && *str <= '9')
    {
        res = res * 10 + (*str - '0');
        str++;
    }

    return res * sign;
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
    printf("ft_atoi------------------\n");
    printf("A%d\n", ft_atoi("+123a"));
    printf("A%d\n", ft_atoi("-123a"));
    printf("A%d\n", ft_atoi(" 123a"));
    printf("A%d\n", ft_atoi(" +123a"));
    printf("A%d\n", ft_atoi(" -123a"));
    printf("A%d\n", ft_atoi("  -123a"));
    printf("A%d\n", atoi("  +-123a"));
    return 0;
}