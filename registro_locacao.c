#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sistema.h"

void registro_locacao(){
    int opcao;
    
    do {
        system("clear");
        printf("╔════════════════════════════════════════╗\n");
        printf("║            RELATÓRIOS DE LOCAÇÃO       ║\n");
        printf("╚════════════════════════════════════════╝\n\n");
        
        Locacao locacoes[100];
        int count = 0;
        
        FILE *arquivo = fopen("relatorios.bin", "rb");
        if(arquivo == NULL)
        {
            printf("❌ Nenhum relatório de locação encontrado!\n\n");
            printf("Pressione Enter para voltar...");
            getchar();
            getchar();
            return;
        }
        
        while(fread(&locacoes[count], sizeof(Locacao), 1, arquivo)) {
            count++;
        }
        fclose(arquivo);
        
        if(count == 0) {
            printf("❌ Nenhuma locação registrada!\n\n");
            printf("Pressione Enter para voltar...");
            getchar();
            getchar();
            return;
        }
        
        for(int i = 0; i < count - 1; i++) {
            for(int j = i + 1; j < count; j++) {
                int dia_i, mes_i, ano_i;
                int dia_j, mes_j, ano_j;
                sscanf(locacoes[i].data_devolucao, "%d/%d/%d", &dia_i, &mes_i, &ano_i);
                sscanf(locacoes[j].data_devolucao, "%d/%d/%d", &dia_j, &mes_j, &ano_j);
                
                if(ano_i > ano_j || (ano_i == ano_j && mes_i > mes_j) || (ano_i == ano_j && mes_i == mes_j && dia_i > dia_j)) {
                    Locacao temp = locacoes[i];
                    locacoes[i] = locacoes[j];
                    locacoes[j] = temp;
                }
            }
        }
        
        printf("Locações em ordem de prazo de devolução:\n\n");
        for(int i = 0; i < count; i++) {
            printf("%d - CPF: %s | Placa: %s\n", i + 1, locacoes[i].CPF_cliente, locacoes[i].placa_veiculo);
            printf("   Período: %s até %s | Valor: R$ %.2f\n", 
                   locacoes[i].data_aluguel, locacoes[i].data_devolucao, locacoes[i].valor_total);
            printf("   Status: %s\n\n", locacoes[i].entregue_no_prazo ? "No prazo ✅" : "Atrasado ❌");
        }
        
        printf("Selecione uma locação (1-%d) ou 0 para voltar: ", count);
        scanf("%d", &opcao);
        
        if(opcao == 0)
        {
            return;
        }
        
        if(opcao < 1 || opcao > count)
        {
            printf("❌ Opção inválida!\n");
            printf("Pressione Enter para continuar...");
            getchar(); 
            getchar();
            continue;
        }
        
        Locacao locacao_selecionada = locacoes[opcao - 1];
        
        system("clear");
        printf("╔════════════════════════════════════════╗\n");
        printf("║           DETALHES DA LOCAÇÃO          ║\n");
        printf("╚════════════════════════════════════════╝\n\n");
        
        printf("CPF do Cliente: %s\n", locacao_selecionada.CPF_cliente);
        printf("Placa do Veículo: %s\n", locacao_selecionada.placa_veiculo);
        printf("Data de Aluguel: %s\n", locacao_selecionada.data_aluguel);
        printf("Data de Devolução: %s\n", locacao_selecionada.data_devolucao);
        printf("Dias Alugados: %d\n", locacao_selecionada.dias_aluguel);
        printf("Valor Total: R$ %.2f\n", locacao_selecionada.valor_total);
        printf("Status: %s\n\n", locacao_selecionada.entregue_no_prazo ? "No prazo ✅" : "Atrasado ❌");
        
        Cliente cliente;
        char nome_cliente[100] = "NÃO ENCONTRADO";
        FILE *arquivo_clientes = fopen("clientes.bin", "rb");
        if(arquivo_clientes != NULL)
        {
            while(fread(&cliente, sizeof(Cliente), 1, arquivo_clientes)) {
                if(strcmp(cliente.CPF, locacao_selecionada.CPF_cliente) == 0) {
                    strcpy(nome_cliente, cliente.nome);
                    break;
                }
            }
            fclose(arquivo_clientes);
        }
        system("clear");
        printf("Nome do Cliente: %s\n\n", nome_cliente);
        
        int opcao_locacao;
        printf("1 - Finalizar Locação (Devolver Veículo)\n");
        printf("2 - Voltar para a lista\n\n");
        printf("Selecione a opção: ");
        scanf("%d", &opcao_locacao);
        
        if(opcao_locacao == 1)
        {
            FILE *arquivo_temp = fopen("temp_relatorios.bin", "wb");
            FILE *arquivo_original = fopen("relatorios.bin", "rb");
            
            if(arquivo_original == NULL || arquivo_temp == NULL)
            {
                printf("❌ Erro ao processar arquivo!\n");
                if(arquivo_original) fclose(arquivo_original);
                if(arquivo_temp) fclose(arquivo_temp);
                printf("Pressione Enter para continuar...");
                getchar(); 
                getchar();
                continue;
            }
            
            Locacao locacao;
            int removido = 0;
            while(fread(&locacao, sizeof(Locacao), 1, arquivo_original)){
                if(strcmp(locacao.CPF_cliente, locacao_selecionada.CPF_cliente) != 0 || 
                   strcmp(locacao.placa_veiculo, locacao_selecionada.placa_veiculo) != 0) {
                    fwrite(&locacao, sizeof(Locacao), 1, arquivo_temp);
                } else {
                    removido = 1;
                }
            }
            
            fclose(arquivo_original);
            fclose(arquivo_temp);
            
            remove("relatorios.bin");
            rename("temp_relatorios.bin", "relatorios.bin");
            
            FILE *arquivo_veiculos = fopen("veiculos.bin", "r+b");
            if(arquivo_veiculos != NULL)
            {
                Veiculo v;
                while(fread(&v, sizeof(Veiculo), 1, arquivo_veiculos)) {
                    if(strcmp(v.placa, locacao_selecionada.placa_veiculo) == 0)
                    {
                        v.alugado = 0;
                        fseek(arquivo_veiculos, -sizeof(Veiculo), SEEK_CUR);
                        fwrite(&v, sizeof(Veiculo), 1, arquivo_veiculos);
                        break;
                    }
                }
                fclose(arquivo_veiculos);
            }
            system("clear");
            if(removido)
            {
                printf("\n✅ Locação finalizada com sucesso! Veículo liberado.\n");
            } else {
                printf("\n❌ Erro ao finalizar locação!\n");
            }
            
            printf("Pressione Enter para continuar...");
            getchar(); 
            getchar();
            return;
        }
        else if(opcao_locacao == 2)
        {
            continue;
        }
        
    } while(opcao != 0);
}
