#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL_ttf.h>
 
#define FPS 12
 
const int WIDTH               = 800;
const int HEIGHT              = 600;
const int BPP                 = 32;
 
int jogoRodando               = 1;
int teclaDireita              = 0;
int pulo                      = 0;
int teste                     = 0;
int ativa_bomba               = 0;
int ativa_bomba4              = 0;
int ativa_bomba2              = 0;
int tela_abertura             = 1;
int contadorAbertura          = 0;
int contador_historia         = 0;
int win                       = 0;
int subida                    = 0;
int conta_colisao             = 0;
int conta_menu                = 0;
int teclaEsquerda             = 0;
int teclaCima                 = 0;
int teclaBaixo                = 0;
 
float score = 0.0;
 
int subindo = 0;
 
SDL_Surface *bender           = NULL;
SDL_Surface *fundo            = NULL;
SDL_Surface *fim              = NULL;
SDL_Surface *bomba            = NULL;
SDL_Surface *bomba2           = NULL;
SDL_Surface *screen           = NULL;
SDL_Surface *plataforma       = NULL;
SDL_Surface *fundomenu        = NULL;
SDL_Surface *winner           = NULL;
SDL_Surface *devil            = NULL;
SDL_Surface *fry              = NULL;
SDL_Surface *duff2            = NULL;
SDL_Surface *boa              = NULL;
SDL_Surface *historia         = NULL;
SDL_Surface *placa            = NULL;
SDL_Surface *escada           = NULL;
SDL_Surface *cano_esquerda    = NULL;
SDL_Surface *cano_direita     = NULL;
SDL_Surface *duff             = NULL;
SDL_Surface *escada_quebrada  = NULL;
Mix_Music   *musica_principal = NULL;
TTF_Font *fonte;
 
SDL_Event event;
 
int larguratotal       = 5099;
int alturatotal        = 54;
int largurabomba_total = 630;
int alturabomba_total  = 20;
int largura_duff       = 183;
int altura_duff        = 15;
int largura_fry        = 581;
int altura_fry         = 81;
int contPulo           = 0;
int largura_devil      = 279;
int altura_devil       = 73;
int largura_fundo      = 4000;
int altura_fundo       = 600;
int largura_placa      = 691;
int altura_placa       = 68;
int largura_duff2       = 135;
int altura_duff2       = 24;
 
 
int telaMenu = 1;
int opcaoMenu = 0;
int telaTutorial = 0;
int telaCredito = 0;
 
SDL_Surface *iniciar ;
SDL_Surface *tutorial;
SDL_Surface *creditos ;
SDL_Surface *nave;
SDL_Surface *menuFundo ;
 
 
SDL_Rect destino[3];
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                         Uint32 start;
 
void desenhaTexto(char* texto, SDL_Surface* dst, int x, int y, SDL_Color cor)
{
    SDL_Surface* src = TTF_RenderText_Blended(fonte, texto, cor);
    SDL_Rect dst_rect = {x, y, 0, 0};
 
    SDL_BlitSurface(src, 0, dst, &dst_rect);
 
    SDL_FreeSurface(src);
}
 
 
void draw_player(float srcX, float srcY, float dstX, float dstY, int width, int height, SDL_Surface* source, SDL_Surface* destination)
{
 //Qual frame eu vou pegar
   SDL_Rect sourc, destino;
   sourc.x = srcX;
   sourc.y = srcY;
   sourc.w = width;
   sourc.h = height;
 // Coloca na posição na tela
   destino.x = dstX;
   destino.y = dstY;
   destino.w = width;
   destino.h = height;
 
   SDL_BlitSurface(source, &sourc, destination, &destino);
 
}
void draw_objeto(float srcX, float srcY, float dstX, float dstY, int width, int height, SDL_Surface* source, SDL_Surface* destination)
{
   SDL_Rect sourc, destino;
   sourc.x = srcX;
   sourc.y = srcY;
   sourc.w = width;
   sourc.h = height;
 
   destino.x = dstX;
   destino.y = dstY;
   destino.w = width;
   destino.h = height;
 
   SDL_BlitSurface(source, &sourc, destination, &destino);
 
}
 
typedef struct OBJETO Objeto;
struct OBJETO
{
     float sx, sy, dx, dy;
     int largura, altura;
 
};
//  O primeiro 'Objeto' representa a  estrutura pelo seu apelido  e o segundo 'objeto' representa a varialvel
Objeto objeto, objeto_escada, objeto_escada2,  objeto_escada3, objeto_escada4, objeto_plataforma, objeto_plataforma2, objeto_plataforma3, objeto_plataforma4, objeto_cano, objeto_cano2,
objeto_cano3, objeto_cano4, objeto_cano5, objeto_cano6, objeto_cano7, objeto_cano8, objeto_duff, objeto_duff2, objeto_devil, objeto_fry, objeto_nave, objeto_fundo, objeto_placa,
objeto_duff3, objeto_boa;
 
typedef struct PLAYER Player;
struct PLAYER
{
     float sx, sy, dx, dy, velx, vely;
     int largura, altura, pulo;
};
// O primeiro 'Player' representa a estrutura e o pelo seu apelido e o  segundo ' player' representa a variavel , outra forma seria no lugar do ' Player player' usar 'struct PLAYER player'
PLAYER player;
 
typedef struct BOMBA Bomba;
struct BOMBA
{
     float sx, sy, dx, dy, velx, vely;
     int largura, altura;
 
};
 
Bomba bomba_objeto, bomba_objeto2, bomba_objeto3, bomba_objeto4, bomba_objeto5;
 
