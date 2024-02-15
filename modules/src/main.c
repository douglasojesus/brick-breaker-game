// ideia: o brick tem 2 colisões 
// muda a cor do brick quando faltar uma colisao
// adiciona a cor na struct

#include <stdio.h>
#include <stdbool.h>
#include <intelfpgaup/video.h>
#include <intelfpgaup/accel.h>
#include <intelfpgaup/KEY.h>
#include <unistd.h>

// Dimensões do bloco
const int BLOCK_WIDTH = 28;
const int BLOCK_HEIGHT = 10;
const int BLOCK_ROWS = 4;
const int BLOCK_COLS = 10;

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
void initBlocks(Block blocks[][BLOCK_COLS]) {

    int i = 0;
    int j = 0;
    //int brick_offset_x = (219 - (BLOCK_COLS * BLOCK_WIDTH)) / 2;
    int brick_offset_x = 4;
    int brick_offset_y = 25;
    int somadorX;
    int somadorY = 3;

    for (i = 0; i < BLOCK_ROWS; i++) {
        somadorX = 3;
        for (j = 0; j < BLOCK_COLS; j++) {
            blocks[i][j].x = (brick_offset_x + (j * BLOCK_WIDTH) + somadorX);
            blocks[i][j].y = (brick_offset_y + (i * BLOCK_HEIGHT) + somadorY);
            blocks[i][j].destroyed = 0;
            somadorX += 3;
        }
        somadorY += 3;
    }
}

// Função para verificar a colisão da bola com a raquete
int checkCollision(const Ball* ball, const Plataforma* paddle) {
    if (ball->y + 8 == paddle->y && // 6 +2 -> a bola anda de 6 em 6 e 2 é o tamanho da bola
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
    p.x2 = x + 60;
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

// Desenha os blocos
void exibeBlocos(Block blocos[][BLOCK_COLS]){

    int i = 0;
    int j = 0;

    for (i = 0; i < BLOCK_ROWS; i++){
        for (j = 0; j < BLOCK_COLS; j++){
            if (!blocos[i][j].destroyed){
                video_box(blocos[i][j].x, blocos[i][j].y, blocos[i][j].x + BLOCK_WIDTH, blocos[i][j].y + BLOCK_HEIGHT, video_RED);
            }
        }
    }
}

//Exibe a raquete com as dimensões antes especificadas
void exibeElementos(Plataforma raquete, Ball bola, Block blocos[][BLOCK_COLS]) {
    video_clear();
    exibeBlocos(blocos);
    video_box(bola.x, bola.y, bola.x + bola.size, bola.y + bola.size, video_RED); //Exibe bola
    video_box(raquete.x, raquete.y, raquete.x2, raquete.y2, video_RED);
    video_line(0, 23, 319, 23, video_WHITE); //linha de cima
    video_line(0, 23, 0, 239, video_WHITE); //linha do lado esquerdo
    video_line(319, 23, 319, 239, video_WHITE); //linha do lado direito
    video_show();
    //para escrever no outro buffer, colocamos a exibição duas vezes
    video_clear();
    exibeBlocos(blocos);
    video_box(bola.x, bola.y, bola.x + bola.size, bola.y + bola.size, video_RED); //Exibe bola
    video_box(raquete.x, raquete.y, raquete.x2, raquete.y2, video_RED);
    video_line(0, 23, 319, 23, video_WHITE); //linha de cima
    video_line(0, 23, 0, 239, video_WHITE); //linha do lado esquerdo
    video_line(319, 23, 319, 239, video_WHITE); //linha do lado direito
    video_show();
}

int main() {
    int colunas, linhas, tcolunas, tlinhas;
    int ptr_x, ptr_y, ptr_z, ptr_ready, ptr_tap, ptr_dtap, ptr_msg; //Dados do accel

    if (initialize(&colunas, &linhas, &tcolunas, &tlinhas)) {
        int x = (colunas - 60) / 2;
        int y = linhas - 10;
        Plataforma raquete = criarRaquete(x, y);
        Ball bola;
        initBall(&bola);
        Block blocos[BLOCK_ROWS][BLOCK_COLS];
        initBlocks(blocos);
        //exibeBlocos(blocos);
        exibeElementos(raquete, bola, blocos);
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

            //printf("x: %d\n", ptr_x);

            if (!(ptr_x <= 15 && ptr_x >= -15)){
                if (ptr_x < -15 && (raquete.x - 6) >= 0){ //Move para esquerda
                    raquete.x -= 6;
                    raquete.x2 -=6;
                } else if ((ptr_x > 15) && (raquete.x2 + 6) <= 319) { //Move para direita
                    raquete.x += 6;
                    raquete.x2 +=6;
                }
            }

            // Move a bola
            bola.x += bola.dx;
            bola.y += bola.dy;

            // Verifica colisão com as paredes
            if (bola.x <= 0 || (bola.x + bola.size) >= 318) {
                bola.dx = -bola.dx;
            }
            if (bola.y <= 24) {
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
            int j = 0;
            for (i = 0; i < BLOCK_ROWS; i++){
                for (j = 0; j < BLOCK_COLS; j++){
                    if (checkBlockCollision(&bola, &blocos[i][j])){
                        blocos[i][j].destroyed = 1;
                        bola.dy = -bola.dy;
                    }
                }
            }

            exibeElementos(raquete, bola, blocos);

        }

        // Fecha a conexão com o acelerômetro
        accel_close();
    }

    video_close();
    return 0;

}

