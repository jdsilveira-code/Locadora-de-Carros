#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

typedef struct {
    int dia;
    int mes;
    int ano;
} Data;

typedef struct {
    int codigo;
    char tipo[50];
} Categoria;

typedef struct {
    int codigo; 
    int codigo_categoria;
    char marca[25];
    char modelo[25];
    int ano;
    float diaria;
    int unidades_disponiveis;
    int unidades_alugadas;
} Veiculo;

typedef struct {
    int numero_locacao;
    int codigo_veiculo;
    Data data_retirada;
    Data data_devolucao;
    Data data_prevista_devolucao;
    int status; 
    float diaria_Atraso;
    float valor_previsto;
    float valor_pago;
} Locacao;

void categoria(Categoria *vet, int *qtd) {
    int resposta;
    int iterador = 0;
    do {
        if (*qtd >= 10) {
            printf("\nLimite de categorias cadastradas atingido.\n");
            break;
        }

        printf("\nCadastro da categoria %d\n", *qtd + 1);
        printf("Digite o codigo da categoria: ");

        while (scanf("%d", &vet->codigo) != 1) {
            printf("Entrada invalida! Digite um numero: ");
            while (getchar() != '\n');
        }
        while (getchar() != '\n');

        printf("Digite o tipo da categoria (ex: SUV, Economico): ");
        scanf(" %49[^\n]", vet->tipo);

        (*qtd)++;
        vet++;
        iterador++;

        printf("\n1 - Cadastrar nova categoria\n");
        printf("2 - Voltar para a pagina inicial\n");
        printf("Sua opcao: ");
        
        while (scanf("%d", &resposta) != 1) {
            printf("Entrada invalida! Digite um numero: ");
            while (getchar() != '\n');
        }
        while (getchar() != '\n');

        while (resposta != 1 && resposta != 2) {
            printf("\n--- Resposta incorreta! ---\n");
            printf("1 - Cadastrar outra categoria\n");
            printf("2 - Voltar para o menu principal\n");
            printf("Sua opcao: ");
            while (scanf("%d", &resposta) != 1) {
                printf("Entrada invalida! Digite um numero: ");
                while (getchar() != '\n');
            }
            while (getchar() != '\n');
        }
    } while (resposta != 2);

    if (iterador > 0) {
        printf("\n%d categoria(s) cadastrada(s) com sucesso!\n", iterador);
    }
}

void exibir_categoria(Categoria *vet, int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        printf("\nCodigo: %d | Tipo: %s\n", vet[i].codigo, vet[i].tipo);
    }
}

void excluir_categoria(Categoria *vet, int *tamanho) {
    int resposta, indice_excluir = -1;
    printf("Qual categoria voce deseja excluir?\n");
    for (int i = 0; i < *tamanho; i++) {
        printf("\nCodigo: %d | Tipo: %s", vet[i].codigo, vet[i].tipo);
    }

    printf("\nSua opcao (digite o codigo): ");
    while (scanf("%d", &resposta) != 1) {
        printf("Entrada invalida! Digite um numero: ");
        while (getchar() != '\n');
    }
    while (getchar() != '\n');

    for (int i = 0; i < *tamanho; i++) {
        if (resposta == vet[i].codigo) {
            indice_excluir = i;
            break;
        }
    }

    if (indice_excluir == -1) {
        printf("\nCodigo nao encontrado!\n");
    } else {
        for (int i = indice_excluir; i < *tamanho - 1; i++) {
            vet[i] = vet[i + 1];
        }
        (*tamanho)--;
        printf("\nCategoria excluida com sucesso!\n");
    }
}

