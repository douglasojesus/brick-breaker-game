#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <intelfpgaup/video.h>

// Definições de constantes para as dimensões da tela, dos tijolos, do jogador (RAQUETE) e da bola
#define SCREEN_WIDTH 319 //Largura
#define SCREEN_HEIGHT 239 //Altura
#define BRICK_ROWS 4
#define BRICK_COLUMNS 10
#define BRICK_WIDTH 60
#define BRICK_HEIGHT 20

#define BALL_RADIUS 10

typedef struct plataforma{
    int x, y; 
    int x2 = x + 40;
    int y2 = y - 20;
} Plataforma;

typedef struct bola{
    int x, y;
    int x2 = x + 2;
    int y2 = y - 2;
} Bola;

// Variáveis globais para a janela, o renderizador, os retângulos representando o jogador, a bola e os tijolos, e velocidades da bola
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
Plataforma raquete;
SDL_Rect ball;
SDL_Rect bricks[BRICK_ROWS][BRICK_COLUMNS];
int ball_velocity_x = 3;
int ball_velocity_y = -3;
bool running = true;

int * colunas;
int * linhas;
int * tcolunas;
int * tlinhas;

// Função de inicialização do jogo
void initialize() {
    // Inicializa o vídeo
    if (video_open()){
        // Faz leitura do dispositivo de vídeo
        video_read(colunas, linhas, tcolunas, tlinhas);

        // Configura as dimensões e posição inicial do jogador (RAQUETE) e da bola
        raquete.x = (SCREEN_WIDTH - 40) / 2; //Define posição no centro
        raquete.y = SCREEN_HEIGHT - 20;

        ball.x = SCREEN_WIDTH / 2;
        ball.y = SCREEN_HEIGHT / 2;
        ball.w = BALL_RADIUS * 2;
        ball.h = BALL_RADIUS * 2;

        // Gera a posição e dimensões dos tijolos
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
    else {
        printf("Erro ao abrir video.");
    }
}

// Função para lidar com a entrada do usuário
void handle_input() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            running = false;
        }
    }

    const Uint8* keystate = SDL_GetKeyboardState(NULL);
    if (keystate[SDL_SCANCODE_LEFT] && RAQUETE.x > 0) {
        RAQUETE.x -= 5;
    }
    if (keystate[SDL_SCANCODE_RIGHT] && RAQUETE.x < SCREEN_WIDTH - RAQUETE.w) {
        RAQUETE.x += 5;
    }
}

/*

Esta função recebe dois retângulos como entrada (SDL_Rect a e SDL_Rect b) e verifica se eles estão colidindo. 

Ela opera seguindo os seguintes passos:

Calcula os limites dos retângulos a e b nas direções x e y. Isso é feito determinando as coordenadas dos lados esquerdo (left), 
direito (right), superior (top) e inferior (bottom) de cada retângulo.

Em seguida, verifica se não há interseção entre os limites dos retângulos nas direções x e y. Se não houver interseção em 
qualquer uma das direções, os retângulos não estão colidindo.

Se houver interseção em ambas as direções, significa que os retângulos estão sobrepostos e, portanto, estão colidindo. Nesse caso, 
a função retorna true. Caso contrário, retorna false.

Essa função é usada para detectar colisões entre a bola e outros objetos do jogo, como o jogador (RAQUETE) e os tijolos. Quando a 
bola colide com um desses objetos, ela muda sua direção ou causa um efeito específico, como quebrar um tijolo.

*/

// Função para verificar colisões entre dois retângulos
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

// Função de atualização do jogo
void update() {
    // Atualiza a posição da bola
    ball.x += ball_velocity_x;
    ball.y += ball_velocity_y;

    // Verifica colisões com as paredes
    if (ball.x <= 0 || ball.x >= SCREEN_WIDTH - ball.w) {
        ball_velocity_x = -ball_velocity_x;
    }
    if (ball.y <= 0) {
        ball_velocity_y = -ball_velocity_y;
    }

    // Verifica colisão com o jogador (RAQUETE)
    if (check_collision(ball, RAQUETE)) {
        ball_velocity_y = -ball_velocity_y;
    }

    // Verifica colisão com os tijolos
    for (int i = 0; i < BRICK_ROWS; i++) {
        for (int j = 0; j < BRICK_COLUMNS; j++) {
            if (check_collision(ball, bricks[i][j])) {
                bricks[i][j].x = -1000; // Esconde o tijolo
                ball_velocity_y = -ball_velocity_y;
            }
        }
    }

    // Verifica se o jogo acabou (bola caiu fora da tela)
    if (ball.y >= SCREEN_HEIGHT) {
        running = false;
    }
}

// Função para renderizar o jogo na tela
void render() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Desenha o jogador (RAQUETE)
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &RAQUETE);

    // Desenha a bola
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, &ball);
// Desenha os tijolos
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    for (int i = 0; i < BRICK_ROWS; i++) {
        for (int j = 0; j < BRICK_COLUMNS; j++) {
            SDL_RenderFillRect(renderer, &bricks[i][j]);
        }
    // Desenha os tijolos
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    for (int i = 0; i < BRICK_ROWS; i++) {
        for (int j = 0; j < BRICK_COLUMNS; j++) {
            SDL_RenderFillRect(renderer, &bricks[i][j]);
        }
    }

    // Atualiza a tela com as mudanças
    SDL_RenderPresent(renderer);
}

// Função para limpar recursos alocados pela SDL
void cleanup() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

// Função principal do programa
int main() {
    // Inicializa o jogo
    initialize();

    // Loop principal do jogo
    while (running) {
        handle_input(); // Lidar com entrada do usuário
        update();       // Atualizar estado do jogo
        render();       // Renderizar o jogo
        SDL_Delay(10);  // Pequena pausa para controlar a taxa de atualização
    }

    // Limpa recursos antes de sair
    cleanup();
    return 0;
}
