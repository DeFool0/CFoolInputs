#include "../CFoolInputs.c"

int main()
{
    printf("started");

    int running = 1;
    while (running)
    {
        check_cfi();

        if (is_key_pressed('j')) printf("Pressed j\n");
        else if (is_key_pressed('e')) running = 0;
    }
    return 0;
}