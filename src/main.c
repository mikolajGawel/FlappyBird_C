#include "defs.h"
void init_window()
{
    InitWindow(WIDTH,HEIGHT,"Ugly Bird [ C ]");
    SetTargetFPS(60);
    HideCursor();
    Image icon = LoadImage("rsc/icon.png");
    SetWindowIcon(icon);
    UnloadImage(icon);
}
void init_player()
{
    Image img = LoadImage("rsc/bird.png");
   
    main_player.width = 75;
    main_player.height = 75;
    main_player.tex2D = LoadTextureFromImage(img);
    UnloadImage(img);
    main_player.tex2D.width = main_player.width;
    main_player.tex2D.height = main_player.height;
    main_player.x = (WIDTH-main_player.width)/2;
    main_player.y = (HEIGHT-main_player.height)/2;
}
void init_pipes()
{
    Image pipe_texture = LoadImage("rsc/pipe.png");
    for(int i = 0;i< PIPES_COUNT;i++)
    {
        pipes[i].tex2D = LoadTextureFromImage(pipe_texture);
        pipes[i].x = WIDTH + DISTANCE_OF_PIPES * i;
        if(i%2 == 0)
        {
            pipes[i].y = 0;
        }else
        {
            pipes[i].y = HEIGHT - pipes[i].tex2D.height;
        }

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
void take_input()
{
    if(IsKeyDown(KEY_SPACE))
    {
        main_player.y -=6;
    }else
    {
        main_player.y+=3;
    }
}
void death()
{
    in_game = false;
    init_player();
    init_pipes();
}
void check_collision()
{
    if(HEIGHT <= main_player.y || main_player.y + main_player.tex2D.height < 0)
    {
        death();
    }
    for(int i = 0;i < PIPES_COUNT;i++)
    {
        Rectangle _player = (Rectangle){main_player.x,main_player.y,main_player.width,main_player.height};
        Rectangle _pipe = (Rectangle){pipes[i].x,pipes[i].y,pipes[i].tex2D.width,pipes[i].tex2D.height};

        if(CheckCollisionRecs(_player,_pipe))
        {
            death();
            break;
        }
    }
}
int main()
{
    init_window();
    init_player();
    init_pipes();

    while(!WindowShouldClose())
    {
        if(in_game == true)
        {
            take_input();
            move_pipes();
            check_collision();
            BeginDrawing();
                ClearBackground((Color){255,255,255,0});
                draw_pipes();
                DrawTexture(main_player.tex2D,main_player.x,main_player.y,WHITE);
            EndDrawing();
        }else
        {
            BeginDrawing();
            ClearBackground(WHITE);
                DrawText("Ugly Bird",WIDTH/2,HEIGHT/2,25,BLACK);
                DrawText("Press Space To Start",WIDTH/2-50,HEIGHT/2+50,25,BLACK);
                if(IsKeyPressed(KEY_SPACE))
                    in_game = true;
            EndDrawing();
        }
       
    }
    unload_textures();
}