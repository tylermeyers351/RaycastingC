#include <SDL2/SDL.h>
#include <stdio.h>
#include "./constants.h"

int game_is_running = FALSE;
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

int last_frame_time = 0;

struct ball 
{
    float x;
    float y;
    float width;
    float height;
} ball;

int initialize_window(void)
{
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        fprintf(stderr, "SDL_Init failed: %s\n", SDL_GetError());
        return FALSE;
    }

    window = SDL_CreateWindow(
        NULL, 
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        SDL_WINDOW_BORDERLESS    
    );
    if (!window)
    {
        fprintf(stderr, "Error creating SDL Window.\n");
        return FALSE;
    }

    renderer = SDL_CreateRenderer(window, -1, 0);
    if (!renderer)
    {
        fprintf(stderr, "Error creating SDL Renderer.\n");
        return FALSE;
    }

    return TRUE;
}

void process_input()
{
    SDL_Event event;
    SDL_PollEvent(&event);

    switch (event.type)
    {
        case SDL_QUIT:
            game_is_running = FALSE;
            break;
        case SDL_KEYDOWN:
            if (event.key.keysym.sym == SDLK_ESCAPE)
                game_is_running = FALSE;
            break;
    }
}

void setup()
{
    ball.x = 20;
    ball.y = 20;
    ball.width = 15;
    ball.height = 15;
}

void update()
{
    // Waste time until we reach the frame target time (using a while loop will take a lot of CPU processing power)
    // while(!SDL_TICKS_PASSED(SDL_GetTicks(), last_frame_time + FRAME_TARGET_TIME));

    // Caps frame rate (remove the next few lines if you don't want to cap)
    int time_to_wait = FRAME_TARGET_TIME - (SDL_GetTicks() - last_frame_time);
  
    if (time_to_wait > 0 && time_to_wait <= FRAME_TARGET_TIME)
    {  
        SDL_Delay(time_to_wait);
    }

    // Get a delta time factor converted to seconds to be used to update my objects later
    float dt = (SDL_GetTicks() - last_frame_time) / 1000.0f;

    last_frame_time = SDL_GetTicks();

    ball.x += 70 * dt;
    ball.y += 50 * dt;
}

void render()
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // TODO: Here is where we start drawing our game objects
    SDL_Rect ball_rect = 
    {
        (int)ball.x, 
        (int)ball.y, 
        (int)ball.width, 
        (int)ball.height
    };

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &ball_rect);

    SDL_RenderPresent(renderer);
}

void destroy_window()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

int SDL_main(int argc, char* argv[])
{
    game_is_running = initialize_window();

    setup();

    while(game_is_running) 
    {
        process_input();
        update();
        render();
    }

    destroy_window();

    return 0;
}