void inserir_veiculo(Veiculo *vet, int *tamanho_veiculo, Categoria *vet_categoria, int tamanho_categoria) {
    int categoria_valida, veiculo_valido, resposta = 0;
    int iterador = 0;
    int codigo_digitado;

    do {
        printf("\nCadastrando veiculo %d\n", *tamanho_veiculo + 1);

        do {
            veiculo_valido = 1;
            printf("\nDigite o codigo do veiculo: ");
            while (scanf("%d", &codigo_digitado) != 1) {
                printf("Entrada invalida! Digite um numero: ");
                while (getchar() != '\n');
            }
            while (getchar() != '\n');

            for (int i = 0; i < *tamanho_veiculo; i++) {
                if (vet[i].codigo == codigo_digitado) {
                    veiculo_valido = 0;
                    printf("\n[ERRO] O codigo de veiculo %d ja esta em uso! Tente outro.\n", codigo_digitado);
                    break;
                }
            }
        } while (veiculo_valido == 0);

        vet[*tamanho_veiculo].codigo = codigo_digitado;

        do {
            categoria_valida = 0;
            printf("\nCategorias disponiveis:\n");
            for (int i = 0; i < tamanho_categoria; i++) {
                printf(" -> Codigo: %d | Tipo: %s\n", vet_categoria[i].codigo, vet_categoria[i].tipo);
            }

            printf("\nDigite o codigo da categoria desejada: ");
            while (scanf("%d", &vet[*tamanho_veiculo].codigo_categoria) != 1) {
                printf("Entrada invalida! Digite um numero: ");
                while (getchar() != '\n');
            }
            while (getchar() != '\n');

            for (int i = 0; i < tamanho_categoria; i++) {
                if (vet_categoria[i].codigo == vet[*tamanho_veiculo].codigo_categoria) {
                    categoria_valida = 1;
                    break;
                }
            }

            if (categoria_valida == 0) {
                printf("\n[ERRO] Codigo de categoria invalido! Tente novamente.\n");
            }
        } while (categoria_valida == 0);

        printf("\nDigite a marca do veiculo: ");
        scanf(" %24[^\n]", vet[*tamanho_veiculo].marca);

        printf("\nDigite o modelo do veiculo: ");
        scanf(" %24[^\n]", vet[*tamanho_veiculo].modelo);

        printf("\nDigite o ano de fabricacao do veiculo: ");
        while (scanf("%d", &vet[*tamanho_veiculo].ano) != 1) {
            printf("Entrada invalida! Digite um numero: ");
            while (getchar() != '\n');
        }
        while (getchar() != '\n');

        printf("\nDigite o valor da diaria do veiculo: ");
        while (scanf("%f", &vet[*tamanho_veiculo].diaria) != 1) {
            printf("Entrada invalida! Digite um numero: ");
            while (getchar() != '\n');
        }
        while (getchar() != '\n');

        printf("\nDigite o numero de unidades disponiveis: ");
        while (scanf("%d", &vet[*tamanho_veiculo].unidades_disponiveis) != 1) {
            printf("Entrada invalida! Digite um numero: ");
            while (getchar() != '\n');
        }
        while (getchar() != '\n');

        vet[*tamanho_veiculo].unidades_alugadas = 0;
        (*tamanho_veiculo)++;
        iterador++;

        printf("\nVeiculo cadastrado!\n");
        printf("1 - Cadastrar outro carro \n2 - Voltar ao menu principal\n");
        printf("Sua opcao: ");
        while (scanf("%d", &resposta) != 1) {
            printf("Entrada invalida! Digite um numero: ");
            while (getchar() != '\n');
        }
        while (getchar() != '\n');

        while (resposta != 1 && resposta != 2) {
            printf("\n[ERRO] Resposta incorreta\n");
            printf("1 - Cadastrar outro veiculo\n");
            printf("2 - Voltar para o menu principal\n");
            printf("Sua opcao: ");
            while (scanf("%d", &resposta) != 1) {
                printf("Entrada invalida! Digite um numero: ");
                while (getchar() != '\n');
            }
            while (getchar() != '\n');
        }
    } while (resposta != 2);

    if (iterador > 0) {
        printf("\n%d veiculo(s) cadastrado(s) com sucesso!\n", iterador);
    }
}

