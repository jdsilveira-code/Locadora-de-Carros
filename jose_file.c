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

/* Lembrete: A chamada na main deve ser:
   inserir_veiculo(vetor_veiculo, &qtd_veiculos, vetor_categoria, qtd_cadastrados);
*/
void inserir_veiculo(Veiculo *vet, int *tamanho_veiculo, Categoria *vet_categoria, int tamanho_categoria){
    
    int categoria_valida, veiculo_valido, resposta = 0;
    int iterador = 0; // Inicializa o contador local
    int codigo_digitado;

    do{
        printf("\nCadastrando veiculo %d\n", *tamanho_veiculo + 1);

        // --- Validacao de Codigo Duplicado ---
        do {
            veiculo_valido = 1; // Assume que e valido
            
            printf("\nDigite o codigo do veiculo: ");
            scanf(" %d", &codigo_digitado);
            if(codigo_digitado == 0){
                printf("\n[ERRO] O codigo 0 não pode ser utilizado");
                veiculo_valido = 0;
            }
            // Verifica se o codigo ja existe no vetor de veiculos
            for(int i = 0; i < *tamanho_veiculo; i++){
                if (vet[i].codigo == codigo_digitado) {
                    veiculo_valido = 0; // Encontrou duplicata
                    printf("\n[ERRO] O codigo de veiculo %d ja esta em uso! Tente outro.\n", codigo_digitado);
                    break; 
                }
            }
        } while (veiculo_valido == 0);

        // Codigo e valido, armazena na posicao correta
        vet[*tamanho_veiculo].codigo = codigo_digitado;

        // --- Validacao do Codigo da Categoria ---
        do{
            categoria_valida = 0;
            printf("\nCategorias disponiveis: \n");
            for (int i = 0; i < tamanho_categoria; i++) {
                printf(" -> Codigo: %d | Tipo: %s\n", vet_categoria[i].codigo, vet_categoria[i].tipo);
            }
            
            printf("\nDigite o codigo da categoria desejada: ");
            scanf(" %d", &vet[*tamanho_veiculo].codigo_categoria);

            for(int i = 0; i < tamanho_categoria; i++){
                if (vet_categoria[i].codigo == vet[*tamanho_veiculo].codigo_categoria) {
                    categoria_valida = 1;
                    break; 
                }
            }

            if (categoria_valida == 0) {
                printf("\n[ERRO] Codigo de categoria invalido! Tente novamente.\n");
            }
        } while (categoria_valida == 0);

        // --- Restante do Cadastro ---
        printf("\nDigite a marca do veiculo: ");
        scanf(" %24[^\n]", vet[*tamanho_veiculo].marca);

        printf("\nDigite o modelo do veiculo: ");
        scanf(" %24[^\n]", vet[*tamanho_veiculo].modelo);
        
        printf("\nDigite o ano de fabricacao do veiculo: ");
        scanf(" %d", &vet[*tamanho_veiculo].ano);
        
        printf("\nDigite o valor da diaria do veiculo: ");
        scanf(" %f", &vet[*tamanho_veiculo].diaria);
        
        printf("\nDigite o numero de unidades disponiveis do veiculo: ");
        scanf(" %d", &vet[*tamanho_veiculo].unidades_disponiveis);
        
        // Assume que um carro novo tem 0 unidades alugadas
        vet[*tamanho_veiculo].unidades_alugadas = 0; 

        (*tamanho_veiculo)++;
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
    
    if (iterador > 0) {
        printf("\n%d veiculo(s) cadastrado(s) com sucesso!\n", iterador);
    }
    
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

void realizar_aluguel(Veiculo *vet, int *qtd, Categoria *vet_categoria, int tamanho){
    int codigoVeiculo, qtd_veiculos = *qtd, indice = -1, codigo_valido = 0;
    printf("\n--- Alugar Veiculo ---\n");
    printf("Digite o codigo do veiculo que deseja alugar\n");
    printf("Veículos disponíveis: \n");
    exibir_veiculo(vet, tamanho);

    do {
        printf("Sua opcao: ");
        scanf(" %d", &codigoVeiculo);
        
        codigo_valido = 0; 
        
        // Procura o codigo no vetor
        for(int i = 0; i < qtd; i++){
            if(vet[i].codigo == codigoVeiculo){
                indice = i;          
                codigo_valido = 1;   
                break;               
            }
        }

        if(codigo_valido == 0){
            printf("[ERRO] codigo nao encontrado, digite novamente.\n");
        }

    } while(codigo_valido == 0); // Repete se o codigo nao foi valido


    int qtdUnidadesDisponiveis = vetor_veiculo[i].unidades_disponiveis - vetor_veiculo[i].unidades_alugadas;
    int qtdAlugada= vetor_veiculo[i].unidades_alugadas;
    if (qtdAlugada<qtdUnidadesDisponiveis) {
        vetor_veiculo[i].unidades_alugadas += 1;
        printf("\nVeiculo alugado com sucesso!\n");
    } else {
        printf("\n[ERRO] Nao ha unidades disponiveis para aluguel deste veiculo.\n");
    }
    break;
    printf("Digite a data de retirada do Veículo: ");
    scanf(" %d", &vet->data_retirada.dia);
    scanf(" %d", &vet->data_retirada.mes);
    scanf(" %d", &vet->data_retirada.ano);
    printf("Digite a data prevista de devolução: ");
    scanf(" %d", &vet->data_prevista_devolucao.dia);
    scanf(" %d", &vet->data_prevista_devolucao.mes);       
    scanf(" %d", &vet->data_prevista_devolucao.ano);
    valorPrevisto = vet->diaria * numeroDias;
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
        printf("5 - Exibir veiculos\n");
        printf("0 - Sair do sistema\n");
        printf("Sua opcao: ");
        scanf(" %d", &resposta);

        switch (resposta){

        case 1:
        //Cadastro de categorias
            if(qtd_cadastrados < 10){
                    printf("\n--- Cadastro de Categoria ---\n");
                    categoria(&vetor_categoria[qtd_cadastrados], &qtd_cadastrados);
            }
            else{
                printf("\n[ERRO] Limite de categorias cadastradas atingido. Nao e possivel cadastrar mais categorias.\n");
                delay(300);
            }
            delay(300);
            break;

        case 2:
        //Exibir categorias
            if(qtd_cadastrados == 0){
                printf("\n[ERRO] Nenhuma categoria cadastrada, tecle 1 para cadastrar a primeira categoria.\n");
            }

            else{
                printf("\n--- Categorias cadastradas ---\n");
                exibir_categoria(vetor_categoria, qtd_cadastrados);
            }
            delay(300);
            break;

        case 3:
        //Excluir categoria
            if(qtd_cadastrados <= 0){
                printf("\n[ERRO] Nenhuma categoria cadastrada, Tecle 1 para cadastrar a primeira categoria.\n");
            }
            else{
                printf("\n--- Excluir Categoria ---\n");
                excluir_categoria(vetor_categoria, &qtd_cadastrados);
            }
            delay(300);
            break;

        case 4:
        //Cadastro de veiculo
            if(qtd_cadastrados <= 0 ){
                printf("\n[ERRO] Nenhuma categoria cadastrada. Cadastre uma antes de inserir veiculos.\n");
            }
            else{
                if(qtd_veiculos < 100){
                    printf("\n--- Cadastro de veiculo ---\n");
                    inserir_veiculo(vetor_veiculo, &qtd_veiculos, vetor_categoria, qtd_cadastrados);
                }
                else{
                    printf("\n[ERRO] Limite de carros atingido. Nao e possivel adicionar mais carros a frota.\n");
                }
            }

            delay(300);
            break;

        case 5:
        //Exibir veiculos
            if(qtd_veiculos <= 0){
                printf("\n[ERRO] Nenhum veiculo cadastrado, primeiro cadastre um veiculo. \nPor favor, retorne ao menu e selecione a opcao 'Inserir veiculo na frota'.\n");
            }
            else{
                printf("\n--- Exibindo veiculos ---\n");
                exibir_veiculo(vetor_veiculo, qtd_veiculos);
            }
            delay(300);
            break;
        case 7: 
        // Fechar locacão
            printf("\n--- Fechar locacao ---\n");

        case 0:
            printf("\nFim do programa.\n");
            break;
        default: 
            printf("\n[ERRO] Opcao invalida! Tente novamente.\n");
            delay(300);
            break;
        }

    } while(resposta != 0);

    return 0;
}