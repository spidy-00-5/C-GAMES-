#include"raylib.h"

#define maxpipe 100 


int main(){
  
  const int screenWidth  = 288;
  const int screenHeight = 512;
  

  InitWindow(screenWidth,screenHeight,"flappy bird");

  Texture2D background = LoadTexture("flappybird/asserts/flappy-bird-assets/sprites/background-day.png");
  Texture2D base      = LoadTexture("flappybird/asserts/flappy-bird-assets/sprites/base.png");
  Texture2D pipe_green = LoadTexture("flappybird/asserts/flappy-bird-assets/sprites/pipe_green.png");
  Texture2D bird_downflap = LoadTexture("flappybird/asserts/flappy-bird-assets/sprites/redbird-downflap.png");
  Texture2D bird_midflap = LoadTexture("flappybird/asserts/flappy-bird-assets/sprites/redbird-midflap.png");
  Texture2D bird_upflap = LoadTexture("flappybird/asserts/flappy-bird-assets/sprites/redbird-upflap.png");

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
  floppybird.radius = (bird_downflap.height+bird_downflap.width)/6.0f;

  pipe_pair pipes[maxpipe];
  int gap = 120;
  float basespeed = 0.0f;
  Vector2 center = (Vector2){floppybird.position.x + (floppybird.spirites.width)/2 ,floppybird.position.y + (floppybird.spirites.height)/2};

   
  for(int i = 0 ; i < 100; i++){

    pipes[i].pipe = pipe_green;
    pipes[i].bottom = (Rectangle){(screenWidth/2)+i*gap,screenHeight - pipe_green.height + GetRandomValue(-60,10)};
    pipes[i].top =(Rectangle){0+i*gap , pipe_green.height+GetRandomValue(0,20)}; 

  }

  SetTargetFPS(60);

  while(!WindowShouldClose()){

   basespeed -= 1.5f;
   if(basespeed <= -base.width) basespeed = 0 ; 
   
   if(IsKeyPressed(KEY_SPACE)){
      floppybird.spirites = bird_upflap;
      floppybird.position.y += 5;
    } 
   if(floppybird.position.y <= 0 || floppybird.position.y >= screenHeight-base.height) return 0  ;
    
    
    for(int i = 0;i< 100;i++){
       if(CheckCollisionCircleRec(center , floppybird.radius,pipes[i].top)) return 0 ;
       if(CheckCollisionCircleRec(center , floppybird.radius,pipes[i].bottom)) return 0 ;
    }

    BeginDrawing();

      ClearBackground(RAYWHITE);
      DrawTexture(background,0,0,WHITE);

      for(int i = 0; i < 100 ; i++){

        //DrawTextpro();
        DrawTextureEx(pipes[i].pipe,(Vector2){pipes[i].bottom.x,pipes[i].bottom.y},0.0f,0.0f,WHITE);

     }
      
      DrawTexture(floppybird.spirites,floppybird.position.x,floppybird.position.y,WHITE);
      DrawTextureEx( base ,(Vector2){basespeed + base.width,screenHeight-base.height},0.0f,0.2f,WHITE);
      DrawTextureEx( base ,(Vector2){basespeed ,screenHeight-base.height},0.0f,0.2f,WHITE);
     
  }

   CloseWindow();
  return 0 ;
}

