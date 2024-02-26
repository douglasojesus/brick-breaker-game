<h1 align="center">
📄<br>Projeto Módulo Integrador de Sistemas Digitais - Problema 03.
</h1>

<h4 align="center">
Projeto produzido a ser avaliado pela disciplina de M.I Sistemas Digitais da Universidade Estadual de Feira de Santana.
</h4> 

<h2 align="center">
🖥️Implementação do jogo Breakout em linguagem C para exibição no monitor CRT através do KIT de desenvolvimento DE1-SoC.
</h2>

<h1 id="sumario" align="center">Sumário</h1>
</h2>
<ul>
  <li><a href="#membros"><b>Equipe de Desenvolvimento</b></li>
  <li><a href="#introducao"> <b>Introdução</b></li>
  <li><a href="#requisitos"> <b>Objetivos e Requisitos do problema</b> </a></li>
  <li><a href="#recursos"> <b>Recursos Utilizados</b></li>
  <li><a href="#desenvolvimento"> <b>Desenvolvimento e Descrição em Alto Nível</b> </a> </li>
  <li><a href="#descricao-e-analise-dos-testes"> <b>Descrição e Análise dos Testes e Simulações, Resultados e Discussões</b> </a></li>
  <li><a href="#conclusao"> <b>Conclusão</b> </a></li>
  <li><a href="#bibliografia"> <b>Bibliografia</b> </a></li>
  <li><a href="#script-de-compilacao"> <b>Uso do projeto</b> </a></li>
</ul>

<h1 id="membros" align="center">Equipe de Desenvolvimento</h1>

  <ul>
		<li><a href="https://github.com/douglasojesus"> Douglas Oliveira de Jesus </li>
		<li><a href="https://github.com/Emanuel-Antonio"> Emanuel Antonio Lima Pereira </a></li>
      <li><a href="https://github.com/emersonrlp"> Emerson Rodrigo Lima Pereira </a></li>
      <li><a href="https://github.com/GabrielSousaSampaio"> Gabriel Sousa Sampaio </a></li>
  </ul>

  <h1 id="introducao" align="center">Introdução</h1> 

 <p align="justify">O Breakout é um clássico jogo de arcade lançado pela Atari em 1976, que desafiou gerações de jogadores com sua jogabilidade simples e viciante. O jogo consiste em mover uma plataforma móvel localizada na parte inferior da tela para rebater uma bola, destruindo blocos dispostos em fileiras na parte superior da tela. Com mecânicas simples, mas desafiadoras, e uma estética retrô, o Breakout continua a ser uma referência na história dos videogames, influenciando inúmeras criações e permanecendo uma fonte de diversão atemporal até os dias de hoje.
   
   O desenvolvimento do Breakout se deu em uma época em que a tecnologia disponível era bastante limitada em comparação com os padrões atuais. Na década de 1970, os recursos computacionais eram escassos, e os desenvolvedores enfrentaram desafios significativos ao criar jogos devido às limitações de hardware e software da época. O Breakout original foi projetado para máquinas de arcade, que tinham recursos muito mais restritos do que os sistemas de jogos contemporâneos. A programação era feita em linguagem de montagem, uma linguagem de baixo nível que permitia um controle mais direto sobre o hardware, mas que também exigia um entendimento profundo da arquitetura específica da máquina.
   
   Dessa forma, o projeto descrito abaixo busca integrar a nostalgia do Breakout com a tecnologia moderna, utilizando o Kit de Desenvolvimento DE1-SoC, que oferece recursos como acelerômetro e botões para a interação do jogador. Neste desafio, o objetivo é desenvolver uma implementação em linguagem C, aproveitando exclusivamente os componentes disponíveis na placa FPGA. O movimento do jogador será captado pelo acelerômetro, enquanto os botões servirão para controlar o jogo, proporcionando uma experiência envolvente através da interface VGA em um monitor CRT.
 </p>
 <h1 id="requisitos" align="center">Objetivos e Requisitos do problema</h1> 

<p align="justify">Desenvolver este projeto implica na criação de um jogo inspirado no clássico Breakout, utilizando o Kit de Desenvolvimento DE1-SoC. O movimento do jogador será captado pelo acelerômetro integrado no kit, proporcionando uma experiência interativa e dinâmica. A interação com o jogo, incluindo ações como iniciar, pausar e continuar, será controlada pelos botões disponíveis na placa. A interface VGA será utilizada para a visualização do jogo em um monitor CRT.

