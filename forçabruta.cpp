#include <iostream>
#include <math.h>

using namespace std;

struct Prato {
  int lucro;
  int custo;
};

double maiorLucroEncontrado;
bool repeticao;

static float calcularRendaCardapio(Prato* pratos, int* cardapio,int j) {
    if(cardapio[j] == cardapio[j+1])
        if(cardapio[j] == cardapio[j+1] && repeticao == true)
            return 0;
        else{
            repeticao = true;
            return pratos[cardapio[j]].lucro/2;
        }
    else
    {
        repeticao = false;
        return pratos[cardapio[j]].lucro;
    }

}

static int* cardapioForcaBruta(Prato* pratos, int orcamento, int nDias, int nPratos) {
    maiorLucroEncontrado = 0.0;
    int* melhorCardapio;
    for(int i=0;i<pow(nPratos,nDias);i++)
    {
        repeticao = false;
        float lucroCardapio = 0;
        int orcamentoCardapio = 0;
        int* cardapio = new int[nDias];
        for(int j=0;j<nDias;j++)
            cardapio[j] = (int)(i / pow(nPratos,j)) % nPratos;
        for(int j=0;j<nDias-1;j++) {
            lucroCardapio += calcularRendaCardapio(pratos,cardapio,j);
            orcamentoCardapio += pratos[cardapio[j]].custo;
        }
        lucroCardapio += pratos[cardapio[nDias-1]].lucro; orcamentoCardapio += pratos[cardapio[nDias-1]].custo;

        if(orcamentoCardapio <= orcamento && lucroCardapio >= maiorLucroEncontrado){
            maiorLucroEncontrado = lucroCardapio;
            melhorCardapio = cardapio;
        }
    }
    return melhorCardapio;
}

int main() {
    int nDias,nPratos,orcamento;
    cin >> nDias >> nPratos >> orcamento;
    Prato* pratos = new Prato[nPratos+1];

    while(!(nDias == 0 && nPratos == 0 && orcamento == 0)){
        for(int i=0;i<nPratos;i++){
            Prato prato;
            cin >> prato.custo >> prato.lucro;
            pratos[i] = prato;
        }
        int* melhorCardapio = cardapioForcaBruta(pratos,orcamento,nDias,nPratos);

        if(maiorLucroEncontrado == 0)
            cout << "0.0\n";
        else
        {
            cout << maiorLucroEncontrado << "\n";
            for(int i=0;i<nDias;i++)
                cout << melhorCardapio[i] +1 << " ";
            cout << "\n";
        }
        cin >> nDias >> nPratos >> orcamento;
    }

    return 0;
}