void exibir_veiculo(Veiculo *vet, int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        printf("\n--- Veiculo %d ---\n", i + 1);
        printf("Codigo.............: %d\n", vet[i].codigo);
        printf("Categoria..........: %d\n", vet[i].codigo_categoria);
        printf("Marca..............: %s\n", vet[i].marca);
        printf("Modelo.............: %s\n", vet[i].modelo);
        printf("Ano................: %d\n", vet[i].ano);
        printf("Diaria.............: R$ %.2f\n", vet[i].diaria);
        printf("Disponiveis........: %d\n", vet[i].unidades_disponiveis);
        printf("Alugados...........: %d\n", vet[i].unidades_alugadas);
    }
}

/* ============================
   LOCAÇÃO E DEVOLUÇÃO
   ============================ */

void realizar_locacao(Locacao *loc, int *qtd_loc, Veiculo *vets, int qtd_veic) {
    int cod_veiculo, indice_veiculo = -1;
    int dias_contratados;
    float diaria_atraso;
    char confirmacao;
    Data data_ret, data_prev;
    int datas_validas;

    printf("\n--- Abrir Nova Locacao ---\n");
    
    printf("Digite o codigo do veiculo que deseja alugar: ");
    while (scanf("%d", &cod_veiculo) != 1) {
        printf("Entrada invalida! Digite um numero: ");
        while (getchar() != '\n');
    }
    while (getchar() != '\n');

    for (int i = 0; i < qtd_veic; i++) {
        if (vets[i].codigo == cod_veiculo) {
            indice_veiculo = i;
            break;
        }
    }

    if (indice_veiculo == -1) {
        printf("\n[ERRO] Veiculo com codigo %d nao encontrado.\n", cod_veiculo);
        return;
    }

    if (vets[indice_veiculo].unidades_alugadas >= vets[indice_veiculo].unidades_disponiveis) {
        printf("\n[ERRO] Veiculo '%s %s' nao possui unidades disponiveis.\n", 
               vets[indice_veiculo].marca, vets[indice_veiculo].modelo);
        return;
    }

    printf("\nVeiculo Encontrado:\n");
    printf("  Marca/Modelo: %s %s\n", vets[indice_veiculo].marca, vets[indice_veiculo].modelo);
    printf("  Diaria: R$ %.2f\n", vets[indice_veiculo].diaria);
    printf("Deseja alugar este veiculo? (S/N): ");
    
    do {
        scanf(" %c", &confirmacao);
        while (getchar() != '\n');
        
        if (confirmacao == 'n' || confirmacao == 'N') {
            printf("\nOperacao cancelada pelo usuario.\n");
            return;
        }
        if (confirmacao != 's' && confirmacao != 'S') {
            printf("Opcao invalida. Digite S ou N: ");
        }
    } while (confirmacao != 's' && confirmacao != 'S');

    do {
        printf("\nData de retirada (dd mm aaaa): ");
        scanf("%d %d %d", &data_ret.dia, &data_ret.mes, &data_ret.ano);
        while (getchar() != '\n');

        printf("Data prevista de devolucao (dd mm aaaa): ");
        scanf("%d %d %d", &data_prev.dia, &data_prev.mes, &data_prev.ano);
        while (getchar() != '\n');

        datas_validas = 0;
        if (data_prev.ano > data_ret.ano) datas_validas = 1;
        else if (data_prev.ano == data_ret.ano && data_prev.mes > data_ret.mes) datas_validas = 1;
        else if (data_prev.ano == data_ret.ano && data_prev.mes == data_ret.mes && data_prev.dia > data_ret.dia) datas_validas = 1;

        if (datas_validas == 0) {
            printf("\n[ERRO] A data de devolucao deve ser posterior a data de retirada. Tente novamente.\n");
        }
    } while (datas_validas == 0);

    printf("\nQuantos dias contratados (para calculo do valor)? ");
    while (scanf("%d", &dias_contratados) != 1 || dias_contratados <= 0) {
        printf("Valor invalido! Digite um numero positivo: ");
        while (getchar() != '\n');
    }
    while (getchar() != '\n');

    printf("Digite o valor da diaria de atraso: R$ ");
    while (scanf("%f", &diaria_atraso) != 1 || diaria_atraso < 0) {
         printf("Valor invalido! Digite um numero (ex: 50.0): ");
        while (getchar() != '\n');
    }
    while (getchar() != '\n');

    int i_loc = *qtd_loc;

    loc[i_loc].numero_locacao = i_loc + 1;
    loc[i_loc].codigo_veiculo = cod_veiculo;
    loc[i_loc].status = 0;
    loc[i_loc].valor_pago = 0;

    loc[i_loc].data_retirada = data_ret;
    loc[i_loc].data_prevista_devolucao = data_prev;
    loc[i_loc].diaria_Atraso = diaria_atraso;

    loc[i_loc].valor_previsto = dias_contratados * vets[indice_veiculo].diaria;

    vets[indice_veiculo].unidades_alugadas++;
    (*qtd_loc)++;

    printf("\n--------------------------------------\n");
    printf("--- Locacao Aberta com Sucesso! ---\n");
    printf("  Numero da Locacao: %d\n", loc[i_loc].numero_locacao);
    printf("  Veiculo: %s %s (Codigo: %d)\n", vets[indice_veiculo].marca, vets[indice_veiculo].modelo, cod_veiculo);
    printf("  Data Retirada: %02d/%02d/%d\n", loc[i_loc].data_retirada.dia, loc[i_loc].data_retirada.mes, loc[i_loc].data_retirada.ano);
    printf("  Data Prev. Dev.: %02d/%02d/%d\n", loc[i_loc].data_prevista_devolucao.dia, loc[i_loc].data_prevista_devolucao.mes, loc[i_loc].data_prevista_devolucao.ano);
    printf("  Valor Previsto: R$ %.2f\n", loc[i_loc].valor_previsto);
    printf("--------------------------------------\n");
}

