// #include <stdio.h>
char *ft_strcpy(char *dest, char *src);
char *ft_strcpy(char *dest, char *src) {
    char *temp;

    temp = dest;
    while (*src != '\0') {
        *temp = *src;
        temp++;
        src++;
    }
    *temp = '\0'; 
    return dest;
}
// #include <stdio.h>
// int main() {
//     char dest[20] = "hello";
//     ft_strcpy(dest, "world");
//     printf("%s\n", dest);
//     return 0;
// }

/*
ポインタで回す場合
tempというポインタにdest(コピー元)の先頭のアドレスを入れておく必要がある
ポインタ同士の定義なので `temp = dest` で問題ない
文字のコピーに関しては、 `*temp = *src` という形でポインタの実数値にアクセスする必要がある
最後に `\0` 終端文字を最後のポインタに与えてdest(先頭のポインタ)を返す
*/