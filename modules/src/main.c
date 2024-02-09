#include <stdio.h>
#include <stdbool.h>
#include <intelfpgaup/video.h>
#include <intelfpgaup/accel.h>
#include <unistd.h>

typedef struct plataforma {
    int x, y;
    int x2, y2;
} Plataforma;

Plataforma criarPlataforma(int x, int y) {
    Plataforma p;
    p.x = x;
    p.y = y;
    p.x2 = x + 80;
    p.y2 = y - 5;
    return p;
}

bool initialize(int *colunas, int *linhas, int *tcolunas, int *tlinhas) {
    if (video_open()) {
        if (video_read(colunas, linhas, tcolunas, tlinhas)) {
            return true;
        }
    }
    return false;
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

void moverRaquete(Plataforma *raquete, int variacaoX) {
    raquete->x += variacaoX;
    raquete->x2 += variacaoX;
}

int main() {
    int colunas, linhas, tcolunas, tlinhas;
    int ptr_x, ptr_y, ptr_z, ptr_ready, ptr_tap, ptr_dtap, ptr_msg;
    int ultimo_x = 0;

    if (initialize(&colunas, &linhas, &tcolunas, &tlinhas)) {
        int x = (colunas - 80) / 2;
        int y = linhas - 10;
        Plataforma raquete = criarPlataforma(x, y);
        exibeRaquete(raquete);

        // Abre a conexão com o acelerômetro
        accel_open();
accel_init();
accel_format(1, 2);
accel_calibrate();
        // Loop principal do jogo
        while (1) {
            // Lê os dados do acelerômetro
            accel_read(&ptr_ready, &ptr_tap, &ptr_dtap, &ptr_x, &ptr_y, &ptr_z, &ptr_msg);
   
            int variacaoX = ptr_x - ultimo_x;
            ultimo_x = variacaoX;
            // Calcula a variação do eixo X em relação à última leitura
   if (variacaoX < 0 && raquete.x > 0) {
            raquete.x -= 1;
raquete.x2 -=1;
            }
            if (variacaoX > 0 && raquete.x < (319 - 80)) {
            raquete.x += 1;
raquete.x2 +=1;
            }
            // Move a raquete de acordo com a variação do eixo X
            //moverRaquete(&raquete, variacaoX);

            // Exibe a raquete na nova posição
            exibeRaquete(raquete);
            // Aguarda um curto período de tempo para evitar que o loop seja muito rápido
            //unsleep(); // Espera 100ms (0.1 segundo)
           
        }

        // Fecha a conexão com o acelerômetro
        accel_close();
    }

    video_close();
    return 0;
}

