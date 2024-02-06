#include "SDL.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "SDL_main.h"
#include "SDL_stdinc.h"
#include "SDL_assert.h"
#include "SDL_atomic.h"
#include "SDL_audio.h"
#include "SDL_clipboard.h"
#include "SDL_cpuinfo.h"
#include "SDL_endian.h"
#include "SDL_error.h"
#include "SDL_events.h"
#include "SDL_filesystem.h"
#include "SDL_gamecontroller.h"
#include "SDL_guid.h"
#include "SDL_haptic.h"
#include "SDL_hidapi.h"
#include "SDL_hints.h"
#include "SDL_joystick.h"
#include "SDL_loadso.h"
#include "SDL_log.h"
#include "SDL_messagebox.h"
#include "SDL_metal.h"
#include "SDL_mutex.h"
#include "SDL_power.h"
#include "SDL_render.h"
#include "SDL_rwops.h"
#include "SDL_sensor.h"
#include "SDL_shape.h"
#include "SDL_system.h"
#include "SDL_thread.h"
#include "SDL_timer.h"
#include "SDL_version.h"
#include "SDL_video.h"
#include "SDL_locale.h"
#include "SDL_misc.h"

int Verifica(int xbola, int ybola, int vector[], int vector1[]){
    for(int i = 0; i < 12; i++){
        if(ybola-11 == vector1[i] && xbola >= vector[i] && xbola + 10 <= vector[i] + 50){
            return i;
        }
    }
    return -1;
}

int WinMain(int argc, char *argv[]) {

    int vector1[10];
    int vector[10];

    vector[0] = 5;
    vector[1] = 60;
    vector[2] = 115;
    vector[3] = 170;
    vector[4] = 225;
    vector[5] = 280;
    vector[6] = 335;
    vector[7] = 390;
    vector[8] = 445;
    vector[9] = 500;
    vector[10] = 555;
    vector[11] = 610;
    vector[12] = 665;


    vector1[0] = 5;
    vector1[1] = 5;
    vector1[2] = 5;
    vector1[3] = 5;
    vector1[4] = 5;
    vector1[5] = 5;
    vector1[6] = 5;
    vector1[7] = 5;
    vector1[8] = 5;
    vector1[9] = 5;
    vector1[10] = 5;
    vector1[11] = 5;
    vector1[12] = 5;

    // Inicializa a SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Erro ao inicializar a SDL: %s\n", SDL_GetError());
        return 1;
    }

    //Posição em x e em y da bola
    int xbola = 315;
    int ybola = 235;

    //Posição em x
    int xraquete = 295;
    int yraquete = 430;
    int velocidade = 5;

    // Cria uma janela
    SDL_Window *window = SDL_CreateWindow("Ponto no Centro", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
    640, 480, SDL_WINDOW_SHOWN);

    // Verifica se a janela foi criada com sucesso
    if (window == NULL) {
        printf("Erro ao criar a janela: %s\n", SDL_GetError());
        return 1;
    }

    // Cria um renderizador
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // Verifica se o renderizador foi criado com sucesso
    if (renderer == NULL) {
        printf("Erro ao criar o renderizador: %s\n", SDL_GetError());
        return 1;
    }

    int somax = 1;
    int somay = 1;

    while(1){

        //printf("%d %d\n",xbola, ybola);

        //printf("%d %d\n" ,xraquete, yraquete);

        int colisao;

        colisao = Verifica(xbola,ybola, vector, vector1);

        if(colisao != -1){
            vector[colisao] = -1;
            vector1[colisao] = -1;
            somax = 1;
            somay = 1;
        }

        if(somax == 0 ){
            xbola -= 1;
            if(xbola == 0 || xbola == 630){
                somax = 1;
            }
        }
        else{
            xbola += 1;
            if(xbola == 0 || xbola == 630 || (ybola+11 == yraquete && xbola >= xraquete && xbola + 10 <= xraquete + 50)){
                somax = 0;
            }
        }
        if(somay == 0){
            ybola -= 1;
            if(ybola == 0 || ybola == 470){
                somay = 1;
            }
        }
        else{
            ybola += 1;
            if(ybola == 0 || ybola == 470 || (ybola+11 == yraquete && xbola >= xraquete && xbola + 10 <= xraquete + 50)){
                somay = 0;            
            }
        }

        // Limpar o renderer
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        // Define a cor do fundo (branco)
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

        // Limpa a tela com a cor do fundo
        SDL_RenderClear(renderer);

        for(int i = 0; i < 12; i++)
        {
            if(vector[i] != -1){
                SDL_SetRenderDrawColor(renderer, 0, 0, 1, 255);
                SDL_Rect raquete = { vector[i], vector1[0], 50, 10 };
                SDL_RenderFillRect(renderer, &raquete);
            }
        
        }

        // Desenhar a raquete
        SDL_SetRenderDrawColor(renderer, 0, 0, 1, 255);
        SDL_Rect raquete = { xraquete, yraquete, 50, 10 };
        SDL_RenderFillRect(renderer, &raquete);

        // Desenhar a bolinha
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_Rect bolinha = { xbola, ybola, 10, 10 };
        SDL_RenderFillRect(renderer, &bolinha);
        
        // Atualiza a tela
        SDL_RenderPresent(renderer);

        // Adicionar uma pequena pausa para controlar a velocidade de movimento
        SDL_Delay(10);

        SDL_Event event;

        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                    case SDLK_LEFT:
                            xraquete -= velocidade;

                        break;
                    case SDLK_RIGHT:
                            xraquete += velocidade;

                        break;
                }
            }
        }
        
        // Aguarda um evento para fechar a janela
        while (SDL_PollEvent(&event) && event.type == SDL_QUIT) {
                break;
        }
    }
    // Libera recursos
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
