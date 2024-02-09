#include <stdio.h>
#include <stdbool.h>
#include <intelfpgaup/video.h>
#include <intelfpgaup/accel.h>
#include <unistd.h>

typedef struct plataforma {
    int x, y;
    int x2, y2;
} Plataforma;

typedef struct brick {
    int x, y;
    int x2, y2;
    int status; // 1 -> exibido, 0 - > quebrado
} Brick;

Plataforma criarPlataforma(int x, int y) {
    Plataforma p;
    p.x = x;
    p.y = y;
    p.x2 = x + 80;
    p.y2 = y - 5;
    return p;
}

int initializeVideo(int *colunas, int *linhas, int *tcolunas, int *tlinhas) {
    if (video_open()) {
        if (video_read(colunas, linhas, tcolunas, tlinhas)) {
            return 1;
        }
    }
    return 0;
}

void initializeAccel(){
    accel_open();
    accel_init();
    accel_format(1, 2);
    accel_calibrate();
}

void exibeRaquete(Plataforma raquete) {
    video_clear();
    video_box(raquete.x, raquete.y, raquete.x2, raquete.y2, video_RED);
    video_show();
    video_clear();
    video_box(raquete.x, raquete.y, raquete.x2, raquete.y2, video_RED);
    video_show();
}

void checkColision(){
}

void createBricksTable(){

}

void moverRaquete(Plataforma *raquete, int variacaoX) {
    raquete->x += variacaoX;
    raquete->x2 += variacaoX;
}

int main() {
    int colunas, linhas, tcolunas, tlinhas;
    int ptr_x, ptr_y, ptr_z, ptr_ready, ptr_tap, ptr_dtap, ptr_msg;
    int ultimo_x = 0;
    int variacaoX;

    if (initializeVideo(&colunas, &linhas, &tcolunas, &tlinhas)) {
        /*Define coordenadas da raquete no centro.*/
        int x = (colunas - 80) / 2;
        int y = linhas - 10;

        Plataforma raquete = criarPlataforma(x, y);

        exibeRaquete(raquete);

        initializeAccel();
    
        /*Início do jogo.*/
        while (1) {
            // Lê os dados do acelerômetro
            accel_read(&ptr_ready, &ptr_tap, &ptr_dtap, &ptr_x, &ptr_y, &ptr_z, &ptr_msg);
   
            // Calcula a variação do eixo X em relação à última leitura
            variacaoX = ptr_x - ultimo_x;
            ultimo_x = variacaoX;

            // Se o acelerômetro marcar negativo e a plataforma estiver dentro da área delimitada
            if (variacaoX < 0 && raquete.x > 0) { 
                raquete.x -= 1;
                raquete.x2 -= 1;
            }

            // Se o acelerômetro marcar positivo e a plataforma estiver dentro da área delimitada
            if (variacaoX > 0 && raquete.x < (319 - 80)) {
                raquete.x += 1;
                raquete.x2 += 1;
            }

            // Move a raquete de acordo com a variação do eixo X
            moverRaquete(&raquete, variacaoX); //Essa parte estava comentada na versão que estava funcionando.

            // Exibe a raquete na nova posição
            exibeRaquete(raquete);

            // Espera 100ms (0.1 segundo)
            unsleep(); //Essa parte estava comentada na versão que estava funcionando.
           
        }        
    }

    /*Fecha dispositivos.*/
    accel_close();
    video_close();
    return 0;
}

