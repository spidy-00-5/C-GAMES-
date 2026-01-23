this /these games are made in "C" using frame work called "ray lib";

how to run on macOS || similar in linux also 

first clone then 

for macOs 

 gcc ".c file " -o "file name " \                                                                                    ─╯
  -I/opt/homebrew/include \
  -L/opt/homebrew/lib \
  -lraylib \
  -framework Cocoa \
  -framework IOKit \
  -framework CoreVideo \
  -framework OpenGL \
  -framework AudioToolbox \
  -framework CoreAudio

for example :

 gcc flappybird.c -o flappybird \                                                                                    ─╯
  -I/opt/homebrew/include \
  -L/opt/homebrew/lib \
  -lraylib \
  -framework Cocoa \
  -framework IOKit \
  -framework CoreVideo \
  -framework OpenGL \
  -framework AudioToolbox \
  -framework CoreAudio
