#include "raylib.h"
int main(){
  const int screenWidth = 288;
  const int screenHeight = 512;
  
  InitWindow(screenWidth,screenHeight,"flappy bird");

  Texture2D background  = LoadTexture("assets/flappy-bird-assets/sprites/background-day.png");
  Texture2D greenpipe   = LoadTexture("assets/flappy-bird-assets/sprites/pipe-green.png");
  Texture2D redbird1    = LoadTexture("assets/flappy-bird-assets/sprites/redbird-downflap.png");  
  Texture2D base        = LoadTexture("assets/flappy-bird-assets/sprites/base.png");
  Texture2D redbird2    = LoadTexture("assets/flappy-bird-assets/sprites/redbird-midflap.png"); 
  Texture2D redbird3    = LoadTexture("assets/flappy-bird-assets/sprites/redbird-upflap.png");  
  Texture2D redbird ; 

  float scrollingbase      = 0.9f;
  int  redbird_positionX   = 1;
  double redbird_positionY = 0;

  double time = GetTime();

  SetTargetFPS(60);
 
  while(!WindowShouldClose())
  {
    redbird    = redbird1;
    scrollingbase      -= 0.9f;
    redbird_positionX  = 20  ;
    redbird_positionY  += 3;

    if(scrollingbase <= -base.width*2) scrollingbase = 0;

    if(IsKeyPressed(KEY_SPACE)){

      redbird_positionY -= 50 ;
      redbird = redbird3;
    }
    
    if(redbird_positionY >= screenHeight-base.height || redbird_positionY <= 0) redbird_positionY = 100;
    

    
    BeginDrawing();
      
         ClearBackground(RAYWHITE);
         DrawTexture(background, 0 , 0 , WHITE);
         DrawTextureEx(greenpipe, (Vector2){scrollingbase+background.width,screenHeight - (greenpipe.height)}, 0.0f, 1.0f, WHITE );
         DrawTexture(redbird, redbird_positionX,redbird_positionY,WHITE);
         DrawTextureEx(base, (Vector2){ scrollingbase, screenHeight - base.height }, 0.0f, 2.0f, WHITE);
         DrawTextureEx(base, (Vector2){background.width*2 + scrollingbase ,screenHeight - base.height }, 0.0f, 2.0f, WHITE);

         

    EndDrawing();

  }
    UnloadTexture(background);
    UnloadTexture(greenpipe);
    UnloadTexture(redbird);
    UnloadTexture(base);
    CloseWindow();
    return 0;
} 


