#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#define CFISTRING_LEN 128

typedef struct
{
    char text_data[CFISTRING_LEN];
} CFIString;

// TODO: Fix bug where sometimes you can input one less char than the actually especified number
CFIString get_input_text()
{
    CFIString return_str;
    char buffer_str[CFISTRING_LEN] = "";
    int cursor = 0;

    int running = 1;
    while (running)
    {
        if (kbhit())
        {
            char character = (char)getch();

            if ((int)character == 8 && cursor != 0)
            {
                buffer_str[cursor] = (char)0;
                cursor--;
                buffer_str[cursor] = (char)0;
            }
            else if ((int)character != 13)
            {
                buffer_str[cursor] = character;
                cursor++;
            }

            printf("\x1B[2K");
            printf("\x1B[0E");
            printf(buffer_str);

            if ((int)character == 13)
            {
                running = 0;
                printf("\n");
            }
        }
    }

    strcpy(return_str.text_data, buffer_str);

    return return_str;
}

// TODO: Propably merge this function with the without limit version
// TODO: Fix bug where sometimes you can input one less char than the actually especified number
CFIString get_input_text_with_limit(int limit)
{
    CFIString return_str;
    char buffer_str[CFISTRING_LEN] = "";
    int cursor = 0;

    int running = 1;
    while (running)
    {
        if (kbhit())
        {
            char character = (char)getch();

            if ((int)character == 8 && cursor != 0)
            {
                buffer_str[cursor] = (char)0;
                cursor--;
                buffer_str[cursor] = (char)0;
            }
            else if ((int)character != 13 && strlen(buffer_str) != limit)
            {
                buffer_str[cursor] = character;
                cursor++;
            }

            printf("\x1B[2K");
            printf("\x1B[0E");
            printf(buffer_str);

            if ((int)character == 13)
            {
                running = 0;
                printf("\n");
            }
        }
    }

    strcpy(return_str.text_data, buffer_str);

    return return_str;
}

bool get_input_yes_or_no()
{
    int running = 1;
    char buffer_choice = ' ';
    while (running)
    {
        if (kbhit())
        {
            char character = (char)getch();

            if (character == 'y' || character == 'Y')
                buffer_choice = 'Y';
            else if (character == 'n' || character == 'N')
                buffer_choice = 'N';

            printf("\x1B[2K");
            printf("\x1B[0E");
            printf("%c", buffer_choice);

            if ((int)character == 13 && (buffer_choice == 'N' || buffer_choice == 'Y'))
            {
                running = 0;
                printf("\n");
            }
        }
    }

    bool return_bool = buffer_choice == 'Y';

    return return_bool;
}

int get_input_int()
{
    char buffer_str[CFISTRING_LEN] = "";
    int cursor = 0;

    int running = 1;
    while (running)
    {
        if (kbhit())
        {
            char character = (char)getch();

            if ((int)character == 8 && cursor != 0)
            {
                buffer_str[cursor] = (char)0;
                cursor--;
                buffer_str[cursor] = (char)0;
            }
            else if ((int)character != 13 && character <= '9' && character >= '0')
            {
                buffer_str[cursor] = character;
                cursor++;
            }

            printf("\x1B[2K");
            printf("\x1B[0E");
            printf(buffer_str);

            if ((int)character == 13)
            {
                running = 0;
                printf("\n");
            }
        }
    }

    return atoi(buffer_str);
}