O objetivo principal deste trabalho é capacitar os discentes a programar em linguagem C para um sistema embarcado, explorando os recursos do Kit DE1-SoC. Isso envolverá a compreensão e aplicação do conjunto de instruções específicas da arquitetura, bem como a integração do acelerômetro para capturar o movimento do jogador. A interface VGA, por sua vez, será empregada para renderizar visualmente o jogo no monitor CRT, reforçando a atmosfera clássica do Breakout.

Para atingir essas metas, é crucial atender aos seguintes requisitos:
- 📝 O código deve ser escrito em linguagem C;
- 📝 O sistema só poderá utilizar os componentes disponíveis na placa FPGA DE1-SoC.

Este projeto não apenas representa um desafio técnico significativo, mas também oferece uma oportunidade valiosa para a aplicação prática de conhecimentos em programação, arquitetura de computadores e desenvolvimento de sistemas embarcados, destacando-se pela integração de dispositivos como o acelerômetro e a interface VGA para proporcionar uma experiência de jogo envolvente e nostálgica.

<h1 id="recursos" align="center">Recursos utilizados</h1>

- 🔧 Visual Studio Code;
- 🔧 Git e Github;
- 🔧 FPGA DE1-SoC;
- 🔧 Monitor CRT Dell E773C;
- 🔧 Linguagem C;

<h2>FPGA DE1-SoC</h2>
A DE1-SoC (Cyclone V SoC Development and Education Board) é uma placa de desenvolvimento criada pela Terasic, projetada para oferecer uma ampla gama de recursos e capacidades para aplicações de desenvolvimento. A DE1-SoC é baseada na família de FPGA Cyclone V da Intel (anteriormente Altera). Dentre suas principais especificações, têm-se:

- Processador:
  - O processador da placa é um dual-core ARM Cortex-A9 integrado no mesmo chip (SoC - System on Chip). Isso permite a execução de sistemas operacionais, como Linux, diretamente na placa.

- Recursos de Memória:
  - A placa possui vários tipos de memória, incluindo DDR3 SDRAM para armazenamento de dados e código, SRAM para armazenamento temporário e memória flash para armazenamento persistente:
    
    - SDRAM de 64 MB (32Mx16) em FPGA
    - SDRAM DDR3 de 1 GB (2x256Mx16) em HPS
    - Soquete para cartão Micro SD no HPS

- Conectividade:
  - A DE1-SoC oferece várias opções de conectividade, incluindo portas USB, HDMI, áudio, Ethernet e muito mais. Essas interfaces possibilitam a interação com periféricos e a comunicação com outros dispositivos.

- Entradas/Saídas (I/O):
  - A placa possui uma variedade de pinos de entrada/saída que podem ser configurados para se adaptar a diferentes aplicações. Isso permite a conexão de sensores, displays, botões e outros dispositivos externos.

- Periféricos Integrados:
  - A DE1-SoC inclui vários periféricos integrados, como acelerômetro, ADC (Conversor Analógico-Digital), entre outros.

- Interfaces de Expansão:
  - A DE1-SoC possui conectores de expansão, como GPIO (General-Purpose Input/Output) e headers de pinos, permitindo a conexão de placas de expansão ou a integração de módulos adicionais.

- Display VGA:
  - A placa é equipada com uma interface VGA que permite a conexão, como no caso desse projeto, a monitores CRT, proporcionando uma saída visual para projetos gráficos, como o caso do jogo Breakout.

- Botões e Interruptores:
  - A DE1-SoC possui botões e interruptores que podem ser utilizados como entradas do usuário em projetos, oferecendo uma forma de interação física.

<h2>Acelerômetro </h2>
<h2>Linguagem C</h2>
<h2>Interface VGA e Monitor CRT Dell E773C</h2>

<h1 id="desenvolvimento" align="center">Desenvolvimento e Descrição em Alto Nível</h1>

<h2>DEFINICAO DAS REGRAS E ESTRUTURAS DO JOGO: ASPECTOS TÉCNICOS</h2>

A primeira etapa do desenvolvimento do projeto Breakout, dedicou-se a atenção meticulosa à definição das regras e funcionalidades fundamentais que moldarão a experiência de jogo. Cada aspecto foi estrategicamente concebido para garantir não apenas a essência do jogo original, mas também uma execução eficiente no contexto de sistemas embarcados.

