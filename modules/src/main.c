#include <stdlib.h>
#include <stdio.h>
#include <intelfpgaup/video.h>
#include <intelfpgaup/accel.h>
#include <intelfpgaup/KEY.h>
#include <unistd.h>

/*
    Dimensões e quantidade do bloco.
*/
const int BLOCK_WIDTH = 28;
const int BLOCK_HEIGHT = 9;
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
    int color;
} Block;

/*
Representação de cores:
    WHITE = 0xFFFF
    YELLOW = 0xFFE0
    RED = 0xF800
    GREEN = 0x07E0
    BLUE = 0x041F
    CYAN = 0x07FF
    MAGENTA = 0xF81F
    GREY = 0xC618
    PINK = 0xFC18
    ORANGE = 0xFC00
*/

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
    //ball->x = 320 / 2;
    ball->y = 240 / 2;
    //int randomValueY = (rand() % 120) + 80;
    int randomValueX = (rand() % 300) + 5;
   
   
   
    ball->x = randomValueX;
    //ball->y = randomValueY;

    ball->dx = 1;
    ball->dy = -1;
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
            blocks[i][j].color = 0x041F; // Azul
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
int checkCollision(const Ball* bola, const Plataforma* bloco) {
        if(bola->x >= bloco->x && bola->x <= bloco->x2 && (bola->y + 6 == bloco->y || bola->y == bloco->y2)){
            return 1;
        }
        else if(bola->y >= bloco->y && bola->y <= bloco->y2 && (bola->x + 6 == bloco->x || bola->x == bloco->x2)){
            return 0;
        }
else if((((bola->x + bola->size) == bloco->x) && ((bola->y >= bloco->y && bola->y <= bloco->y2) || (bola->y + bola->size >= bloco->y && bola->y + bola->size <= bloco->y2))) ||
(((bloco->x2) == bola->x) && ((bola->y >= bloco->y && bola->y <= bloco->y2) || (bola->y + bola->size >= bloco->y && bola->y + bola->size <= bloco->y2))) ||
  (((bloco->y2) == bola->y) && ((bola->x >= bloco->x && bola->x <= bloco->x2) || (bola->x + bola->size >= bloco->x && bola->x + bola->size <= bloco->x2))) ||
  (((bola->y + bola->size) == bloco->y) && ((bola->x >= bloco->x && bola->x <= bloco->x2) || (bola->x + bola->size >= bloco->x && bola->x + bola->size <= bloco->x2)))){
    return 2;
}
  return -1;
}

// Função para verificar a colisão da bola com um bloco
int checkBlockCollision(const Ball* bola, const Block* bloco) {
    if (!bloco->destroyed){
    //Block_height y
    //Block_width x
        //colisão baixo cima do bloco
        if(bola->x <= (bloco->x + BLOCK_WIDTH) && (bola->x + bola->size) >= bloco->x && (((bloco->y + BLOCK_HEIGHT) == bola->y) || ((bola->y + bola->size) == bloco->y))){
            //colisão lateral com dy >0 e dx <0
	    if((bola->x == (bloco->x + BLOCK_WIDTH)) && bola->dy > 0 && bola->dx < 0){
                return 0;
            }
	    //colisão lateral
            else if(((bola->x + bola->size) == bloco->x) && bola->dy > 0 && bola->dx > 0){
                return 0;
            }
            else if((bola->x == (bloco->x + BLOCK_WIDTH)) && bola->dy < 0 && bola->dx < 0){
                return 0;
            }
            else if(((bola->x + bola->size) == bloco->x) && bola->dy < 0 && bola->dx > 0){
                return 0;
            }

            return 1;
        }
        //colisão direita esquerda do bloco
        else if((bola->y + bola->size) >= bloco->y && bola->y <= (bloco->y + BLOCK_HEIGHT) && (bola->x == (bloco->x + BLOCK_WIDTH) || (bola->x + bola->size) == bloco->x)){
            if((bola->y == (bloco->y + BLOCK_HEIGHT)) && bola->dy > 0 && bola->dx < 0){
                return 1;
            }
            else if(((bola->y + bola->size) == bloco->y) && bola->dy < 0 && bola->dx < 0){
                return 1;
            }
	    else if((bola->y == (bloco->y + BLOCK_HEIGHT)) && bola->dy > 0 && bola->dx > 0){
                return 1;
            }
            else if(((bola->y + bola->size) == bloco->y) && bola->dy < 0 && bola->dx > 0){
                return 1;
            }

            return 0;
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
                            blocos[i][j].y + BLOCK_HEIGHT, blocos[i][j].color);
            }
        }
    }
}

