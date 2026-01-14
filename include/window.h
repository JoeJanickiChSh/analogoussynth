#pragma once
#include <stdbool.h>
#include <SDL2/SDL.h>

#define WINDOW_FRAMERATE 30
#define WINDOW_TITLE "Analogous"
#define WINDOW_WIDTH_DEFAULT 800
#define WINDOW_HEIGHT_DEFAULT 600

/**
* @struct as_Window
* @brief Stores data for managing the application's window.
*/
typedef struct as_Window
{
	bool isopen; /** Stores whether or not the window is currently open.*/
	SDL_Window* sdlwindow; /** The SDL window object */
	SDL_Surface* surface; /** The window's rendering surface */
} as_Window;

/**
* @brief Initializes the window.
*
* @param window  pointer to the window structure.
*
* @return false on success
* @return true on failure
*/
bool as_windowinit(as_Window* window);

/**
* @brief Updates the window, including rendering and events.
*
* @param window  pointer to the window structure.
* @param keyboard  pointer to the keyboard state.
*/
void as_windowupdate(as_Window* window, bool* keyboard);

/**
* @brief closes the window, freeing all allocated memory.
*
* @param window  pointer to the window structure.
*/
void as_windowclose(as_Window* window);
