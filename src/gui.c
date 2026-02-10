#include "gui.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

bool as_guiinit(as_Gui* gui, int colorkey)
{
	gui->anim.key = as_animationnew("assets/keys.bmp", 32, 64, colorkey);
	gui->anim.knob = as_animationnew("assets/knob.bmp", 64, 64, colorkey);
	gui->anim.background = as_animationnew("assets/background.bmp", 800, 600, colorkey);
	gui->anim.font = as_animationnew("assets/font.bmp", 16, 16, colorkey);
	gui->prevmousedown = false;
	gui->prevmousex = 0;
	gui->prevmousey = 0;
	gui->head = NULL;
	return !(gui->anim.key && gui->anim.knob);
}

as_GuiNode* as_guiaddnode(as_Gui* gui, as_GuiNodeType type)
{
	as_GuiNode* new_node = malloc(sizeof(as_GuiNode));
	new_node->type = type;
	new_node->next = gui->head;
	gui->head = new_node;
	return new_node;
}

void as_guiaddknob(as_Gui* gui, int x, int y, float* value)
{
	as_GuiNode* nd = as_guiaddnode(gui, AS_GUI_KNOB);
	nd->obj.knob.x = x;
	nd->obj.knob.y = y;
	nd->obj.knob.value = value;
	nd->obj.knob.selected = false;
}

void as_guiaddtext(as_Gui* gui, int x, int y, const char* str)
{
	as_GuiNode* nd = as_guiaddnode(gui, AS_GUI_TEXT);
	nd->obj.text.x = x;
	nd->obj.text.y = y;
	nd->obj.text.str = str;
	nd->obj.text.len = strlen(str);
}

void as_guifree(as_Gui* gui)
{
	as_GuiNode* nd = gui->head;
	while (nd)
	{
		as_GuiNode* next = nd->next;
		free(nd);
		nd = next;
	}
	gui->head = NULL;
	as_animationfree(gui->anim.key);
	as_animationfree(gui->anim.knob);
	as_animationfree(gui->anim.font);
	as_animationfree(gui->anim.background);
}


void as_guidraw(as_Gui* gui, SDL_Surface* surface, bool mousedown, int mousex, int mousey)
{
	int relx = mousex - gui->prevmousex;
	int rely = mousey - gui->prevmousey;
	bool mousepressed = mousedown && (!gui->prevmousedown);
	as_animationdraw(gui->anim.background, 0, 0, 0, 0, surface);
	for (as_GuiNode* nd = gui->head; nd; nd = nd->next)
	{
		switch (nd->type)
		{
		case AS_GUI_KNOB:
			as_animationdraw(gui->anim.knob, nd->obj.knob.x, nd->obj.knob.y, 0, (*nd->obj.knob.value)*31, surface);
			if (mousepressed && (mousex >= nd->obj.knob.x) && (mousey >= nd->obj.knob.y) && 
					(mousex < nd->obj.knob.x + gui->anim.knob->width) && (mousey < nd->obj.knob.y + gui->anim.knob->height))
			{
				nd->obj.knob.selected = true;
			}
			if (!mousedown)
			{
				nd->obj.knob.selected = false;
			}

			if (nd->obj.knob.selected)
			{
				*nd->obj.knob.value -= rely * 0.005f;
			}
			if (*nd->obj.knob.value < 0.0f)
				*nd->obj.knob.value = 0.0f;
			if (*nd->obj.knob.value > 1.0f)
				*nd->obj.knob.value = 1.0f;
			break;
		case AS_GUI_TEXT:
			for (size_t i = 0; i < nd->obj.text.len; i++)
			{
				if (nd->obj.text.str[i] >= 'A' && nd->obj.text.str[i] <= 'Z')
					as_animationdraw(gui->anim.font, i * gui->anim.font->width + nd->obj.text.x, nd->obj.text.y, 0, nd->obj.text.str[i] - 'A', surface);
			}
			break;
		}
	}
	gui->prevmousedown = mousedown;
	gui->prevmousex = mousex;
	gui->prevmousey = mousey;
}