void plataforma_info()
{
 
   objeto_plataforma.sx = 0; objeto_plataforma.sy = 0;
   objeto_plataforma.dx = 25; objeto_plataforma.dy = 484;
   objeto_plataforma.largura = 728; objeto_plataforma.altura = 34;
 
   objeto_plataforma2.sx = 0; objeto_plataforma2.sy = 0;
   objeto_plataforma2.dx = 25; objeto_plataforma2.dy = 378;
   objeto_plataforma2.largura = 728; objeto_plataforma2.altura = 34;
 
   objeto_plataforma3.sx = 0; objeto_plataforma3.sy = 0;
   objeto_plataforma3.dx = 25; objeto_plataforma3.dy = 272;
   objeto_plataforma3.largura = 728; objeto_plataforma3.altura = 34;
 
   objeto_plataforma4.sx = 0; objeto_plataforma4.sy = 0;
   objeto_plataforma4.dx = 25; objeto_plataforma4.dy = 167;
   objeto_plataforma4.largura = 728; objeto_plataforma4.altura = 34;
 
   objeto_duff.sx = 0; objeto_duff.sy = 0;
   objeto_duff.dx = 500 ; objeto_duff.dy =430;
   objeto_duff.largura = 13; objeto_duff.altura = 15;
 
    objeto_duff2.sx = 0; objeto_duff2.sy = 0;
   objeto_duff2.dx = 300 ; objeto_duff2.dy =330;
   objeto_duff2.largura = 13; objeto_duff2.altura = 15;
 
   objeto_devil.sx = 0; objeto_devil.sy = 0;
   objeto_devil.dx = 30 ; objeto_devil.dy = 94;
   objeto_devil.largura = 69.75; objeto_devil.altura = 73;
 
   objeto_fry.sx = 0; objeto_fry.sy = 0;
   objeto_fry.dx = 350 ; objeto_fry.dy = 88;
   objeto_fry.largura = 93,5; objeto_fry.altura = 81;
 
   objeto_fundo.sx = 0; objeto_fundo.sy = 0;
   objeto_fundo.dx = 0 ; objeto_fundo.dy = 0;
   objeto_fundo.largura = 800; objeto_fundo.altura = 600;
 
   objeto_placa.sx = 0; objeto_placa.sy = 0;
   objeto_placa.dx = 150 ; objeto_placa.dy = 187;
   objeto_placa.largura = 86,37; objeto_placa.altura = 68;
 
 
   objeto_duff3.sx = 0; objeto_duff3.sy = 0;
   objeto_duff3.dx = 150 ; objeto_duff3.dy = 550;
   objeto_duff3.largura = 12.27; objeto_duff3.altura = 24;
 
   objeto_boa.sx = 0; objeto_boa.sy = 0;
   objeto_boa.dx = 650 ; objeto_boa.dy = 230 ;
   objeto_boa.largura = 12.27; objeto_boa.altura = 24;
 
 
 
}
void bombainfo()
{
    bomba_objeto.largura = 57; bomba_objeto.altura = 20;;
    bomba_objeto.sx = 0, bomba_objeto.sy = 0, bomba_objeto.dx = 50, bomba_objeto.dy = 145,bomba_objeto.velx = 10, bomba_objeto.vely =10.5;
 
    bomba_objeto2.largura = 57; bomba_objeto2.altura = 20;;
    bomba_objeto2.sx = 0, bomba_objeto2.sy = 0, bomba_objeto2.dx = 55, bomba_objeto2.dy = 145,bomba_objeto2.velx = 10, bomba_objeto2.vely =10.5;
 
    bomba_objeto3.largura = 57; bomba_objeto3.altura = 20;
    bomba_objeto3.sx = 0, bomba_objeto3.sy = 0, bomba_objeto3.dx = 0, bomba_objeto3.dy = 357,bomba_objeto3.velx = 10, bomba_objeto3.vely =10.5;
 
    bomba_objeto4.largura = 57; bomba_objeto4.altura = 20;
    bomba_objeto4.sx = 0, bomba_objeto4.sy = 0, bomba_objeto4.dx = 750, bomba_objeto4.dy = 250,bomba_objeto4.velx = 10, bomba_objeto4.vely =10.5;
 
    bomba_objeto5.largura = 57; bomba_objeto5.altura = 20;
    bomba_objeto5.sx = 0, bomba_objeto5.sy = 0, bomba_objeto5.dx = 750, bomba_objeto5.dy = 460 ,bomba_objeto5.velx = 10, bomba_objeto5.vely =10.5;
 
 
}
 
 
 
