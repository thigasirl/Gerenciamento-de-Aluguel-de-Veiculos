#include <stdio.h>
#include <stdlib.h>
#include "sistema.h"
#include <ctype.h>
#include <string.h>

void dados_cliente()
{
    int opcao_final;
    
    do {
        FILE *clientes = fopen("clientes.bin","ab");
        
        if(clientes == NULL){
            printf("❌ Erro ao abrir arquivo de clientes!\n");
            return;
        }
        
        Cliente novo_cliente;
        memset(&novo_cliente, 0, sizeof(Cliente));
        system("clear");
        printf("=== DADOS PESSOAIS ===\n\n");
        
        
        printf("Nome completo: ");
        scanf(" %[^\n]", novo_cliente.nome);
        
        //========================================================
        printf("\nCPF (11 dígitos): ");
        char cpf_temp[12];
        do {
            scanf("%11s", cpf_temp);
            while (getchar() != '\n');
    
            if(strlen(cpf_temp) != 11)
            {
                printf("CPF deve ter exatamente 11 dígitos! Digite novamente: ");
                continue;
            }
    
            int apenas_numeros = 1;
            for(int i = 0; i < 11; i++) {
                if(!isdigit(cpf_temp[i]))
                {
                    apenas_numeros = 0;
                    break;
                }
            }
    
            if(!apenas_numeros)
            {
                printf("CPF deve conter apenas números! Digite novamente: ");
                continue;
            }
    
            if(!validarCPF(cpf_temp))
            {
            printf("CPF inválido! Digite novamente: ");
            } else {
                strcpy(novo_cliente.CPF, cpf_temp);
            }
        }while(!validarCPF(cpf_temp));

        //========================================================
        printf("\nCNH (11 dígitos): ");
        char cnh_temp[12];
        do {
            scanf("%11s", cnh_temp);
            while (getchar() != '\n');
    
            if(strlen(cnh_temp) != 11)
            {
                printf("CNH deve ter exatamente 11 dígitos! Digite novamente: ");
                continue;
            }
    
            int apenas_numeros = 1;
            for(int i = 0; i < 11; i++){
                if(!isdigit(cnh_temp[i])){
                    apenas_numeros = 0;
                    break;
                }
            }
    
            if(!apenas_numeros){
                printf("CNH deve conter apenas números! Digite novamente: ");
                continue;
            }
    
                if(!validarCNH(cnh_temp))
                {
                    printf("CNH inválida! Digite novamente: ");
                } else {
                    strcpy(novo_cliente.CNH, cnh_temp);
                }
        } while(!validarCNH(cnh_temp));

        //=========================================================
        printf("\nCategoria CNH (A, B, C, D, E, AB): ");
        do 
        {
            scanf("%2s", novo_cliente.categoria_cnh);
            for (int i = 0; novo_cliente.categoria_cnh[i]; i++){
                novo_cliente.categoria_cnh[i] = toupper(novo_cliente.categoria_cnh[i]);
            }
            if(!validarCategoriaCNH(novo_cliente.categoria_cnh)){
                printf("Categoria inválida! Digite (A, B, C, D, E, AB): ");
            }
        }while(!validarCategoriaCNH(novo_cliente.categoria_cnh));
        
        //==========================================================
        printf("\nTelefone (apenas números): ");
        scanf("%lld", &novo_cliente.telefone);
        while (getchar() != '\n');  // limpa buffer
        
        //==========================================================
        
        novo_cliente.ativo = 1;

        fwrite(&novo_cliente, sizeof(Cliente), 1, clientes);
        fclose(clientes);
        
        system("clear");
        printf("\n✅ Cliente cadastrado com sucesso!\n\n");
        
        printf("1 - Cadastrar novo cliente\n2 - Voltar\n\n");
        printf("\nSelecione a opção: ");
        scanf("%d", &opcao_final);
        
        while (getchar() != '\n');
        
        if (opcao_final != 1) {
            return;
        }
    }while(opcao_final == 1);
}
