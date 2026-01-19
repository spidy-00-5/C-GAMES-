#include "raylib.h"

#define MAX_PIPE 100

int main() {

    const int screenWidth  = 288;
    const int screenHeight = 512;

    InitWindow(screenWidth, screenHeight, "flappy bird");
    InitAudioDevice();

    Sound die    = LoadSound("assets/flappy-bird-assets/audio/die.ogg");
    Sound hit    = LoadSound("assets/flappy-bird-assets/audio/hit.ogg");
    Sound point  = LoadSound("assets/flappy-bird-assets/audio/point.ogg");
    Sound swoosh = LoadSound("assets/flappy-bird-assets/audio/swoosh.ogg");
    Sound wing   = LoadSound("assets/flappy-bird-assets/audio/wing.ogg");
    Music song   = LoadMusicStream("assets/flappy-bird-assets/audio/song.mp4");

    Texture2D background    = LoadTexture("assets/flappy-bird-assets/sprites/background-day.png");
    Texture2D base          = LoadTexture("assets/flappy-bird-assets/sprites/base.png");
    Texture2D pipe_green    = LoadTexture("assets/flappy-bird-assets/sprites/pipe-green.png");
    Texture2D bird_downflap = LoadTexture("assets/flappy-bird-assets/sprites/redbird-downflap.png");
    Texture2D bird_midflap  = LoadTexture("assets/flappy-bird-assets/sprites/redbird-midflap.png");
    Texture2D bird_upflap   = LoadTexture("assets/flappy-bird-assets/sprites/redbird-upflap.png");
    Texture2D pipe_inverted = LoadTexture("assets/flappy-bird-assets/sprites/pipe-green-inverted.png");
    Texture2D gameover      = LoadTexture("assets/flappy-bird-assets/sprites/gameover.png");
    Texture2D message       = LoadTexture("assets/flappy-bird-assets/sprites/message.png");

    typedef struct bird {
        Texture2D spirites;
        Vector2   position;
        float     radius;
    } bird;

    typedef struct pipe_pair {
        Texture2D pipe;
        Texture2D pipe1;
        Rectangle top;
        Rectangle bottom;
    } pipe_pair;

    bird floppybird;
    floppybird.spirites = bird_downflap;
    floppybird.position = (Vector2){ 10, screenHeight/2 };
    floppybird.radius   = (bird_downflap.height + bird_downflap.width) / 4.0f;

    pipe_pair pipes[MAX_PIPE];
    int   gap       = 150;
    float basespeed = 0.0f;
    bool  gameend   = false;
    bool  pause     = false;

    Vector2 gameoverpos = (Vector2){
        (screenWidth/2) - (gameover.width)/2,
        ((screenHeight/2) - (gameover.height/2)) - 50
    };

    for (int i = 0; i < MAX_PIPE; i++) {
        pipes[i].pipe  = pipe_green;
        pipes[i].pipe1 = pipe_inverted;

        float x             = (screenWidth/2) + i * gap;
        float randombottom  = GetRandomValue(-90, -70);
        float randomtop     = GetRandomValue(-140, -90);

        pipes[i].bottom = (Rectangle){ x, (pipe_green.height + randombottom),  pipe_green.width, pipe_green.height };
        pipes[i].top    = (Rectangle){ x, -(pipe_green.height + randomtop),     pipe_green.width, pipe_green.height };
    }

    SetTargetFPS(60);
    PlayMusicStream(song);

    while (!WindowShouldClose()) {

        if (!gameend) {

            if (IsKeyPressed('p')) pause = !pause;

            if (!pause) {

                UpdateMusicStream(song);

                floppybird.position.y += 2;
                basespeed -= 1.5f;
                if (basespeed <= -base.width) basespeed = 0;

                Vector2 center = (Vector2){
                    floppybird.position.x + (bird_downflap.width/2),
                    floppybird.position.y + (bird_downflap.height/2)
                };

                if (IsKeyPressed(KEY_SPACE)) {
                    floppybird.spirites = bird_upflap;
                    floppybird.position.y -= 50;
                    PlaySound(wing);
                }

                if (floppybird.position.y <= 0 ||
                    floppybird.position.y >= screenHeight - base.height) {
                    return 0;
                }

                for (int i = 0; i < MAX_PIPE; i++) {

                    if (CheckCollisionCircleRec(center, floppybird.radius, pipes[i].bottom)) {
                        PlaySound(hit);
                        gameend = true;
                    }

                    if (CheckCollisionCircleRec(center, floppybird.radius, pipes[i].top)) {
                        PlaySound(hit);
                        gameend = true;
                    }

                    pipes[i].bottom.x -= 1.5;
                    pipes[i].top.x    -= 1.5;
                }
            }
        }

        BeginDrawing();

        ClearBackground(RAYWHITE);
        DrawTexture(background, 0, 0, WHITE);

      
        if (gameend)DrawTexture(gameover, gameoverpos.x, gameoverpos.y, WHITE);

        for (int i = 0; i < MAX_PIPE; i++) {
            DrawTextureEx(pipes[i].pipe,  (Vector2){ pipes[i].bottom.x, pipes[i].bottom.y }, 0, 1.0f, WHITE);
            DrawTextureEx(pipes[i].pipe1, (Vector2){ pipes[i].top.x,    pipes[i].top.y    }, 0, 1.0f, WHITE);
        }

        DrawTexture(message, gameoverpos.x, gameoverpos.y, WHITE);
        DrawTexture(floppybird.spirites, floppybird.position.x, floppybird.position.y, WHITE);

        DrawTextureEx(base, (Vector2){ basespeed + base.width, screenHeight - base.height }, 0, 1.0f, WHITE);
        DrawTextureEx(base, (Vector2){ basespeed,              screenHeight - base.height }, 0, 1.0f, WHITE);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
