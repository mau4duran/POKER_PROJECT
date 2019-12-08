#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>

/*Consrant Definitions such as deck size, unicodes for */
#define SIZE 52
#define HEART "\u2661"
#define DIAMOND "\u2662"
#define SPADE "\u2664"
#define CLOVER "\u2667"
#define HAND_SIZE 5

typedef enum {False, True} boolean;

typedef struct{
    int valor;
    char simbolo;
    char* palo; //c for corazon, d for diamond, e for espada, t for trebol
    int currentlyUsed; //0 Falso. Sirve para no repetir cartas
} Carta;

typedef struct{
    Carta mano[HAND_SIZE];
    int indices[HAND_SIZE];
} Jugador;

Carta deck[SIZE];

int indicesUsuario[HAND_SIZE];
int valoresUsuario[HAND_SIZE];
int indicesPC[HAND_SIZE];
int valoresPC[HAND_SIZE];

Jugador usuario;
Jugador pc;

void swap (int arr[], int index[], int i1, int i2){
    int tmp = arr[i1];
    int tmp2 = index[i1];
    arr[i1] = arr[i2];
    index[i1]= index[i2];
    index[i2]=tmp2;
    arr[i2] = tmp;
}

void ordenamientoBurbuja(int arr[], int index[]){
    int i, j;
    for (i=HAND_SIZE-1; i>=1; i--){
        for (j=0; j<i; j++)
            if (arr[j+1] < arr[j]) {
                swap(arr, index, j, j+1);
            }
        }
    }

int aleatorioEntre(int x, int y){
    int z = y-x+1;
    return (rand()%(z))+ x;
}

void imprimirCartas(Jugador player) {
    for (int i = 0; i < HAND_SIZE; i++) {
        printf("__________\t");
    }
    printf("\n" );
    for (int i = 0; i < HAND_SIZE; i++) {
        printf("|%s       |\t", player.mano[i].palo);
    }
    printf("\n" );
    for (int i = 0; i < HAND_SIZE; i++) {
        printf("|        |\t");
    }
    printf("\n" );

    for (int i = 0; i < HAND_SIZE; i++) {
        if (player.mano[i].valor==10){
            printf("|   10   |\t");
        }else{
            printf("|   %c    |\t",player.mano[i].simbolo);
        }
    }

    printf("\n" );

    for (int i = 0; i < HAND_SIZE; i++) {
        printf("|        |\t");
    }
    printf("\n" );

    for (int i = 0; i < HAND_SIZE; i++) {
        printf("|      %s |\t", player.mano[i].palo);
    }
    printf("\n" );

    for (int i = 0; i < HAND_SIZE; i++) {
        printf("——————————\t");
    }
    printf("\n\n" );
}

void generarMazo() {
    int count=0;
    for (int i = 1; i < HAND_SIZE; i++) {
        for (int k = 2; k < 15; k++) {
            deck[count].valor=k;
            switch (k) {
                case 11: deck[count].simbolo='J'; break;
                case 12: deck[count].simbolo='Q'; break;
                case 13: deck[count].simbolo='K'; break;
                case 14: deck[count].simbolo='A'; break;
                default: deck[count].simbolo= k+'0';
            }

            switch (i) {
                case 1: deck[count].palo=HEART; break;
                case 2: deck[count].palo=DIAMOND; break;
                case 3: deck[count].palo=SPADE; break;
                case 4: deck[count].palo=CLOVER; break;
            }

            deck[count].currentlyUsed=0;
                count++;
        }
    }
}


void repartir() {
    int user = 0;
    int ord = 0;
    int valores[10]={-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};

    for (int i = 0; i < 10; i++) {
        int x = aleatorioEntre(0, SIZE-1);

        if (deck[x].currentlyUsed==1) {
            i--;
            continue;

        }else{
            valores[i]=x;
            if (i%2==0) {
                indicesUsuario[user]=x;
                valoresUsuario[user]=deck[x].valor;
                usuario.mano[(int)i/2].valor=deck[x].valor;
                usuario.mano[(int)i/2].simbolo=deck[x].simbolo;
                usuario.mano[(int)i/2].palo=deck[x].palo;
                usuario.indices[(int)i/2]=x;
                deck[x].currentlyUsed=1;
                user++;
            }else{
                indicesPC[ord]=x;
                valoresPC[ord]=deck[x].valor;

                pc.mano[(int)i/2].valor=deck[x].valor;
                pc.mano[(int)i/2].simbolo=deck[x].simbolo;
                pc.mano[(int)i/2].palo=deck[x].palo;
                pc.indices[(int)i/2]=x;
                deck[x].currentlyUsed=1;
                ord++;
            }
        }
    }

}