void objetoinfo()
{
    // o ponto '.' é para acessar cada variável da estrutura
    objeto.largura = 698, objeto.altura = 38;
    objeto.sx =0, objeto.sy = 0, objeto.dx = 45, objeto.dy = 80;
 
    objeto_escada.largura = 25 , objeto_escada.altura = 86;
    objeto_escada.sx =0, objeto_escada.sy = 0, objeto_escada.dx = 300, objeto_escada.dy = 504;
 
    objeto_escada2.largura = 25 , objeto_escada2.altura = 86;
    objeto_escada2.sx =0, objeto_escada2.sy = 0, objeto_escada2.dx = 170, objeto_escada2.dy = 398;
 
    objeto_escada3.largura = 25 , objeto_escada3.altura = 86;
    objeto_escada3.sx =0, objeto_escada3.sy = 0, objeto_escada3.dx = 560, objeto_escada3.dy = 293;
 
    objeto_escada4.largura = 25 , objeto_escada4.altura = 86;
    objeto_escada4.sx =0, objeto_escada4.sy = 0, objeto_escada4.dx = 250, objeto_escada4.dy = 187;
 
    objeto_cano.largura = 61 , objeto_cano.altura = 61;
    objeto_cano.sx =0, objeto_cano.sy = 0, objeto_cano.dx = 0, objeto_cano.dy = 432;
 
    objeto_cano2.largura = 61 , objeto_cano2.altura = 61;
    objeto_cano2.sx =0, objeto_cano2.sy = 0, objeto_cano2.dx = 0, objeto_cano2.dy = 327;
 
    objeto_cano3.largura = 61 , objeto_cano3.altura = 61;
    objeto_cano3.sx =0, objeto_cano3.sy = 0, objeto_cano3.dx = 0, objeto_cano3.dy = 220;
 
    objeto_cano4.largura = 61 , objeto_cano4.altura = 61;
    objeto_cano4.sx =0, objeto_cano4.sy = 0, objeto_cano4.dx = 0, objeto_cano4.dy = 540;
 
    objeto_cano5.largura = 61 , objeto_cano5.altura = 61;
    objeto_cano5.sx =0, objeto_cano5.sy = 0, objeto_cano5.dx = 740, objeto_cano5.dy = 220;
 
    objeto_cano6.largura = 61 , objeto_cano6.altura = 61;
    objeto_cano6.sx =0, objeto_cano6.sy = 0, objeto_cano6.dx = 740, objeto_cano6.dy = 432;
 
    objeto_cano7.largura = 61 , objeto_cano7.altura = 61;
    objeto_cano7.sx =0, objeto_cano7.sy = 0, objeto_cano7.dx = 740, objeto_cano7.dy = 327;
 
    objeto_cano8.largura = 61 , objeto_cano8.altura = 61;
    objeto_cano8.sx =0, objeto_cano8.sy = 0, objeto_cano8.dx = 740, objeto_cano8.dy = 115;
 
   objeto_fundo.sx = 0; objeto_fundo.sy = 0;
   objeto_fundo.dx = 0 ; objeto_fundo.dy = 0;
   objeto_fundo.largura = 800; objeto_fundo.altura = 600;
 
 
}
 
void playerInfo()
{
    player.largura = 42; player.altura = 69, player.pulo = 0;
    player.sx =0, player.sy = 0, player.dx = 750, player.dy = 525, player.velx = 10, player.vely =7;
}
 
void SONG()
{
 Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 2048 );
 musica_principal = Mix_LoadMUS("musica-principal.mp3");
 Mix_PlayMusic(musica_principal, -1);
 Mix_VolumeMusic(40);
 
 
}
void LOAD_FILES()
{
    Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 2048 );
    bender           = IMG_Load("bender-direita.png");
    fundo            = IMG_Load("background.png");
    plataforma       = IMG_Load("plataforma.png");;
    escada           = IMG_Load("escada.png");
    escada_quebrada  = IMG_Load("escadaq.png");
    escada           = IMG_Load("escada.png");
    winner           = IMG_Load("ganhar.png");
    devil            = IMG_Load("devil.png");
    bomba2           = IMG_Load("bomba2.png");
    duff2            = IMG_Load("duff2.png");
    fry              = IMG_Load("fry.png");
    placa            = IMG_Load("placa.png");
    boa              = IMG_Load("boa.png");
    fundomenu        = IMG_Load("fundo2.png");
    historia         = IMG_Load("historia.png");
    bomba            = IMG_Load("bomba.png");
    fim              = IMG_Load("fim.png");
    cano_esquerda    = IMG_Load("cano_es.png");
    duff             = IMG_Load("duff.png");
    cano_direita     = IMG_Load("cano_di.png");
    screen           = SDL_SetVideoMode(WIDTH, HEIGHT ,BPP, SDL_SWSURFACE);
 
}
 
 
void INIT()
{
    LOAD_FILES();
    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();
    playerInfo();
    objetoinfo();
    SONG();
    plataforma_info();
    bombainfo();
 
}
 int COLISAO(Player player, Objeto objeto) // Player player  é como se fosse meu rect, o mesmo para Objeto objeto
{
 
    if((player.dx < objeto.dx + objeto.largura) && ( player.dx+player.largura > objeto.dx) && (player.dy < objeto.dy + objeto.altura)
     && ( player.dy+player.altura) > (objeto.dy))
      return 1;
 
    else
      return 0;
 
 
}
 
 int COLISAO_BOMBA(Player player, Bomba bomba)
 {
 
     if((player.dx < bomba.dx + bomba.largura) && ( player.dx+player.largura > bomba.dx) && (player.dy < bomba.dy + bomba.altura)
     && ( player.dy+player.altura) > (bomba.dy))
      return 1;
 
    else
      return 0;
 
 
}
void ANIMA_BOMBA()
{
  bomba_objeto.sx  += bomba_objeto.largura;
  bomba_objeto2.sx += bomba_objeto2.largura;
  bomba_objeto3.sx += bomba_objeto3.largura;
  bomba_objeto4.sx += bomba_objeto4.largura;
  bomba_objeto5.sx += bomba_objeto5.largura;
 
  objeto_placa.sx  += objeto_placa.largura;
  objeto_fry.sx    +=  objeto_fry.largura;
  objeto_devil.sx  +=  objeto_devil.largura;
 
 objeto_duff3.sx   += objeto_duff3.largura;
 
 objeto_boa.sx   += objeto_boa.largura;
 
 
   if(objeto_boa.sx > largura_duff2 - objeto_boa.largura)
            objeto_boa.sx = 0;
 
   if(objeto_duff3.sx > largura_duff2 - objeto_duff3.largura)
            objeto_duff3.sx = 0;
 
   if(objeto_placa.sx > largura_placa - objeto_placa.largura)
            objeto_placa.sx = 0;
 
    if(objeto_devil.sx > largura_devil - objeto_devil.largura)
            objeto_devil.sx = 0;
 
    if(objeto_fry.sx > largura_fry - objeto_fry.largura)
            objeto_fry.sx = 0;
 
 
    if(bomba_objeto4.sx > largurabomba_total - bomba_objeto4.largura)
            bomba_objeto4.sx = 0;
 
    if(bomba_objeto.sx > largurabomba_total - bomba_objeto.largura)
            bomba_objeto.sx = 0;
 
    if(bomba_objeto2.sx > largurabomba_total - bomba_objeto2.largura)
            bomba_objeto2.sx = 0;
 
    if(bomba_objeto5.sx > largurabomba_total - bomba_objeto5.largura)
            bomba_objeto3.sx = 0;
 
  if(bomba_objeto5.sx > largurabomba_total - bomba_objeto3.largura)
            bomba_objeto5.sx = 0;
 
    if(bomba_objeto.dx >= 750 & bomba_objeto.dy == 145)
    {
      bomba_objeto.dy = 570;
      bomba_objeto.dx = 0;
    }
 
    if(bomba_objeto.dx >= 750 & bomba_objeto.dy == 570)
    {
      bomba_objeto.dy = 145;
      bomba_objeto.dx = 0;
    }
 
 
 
}
void ANIMA_PLATAFORMA()
{
 
      objeto_plataforma4.sx += objeto_plataforma4.largura;
 
    if(objeto_plataforma4.sx > larguratotal - objeto_plataforma4.largura)
            objeto_plataforma4.sx = 0;
 
    objeto_plataforma3.sx += objeto_plataforma3.largura;
 
    if(objeto_plataforma3.sx > larguratotal - objeto_plataforma3.largura)
            objeto_plataforma3.sx = 0;
 
 
    objeto_plataforma2.sx += objeto_plataforma2.largura;
 
    if(objeto_plataforma2.sx > larguratotal - objeto_plataforma2.largura)
            objeto_plataforma2.sx = 0;
 
    objeto_plataforma.sx += objeto_plataforma.largura;
 
    if(objeto_plataforma.sx > larguratotal - objeto_plataforma.largura)
            objeto_plataforma.sx = 0;
 
     objeto_duff.sx += objeto_duff.largura;
 
    if(objeto_duff.sx > largura_duff - objeto_duff.largura)
            objeto_duff.sx = 0;
 
     objeto_duff2.sx += objeto_duff2.largura;
 
    if(objeto_duff2.sx > largura_duff - objeto_duff2.largura)
            objeto_duff2.sx = 0;
 
 
}
 