O projeto possui três telas principais, a tela de início (start game), o jogo em si e a de final de jogo (Figura X). Ao acionar o programa, a interface inicial é revelada dando a opção do usuário iniciar o jogo. Em seguida, ao selecionar a opção de start, o jogo se inicia apresentando-lhe os tijolos localizados na parte superior da tela, uma plataforma na parte inferior e o brick breaker (bola) no centro. O objetivo central do jogo é evitar que a bola (brick breaker) ultrapasse a parte inferior da tela utilizando a plataforma móvel para rebater a bola e, ao mesmo tempo, destruir todos os tijolos. Se a bola ultrapassar a área da plataforma a vida do jogador é decrementada, e se as suas vidas acabarem a partida se encerra e a pontuação é zerada.

O jogo possui apenas uma fase e a pontuação é registrada de acordo com a quantidade de tijolos destruídos, atribuindo 1 ponto a cada tijolo. Além disso, possibilita-se o registro da maior pontuação já feita, sendo esse o recorde da rodada.

A plataforma reflete a bola de acordo com o ângulo de incidência, com um acréscimo ou decréscimo arbitrário de graus para evitar constância. Paredes e tijolos, da mesma forma, reagem refletindo o ângulo da bola.

A bola é lançada inicialmente em uma certa direção, e sua velocidade permanece constante após o lançamento. Essas regras e funcionalidades combinadas proporcionam uma experiência dinâmica e estrategicamente desafiadora, ressaltando a complexidade envolvida na criação de jogos em ambientes embarcados.



<h2>FLUXO DE EXECUÇÃO DO SISTEMA</h2>

O fluxo de execução do sistema do jogo segue uma sequência lógica que abrange desde a conexão e inicialização até as iterações principais do jogo.

Antes da inicialização do programa, o usuário estabelece uma conexão via SSH com a placa FPGA DE1-SoC. Isso pode ser feito através do terminal do sistema operacional do computador através de um comando específico para o acesso. Após a conexão SSH ser estabelecida com sucesso, o usuário pode transferir o código fonte do jogo e os recursos necessários para a placa. Ademais, necessita-se também fazer a conexão da placa com o monitor CRT, através do cabo VGA, que será responsável pela exibição do jogo (Figura X).

O programa se dá com a inicialização de recursos e bibliotecas essenciais, que controlam o sistema de vídeo VGA, módulo de entrada dos botões, display de 7 segmentos para a demonstração das “vidas” do jogador e o acelerômetro. Em seguida, são definidas as estruturas principais do jogo, como a plataforma, a bola e os blocos. 

Essas estruturas, que por sua vez, são consideradas “structs" em C e portanto possuem atributos (como suas dimensões) que servirão para definir o estado daquele objeto. Esses atributos são definidos através de funções logo no início do programa. Dessa forma, tem-se por exemplo, a localização e dimensão das principais estruturas. 

Em seguida, também são definidas algumas funções auxiliares que servirão para controlar o fluxo do programa, como a funções que checam a colisão entre os objetos, funções de exibição dos elementos (estruturais, pontuação, recorde, etc.) na tela e funções de exibição dos estados do jogo (tela de início e tela de fim de jogo).

Após essas etapas de inicialização, o jogo entra em um loop principal que é executado continuamente. Durante cada iteração do loop, o programa lê os dados do acelerômetro para determinar o movimento da plataforma (raquete). As coordenadas da bola são atualizadas com base nas direções dx e dy, determinando seu movimento na tela. 

O programa verifica constantemente as colisões da bola com as paredes, a plataforma e os blocos através das funções auxiliares. Se a bola atinge as paredes, as direções dx e dy são invertidas para simular o reflexo. As Colisões com a plataforma (raquete) também alteram a direção da bola, proporcionando uma jogabilidade interativa. A colisão entre a bola e um bloco resultam em sua destruição, alterando a direção da bola e incrementando a pontuação do jogador.

O programa também lê constantemente o estado do botão para verificar se o jogador pressionou o botão de pausa. Se o botão for pressionado, o jogo entra em um estado de pausa (um loop infinito) até que o botão seja pressionado novamente para retomar o jogo.

O jogo verifica se todos os blocos foram quebrados, reiniciando o layout dos blocos e incrementando a pontuação. Se a bola ultrapassar a plataforma, o número de vidas é decrementado. Se o jogador ficar sem vida, o jogo entra em um estado de game over. Após o término do jogo, uma tela de game over é exibida e o programa aguarda a interação do jogador para reiniciar o jogo.

