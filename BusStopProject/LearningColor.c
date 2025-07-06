#include <stdio.h>

int main() {
    const char* textBac = "Hello, World!";
    const char* colorsBac[] = {
        "\033[41m", // Red
        "\033[42m", // Green
        "\033[43m", // Yellow
        "\033[44m", // Blue
        "\033[45m", // Magenta
        "\033[46m", // Cyan
        "\033[47m", // White
    };
    int num_colorsBac = sizeof(colorsBac) / sizeof(colorsBac[0]);

    for (int i = 0; textBac[i] != '\0'; i++) {
        printf("%s%c\033[0m", colorsBac[i % num_colorsBac], textBac[i]);  // Color char, then reset
    }

    printf("\n");

    const char* text = "Colorful Text!";
    const char* colors[] = {
        "\033[31m", // Red
        "\033[32m", // Green
        "\033[33m", // Yellow
        "\033[34m", // Blue
        "\033[35m", // Magenta
        "\033[36m", // Cyan
        "\033[37m", // White
    };
    int num_colors = sizeof(colors) / sizeof(colors[0]);

    for (int i = 0; text[i] != '\0'; i++) {
        printf("%s%c\033[0m", colors[i % num_colors], text[i]); // Color char, then reset
    }

    printf("\033[5;5HHello, World!");

    printf("\n");
    return 0;
}