void ANIMA_FUNDO()
{
    objeto_fundo.sx +=  objeto_fundo.largura;
 
    if(objeto_fundo.sx >= 5600 && objeto_fundo.sy == 0)
     {
        objeto_fundo.sx = 0;
        objeto_fundo.sy = 600;
 
     }
 
    if(objeto_fundo.sx >= 5600 && objeto_fundo.sy == 600)
     {
        objeto_fundo.sx = 0;
        objeto_fundo.sy = 1200;
 
     }
 
    if(objeto_fundo.sx >= 5600 && objeto_fundo.sy == 1200)
     {
        objeto_fundo.sx = 0;
        objeto_fundo.sy = 1800;
 
     }
 
    if(objeto_fundo.sx >= 5600 && objeto_fundo.sy == 1800)
     {
        objeto_fundo.sx = 0;
        objeto_fundo.sy = 2400;
 
     }
 
 
    if(objeto_fundo.sx >= 5600 && objeto_fundo.sy == 2400)
     {
        objeto_fundo.sx = 0;
        objeto_fundo.sy = 3000;
 
     }
 
        if(objeto_fundo.sx >= 5600 && objeto_fundo.sy == 3000)
     {
        objeto_fundo.sx = 0;
        objeto_fundo.sy = 3600;
 
     }
 
 
       if(objeto_fundo.sx >= 5600 && objeto_fundo.sy == 3600)
     {
        objeto_fundo.sx = 0;
        objeto_fundo.sy = 0;
 
     }
 
 
 
}
 
void andar()
{
     if(teclaDireita)
    {
        SDL_Surface *aux = bender;
        bender = IMG_Load("bender-direita.png");
        SDL_FreeSurface(aux);
        player.sx += player.largura; //Andar pelo frame
        player.dx += player.velx;   // andar pelo eixo
    }
 
     if(teclaEsquerda)
    {
        SDL_Surface *aux = bender;
        bender = IMG_Load("bender-esquerda.png");
        SDL_FreeSurface(aux);
        player.sx -= player.largura;
        player.dx -= player.velx;
    }
}
 
