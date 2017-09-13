#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define BRANCO 2
#define CINZA 3
#define PRETO 4

typedef struct{
    int v1,v2;
    int peso;
} Aresta;

struct grafo{
    int v;
    int a;
    Aresta *arest;
    int maxArest;
};

typedef struct grafo *Grafo;

Grafo iniciaGrafo(int v){
    Grafo G = malloc(sizeof(struct grafo));
    G->v = v;
    G->a = 0;
    G->maxArest = v;
    G-> arest = malloc(v * sizeof(Aresta));
    return G;
}

void insere(Grafo G, int v1, int v2, int peso){
    int i;
    for(i=0;i<G->a;i++){
        Aresta a = G->arest[i];
        if(a.v1 == v1 && a.v2 == v2)
            return;
    }
    if(G->a == G->maxArest){
        G->maxArest *= 2;
        G-> arest = realloc(G->arest,G->maxArest * sizeof(Aresta));
    }
    G->arest[G->a].v1 = v1;
    G->arest[G->a].v2 = v2;
    G->arest[G->a].peso = peso;
    G->a++;
}

int busca(Grafo g, int v1, int v2,int b){
    int i;
	for(i=0; i<=b; i++){

		if( g->arest[i].v1==v2 && g->arest[i].v2==v1)
            return 1;
	}
    return 0;
}

int randV(Grafo G){
    //double r;
     srand( time(NULL) );
    //r = (rand()+430) / (RAND_MAX + 89.0);
    //printf("%d\n",(int) r*(G->v) );
    //getchar();
    int r;

    //getchar();
    r= 1+(rand()%G->v);
    //printf("%d\n",r );
    return r;
}

Grafo constroiGrafo(int vertice, float densidade){
    int arestas = (int)(densidade*vertice*(vertice-1))/2;
    int v1,v2;
    Grafo G = iniciaGrafo(vertice);
    int i=0;
    int peso;

    while(G->a < arestas){
        v1 = randV(G);
        v2 = randV(G);
        srand( time(NULL) );
        peso = 1 + (rand()%100);
        if(i==0  && v1 != v2 ) { insere(G, v1, v2, peso); i++;}
        else if( v1 != v2)
        {
            //printf("%d\n",i);
            int res = busca(G, v1, v2, i);
            if(res ==0 ){
            insere(G, v1, v2, peso); i++;
            }
        }
    }
    //printf("saiu");
    //getchar();
    return G;
}



void printmadjacencia(Grafo G){
int i,j,m[G->v+1][G->v+1],k,l,p; Aresta a;
        //zerando a matriz
        for(i=1; i<=G->v; i++){
            for(j=1; j<=G->v;j++){
                m[i][j]=0;
            }
        }

        //atribuindo onde tiver ligações de vertices
        for(i=0; i<G->maxArest; i++){
            a= G->arest[i];
            m[a.v1][a.v2]=1;
            m[a.v2][a.v1]=1;
        }

            //aqui eu imprimo na forma de matriz os vertices e arestas
            for(i=1; i<=G->v; i++){

                if(i==1){ printf("  "); for(p=1; p<=G->v;p++)printf(" %d",p); printf("\n");  }

                 printf("%d|",i);

                for(j=1; j<=G->v;j++){
                  printf(" %d",m[i][j]);
                }
                printf("\n");
            }
printf("\n");
}

void dimacs(int nv, int na){
int dim[na][4],i,j,l,c;


for(i=0; i<=na; i++){
 	for(j=0;  j<=3; j++){

 		dim[i][j]=0;
 		
 	}

 }

 for(i=0; i<na; i++){
 	for(j=1;  j<2; j++){
		printf("Informe a linha: ");
 		scanf("%d", &l);
 		printf("Informe a coluna: "); 
 		scanf("%d", &c); 
 		printf("Informe o peso: "); 
 		scanf(" %d", &dim[l][c]);
 		
 	}

 }

 for(i=1; i<=na; i++){
 	for(j=1; j<na; j++){

 		if(dim[i][j]!=0 )printf("%d %d %d\n",i,j,dim[i][j]);
 	}
 }
  printf("\n");
}



