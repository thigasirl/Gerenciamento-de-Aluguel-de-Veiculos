#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sistema.h"

void consulta_cliente() {
    char cpf_busca[12];
    int opcao;
    
    do {
        system("clear");
        printf("╔════════════════════════════════════════╗\n");
        printf("║           CONSULTA DE CLIENTE          ║\n");
        printf("╚════════════════════════════════════════╝\n\n");
        
        printf("1 - Buscar por CPF\n");
        printf("2 - Voltar ao menu principal\n\n");
        printf("Selecione a opção: ");
        scanf("%d", &opcao);
        
        if(opcao == 2) {
            return;
        }
        
        if(opcao != 1) {
            printf("❌ Opção inválida!\n");
            printf("Pressione Enter para continuar...");
            getchar(); getchar();
            continue;
        }
        printf("Digite o CPF do cliente (11 dígitos): ");
        scanf("%11s", cpf_busca);
        
        Cliente cliente;
        int cliente_encontrado = 0;
        long posicao = 0;
        
        FILE *arquivo_clientes = fopen("clientes.bin", "rb");
        if(arquivo_clientes == NULL)
        {
            printf("❌ Erro ao abrir arquivo de clientes!\n\n");
            printf("Pressione Enter para voltar...");
            getchar(); 
            getchar();
            return;
        }
        
        while(fread(&cliente, sizeof(Cliente), 1, arquivo_clientes)){
            if(cliente.ativo != 0 && cliente.ativo != 1)
            {
                cliente.ativo = 1;
            }
            
            if(strcmp(cliente.CPF, cpf_busca) == 0 && cliente.ativo == 1)
            {
                cliente_encontrado = 1;
                posicao = ftell(arquivo_clientes) - sizeof(Cliente);
                break;
            }
        }
        fclose(arquivo_clientes);
        
        if(!cliente_encontrado)
        {
            printf("❌ Cliente não encontrado ou inativo!\n\n");
            printf("Pressione Enter para voltar...");
            getchar(); 
            getchar();
            return;
        }
        
        system("clear");
        printf("╔════════════════════════════════════════╗\n");
        printf("║           DADOS DO CLIENTE             ║\n");
        printf("╚════════════════════════════════════════╝\n\n");
        
        printf("Nome: %s\n", cliente.nome);
        printf("CPF: %s\n", cliente.CPF);
        printf("CNH: %s\n", cliente.CNH);
        printf("Categoria CNH: %s\n", cliente.categoria_cnh);
        printf("Telefone: %lld\n", cliente.telefone);
        printf("Status: %s\n\n", cliente.ativo ? "Ativo ✅" : "Inativo ❌");
        
        printf("═══════════════════════════════════════════\n");
        printf("            LOCAÇÕES DO CLIENTE           \n");
        printf("═══════════════════════════════════════════\n\n");
        
        Locacao locacoes[100];
        int count_locacoes = 0;
        
        FILE *arquivo_locacoes = fopen("relatorios.bin", "rb");
        if(arquivo_locacoes != NULL)
        {
            Locacao locacao;
            while(fread(&locacao, sizeof(Locacao), 1, arquivo_locacoes)){
                if(strcmp(locacao.CPF_cliente, cpf_busca) == 0)
                {
                    locacoes[count_locacoes] = locacao;
                    count_locacoes++;
                }
            }
            fclose(arquivo_locacoes);
        }
        
        if(count_locacoes == 0)
        {
            printf("Nenhuma locação encontrada para este cliente.\n\n");
        } else {
            printf("Total de locações: %d\n\n", count_locacoes);
            for(int i = 0; i < count_locacoes; i++){
                printf("%d - Placa: %s | Período: %s a %s\n", 
                       i + 1, locacoes[i].placa_veiculo, 
                       locacoes[i].data_aluguel, locacoes[i].data_devolucao);
                printf("   Valor: R$ %.2f | Status: %s\n\n",
                       locacoes[i].valor_total, 
                       locacoes[i].entregue_no_prazo ? "No prazo ✅" : "Atrasado ❌");
            }
        }
        
        printf("═══════════════════════════════════════════\n");
        printf("                  OPÇÕES                  \n");
        printf("═══════════════════════════════════════════\n\n");
        
        printf("1 - Voltar\n");
        printf("2 - Atualizar dados\n");
        printf("3 - Excluir cliente\n\n");
        printf("Selecione a opção: ");
        scanf("%d", &opcao);
        
        switch(opcao){
            case 1:
                return;
                
            case 2:
                atualizar_cliente(cpf_busca, posicao);
                break;
                
            case 3:
                excluir_cliente(cpf_busca, posicao, count_locacoes);
                break;
                
            default:
                printf("❌ Opção inválida!\n");
                printf("Pressione Enter para continuar...");
                getchar(); getchar();
                break;
        }
        
    } while(opcao != 1);
}
