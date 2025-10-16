#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct {
    int dia;
    int mes;
    int ano;
}Data;
typedef struct {
    int Código[9];
    char *Nome[9];
    char buffer[50];
}Categoria;
typedef struct {
    char Código[9];
    char *Marca[100];
    char *Modelo[100];
    struct Categoria categoria;
    int Ano[4];
    float Diaria[10];
    int qtdUnidades[101];
    int qtdAlugadas[101];
}Veículo;
typedef struct{
    int numero;
    codigoVeiculo[9];
    Data dataRetirada;
    Data dataPrevistaDevolucao;
    Data Devolucao;
    int status;
    float diariaAtrasoContrato;
    float valorPrevisto;
    float valorPago;
}Locacao;
void cadastrarCategoria(){
    printf("Digite o código da categoria: ");
    scanf("%s", &Categoria.Código);
    printf("Digite o nome da categoria: ");
    scanf("%s", &Categoria.Nome);
    printf("Categoria cadastrada com sucesso!\n");
}
void exibirCategorias(){
    for (int i = 0; i < 9; i++){
        if (Categoria.Código[i] != '\0'){
            printf("Código: %s\n", Categoria.Código[i]);
            printf("Nome: %s\n", Categoria.Nome[i]);
        }
    }
}
void InserirVeiculo(){
    printf("Digite o código do veículo: ");
    scanf("%s", &Veículo.Código);
    printf("Digite a marca do veículo: ");
    scanf("%s", &Veículo.Marca);
    printf("Digite o modelo do veículo: ");
    scanf("%s", &Veículo.Modelo);
    printf("Digite o código da categoria do veículo: ");
    scanf("%s", &Veículo.categoria.Código);
    printf("Digite o ano do veículo: ");
    scanf("%d", &Veículo.Ano);
    printf("Digite o valor da diária do veículo: ");
    scanf("%f", &Veículo.Diaria);
    printf("Digite a quantidade de unidades do veículo: ");
    scanf("%d", &Veículo.qtdUnidades);
    Veículo.qtdAlugadas = 0;
    printf("Veículo inserido na frota com sucesso!\n");
}
void exibirFrota(){
}
void realizarAluguel(){
}
void realizarDevolucao(){
}
void alugadosCategoria(){
}
void alugadosGeral(){
}
void LocacoesAbertas(){
}
int main(){
    char frota[100];
    char categorias[11];
    char contratos[1001];
    int Digito;
    printf("Bem-vindo ao sistema de locação de veículos!\n");
    printf("Escolha uma das opções abaixo:\n");
    printf("1 - Cadastrar categoria\n");
    printf("2 - Exibir categorias\n");
    printf("3 - Inserir veículo na frota\n");
    printf("4 - Exibir frota\n");
    printf("5 - Realizar aluguel\n");
    printf("6 - Realizar devolução\n");
    printf("7 - Veículos alugados por categoria\n");
    printf("8 - Veículos alugados (geral)\n");
    printf("9 - Locações em aberto\n");
    printf("0 - Sair do sistema\n");
    scanf("%d", &Digito);
    switch (Digito){
    case 1:
        cadastrarCategoria();
        break;
    case 2:
        exibirCategorias();
        break;
    case 3:
        InserirVeiculo();
        break;
    case 4:
        exibirFrota();
        break;
    case 5:
        realizarAluguel();
        break;
    case 6:
        realizarDevolucao();
        break;
    case 7:
        alugadosCategoria();
        break;
    case 8:
        alugadosGeral();
        break;
    case 9:
        LocacoesAbertas();
        break;
    case 0:
        printf("Saindo do sistema...\n");
        break;
    }
}