bool eventoTeclado()
{
       if(SDL_PollEvent(&event))
    {
        if(event.type == SDL_QUIT) exit(0);
 
        if(event.type == SDL_KEYDOWN)
        {
            switch(event.key.keysym.sym)
            {
                case SDLK_RIGHT: if(!((COLISAO(player, objeto_escada) || player.dy > 416 && player.dx == 290) &&
                                  (COLISAO(player, objeto_escada2) || player.dy > 312 && player.dx == 160) &&
                                 (COLISAO(player, objeto_escada3) || player.dy > 205 && player.dx == 547) &&
                                  (COLISAO(player, objeto_escada4)|| player.dy > 100 && player.dx == 240))){teclaDireita = 1;}
 
 
                     break;
                case SDLK_LEFT: if(!((COLISAO(player, objeto_escada) || player.dy > 416 && player.dx == 290) &&
                                  (COLISAO(player, objeto_escada2) || player.dy > 312 && player.dx == 160) &&
                                 (COLISAO(player, objeto_escada3) || player.dy > 205 && player.dx == 547) &&
                                  (COLISAO(player, objeto_escada4)|| player.dy > 100 && player.dx == 240))){teclaEsquerda = 1;}
 
                     break;
                case SDLK_ESCAPE: jogoRodando = 0;
                     break;
               case SDLK_UP:
                              if(COLISAO(player, objeto_escada) || COLISAO(player, objeto_escada2) ||
                                 COLISAO(player, objeto_escada3) ||COLISAO(player, objeto_escada4) &&
                                player.dy >= 100 && player.dx == 240 || player.dy >= 416 && player.dx == 290 ||
                                player.dy >= 312 && player.dx == 160 || player.dy >= 205 && player.dx == 547    ){
                                 teclaCima = 1;
                                 subindo = 1;
                              bender = IMG_Load("bender2.png");
                              player.sy = 368-73.6;
 
                                 }
 
                              break;
                case SDLK_DOWN:
                             if(COLISAO(player, objeto_escada) || COLISAO(player, objeto_escada2) ||
                                 COLISAO(player, objeto_escada3) ||COLISAO(player, objeto_escada4) &&
                                player.dy >= 100 && player.dx == 240 || player.dy >= 416 && player.dx == 290 ||
                                player.dy >= 312 && player.dx == 160 || player.dy >= 205 && player.dx == 547    ){
                                    teclaBaixo = 1;
                                    subindo = 1;
                              bender = IMG_Load("bender2.png");
                              player.sy = 368-73.6;
                                }
 
                              break;
                case SDLK_SPACE: pulo = 1, subida  =1 ;
 
                case SDLK_RETURN: if(teste){telaMenu = 1;
                                            teste = 0;
                                            INIT();}
 
                       if(win == 1)
                        {
                         win = 0;
                    score=0;
                    INIT();
                             telaMenu = 1;
                        }
                                            break;
 
 
            }
        }
 
         if(event.type == SDL_KEYUP)
        {
            switch(event.key.keysym.sym)
            {
                case SDLK_RIGHT: teclaDireita = 0;
                    player.sx = 0;
                     break;
                case SDLK_LEFT: teclaEsquerda = 0;
                     player.sx = 126;
                     break;
                case SDLK_UP:   teclaCima = 0;
                     break;
                case SDLK_DOWN: teclaBaixo = 0;
                     break;
 
            }
        }
 
    }
 
    andar();
 
}
void MOVIMENTO_SPRITE()
{
 
  if(teclaDireita)
     {
        if(player.sx >126)
        player.sx = 42;
        if(player.sx < 42)
        player.sx = 126;
 
     }
    if(teclaEsquerda)
    {
    if(player.sx > 84)
        player.sx = 0;
    if(player.sx < 0)
       player.sx = 84;
    }
 
 
}
void LIMITES_TELA()
{
 
    if(player.dx >= 700)
    {
        player.dx = 700;
    }
 
    if(player.dx <= 61 )
    {
      player.dx = 61;
    }
}
 
