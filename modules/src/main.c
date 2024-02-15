#include <stdio.h>
#include <stdbool.h>
#include <intelfpgaup/video.h>
#include <intelfpgaup/accel.h>
#include <intelfpgaup/KEY.h>
#include <unistd.h>

// Dimensões do bloco
const int BLOCK_WIDTH = 28;
const int BLOCK_HEIGHT = 10;
const int NUM_BLOCKS = 33;
const int BLOCK_ROWS = 3;
const int BLOCK_COLS = 11;

//Estrutura para representar a raquete (Plataforma)
typedef struct plataforma {
    int x, y;
    int x2, y2;
} Plataforma;

// Estrutura para representar um bloco
typedef struct {
    int x, y;
    bool destroyed;
} Block;

// Estrutura para representar a bola
typedef struct {
    int x, y;
    int dx, dy;
    int size;
} Ball;

// Função para inicializar a bola
void initBall(Ball* ball) {
    ball->x = 320 / 2;
    ball->y = 240 / 2;
    ball->dx = 2;
    ball->dy = -2;
    ball->size = 2;
}

// Função para inicializar os blocos
void initBlocks(Block blocks[]) {
    int blockWidthWithSpacing = BLOCK_WIDTH + 1;
    int blockHeightWithSpacing = BLOCK_HEIGHT + 1;
    int i = 0;
    for (i; i < NUM_BLOCKS; ++i) {
        blocks[i].x = (i % BLOCK_COLS) * blockWidthWithSpacing;
        blocks[i].y = (i / BLOCK_COLS) * blockHeightWithSpacing;
        blocks[i].destroyed = false;
    }
}

// Função para verificar a colisão da bola com a raquete
int checkCollision(const Ball* ball, const Plataforma* paddle) {
    if (ball->y + ball->size == paddle->y &&
        ball->x >= paddle->x &&
        ball->x <= paddle->x2) {
        return 0;
    }
    else if(ball->x >= paddle->x &&
        ball->x <= paddle->x2 && ball->y + ball->size >= paddle->y && ball->y + ball->size <= paddle->y2){
        return 1;
        }
    return -1;
}

// Função para verificar a colisão da bola com um bloco
bool checkBlockCollision(const Ball* bola, const Block* bloco) {
    if (!bloco->destroyed &&
        bola->x >= bloco->x &&
        bola->x <= bloco->x + BLOCK_WIDTH &&
        bola->y >= bloco->y &&
        bola->y <= bloco->y + BLOCK_HEIGHT) {
        return true;
    }
    return false;
}

//Cria (inicia) a posição da raquete
Plataforma criarRaquete(int x, int y) {
    Plataforma p;
    p.x = x;
    p.y = y;
    p.x2 = x + 80;
    p.y2 = y - 5;
    return p;
}

//Verifica se conseguiu abrir o video e tenta ler as dimensões da tela
bool initialize(int *colunas, int *linhas, int *tcolunas, int *tlinhas) {
    if (video_open()) {
        if (video_read(colunas, linhas, tcolunas, tlinhas)) {
            return true;
        }
    }
    return false;
}

//Exibe a raquete com as dimensões antes especificadas
void exibeRaquete(Plataforma raquete, Ball bola, Block blocos[]) {
    video_clear();
    exibeBlocos(blocos);
    video_box(bola.x, bola.y, bola.x + bola.size, bola.y + bola.size, video_RED);
    video_box(raquete.x, raquete.y, raquete.x2, raquete.y2, video_RED);
    video_show();
    video_clear();
    exibeBlocos(blocos);
    video_box(bola.x, bola.y, bola.x + bola.size, bola.y + bola.size, video_RED);
    video_box(raquete.x, raquete.y, raquete.x2, raquete.y2, video_RED);
    video_show();
}

//Exibe a bola nas dimensões antes especificadas
/*void exibeBola(Ball bola){
    video_clear();
    video_box(bola.x, bola.y, bola.x + bola.size, bola.y + bola.size, video_RED);
    video_show();
    video_clear();
    video_box(bola.x, bola.y, bola.x + bola.size, bola.y + bola.size, video_RED);
    video_clear();
}*/

// Desenha os blocos
void exibeBlocos(Block blocos[]){
    int i = 0;
    for (i; i < NUM_BLOCKS; ++i) {
        if (!blocos[i].destroyed) {
            video_box(blocos[i].x, blocos[i].y, blocos[i].x + BLOCK_WIDTH, blocos[i].y + BLOCK_HEIGHT, video_RED);
        }
    }
}

int main() {
    int colunas, linhas, tcolunas, tlinhas;
    int ptr_x, ptr_y, ptr_z, ptr_ready, ptr_tap, ptr_dtap, ptr_msg;
    int ultimo_x = 0;

    if (initialize(&colunas, &linhas, &tcolunas, &tlinhas)) {
        int x = (colunas - 80) / 2;
        int y = linhas - 10;
        Plataforma raquete = criarRaquete(x, y);
        Ball bola;
        initBall(&bola);
        Block blocos[NUM_BLOCKS];
        initBlocks(blocos);
        //exibeBlocos(blocos);
        exibeRaquete(raquete, bola, blocos);
        //exibeBola(bola);

        // Abre a conexão com o acelerômetro
        accel_open();
        accel_init();
        accel_format(1, 2);
        accel_calibrate();
        // Loop principal do jogo
        while (1) {
            // Lê os dados do acelerômetro
            accel_read(&ptr_ready, &ptr_tap, &ptr_dtap, &ptr_x, &ptr_y, &ptr_z, &ptr_msg);

            printf("x: %d\n", ptr_x);

            if (!(ptr_x <= 15 && ptr_x >= -15)){
                if (ptr_x < -15 && (raquete.x - 6) >= 0){ //Move para esquerda
                    raquete.x -= 6;
                    raquete.x2 -=6;
                } else if ((ptr_x > 15) && (raquete.x2 + 6) <= 319) { //Move para direita
                    raquete.x += 6;
                    raquete.x2 +=6;
                }
            }

            //ultimo_x = ptr_x;

            // Move a raquete de acordo com a variação do eixo X
            //moverRaquete(&raquete, variacaoX);
           
            // Move a bola
            bola.x += bola.dx;
            bola.y += bola.dy;

            // Verifica colisão com as paredes
            if (bola.x <= 0 || (bola.x + bola.size) >= 319) {
                bola.dx = -bola.dx;
            }
            if (bola.y <= 0) {
                bola.dy = -bola.dy;
            }
           
            // Verifica colisão com a raquete
            if (checkCollision(&bola, &raquete) == 0) {
                bola.dy = -bola.dy;
            }else if(checkCollision(&bola, &raquete) == 1){
                bola.dx = -bola.dx;
            }

            // Verifica colisão com os blocos
            int i = 0;
            for (i; i < NUM_BLOCKS; ++i) {
                if (checkBlockCollision(&bola, &blocos[i])) {
                    blocos[i].destroyed = true;
                    bola.dy = -bola.dy;
                }
            }

            //Exibe os blocos atualizados
            //exibeBlocos(blocos);
            // Exibe a raquete na nova posição
            exibeRaquete(raquete, bola, blocos);
            //Exibe a bola na nova posição
            //exibeBola(bola);
            // Aguarda um curto período de tempo para evitar que o loop seja muito rápido
            //unsleep(); // Espera 100ms (0.1 segundo)
           
        }

        // Fecha a conexão com o acelerômetro
        accel_close();
    }

    video_close();
    return 0;

}
