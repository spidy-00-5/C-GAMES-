#include"raylib.h"

#define maxpipe 100 


int main(){
  
  const int screenWidth  = 288;
  const int screenHeight = 512;
  

  InitWindow(screenWidth,screenHeight,"flappy bird");

  Texture2D background = LoadTexture("assets/flappy-bird-assets/sprites/background-day.png");
  Texture2D base      = LoadTexture("assets/flappy-bird-assets/sprites/base.png");
  Texture2D pipe_green = LoadTexture("assets/flappy-bird-assets/sprites/pipe-green.png");
  Texture2D bird_downflap = LoadTexture("assets/flappy-bird-assets/sprites/redbird-downflap.png");
  Texture2D bird_midflap = LoadTexture("assets/flappy-bird-assets/sprites/redbird-midflap.png");
  Texture2D bird_upflap = LoadTexture("assets/flappy-bird-assets/sprites/redbird-upflap.png");

  typedef struct bird {
    
    Texture2D spirites;
    Vector2   position;
    float     radius;

  }bird;

  typedef struct pipe_pair{
    
    Texture2D pipe;
    Rectangle top;
    Rectangle bottom;

  }pipe_pair;

  bird floppybird;
  floppybird.spirites = bird_downflap;
  floppybird.position = (Vector2){1,1};
  floppybird.radius = (bird_downflap.height+bird_downflap.width)/4.0f;

  pipe_pair pipes[maxpipe];
  int gap = 140;
  float basespeed = 0.0f;

   
  for(int i = 0 ; i < 100; i++){

    pipes[i].pipe = pipe_green;
    float x = (screenWidth/2) + i * gap;
    float random = GetRandomValue(-120,-20); 
    pipes[i].bottom = (Rectangle){ x, (pipe_green.height + random ), pipe_green.width, pipe_green.height};
    pipes[i].top = (Rectangle){ x ,-(pipe_green.height + random+20), pipe_green.width, pipe_green.height };
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
    } 
   if(floppybird.position.y <= 0 || floppybird.position.y >= screenHeight-base.height) return 0  ;
    
    
    for(int i = 0;i< 100;i++){
       if(CheckCollisionCircleRec(center , floppybird.radius,pipes[i].bottom)) return 0 ;
       pipes[i].bottom.x -= 1.5;
       pipes[i].top.x -= 1.5;

    }

    BeginDrawing();

      ClearBackground(RAYWHITE);
      DrawTexture(background,0,0,WHITE);

      for(int i = 0; i < maxpipe ; i++){
      

      
        DrawTextureEx(pipes[i].pipe,(Vector2){pipes[i].bottom.x , pipes[i].bottom.y},0,1.0f,WHITE);
        DrawRectangleLines( pipes[i].bottom.x, pipes[i].bottom.y, pipes[i].bottom.width, pipes[i].bottom.height,RED);
        DrawRectangleLines( pipes[i].top.x, pipes[i].top.y, pipes[i].top.width, pipes[i].top.height,RED);

     }
        DrawTexture(floppybird.spirites,floppybird.position.x,floppybird.position.y,WHITE);
        DrawTextureEx( base ,(Vector2){basespeed + base.width,screenHeight-(base.height)},0.0f,1.0f,WHITE);
        DrawTextureEx( base ,(Vector2){basespeed ,screenHeight-(base.height)},0.0f,1.0f,WHITE);
       
    EndDrawing();
  }

   CloseWindow();
  return 0 ;
}