Ao final do programa, os módulos do acelerômetro, do botão, do display de sete segmentos e do sistema de vídeo VGA são fechados para liberar os recursos utilizados. 


<h2>CONTROLE DOS PRINCIPAIS RECURSOS UTILIZADOS (VGA, BOTÕES E ACELERÔMETRO)</h2>

O controle dos principais recursos utilizados para a confecção do projeto são dados pela biblioteca lintelfpgaup. Através dela, conseguimos manipular alguns dos elementos presentes na placa que auxiliaram no projeto, sendo eles: a saída VGA, os botões, display LCD e o acelerômetro.

<h2>EXIBIÇÃO NA TELA CRT ATRAVÉS DO VGA</h2>

A exibição do jogo e seus elementos na tela é facilitada pela biblioteca lintelfpgaup, que oferece funcionalidades essenciais para manipulação de vídeo no ambiente de sistemas embarcados. O processo de exibição e atualização dos elementos na tela envolvem o uso do pixel buffer e funções como: video_box(), video_clear(), video_show().

O pixel buffer é uma área de memória designada para armazenar a representação gráfica dos elementos do jogo, como a bola, a raquete e os blocos. Ele atua como um espaço intermediário onde as alterações visuais são aplicadas antes de serem refletidas na tela. 

A função video_show() desempenha um papel vital no processo, uma vez que, atualiza a tela com as informações contidas no pixel buffer. Essa função efetua o processo de "swap" entre o Backbuffer e o Buffer Register. Isso significa que, ao escrever ou apagar informações na tela, os valores alterados são inicialmente armazenados no Backbuffer. O video_show() executa o swap, fazendo com que o Buffer Register agora referencie o Backbuffer atualizado, resultando na exibição visual dessas alterações na tela (Figura X). Essa técnica é chamada de Double-Buffering.

Válido ressaltar que a área do pixel buffer é de 320x240, enquanto o monitor utilizado possui uma resolução de 640x480. Dessa forma, entende-se que cada valor do pixel será duplicado nas direções x e y (Figura X).

Ademais, tem-se a função video_box() que é utilizada para desenhar caixas (ou retângulos) na tela, preenchendo determinadas áreas com cores específicas. Nesse contexto, essa função é empregada para renderizar a raquete, a bola, os blocos e outros elementos visuais. As coordenadas e dimensões dos elementos são especificadas como argumentos para posicionar e dimensionar corretamente cada componente do jogo.

A função video_clear(), por sua vez, é responsável por apagar o conteúdo do pixel buffer, preparando-o para receber novas informações. Isso é crucial para evitar sobreposições indesejadas e garantir que apenas os elementos relevantes sejam renderizados na próxima iteração do loop do jogo.

O processo de renderização, portanto, envolve a manipulação cuidadosa do pixel buffer usando as funções mencionadas. À medida que os elementos do jogo são movidos, colidem ou são atualizados, essas funções garantem uma representação visual precisa e dinâmica na tela. Essa abordagem otimizada é essencial para oferecer uma experiência de jogo continua e envolvente aos usuários, especialmente em sistemas embarcados onde os recursos são limitados.


<h2>CRIAÇÃO DAS ESTRUTURAS DO JOGO</h2>

A criação das principais estruturas do jogo envolvem a definição e inicialização de três principais elementos: a plataforma (raquete), a bola e os blocos. 

A plataforma é representada pela estrutura “Plataforma”, que contém as coordenadas (x, y) do canto superior esquerdo e (x2, y2) do canto inferior direito. A função criarRaquete() é responsável pela inicialização da plataforma com base nas coordenadas iniciais.

A bola é representada pela estrutura “Ball", que armazena as coordenadas (x, y) da posição da bola, bem como as variáveis dx e dy que indicam a direção do movimento e size que indica seu tamanho. A função initBall() inicializa as propriedades da bola, como sua posição inicial (no centro da tela) e sua direção.

Os blocos são representados pela estrutura “Block", que armazena as coordenadas (x, y) de cada bloco na matriz de blocos. A matriz de blocos é uma representação visual do layout dos blocos na tela. A função initBlocks() inicializa as propriedades dos blocos, definindo suas posições iniciais e marcando-os como não destruídos.

Essas estruturas formam a base do jogo Breakout, permitindo a representação e manipulação eficaz dos elementos visuais e lógicos do jogo. O código utiliza essas estruturas em conjunto com funções de colisão e manipulação de elementos gráficos para criar uma experiência interativa para o jogador.


