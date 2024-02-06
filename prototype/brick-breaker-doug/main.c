#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define BRICK_ROWS 4
#define BRICK_COLUMNS 10
#define BRICK_WIDTH 60
#define BRICK_HEIGHT 20
#define PADDLE_WIDTH 100
#define PADDLE_HEIGHT 20
#define BALL_RADIUS 10

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
SDL_Rect paddle;
SDL_Rect ball;
SDL_Rect bricks[BRICK_ROWS][BRICK_COLUMNS];
int ball_velocity_x = 3;
int ball_velocity_y = -3;
bool running = true;

void initialize() {
    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow("Brick Breaker", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    paddle.x = (SCREEN_WIDTH - PADDLE_WIDTH) / 2;
    paddle.y = SCREEN_HEIGHT - PADDLE_HEIGHT;
    paddle.w = PADDLE_WIDTH;
    paddle.h = PADDLE_HEIGHT;

    ball.x = SCREEN_WIDTH / 2;
    ball.y = SCREEN_HEIGHT / 2;
    ball.w = BALL_RADIUS * 2;
    ball.h = BALL_RADIUS * 2;

    // Generate bricks
    int brick_offset_x = (SCREEN_WIDTH - (BRICK_COLUMNS * BRICK_WIDTH)) / 2;
    int brick_offset_y = 50;
    for (int i = 0; i < BRICK_ROWS; i++) {
        for (int j = 0; j < BRICK_COLUMNS; j++) {
            bricks[i][j].x = brick_offset_x + j * BRICK_WIDTH;
            bricks[i][j].y = brick_offset_y + i * BRICK_HEIGHT;
            bricks[i][j].w = BRICK_WIDTH;
            bricks[i][j].h = BRICK_HEIGHT;
        }
    }
}

void handle_input() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            running = false;
        }
    }

    const Uint8* keystate = SDL_GetKeyboardState(NULL);
    if (keystate[SDL_SCANCODE_LEFT] && paddle.x > 0) {
        paddle.x -= 5;
    }
    if (keystate[SDL_SCANCODE_RIGHT] && paddle.x < SCREEN_WIDTH - paddle.w) {
        paddle.x += 5;
    }
}

bool check_collision(SDL_Rect a, SDL_Rect b) {
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    leftA = a.x;
    rightA = a.x + a.w;
    topA = a.y;
    bottomA = a.y + a.h;

    leftB = b.x;
    rightB = b.x + b.w;
    topB = b.y;
    bottomB = b.y + b.h;

    if (bottomA <= topB || topA >= bottomB || rightA <= leftB || leftA >= rightB) {
        return false;
    }

    return true;
}

void update() {
    ball.x += ball_velocity_x;
    ball.y += ball_velocity_y;

    // Collision with walls
    if (ball.x <= 0 || ball.x >= SCREEN_WIDTH - ball.w) {
        ball_velocity_x = -ball_velocity_x;
    }
    if (ball.y <= 0) {
        ball_velocity_y = -ball_velocity_y;
    }

    // Collision with paddle
    if (check_collision(ball, paddle)) {
        ball_velocity_y = -ball_velocity_y;
    }

    // Collision with bricks
    for (int i = 0; i < BRICK_ROWS; i++) {
        for (int j = 0; j < BRICK_COLUMNS; j++) {
            if (check_collision(ball, bricks[i][j])) {
                bricks[i][j].x = -1000; // Hide the brick
                ball_velocity_y = -ball_velocity_y;
            }
        }
    }

    // Game over
    if (ball.y >= SCREEN_HEIGHT) {
        running = false;
    }
}

void render() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &paddle);

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, &ball);

    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    for (int i = 0; i < BRICK_ROWS; i++) {
        for (int j = 0; j < BRICK_COLUMNS; j++) {
            SDL_RenderFillRect(renderer, &bricks[i][j]);
        }
    }

    SDL_RenderPresent(renderer);
}

void cleanup() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

int main() {
    initialize();

    while (running) {
        handle_input();
        update();
        render();
        SDL_Delay(10);
    }

    cleanup();
    return 0;
}