void realizar_devolucao(Locacao *loc, int qtd_loc, Veiculo *vet, int qtd_veic) {
    int num_locacao, indice_locacao = -1;
    int indice_veiculo = -1;
    int dias_atraso;
    Data data_dev;
    int data_valida;

    printf("\n--- Realizar Devolucao ---\n");
    printf("Digite o numero da locacao para devolver: ");
    while (scanf("%d", &num_locacao) != 1) {
        printf("Entrada invalida! Digite um numero: ");
        while (getchar() != '\n');
    }
    while (getchar() != '\n');

    for (int i = 0; i < qtd_loc; i++) {
        if (loc[i].numero_locacao == num_locacao) {
            if (loc[i].status == 0) {
                indice_locacao = i;
            } else {
                printf("\n[ERRO] Locacao %d ja foi devolvida anteriormente.\n", num_locacao);
                return;
            }
            break;
        }
    }

    if (indice_locacao == -1) {
        printf("\n[ERRO] Locacao com numero %d nao encontrada ou nao esta aberta.\n", num_locacao);
        return;
    }

    do {
        printf("Data da devolucao (dd mm aaaa): ");
        scanf("%d %d %d", &data_dev.dia, &data_dev.mes, &data_dev.ano);
        while (getchar() != '\n');

        data_valida = 0;
        if (data_dev.ano > loc[indice_locacao].data_retirada.ano) data_valida = 1;
        else if (data_dev.ano == loc[indice_locacao].data_retirada.ano && data_dev.mes > loc[indice_locacao].data_retirada.mes) data_valida = 1;
        else if (data_dev.ano == loc[indice_locacao].data_retirada.ano && data_dev.mes == loc[indice_locacao].data_retirada.mes && data_dev.dia >= loc[indice_locacao].data_retirada.dia) data_valida = 1;

        if (data_valida == 0) {
            printf("\n[ERRO] A data de devolucao deve ser igual ou posterior a data de retirada (%02d/%02d/%d). Tente novamente.\n",
                   loc[indice_locacao].data_retirada.dia, loc[indice_locacao].data_retirada.mes, loc[indice_locacao].data_retirada.ano);
        }
    } while (data_valida == 0);

    printf("Quantos dias de atraso? (Digite 0 se nao houve): ");
    while (scanf("%d", &dias_atraso) != 1 || dias_atraso < 0) {
         printf("Entrada invalida! Digite 0 ou um numero positivo: ");
         while (getchar() != '\n');
    }
    while (getchar() != '\n');
    
    loc[indice_locacao].status = 1;
    loc[indice_locacao].data_devolucao = data_dev;
    loc[indice_locacao].valor_pago = loc[indice_locacao].valor_previsto + (dias_atraso * loc[indice_locacao].diaria_Atraso);

    for (int i = 0; i < qtd_veic; i++) {
        if (vet[i].codigo == loc[indice_locacao].codigo_veiculo) {
            vet[i].unidades_alugadas--;
            indice_veiculo = i;
            break;
        }
    }

    printf("\n--------------------------------------\n");
    printf("--- Devolucao Realizada com Sucesso ---\n");
    printf("  Numero da Locacao: %d\n", loc[indice_locacao].numero_locacao);
    printf("  Status: Devolvida\n");
    
    if(indice_veiculo != -1){
        printf("  Veiculo: %s %s (Cod: %d)\n", vet[indice_veiculo].marca, vet[indice_veiculo].modelo, vet[indice_veiculo].codigo);
    }

    printf("\n  --- Datas ---\n");
    printf("  Retirada: %02d/%02d/%d\n", loc[indice_locacao].data_retirada.dia, loc[indice_locacao].data_retirada.mes, loc[indice_locacao].data_retirada.ano);
    printf("  Prevista: %02d/%02d/%d\n", loc[indice_locacao].data_prevista_devolucao.dia, loc[indice_locacao].data_prevista_devolucao.mes, loc[indice_locacao].data_prevista_devolucao.ano);
    printf("  Devolucao: %02d/%02d/%d\n", loc[indice_locacao].data_devolucao.dia, loc[indice_locacao].data_devolucao.mes, loc[indice_locacao].data_devolucao.ano);

    printf("\n  --- Valores ---\n");
    printf("  Valor Previsto....: R$ %8.2f\n", loc[indice_locacao].valor_previsto);
    printf("  Dias de Atraso....: %d\n", dias_atraso);
    printf("  Diaria Atraso.....: R$ %8.2f\n", loc[indice_locacao].diaria_Atraso);
    printf("  Total Atraso......: R$ %8.2f\n", (dias_atraso * loc[indice_locacao].diaria_Atraso));
    printf("  VALOR TOTAL PAGO..: R$ %8.2f\n", loc[indice_locacao].valor_pago);
    printf("--------------------------------------\n");
}

