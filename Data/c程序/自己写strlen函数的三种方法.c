#include <stdio.h>

int my_strlen(char *str)
{
    int count = 0;
    while (*str++ != '\0')
    {
        count++;
    }
    return count;
}

int main(int argc, char *argv[])
{
    char str[] = "abcdeffg";
    int ret = my_strlen(str);
    printf("%d", ret);    
}