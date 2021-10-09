#include "../CFoolInputs.c"

int main()
{
    printf("What's your age:\n");
    int age = get_input_int();
    printf("Returned: %d", age);
    return 0;
}