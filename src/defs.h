#define WIDTH 640
#define HEIGHT 480
#define DISTANCE_OF_PIPES 200
#define PIPES_COUNT 6
#include "structs.h"
#include <stdlib.h>
#include <raylib.h>
bool in_game = false;

struct player main_player;
struct pipe pipes[PIPES_COUNT];