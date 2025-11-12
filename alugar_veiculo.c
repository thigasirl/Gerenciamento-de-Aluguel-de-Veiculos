#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "sistema.h"

void alugar_veiculo()
{
    system("clear");
    printf("╔════════════════════════════════════════╗\n");
    printf("║            LOCAÇÃO DE VEÍCULO          ║\n");
    printf("╚════════════════════════════════════════╝\n\n");
    
    char cpf_cliente[12];
    char marca_desejada[30];
    char categoria_cliente[3];
    Cliente cliente;
    int cliente_encontrado = 0;
    
    printf("Digite o CPF do cliente (11 dígitos): ");
    scanf("%11s", cpf_cliente);
    while (getchar() != '\n');
    
    FILE *arquivo_clientes = fopen("clientes.bin", "rb");
    if(arquivo_clientes == NULL)
    {
        printf("❌ Erro ao abrir arquivo de clientes!\n");
        printf("Pressione Enter para voltar...");
        getchar();
        return;
    }
    
    while(fread(&cliente, sizeof(Cliente), 1, arquivo_clientes)){
        if(strcmp(cliente.CPF, cpf_cliente) == 0 && (cliente.ativo == 1 || cliente.ativo == 4))
        {
            cliente_encontrado = 1;
            strcpy(categoria_cliente, cliente.categoria_cnh);
            break;
        }
    }
    fclose(arquivo_clientes);
    
    if(!cliente_encontrado)
    {
        printf("❌ Cliente não encontrado ou inativo!\n");
        printf("Pressione Enter para voltar...");
        getchar();
        return;
    }
    
    printf("Cliente encontrado: %s\n", cliente.nome);
    printf("Categoria CNH: %s\n\n", categoria_cliente);
    
    printf("Digite a marca desejada: ");
    scanf("%29s", marca_desejada);
    for(int i = 0; marca_desejada[i]; i++){
        marca_desejada[i] = toupper(marca_desejada[i]);
    }
    
    Veiculo veiculos[100];
    int count = 0;
    
    FILE *arquivo_veiculos = fopen("veiculos.bin", "rb");
    if(arquivo_veiculos == NULL)
    {
        printf("❌ Erro ao abrir arquivo de veículos!\n");
        printf("Pressione Enter para voltar...");
        getchar();
        return;
    }
    
    Veiculo veiculo;
    while(fread(&veiculo, sizeof(Veiculo), 1, arquivo_veiculos)){
        int marca_ok = (strcmp(veiculo.marca, marca_desejada) == 0);
        int ativo_ok = (veiculo.ativo == 1);
        int alugado_ok = (veiculo.alugado == 0);
        int categoria_ok = validarCompatibilidadeCategoria(categoria_cliente, veiculo.categoria_cnh);
        
        if(ativo_ok && alugado_ok && marca_ok && categoria_ok) {
            veiculos[count] = veiculo;
            count++;
        }
    }
    fclose(arquivo_veiculos);
    
    if(count == 0)
    {
        printf("❌ Nenhum veículo disponível da marca %s para categoria %s\n", marca_desejada, categoria_cliente);
        printf("Pressione Enter para voltar...");
        getchar();
        getchar(); // Segundo getchar() para capturar o Enter
        return;
    }
    
    system("clear");
    printf("\n╔════════════════════════════════════════╗\n");
    printf("║         VEÍCULOS DISPONÍVEIS           ║\n");
    printf("╚════════════════════════════════════════╝\n\n");
    
    for(int i = 0; i < count; i++){
        printf("%d - %s %s; Placa: %s\n", i + 1, veiculos[i].marca, veiculos[i].modelo, veiculos[i].placa);
    }
    
    int opcao;
    printf("\nSelecione o veículo desejado (1-%d): ", count);
    scanf("%d", &opcao);
    
    if(opcao < 1 || opcao > count)
    {
        printf("❌ Opção inválida!\n");
        printf("Pressione Enter para voltar...");
        getchar();
        getchar();
        return;
    }
    
    Veiculo veiculo_escolhido = veiculos[opcao - 1];
    system("clear");
    printf("\n╔════════════════════════════════════════╗\n");
    printf("║              VALOR DA DIÁRIA           ║\n");
    printf("╚════════════════════════════════════════╝\n\n");
    printf("Veículo: %s %s\n", veiculo_escolhido.marca, veiculo_escolhido.modelo);
    printf("Placa: %s\n", veiculo_escolhido.placa);
    printf("Valor da diária: R$ %.2f\n\n", veiculo_escolhido.valor_diaria);
    
    int dias;
    printf("Quantos dias deseja alugar o veículo? ");
    scanf("%d", &dias);
    
    if(dias <= 0)
    {
        printf("❌ Quantidade de dias inválida!\n");
        printf("Pressione Enter para voltar...");
        getchar();
        getchar();
        return;
    }
    
    float valor_total = veiculo_escolhido.valor_diaria * dias;
    
    time_t t = time(NULL);
    struct tm *tm_info = localtime(&t);
    
    char data_aluguel[11], data_devolucao[11];
    
    strftime(data_aluguel, 11, "%d/%m/%Y", tm_info);
    
    struct tm devolucao = *tm_info;
    devolucao.tm_mday += dias;
    mktime(&devolucao);
    strftime(data_devolucao, 11, "%d/%m/%Y", &devolucao);
    
    Locacao locacao;
    strcpy(locacao.CPF_cliente, cpf_cliente);
    strcpy(locacao.placa_veiculo, veiculo_escolhido.placa);
    strcpy(locacao.data_aluguel, data_aluguel);
    strcpy(locacao.data_devolucao, data_devolucao);
    locacao.dias_aluguel = dias;
    locacao.valor_total = valor_total;
    locacao.entregue_no_prazo = 1;
    
    FILE *arquivo_locacoes = fopen("relatorios.bin", "ab");
    if(arquivo_locacoes == NULL)
    {
        printf("❌ Erro ao salvar relatório!\n");
        printf("Pressione Enter para voltar...");
        getchar();
        getchar();
        return;
    }
    
    fwrite(&locacao, sizeof(Locacao), 1, arquivo_locacoes);
    fclose(arquivo_locacoes);
    
    FILE *arquivo_veiculos_atualizar = fopen("veiculos.bin", "r+b");
    if(arquivo_veiculos_atualizar != NULL)
    {
        Veiculo v;
        while(fread(&v, sizeof(Veiculo), 1, arquivo_veiculos_atualizar)){
            if(strcmp(v.placa, veiculo_escolhido.placa) == 0)
            {
                v.alugado = 1;
                fseek(arquivo_veiculos_atualizar, -sizeof(Veiculo), SEEK_CUR);
                fwrite(&v, sizeof(Veiculo), 1, arquivo_veiculos_atualizar);
                break;
            }
        }
        fclose(arquivo_veiculos_atualizar);
    }
    
    system("clear");
    printf("╔════════════════════════════════════════╗\n");
    printf("║         LOCAÇÃO CONCLUÍDA!            ║\n");
    printf("╚════════════════════════════════════════╝\n\n");
    
    printf("✅ Locação registrada com sucesso!\n\n");
    printf("CLIENTE: %s\n", cliente.nome);
    printf("CPF: %s\n", cpf_cliente);
    printf("VEÍCULO: %s %s\n", veiculo_escolhido.marca, veiculo_escolhido.modelo);
    printf("PLACA: %s\n", veiculo_escolhido.placa);
    printf("DATA DE ALUGUEL: %s\n", data_aluguel);
    printf("DATA DE DEVOLUÇÃO: %s\n", data_devolucao);
    printf("DIAS CONTRATADOS: %d\n", dias);
    printf("VALOR TOTAL: R$ %.2f\n\n", valor_total);
    printf("STATUS: ENTREGA NO PRAZO ✅\n\n");
    
    printf("Pressione Enter para voltar...");
    getchar();
    getchar();
}
