#ifndef INTERFACE_INGAME_RENDERER_H
#define INTERFACE_INGAME_RENDERER_H
#include "global.h"

extern bool isMapInit;

void render_frame_cbased(struct Board* board);
void render_frame_dynamic(struct Board* board);
void render_pause();

#endif