<h2>MOVIMENTO DA BOLA E COLISÃO </h2>

O movimento da bola é implementado através da atualização contínua das coordenadas da bola no plano bidimensional (X, Y) durante cada iteração do loop principal. Como dito anteriormente, o código utiliza a estrutura Ball para representar a bola, e as variáveis dx e dy são responsáveis por determinar a direção do movimento nos eixos horizontal e vertical, respectivamente.

No início do jogo, a função initBall() é chamada para inicializar as propriedades da bola. As coordenadas iniciais (x, y) são posicionadas no centro da tela, e as variáveis dx e dy determinam a direção inicial do movimento.

Dentro do loop principal do jogo, as coordenadas da bola são atualizadas continuamente com base nas variáveis dx e dy. A posição (x, y) da bola é modificada de acordo com essas direções, causando seu movimento na tela.

Após cada atualização de posição, o código verifica colisões da bola com as paredes, a raquete e os blocos. Caso uma colisão seja detectada, as direções dx e dy podem ser invertidas ou ajustadas, dependendo do componente com o qual a bola colidiu.

Essencialmente, o movimento da bola é uma combinação da atualização contínua de suas coordenadas e da gestão de colisões com outros elementos do jogo. Isso resulta em um comportamento dinâmico da bola.

A mecânica de colisão é implementada por meio das funções checkCollision() e checkBlockCollision(). Essas funções são cruciais para determinar se a bola colidiu com a raquete, com as paredes ou com os blocos. 

A função checkCollision() é responsável por verificar se a bola colidiu com a raquete. Ela retorna um valor que indica se houve uma colisão e, em caso afirmativo, em qual direção a bola colidiu com a raquete. Ela verifica se a parte inferior da bola (ball->y + 6) está na mesma linha vertical que o topo da raquete (paddle->y). Além disso, verifica se a posição horizontal da bola (ball->x) está dentro dos limites horizontais da raquete (paddle->x e paddle->x2). Dependendo dessas condições, a função retorna um valor indicando a direção da colisão.

A função checkBlockCollision() é utilizada para verificar a colisão da bola com um bloco específico. Ela retorna um valor indicando se a colisão ocorreu na direção vertical ou horizontal. Primeiro a função verifica se o bloco ainda não foi destruído (!bloco->destroyed). Em seguida, verifica se a posição horizontal (bola->x) e vertical (bola->y) da bola está dentro dos limites do bloco. Dependendo dessas condições, a função retorna um valor indicando a direção da colisão.

Essas mecânicas de colisão são fundamentais para o funcionamento do jogo, determinando as reações da bola ao interagir com a raquete, as paredes e os blocos. A lógica dessas funções contribui para uma experiência de jogo dinâmica e envolvente.


<h2>MOVIMENTO DA PLATAFORMA</h2>

O movimento da plataforma no jogo Breakout é possibilitado pela integração do módulo do acelerômetro, que fornece funcionalidades cruciais para a configuração e leitura de dados do dispositivo 3D. As principais funções utilizadas são accel_format(), accel_calibrate(), e accel_read().

A função accel_format() é empregada para configurar o formato de saída do acelerômetro. Nesse contexto, ela é invocada com os parâmetros adequados (1, 2) para garantir que os dados de saída sejam apresentados de maneira coerente, proporcionando informações significativas sobre a aceleração nas três dimensões (X, Y e Z). O primeiro parâmetro define o alcance (range) da leitura do acelerômetro, ou seja, o intervalo máximo de valores que o dispositivo pode fornecer. Valores maiores de range podem capturar acelerações mais intensas. Exemplos comuns de valores para o range são 2, 4, 8 ou 16, indicando o alcance em g (gravidade). O segundo parâmetro define a resolução da leitura, ou seja, a menor mudança detectável no valor da aceleração. Pode ser especificado como 8, 10, 12 ou 14 bits.

A calibração é uma etapa crucial para assegurar a precisão dos dados do acelerômetro. A função accel_calibrate() é responsável por calibrar o sensor, considerando possíveis variações e compensando quaisquer desvios na leitura dos dados. Isso garante uma resposta mais confiável e precisa durante o controle da plataforma no jogo.


