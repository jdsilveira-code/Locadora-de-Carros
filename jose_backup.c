#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

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

/*Função que limpa o buffer
  Deve ser utilizada antes de fgets, getline, getchar e após scanfs*/
void limpar_buffer(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

/*Função que substitui o scanf para strings
  Exemplo de uso: ler_str(variavel)*/
void ler_str(char *string, int tamanho){
    fgets(string, tamanho, stdin);
    string[strcspn(string, "\n")] = '\0';

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
        printf("\nDigite o codigo da categoria: ");
        scanf("%d", &vet->codigo);
        limpar_buffer();

        printf("Digite o tipo da categoria (ex: SUV, Economico): ");
        ler_str(vet->tipo, sizeof(vet->tipo));

        (*qtd)++;
        vet++;
        iterador++;

        printf("\n1 - Cadastrar nova categoria");
        printf("\n2 - Voltar para a pagina inicial\n");
        printf("Sua opcao: ");
        scanf("%d", &resposta);
        limpar_buffer();

        while (resposta != 1 && resposta != 2) {
            printf("\n--- Resposta incorreta! ---\n");
            printf("1 - Cadastrar outra categoria\n");
            printf("2 - Voltar para o menu principal\n");
            printf("3 - Excluir categoria\n");
            printf("Sua opcao: ");
            scanf("%d", &resposta);
            limpar_buffer();
        }
    }while(resposta != 2);

    if (iterador > 0){
        printf("\n%d categoria(s) cadastrada(s) com sucesso!\n", iterador);
    }
}
/* Função que exibe as categorias cadastradas.*/
void exibir_categoria(Categoria *vet, int tamanho){

    for(int i = 0; i < tamanho; i++){
        printf("\nCodigo: %d\n", vet[i].codigo);
        printf("Tipo: %s\n\n", vet[i].tipo);
    }
    delay(300);
}

void excluir_categoria(Categoria *vet, int *tamanho){
    int resposta, indice_excluir = -1;

    printf("\n--- Excluir Categoria ---\n");
    printf("Qual categoria voce deseja excluir?\n");
    for (int i = 0; i < *tamanho; i++) {
        printf("\nCodigo: %d | Tipo: %s", vet[i].codigo, vet[i].tipo);
    }
    printf("\n\nSua opcao (digite o codigo): ");
    scanf("%d", &resposta);
    limpar_buffer();

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
    int categoria_valida = 0;
    printf("\nCadastrando veiculo %d\n", *qtd + 1);
    printf("Digite o codigo do veiculo: ");
    scanf("%d", &vet->codigo);
    limpar_buffer();

    // Cadastro do codigo categoria
    do {
        printf("\nCategorias disponiveis: \n");
        for (int i = 0; i < tamanho; i++) {
            printf(" -> Codigo: %d | Tipo: %s\n", vet_categoria[i].codigo, vet_categoria[i].tipo);
        }

        printf("\nDigite o codigo da categoria desejada: ");
        scanf("%d", &vet->codigo_categoria);
        limpar_buffer();

        // Verifica se o código escolhido existe no vetor de categorias
        for(int i = 0; i < tamanho; i++){
            if (vet_categoria[i].codigo == vet->codigo_categoria) {
                categoria_valida = 1;
                break; 
            }
        }

        if (categoria_valida == 0) {
            printf("\n--- ERRO: Codigo de categoria invalido! Tente novamente. ---\n");
        }

    } while (categoria_valida == 0);

    printf("\nDigite a marca do veiculo: ");
    ler_str(vet->marca, sizeof(vet->marca));
    limpar_buffer();

    printf("Digite o modelo do veiculo: ");
    ler_str(vet->modelo, sizeof(vet->modelo));
    
    printf("\nDigite o ano de fabricacao do veiculo: ");
    scanf("%d", &vet->ano);
    limpar_buffer();

    printf("\nDigite o valor da diaria do veiculo: ");
    scanf("%f", &vet->diaria);
    limpar_buffer();

    printf("\nDigite o numero de unidades disponiveis do veiculo: ");
    scanf("%d", &vet->unidades_disponiveis);
    limpar_buffer();
    
    printf("\nDigite o numero de unidades alugadas do veiculo: ");
    scanf("%d", &vet->unidades_alugadas);

    (*qtd)++;
    delay(300);
}

int main(){
    int resposta, qtd_cadastrados = 0, qtd_veiculos = 0;
    Categoria vetor_categoria[10];
    Veiculo vetor_veiculo[100];

    do{
        printf("\n--- Sistema de Locacao de Veiculos ---\n");
        printf("Escolha uma das opcoes abaixo:\n");
        printf("1 - Cadastrar categoria\n");
        printf("2 - Exibir categorias\n");
        printf("3 - Excluir categoria\n");
        printf("4 - Inserir veiculo na frota\n");
        printf("0 - Sair do sistema\n");
        printf("Sua opcao: "); 
        scanf("%d", &resposta);

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
                printf("\nNenhuma categoria cadastrada, tecle 1 para cadastrar.\n");
            }

            else{
                printf("\nCategorias cadastradas: \n");
                exibir_categoria(vetor_categoria, qtd_cadastrados);
            }
            delay(300);
            break;

        case 3:
            if(qtd_cadastrados <= 0){
                printf("\nNenhuma categoria encontrada, Tecle 1 para cadastrar a primeira categoria.\n");
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