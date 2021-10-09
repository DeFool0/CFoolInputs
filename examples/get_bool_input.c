#include "../CFoolInputs.c"

int main()
{
    printf("Yes or no:\n");
    bool answer = get_input_yes_or_no();
    printf("Returned: %d", answer);
    return 0;
}