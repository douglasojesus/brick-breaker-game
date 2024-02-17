#include <stdio.h>
#include <intelfpgaup/video.h>
#include <intelfpgaup/accel.h>
#include <intelfpgaup/KEY.h>
#include <intelfpgaup/HEX.h>
#include <unistd.h>

/*
    Dimensões e quantidade do bloco.
*/
const int BLOCK_WIDTH = 28;
const int BLOCK_HEIGHT = 10;
const int BLOCK_ROWS = 4;
const int BLOCK_COLS = 10;

/*
    Estrutura para representar a raquete (Plataforma).
*/
typedef struct plataforma {
    int x, y;
    int x2, y2;
} Plataforma;

/*
    Estrutura para representar um bloco.
*/
typedef struct {
    int x, y;
    int destroyed;
} Block;

/*
    Estrutura para representar a bola.
*/
typedef struct {
    int x, y;
    int dx, dy;
    int size;
} Ball;

/*
    Função reponsável por inicializar posição da bola.
*/
void initBall(Ball* ball) {
    ball->x = 320 / 2;
    ball->y = 240 / 2;
    ball->dx = 2;
    ball->dy = -2;
    ball->size = 2;
}

/*
    Função responsável por inicializar a posição dos blocos. 
*/
void initBlocks(Block blocks[][BLOCK_COLS]) {
    int i = 0;
    int j = 0;
    int brick_offset_x = 4;
    int brick_offset_y = 25;
    // Somadores responsáveis por auxiliar no espaçamento entre blocos.
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

/*
    Função para verificar a colisão da bola com a raquete.
    Ela retorna um valor inteiro que indica se houve uma colisão e, 
    em caso afirmativo, em qual direção a bola colidiu com a raquete.
    -Verifica se a parte inferior da bola (ball->y + 8) está na mesma 
    linha vertical que o topo da raquete (paddle->y).
    -Verifica se a posição horizontal da bola (ball->x) está dentro dos 
    limites horizontais da raquete (paddle->x e paddle->x2) e se a parte
    inferior da bola está dentro dos limites verticais (y, y2) da raquete.
*/
int checkCollision(const Ball* ball, const Plataforma* paddle) {
    // 
    if (ball->y + 6 == paddle->y && 
        ball->x >= paddle->x &&
        ball->x <= paddle->x2) {
        return 0;
    }
    
    else if(ball->x >= paddle->x &&
        ball->x <= paddle->x2 && 
        ball->y + ball->size >= paddle->y && 
        ball->y + ball->size <= paddle->y2) {
        return 1;
    }
    return -1;
}

/*
    Função que verifica a colisão da bola com um bloco.
    Verifica se o bloco ainda não foi destruído (!bloco->destroyed).
    Verifica se a posição horizontal (x) da bola está dentro dos 
    limites horizontais do bloco (bola->x >= bloco->x && bola->x <= bloco->x + BLOCK_WIDTH).
    Verifica se a posição vertical (y) da bola está dentro dos 
    limites verticais do bloco (bola->y >= bloco->y && bola->y <= bloco->y + BLOCK_HEIGHT).
*/
int checkBlockCollision(const Ball* bola, const Block* bloco) {
    if (!(bloco->destroyed)){
        if ((bola->x >= bloco->x) && (bola->x <= (bloco->x + BLOCK_WIDTH)) && (bola->y >= bloco->y) && (bola->y <= (bloco->y + BLOCK_HEIGHT))) { 
            if(((bola->x + bola->size) >= (bloco->x)) && ((bola->x + bola->size) <= (bloco->x + 1)) || ((bola->x) >= (bloco->x + BLOCK_WIDTH)) && ((bola->x) <= (bloco->x + BLOCK_WIDTH -1))){
                printf("entrei na vertical\n");
                return 1;
            } else {
                return 0;
            }
        }
    }
    return -1;    
}    

/*
    Função que inicia a posição da raquete.
*/
Plataforma criarRaquete(int x, int y) {
    Plataforma p;
    p.x = x;
    p.y = y;
    p.x2 = x + 60;
    p.y2 = y - 5;
    return p;
}

/*
    Função que verifica se conseguiu abrir o video e tenta ler as dimensões da tela.
*/
int initialize(int *colunas, int *linhas, int *tcolunas, int *tlinhas) {
    if (video_open()) {
        if (video_read(colunas, linhas, tcolunas, tlinhas)) {
            return 1;
        }
    }
    return 0;
}

/*
    Função que exibe os blocos no monitor. 
    Se o bloco não estiver com o status destroyed, ele é exibido.
*/
void exibeBlocos(Block blocos[][BLOCK_COLS]){

    int i = 0;
    int j = 0;

    for (i = 0; i < BLOCK_ROWS; i++){
        for (j = 0; j < BLOCK_COLS; j++){
            if (!blocos[i][j].destroyed){
                video_box(  blocos[i][j].x, blocos[i][j].y, 
                            blocos[i][j].x + BLOCK_WIDTH, 
                            blocos[i][j].y + BLOCK_HEIGHT, video_BLUE);
            }
        }
    }
}

/*
    Função responsável por exibir os elementos do jogo: raquete, bola e matriz de blocos.
    É executado duas vezes para escrever no Buffer para próxima exibição. Isso garante que não
    haja um efeito de 'pisca' no monitor.
*/
void exibeElementos(Plataforma raquete, Ball bola, Block blocos[][BLOCK_COLS], int pontuacao, int * recorde) {
    char score[]={'S', 'C', 'O', 'R', 'E', '\0'};
    char record[]={'R', 'E', 'C', 'O', 'R', 'D', '\0'};
    char str_pontuacao[20];
    char str_recorde[40];

    if (pontuacao > *recorde){
        *recorde = pontuacao;
    }

    sprintf(str_pontuacao, "%d", pontuacao); // Casting da pontuação
    sprintf(str_recorde, "%d", *recorde); // Casting do recorde

    video_clear();
    video_erase();
    exibeBlocos(blocos);
    // Exibe bola
    video_box(bola.x, bola.y, bola.x + bola.size, bola.y + bola.size, video_RED); 
    // Exibe raquete
    video_box(raquete.x, raquete.y, raquete.x2, raquete.y2, video_WHITE);
    // Exibe linha superior
    video_line(4, 23, 316, 23, video_WHITE); 
    // Exibe linha do lado esquerdo
    video_line(4, 23, 4, 239, video_WHITE);
    // Exibe linha do lado direito
    video_line(316, 23, 316, 239, video_WHITE); //linha do lado direito
    // Exibe texto
    video_text(3, 3, score);
    video_text(11, 3, str_pontuacao);
    video_text(20, 3, record);
    video_text(29, 3, str_recorde);
    video_show();
    
    video_clear();
    video_erase();
    exibeBlocos(blocos);
    // Exibe bola
    video_box(bola.x, bola.y, bola.x + bola.size, bola.y + bola.size, video_RED); 
    // Exibe raquete
    video_box(raquete.x, raquete.y, raquete.x2, raquete.y2, video_WHITE);
    // Exibe linha superior
    video_line(4, 23, 316, 23, video_WHITE); 
    // Exibe linha do lado esquerdo
    video_line(4, 23, 4, 239, video_WHITE);
    // Exibe linha do lado direito
    video_line(316, 23, 316, 239, video_WHITE); //linha do lado direito
    // Exibe texto
    video_text(3, 3, score);
    video_text(11, 3, str_pontuacao);
    video_text(20, 3, record);
    video_text(29, 3, str_recorde);
    video_show();
}

void homePage(){
    char palavra[]={'S', 'T', 'A', 'R', 'T', '?', '\0'};
    video_clear();
    video_erase();
    video_text(34, 30, palavra);
    video_show();

    video_clear();
    video_erase();
    video_text(34, 30, palavra);
    video_show();
}

void endPage(){
    char palavra[]={'G', 'A', 'M', 'E', ' ', 'O', 'V', 'E', 'R', '!', '\0'};
    video_clear();
    video_erase();
    video_text(34, 30, palavra);
    video_show();

    video_clear();
    video_erase();
    video_text(34, 30, palavra);
    video_show();
}

int main() {
    int colunas, linhas, tcolunas, tlinhas;
    int ptr_x, ptr_y, ptr_z, ptr_ready, ptr_tap, ptr_dtap, ptr_msg; //Dados do accel
    int pontuacao = 0;
    int recorde = 0;
    int gameOver = 0;
    int vidas = 3;

    // Se a saída do vídeo e a entrada do botão foram inicializadas
    if (initialize(&colunas, &linhas, &tcolunas, &tlinhas) && KEY_open()) {
        // Inicialização da raquete
        int x = (colunas - 60) / 2;
        int y = linhas - 10;
        Plataforma raquete = criarRaquete(x, y);
        // Inicialização da bola
        Ball bola;
        initBall(&bola);
        // Inicialização da matriz de blocos
        Block blocos[BLOCK_ROWS][BLOCK_COLS];
        initBlocks(blocos);
        // Inicialização do botão
        int KEY_data;
        // Inicialização do display de 7 segmentos
        HEX_open();
        // Inicialização do acelerômetro
        accel_open();
        accel_init();
        accel_format(1, 2);
        accel_calibrate();

        while (1){
            homePage();
            KEY_read(&KEY_data);
            if(KEY_data == 1){
                exibeElementos(raquete, bola, blocos, pontuacao, &recorde);
                break;
            }
        }

        // Loop principal do jogo
        while (1) {
            // Lê os dados do acelerômetro
            accel_read(&ptr_ready, &ptr_tap, &ptr_dtap, &ptr_x, &ptr_y, &ptr_z, &ptr_msg);

            // Altera a posição da raquete de acordo com variação do acelerômetro.
            // A posição só é alterada se o ptr_x não estiver entre -15 e 15 para 
            // evitar movimentação involuntária da raquete devido a sensibilidade do sensor.
            if (!(ptr_x <= 15 && ptr_x >= -15)){
                //Move para esquerda
                if (ptr_x < -15 && (raquete.x - 6) >= 0){ 
                    raquete.x -= 6;
                    raquete.x2 -=6;
                } 
                //Move para direita
                else if ((ptr_x > 15) && (raquete.x2 + 6) <= 319) { 
                    raquete.x += 6;
                    raquete.x2 +=6;
                }
            }

            // Muda a posição da bola
            bola.x += bola.dx;
            bola.y += bola.dy;

            // Verificações de colisão:

                // Verifica colisão da bola com as paredes
            if (bola.x <= 4 || (bola.x + bola.size) >= 315) {
                bola.dx = -bola.dx;
            }
            if (bola.y <= 24) {
                bola.dy = -bola.dy;
            }
           

                // Verifica colisão da bola com a raquete
            if (checkCollision(&bola, &raquete) == 0) {
                bola.dy = -bola.dy;
            }else if(checkCollision(&bola, &raquete) == 1){
                bola.dx = -bola.dx;
            }

                // Verifica colisão da bola com os blocos
            int i = 0;
            int j = 0;
            for (i = 0; i < BLOCK_ROWS; i++){
                for (j = 0; j < BLOCK_COLS; j++){
                    if (checkBlockCollision(&bola, &blocos[i][j]) == 1){
                        blocos[i][j].destroyed = 1;
                        bola.dx = -bola.dx;
                        pontuacao += 1;
                    } else if (checkBlockCollision(&bola, &blocos[i][j]) == 0){
                        blocos[i][j].destroyed = 1;
                        bola.dy = -bola.dy;
                        pontuacao += 1;
                    }
                }
            }

            // Leitura do botão. 
            KEY_read(&KEY_data);

            // Se for o botão 1, o jogo será pausado e a leitura do botão continuará até
            // o botão 1 ser acionado novamente, saindo da iteração.
            if (KEY_data == 1){ //Para pausar
                while (1){
                    KEY_read(&KEY_data);
                    if (KEY_data == 1){ //Para despausar
                          break;
                    }
                }
            }

            // Se quebrou todos os blocos
            if (pontuacao != 0 && (pontuacao % (BLOCK_COLS*BLOCK_ROWS) == 0)){
                initBlocks(blocos);
                initBall(&bola);
                pontuacao += 1;
            }

            // Verifica se a bola caiu e decrementa a vida
            if(bola.y >= 238){
                vidas -= 1;
                if (vidas == 0){
                    gameOver = 1;
                    break;
                }
                initBall(&bola);
                raquete = criarRaquete(x, y);
            }

            // Exibe a vida no display de 7 segmentos
            HEX_set(vidas);

            // Estado de game over
            while (gameOver){
                endPage();
                KEY_read(&KEY_data);
                if(KEY_data == 1){
                    pontuacao = 0;
                    raquete = criarRaquete(x, y);
                    initBall(&bola);
                    initBlocks(blocos);
                    exibeElementos(raquete, bola, blocos, pontuacao, &recorde);
                    vidas = 3;
                    perdeu = 0;
                }
            }

            exibeElementos(raquete, bola, blocos, pontuacao, &recorde);
        }

        // Fecha a conexão com o acelerômetro
        accel_close();
    } else {
        printf("Erro ao inicializar VGA ou botão!\n");
    }
    // Fecha a conexão com o display de sete segmentos e o vídeo/VGA
    HEX_close();
    video_close();
    return 0;
}
