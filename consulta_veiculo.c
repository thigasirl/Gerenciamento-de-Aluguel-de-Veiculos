#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "sistema.h"

void consulta_veiculo() {
    char marca_busca[30];
    int opcao;
    
    do {
        system("clear");
        printf("╔════════════════════════════════════════╗\n");
        printf("║           CONSULTA DE VEÍCULO          ║\n");
        printf("╚════════════════════════════════════════╝\n\n");
        
        printf("1 - Buscar por marca\n");
        printf("2 - Voltar ao menu principal\n\n");
        printf("Selecione a opção: ");
        scanf("%d", &opcao);
        
        if(opcao == 2) {
            return;
        }
        printf("Digite a marca do veículo: ");
        scanf("%29s", marca_busca);
        
        for(int i = 0; marca_busca[i]; i++){
            marca_busca[i] = toupper(marca_busca[i]);
        }
        
        Veiculo veiculos[100];
        int count_veiculos = 0;
        
        FILE *arquivo_veiculos = fopen("veiculos.bin", "rb");
        if(arquivo_veiculos == NULL)
        {
            printf("❌ Erro ao abrir arquivo de veículos!\n\n");
            printf("Pressione Enter para voltar...");
            getchar(); 
            getchar();
            return;
        }
        
        Veiculo veiculo;
        while(fread(&veiculo, sizeof(Veiculo), 1, arquivo_veiculos)){
            if(strcmp(veiculo.marca, marca_busca) == 0 && veiculo.ativo == 1)
            {
                veiculos[count_veiculos] = veiculo;
                count_veiculos++;
            }
        }
        fclose(arquivo_veiculos);
        
        if(count_veiculos == 0)
        {
            printf("❌ Nenhum veículo da marca %s encontrado!\n\n", marca_busca);
            printf("Pressione Enter para voltar...");
            getchar(); 
            getchar();
            return;
        }
        
        system("clear");
        printf("╔════════════════════════════════════════╗\n");
        printf("║           VEÍCULOS ENCONTRADOS         ║\n");
        printf("╚════════════════════════════════════════╝\n\n");
        
        for(int i = 0; i < count_veiculos; i++){
            printf("%d - %s %s | Placa: %s\n", 
                   i + 1, veiculos[i].marca, veiculos[i].modelo, veiculos[i].placa);
            printf("   Categoria: %s | Diária: R$ %.2f\n",
                   veiculos[i].categoria_cnh, veiculos[i].valor_diaria);
            printf("   Status: %s\n\n", 
                   veiculos[i].alugado ? "Alugado 🔴" : "Disponível ✅");
        }
        
        int selecao;
        printf("Selecione o veículo (1-%d): ", count_veiculos);
        scanf("%d", &selecao);
        
        if(selecao < 1 || selecao > count_veiculos)
        {
            printf("❌ Opção inválida!\n");
            printf("Pressione Enter para voltar...");
            getchar(); getchar();
            return;
        }
        
        Veiculo veiculo_selecionado = veiculos[selecao - 1];
        long posicao = 0;
        
        FILE *arquivo_pos = fopen("veiculos.bin", "rb");
        if(arquivo_pos != NULL)
        {
            Veiculo v;
            while(fread(&v, sizeof(Veiculo), 1, arquivo_pos)){
                if(strcmp(v.placa, veiculo_selecionado.placa) == 0)
                {
                    posicao = ftell(arquivo_pos) - sizeof(Veiculo);
                    break;
                }
            }
            fclose(arquivo_pos);
        }
        
        system("clear");
        printf("╔════════════════════════════════════════╗\n");
        printf("║           DADOS DO VEÍCULO             ║\n");
        printf("╚════════════════════════════════════════╝\n\n");
        
        printf("Marca: %s\n", veiculo_selecionado.marca);
        printf("Modelo: %s\n", veiculo_selecionado.modelo);
        printf("Placa: %s\n", veiculo_selecionado.placa);
        printf("Categoria CNH: %s\n", veiculo_selecionado.categoria_cnh);
        printf("Valor da diária: R$ %.2f\n", veiculo_selecionado.valor_diaria);
        printf("Status: %s\n", veiculo_selecionado.ativo ? "Ativo ✅" : "Inativo ❌");
        printf("Locação: %s\n\n", 
               veiculo_selecionado.alugado ? "Alugado 🔴" : "Disponível ✅");
        
        if(veiculo_selecionado.alugado)
        {
            printf("═══════════════════════════════════════════\n");
            printf("            INFORMAÇÕES DA LOCAÇÃO        \n");
            printf("═══════════════════════════════════════════\n\n");
            
            FILE *arquivo_locacoes = fopen("relatorios.bin", "rb");
            if(arquivo_locacoes != NULL)
            {
                Locacao locacao;
                int locacao_encontrada = 0;
                
                while(fread(&locacao, sizeof(Locacao), 1, arquivo_locacoes)){
                    if(strcmp(locacao.placa_veiculo, veiculo_selecionado.placa) == 0)
                    {
                        Cliente cliente;
                        char nome_cliente[100] = "Cliente não encontrado";
                        FILE *arquivo_clientes = fopen("clientes.bin", "rb");
                        if(arquivo_clientes != NULL)
                        {
                            while(fread(&cliente, sizeof(Cliente), 1, arquivo_clientes)){
                                if(strcmp(cliente.CPF, locacao.CPF_cliente) == 0)
                                {
                                    strcpy(nome_cliente, cliente.nome);
                                    break;
                                }
                            }
                            fclose(arquivo_clientes);
                        }
                        
                        printf("Cliente: %s\n", nome_cliente);
                        printf("CPF: %s\n", locacao.CPF_cliente);
                        printf("Período: %s a %s\n", locacao.data_aluguel, locacao.data_devolucao);
                        printf("Dias contratados: %d\n", locacao.dias_aluguel);
                        printf("Valor total: R$ %.2f\n", locacao.valor_total);
                        printf("Status: %s\n\n", 
                               locacao.entregue_no_prazo ? "No prazo ✅" : "Atrasado ❌");
                        locacao_encontrada = 1;
                        break;
                    }
                }
                fclose(arquivo_locacoes);
                
                if(!locacao_encontrada)
                {
                    printf("Informações de locação não encontradas.\n\n");
                }
            }
        }
        
        printf("═══════════════════════════════════════════\n");
        printf("                  OPÇÕES                  \n");
        printf("═══════════════════════════════════════════\n\n");
        
        printf("1 - Voltar\n");
        printf("2 - Atualizar valor da diária\n");
        printf("3 - Excluir veículo\n\n");
        printf("Selecione a opção: ");
        scanf("%d", &opcao);
        
        switch(opcao){
            case 1:
                return;
                
            case 2:
                if(veiculo_selecionado.alugado)
                {
                    printf("\n❌ Não é possível alterar o valor da diária!\n");
                    printf("Motivo: Veículo está atualmente alugado.\n\n");
                    printf("Pressione Enter para continuar...");
                    getchar(); 
                    getchar();
                } else {
                    atualizar_veiculo(veiculo_selecionado.placa, posicao);
                }
                break;
                
            case 3:
                excluir_veiculo(veiculo_selecionado.placa, posicao);
                break;
                
            default:
                printf("❌ Opção inválida!\n");
                printf("Pressione Enter para continuar...");
                getchar(); getchar();
                break;
        }
        
    } while(opcao != 1);
}
