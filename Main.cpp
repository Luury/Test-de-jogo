#include <stdio.h>
#include <SDL2/SDL.h>
#include <Gl/gl.h>          // Bibliotecas Necessárias
#include <SDL2/SDL_image.h>
#include "string"


// Função Colisão entre inimigo e o personagem
bool colisao (float Ax, float Ay, float Acomp, float Aalt, float Bx, float By, float Bcomp, float Balt){ 
	if (Ay+Aalt < By) return false;
	else if (Ay > By + Balt) return false;
	else if (Ax+Acomp < Bx) return false;
	else if (Ax > Bx+Bcomp) return false;
	return true;
}

// Função Colisão entre a espada e o Inimigo
bool colisaoEspada (float Ax, float Ay, float Acomp, float Aalt, float Bx, float By, float Bx1, float By1, float Bx2, float By2, float Bx3, float By3){ 
    if (Ax > Bx3) return false;
    else if (Ay > By3) return false;
    else if (Ay + Aalt < By1) return false;
    else if (Ax + Acomp < Bx1) return false;
	return true;
}

int main( int argc, char* args[] )

{
    //Iniciar SDL
    SDL_Init(SDL_INIT_EVERYTHING);
    
    //Atributos de Cores
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8); // Vermelho
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8); // Verde
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8); // Azul
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8); // Transparencia
    
    //Atributos Buffer
    SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32); 
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);  
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1); 
    
    //Criando Janela                     
    SDL_Window* janela = SDL_CreateWindow ("A Link to the Vulture", //Nome da janela
	300, 20,           // Localização da abertura de janela na área de trabalho
	800, 720,           // Tamanho da Janela
	SDL_WINDOW_OPENGL); // Abrir em modo janela e contexto com OpenGL
	SDL_GLContext contexto = SDL_GL_CreateContext(janela); // Contexto com OpenGL
	
	// Criando framerate
	const int FPS = 144; // Variável do contador de fps
    Uint64 start;
    
	//Chamando imagens e criando superficies
	SDL_Surface * background = IMG_Load ("sprites/background.PNG");
	SDL_Surface * personagem = IMG_Load ("sprites/personagem.PNG");
	SDL_Surface * personagemWalk1 = IMG_Load ("sprites/personagemWalk1.PNG");
	SDL_Surface * personagemWalk2 = IMG_Load ("sprites/personagemWalk2.PNG");
	SDL_Surface * personagemCosta = IMG_Load ("sprites/personagemCosta.PNG");
	SDL_Surface * personagemCostaWalk1 = IMG_Load ("sprites/personagemCostaWalk1.PNG");
	SDL_Surface * personagemCostaWalk2 = IMG_Load ("sprites/personagemCostaWalk2.PNG");
	SDL_Surface * personagemEsquerda = IMG_Load ("sprites/personagemEsquerda.PNG");
	SDL_Surface * personagemEsquerdaWalk1 = IMG_Load ("sprites/personagemEsquerdaWalk1.PNG");
	SDL_Surface * personagemEsquerdaWalk2 = IMG_Load ("sprites/personagemEsquerdaWalk2.PNG");
	SDL_Surface * personagemDireita = IMG_Load ("sprites/personagemDireita.PNG");
	SDL_Surface * personagemDireitaWalk1 = IMG_Load ("sprites/personagemDireitaWalk1.PNG");
	SDL_Surface * personagemDireitaWalk2 = IMG_Load ("sprites/personagemDireitaWalk2.PNG");
	SDL_Surface * personagemAtaqueFrente = IMG_Load ("sprites/personagemAtaqueFrente.PNG");
	SDL_Surface * personagemAtaqueCosta = IMG_Load ("sprites/personagemAtaqueCosta.PNG");
	SDL_Surface * personagemAtaqueDireita = IMG_Load ("sprites/personagemAtaqueDireita.PNG");
	SDL_Surface * personagemAtaqueEsquerda = IMG_Load ("sprites/personagemAtaqueEsquerda.PNG");
	SDL_Surface * personagemTonto = IMG_Load ("sprites/personagemTonto.PNG");
	SDL_Surface * inimigoIdle1 = IMG_Load ("sprites/inimigoIdle1.PNG");
	SDL_Surface * inimigoIdle2 = IMG_Load ("sprites/inimigoIdle2.PNG");
	SDL_Surface * inimigoIdle3 = IMG_Load ("sprites/inimigoIdle3.PNG");
	SDL_Surface * espada = IMG_Load ("sprites/espada.PNG");
	SDL_Surface * lifeBar = IMG_Load ("sprites/lifeBar.PNG");
	SDL_Surface * lifeBarProgress = IMG_Load ("sprites/lifeBarProgress.PNG");
	
	//criando texturas
	glEnable (GL_TEXTURE_2D); // Permitir texturas 2d
	glEnable(GL_BLEND); glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); // Permitir transparencia
	
	//Background
	GLuint backgroundtextura; glGenTextures(1, &backgroundtextura);
	glBindTexture(GL_TEXTURE_2D, backgroundtextura);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, background->w, background->h, 0, GL_RGB, GL_UNSIGNED_BYTE, background->pixels);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	SDL_FreeSurface(background);
	
	// Personagem
	GLuint personagemtextura; glGenTextures(1, &personagemtextura);
	glBindTexture(GL_TEXTURE_2D, personagemtextura);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, personagem->w, personagem->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, personagem->pixels);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	SDL_FreeSurface(personagem);
	
	GLuint personagemWalk1textura; glGenTextures(1, &personagemWalk1textura);
	glBindTexture(GL_TEXTURE_2D, personagemWalk1textura);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, personagemWalk1->w, personagemWalk1->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, personagemWalk1->pixels);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	SDL_FreeSurface(personagemWalk1);
	
	GLuint personagemWalk2textura; glGenTextures(1, &personagemWalk2textura);
	glBindTexture(GL_TEXTURE_2D, personagemWalk2textura);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, personagemWalk2->w, personagemWalk2->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, personagemWalk2->pixels);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	SDL_FreeSurface(personagemWalk2);
	
	GLuint personagemCostatextura; glGenTextures(1, &personagemCostatextura);
	glBindTexture(GL_TEXTURE_2D, personagemCostatextura);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, personagemCosta->w, personagemCosta->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, personagemCosta->pixels);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	SDL_FreeSurface(personagemCosta);
	
	GLuint personagemCostaWalk1textura; glGenTextures(1, &personagemCostaWalk1textura);
	glBindTexture(GL_TEXTURE_2D, personagemCostaWalk1textura);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, personagemCostaWalk1->w, personagemCostaWalk1->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, personagemCostaWalk1->pixels);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	SDL_FreeSurface(personagemCostaWalk1);
	
	GLuint personagemCostaWalk2textura; glGenTextures(1, &personagemCostaWalk2textura);
	glBindTexture(GL_TEXTURE_2D, personagemCostaWalk2textura);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, personagemWalk2->w, personagemCostaWalk2->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, personagemCostaWalk2->pixels);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	SDL_FreeSurface(personagemCostaWalk2);
	
	GLuint personagemEsquerdatextura; glGenTextures(1, &personagemEsquerdatextura);
	glBindTexture(GL_TEXTURE_2D, personagemEsquerdatextura);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, personagemEsquerda->w, personagemEsquerda->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, personagemEsquerda->pixels);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	SDL_FreeSurface(personagemEsquerda);
	
	GLuint personagemEsquerdaWalk1textura; glGenTextures(1, &personagemEsquerdaWalk1textura);
	glBindTexture(GL_TEXTURE_2D, personagemEsquerdaWalk1textura);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, personagemEsquerdaWalk1->w, personagemEsquerdaWalk1->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, personagemEsquerdaWalk1->pixels);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	SDL_FreeSurface(personagemEsquerdaWalk1);
	
	GLuint personagemEsquerdaWalk2textura; glGenTextures(1, &personagemEsquerdaWalk2textura);
	glBindTexture(GL_TEXTURE_2D, personagemEsquerdaWalk2textura);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, personagemWalk2->w, personagemEsquerdaWalk2->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, personagemEsquerdaWalk2->pixels);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	SDL_FreeSurface(personagemEsquerdaWalk2);
	
	GLuint personagemDireitatextura; glGenTextures(1, &personagemDireitatextura);
	glBindTexture(GL_TEXTURE_2D, personagemDireitatextura);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, personagemDireita->w, personagemDireita->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, personagemDireita->pixels);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	SDL_FreeSurface(personagemDireita);
	
	GLuint personagemDireitaWalk1textura; glGenTextures(1, &personagemDireitaWalk1textura);
	glBindTexture(GL_TEXTURE_2D, personagemDireitaWalk1textura);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, personagemDireitaWalk1->w, personagemDireitaWalk1->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, personagemDireitaWalk1->pixels);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	SDL_FreeSurface(personagemDireitaWalk1);
	
	GLuint personagemDireitaWalk2textura; glGenTextures(1, &personagemDireitaWalk2textura);
	glBindTexture(GL_TEXTURE_2D, personagemDireitaWalk2textura);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, personagemWalk2->w, personagemDireitaWalk2->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, personagemDireitaWalk2->pixels);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	SDL_FreeSurface(personagemDireitaWalk2);
	
	GLuint personagemAtaqueFrentetextura; glGenTextures(1, &personagemAtaqueFrentetextura);
	glBindTexture(GL_TEXTURE_2D, personagemAtaqueFrentetextura);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, personagemAtaqueFrente->w, personagemAtaqueFrente->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, personagemAtaqueFrente->pixels);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	SDL_FreeSurface(personagemAtaqueFrente);
	
	GLuint personagemAtaqueCostatextura; glGenTextures(1, &personagemAtaqueCostatextura);
	glBindTexture(GL_TEXTURE_2D, personagemAtaqueCostatextura);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, personagemAtaqueCosta->w, personagemAtaqueCosta->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, personagemAtaqueCosta->pixels);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	SDL_FreeSurface(personagemAtaqueCosta);
	
	GLuint personagemAtaqueDireitatextura; glGenTextures(1, &personagemAtaqueDireitatextura);
	glBindTexture(GL_TEXTURE_2D, personagemAtaqueDireitatextura);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, personagemAtaqueDireita->w, personagemAtaqueDireita->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, personagemAtaqueDireita->pixels);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	SDL_FreeSurface(personagemAtaqueDireita);
	
	GLuint personagemAtaqueEsquerdatextura; glGenTextures(1, &personagemAtaqueEsquerdatextura);
	glBindTexture(GL_TEXTURE_2D, personagemAtaqueEsquerdatextura);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, personagemAtaqueEsquerda->w, personagemAtaqueEsquerda->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, personagemAtaqueEsquerda->pixels);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	SDL_FreeSurface(personagemAtaqueEsquerda);
	
	GLuint personagemTontotextura; glGenTextures(1, &personagemTontotextura);
	glBindTexture(GL_TEXTURE_2D, personagemTontotextura);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, personagemTonto->w, personagemTonto->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, personagemTonto->pixels);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	SDL_FreeSurface(personagemTonto);
	
	GLuint AnimacaoPersonagem = personagemtextura;
	
	// Inimigo
	GLuint inimigoIdle1textura; glGenTextures(1, &inimigoIdle1textura);
	glBindTexture(GL_TEXTURE_2D, inimigoIdle1textura);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, inimigoIdle1->w, inimigoIdle1->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, inimigoIdle1->pixels);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	SDL_FreeSurface(inimigoIdle1);
	
	GLuint inimigoIdle2textura; glGenTextures(1, &inimigoIdle2textura);
	glBindTexture(GL_TEXTURE_2D, inimigoIdle2textura);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, inimigoIdle2->w, inimigoIdle2->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, inimigoIdle2->pixels);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	SDL_FreeSurface(inimigoIdle2);
	
	GLuint inimigoIdle3textura; glGenTextures(1, &inimigoIdle3textura);
	glBindTexture(GL_TEXTURE_2D, inimigoIdle3textura);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, inimigoIdle3->w, inimigoIdle3->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, inimigoIdle3->pixels);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	SDL_FreeSurface(inimigoIdle3);
	
	GLuint inimigotextura = inimigoIdle1textura;
	
	//Espada
	GLuint espadatextura; glGenTextures(1, &espadatextura);
	glBindTexture(GL_TEXTURE_2D, espadatextura);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, espada->w, espada->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, espada->pixels);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	SDL_FreeSurface(espada);
	
	//Barra de vida
	GLuint lifeBartextura; glGenTextures(1, &lifeBartextura);
	glBindTexture(GL_TEXTURE_2D, lifeBartextura);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, lifeBar->w, lifeBar->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, lifeBar->pixels);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	SDL_FreeSurface(lifeBar);
	
	GLuint lifeBarProgresstextura; glGenTextures(1, &lifeBarProgresstextura);
	glBindTexture(GL_TEXTURE_2D, lifeBarProgresstextura);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, lifeBarProgress->w, lifeBarProgress->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, lifeBarProgress->pixels);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	SDL_FreeSurface(lifeBarProgress);
	
	// Criando Eventos
    SDL_Event Eventos;    
	
	// Variáveis
    bool moverx = false, moverx1 = false, movery = false, movery1 = false, personagemataque = false; // Movimento de forma
    float formax = 280, formay = 270, formax1 = 26, formay1 = 35; // Inicializando Valores X Y para o personagem
    float forma2x = 280, forma2y = 400, forma2x1 = 35, forma2y1 = 15; // Inicializando Valores X Y para o inimigo
    float espadax, espaday, espadax1, espaday1, espadax2, espaday2, espadax3, espaday3;  // Inicializando Valores X Y para a esparada
    float velocidade1 = 0.6, velocidade2 = 0.6; // Velocidade que se move o personagem
    float velocidadex = 0.03, velocidadey = 0.03; // Velocidade que se move a segunda forma
    int con = 5; // Váriavel do contador de frames
    int vida = 5; // Vida do personagem
    int score = 0; // Pontuação
    
    
    while (true)            // Loop do jogo
	{
    	if(SDL_PollEvent (&Eventos))  //Eventos
    {
    		if(Eventos.type == SDL_QUIT){ // Fechar Jogo no "x"
    		break;
	    }
    		if(Eventos.type == SDL_KEYDOWN){ 
    		
    		if(Eventos.key.keysym.sym == SDLK_ESCAPE){ //Fechar jogo com a tecla ESC
    		break;
		}		
			if(Eventos.key.keysym.sym == SDLK_RIGHT) {// Deixar o botão "seta direita" pressionado altera a variável moverx
    		moverx = true;
        }
        	if(Eventos.key.keysym.sym == SDLK_LEFT) {// Deixar o botão "seta esquerda" pressionado altera a variável moverx1
    		moverx1 = true;
        }
        	if(Eventos.key.keysym.sym == SDLK_DOWN) {// Deixar o botão "seta para baixo" pressionado altera a variável movery
    		movery = true;
        }
        	if(Eventos.key.keysym.sym == SDLK_UP) {// Deixar o botão "seta para cima" pressionado altera a variável movery1
    		movery1 = true;
        }
            if(Eventos.key.keysym.sym == SDLK_SPACE) {// Deixar o botão "espaço" pressionado  altera a variável personagemataque, e o personagem para de se mover
    		personagemataque = true; 
    		moverx1 = false;
            moverx = false;
		    movery1 = false;
            movery = false;
          }
		}	
        else if(Eventos.type == SDL_KEYUP){
            if(Eventos.key.keysym.sym == SDLK_RIGHT){ // Deixar o botão "seta direita" solta altera a variável moverx
    		moverx = false;
    		AnimacaoPersonagem = personagemDireitatextura;
        }
            if(Eventos.key.keysym.sym == SDLK_LEFT){ // Deixar o botão "seta esquerda" solta altera a variável moverx
    		moverx1 = false;
    		AnimacaoPersonagem = personagemEsquerdatextura;
        }
            if(Eventos.key.keysym.sym == SDLK_DOWN) { // Deixar o botão "seta para baixo" solta altera a variável movery
    		movery = false;
    		AnimacaoPersonagem = personagemtextura;
        }
        	if(Eventos.key.keysym.sym == SDLK_UP) {// Deixar o botão "seta para cima" solta altera a variável movery1
    		movery1 = false;
    		AnimacaoPersonagem = personagemCostatextura;
        }
            if(Eventos.key.keysym.sym == SDLK_SPACE) {// Deixar o botão "seta para cima" solta altera a variável movery1
    		personagemataque = false;
         	    if(AnimacaoPersonagem == personagemAtaqueFrentetextura){
        	           AnimacaoPersonagem = personagemtextura;
	          	}
	       	     if(AnimacaoPersonagem == personagemAtaqueCostatextura  ){
        	           AnimacaoPersonagem = personagemCostatextura;
		        }
	    	     if(AnimacaoPersonagem == personagemAtaqueEsquerdatextura){  // Voltando a animação original a depender da direção
        	          AnimacaoPersonagem = personagemEsquerdatextura;
	         	}
		         if(AnimacaoPersonagem == personagemAtaqueDireitatextura){
        	          AnimacaoPersonagem = personagemDireitatextura;
	        	}
	         espadax = 0; espaday = 0;
			 espadax1 = 0; espaday1 = 0;
			 espadax2 = 0; espaday2 = 0; // Zerando a area da espada
			 espadax3 = 0; espaday3 = 0;
            }
        }
    }
	
	// Limitador de FPS
	start = SDL_GetTicks();
    if(1000/FPS > SDL_GetTicks()-start) {
        SDL_Delay(1000/FPS-(SDL_GetTicks()-start));
        
        
	//Barra de vida
	int vidaperdida = 0;
	if (vida == 4){ // Se a vida for igual a 4
	vidaperdida = 30;
	}
	if (vida == 3){ // Se a vida for igual a 4
	vidaperdida = 60;
	}
	if (vida == 2){ // Se a vida for igual a 4
	vidaperdida = 90;
	}
	if (vida == 1){ // Se a vida for igual a 4
	vidaperdida = 120;
	}
    if (vida < 1){ // Se a vida for menor que 1
    vidaperdida = 150;
    Sleep(2000);                   // Pausa o jogo na hora da morte por 2 segundos
    printf("Game Over\n");         // Print GameOver
    printf("Score: %d \n", score); // Mostrar Score
	break;	                       // Fim de jogo
	}
	
    //Timer de todos sprites do jogo
		  if (con >= 0 && con < 60) {
          	    con = con + 1;
		  }
		  if (con >= 60){
		  	    con = con - 60;
		  }
	
	if (forma2x < 1 ){               
		velocidadex = -velocidadex;
	}
	else if (forma2x + forma2x1 > 599){
		velocidadex = -velocidadex;
	}
	if (forma2y < 1){                           // Não deixar sair inimigo de dentro da "tela"
		velocidadey = -velocidadey;
	}
	else if (forma2y + forma2x1 > 549) {
		velocidadey = -velocidadey;
	}
	
	if (formax < 1 ){               
		moverx1 = false;
	}
	else if (formax + formax1 > 599){
		moverx = false;
	}
	if (formay < 1){                           // Não deixar o personagem sair de dentro da "tela"
		movery1 = false;
	}
	else if (formay + formax1 > 541) {
		movery = false;
	}
		  
	// Mover Personagem
    if(moverx == true){    // Se a variável moverx for verdadeira
    formax += velocidade1 ; // Somar Formax + a velocidade escrita em pixels
                if (con < 30) {
          	    AnimacaoPersonagem = personagemDireitaWalk1textura;
		  }
		        if (con > 30) {
          	    AnimacaoPersonagem = personagemDireitaWalk2textura;
		  }
	   }
    if(moverx1 == true){   // Se a variável mover1 for verdadeira
    formax -= velocidade1 ; // Somar Formax - a velocidade escrita em pixels
                if (con < 30) {
          	    AnimacaoPersonagem = personagemEsquerdaWalk1textura;
		  }
		        if (con > 30) {
          	    AnimacaoPersonagem = personagemEsquerdaWalk2textura;
		  }
	   }
	if(movery == true){    // Se a variável movery for verdadeira
    formay += velocidade2 ; // Somar Formay + a velocidade escrita em pixels
                if (con < 30) {
          	    AnimacaoPersonagem = personagemWalk1textura;
		  }
		        if (con > 30) {
          	    AnimacaoPersonagem = personagemWalk2textura;
		  }
	   }
	if(movery1 == true){   // Se a variável movery1 for verdadeira
    formay -= velocidade2 ; // Somar Formay - a velocidade escrita em pixels
                if (con < 30) {
          	    AnimacaoPersonagem = personagemCostaWalk1textura;
		  }
		        if (con > 30) {
          	    AnimacaoPersonagem = personagemCostaWalk2textura;
		  }
	   }
	   
	//Atacar com o Personagem
	if(personagemataque == true){   // Se o personagem estiver atacando, a espada e a textura vai mudar a depender da direção
        if(AnimacaoPersonagem == personagemtextura || AnimacaoPersonagem == personagemWalk2textura || AnimacaoPersonagem == personagemWalk1textura ){
        	 AnimacaoPersonagem = personagemAtaqueFrentetextura;
        	 espadax = formax + 20; espaday = formay + 34;
			 espadax1 = formax + 22; espaday1 = formay + 34;
			 espadax2 = formax + 22; espaday2 = formay + 52;
			 espadax3 = formax + 20; espaday3 = formay + 52;
		}
		if(AnimacaoPersonagem == personagemCostatextura || AnimacaoPersonagem == personagemCostaWalk1textura || AnimacaoPersonagem == personagemCostaWalk2textura ){
        	 AnimacaoPersonagem = personagemAtaqueCostatextura;
        	 espadax = formax + 3; espaday = formay - 18;
			 espadax1 = formax + 5; espaday1 = formay - 18;
			 espadax2 = formax + 5; espaday2 = formay + 1;
			 espadax3 = formax + 3; espaday3 = formay + 1;
		}
		if(AnimacaoPersonagem == personagemEsquerdatextura || AnimacaoPersonagem == personagemEsquerdaWalk1textura|| AnimacaoPersonagem == personagemEsquerdaWalk2textura ){
        	 AnimacaoPersonagem = personagemAtaqueEsquerdatextura;
        	 espadax = formax + 1; espaday = formay + 20;
			 espadax1 = formax - 18; espaday1 = formay + 20;
			 espadax2 = formax - 18; espaday2 = formay + 22;
			 espadax3 = formax + 1 ; espaday3 = formay + 22;
		}
		if(AnimacaoPersonagem == personagemDireitatextura || AnimacaoPersonagem == personagemDireitaWalk1textura || AnimacaoPersonagem == personagemDireitaWalk2textura ){
        	 AnimacaoPersonagem = personagemAtaqueDireitatextura;
        	 espadax = formax + 26; espaday = formay + 20;
			 espadax1 = formax + 26; espaday1 = formay + 22;
			 espadax2 = formax + 44; espaday2 = formay + 22;
			 espadax3 = formax + 44; espaday3 = formay + 20;
		}
    	moverx1 = false;
        moverx = false;
		movery1 = false; // Enquanto ataca o personagem não pode se mover
        movery = false;
	   }
	   
	   
	//Mover o inimigo aleatóriamente
	int random;   
    random = rand() % 150; // Vai sortear um numero em todo loop entre 0 e 150
    
    forma2x += velocidadex; // Inicializando as velocidades positivas
    forma2y += velocidadey;
    
    if (random == 25){ // se o numero sorteado for 25 a velocidadex será negativa
	velocidadex = -velocidadex;
	}
    else if (random == 50){ // se o numero sorteado for 50 a velocidadey será negativa
    velocidadey = -velocidadey;
	}
	else if (random == 75){ // se o numero sorteado for 75 a velocidadex será positiva
	velocidadex = -(-velocidadex);
	}
    else if (random == 100){ // se o numero sorteado for 100 a velocidadey será positiva
    velocidadey = -(-velocidadey);
	}
	
	
		//Animação do Inimigo
	            if (con < 20) {
          	    inimigotextura = inimigoIdle1textura;
		  }
		        if (con > 20 & con < 40) {
          	    inimigotextura = inimigoIdle3textura; // Idle do inimigo utilizando o contador de frames
		  }
		  	    if (con > 40) {
          	    inimigotextura = inimigoIdle2textura; 
		  }
		
		
	//Colisão do inimigo com o personagem
	if (colisao(forma2x, forma2y, forma2x1, forma2y1, formax, formay, formax1, formay1) == true){ // Chamando a função da colisão
		if (velocidadex == -(-velocidadex)){
			velocidadex = -velocidadex;
		}
		if (velocidadex == -velocidadex){
		velocidadex = -(-velocidadex);
		}
		if (velocidadey == -(-velocidadey)){ // Se acontecer uma colisão o inimigo vai ser repelido
			velocidadey = -velocidadey;
		}
		if (velocidadey == -velocidadey){
		velocidadey = -(-velocidadey);
		}
		int posicaoAleatoria;   
		posicaoAleatoria = rand() % 450; // Sorteando um numero entre 0 e 450
		forma2x = 35 + posicaoAleatoria, forma2y = 2 + posicaoAleatoria, forma2x1 = 35, forma2y1 = 15; // Inicializando o inimigo em outra posição aleatória a depender do numero sorteado
		AnimacaoPersonagem = personagemTontotextura; // Muda a textura pro personagem tonto
		Sleep(1000);                                // Pausa o jogo por um segundo na hora da colisão
		AnimacaoPersonagem = personagemtextura;     //  Muda a textura pro personagem normal
		vida = vida - 1;                            // Retira 1 da vida
	}	
	
	//Colisão do inimigo com a espada
	if (colisaoEspada(forma2x, forma2y, forma2x1, forma2y1, espadax, espaday, espadax1, espaday1, espadax2, espaday2, espadax3, espaday3) == true){
		
		if (velocidadex == -(-velocidadex)){
			velocidadex = -velocidadex;
		}
		if (velocidadex == -velocidadex){
		velocidadex = -(-velocidadex);
		}
		if (velocidadey == -(-velocidadey)){ // Se acontecer uma colisão o inimigo vai ser repelido
			velocidadey = -velocidadey;
		}
		if (velocidadey == -velocidadey){
		velocidadey = -(-velocidadey);
		}
		
		int posicaoAleatoria;
		posicaoAleatoria = rand() % 450; // Sorteando um numero entre 0 e 450
		forma2x = 35 + posicaoAleatoria, forma2y = 2 + posicaoAleatoria, forma2x1 = 35, forma2y1 = 15; // Inicializando o inimigo em outra posição aleatória
		
		float aumentoVelocidade = 0.03;
		if (velocidadex > 0){
			velocidadex = velocidadex + aumentoVelocidade;
		}
		if (velocidadey > 0){
			velocidadey = velocidadey + aumentoVelocidade;
		}
	    if (velocidadex < 0){                                  // Aumento de velocidade do inimigo a cada colisão
			velocidadex = velocidadex - aumentoVelocidade;
		}
		if (velocidadey < 0){
			velocidadey = velocidadey - aumentoVelocidade;
		}
		score = score + 1; // Soma a pontuação +1 a cada acerto no inimigo
	}
	
	
	//Inicializar uma Matriz
	glPushMatrix(); // Abrir Matriz
	
	glOrtho( 0,  // Ponto Minimo do "x"
	600,         // Ponto Máximo do "x"
	600,         // Ponto  Máximo do "y"   	//Especificações da matrix
	0,           // Ponto Mínimo do "y"
	-1,          // Valor pré definido
	1);          // Valor pré definido
	
	
	glBindTexture(GL_TEXTURE_2D, backgroundtextura); // Textura do chão
	glBegin(GL_QUADS);{ // background
	
	glTexCoord2f(0,0); glVertex2f(0,0); // Primeiro ponto
	glTexCoord2f(1,0); glVertex2f(600,0); // Segundo ponto
	glTexCoord2f(1,1); glVertex2f(600,550); // Terceiro Ponto
	glTexCoord2f(0,1); glVertex2f(0,550); // Quarto ponto
	glEnd();} // Final da da Forma
	

	glBindTexture(GL_TEXTURE_2D, AnimacaoPersonagem);  // Textura do personagem
	glBegin(GL_QUADS);{ // Iniciando personagem
	glTexCoord2f(0,0); glVertex2f(formax, formay); // Primeiro ponto
	glTexCoord2f(1,0); glVertex2f(formax + formax1 , formay); // Segundo Ponto
	glTexCoord2f(1,1); glVertex2f(formax + formax1, formay + formay1); // Terceiro Ponto
	glTexCoord2f(0,1); glVertex2f(formax, formay + formay1); // Quarto ponto
		
	glEnd();} // Final da da Forma
	
	glBindTexture(GL_TEXTURE_2D, inimigotextura);  // Textura do inimigo
	glBegin(GL_QUADS);{ // Iniciando o inimigo
	
	glTexCoord2f(0,0); glVertex2f(forma2x, forma2y); // Primeiro ponto
	glTexCoord2f(1,0); glVertex2f(forma2x + forma2x1 , forma2y); // Segundo ponto
	glTexCoord2f(1,1); glVertex2f(forma2x + forma2x1, forma2y + forma2y1); // Terceiro Ponto
	glTexCoord2f(0,1); glVertex2f(forma2x, forma2y + forma2y1); // Quarto ponto
		
	glEnd();} // Final da da Forma
	
	glBindTexture(GL_TEXTURE_2D, espadatextura);  // Textura da espada
	glBegin(GL_QUADS);{ // Iniciando a espada
	
	glTexCoord2f(0,0); glVertex2f(espadax, espaday); // Primeiro ponto
	glTexCoord2f(1,0); glVertex2f(espadax1, espaday1); // Segundo ponto
	glTexCoord2f(1,1); glVertex2f(espadax2, espaday2); // Terceiro Ponto
	glTexCoord2f(0,1); glVertex2f(espadax3, espaday3); // Quarto ponto
		
	glEnd();} // Final da da Forma
	
	glBindTexture(GL_TEXTURE_2D, lifeBarProgresstextura);  // Textura borda barra de vida
	glBegin(GL_QUADS);{ // Iniciando a textura da barra de vida
	
	glTexCoord2f(0,0); glVertex2f(35, 566); // Primeiro ponto
	glTexCoord2f(1,0); glVertex2f(178 - vidaperdida, 566); // Segundo ponto
	glTexCoord2f(1,1); glVertex2f(178 - vidaperdida, 583); // Terceiro Ponto
	glTexCoord2f(0,1); glVertex2f(35, 583); // Quarto ponto
		
	glEnd();} // Final da da Forma
	
	glBindTexture(GL_TEXTURE_2D, lifeBartextura);  // Textura da borda da barra de vida
	glBegin(GL_QUADS);{ // Iniciando a borda da barra de vida
	
	glTexCoord2f(0,0); glVertex2f(20, 560); // Primeiro ponto
	glTexCoord2f(1,0); glVertex2f(180, 560); // Segundo ponto
	glTexCoord2f(1,1); glVertex2f(180, 590); // Terceiro Ponto
	glTexCoord2f(0,1); glVertex2f(20, 590); // Quarto ponto
		
	glEnd();} // Final da da Forma
	
	glPopMatrix(); // Fecha a matriz
	
	SDL_GL_SwapWindow(janela);// Animação Buffer
	glClear(GL_COLOR_BUFFER_BIT); // Limpa o Buffer	
	}
  }
    return 0;
}

