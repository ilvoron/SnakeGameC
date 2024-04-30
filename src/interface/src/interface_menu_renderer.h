#ifndef INTERFACE_MENU_RENDERER_H
#define INTERFACE_MENU_RENDERER_H

enum MENU_ACTION {
	MA_PREV = -1,
	MA_NEXT = 1
};
void render_menu();
void select_item();
void change_select(enum MENU_ACTION action);

#endif