void printmincidencia(Grafo G){
int i,j,m[G->v][G->maxArest],k,l,p; Aresta a;
        //zerando a matriz
        for(i=0; i<=G->v; i++){
            for(j=0; j<=G->a;j++){
                m[i][j]=0;
            }
        }
        //atribuindo onde tiver ligações de vertices
        for(i=0; i<G->maxArest; i++){
            a= G->arest[i];
            m[a.v1][i+1]=1;
            m[a.v2][i+1]=1;
        }


            //imprimir na forma de matriz os vertices e arestas
            for(i=1; i<=G->v; i++){
                if(i==1){
                    printf("   E%d",i);
                    for(p=2; p<=G->a;p++)
                        printf(" E%d",p);
                    printf("\n");
                }

                 printf("%d|",i);

                for(j=1; j<=G->a;j++)
                    printf("  %d",m[i][j]);
                printf("\n");
            }
printf("\n");
}

void imprimi(Grafo G){
    int i;
    for(i=0;i<G->a;i++){
        Aresta a = G->arest[i];

        printf("%d->%d   peso: %d",a.v1,a.v2,a.peso);
        printf("\n");
    }
    printf("\n");
}

void printlistadjacencia(Grafo G){
    int i,p;
    for(i=0; i<G->v; i++){
        printf("|%d|->",i+1);

        for(p=0; p <G->a;p++){
            if(G->arest[p].v1 == i+1)
                printf("|%d|->", G->arest[p].v2);
        }
        printf("\n\n");
    }
 }

void BFS(Grafo G, int s){ //busca de profundidade
    int i,j=0,x,*aux;
    cor = (int *)malloc((G->v) * sizeof(int));
    d = (int *)malloc((G->v) * sizeof(int));
    pi = (int *)malloc((G->v) * sizeof(int));
    aux = (int *)malloc((G->v) * sizeof(int));

    for(i=1;i<G->v;i++){
        cor[i] = BRANCO;
        d[i] = 0;
        pi[i] = -1;
    }

    cor[s] = CINZA;
    d[s] = 0;
    pi[s] = -1;

    Fila f;
    FFVazia(*f);
    Enfileirar(*f,s);

    while(!Vazia(*f)){
        x = Desenfileirar(*f,s);
        for(i=0;i<G->v;i++){
            if(G->v[x][i]==1){
                aux[j] = i;
                j++;
            }
        }
        i=0;

        do{
            if(cor[aux[i]] == BRANCO){
                cor[aux[i]] = CINZA;
                d[aux[i]] = d[x] + 1;
                pi[aux[i]] = x;

                Enfileirar(*f,aux[i]);
            }
            i++;
        }while(i<j);
        cor[x] = PRETO;
        j=0;
    }
}





 void isomorfos (Grafo G, Grafo H){
    if(G->v == H->v && G->a == H->a)
        printf("\nOs grafos dados podem ser isomorfos");
    else printf("\nOs grafos dados nao sao isomorfos");
 }

 int grauVertice(Grafo G, int v){
    int i, grau=0;
    for(i=0;i<G->a;i++){
        if((v == G->arest[i].v1) || (v == G->arest[i].v2))
            grau++;
    }
    return grau;
 }

 void verticesAdjacentes(Grafo G, int a, int b){
    int i;
    for(i=0;i<G->a;i++){
        if((a == G->arest[i].v1 && b == G->arest[i].v2) || (b == G->arest[i].v1 && a == G->arest[i].v2)){
			printf("\nOs vertices dados sao adjacentes");
            break;
		} 
        else{
		 printf("\nOs vertices dados nao sao adjacentes");
        	break; 
		}
    }
 }

void substituirPeso(Grafo G, int a, int b, int c){
    int i,flag=0;
    for(i=0;i<G->a;i++){
        if((a == G->arest[i].v1 && b == G->arest[i].v2) || (b == G->arest[i].v1 && a == G->arest[i].v2)){
            G->arest[i].peso = c;
            printf("\nAlteracao efetuada com sucesso!\n");
            flag = 1;
        }
    }
    if (flag == 0)
        printf("\nAresta nao encontrada!\n");
}


void trocarVertices(Grafo G, int a, int b){
    int i,aux;
    for(i=0;i<G->a;i++){
        if((G->arest[i].v1 == a && G->arest[i].v2 == b) || (G->arest[i].v1 == b && G->arest[i].v2 == a)){
            aux = G->arest[i].v1;
            G->arest[i].v1 = G->arest[i].v2;
            G->arest[i].v2 = aux;
        }else if(G->arest[i].v1 == a){
            G->arest[i].v1 == b;
        }else if(G->arest[i].v1 == b){
            G->arest[i].v1 == a;
        }else if(G->arest[i].v2 == a){
            G->arest[i].v2 == b;
        }else if(G->arest[i].v2 == b){
            G->arest[i].v2 == a;
        }
    }
}


