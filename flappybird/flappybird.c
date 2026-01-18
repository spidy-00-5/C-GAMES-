#include "raylib.h"
int main(){
  const int screenWidth = 288;
  const int screenHeight = 512;
 


  typedef struct Floppy {
    Vector2 position;
    Texture2D floppybird;
    int radius;

  } Floppy;

  typedef struct Tube {
    Rectangle rec;
    Texture2D pipe;

  } Tube ;
   

  InitWindow(screenWidth,screenHeight,"flappy bird");

  Texture2D background  = LoadTexture("assets/flappy-bird-assets/sprites/background-day.png");
  Texture2D greenpipe   = LoadTexture("assets/flappy-bird-assets/sprites/pipe-green.png");
  Texture2D redbird1    = LoadTexture("assets/flappy-bird-assets/sprites/redbird-downflap.png");  
  Texture2D base        = LoadTexture("assets/flappy-bird-assets/sprites/base.png");
  Texture2D redbird2    = LoadTexture("assets/flappy-bird-assets/sprites/redbird-midflap.png"); 
  Texture2D redbird3    = LoadTexture("assets/flappy-bird-assets/sprites/redbird-upflap.png");  
  Texture2D redbird ;
 
  static Floppy floppy ;
  floppy.floppybird  = redbird1;
  floppy.position.x  = 1;
  floppy.position.y  = 0;
  floppy.radius      = redbird1.width/3; 

  static Tube tube;
  tube.pipe = greenpipe;
  tube.rec  = (Rectangle){ screenWidth/2,screenHeight-(greenpipe.height),greenpipe.width,greenpipe.height};
  
  tube.rec.x = 0;
 
  double time = GetTime();
  SetTargetFPS(60);
 
  while(!WindowShouldClose())
  {
    tube.rec.x  -= 0.9f;
    floppy.position.y  += 2;

    if(tube.rec.x <= -base.width) tube.rec.x = 0;

    if(IsKeyPressed(KEY_SPACE)){
      floppy.position.y -= 50 ;

      }
    
    if(floppy.position.y >= screenHeight-base.height || floppy.position.y <= 0) floppy.position.y = 100;

    
    BeginDrawing();  
         ClearBackground(RAYWHITE);
         DrawTexture(background, 0 , 0 , WHITE);

         DrawTextureEx(tube.pipe, (Vector2){ (tube.rec.x)+screenHeight,tube.rec.y}, 0.0f, 1.0f, WHITE );

         DrawTextureEx(tube.pipe, (Vector2){( tube.rec.x)+screenWidth , (tube.rec.y)}, 180.0f, 1.0f, WHITE );

         DrawTexture(floppy.floppybird, floppy.position.x,floppy.position.y,WHITE);

         DrawTextureEx(base, (Vector2){ tube.rec.x, screenHeight - base.height }, 0.0f, 2.0f, WHITE);

         DrawTextureEx(base, (Vector2){ screenWidth + tube.rec.x ,screenHeight - base.height }, 0.0f, 2.0f, WHITE);

    EndDrawing();
     Vector2 center = (Vector2){ floppy.position.x + redbird1.width/2, floppy.position.y + redbird1.height/2 };
    if( CheckCollisionCircleRec(center, floppy.radius, tube.rec)) return 0;
  }
    UnloadTexture(background);
    UnloadTexture(greenpipe);
    UnloadTexture(redbird);
    UnloadTexture(base);
    CloseWindow();
    return 0;
} 


