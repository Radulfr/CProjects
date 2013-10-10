#include <stdio.h>
#define MAXDIM 50
#define TRUE 1
#define FALSE 0
typedef enum { Perdedora, Tablas, Ganadora } TPosicion;
typedef struct {
  int Peso, Valor, Cogido;
} TObjeto;
typedef struct {
  int Peso, Valor;
} TJugador;

void Evaluar (TJugador JugadorA, TJugador JugadorB, int K, TObjeto Objeto [], int  N, TPosicion *Pos, int *NumObjeto);
void EvaluarAuto(TJugador JugadorA, TJugador COM, int K, TObjeto Objeto[], int N, TPosicion *Pos);
int PuedeCoger (TJugador Jugador, int K, TObjeto Objeto[], int N);
void Entrada (int *K, int *N, TObjeto Objeto[]);
void Inicializa(TJugador *JugadorA, TJugador *JugadorB, TObjeto Objeto[], int N);
void Genera(int *K, int *N, TObjeto Objeto[]);
void print_status(TObjeto Objeto[], int N);
void print_score(TJugador *JugadorA, TJugador *COM);
   
main () {
  int N, K, i, modo_juego=-1;
  TPosicion Pos;
  int NumObjeto;
  TJugador JugadorA, JugadorB, COM;
  TObjeto Objeto[MAXDIM];

  /*Generacion de objetos:
   * Comentar "Entrada" para generacion automatica
   * Comentar "Genera" para generacion manual
   */

  // Generamos los objetos manualmente

  //  Entrada (&K,&N,Objeto);

  //Generamos los objetos de manera aleatoria
  Genera (&K,&N,Objeto);


  // MODO DE JUEGO         
  printf("Seleccione modo de juego:\n1.Automatico\n2.Vs COM\n"); 
  while (modo_juego < 1 || modo_juego > 2){
    scanf("%d", &modo_juego); 
    if(modo_juego < 1 || modo_juego > 2)
      printf("Seleccion incorrecta, (1) o (2): "); 
  }
  // COM VS COM
  if(modo_juego == 1){
    printf("\n\nEvaluando Posicion...\n");
    Inicializa(&JugadorA,&JugadorB,Objeto,N);
    Evaluar (JugadorA,JugadorB,K,Objeto,N,&Pos,&NumObjeto);
    printf("\n\nLos objetos con su peso y valor son: \n");
    for (i = 0; i < N; i++)
      printf("Objeto %d -> Valor: %2d (Peso %2d)\n",i,Objeto[i].Valor,Objeto[i].Peso);
      
    printf("\n\nLa posicion del juego es ");
  
    if (Pos == Perdedora)
      printf("Posicion PERDEDORA\n\n");
    else {
      if (Pos == Ganadora) printf("Posicion GANADORA\n\n");
      else printf("Hay TABLAS\n\n");
   
      printf("El resultado se obtiene cogiendo el objeto %d: (Valor: %d, Peso: %d)\n" , NumObjeto,Objeto[NumObjeto].Valor,Objeto[NumObjeto].Peso);
      printf("(Los objetos comienzan a numerarse por 0)\n");
    }
  }
  // HUMAN VS COM
  else if (modo_juego == 2){
    Inicializa(&JugadorA,&COM,Objeto,N);
    EvaluarAuto(JugadorA,COM,K,Objeto,N, &Pos);//Nueva funcion de evaluacion
    if (Pos == Perdedora)
      printf("PERDEDORA\n\n");
    else {
      if (Pos == Ganadora) printf("GANADORA\n\n");
      else printf("TABLAS\n\n");
    }
  }
} // fin main
void Genera(int *K, int *N, TObjeto Objeto[]){
  int i; 
  int max_size; 
  int max_value; 

  printf("Peso Maximo... "); scanf(" %d",K);
  printf("Numero de Objetos (< %d) ... ",MAXDIM); scanf(" %d",N);
  printf("Tam. maximo de objeto: "); scanf("%d", &max_size); 
  printf("Valor maximo de objeto: "); scanf("%d", &max_value); 
  printf("\nGenerando objetos aleatorios...\n"); 
  srand(getpid()); 
  for(i=0; i<*N; i++){
    Objeto[i].Peso = (rand() % max_size) +1; 
    Objeto[i].Valor = (rand() % max_value) +1; 
    //    printf("Objeto [%d] - TAM: %d \tVAL: %d\n", i, Objeto[i].Peso, Objeto[i].Valor); 
  }

}
void Entrada (int *K, int *N, TObjeto Objeto[]) {
  int i;
   
  printf("Peso Maximo... "); scanf(" %d",K);
  printf("Numero de Objetos (< %d) ... ",MAXDIM); scanf(" %d",N);
  printf("Peso de cada objeto -> ");
  for (i=0; i<*N; i++) scanf(" %d", &Objeto[i].Peso);
  printf("\nValor de cada objeto -> ");
  for (i=0; i<*N; i++) scanf(" %d", &Objeto[i].Valor);
}
      
   
void Inicializa(TJugador *JugadorA, TJugador *JugadorB, TObjeto Objeto[], int N) {
  int i;
  JugadorA->Peso = 0; JugadorA->Valor = 0;
  JugadorB->Peso = 0; JugadorB->Valor = 0;
  for (i=0; i<N; i++) Objeto[i].Cogido = FALSE;
}
 
