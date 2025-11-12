#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "sistema.h"

void excluir_veiculo(char placa[8], long posicao) {
    system("clear");
    printf("╔════════════════════════════════════════╗\n");
    printf("║           EXCLUIR VEÍCULO              ║\n");
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
    
    printf("Veículo: %s %s\n", veiculo.marca, veiculo.modelo);
    printf("Placa: %s\n\n", veiculo.placa);
    
    if(veiculo.alugado)
    {
        printf("❌ Não é possível excluir este veículo!\n");
        printf("Motivo: Veículo está atualmente alugado.\n\n");
        printf("Pressione Enter para voltar...");
        getchar(); 
        getchar();
        fclose(arquivo_veiculos);
        return;
    }
    
    char confirmacao;
    printf("⚠️  TEM CERTEZA QUE DESEJA EXCLUIR ESTE VEÍCULO?\n");
    printf("Esta ação não pode ser desfeita! (s/N): ");
    scanf(" %c", &confirmacao);
    
    if(confirmacao == 's' || confirmacao == 'S')
    {
        veiculo.ativo = 0;
        
        fseek(arquivo_veiculos, posicao, SEEK_SET);
        fwrite(&veiculo, sizeof(Veiculo), 1, arquivo_veiculos);
        fclose(arquivo_veiculos);
        
        printf("\n✅ Veículo excluído com sucesso!\n");
    }
    else
    {
        fclose(arquivo_veiculos);
        printf("\nOperação cancelada.\n");
    }
    
    printf("Pressione Enter para continuar...");
    getchar(); 
    getchar();
}
