#include <stdio.h>
#include <math.h>
#include <vector>

using namespace std;

double lucro;

struct Prato {
  int lucro;
  int custo;
};

static int* cardapioGuloso(Prato* pratos,int nDias,int nPratos, int orcamento) {
    lucro = 0;
    int* cardapio = new int[nDias+2];
    int orcamentoRestante = orcamento;
    double val=0;
    for(int i=0;i<nDias+2;i++)
        cardapio[i] = 0;
    int pratoAnterior;
    for(int i=2;i<nDias+2;i++) {
        for(int j=1;j<=nPratos;j++)
            if(pratos[j].custo < orcamentoRestante)
                if(cardapio[i-1] == j && cardapio[i-2] != j) {
                    if((double)(pratos[j].lucro/2)/pratos[j].custo > val) {
                        cardapio[i] = j;
                        val = (double) (pratos[j].lucro/2)/pratos[j].custo;
                    }
                } else if(cardapio[i-1] != j)
                    if( ((double)(pratos[j].lucro)/pratos[j].custo) > val) {
                        cardapio[i] = j;
                        val = (double) (pratos[j].lucro)/pratos[j].custo;
                    }
                if(cardapio[i] == 0)
                    return 0;
                orcamentoRestante -= pratos[cardapio[i]].custo;
                lucro += val * pratos[cardapio[i]].custo;
                val = 0;
    }
    return cardapio;
}

static void printCardapio(int* cardapio,int nDias,Prato* pratos) {
    if(cardapio == 0)
        printf("0.0");
    else {
        printf("%.1f\n",lucro);
        for(int i=2;i<nDias+2;i++)
            printf("%d ",cardapio[i]);
        printf("\n");
    }
}

int main() {
    int* cardapio;
    int nDias,nPratos,orcamento;
    while (scanf("%d %d %d", &nDias, &nPratos, &orcamento) == 3 && (nDias || nPratos || orcamento)) {
        Prato* pratos = new Prato[nPratos+1];
        for(int i=1;i<=nPratos;i++){
            Prato prato;
            scanf("%d %d", &prato.custo, &prato.lucro);
            pratos[i] = prato;
        }
        cardapio = cardapioGuloso(pratos,nDias,nPratos,orcamento);
        printCardapio(cardapio, nDias,pratos);
        delete pratos;
    }
    delete cardapio;
}


