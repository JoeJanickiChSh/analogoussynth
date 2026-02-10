#pragma once
#include <SDL2/SDL.h>
#include <stdbool.h>
#include "animation.h"

typedef struct as_GuiAnimations
{
	as_Animation* background;
	as_Animation* key; /** Keyboard keys **/
	as_Animation* knob; /** Knobs **/
	as_Animation* jack; /** Jacks **/
	as_Animation* font;
} as_GuiAnimation;


typedef enum as_GuiNodeType {
	AS_GUI_KNOB, AS_GUI_TEXT, AS_GUI_JACK
} as_GuiNodeType;

typedef struct as_GuiKnob {
	int x;
	int y;
	float* value;
	bool selected;
} as_GuiKnob;

typedef struct as_GuiText {
	int x;
	int y;
	const char* str;
	size_t len;
} as_GuiText;

typedef struct as_GuiJack {
	int x;
	int y;
	int color;
} as_GuiJack;

typedef union as_GuiObject {
	as_GuiKnob knob;
	as_GuiText text;
	as_GuiJack jack;
} as_GuiObject;

typedef struct as_GuiNode {
	struct as_GuiNode* next;
	as_GuiNodeType type;
	as_GuiObject obj;
} as_GuiNode;

typedef struct as_Gui {
	as_GuiNode* head;
	as_GuiAnimation anim;
	bool prevmousedown;
	int prevmousex;
	int prevmousey;
} as_Gui;

bool as_guiinit(as_Gui* gui, int colorkey);

void as_guiaddknob(as_Gui* gui, int x, int y, float* value);

void as_guiaddtext(as_Gui* gui, int x, int y, const char* str);

void as_guiaddjack(as_Gui* gui, int x, int y, int color);

as_GuiNode* as_guiaddnode(as_Gui* gui, as_GuiNodeType type);

void as_guifree(as_Gui* gui);

void as_guidraw(as_Gui* gui, SDL_Surface* surface, bool mousedown, int mousex, int mousey);
