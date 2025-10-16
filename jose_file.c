#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Estrutura data
typedef struct 
{
    int dia;
    int ano;
    int mes;

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

}locacao;


int main(){
    int resposta;
    do{
        printf("OPCAO 1\n");
        printf("OPCAO 2\n");
        printf("OPCAO 3\n");
        printf("OPCAO 4\n");
        scanf("%d", &resposta);

        switch (resposta)
        {
        case 1:
            printf("Função 1\n");
            break;
        case 2:
            printf("Opção 2\n");
            break;
        case 3:
            printf("Opção 3\n");
            break;
        case 4:
            printf("Opção 4\n");
            break;
        }
    } while(resposta != 4);




    return 0;
}