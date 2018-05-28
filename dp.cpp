#include <stdio.h>
#include <math.h>
#include <vector>

using namespace std;

double dp[22][51][2][105];
double maiorLucroEncontrado = 0;
int nDias,nPratos,orcamento;

struct Prato {
  int lucro;
  int custo;
};

Prato* pratos;

static void printMelhorCardapio(const vector<int> ultimoEstado) {
    int dia,prato,nRepeticoes,orcamento;
    dia=ultimoEstado[0];prato=ultimoEstado[1];nRepeticoes=ultimoEstado[2];orcamento=ultimoEstado[3];

    if(dia == 0) {
        printf("\n");
    } else {
        printf("%d ",ultimoEstado[1]);
        if(nRepeticoes == 0) {
            for(int i=1;i<=nPratos;i++)
                if(i != prato)
                    for(int j=0;j<2;j++)
                        if( (dp[dia-1][i][j][orcamento + pratos[prato].custo])
                           == (dp[dia][prato][nRepeticoes][orcamento] - pratos[prato].lucro) ) {
                            printMelhorCardapio({dia-1, i, j, orcamento + pratos[prato].custo });
                            j=3;i=6;
                        }
        } else if(nRepeticoes == 1) {
            printMelhorCardapio({ ultimoEstado[0]-1,ultimoEstado[1],0,ultimoEstado[3] + pratos[ultimoEstado[1]].custo });
        } else {
            printMelhorCardapio({ ultimoEstado[0]-1,ultimoEstado[1],1,ultimoEstado[3] + pratos[ultimoEstado[1]].custo });
        }
    }
}

static vector<int> cardapioDinamico() {
    std::vector<int> ultimoEstado;
    maiorLucroEncontrado = 0;
    for(int i=0;i<=nDias;i++)
        for(int j=0;j<=nPratos;j++)
            for(int k=0;k<2;k++)
                for(int l=0;l<=orcamento;l++)
                    dp[i][j][k][l] = -1;
    dp[0][0][0][orcamento] = 0;
    for(int i=0;i<nDias;i++)
        for(int j=0;j<=nPratos;j++)
            for(int k=0;k<2;k++)
                for(int l=0;l<=orcamento;l++)
                    if(dp[i][j][k][l] >= 0) {
                        for(int m=1;m<=nPratos;m++) {
                            if(l > pratos[m].custo) {
                                double lucro = dp[i][j][k][l];
                                int nRepeticoes = 0;
                                if(j == m) {
                                    lucro += pratos[m].lucro/2;
                                    nRepeticoes = 1;
                                }
                                else
                                    lucro += pratos[m].lucro;
                                if(lucro > dp[i+1][m][nRepeticoes][l - pratos[m].custo]) {
                                    dp[i+1][m][nRepeticoes][l - pratos[m].custo] = lucro;
                                    if(lucro >= maiorLucroEncontrado) {
                                        maiorLucroEncontrado = lucro;
                                        ultimoEstado = { i+1, m, nRepeticoes, l-pratos[m].custo };
                                    }
                                }

                            }
                        }
                    }
    if(ultimoEstado[0] != nDias) {
        printf("0.0\n");
        return {0,0,0,0};
    } else {
        printf("%.1f\n",maiorLucroEncontrado);
        return ultimoEstado;
    }
}


int main() {
    vector<int> ultimoEstado;
    while (scanf("%d %d %d", &nDias, &nPratos, &orcamento) == 3 && (nDias || nPratos || orcamento)) {
        pratos = new Prato[nPratos+1];
        for(int i=1;i<=nPratos;i++){
            Prato prato;
            scanf("%d %d", &prato.custo, &prato.lucro);
            pratos[i] = prato;
        }
        ultimoEstado = cardapioDinamico();
        printMelhorCardapio(ultimoEstado);
    }
    delete dp;
    delete pratos;
    ultimoEstado = vector<int>();
    return 0;
}