void CLEAN_UP()
{
 
    SDL_FreeSurface(fundo);
    SDL_FreeSurface(plataforma);
    SDL_FreeSurface(bender);
    SDL_FreeSurface(escada);
    SDL_FreeSurface(devil);
    SDL_FreeSurface(fry);
    SDL_FreeSurface(historia);
    SDL_FreeSurface(bomba);
    SDL_FreeSurface(duff2);
    SDL_FreeSurface(boa);
    SDL_FreeSurface(placa);
    SDL_FreeSurface(bomba2);
    SDL_FreeSurface(winner);
    SDL_FreeSurface(cano_esquerda);
    SDL_FreeSurface(fim);
    SDL_FreeSurface(fundomenu);
    SDL_FreeSurface(escada_quebrada);
    SDL_Quit();
 
}
void DRAW()
{
    draw_objeto(objeto_fundo.sx, objeto_fundo.sy, objeto_fundo.dx, objeto_fundo.dy, objeto_fundo.largura, objeto_fundo.altura, fundo, screen);
    draw_objeto(objeto_plataforma.sx, objeto_plataforma.sy, objeto_plataforma.dx, objeto_plataforma.dy, objeto_plataforma.largura, objeto_plataforma.altura, plataforma, screen);
    draw_objeto(objeto_duff.sx, objeto_duff.sy, objeto_duff.dx, objeto_duff.dy, objeto_duff.largura, objeto_duff.altura, duff, screen);
    draw_objeto(objeto_duff3.sx, objeto_duff3.sy, objeto_duff3.dx, objeto_duff3.dy, objeto_duff3.largura, objeto_duff3.altura, duff2 , screen);
    draw_objeto(objeto_boa.sx, objeto_boa.sy, objeto_boa.dx, objeto_boa.dy, objeto_boa.largura, objeto_boa.altura, boa , screen);
    draw_objeto(objeto_duff2.sx, objeto_duff2.sy, objeto_duff2.dx, objeto_duff2.dy, objeto_duff2.largura, objeto_duff2.altura, duff, screen);
    draw_objeto(objeto_plataforma4.sx, objeto_plataforma4.sy, objeto_plataforma4.dx, objeto_plataforma4.dy, objeto_plataforma4.largura, objeto_plataforma4.altura, plataforma, screen);
    draw_objeto(objeto_placa.sx, objeto_placa.sy, objeto_placa.dx, objeto_placa.dy, objeto_placa.largura, objeto_placa.altura, placa , screen);
    draw_objeto(bomba_objeto.sx, bomba_objeto.sy, bomba_objeto.dx , bomba_objeto.dy , bomba_objeto.largura, bomba_objeto.altura , bomba, screen);
    draw_objeto(bomba_objeto2.sx, bomba_objeto2.sy, bomba_objeto2.dx , bomba_objeto2.dy , bomba_objeto2.largura, bomba_objeto2.altura , bomba, screen);
    draw_objeto(bomba_objeto3.sx, bomba_objeto3.sy, bomba_objeto3.dx , bomba_objeto3.dy , bomba_objeto3.largura, bomba_objeto3.altura , bomba, screen);
    draw_objeto(bomba_objeto4.sx, bomba_objeto4.sy, bomba_objeto4.dx , bomba_objeto4.dy , bomba_objeto4.largura, bomba_objeto4.altura , bomba2, screen);
    draw_objeto(bomba_objeto5.sx, bomba_objeto5.sy, bomba_objeto5.dx , bomba_objeto5.dy , bomba_objeto5.largura, bomba_objeto5.altura , bomba2, screen);
    draw_objeto(objeto_cano.sx, objeto_cano.sy, objeto_cano.dx, objeto_cano.dy, objeto_cano.largura, objeto_cano.altura, cano_esquerda, screen);
    draw_objeto(objeto_cano2.sx, objeto_cano2.sy, objeto_cano2.dx, objeto_cano2.dy, objeto_cano2.largura, objeto_cano2.altura, cano_esquerda, screen);
    draw_objeto(objeto_cano3.sx, objeto_cano3.sy, objeto_cano3.dx, objeto_cano3.dy, objeto_cano3.largura, objeto_cano3.altura, cano_esquerda, screen);
    draw_objeto(objeto_cano4.sx, objeto_cano4.sy, objeto_cano4.dx, objeto_cano4.dy, objeto_cano4.largura, objeto_cano4.altura, cano_esquerda, screen);
    draw_objeto(objeto_cano5.sx, objeto_cano5.sy, objeto_cano5.dx, objeto_cano5.dy, objeto_cano5.largura, objeto_cano5.altura, cano_direita, screen);
    draw_objeto(objeto_cano6.sx, objeto_cano6.sy, objeto_cano6.dx, objeto_cano6.dy, objeto_cano6.largura, objeto_cano6.altura, cano_direita, screen);
    draw_objeto(objeto_cano7.sx, objeto_cano7.sy, objeto_cano7.dx, objeto_cano7.dy, objeto_cano7.largura, objeto_cano7.altura, cano_direita, screen);
    draw_objeto(objeto_cano8.sx, objeto_cano8.sy, objeto_cano8.dx, objeto_cano8.dy, objeto_cano8.largura, objeto_cano8.altura, cano_direita, screen);
    draw_objeto(objeto_plataforma3.sx, objeto_plataforma3.sy, objeto_plataforma3.dx, objeto_plataforma3.dy, objeto_plataforma3.largura, objeto_plataforma3.altura, plataforma, screen);
    draw_objeto(objeto_plataforma2.sx, objeto_plataforma2.sy, objeto_plataforma2.dx, objeto_plataforma2.dy, objeto_plataforma2.largura, objeto_plataforma2.altura, plataforma, screen);
    draw_objeto(objeto_escada.sx, objeto_escada.sy, objeto_escada.dx , objeto_escada.dy ,objeto_escada.largura,objeto_escada.altura , escada, screen);
    draw_objeto(objeto_escada2.sx, objeto_escada2.sy, objeto_escada2.dx , objeto_escada2.dy ,objeto_escada2.largura,objeto_escada2.altura , escada, screen);
    draw_objeto(objeto_escada3.sx, objeto_escada3.sy, objeto_escada3.dx , objeto_escada3.dy ,objeto_escada3.largura,objeto_escada3.altura , escada, screen);
    draw_objeto(objeto_escada4.sx, objeto_escada4.sy, objeto_escada4.dx , objeto_escada4.dy ,objeto_escada4.largura,objeto_escada4.altura , escada, screen);
    draw_objeto(objeto.sx, objeto.sy, 500, 188, 25, 96, escada_quebrada, screen);
    draw_objeto(objeto.sx, objeto.sy, 100, 293, 25, 96, escada_quebrada, screen);
    draw_objeto(objeto.sx, objeto.sy, 430, 398, 25, 96, escada_quebrada, screen);
    draw_objeto(objeto_devil.sx, objeto_devil.sy, objeto_devil.dx, objeto_devil.dy, objeto_devil.largura, objeto_devil.altura, devil, screen);
    draw_objeto(objeto_fry.sx, objeto_fry.sy, objeto_fry.dx, objeto_fry.dy, objeto_fry.largura, objeto_fry.altura,fry, screen);
    draw_player(player.sx, player.sy, player.dx, player.dy, player.largura, player.altura, bender, screen);
 
 
}
 
void inicializaMenu(){
 
iniciar = IMG_Load("jogar.png");
tutorial = IMG_Load("tutorial.png");
nave    = IMG_Load("nave.png");
creditos = IMG_Load("creditos.png");
menuFundo = IMG_Load("menu_fundo.png");
 
destino[0].x = 400 ;
destino[0].y = 250;
 
destino[1].x = 400 ;
destino[1].y = 350;
 
destino[2].x = 400 ;
destino[2].y = 410;
 
objeto_nave.sx = 0;
objeto_nave.sy = 0;
objeto_nave.dx = 400-150;
objeto_nave.dy = 250;
objeto_nave.largura = 130;
objeto_nave.altura = 50;
 
 
}
 
 
 