A função accel_read() desempenha um papel fundamental ao realizar a leitura dos dados provenientes do acelerômetro. Ela recupera informações sobre a aceleração nas três dimensões, representadas pelos parâmetros ptr_x, ptr_y e ptr_z. Essas leituras são então utilizadas para interpretar a inclinação do dispositivo e, consequentemente, movimentar a plataforma horizontalmente no jogo.

O processo inicia com a captura das leituras do acelerômetro, mais especificamente do eixo horizontal (X), representando os movimentos laterais do jogador. O valor obtido, após a calibração, é então processado para determinar a direção do movimento da plataforma. Caso a leitura indique uma inclinação para a esquerda, a posição da plataforma é ajustada para a esquerda; similarmente, para uma inclinação para a direita, a plataforma se move para a direita.

Dessa forma, a utilização coordenada dessas funções do módulo do acelerômetro possibilita uma resposta fluida e precisa aos movimentos físicos do jogador que serão transmitidos para a plataforma dentro do jogo.


<h2>PAUSE</h2>
A mecânica de pausa no jogo Breakout é implementada para permitir que o jogador interrompa temporariamente o jogo e, posteriormente, retome a jogabilidade. 

Durante o loop principal do jogo, o programa constantemente lê o estado do botão.
Se o botão correspondente à pausa for pressionado, o jogo entra em um estado de pausa, ou seja, o código entra em um loop infinito que representa o estado de pausa. Dentro desse loop de pausa, o jogo continua a ler o estado do botão. Quando o botão para a pausa é acionado novamente, o código sai do loop, retomando assim o fluxo normal do jogo.

Essa mecânica de pausa permite que o jogador tenha controle sobre o ritmo do jogo, proporcionando uma experiência mais flexível e adaptada às suas preferências. O uso do botão de pausa é uma característica comum em jogos para oferecer maior interatividade e conveniência ao jogador.


<h2>MECÂNICA DE VIDAS</h2>

A mecânica de vidas no jogo Breakout implementado em C segue um padrão comum em jogos arcade. O jogo começa com um número inicial de vidas, neste caso, 3. A posição da bola é monitorada, e se ela ultrapassar uma determinada altura na tela (238 no caso), indica que a bola escapou da área da plataforma. Nesse ponto, o número de vidas é decrementado.

A exibição do número atual de vidas acontece através do display de 7 segmentos. Entre as funções fornecidas pela biblioteca lintelfpgaup, tem-se a função HEX_set(). Ela é responsável por atualizar o display de 7 segmentos com o valor atual da variável “vidas". Nesse caso, ela converte o valor numérico em uma representação adequada para o display de 7 segmentos. Cada segmento do display é controlado individualmente para formar os dígitos desejados.

Quando o número de vidas atinge zero, o jogo entra em um estado de "Game Over", onde o jogador pode interagir para reiniciar o jogo.


<h1 id="descricao-e-analise-dos-testes" align="center">Descrição e Análise dos Testes e Simulações, Resultados e Discussões</h1>

<h1 id="conclusao" align="center">Conclusão</h1>

A execução bem-sucedida deste projeto destaca a valiosa aprendizagem obtida ao enfrentar desafios no desenvolvimento de jogos em sistemas embarcados com recursos limitados. A integração eficaz entre o acelerômetro, os botões e a interface VGA no Kit FPGA DE1-SoC não apenas resultou em uma experiência de jogo fluida e responsiva, mas também proporcionou insights valiosos sobre a otimização de recursos em ambientes computacionais embarcados.

A escolha da linguagem C para a implementação do projeto destaca sua versatilidade, mostrando que é possível criar aplicações complexas mesmo em ambientes restritos. Ao cumprir as restrições impostas e alcançar resultados satisfatórios, o desenvolvedor não apenas aplicou conhecimentos teóricos, mas também desenvolveu habilidades práticas na manipulação eficiente de recursos e na solução de problemas específicos de sistemas embarcados.

O aprendizado derivado deste projeto vai além da simples realização técnica, pois envolve a compreensão profunda da interação entre hardware e software, bem como a importância da otimização para alcançar um desempenho eficiente. Essa experiência prática fortaleceu a capacidade do desenvolvedor de enfrentar desafios complexos e de aplicar criatividade e engenhosidade para superar limitações, preparando-o de maneira robusta para futuros projetos e oportunidades no campo dos sistemas embarcados.


<h1 id="bibliografia" align="center">Bibliografia</h1>

<h1 id="script-de-compilacao" align="center">Uso do projeto</h1>