int testaAresta(Grafo G, int v1, int v2){ 
	int i; 
	for(i=0; i<G->a; i++){
	Aresta a = G->arest[i]; 
		if((a.v1 == v1 && a.v2 == v2) || (a.v1 == v2 && a.v2 == v1)){
			return 1; 
		}
	}

}


void exibeArestasadjacentes(Grafo G, int v1, int v2){
	Aresta adj[100]; 
	int i, j=0;
	if (testaAresta(G, v1, v2) == 1){ 
		for(i=0;i<G->a;i++){
    		Aresta a = G->arest[i];
    			if(a.v1 == v1 || a.v2 == v2 || a.v1 == v2 || a.v2 == v1){ 
    			adj[j] = a; 
				j++; 	
			
		}
	}
	
	for (i=0; i<j; i++){
		printf("%d->%d\n", adj[i].v1, adj[i].v2);
		
	}
	
}else{ 
	printf("Aresta nao existe no grafo!!\n\n"); 
}	
	
}


void exibeVerticeadjacentes(Grafo G, int v1){ 
	int vertices[100]; 
	int i, j=0; 
	for (i=1; i<G->a; i++){ 
		if(testaAresta(G, v1, i) == 1){ 
			vertices[j] = i; 
			j++; 
	
		}
	}
	for (i=0; i<j; i++){ 
		printf("%d\n", vertices[i]); 
	}
}

void exibeArestasincidentes(Grafo G, int v1){ 
	int i, j;  
	for (i=0; i<G->a; i++){ 
		Aresta a = G->arest[i]; 
		if(a.v1 == v1 || a.v2 == v1){ 
			printf("%d->%d\n", a.v1, a.v2); 
		}
		
	} 
} 


