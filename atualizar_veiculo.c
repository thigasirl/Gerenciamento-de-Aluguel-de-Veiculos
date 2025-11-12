#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "sistema.h"

void atualizar_veiculo(char placa[8], long posicao) {
    system("clear");
    printf("╔════════════════════════════════════════╗\n");
    printf("║         ATUALIZAR VEÍCULO              ║\n");
    printf("╚════════════════════════════════════════╝\n\n");
    
    FILE *arquivo_veiculos = fopen("veiculos.bin", "r+b");
    if(arquivo_veiculos == NULL)
    {
        printf("❌ Erro ao abrir arquivo de veículos!\n");
        printf("Pressione Enter para voltar...");
        getchar(); 
        getchar();
        return;
    }
    
    Veiculo veiculo;
    fseek(arquivo_veiculos, posicao, SEEK_SET);
    fread(&veiculo, sizeof(Veiculo), 1, arquivo_veiculos);
    
    printf("Veículo: %s %s - Placa: %s\n\n", veiculo.marca, veiculo.modelo, veiculo.placa);
    printf("Valor atual da diária: R$ %.2f\n\n", veiculo.valor_diaria);
    
    float novo_valor;
    printf("Digite o novo valor da diária: R$ ");
    scanf("%f", &novo_valor);
    
    if(novo_valor <= 0)
    {
        printf("❌ Valor inválido!\n");
        printf("Pressione Enter para voltar...");
        getchar(); getchar();
        fclose(arquivo_veiculos);
        return;
    }
    
    veiculo.valor_diaria = novo_valor;
    
    fseek(arquivo_veiculos, posicao, SEEK_SET);
    fwrite(&veiculo, sizeof(Veiculo), 1, arquivo_veiculos);
    fclose(arquivo_veiculos);
    
    printf("\n✅ Valor da diária atualizado com sucesso!\n");
    printf("Novo valor: R$ %.2f\n\n", veiculo.valor_diaria);
    printf("Pressione Enter para continuar...");
    getchar(); 
    getchar();
}
