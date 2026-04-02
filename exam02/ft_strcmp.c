int ft_strcmp(char *s1, char *s2);

int ft_strcmp(char *s1, char *s2) {
    while(*s1 || *s2) {
        if ((unsigned char)*s1 != (unsigned char)*s2) {
            return (unsigned char)*s1 - (unsigned char)*s2;
        }
        s1++;
        s2++;
    }
    return 0;
}

// int ft_strcmp(char *s1, char *s2)
// {
//     while (*s1 && (*s1 == *s2))
//     {
//         s1++;
//         s2++;
//     }
//     return (*s1 - *s2);
// }

#include <string.h>
#include <stdio.h>
int main() {
    printf(" a: %d = %d\n", strcmp("", "a"), ft_strcmp("", "a"));
    printf("hai: %d = %d\n", strcmp("hello", "hai"), ft_strcmp("hello", "hai"));
    printf("hei: %d = %d\n", strcmp("hello", "hoi"), ft_strcmp("hello", "hoi"));
    printf("hello: %d = %d\n", strcmp("hello", "hello"), ft_strcmp("hello", "hello"));
    printf("hai: %d = %d\n", strcmp("hai", "hello"), ft_strcmp("hai", "hello"));
    printf("hei: %d = %d\n", strcmp("hoi", "hello"), ft_strcmp("hoi", "hello"));
    printf("hello: %d = %d\n", strcmp("hello", "hello"), ft_strcmp("hello", "hello"));
    return 0;
}