int main(){ 
	int vert, op1;
    int v1, v2;
    float dens;
    do{
    system("cls");
   	printf("Bruno A. Camarda \nMatheus Takeshi Y. Ikeda \nOlimpio Pimenta");
    printf("\n\n>>>>>> Construindo o grafo: "); 	
    printf("\n01. Informar vertices e densidade"); 
	printf("\n02. Ler grafo em formato DIMACS");
	printf("\n03. Exibir Matriz de Adjacencia");
	printf("\n04. Exibir Matriz de Incidencia");
	printf("\n05. Exibir Lista de Adjacencia");
	printf("\n06. Determinar se 2 grafos sao isomorfos");
	printf("\n07. Imprimir arestas adjacentes a uma aresta");
	printf("\n08. Imprimir vertices adjacentes a um vertice"); 
	printf("\n09. Imprimir arestas incidentes a um vertice");
	printf("\n10. Exibir grau de um vertice");
	printf("\n11. Determinar se dois vertices sao adjacentes");
	printf("\n12. Substituir um peso em uma aresta");
	printf("\n13. Trocar dois vertices");
	printf("\n14. Algoritmo de Djikstra");
	printf("\n15. Busca em largura");
	printf("\n16. Busca em profundidade");
	printf("\n17. IMPRIMIR GRAFO");
	printf("\n00. SAIR\n\n");
	scanf("%d", &op1); 	
	switch(op1){ 
		case 1:
		system("cls"); 
		printf("\nInforme o numero de vertices: ");
		scanf("%d",&vert);
    	printf("\nInforme a densidade: ");
    	scanf("%f",&dens);
    	Grafo G=constroiGrafo(vert, dens);
		imprimi(G);
		system("pause"); 
		break; 
						
		case 2:
		system("cls"); 
		printf("\nInforme o numero de vertices: ");
		scanf("%d", &v1);
		printf("\nInforme o numero de arestas");  
		scanf("%d", &v2); 
		dimacs(v1, v2); 
		break; 
		
		
		case 3: 
		system("cls"); 
		printf("\n\n>> MATRIZ DE ADJACENCIA\n\n");
		printmadjacencia(G); 
    	system("pause"); 
		break; 
		
		case 4: 
		system("cls"); 
		printf("\n\n>> MATRIZ DE INCIDENCIA\n\n");
		printmincidencia(G);
    	system("pause"); 
		break;
	
		case 5: 
		system("cls"); 
		printf("\n\n>> LISTA DE ADJACENCIA\n\n");
		printlistadjacencia(G);
    	system("pause"); 
		break;
	
		case 6: 
		system("cls"); 
		printf("\n\n>> GRAFOS ISOMORFOS\n\n");
		printf("Adicione um novo grafo: ");
		printf("\nInforme o numero de vertices: ");
		scanf("%d",&vert);
    	printf("\nInforme a densidade: ");
    	scanf("%f",&dens);
    	Grafo H=constroiGrafo(vert,dens);
		imprimi(H);
		printf("\n\n"); 
		isomorfos(G, H); 
    	system("pause"); 
		break;
		
		case 7: 
		system("cls"); 
		printf("\n\n>> ARESTAS ADJACENTES A UMA ARESTA\n\n");
		printf("Insira uma aresta para ver suas adjacentes: \n"); 
		printf("Vertice 1: "); 
		scanf("%d", &v1);
		printf("Vertice 2: "); 
		scanf("%d", &v2);
		exibeArestasadjacentes(G, v1, v2); 
    	system("pause"); 
		break;
		
		case 8: 
		system("cls"); 
		printf("\n\n>> VERTICES ADJACENTES A UM VERTICE\n\n");
		printf("Insira um vertice para ver seus adjacentes: \n"); 
		printf("Vertice 1: "); 
		scanf("%d", &v1);
		exibeVerticeadjacentes(G, v1); 
    	system("pause"); 
		break;
		
		case 9: 
		system("cls"); 
		printf("\n\n>> ARESTAS INCIDENTES A UM VERTICE\n\n");
		printf("Insira um vertice para ver suas arestas incidentes: \n"); 
		printf("Vertice 1: "); 
		scanf("%d", &v1);
		exibeArestasincidentes(G, v1);
    	system("pause"); 
		break;
		
		case 10: 
		system("cls"); 
		printf("\n\n>> GRAU DE UM VERTICE\n\n");
		printf("Informe um vertice para saber seu grau: \n"); 
		printf("Vertice: "); 
		scanf("%d", &v1); 
		vert = grauVertice(G, v1); 
    	printf("%d", vert);
		system("pause"); 
		break;
		
		case 11: 
		system("cls"); 
		printf("\n\n>> DETERMINAR SE DOIS VERTICES SAO ADJACENTES\n\n");
		printf("Informe um vertice: "); 
		scanf("%d", &v1); 
		printf("Informe o segundo vertice: "); 
		scanf("%d", &v2); 
		verticesAdjacentes(G, v1, v2); 
    	system("pause"); 
		break;
		
		case 12: 
		system("cls"); 
		printf("\n\n>> SUBSTITUIR PESO EM UMA ARESTA\n\n");
		printf("Informe os dois vertices da aresta que deseja substituir o peso: \n"); 
		printf("Vertice 1: "); 
		scanf("%d", &v1);
		printf("Vertice 2: "); 
		scanf("%d", &v2);
		printf("Informe o novo peso: "); 
		scanf("%d", &vert);
		substituirPeso(G, v1, v2, vert); 
    	system("pause"); 
		break;
	
		case 13: 
		system("cls"); 
		printf("\n\n>> TROCA DE VERTICES\n\n");
		printf("Insira os dois vertices que deseja trocar\n\n");
		printf("Vertice 1: "); 
		scanf("%d", &v1); 
		printf("Vertice 2: "); 
		scanf("%d", &v2); 
		trocarVertices(G, v1, v2); 
    	system("pause"); 
		break;
		
		case 14: 
		system("cls"); 
		printf("\n\n>> ALGORITMO DE DJKISTRA\n\n");
    	system("pause"); 
		break;
		
		case 15: 
		system("cls"); 
		printf("\n\n>> BUSCA EM LARGURA\n\n");
    	system("pause"); 
		break;
		
		case 16: 
		system("cls"); 
		printf("\n\n>> BUSCA EM PROFUNDIDADE\n\n");
    	system("pause"); 
		break;
		
		case 17: 
		system("cls"); 
		imprimi(G); 
		system("pause"); 
		break; 
		
		}	
    		
  
	}while(op1!=0); 

return (0);
}


