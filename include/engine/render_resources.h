#include "raylib.h"

namespace engine
{

struct RenderContext
{
    Shader skewShader;

    int mouseLoc;
    int hoveringLoc;
    int scaleLoc;
    int screenSizeLoc;
};
 
}