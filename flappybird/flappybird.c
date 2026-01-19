#include"raylib.h"

#define maxpipe 100 


int main(){
  
  const int screenWidth  = 288;
  const int screenHeight = 512;
  

  InitWindow(screenWidth,screenHeight,"flappy bird");
  InitAudioDevice();
  
  Sound     die  = LoadSound("assets/flappy-bird-assets/audio/die.ogg");
  Sound     hit  = LoadSound("assets/flappy-bird-assets/audio/hit.ogg");
  Sound     point   = LoadSound("assets/flappy-bird-assets/audio/point.ogg");
  Sound     swoosh = LoadSound("assets/flappy-bird-assets/audio/swoosh.ogg");
  Sound     wing   = LoadSound("assets/flappy-bird-assets/audio/wing.ogg");

  Texture2D background = LoadTexture("assets/flappy-bird-assets/sprites/background-day.png");
  Texture2D base      = LoadTexture("assets/flappy-bird-assets/sprites/base.png");
  Texture2D pipe_green = LoadTexture("assets/flappy-bird-assets/sprites/pipe-green.png");
  Texture2D bird_downflap = LoadTexture("assets/flappy-bird-assets/sprites/redbird-downflap.png");
  Texture2D bird_midflap = LoadTexture("assets/flappy-bird-assets/sprites/redbird-midflap.png");
  Texture2D bird_upflap = LoadTexture("assets/flappy-bird-assets/sprites/redbird-upflap.png");
  Texture2D pipe_inverted = LoadTexture("assets/flappy-bird-assets/sprites/pipe-green-inverted.png");
  typedef struct bird {
    
    Texture2D spirites;
    Vector2   position;
    float     radius;

  }bird;

  typedef struct pipe_pair{
    
    Texture2D pipe;
    Texture2D pipe1;
    Rectangle top;
    Rectangle bottom;

  }pipe_pair;

  bird floppybird;
  floppybird.spirites = bird_downflap;
  floppybird.position = (Vector2){10,10};
  floppybird.radius = (bird_downflap.height+bird_downflap.width)/4.0f;

  pipe_pair pipes[maxpipe];
  int gap = 140;
  float basespeed = 0.0f;

   
  for(int i = 0 ; i < 100; i++){

    pipes[i].pipe = pipe_green;
    pipes[i].pipe1 = pipe_inverted;
    float x = (screenWidth/2) + i * gap;
    float randombottom = GetRandomValue(-80,-60); 
    float randomtop = GetRandomValue(-130,-80);
    pipes[i].bottom = (Rectangle){ x, (pipe_green.height + randombottom ), pipe_green.width, pipe_green.height};
    pipes[i].top = (Rectangle){ x ,- (pipe_green.height + randomtop), pipe_green.width, pipe_green.height };
  }

  SetTargetFPS(60);

  while(!WindowShouldClose()){
   
   floppybird.position.y += 2;  
   basespeed -= 1.5f;
   if(basespeed <= -base.width) basespeed = 0 ; 
    

   Vector2 center = (Vector2){floppybird.position.x + (bird_downflap.width)/2 ,floppybird.position.y + (bird_downflap.height)/2};
  
   if(IsKeyPressed(KEY_SPACE)){
      floppybird.spirites = bird_upflap;
      floppybird.position.y -= 50;
      PlaySound(wing);
    } 
   if(floppybird.position.y <= 0 || floppybird.position.y >= screenHeight-base.height) return 0  ;
    
    
    for(int i = 0;i< maxpipe;i++){
       if(CheckCollisionCircleRec(center , floppybird.radius,pipes[i].bottom)){
        PlaySound(hit);
        return 0 ;
      }
       if(CheckCollisionCircleRec(center , floppybird.radius,pipes[i].top)){
        PlaySound(hit);
        return 0 ;
      }
       pipes[i].bottom.x -= 1.5;
       pipes[i].top.x -= 1.5;

    }

    BeginDrawing();

      ClearBackground(RAYWHITE);
      DrawTexture(background,0,0,WHITE);

      for(int i = 0; i < maxpipe ; i++){
        
        DrawTextureEx(pipes[i].pipe,(Vector2){pipes[i].bottom.x , pipes[i].bottom.y},0,1.0f,WHITE);
        DrawTextureEx(pipes[i].pipe1,(Vector2){pipes[i].top.x , pipes[i].top.y},0,1.0f,WHITE);

     }
        DrawTexture(floppybird.spirites,floppybird.position.x,floppybird.position.y,WHITE);
        DrawTextureEx( base ,(Vector2){basespeed + base.width,screenHeight-(base.height)},0.0f,1.0f,WHITE);
        DrawTextureEx( base ,(Vector2){basespeed ,screenHeight-(base.height)},0.0f,1.0f,WHITE);
       
    EndDrawing();
  }

   CloseWindow();
  return 0 ;
}

