#include<stdio.h>
#include<stdlib.h>

int main() {
    FILE *f = fopen("./clean_src.txt", "r");
    FILE *output = fopen("./clean_dst.txt", "w+");
    char str[1024];
    while(fgets(str,1000,f)) {
        printf("%s",str);
        if (str[0] == '+') {
            fputs(str + 1,output);
        }
    }

    return 0;

}