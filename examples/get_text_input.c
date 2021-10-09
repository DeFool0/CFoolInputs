#include "../CFoolInputs.c"

int main()
{
    printf("What's your name?:\n");
    CFIString name = get_input_text();
    printf("Hello there, %s!", name.text_data);
    return 0;
}