bool eventoTecladoMenu()
{
       if(SDL_PollEvent(&event))
    {
        if(event.type == SDL_QUIT) exit(0);
 
        if(event.type == SDL_KEYDOWN)
        {
            switch(event.key.keysym.sym)
            {
 
                case SDLK_ESCAPE: jogoRodando = 0;
                     break;
               case SDLK_UP:  if(!telaTutorial && !telaCredito) opcaoMenu -=1;
 
                              break;
                case SDLK_DOWN: if(!telaTutorial && !telaCredito) opcaoMenu +=1;
 
                              break;
                case SDLK_RETURN: if(opcaoMenu == 0)
                                                    telaMenu = 0;
                                                    else if(opcaoMenu == 1){
                                                      if(!telaTutorial){
                                                      telaTutorial = 1;
                                                      SDL_Surface* aux = menuFundo;
                                                      menuFundo = IMG_Load("MENU_tutorial.png");
                                                      SDL_FreeSurface(aux);
                                                    }
                                                      else{
                                                        telaTutorial = 0;
 
                                                        SDL_Surface* aux = menuFundo;
                                                      menuFundo = IMG_Load("menu_fundo.png");
                                                      SDL_FreeSurface(aux);
                                                      }
                                                    }
                                                     else if(opcaoMenu == 2){
                                                        if(!telaCredito){
                                                      telaCredito = 1;
                                                      SDL_Surface* aux = menuFundo;
                                                      menuFundo = IMG_Load("MENU_creditos.png");
                                                      SDL_FreeSurface(aux);
                                                    }
                                                      else{
                                                        telaCredito = 0;
                                                        SDL_Surface* aux = menuFundo;
                                                      menuFundo = IMG_Load("menu_fundo.png");
                                                      SDL_FreeSurface(aux);
                                                      }
                                                     }
 
 
 
 
            }
        }
 
 
    }
 
    if(opcaoMenu > 2) opcaoMenu = 0;
 
    if(opcaoMenu < 0) opcaoMenu = 2;
 
}
 
 
int main ( int argc, char** argv )
{
 
 
    INIT();
 
 
    int segundos = 600, minutos=20, i;
    char string_minuto[2], string_segundo[3],string_score[6];
        int pontos = 0;
    for(i=0;i<2; i++)//limpar lixo de memória na string
      string_minuto[i]='\0';
    for(i=0;i<3; i++)//limpar lixo de memória na string
      string_segundo[i]='\0';
 
 
 
    inicializaMenu();
 
 
 
    while(jogoRodando ){
 
 
     start = SDL_GetTicks();
 
  if(tela_abertura)
  {
 
    draw_objeto(objeto_fundo.sx, objeto_fundo.sy, objeto_fundo.dx , objeto_fundo.dy , objeto_fundo.largura, objeto_fundo.altura , historia, screen);
 
    if(contadorAbertura == 15){
     objeto_fundo.sx += objeto_fundo.largura;
    contadorAbertura = 0;
   }
 
     if(objeto_fundo.sx > largura_fundo - objeto_fundo.largura)
     {
        objeto_fundo.sx = 0;
        telaMenu = 1;
       tela_abertura = 0;
       continue;
}
 
     contadorAbertura++;
 
 
 }
     else if(telaMenu){
 
 eventoTecladoMenu();
 
 ativa_bomba2  = 0;
 ativa_bomba4  = 0;
 
 
 
 
SDL_BlitSurface(menuFundo, 0, screen, 0);
 
 if(!telaCredito && !telaTutorial){
 
 objeto_nave.dx = destino[opcaoMenu].x - 130;
objeto_nave.dy = destino[opcaoMenu].y;
 
objeto_nave.sx += 130;
 
if(objeto_nave.sx > 780-130) objeto_nave.sx = 0;
 
   SDL_BlitSurface(iniciar, 0, screen, &destino[0]);
   SDL_BlitSurface(tutorial, 0, screen, &destino[1]);
   SDL_BlitSurface(creditos, 0, screen,&destino[2]);
   draw_objeto(objeto_nave.sx, objeto_nave.sy, objeto_nave.dx, objeto_nave.dy, objeto_nave.largura, objeto_nave.altura, nave, screen);
 }
 
 
}
 
 
else{
    eventoTeclado();
    ANIMA_BOMBA();
    ANIMA_FUNDO();
    ANIMA_PLATAFORMA();
    bomba_objeto.dx +=10;
 
    if(bomba_objeto.dx >= 750 && bomba_objeto.dy == 145)
    {
        ativa_bomba =1;
    }
 
    if(ativa_bomba == 1)
      bomba_objeto2.dx +=13;
 
    if(bomba_objeto2.dx >= 750 && bomba_objeto2.dy == 145)
    {    ativa_bomba2 =1;
        bomba_objeto2.dx = 50;
    }
 
    if(ativa_bomba2 == 1)
    {
 
       bomba_objeto3.dx +=15;
    }
    if(bomba_objeto3.dx >= 800 && bomba_objeto3.dy == 357 )
    {
 
       bomba_objeto3.dx = 0;
       ativa_bomba4 =1;
 
    }
 
    if(ativa_bomba2 == 1)
    {
     bomba_objeto5.dx -=14;
 
    }
 
 
      if(bomba_objeto5.dx <= 40 && bomba_objeto5.dy ==  460)
    {
 
       bomba_objeto5.dx = 750;
 
    }
 
    if(ativa_bomba4 == 1 )
    {
 
       bomba_objeto4.dx -= 13;;
 
    }
 
      if(bomba_objeto4.dx <= 40 && bomba_objeto4.dy ==  250 )
    {
 
       bomba_objeto4.dx = 750;
 
    }
 
 
    if(pulo)
{
     if(subida)
    {
       player.dy -= 5;
           contPulo++;
 
           if(contPulo == 10)
           {
         subida = 0;
           }
    }
 
     else{
 
        player.dy += 5;
        contPulo--;
 
          if(contPulo == 0)
             pulo = 0;
 
}
}
 
 
 
 
    if(COLISAO(player, objeto_escada) || player.dy >= 416 && player.dx == 290 )
 
    {
 
 
        player.sx= 0;
      if(player.dx >= 290 && player.dy <= 511 )
      {
        player.dx = 290;
       }
       if(player.dx <= 290 && player.dy <= 511 )
       {
        player.sx = 0;
        player.dx = 290;
 
 
       }
 
      if(teclaCima)
      {
 
        player.sy -= 73.6;
        player.dy -= player.vely;
 
        if(player.dy <= 443)
        {
          player.dy = 416;
        }
 
      }
     if(teclaBaixo )
     {
         player.sy += 73.6;
       player.dy +=7;
       if(player.dy >= 525)
         player.dy = 525;
 
 
     }
    }
    if(COLISAO(player, objeto_escada2) || player.dy >= 312 && player.dx == 160)
 
    {
         player.sx= 0;
      if(player.dx >= 160 && player.dy <= 413 )
      {
          player.sx = 0;
        player.dx = 160;
       }
       if(player.dx <= 160 && player.dy <= 413)
       {
        player.dx = 160;
 
       }
 
       if(teclaCima)
      {
          player.sy -= 73.6;
        player.dy -=7;
 
       if( player.dy <=342 )
        {
        player.dy  = 312;
 
        }
      }
     if(teclaBaixo )
     {
         player.sy += 73.6;
       player.dy +=7;
       if(player.dy >= 417)
         player.dy = 417;
 
 
     }
 
    }
    if(COLISAO(player, objeto_escada3) || player.dy >= 205 && player.dx == 547)
    {
         player.sx= 0;
      if(player.dx >= 547 && player.dy >= 298 )
      {
        player.dx = 547;
       }
       if(player.dx <= 547 && player.dy <= 298)
       {
        player.dx = 547;
        }
 
       if(teclaCima)
       {
           player.sy -= 73.6;
       player.dy -= 7;
 
       if(player.dy <=226)
       {
          player.dy = 205;
       }
       }
       if(teclaBaixo)
       {
           player.sy += 73.6;
          player.dy +=7;
       if(player.dy >= 312)
       {
          player.dy = 312;
       }
       }
     }
 
      if(COLISAO(player, objeto_escada4)|| player.dy >= 100 && player.dx == 240)
    {
         player.sx= 0;
       if(player.dx >= 240 && player.dy <= 200 )
       {
           player.sx = 0;
        player.dx = 240;
       }
       if(player.dx <= 240 && player.dy <= 200)
       {
           player.sx = 0;
        player.dx = 240;
 
       }
       if(teclaCima)
       {
           player.sy -= 73.6;
       player.dy -= 7;
 
       if(player.dy <= 121)
         player.dy = 100;
     }
 
     if(teclaBaixo)
     {
         player.sy += 73.6;
       player.dy +=7;
       if(player.dy >= 205)
         player.dy = 205;
 
     }
   }
 
    if(player.sy >368- 73.6)
    {
        player.sy = 0;
    }
 
    if(player.sy < 0)
    {
        player.sy = 368-73.6;
    }
 
    if(subindo){player.sx= 0;}
 
//subindo escada
     if(player.dy == 100 && player.dx == 240 || player.dy == 416 && player.dx == 290 ||
                                player.dy == 312 && player.dx == 160 || player.dy == 205 && player.dx == 547 || player.dy == 525 && player.dx == 290 || player.dy == 417 && player.dx == 160 || player.dy == 312 && player.dx == 547 ){
        subindo = 0;
        SDL_Surface *aux = bender;
                                    bender = IMG_Load("bender-direita.png");
                                    player.sy = 0;
                                    SDL_FreeSurface(aux);
     }
 
     MOVIMENTO_SPRITE();
     LIMITES_TELA();
     DRAW();
 
    SDL_Color cor = {25, 25 , 112};//objeto de cor
    fonte = TTF_OpenFont("space_age.ttf",20);
    segundos--;
    score = score + 0.0;
 
    //sprintf(string_minuto,"%d",minutos/10);//convertendo inteiro pra string
    //sprintf(string_segundo,"%d",segundos/10);//convertendo inteiro pra string
    //desenhaTexto(string_minuto, screen, 380, 10, cor);//primeira posição é o X e a segunda Y
    //desenhaTexto(":", screen, 395, 10, cor);//primeira posição é o X e a segunda Y
    //desenhaTexto(string_segundo, screen, 400, 10, cor);//primeira posição é o X e a segunda Y
    //cor.r = 10;
    //cor.g =  10;
    //cor.b = 10;
 
    if(COLISAO(player, objeto_duff))
    {
       score += 30;
       objeto_duff.dx = 0 ;
       objeto_duff.dy = 15;
 
 
    }
        if(COLISAO(player, objeto_duff2))
    {
       score += 30;
       objeto_duff2.dx = 14 ;
       objeto_duff2.dy = 15;
 
 
    }
 
    if(COLISAO(player, objeto_duff3))
       {
       score += 100;
       objeto_duff3.dx = 28 ;
       objeto_duff3.dy = 15;
 
 
    }
 
    if(COLISAO(player, objeto_boa))
       {
       score += 100;
       objeto_boa.dx = 42 ;
       objeto_boa.dy = 15;
    }
 
 
 
    sprintf(string_score,"%.0f",score);
    desenhaTexto("SCORE: ", screen, 600, 10, cor);
    desenhaTexto(string_score, screen, 700, 10, cor);
 
 
    TTF_CloseFont(fonte);
 
      if(COLISAO_BOMBA(player, bomba_objeto)|| COLISAO_BOMBA(player, bomba_objeto2) || COLISAO_BOMBA(player, bomba_objeto3))
    {
       teste  = 1;
 
    }
 
    if(COLISAO(player, objeto_fry))
    {
       win = 1;
 
    }
 
    if(teste == 1 )
    {
        score=0;
        minutos=20;
        segundos=600;
        SDL_BlitSurface(fim, 0, screen, 0);
        Mix_VolumeMusic(0);
   }
 
   if(win ==1)
   {
        score=0;
        minutos=20;
        segundos=600;
        SDL_BlitSurface(winner, 0, screen, 0);
        Mix_VolumeMusic(0);
        teste = 0;
 
 
 
   }
 
 
 
     printf("%.0f %.0f\n",player.dx, player.dy);
     printf("teste = %d\n", teste);
 
     }
 
 
      if(1000/FPS >(SDL_GetTicks()-start))
          SDL_Delay(1000/FPS-(SDL_GetTicks()-start));
       SDL_Flip( screen);
 
           if(SDL_Flip(screen) == -1)
          {;
           return 1;
          }
 
 
 
 
 
 
}
 
 
    CLEAN_UP();
 
    return 0;
}