/*
    Função responsável por exibir os elementos do jogo: raquete, bola e matriz de blocos.
    É executado duas vezes para escrever no Buffer para próxima exibição. Isso garante que não
    haja um efeito de 'pisca' no monitor.
*/
void exibeElementos(Plataforma raquete, Ball bola, Block blocos[][BLOCK_COLS], int pontuacao, int * recorde, int vida) {
    char score[]={'S', 'C', 'O', 'R', 'E', '\0'};
    char record[]={'R', 'E', 'C', 'O', 'R', 'D', '\0'};
    char vidas[]={'L', 'I', 'F', 'E', ':', '\0'};
    char str_pontuacao[20];
    char str_recorde[40];
    char quant_vidas[3];

    if (pontuacao > *recorde){
        *recorde = pontuacao;
    }

    sprintf(str_pontuacao, "%d", pontuacao); // Casting da pontuação
    sprintf(str_recorde, "%d", *recorde); // Casting do recorde
    sprintf(quant_vidas, "%d", vida); // Casting da vida

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
    video_text(40, 3, vidas);
    video_text(48, 3, quant_vidas);
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
    video_text(40, 3, vidas);
    video_text(48, 3, quant_vidas);
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
    int perdeu = 0;
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
        // Inicialização do acelerômetro
        accel_open();
        accel_init();
        accel_format(1, 2);
        accel_calibrate();
        //Inicialização do display de sete segmentos
        HEX_open();

        while (1){
            homePage();
            KEY_read(&KEY_data);
            if(KEY_data == 1){
                exibeElementos(raquete, bola, blocos, pontuacao, &recorde, vidas);
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

            int ii = 0;
            int jj = 0;
            for (ii = 0; ii < BLOCK_ROWS; ii++){
                for (jj = 0; jj < BLOCK_COLS; jj++){
                    if (checkBlockCollision(&bola, &blocos[ii][jj]) == 1){
                        if (blocos[ii][jj].color == 0xFC00){ // Laranja
                            blocos[ii][jj].destroyed = 1;
                        }
                        blocos[ii][jj].color = 0xFC00; // Laranja
                        bola.dy = -bola.dy;
                        pontuacao +=1;
break;
                    }
                    else if(checkBlockCollision(&bola, &blocos[ii][jj]) == 0){
                        if (blocos[ii][jj].color == 0xFC00){ // Laranja
                            blocos[ii][jj].destroyed = 1;
                        }
                        blocos[ii][jj].color = 0xFC00; // Laranja
                        bola.dx = -bola.dx;
                        pontuacao +=1;
break;
                    }
                }
            }
   bola.x += bola.dx;
   bola.y += bola.dy;
   int i = 0;
            int j = 0;
            for (i = 0; i < BLOCK_ROWS; i++){
                for (j = 0; j < BLOCK_COLS; j++){
                    if (checkBlockCollision(&bola, &blocos[i][j]) == 1){
                    if (blocos[i][j].color == 0xFC00){ // Laranja
                    blocos[i][j].destroyed = 1;
                    }
                        blocos[i][j].color = 0xFC00; // Laranja
                        bola.dy = -bola.dy;
                        pontuacao +=1;
break;
                    }
                    else if(checkBlockCollision(&bola, &blocos[i][j]) == 0){
                    if (blocos[i][j].color == 0xFC00){ // Laranja
                    blocos[i][j].destroyed = 1;
                    }
                        blocos[i][j].color = 0xFC00; // Laranja
                        bola.dx = -bola.dx;
                        pontuacao +=1;
break;
                    }
                }
            }
   

            // Verificações de colisão:

                // Verifica colisão da bola com as paredes
            if (bola.x <= 6 || (bola.x + bola.size) >= 315) {
                bola.dx = -bola.dx;
            }
            if (bola.y <= 24) {
                bola.dy = -bola.dy;
            }
           
           
            if (checkCollision(&bola, &raquete) == 1){
                bola.dy = -bola.dy;
            }
            else if(checkCollision(&bola, &raquete) == 0){
                bola.dx = -bola.dx;
            }
            else if(checkCollision(&bola, &raquete) == 2){
bola.dx = -bola.dx;
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
            if (pontuacao != 0 && (pontuacao % (BLOCK_COLS*BLOCK_ROWS*2) == 0)){
                initBlocks(blocos);
                initBall(&bola);
                pontuacao++;
            }

            //verifica se a bola caiu
            if(bola.y >= 238){
                vidas -=1;
perdeu = 1;
            }
            if(vidas != 0 && perdeu == 1){
                   raquete = criarRaquete(x, y);
                   initBall(&bola);
                   perdeu = 0;
   }
   else{
                while (vidas == 0){
                    endPage();
                    KEY_read(&KEY_data);
                    HEX_set(0);
                    if(KEY_data == 1){
                         pontuacao = 0;
                         raquete = criarRaquete(x, y);
                         initBall(&bola);
                         initBlocks(blocos);
                         exibeElementos(raquete, bola, blocos, pontuacao, &recorde, vidas);
        vidas = 3;
                }
            }
            }
            exibeElementos(raquete, bola, blocos, pontuacao, &recorde, vidas);
            HEX_set(vidas);
        }

        // Fecha a conexão com o acelerômetro
        accel_close();
    } else {
        printf("Erro ao inicializar VGA ou botão!\n");
    }
    // Fecha a conexão com o vídeo/VGA
    HEX_open();
    video_close();
    return 0;
}

