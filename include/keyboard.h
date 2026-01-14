#pragma once
#include <stdbool.h>

#define KB_NUM_KEYS 24


/**
* @brief Allocate and initialize memory for keyboard state.
* Memory must be manually freed.
*
* @return pointer to keyboard state
*/
bool* as_keyalloc();
