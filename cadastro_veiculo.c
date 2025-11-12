#include <stdio.h>
#include <stdlib.h>
#include "sistema.h"

void cadastro_veiculo()
{
    system("clear");
    printf("╔════════════════════════════════════════╗\n");
    printf("║         CADASTRO DE VEICULO            ║\n");
    printf("╚════════════════════════════════════════╝\n\n");
    printf("Preencha os dados abaixo:\n");
    printf("• Todos os campos são obrigatórios\n");
    printf("• Placa: 7 caracteres\n");
    printf("• Categoria CNH: 2 caracteres\n\n");
    printf("Pressione Enter para começar...");
    
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
    getchar();
    
    dados_veiculo();
}
