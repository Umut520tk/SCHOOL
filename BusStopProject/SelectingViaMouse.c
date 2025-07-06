#include <windows.h>
#include <stdio.h>
#include <conio.h>

int main() {
    // Enable mouse input
    HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
    DWORD prev_mode;
    GetConsoleMode(hInput, &prev_mode);
    SetConsoleMode(hInput, ENABLE_MOUSE_INPUT | ENABLE_EXTENDED_FLAGS);

    // Set console title
    SetConsoleTitle("Click on Characters");

    // Print some characters for testing
    printf("Click on any of these characters:\n");
    printf("A B C D E F G H I J\n");
    printf("1 2 3 4 5 6 7 8 9 0\n");

    INPUT_RECORD irInBuf[128];
    DWORD cNumRead;

    while (1) {
        // Read console input
        ReadConsoleInput(hInput, irInBuf, 128, &cNumRead);

        for (DWORD i = 0; i < cNumRead; i++) {
            if (irInBuf[i].EventType == MOUSE_EVENT) {
                if (irInBuf[i].Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED) {
                    // Get mouse position
                    COORD mousePos = irInBuf[i].Event.MouseEvent.dwMousePosition;
                    
                    // Get character at mouse position
                    CHAR_INFO charInfo;
                    COORD bufferSize = {1, 1};
                    COORD bufferCoord = {0, 0};
                    SMALL_RECT readRegion = {mousePos.X, mousePos.Y, mousePos.X, mousePos.Y};
                    
                    ReadConsoleOutput(GetStdHandle(STD_OUTPUT_HANDLE), &charInfo, bufferSize, bufferCoord, &readRegion);
                    
                    // Print the clicked character
                    printf("\nCharacter '%c' was clicked at position (%d, %d)\n", 
                           charInfo.Char.AsciiChar, mousePos.X, mousePos.Y);
                }
            }
        }
    }

    // Restore console mode
    SetConsoleMode(hInput, prev_mode);
    return 0;
}
