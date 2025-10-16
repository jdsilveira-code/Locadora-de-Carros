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

/*Função para pausar a execução por um tempo em milissegundos.
  Exemplo de uso: delay(1000);*/
void delay(int tempo){
    fflush(stdout);
    Sleep(tempo);
}

/* Função para cadastrar uma categoria de veículo.
   Recebe um ponteiro para Categoria e solicita os dados ao usuário.*/
void categoria(Categoria *v, int *qtd){
    int resposta;
    do{
        printf("\nDigite o codigo da categoria: ");
        scanf("%d", &v->codigo);

        printf("Digite o tipo da categoria (ex: SUV, Economico): ");
        scanf("%s", v->tipo); // DICA: Para ler nomes com espaço, ex: "Carro de Luxo", use a função fgets.
        *qtd += 1;
        // Adicionado \n para separar o formulário do menu de opções
        printf("\n1 - Cadastrar nova categoria");
        printf("\n2 - Voltar para a pagina inicial\n");
        printf("Sua opcao: ");
        scanf("%d", &resposta);

        if(resposta != 1 && resposta != 2){
            do{
                printf("\n--- Resposta incorreta! ---"); 
                printf("\n1 - Cadastrar nova categoria");
                printf("\n2 - Voltar para a página inicial\n");
                printf("Sua opcao: ");
                scanf("%d", &resposta);
            }while(resposta != 1 && resposta != 2);
        }
    }while(resposta != 2);
    delay(300);
}

void exibir_categoria(Categoria *vet, int *tamanho){
    for(int i = 0; i < *tamanho; i++){
        printf("Codigo: %d\n", (vet + i)->codigo);
        printf("Tipo: %s", (vet + i)->tipo);
        printf("\n");
    }
    delay(300);
}

int main(){
    int resposta, qtd_cadastrados;
    Categoria vetor_categoria[10];

    do{
        printf("\n--- Sistema de Locacao de Veiculos ---\n");
        printf("Escolha uma das opcoes abaixo:\n");
        printf("1 - Cadastrar categoria\n");
        printf("2 - Exibir categorias\n");
        printf("3 - Inserir veiculo na frota\n");
        printf("4 - Exibir frota\n");
        printf("5 - Realizar aluguel\n");
        printf("6 - Realizar devolucao\n");
        printf("7 - Veiculos alugados por categoria\n");
        printf("8 - Veiculos alugados (geral)\n");
        printf("9 - Locacoes em aberto\n");
        printf("0 - Sair do sistema\n");
        printf("Sua opcao: "); 
        scanf("%d", &resposta);

        switch (resposta)
        {
        case 1:
            printf("\n--- Cadastro de Categoria ---\n");
            categoria(vetor_categoria, &qtd_cadastrados);
            break;
        case 2:
            if(qtd_cadastrados == 0){
                printf("Nenhuma categoria cadastrada, tecle 1 para cadastrar.\n");
                break;
            }
            else{
                printf("\nCategorias cadastradas: \n");
                exibir_categoria(vetor_categoria, &qtd_cadastrados);
                break;
            }
        case 3:
            printf("\nOpcao 3 selecionada.\n");
            break;
        case 0:
            printf("\nFim do programa.\n");
            break;
        default: 
            printf("\nOpcao invalida! Tente novamente.\n");
            break;
        }

    } while(resposta != 0);

    return 0;
}