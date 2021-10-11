#include "../../CFoolInputs.c"

// NOTE: VEC2i STUFF

typedef struct
{
    int x;
    int y;
} vec2i;

vec2i new_vec2i(int x, int y)
{
    vec2i to_return;
    to_return.x = x;
    to_return.y = y;
    return to_return;
}

// NOTE: RENDERING STUFF

#define SCREEN_WIDTH 50
#define SCREEN_HEIGHT 25

char screen_pixels[SCREEN_HEIGHT * SCREEN_WIDTH];

void fill_screen(char bg)
{
    for (int x = 0; x < SCREEN_WIDTH; x++)
    {
        for (int y = 0; y < SCREEN_HEIGHT; y++)
        {
            screen_pixels[SCREEN_WIDTH * y + x] = bg;
        }
    }
}

void show_screen()
{
    char rendered_screen[(SCREEN_HEIGHT + 1) * (SCREEN_WIDTH + 1)] = "";

    int current_pixel = 0;

    for (int y = 0; y < SCREEN_HEIGHT; y++)
    {
        for (int x = 0; x < SCREEN_WIDTH; x++)
        {
            rendered_screen[current_pixel] = screen_pixels[SCREEN_WIDTH * y + x];
            current_pixel++;
        }
        rendered_screen[current_pixel] = '\n';
        current_pixel++;
    }
    printf("%s", rendered_screen);
}

void set_pixel(vec2i pixel_pos, char pixel)
{
    screen_pixels[SCREEN_WIDTH * pixel_pos.y + pixel_pos.x] = pixel;
}

int main()
{
    vec2i player_pos = new_vec2i(1, 1);

    while (1)
    {
        // screen things
        printf("%c", '\n');
        fill_screen('*');
        set_pixel(player_pos, '@');
        show_screen();

        int is_still = 1;

        // wait till an input is detected to move the player and update the screen
        while (is_still)
        {
            check_cfi();

            if (is_key_pressed('a'))
            {
                is_still = 0;
                player_pos.x--;
            }
            else if (is_key_pressed('s'))
            {
                is_still = 0;
                player_pos.y++;
            }
            else if (is_key_pressed('d'))
            {
                is_still = 0;
                player_pos.x++;
            }
            else if (is_key_pressed('w'))
            {
                is_still = 0;
                player_pos.y--;
            }
        }
    }
    return 0;
}