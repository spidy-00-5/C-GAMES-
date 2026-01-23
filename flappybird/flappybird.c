#include "raylib.h"

#define MAX_PIPE 100

typedef enum {
    STATE_WAIT_START,
    STATE_PLAY,
    STATE_GAMEOVER
} GameState;

typedef struct {
    Texture2D spirites;
    Vector2 position;
    float radius;
} Bird;

typedef struct {
    Texture2D pipe;
    Texture2D pipe1;
    Rectangle top;
    Rectangle bottom;
} PipePair;

Bird floppybird;
PipePair pipes[MAX_PIPE];
int gap = 150;
float basespeed = 0.0f;
int screenWidth = 288;
int screenHeight = 512;

Texture2D pipe_green, pipe_inverted;

void ResetGame(void) {

    floppybird.position = (Vector2){ 10, screenHeight/2 };
    floppybird.radius = 15;

    basespeed = 0;

    for (int i = 0; i < MAX_PIPE; i++) {
        pipes[i].pipe  = pipe_green;
        pipes[i].pipe1 = pipe_inverted;

        float x             = (screenWidth/2) + i * gap;
        float randombottom  = GetRandomValue(-90, -70);
        float randomtop     = GetRandomValue(-140, -90);

        pipes[i].bottom = (Rectangle){ x, (pipe_green.height + randombottom),  pipe_green.width, pipe_green.height };
        pipes[i].top    = (Rectangle){ x, -(pipe_green.height + randomtop),     pipe_green.width, pipe_green.height };
    }
}

int main() {

    InitWindow(screenWidth, screenHeight, "flappy bird");
    InitAudioDevice();

    Music  bgm   = LoadMusicStream("assets/flappy-bird-assets/audio/song.mp3");
    Sound wing   = LoadSound("assets/flappy-bird-assets/audio/wing.ogg");
    Sound hit    = LoadSound("assets/flappy-bird-assets/audio/hit.ogg");
    Sound point  = LoadSound("assets/flappy-bird-assets/audio/point.ogg");
    Sound die    = LoadSound("assets/flappy-bird-assets/audio/die.ogg");

    Texture2D background    = LoadTexture("assets/flappy-bird-assets/sprites/background-day.png");
    Texture2D base          = LoadTexture("assets/flappy-bird-assets/sprites/base.png");
    pipe_green              = LoadTexture("assets/flappy-bird-assets/sprites/pipe-green.png");
    pipe_inverted           = LoadTexture("assets/flappy-bird-assets/sprites/pipe-green-inverted.png");
    Texture2D bird_downflap  = LoadTexture("assets/flappy-bird-assets/sprites/redbird-downflap.png");
    Texture2D bird_upflap   = LoadTexture("assets/flappy-bird-assets/sprites/redbird-upflap.png");
    Texture2D gameover      = LoadTexture("assets/flappy-bird-assets/sprites/gameover.png");
    Texture2D message       = LoadTexture("assets/flappy-bird-assets/sprites/message.png");
     
    PlayMusicStream(bgm);
    GameState state = STATE_WAIT_START;
    floppybird.spirites = bird_downflap;

    ResetGame();

    Vector2 gameoverpos = (Vector2){
        (screenWidth/2) - (gameover.width)/2,
        ((screenHeight/2) - (gameover.height/2)) - 50
    };

    SetTargetFPS(60);

    while (!WindowShouldClose()) {

      
        UpdateMusicStream(bgm);

        if(state == STATE_WAIT_START){
            if(IsKeyPressed(KEY_S)){
                ResetGame();
                state = STATE_PLAY;
            }
        }

        else if(state == STATE_PLAY){

            floppybird.position.y += 2;

            if (IsKeyPressed(KEY_SPACE)) {
                floppybird.spirites = bird_upflap;
                floppybird.position.y -= 50;
                PlaySound(wing);
            }

            if (floppybird.position.y <= 0 ||
                floppybird.position.y >= screenHeight - base.height) {
                PlaySound(hit);
                PlaySound(die);
                state = STATE_GAMEOVER;
                
            }

            Vector2 center = (Vector2){
                floppybird.position.x + 15,
                floppybird.position.y + 15
            };

            for (int i = 0; i < MAX_PIPE; i++) {

                if (CheckCollisionCircleRec(center, floppybird.radius, pipes[i].bottom) ||
                    CheckCollisionCircleRec(center, floppybird.radius, pipes[i].top)) {
                    PlaySound(hit);
                    PlaySound(die);
                    state = STATE_GAMEOVER;
                }

                pipes[i].bottom.x -= 1.5;
                pipes[i].top.x    -= 1.5;
            }
        }

        else if(state == STATE_GAMEOVER) {
            if(IsKeyPressed(KEY_R)) {
                ResetGame();
                state = STATE_WAIT_START;
            }
        }

        BeginDrawing();

        if(state == STATE_WAIT_START){
            ClearBackground((Color){154,181,95,255});
            DrawTexture(message, gameoverpos.x , gameoverpos.y -50, WHITE);
            DrawText("PRESS S TO START", 30, screenHeight/2 + 120, 20, WHITE);
        }

        if(state == STATE_GAMEOVER){
            ClearBackground((Color){ 154, 181, 95, 255 });
            DrawTexture(gameover, gameoverpos.x, gameoverpos.y, WHITE);
            DrawText("PRESS R TO RESTART ",20,screenHeight/2 +120,20,RED);
        }

        if(state == STATE_PLAY){
            ClearBackground(RAYWHITE);
            DrawTexture(background,0,0,RAYWHITE);
            for (int i = 0; i < MAX_PIPE; i++) {
                DrawTextureEx(pipes[i].pipe,  (Vector2){ pipes[i].bottom.x, pipes[i].bottom.y }, 0, 1.0f, WHITE);
                DrawTextureEx(pipes[i].pipe1, (Vector2){ pipes[i].top.x,    pipes[i].top.y    }, 0, 1.0f, WHITE);
            }

            DrawTexture(floppybird.spirites, floppybird.position.x, floppybird.position.y, WHITE);
            DrawTextureEx(base, (Vector2){ basespeed + base.width, screenHeight - base.height }, 0, 1.0f, WHITE);
            DrawTextureEx(base, (Vector2){ basespeed,              screenHeight - base.height }, 0, 1.0f, WHITE);
        }

        EndDrawing();
    }
    UnloadSound(die);
    UnloadSound(hit);
    UnloadSound(point);
    UnloadSound(wing);
    UnloadMusicStream(bgm);
    UnloadTexture(background);
    UnloadTexture(pipe_green);
    UnloadTexture(pipe_inverted);
    UnloadTexture(bird_downflap);
    UnloadTexture(bird_upflap);
    UnloadTexture(gameover);
    UnloadTexture(message);
    UnloadTexture(base);
    CloseWindow();
    return 0;
}
