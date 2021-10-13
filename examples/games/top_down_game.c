#include "../../CFoolInputs.c"

// NOTE: CONSTS

#define SCREEN_WIDTH 50
#define SCREEN_HEIGHT 30

typedef struct
{
    int x;
    int y;
} Vec2i;

typedef struct
{
    Vec2i world_pos;
    char name[10];
} Player;

#define RENDER_QUEUE_SIZE 128

typedef struct
{
    char render_type[30];
    Vec2i world_pos;
} RenderRequest;

// NOTE: IMPLICIT DECLARATIONS

void set_pixel(Vec2i pixel_pos, char pixel);

// NOTE: VEC2I STUFF

Vec2i new_vec2i(int x, int y)
{
    Vec2i to_return;
    to_return.x = x;
    to_return.y = y;
    return to_return;
}

Vec2i vec2i_sum(Vec2i vec1, Vec2i vec2)
{
    Vec2i to_return;
    to_return.x = vec1.x + vec2.x;
    to_return.y = vec1.y + vec2.y;
    return to_return;
}

Vec2i vec2i_sub(Vec2i vec1, Vec2i vec2)
{
    Vec2i to_return;
    to_return.x = vec1.x - vec2.x;
    to_return.y = vec1.y - vec2.y;
    return to_return;
}

// NOTE: PLAYER STUFF

Player new_player(Vec2i world_pos)
{
    Player to_return;
    to_return.world_pos = world_pos;
    return to_return;
}

// NOTE: CAMERA STUFF

typedef struct
{
    Vec2i world_pos;
    RenderRequest render_queue[RENDER_QUEUE_SIZE];
    int render_queue_index;
} Camera;

Camera new_camera(Vec2i world_pos)
{
    Camera to_return;
    to_return.world_pos = world_pos;
    to_return.render_queue_index = 0;
    return to_return;
}

void clear_cam_data(Camera *camera)
{
    camera->render_queue_index = 0;
}

void render_player(Camera *camera, Player player)
{
    RenderRequest player_render_request;
    strcpy(player_render_request.render_type, "player");
    player_render_request.world_pos = player.world_pos;
    camera->render_queue[camera->render_queue_index] = player_render_request;
    camera->render_queue_index++;
}

void show_cam(Camera *camera)
{
    // Cam pos = 25, 15
    // Player pos = 1, 1
    // Player screen pos = 1, 1

    for (int i = 0; i != camera->render_queue_index; i++)
    {
        RenderRequest cur_render = camera->render_queue[i];
        if (strcmp(cur_render.render_type, "player") == 0)
        {
            Vec2i cur_render_pos = cur_render.world_pos;
            Vec2i camera_pos = camera->world_pos;
            
            Vec2i scr_pos = new_vec2i(cur_render_pos.x + SCREEN_WIDTH / 2 - camera_pos.x, cur_render_pos.y + SCREEN_HEIGHT / 2 - camera_pos.y);

            printf("Scr pos: (%d, %d)\n", scr_pos.x, scr_pos.y);
            set_pixel(scr_pos, '@');
        }
    }
}

// NOTE: RENDERING STUFF

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
    rendered_screen[current_pixel - 1] = '\0';
    puts(rendered_screen);
}

void set_pixel(Vec2i pixel_pos, char pixel)
{
    if (pixel_pos.x >= 0 && pixel_pos.x < SCREEN_WIDTH)
        if (pixel_pos.y >= 0 && pixel_pos.y < SCREEN_HEIGHT)
            screen_pixels[SCREEN_WIDTH * pixel_pos.y + pixel_pos.x] = pixel;
}

// NOTE: DEBUGGING STUFF
void debug_print_info(Vec2i player_pos, Vec2i cam_pos)
{
    printf("Player pos: (%d, %d)\n", player_pos.x, player_pos.y);
    printf("Camera pos: (%d, %d)\n", cam_pos.x, cam_pos.y);
    printf("Vec2i size: %d\n", sizeof(Vec2i));
    printf("Player size: %d\n", sizeof(Player));
    printf("RenderRequest size: %d\n", sizeof(RenderRequest));
    printf("Camera size: %d\n", sizeof(Camera));
}

// NOTE: MAIN GAME STUFF

int main()
{
    Player player = new_player(new_vec2i(1, 1));
    Vec2i world_size = new_vec2i(100, 100);
    Camera camera = new_camera(new_vec2i(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2));

    while (1)
    {
        clear_cam_data(&camera);
        render_player(&camera, player);

        puts("\n");

        // screen things
        fill_screen('*');
        show_cam(&camera);
        show_screen();

        debug_print_info(player.world_pos, camera.world_pos);

        int is_still = 1;

        // wait till an input is detected to move the player and update the screen
        while (is_still)
        {
            check_cfi();

            is_still = 0;
            if (is_key_pressed('a'))
                player.world_pos.x--;
            else if (is_key_pressed('s'))
                player.world_pos.y++;
            else if (is_key_pressed('d'))
                player.world_pos.x++;
            else if (is_key_pressed('w'))
                player.world_pos.y--;
            else if (is_key_pressed('j'))
                camera.world_pos.x--;
            else if (is_key_pressed('k'))
                camera.world_pos.y++;
            else if (is_key_pressed('l'))
                camera.world_pos.x++;
            else if (is_key_pressed('i'))
                camera.world_pos.y--;
            else
                is_still = 1;
        }
    }
    return 0;
}