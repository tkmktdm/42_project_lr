#include <stdio.h>

int main(int ac, char **av) {
    int i;

    i = 0;
    if (ac == 2) {
        while (av[1][i] != '\0')
        {
            i++;
        }
        if(ft_space(av[1][i]))
        printf("%d", i);
    }
    return 0;
}