#include "keyboard.h"
#include "stdlib.h"

bool* as_keyalloc()
{
	bool* keys = malloc(KB_NUM_KEYS * sizeof(bool));
	for (bool* key = keys; key < keys + KB_NUM_KEYS; key++)
	{
		*key = false;
	}
	return keys;
}