/* ============================
    RELATÓRIOS
   ============================ */

void relatorio_veiculos_por_categoria(Veiculo *vets, int qtd_veic, Categoria *cats, int qtd_cat) {
    int cod_cat;
    int indice_cat = -1;
    int total_alugados_categoria = 0;
    int veiculos_encontrados = 0;

    printf("\n--- Relatorio: Veiculos Alugados por Categoria ---\n");
    printf("Categorias disponiveis:\n");
    for (int i = 0; i < qtd_cat; i++) {
        printf("  Codigo: %d | Tipo: %s\n", cats[i].codigo, cats[i].tipo);
    }

    printf("\nDigite o codigo da categoria para o relatorio: ");
    while (scanf("%d", &cod_cat) != 1) {
        printf("Entrada invalida! Digite um numero: ");
        while (getchar() != '\n');
    }
    while (getchar() != '\n');

    for (int i = 0; i < qtd_cat; i++) {
        if (cats[i].codigo == cod_cat) {
            indice_cat = i;
            break;
        }
    }

    if (indice_cat == -1) {
        printf("\n[ERRO] Categoria com codigo %d nao encontrada.\n", cod_cat);
        return;
    }

    printf("\n--- Veiculos Alugados da Categoria: %s ---\n", cats[indice_cat].tipo);
    
    for (int i = 0; i < qtd_veic; i++) {
        if (vets[i].codigo_categoria == cod_cat && vets[i].unidades_alugadas > 0) {
            printf("  Veiculo: %s %s (Cod: %d)\n", vets[i].marca, vets[i].modelo, vets[i].codigo);
            printf("  Unidades Alugadas: %d\n", vets[i].unidades_alugadas);
            printf("  --------------------------------\n");
            
            total_alugados_categoria += vets[i].unidades_alugadas;
            veiculos_encontrados++;
        }
    }

    if (veiculos_encontrados == 0) {
        printf("\nNenhum veiculo desta categoria foi alugado no momento.\n");
    } else {
        printf("\nTotal de unidades alugadas para esta categoria: %d\n", total_alugados_categoria);
    }
}

