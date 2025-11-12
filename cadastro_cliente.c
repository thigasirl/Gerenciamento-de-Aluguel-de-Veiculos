#include <stdio.h>
#include <stdlib.h>
#include "sistema.h"

void cadastro_cliente()
{
    system("clear");
    printf("╔════════════════════════════════════════╗\n");
    printf("║         CADASTRO DE CLIENTE            ║\n");
    printf("╚════════════════════════════════════════╝\n\n");
    printf("Preencha os dados abaixo:\n");
    printf("• Todos os campos são obrigatórios\n");
    printf("• Use CPF apenas números (11 dígitos)\n");
    printf("• CNH apenas números\n\n");
    printf("Pressione Enter para começar...");
    getchar(); 
    getchar();
    
    dados_cliente();
}
