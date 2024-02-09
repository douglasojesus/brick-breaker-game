#include <stdio.h>
#include <stdbool.h>
#include <intelfpgaup/video.h>

typedef struct plataforma{
    int x, y; 
    int x2, y2;
} Plataforma;

// Função para inicializar a struct
Plataforma criarPlataforma(int x, int y) {
    Plataforma p;
    p.x = x;
    p.y = y;
    p.x2 = x + 80;
    p.y2 = y - 5;
    return p;
}

// Função de inicialização do jogo
int initialize(int * colunas, int * linhas, int * tcolunas, int * tlinhas) {
    // Inicializa o vídeo
    if (video_open()){
        printf("video open!!!!!!!!\n");
        // Faz leitura do dispositivo de vídeo
        if (video_read(colunas, linhas, tcolunas, tlinhas)){
            printf("ENTROU!!!!!!!!\n");
            return 1;
        }
    }
    return 0;
}

void exibeRaquete(Plataforma raquete){
    video_clear();
    video_box(raquete.x, raquete.y, raquete.x2, raquete.y2, video_RED);
    video_show();
    printf("entrou no initialize.\n");
}

void moverRaquete(Plataforma raquete, int variacaoX){
    video_clear();
}

// Função principal do programa
int main() {
    int colunas;
    int linhas;
    int tcolunas;
    int tlinhas;

    // Inicializa o jogo

    if (initialize(&colunas, &linhas, &tcolunas, &tlinhas)){
        printf("entrou no initialize.\n");
        // Coordenadas para definir a raquete na posição inicial
        int x = (colunas - 80) / 2;
        int y = (linhas) - 10;

        Plataforma raquete = criarPlataforma(x, y);

        exibeRaquete(raquete);
    }

    video_close();
    return 0;
}
