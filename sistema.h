#ifndef SISTEMA_H
#define SISTEMA_H

    void menu();
    
    typedef struct{
        char nome[50];
        char CPF[12];
        char CNH[12];
        char categoria_cnh[3];
        long long telefone;
        int ativo;
    } __attribute__((packed))Cliente;
    
    typedef struct {
        char CPF_cliente[12];
        char placa_veiculo[8];
        char data_aluguel[11];
        char data_devolucao[11];
        int dias_aluguel;
        float valor_total;
        int entregue_no_prazo;
    } Locacao;
    
    typedef struct{
        char placa[8];
        char marca[30];
        char modelo[50];
        char categoria_cnh[3];
        float valor_diaria;    
        int alugado;
        int ativo;
    } Veiculo;
    
    int validarCategoriaCNH(const char* categoria);
    int validarCompatibilidadeCategoria(const char* categoria_cliente, const char* categoria_veiculo);
    int validarCNH(char cnh[]);
    
    int validarCPF(char cpf[]);
    void verificar_tamanho_struct();
    int validarPlaca(char placa[]);
    void verificar_atrasos();
    
    void area_cadastro();
    void cadastro_cliente();
    void cadastro_veiculo();
    void area_consulta();
    void consulta_cliente();
    void atualizar_cliente(char cpf_busca[12], long posicao);
    void excluir_cliente(char cpf_busca[12], long posicao, int tem_locacoes);
    void consulta_veiculo();
    void atualizar_veiculo(char placa[8], long posicao);
    void excluir_veiculo(char placa[8], long posicao);
    void area_locacao();
    void registro_locacao();
    void registro_locacao_test();
    void alugar_veiculo();
    void dados_cliente();
    void dados_veiculo();
    
#endif