void ordenarCartas(int ind[], int pcind[]){
    printf("\n\n\n");
    ordenamientoBurbuja(valoresUsuario, indicesUsuario);
    ordenamientoBurbuja(valoresPC, indicesPC);
    for (int i = 0; i < HAND_SIZE; i++) {
        usuario.mano[i].valor=deck[ind[i]].valor;
        usuario.mano[i].simbolo=deck[ind[i]].simbolo;
        usuario.mano[i].palo=deck[ind[i]].palo;
        usuario.indices[i]=ind[i];

        pc.mano[i].valor=deck[pcind[i]].valor;
        pc.mano[i].simbolo=deck[pcind[i]].simbolo;
        pc.mano[i].palo=deck[pcind[i]].palo;
        pc.indices[i]=pcind[i];
    }
}

void modificar(int jugador, int index){
    if (jugador==1) {
        for (int i = 0; i < 1; i++) {
            int x = aleatorioEntre(0, SIZE-1);
            if (deck[x].currentlyUsed==1) {
                i--;
                continue;
            }else{
                indicesUsuario[index]=x;
                valoresUsuario[index]=deck[x].valor;
                usuario.mano[index].valor=deck[x].valor;
                usuario.mano[index].simbolo=deck[x].simbolo;
                usuario.mano[index].palo=deck[x].palo;
                usuario.indices[index]=x;
                deck[x].currentlyUsed=1;
            }
        }
    } else{
        for (int i = 0; i < 1; i++) {
            int x = aleatorioEntre(0, SIZE-1);
            if (deck[x].currentlyUsed==1) {
                i--;
                continue;
            }else{
                for (int i = 0; i < 1; i++) {
                    int x = aleatorioEntre(0, SIZE-1);
                    if (deck[x].currentlyUsed==1) {
                        i--;
                        continue;
                    }else{
                        indicesPC[index]=x;
                        valoresPC[index]=deck[x].valor;
                        pc.mano[index].valor=deck[x].valor;
                        pc.mano[index].simbolo=deck[x].simbolo;
                        pc.mano[index].palo=deck[x].palo;
                        pc.indices[index]=x;
                        deck[x].currentlyUsed=1;
                    }
                }
            }
        }
    }
}

void deseaCambio() {
    char w;
    int condition=0, cambiar, camb, loop=1;

    do {
        printf("\nQuieres cambiar cartas? ( S / N ): ");
        scanf("%c", &w);

        if (w=='S' || w=='s') {
            condition=1;
            printf("Cuantas cartas quieres cambiar 1-3: ");
            scanf("%d", &cambiar);
            if (cambiar > 0 && cambiar < 4) {
                for (int i = 0; i < cambiar; i++) {
                    printf("¿Que carta quieres cambiar? (Posicion de la carta 1-5)\n");
                    scanf("%d", &camb);
                    modificar(1, camb-1);
                }
                system("clear");
                ordenarCartas(indicesUsuario, indicesPC);
                printf("Tus cartas:\n");
                imprimirCartas(usuario);
                loop=0;
            } else{
                printf("Error. Vuelva a intentar");
                continue;
            }
            break;
        } else if(w=='N' || w=='n'){
            condition= 0;
            loop=0;
            break;
        } else{
            printf("Respuesta no reconocida. Escriba S para si o N para no\n");
        }
    } while(loop==1);
}

int valorMano(int indices[]){
    Carta A = deck[indices[0]], B = deck[indices[1]], C = deck[indices[2]], D = deck[indices[3]], E = deck[indices[4]];
    boolean seguidas = (A.valor == B.valor-1 && B.valor == C.valor-1 && C.valor == D.valor-1 && D.valor == E.valor-1)? True: False;
    boolean mismoPalo = (A.palo == B.palo && B.palo == C.palo && C.palo == D.palo && D.palo == E.palo)? True: False;

    // Royal Flush?
    if (seguidas && mismoPalo && A.valor == 10) return 900;
    // Straight Flush?
    if (seguidas && mismoPalo) return 800 + A.valor;

    //Four of a kind?
    if (((A.valor == B.valor||D.valor == E.valor) && B.valor == C.valor && C.valor == D.valor)) return 700 + C.valor;

    // Full House?
    if ((A.valor == B.valor && B.valor == C.valor && D.valor == E.valor) ||
    (A.valor == B.valor && C.valor == D.valor && D.valor == E.valor))
    return 600 + C.valor;

    // Flush?
    if (mismoPalo) return 500 + E.valor;

    // Straight?
    if (seguidas) return 400 + A.valor;

    // Three of a kind?
    if ((A.valor == B.valor && B.valor == C.valor) ||
    (B.valor == C.valor && C.valor == D.valor) ||
    (C.valor == D.valor && D.valor == E.valor))
    return 300 + C.valor;  // Note that C will always be part of the three equal cards

    // Two pairs?
    if ((A.valor == B.valor && C.valor == D.valor) ||
    (A.valor == B.valor && D.valor == E.valor) ||
    (B.valor == C.valor && D.valor == E.valor)){
        if (B.valor > D.valor) return 200 + B.valor;
        else return 200 + D.valor; // if the biggest pair value of two hands was equal, the value of the lowest pair is considered...
        //...but I can't do that here w/o knowing what the other hand has so if that happens a tie will have to do
    }
    // One pair?
    if (A.valor == B.valor) return 100 + A.valor;
    if (B.valor == C.valor) return 100 + B.valor;
    if (C.valor == D.valor) return 100 + C.valor;
    if (D.valor == E.valor) return 100 + D.valor;

    // Else, the higher card's value is used
    return E.valor;
}

