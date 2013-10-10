#include "orders.h"

int years(int X[], int Y[], int lix, int lsx, int liy, int lsy);
int med(int x, int y); 
int min(int x, int y); 
int max(int x, int y);

void main(){
  int N, M; 

  printf("==========\nPractica 1\n==========\n"); 
  printf("Valor de N: "); 
  scanf("%d", &N); 
  printf("\nValor de M: "); 
  scanf("%d", &M); 
  printf("\n"); 

  int v1[N]; 
  int v2[M]; 
  int i=0, jon; 
  int vmezcla[N+M+1];
  int a=0,b=0; 

  srand(getpid()); 

  printf("Generando vectores [%d, %d]...\n", N, M); 

  for(i=0; i<N; i++)
    v1[i]=rand()%20 + 15; 

  for(i=0; i<M; i++)
    v2[i]=rand()%20 + 15 ; 

  /* Ordenar los vectores con QS*/
  QS(v1,0,N-1); 
  printf("\nN soldados: "); 
  printvec(v1,N); 

  QS(v2,0,M-1); 
  printf("M soldados: "); 
  printvec(v2,M); 

  int cont = 1; 
  a=0; 
  b=0; 

  /* Mostrar vector solución */

  for(i=0; i<=(N+M); i++){
    if((i==((N+M)/2)) && cont==1){
      printf("<JON> "); 
      cont=0; 
    }
    else if((v1[a]<=v2[b]) && (a<N)){
      printf("%d ", v1[a]); 
      a++; 
    }
    else if((v2[b] < v1[a]) && (b < M)){
      printf("%d ", v2[b]); 
      b++; 
    }
    else{
      if(a==N){
	printf("%d ", v2[b]); 
	b++; 
      }
      else if(b==M){
	printf("%d ", v1[a]); 
	a++; 
      }
      else{
	printf("Cuek "); 
      }
    }
  }

  printf("\n"); 
  /* Búsqueda DYV */
  /* ----- Comienzo del problema ----- */

  printf("Calculando edad de Jon... \n");
  int edad = years(v1, v2, 0, N-1, 0, M-1); 
  printf("Edad: %d\n", edad); 
}

