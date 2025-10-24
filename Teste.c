#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <errno.h>
//#define valor_max_cadastro 10

//Estrutura data
typedef struct 
{
    int dia;
    int mes;
    int ano;

}Data;

//Estrutura categoria
typedef struct 
{
    int codigo;
    char tipo[50];
}Categoria;

typedef struct 
{
    int codigo; 
    int codigo_categoria; // igual a categoria.codigo
    char marca[25];
    char modelo[25];
    int ano;
    float diaria;
    int unidades_disponiveis;
    int unidades_alugadas;

}Veiculo;

typedef struct 
{
    int numero_locacao;
    int codigo_veiculo; // codigo igual ao veiculo.codigo
    Data data_retirada;
    Data data_devolucao;
    Data data_prevista_devolucao;
    char status[10];
    float diaria_Atraso;
    float valor_previsto;
    float valor_pago;

}Locacao;

/*Função para pausar a execução por um tempo em milisegundos.
  Exemplo de uso: delay(1000);*/
void delay(int tempo){
    fflush(stdout);
    Sleep(tempo);
}
/* Função para cadastrar uma categoria de veículo.
   Recebe um ponteiro para Categoria e solicita os dados ao usuário.*/
void categoria(Categoria *vet, int *qtd){
    int resposta;
    int iterador = 0;
    do{
        if(*qtd >= 10){
        printf("\nLimite de categorias cadastradas atingido. Nao e possivel cadastrar mais categorias.\n");
        break;
        }

        printf("\nCadastro da categoria %d\n", *qtd +1);
        printf("Digite o codigo da categoria: ");
        scanf(" %d", &vet->codigo);

        /*printf("\nDigite o tipo da categoria (ex: SUV, Economico): ");
        ler_str(vet->tipo, sizeof(vet->tipo));*/
        printf("Digite o tipo da categoria (ex: SUV, Economico): ");
        scanf(" %49[^\n]", vet->tipo);

        (*qtd)++;
        vet++;
        iterador++;

        printf("\n1 - Cadastrar nova categoria");
        printf("\n2 - Voltar para a pagina inicial\n");
        printf("Sua opcao: ");
        scanf(" %d", &resposta);


        while (resposta != 1 && resposta != 2) {
            printf("\n--- Resposta incorreta! ---\n");
            printf("1 - Cadastrar outra categoria\n");
            printf("2 - Voltar para o menu principal\n");
            printf("Sua opcao: ");
            scanf(" %d", &resposta);
        }
    }while(resposta != 2);

    if (iterador > 0){
        printf("\n%d categoria(s) cadastrada(s) com sucesso!\n", iterador);
    }
}
/* Função que exibe as categorias cadastradas.*/
void exibir_categoria(Categoria *vet, int tamanho){
    for (int i = 0; i < tamanho; i++) {
        printf("\nCodigo: %d | Tipo: %s\n", vet[i].codigo, vet[i].tipo);
    }
    delay(300);
}
/* Função que exclui alguma categoria cadastrada.*/
void excluir_categoria(Categoria *vet, int *tamanho){
    int resposta, indice_excluir = -1;
    printf("Qual categoria voce deseja excluir?\n");
    // Imprime as categorias existentes
    for (int i = 0; i < *tamanho; i++) {
        printf("\nCodigo: %d | Tipo: %s", vet[i].codigo, vet[i].tipo);
    }

    printf("\nSua opcao (digite o codigo): ");
    scanf(" %d", &resposta);

    // Varre o vetor até encontrar o codigo e salva o indice da posição
    for (int i = 0; i < *tamanho; i++) {
        if (resposta == vet[i].codigo) {
            indice_excluir = i;
            break;
        }
    }

    if (indice_excluir == -1) {
        printf("\nCodigo nao encontrado!\n");
        // MELHORIA 2: Adiciona delay no caso de erro.
        delay(300);
    } else {
        // O deslocamento está perfeito.
        for (int i = indice_excluir; i < *tamanho - 1; i++) {
            vet[i] = vet[i + 1];
        }
        (*tamanho)--;

        // MELHORIA 1: Adiciona mensagem de sucesso.
        printf("\nCategoria excluida com sucesso!\n");
        delay(300);
    }
}

void inserir_veiculo(Veiculo *vet, int *qtd, Categoria *vet_categoria, int tamanho){
    int categoria_valida, resposta = 0, iterador = 0;
    printf("\nCadastrando veiculo %d\n", *qtd + 1);
    printf("Digite o codigo do veiculo: ");
    scanf(" %d", &vet->codigo);

    // Cadastro do codigo categoria
    do{
        categoria_valida = 0;
        do {
            printf("\nCategorias disponiveis: \n");
            for (int i = 0; i < tamanho; i++) {
                printf(" -> Codigo: %d | Tipo: %s\n", vet_categoria[i].codigo, vet_categoria[i].tipo);
            }
            printf("\nDigite o codigo da categoria desejada: ");
            scanf(" %d", &vet->codigo_categoria);

            // Verifica se o código escolhido existe no vetor de categorias
            for(int i = 0; i < tamanho; i++){
                if (vet_categoria[i].codigo == vet->codigo_categoria) {
                    categoria_valida = 1;
                    break; 
                }
            }

            if (categoria_valida == 0) {
                printf("\n[ERRO] Codigo de categoria invalido! Tente novamente.\n");
            }

        } while (categoria_valida == 0);

        printf("\nDigite a marca do veiculo: ");
        scanf(" %49[^\n]", vet->marca);

        printf("\nDigite o modelo do veiculo: ");
        scanf(" %49[^\n]", vet->modelo);
        
        printf("\nDigite o ano de fabricacao do veiculo: ");
        scanf(" %d", &vet->ano);
        printf("\nDigite o valor da diaria do veiculo: ");
        scanf(" %f", &vet->diaria);
        printf("\nDigite o numero de unidades disponiveis do veiculo: ");
        scanf(" %d", &vet->unidades_disponiveis);

        (*qtd)++;
        vet++;
        iterador++;

        printf("\nVeiculo cadastrado!\n");
        printf("1 - Cadastrar outro carro \n2 - Voltar ao menu principal\n");
        printf("Sua opcao: ");
        scanf(" %d", &resposta); 

        while(resposta != 1 && resposta != 2){
            printf("\n[ERRO] Resposta incorreta\n");
            printf("1 - Cadastrar outro veiculo\n");
            printf("2 - Voltar para o menu principal\n");
            printf("Sua opcao: ");
            scanf(" %d", &resposta); 
        }
    } while(resposta != 2);
    
    delay(300);
}