void relatorio_todas_categorias(Veiculo *vets, int qtd_veic, Categoria *cats, int qtd_cat) {
    int total_geral_alugados = 0;
    
    printf("\n--- Relatorio: Veiculos Alugados (Todas Categorias) ---\n");

    if (qtd_veic == 0) {
        printf("\nNenhum veiculo cadastrado.\n");
        return;
    }

    for (int i = 0; i < qtd_cat; i++) {
        int subtotal_categoria = 0;
        int veiculos_encontrados_na_categoria = 0;

        printf("\n==============================================\n");
        printf("Categoria: %s (Codigo: %d)\n", cats[i].tipo, cats[i].codigo);
        printf("==============================================\n");

        for (int j = 0; j < qtd_veic; j++) {
            if (vets[j].codigo_categoria == cats[i].codigo && vets[j].unidades_alugadas > 0) {
                printf("  Veiculo: %s %s (Cod: %d)\n", vets[j].marca, vets[j].modelo, vets[j].codigo);
                printf("  Unidades Alugadas: %d\n\n", vets[j].unidades_alugadas);
                
                subtotal_categoria += vets[j].unidades_alugadas;
                veiculos_encontrados_na_categoria++;
            }
        }

        if (veiculos_encontrados_na_categoria == 0) {
            printf("Nenhum veiculo alugado para esta categoria.\n");
        } else {
            printf("Subtotal de unidades alugadas nesta categoria: %d\n", subtotal_categoria);
        }
        
        total_geral_alugados += subtotal_categoria;
    }

    printf("\n==============================================\n");
    printf("TOTAL GERAL de unidades alugadas: %d\n", total_geral_alugados);
    printf("==============================================\n");
}

void relatorio_locacoes_abertas(Locacao *locs, int qtd_loc) {
    int locacoes_abertas_encontradas = 0;

    printf("\n--- Relatorio: Locacoes Abertas (Geral) ---\n");

    if (qtd_loc == 0) {
        printf("\nNenhuma locacao foi registrada no sistema.\n");
        return;
    }

    for (int i = 0; i < qtd_loc; i++) {
        if (locs[i].status == 0) {
            printf("--------------------------------------\n");
            printf("  Numero Locacao.....: %d\n", locs[i].numero_locacao);
            printf("  Codigo do Veiculo..: %d\n", locs[i].codigo_veiculo);
            printf("  Data Retirada......: %02d/%02d/%d\n", locs[i].data_retirada.dia, locs[i].data_retirada.mes, locs[i].data_retirada.ano);
            printf("  Data Prev. Dev.....: %02d/%02d/%d\n", locs[i].data_prevista_devolucao.dia, locs[i].data_prevista_devolucao.mes, locs[i].data_prevista_devolucao.ano);
            printf("  Diaria Atraso......: R$ %.2f\n", locs[i].diaria_Atraso);
            printf("  Valor Previsto.....: R$ %.2f\n", locs[i].valor_previsto);
            
            locacoes_abertas_encontradas++;
        }
    }

    if (locacoes_abertas_encontradas == 0) {
        printf("\nNenhuma locacao aberta encontrada no momento.\n");
    } else {
        printf("--------------------------------------\n");
        printf("Total de locacoes abertas: %d\n", locacoes_abertas_encontradas);
    }
}

/* ============================
    MAIN
   ============================ */