void Mano(int valor) {
    if (valor==900) {
        printf("Flor imperial.\n");
    } else if(valor>=800){
        printf("Corrida del mismo Palo.\n");
    } else if(valor>=700){
        printf("Poker.\n");
    } else if (valor>=600) {
        printf("Full House.\n");
    } else if (valor>=500) {
        printf("Color.\n");
    } else if (valor>=400) {
        printf("Corrida.\n");
    } else if (valor>=300) {
        printf("Tercia.\n");
    } else if (valor>=200) {
        printf("Dos pares.\n");
    } else if (valor>=100) {
        printf("Par.\n");
    } else{
        printf("Carta Alta.\n");
    }
}

void Tfrequencias(int array[],int freq[], int freqVal[]){
    int k=0;
    int r=0;
    freq[0]=1;
    int valor=0;
    freqVal[valor]=array[0];

    for (int i = 0; i < HAND_SIZE; i++) {
        if (array[i+1]==0) {
            freq[k+1] = 0;
            return;
        }
        if(array[i]==array[i+1]) {
            freq[k]+=1;
            r++;
        } else{
            k+=1;
            r++;
            valor++;
            freqVal[valor]=array[r];
            freq[k]=1;
        }
    }
}

int cambioPC(int valores[], int freq[]){
    int w = valorMano(indicesPC);
    int value=-1;
    int condition = -1;

    if (w>=300&&w<400) {
        for (int i = 0; i < 5; i++) {
            if (freq[i]==3) {
                value=valores[i];
                condition = 0;
            }
        }

    } else if (w>=200) {
        for (int i = 0; i < 5; i++) {
            if (freq[i]==1) {
                value=valores[i];
                condition = 1;
            }
        }

    } else if (w>=100) {
        for (int i = 0; i < 5; i++) {
            if (freq[i]==2) {
                value=valores[i];
                condition = 2;
            }
        }
    } else{
        modificar(0,0);
        modificar(0,2);
        modificar(0,4);
        return 3;
    }

    for (int i = 0; i < 5; i++) {
        switch (condition) {
            case 0:
            if (pc.mano[i].valor!=value) {
                modificar(0,i);
                return 2;
            }
            break;

            case 1:
            if (pc.mano[i].valor==value) {
                modificar(0,i);
                return 1;
            }
            break;

            case 2:
            if (pc.mano[i].valor!=value) {
                modificar(0,i);
                return 3;
            }
            break;
        }
    }

    return 0;

}


int main(void) {
    srand(time(NULL));
    setvbuf(stdout, NULL, _IONBF, 0);
    int valFreqUsr[HAND_SIZE] ={0,0,0,0,0};
    int freqUsr[HAND_SIZE] ={0,0,0,0,0};

    int valFreqPC[HAND_SIZE] ={0,0,0,0,0};
    int freqPC[HAND_SIZE] ={0,0,0,0,0};

    generarMazo();
    repartir();
    ordenarCartas(indicesUsuario, indicesPC);
    imprimirCartas(usuario);

    Tfrequencias(valoresPC,freqPC,valFreqPC);

    cambioPC(valFreqPC,freqPC);

    deseaCambio();

    printf("La PC cambio %d cartas.\n", cambioPC(valFreqPC,freqPC));


    printf("Presione enter para ver la mano de la computadora ");
    getchar();
    getchar();

    printf("PC\n");

    ordenarCartas(indicesUsuario, indicesPC);

    imprimirCartas(pc);

    int x = valorMano(indicesPC);
    int y = valorMano(indicesUsuario);


    printf("Usuario: ");
    Mano(y);

    printf("\n");


    printf("PC: ");
    Mano(x);


    if (y>x) {
        printf("\nUSUARIO GANA!!\n");
    } else if(x>y){
        printf("\nPC GANA\n");
    } else{
        printf("\nEmpate\n");
    }


	return EXIT_SUCCESS;
}