void exibir_veiculo(Veiculo *vet, int tamanho){
    delay(300);
    printf("\nImprimindo veiculos: ");
    for(int i = 0; i < tamanho; i++){
        printf("\n--- Detalhes do Veiculo ---\n");
        printf("Codigo.............: %d\n", vet[i].codigo);
        printf("Codigo Categoria...: %d\n", vet[i].codigo_categoria);
        printf("Marca..............: %s\n", vet[i].marca);
        printf("Modelo.............: %s\n", vet[i].modelo);
        printf("Ano................: %d\n", vet[i].ano);
        printf("Valor da Diaria....: R$ %.2f\n", vet[i].diaria); // Formata para 2 casas decimais
        printf("Unidades Disponiveis: %d\n", vet[i].unidades_disponiveis);
        printf("Unidades Alugadas..: %d\n", vet[i].unidades_alugadas);
    }
}

int main(){
    int resposta, qtd_cadastrados = 3, qtd_veiculos = 3;
    Categoria vetor_categoria[10] = {
        {147, "Economico"},
        {258, "SUV"},
        {369, "Luxo"}
    };
    Veiculo vetor_veiculo[100] = {
        {1001, 1, "Fiat",   "Uno",  2015, 120.0f, 3, 0},
        {1002, 2, "Toyota","RAV4", 2020, 250.0f, 2, 1},
        {1003, 3, "BMW",   "320i", 2022, 450.0f, 1, 0}
    };

    do{
        printf("\n--- Sistema de Locacao de Veiculos ---\n");
        printf("Escolha uma das opcoes abaixo:\n");
        printf("1 - Cadastrar categoria\n");
        printf("2 - Exibir categorias\n");
        printf("3 - Excluir categoria\n");
        printf("4 - Inserir veiculo na frota\n");
        printf("5 - Exibir veiculos\n");
        printf("0 - Sair do sistema\n");
        printf("Sua opcao: ");
        scanf(" %d", &resposta);

        switch (resposta){

        case 1:
            if(qtd_cadastrados < 10){
                    printf("\n--- Cadastro de Categoria ---\n");
                    categoria(&vetor_categoria[qtd_cadastrados], &qtd_cadastrados);
            }
            else{
                printf("\nLimite de categorias cadastradas atingido. Nao e possivel cadastrar mais categorias.\n");
                delay(300);
            }
            delay(300);
            break;

        case 2:
            if(qtd_cadastrados == 0){
                printf("\nNenhuma categoria cadastrada, tecle 1 para cadastrar a primeira categoria.\n");
            }

            else{
                printf("\nCategorias cadastradas: \n");
                exibir_categoria(vetor_categoria, qtd_cadastrados);
            }
            delay(300);
            break;

        case 3:
            if(qtd_cadastrados <= 0){
                printf("\nNenhuma categoria cadastrada, Tecle 1 para cadastrar a primeira categoria.\n");
            }
            else{
                excluir_categoria(vetor_categoria, &qtd_cadastrados);
            }
            delay(300);
            break;
            
        case 4:
            if(qtd_cadastrados <= 0 ){
                printf("\nPara adicionar um veiculo, primeiro e necessario cadastrar uma categoria.\nPor favor, retorne ao menu e selecione a opcao 'Cadastrar Categoria'.\n");
            }
            else{
                if(qtd_veiculos < 100){
                    printf("\n---Cadastrando veiculo---\n");
                    inserir_veiculo(&vetor_veiculo[qtd_veiculos], &qtd_veiculos, vetor_categoria, qtd_cadastrados);
                }
                else{
                    printf("\nLimite de carros atingido. Nao e possivel adicionar mais carros a frota.\n");
                }
            }

            delay(300);
            break;

        case 5:
            if(qtd_veiculos <= 0){
                printf("\nNenhum veiculo cadastrado, primeiro cadastre um veiculo. \nPor favor, retorne ao menu e selecione a opcao 'Inserir veiculo na frota'.\n");
            }
            else{
                exibir_veiculo(vetor_veiculo, qtd_veiculos);
            }
            delay(300);
            break;

        case 0:
            printf("\nFim do programa.\n");
            break;
        default: 
            printf("\nOpcao invalida! Tente novamente.\n");
            delay(300);
            break;
        }

    } while(resposta != 0);

    return 0;
}