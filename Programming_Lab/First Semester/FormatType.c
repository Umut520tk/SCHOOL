#include <stdio.h>

int main() {
    int d = 42;
    unsigned int u = 42;
    int o = 42;
    int x = 42;
    float f = 3.14159;
    double e = 2.71828;
    char c = 'A';
    char s[] = "Hello, World!";
    void *p = &d;

    printf("Signed decimal integer: %d\n", d);
    printf("Unsigned decimal integer: %u\n", u);
    printf("Unsigned octal: %o\n", o);
    printf("Unsigned hexadecimal: %x\n", x);
    printf("Decimal floating-point: %f\n", f);
    printf("Scientific notation: %lf\n", e);
    printf("Single character: %c\n", c);
    printf("String of characters: %s\n", s);
    printf("Pointer address: %p\n", p);
    printf("Literal percent sign: %%\n");

    return 0;
}