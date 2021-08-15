#include "defs.h"

void init_player()
{
    Image img = LoadImage("rsc/bird.png");
    main_player.x = 50;
    main_player.y = 50;
    main_player.width = 75;
    main_player.height = 75;
    main_player.tex2D = LoadTextureFromImage(img);
    UnloadImage(img);
    main_player.tex2D.width = main_player.width;
    main_player.tex2D.height = main_player.height;
}
void init_pipes()
{
    Image pipe_texture = LoadImage("rsc/pipe.png");
    for(int i = 0;i< PIPES_COUNT;i++)
    {
        pipes[i].tex2D = LoadTextureFromImage(pipe_texture);
        pipes[i].x = WIDTH + pipes[i].tex2D.width + DISTANCE_OF_PIPES + 100* i;
        pipes[i].y = 0;

    }
    UnloadImage(pipe_texture);
}
void draw_pipes()
{
    for(int i = 0;i< PIPES_COUNT;i++)
    {
        DrawTexture(pipes[i].tex2D,pipes[i].x,pipes[i].y,WHITE);
    }
}
void move_pipes()
{
    for(int i = 0;i < PIPES_COUNT;i++)
    {
        if(pipes[i].x < -pipes[i].tex2D.width)
        {
            pipes[i].x = WIDTH + pipes[i].tex2D.width;
        }else
        {
            pipes[i].x -= 3;
        }
    }
}
void unload_textures()
{
    for(int i = 0;i < PIPES_COUNT;i++)
        UnloadTexture(pipes[i].tex2D);
    UnloadTexture(main_player.tex2D);
}
void takeInput()
{
    if(IsKeyDown(KEY_SPACE))
    {
        main_player.y -=2;
    }else
    {
        main_player.y++;
    }
}
int main()
{
    InitWindow(WIDTH,HEIGHT,"[ C ] Ugly Bird");
    SetTargetFPS(60);

    init_player();
    init_pipes();

    while(!WindowShouldClose())
    {
        takeInput();
        move_pipes();
        BeginDrawing();
            ClearBackground((Color){255,255,255,0});
            draw_pipes();
            DrawTexture(main_player.tex2D,main_player.x,main_player.y,WHITE);
        EndDrawing();
    }
    unload_textures();
}