void EvaluarAuto(TJugador JugadorA, TJugador COM, int K, TObjeto Objeto[], int N, TPosicion *Pos){
  TPosicion posi = Tablas; 
  int turno = 0; 
  int i, seleccion=0; 
  int x=-1; 
  int legal=FALSE, fin=FALSE;
  TPosicion PosDejamos; 

  while (fin==FALSE){
    print_score(&JugadorA, &COM); 
    print_status(Objeto, N); 

    // PARTE DEL JUGADOR
    legal = FALSE; 
    printf("Seleccione objeto:\n"); 

    while (legal==FALSE ){
      if(!PuedeCoger(JugadorA,K,Objeto,N)){
	legal=TRUE; 
	printf("Paso!\n"); 
      }
      else{
	scanf("%d", &seleccion); 
	if((Objeto[seleccion].Cogido==FALSE) && (Objeto[seleccion].Peso <= (K-JugadorA.Peso))){
	  legal=TRUE; 
	  Objeto[seleccion].Cogido = TRUE; 
	  JugadorA.Valor += Objeto[seleccion].Valor;
	  JugadorA.Peso += Objeto[seleccion].Peso;
	}
	else
	  printf("No puede seleccionar ese objeto. Elija otro: "); 
      }
    }
    // PARTE DE LA MAQUINA
    if (!PuedeCoger(COM,K,Objeto,N)){
      printf("COM: Paso\n"); 
      // TODO
    }
    else{
      Evaluar (COM,JugadorA,K,Objeto,N,&PosDejamos,&x);

      if((x>=0) && (Objeto[x].Cogido == FALSE)){
	printf("COM escoge Objeto [%d]\n", x); 
	Objeto[x].Cogido=TRUE; 
	COM.Valor +=Objeto[x].Valor; 
	COM.Peso += Objeto[x].Peso; 
      }
      else{
	printf("COM: Paso\n"); 
	fin=TRUE; 
      }
    }

    if(!PuedeCoger(COM,K,Objeto,N) && !PuedeCoger(JugadorA,K,Objeto,N)){
      print_score(&JugadorA, &COM); 
      if(JugadorA.Valor > COM.Valor)
	*Pos = Ganadora;
      else if (JugadorA.Valor < COM.Valor)
	*Pos = Perdedora; 
      else
	*Pos = Tablas; 

      fin=TRUE; 
    }
  }
}

   
void Evaluar (TJugador JugadorA, TJugador JugadorB, int K, TObjeto Objeto[], int N , TPosicion *Pos, int *NumObjeto) {
  int i, x, Valor;
  TPosicion PosDejamos;
   
  if (!PuedeCoger(JugadorA,K,Objeto,N))
    if (!PuedeCoger(JugadorB,K,Objeto,N))

      if (JugadorA.Valor > JugadorB.Valor) *Pos = Ganadora;
      else if (JugadorA.Valor == JugadorB.Valor) *Pos = Tablas;
      else *Pos = Perdedora;
    else {

      Evaluar (JugadorB,JugadorA,K,Objeto,N,&PosDejamos,&x);
      if (PosDejamos == Ganadora) *Pos = Perdedora;
      else if (PosDejamos == Perdedora) *Pos = Ganadora;
      else *Pos = Tablas;
      *NumObjeto = -1; // Para indicar que no hacemos nada
    }
  else {

    i = 0; *Pos = Perdedora;
    while ((i<N) && (*Pos != Ganadora)) {
      if (!Objeto[i].Cogido && (JugadorA.Peso + Objeto[i].Peso <= K)) {
	Objeto[i].Cogido = TRUE; 
	JugadorA.Valor += Objeto[i].Valor;
	JugadorA.Peso += Objeto[i].Peso;
               
	Evaluar (JugadorB,JugadorA,K,Objeto,N,&PosDejamos,&x);
	if (PosDejamos != Ganadora) {
	  *NumObjeto = i;
	  if (PosDejamos == Perdedora) *Pos = Ganadora;
	  else *Pos = Tablas;
	}
	// Restablecemos los valores
	Objeto[i].Cogido = FALSE; 
	JugadorA.Valor -= Objeto[i].Valor;
	JugadorA.Peso -= Objeto[i].Peso;
      }   
      i++;
    }
  }    
} // Fin Evaluar 
void print_status(TObjeto Objeto[], int N){
  int i; 
  for (i = 0; i < N; i++){
    printf("Objeto %d -> Valor: %2d (Peso %2d)",i,Objeto[i].Valor,Objeto[i].Peso);
    if(Objeto[i].Cogido==TRUE)
      printf(" -[%d][COGIDO]\n", i); 
    else
      printf("\n"); 
  }
}

void print_score(TJugador *JugadorA, TJugador *COM){
  printf("[A] Peso: %d - Valor: %d \t[B] Peso: %d - Valor: %d\n", JugadorA->Peso, JugadorA->Valor, COM->Peso, COM->Valor); 
}

int PuedeCoger (TJugador Jugador, int K, TObjeto Objeto[], int N) {
  int i;
  for (i= 0; i<N; i++) 
    if (!Objeto[i].Cogido && (Jugador.Peso + Objeto[i].Peso <= K)) return TRUE;
  return FALSE;
}
