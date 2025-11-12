#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sistema.h"

void excluir_cliente(char cpf_busca[12], long posicao, int tem_locacoes) {
    system("clear");
    printf("╔════════════════════════════════════════╗\n");
    printf("║            EXCLUIR CLIENTE             ║\n");
    printf("╚════════════════════════════════════════╝\n\n");
    
    if(tem_locacoes > 0)
    {
        printf("❌ Não é possível excluir este cliente!\n");
        printf("O cliente possui %d locação(ões) ativa(s).\n\n", tem_locacoes);
        printf("Pressione Enter para voltar...");
        getchar(); 
        getchar();
        return;
    }
    
    printf("Tem certeza que deseja excluir este cliente? (s/n): ");
    char confirmacao;
    scanf(" %c", &confirmacao);
    
    if(confirmacao == 's' || confirmacao == 'S')
    {
        FILE *arquivo = fopen("clientes.bin", "r+b");
        if(arquivo != NULL)
        {
            Cliente cliente;
            fseek(arquivo, posicao, SEEK_SET);
            fread(&cliente, sizeof(Cliente), 1, arquivo);
            cliente.ativo = 0;
            fseek(arquivo, posicao, SEEK_SET);
            fwrite(&cliente, sizeof(Cliente), 1, arquivo);
            fclose(arquivo);
            printf("\n✅ Cliente excluído com sucesso!\n");
        } else {
            printf("\n❌ Erro ao excluir cliente!\n");
        }
    } else {
        printf("\nOperação cancelada.\n");
    }
    
    printf("Pressione Enter para continuar...");
    getchar(); 
    getchar();
}