int main() {
    int resposta, qtd_cadastrados = 0, qtd_veiculos = 0, qtd_locacoes = 0;
    Categoria vetor_categoria[10];
    Veiculo vetor_veiculo[100];
    Locacao vetor_locacao[1000]; 

    do {
        printf("\n--- Sistema de Locacao de Veiculos ---\n");
        printf("1 - Cadastrar categoria\n");
        printf("2 - Exibir categorias\n");
        printf("3 - Excluir categoria\n");
        printf("4 - Inserir veiculo na frota\n");
        printf("5 - Exibir veiculos\n");
        printf("6 - Realizar aluguel\n");
        printf("7 - Realizar devolucao\n");
        printf("8 - Relatorio: Veiculos alugados por Categoria\n");
        printf("9 - Relatorio: Veiculos alugados (Todas)\n");
        printf("10 - Relatorio: Locacoes Abertas (Geral)\n");
        printf("0 - Sair do sistema\n");
        printf("Sua opcao: ");

        while (scanf("%d", &resposta) != 1) {
            printf("Entrada invalida! Digite um numero: ");
            while (getchar() != '\n');
        }
        while (getchar() != '\n');

        switch (resposta) {
            case 1:
                if (qtd_cadastrados < 10)
                    categoria(&vetor_categoria[qtd_cadastrados], &qtd_cadastrados);
                else
                    printf("\n[ERRO] Limite atingido.\n");
                break;

            case 2:
                if (qtd_cadastrados == 0)
                    printf("\n[ERRO] Nenhuma categoria cadastrada.\n");
                else
                    exibir_categoria(vetor_categoria, qtd_cadastrados);
                break;

            case 3:
                if (qtd_cadastrados == 0)
                    printf("\n[ERRO] Nenhuma categoria cadastrada.\n");
                else
                    excluir_categoria(vetor_categoria, &qtd_cadastrados);
                break;

            case 4:
                if (qtd_cadastrados == 0) {
                    printf("\n[ERRO] Nenhuma categoria cadastrada. Cadastre uma categoria primeiro.\n");
                } else if (qtd_veiculos >= 100) { 
                    printf("\n[ERRO] Limite de 100 veiculos atingido.\n");
                } else {
                    inserir_veiculo(vetor_veiculo, &qtd_veiculos, vetor_categoria, qtd_cadastrados);
                }
                break;

            case 5:
                if (qtd_veiculos == 0)
                    printf("\n[ERRO] Nenhum veiculo cadastrado.\n");
                else
                    exibir_veiculo(vetor_veiculo, qtd_veiculos);
                break;

            case 6:
                if (qtd_veiculos == 0) {
                    printf("\n[ERRO] Nenhum veiculo cadastrado.\n");
                } else if (qtd_locacoes >= 1000) { 
                    printf("\n[ERRO] Limite de 1000 locacoes atingido.\n");
                } else {
                    realizar_locacao(vetor_locacao, &qtd_locacoes, vetor_veiculo, qtd_veiculos);
                }
                break;

            case 7:
                if (qtd_locacoes == 0)
                    printf("\n[ERRO] Nenhuma locacao aberta.\n");
                else
                    realizar_devolucao(vetor_locacao, qtd_locacoes, vetor_veiculo, qtd_veiculos);
                break;

            case 8: 
                if (qtd_veiculos == 0 || qtd_cadastrados == 0)
                    printf("\n[ERRO] E necessario ter veiculos E categorias cadastradas.\n");
                else
                    relatorio_veiculos_por_categoria(vetor_veiculo, qtd_veiculos, vetor_categoria, qtd_cadastrados);
                break;

            case 9: 
                if (qtd_veiculos == 0 || qtd_cadastrados == 0)
                    printf("\n[ERRO] E necessario ter veiculos E categorias cadastradas.\n");
                else
                    relatorio_todas_categorias(vetor_veiculo, qtd_veiculos, vetor_categoria, qtd_cadastrados);
                break;

            case 10: 
                if (qtd_locacoes == 0)
                    printf("\n[ERRO] Nenhuma locacao foi registrada.\n");
                else
                    relatorio_locacoes_abertas(vetor_locacao, qtd_locacoes);
                break;

            case 0:
                printf("\nFim do programa.\n");
                break;

            default:
                printf("\n[ERRO] Opcao invalida!\n");
                break;
        }

    } while (resposta != 0);

    return 0;
}