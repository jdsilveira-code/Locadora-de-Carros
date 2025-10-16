int main()
{
    char frota[100];
    char categorias[11];
    char contratos[1001];
    struct Data{
        int dia;
        int mes;
        int ano;
    };
    struct Categoria{
        int Código[9];
        char *Nome[9];
        char buffer[50];
    };
    struct Veículo{
        char Código[9];
        char *Marca[100];
        char *Modelo[100];
        struct Categoria categoria;
        int Ano[4];
        float Diaria[10];
        int qtdUnidades[101];
        int qtdAlugadas[101];
    };
    struct Locacao{
        int numero;
        codigoVeiculo[9];
        dataRetirada(Data);
        dataPrevistaDevolucao(Data);
        dataDevolucao(Data);
        int status;
        float diariaAtrasoContrato;
        float valorPrevisto;
        float valorPago;
    }
    switch (Digito){
    case 1:
}
void cadastrarCategoria(){
}