/* Función de edad */
int years(int X[], int Y[], int lix, int lsx, int liy, int lsy){
  int posX, posY, nitems; 
  int param, longitudx, longitudy; 
  posX = (lsx+lix)/2; 
  posY = (lsy+liy)/2;
  longitudx = lsx-lix; 
  longitudy = lsy-liy; 
    
  if((longitudx==0) && (longitudy==0)){/* 1º caso base */
    printf("----- CASO BASE 1 ----- \n"); 
    return med(X[lsx], Y[lsy]); 
  }
  /* 2º caso base: |A| = 2, |B| = 1 */
  /*2.1  para |X|=2 e |Y|=1 */
  else if((longitudx==1)  && (longitudy==0)){
    printf("----- CASO BASE 2 ----- \n"); 
    if((Y[lsy]<=X[lsx]) && (Y[lsy] >= X[lix]))
      return Y[lsy]; 
    else if(Y[lsy]<X[lix])
      return X[lix]; 
    else if(Y[lsy]>X[lsx])
      return X[lsx]; 
  }
  /*2.2 para |Y|=2 y |X|=1 */
  else if((longitudy == 1) && (longitudx==0)){
    printf("----- CASO BASE 2 ----- \n"); 
    if((X[lsx]<=Y[lsy]) && (X[lsx] >= Y[liy]) )
      return X[lsx]; 
    else if(X[lsx]<Y[liy])
      return Y[liy]; 
    else if(X[lsx]>Y[lsy])
      return Y[lsy]; 
  }
  /* 3º caso base: |A| = |B| = 2 */
  else if((longitudx==1) && (longitudy==1)){
    /*3.1 A contenido en B */
    if((X[lix] >= Y[liy]) && (X[lix] <= Y[lsy])
       && (X[lsx] <= Y[lsy]) && (X[lsx] >= Y[liy])){
      printf("----- CASO BASE 3 ----- \n"); 
      return med(X[lix], X[lsx]); 
    }
    /*3.2 B contenido en A */
    else if((Y[liy] >= X[lix]) && (Y[liy] <= X[lsx])
	    && (Y[lsy] <= X[lsx]) && (Y[lsy] >= X[lix])){
      printf("----- CASO BASE 3 ----- \n"); 
      return med(Y[liy], Y[lsy]); 
    }
    
    /*3.3 B es solapado y continuado por A */
    else if((X[lix] >= Y[liy]) && (X[lix] <= Y[lsy]) 
	    && (X[lsx] > Y[lsy])){
      printf("----- CASO BASE 3 ----- \n"); 
      return med(Y[lsy], X[lix]); 
    }
    
    /*3.4 A es solapado y continuado por B */
    else if((Y[liy] >= X[lix]) && (Y[liy] <= X[lsx]) 
	    && (Y[lsy] > X[lsx])){
      printf("----- CASO BASE 3 ----- \n"); 
      return med(X[lsx], Y[liy]); 
    }
    
    /*3.5 A y B son disjuntos */
    
    /*3.5.1 A estrictamente mayor que B */
    else if(X[lsx] < Y[liy]){
      printf("----- CASO BASE 3 ----- \n"); 
      return med(X[lsx], Y[liy]); 
    }
    
    /*3.5.2 B estrictamente mayor que A */
    else if(Y[lsy] < X[lix]){
      printf("----- CASO BASE 3 ----- \n"); 
      return med(Y[lsy], X[lix]);
    }
  }
  
  /*4º Casos |A|=1, |B|>2 y vic. */
  /*4.1 - |X| = 1, |Y| > 2 */
  else if((longitudx==0) && (longitudy>1)){
    printf("----- CASO BASE 4 ----- \n"); 
    /*4.1.1 Si X coincide con el medio de Y */
    if((X[lsx] == Y[(lsy+liy)/2]))
      return X[lsx]; 
    /*4.1.2 Si X es menor estricto que Y */
    else if(X[lsx] <= Y[liy]){
      /*Comprobamos paridad*/
      if((lsy-liy)%2 == 0) /* Es de longitud impar */
	return med(Y[(lsy+liy)/2], Y[(lsy+liy)/2 -1]); 
      else /*Es de longitud par */
	return Y[(lsy+liy)/2];
    }
    /*4.1.2 Si X es mayor estricto que Y */
    else if(X[lix] >= Y[lsy]){
      /*Comprobamos paridad*/
      if((lsy-liy)%2 == 0) /* Es de longitud impar */
	return med(Y[(lsy+liy)/2], Y[(lsy+liy)/2 +1]); 
      else /*Es de longitud par */
	return Y[(lsy+liy)/2 +1];
    }
    /*4.1.3 Si X está contenido en Y */
    else if((X[lsx] > Y[liy]) && (X[lsx] < Y[lsy])){
      /*Comprobamos paridad*/
      if((lsy-liy)%2 == 0){ /* Es de longitud impar */
	/*4.1.3.1 Si está por encima de la mediana */
	if(X[lsx] > Y[(lsy+liy)/2]){
	  return med(Y[(lsy+liy)/2], Y[(lsy+liy)/2 +1]); 
	}
	/*4.1.3.1 Si está por debajo de la mediana */
	else{
	  return med(Y[(lsy+liy)/2], Y[(lsy+liy)/2 -1]); 
	}
      }
      else{ /*Es de longitud par */
	/*4.1.3.1 Si está por encima de la mediana */
	if(X[lsx] > Y[(lsy+liy)/2]){
	  return Y[(lsy+liy)/2 +1]; 
	}
	/*4.1.3.1 Si está por debajo de la mediana */
	else{
	  return Y[(lsy+liy)/2]; 
	}
      }
    }
  }
  /*4.2 - |X| > 2, |Y| = 1 */
  else if((longitudy==0) && (longitudx>1)){
    printf("----- CASO BASE 4 ----- \n"); 
    /*4.1.1 Si Y coincide con el medio de X */
    if((Y[lsy] == X[(lsx+lix)/2]))
      return Y[lsy]; 
    /*4.1.2 Si Y es menor estricto que X */
    else if(Y[lsy] <= X[lix]){
      /*Comprobamos paridad*/
      if((lsx-lix)%2 == 0) /* Es de longitud impar */
	return med(X[(lsx+lix)/2], X[(lsx+lix)/2 -1]); 
      else /*Es de longitud par */
	return X[(lsx+lix)/2];
    }
    /*4.1.2 Si Y es mayor estricto que X */
    else if(Y[liy] >= X[lsx]){
      /*Comprobamos paridad*/
      if((lsx-lix)%2 == 0) /* Es de longitud impar */
	return med(X[(lsx+lix)/2], Y[(lsx+lix)/2 +1]); 
      else /*Es de longitud par */
	return X[(lsx+lix)/2 +1];
    }
    /*4.1.3 Si Y está contenido en X */
    else if((Y[lsy] > X[lix]) && (Y[lsy] < X[lsx])){
      /*Comprobamos paridad*/
      if((lsx-lix)%2 == 0){ /* Es de longitud impar */
	/*4.1.3.1 Si está por encima de la mediana */
	if(Y[lsy] > X[(lsx+lix)/2]){
	  return med(X[(lsx+lix)/2], X[(lsx+lix)/2 +1]); 
	}
	/*4.1.3.1 Si está por debajo de la mediana */
	else{
	  return med(X[(lsx+lix)/2], X[(lsx+lix)/2 -1]); 
	}
      }
      else{ /*Es de longitud par */
	/*4.1.3.1 Si está por encima de la mediana */
	if(Y[lsy] > X[(lsx+lix)/2]){
	  return X[(lsx+lix)/2 +1]; 
	}
	/*4.1.3.1 Si está por debajo de la mediana */
	else{
	  return X[(lsx+lix)/2]; 
	}
      }
    }
  }
  /*5º - |X|==2, |Y| > 2 y vic */
  /* 5.1 |X| ==2 , |Y| >2 */
  else if((longitudx==1) && (longitudy>=2)){
    printf("----- CASO BASE 5 ----- \n"); 
    
    if((Y[posY] >= X[lix]) && (Y[posY] <= X[lsx]))
      return Y[posY]; 
    
    else if(Y[posY] >= X[lsx]){
      /*Comprobamos paridad*/
      if((lsy-liy)%2 == 0) /* Es de longitud impar */
	return med(Y[posY-1], max(Y[posY-1], X[lsx]));
      else /*Es de longitud par */
	if((posX-2)>=0)
	  return med(Y[posY], max(Y[posY-2], X[lsx]));
	else
	  return med(Y[posY], max(Y[posY-1], X[lsx]));
    }
    else if(Y[posY] < X[lix]){
      /*Comprobamos paridad*/
      if((lsy-liy)%2 == 0) /* Es de longitud impar */
	return med(Y[posY], min(Y[posY+1], X[lsx]));
      else /*Es de longitud par */
	return med(Y[posY+1], min(Y[posY+1], X[lsx]));
    }
  }
  /* 5.2 |X| > 2 , |Y| == 2 */
  else if((longitudx>=2) && (longitudy==1)){
    printf("----- CASO BASE 5 ----- \n"); 
  
    if((X[posX] >= Y[liy]) && (X[posX] <= Y[lsy]))
      return X[posX]; 

    else if(X[posX] >= Y[lsy]){
      /*Comprobamos paridad*/
      if((lsx-lix)%2 == 0) /* Es de longitud impar */
	return med(X[posX-1], max(X[posX-1], Y[lsy]));
      else /*Es de longitud par */
	if((posX-2)>=0)
	  return med(X[posX], max(X[posX-2], Y[lsy]));
	else
	  return med(X[posX], max(X[posX-1], Y[lsy])); 
    }
    else if(X[posX] <= Y[liy]){
      /*Comprobamos paridad*/
      if((lsx-lix)%2 == 0) /* Es de longitud impar */
	return med(X[posX], min(X[posX+1], Y[lsy]));
      else /*Es de longitud par */
	return med(X[posX+1], min(X[posX+1], Y[lsy]));
    }
  }
  
  /* ------------------------------------------- Caso general */
  else{
    printf("----- CASO GENERAL ----- \n"); 
    /* Si las medianas son iguales, será esa misma */
    if(X[posX] == Y[posY]) 
      return X[posX]; 
    /* De no ser así, se llama recursivamente según casos */
    
    /*X anterior a Y */
    else if(X[lsx] <= Y[liy]){
      longitudx = lsx-lix; 
      longitudy = lsy-liy; 
      param = longitudx+longitudy; 
      
      if ((param/2)==longitudx)
	return X[lsx]; 
      else if((param/2)>longitudx)
	return Y[(param/2)-longitudx +liy]; 
      else
	return X[param/2]; 
    }
    /*Y anterior a X */
    else if(Y[lsy] <= X[lix]){
      longitudx = lsx-lix; 
      longitudy = lsy-liy; 
      param = longitudx+longitudy; 
      
      if ((param/2)==longitudy)
	return Y[lsy]; 
      else if((param/2)>longitudy)
	return X[(param/2)-longitudy +lix]; 
      else
	return Y[param/2]; 
    }
    /*------------*/
    else if(X[posX] > Y[posY]){
      printf("Xmed = %d\nYmed = %d\t X: [%d:%d, %d:%d] \t Y: [%d:%d, %d:%d]\n", X[posX], Y[posY], lix, X[lix], lsx, X[lsx], liy, Y[liy], lsy, Y[lsy]); 
      nitems=min((lsx-posX),(posY-liy));
      printf("items/lado: %d\n---------\n", nitems); 
      return years(X,Y, lix, (lsx-nitems), (liy+nitems), lsy); 
    }
    else if(X[posX] < Y[posY]){
      printf("Xmed = %d\nYmed = %d\t X: [%d:%d, %d:%d] \t Y: [%d:%d, %d:%d]\n", X[posX], Y[posY], lix, X[lix], lsx, X[lsx], liy, Y[liy], lsy, Y[lsy]); 
      nitems = min((posX-lix),(lsy-posY));
      printf("items/lado: %d\n---------\n", nitems); 
      return years(X,Y, (lix+nitems), lsx, liy, (lsy-nitems));  
    }
  }
}

/* Halla la media entre dos números */
int med(int x, int y){ 
  return (int)(x+y)/2; 
}

/* Halla el mínimo entre dos números */
int min(int x, int y){ 
  if(x<=y)
    return x; 
  else
    return y; 
}

/* Halla el máximo entre dos números */
int max(int x, int y){ 
  if(x<=y)
    return y; 
  else
    return x; 
}


