#include <stdio.h>
#include <stdlib.h>
#include "sistema.h"
#include <ctype.h>
#include <string.h>

void dados_veiculo()
{
    int opcao_final;
    
    do {
        FILE *veiculos = fopen("veiculos.bin","ab");
        
        if(veiculos == NULL){
            printf("❌ Erro ao abrir arquivo de veículos!\n");
            return;
        }
        
        Veiculo novo_veiculo;
        memset(&novo_veiculo, 0, sizeof(Veiculo));
        system("clear");
        printf("=== DADOS DO VEUCULO ===\n\n");
        
        //========================================================
        printf("Placa (7 caracteres, ex: ABC1D23): ");
        do 
        {
            scanf("%7s", novo_veiculo.placa);
            while (getchar() != '\n');
            
            for(int i = 0; novo_veiculo.placa[i]; i++){
                novo_veiculo.placa[i] = toupper(novo_veiculo.placa[i]);
            }
            
            if(!validarPlaca(novo_veiculo.placa)){
                printf("Placa inválida! Use 7 caracteres (ex: ABC1D23): ");
            }
        }while(!validarPlaca(novo_veiculo.placa));
        
        //========================================================
        printf("\nMarca (até 30 caracteres): ");
        scanf(" %[^\n]", novo_veiculo.marca);
        for(int i = 0; novo_veiculo.marca[i]; i++){
            novo_veiculo.marca[i] = toupper(novo_veiculo.marca[i]);
        }
        
        //========================================================
        printf("\nModelo (até 50 caracteres): ");
        scanf(" %[^\n]", novo_veiculo.modelo);
        
        //========================================================
        printf("\nCategoria CNH (A, B, C, D, E, AB): ");
        do 
        {
            scanf("%2s", novo_veiculo.categoria_cnh);
            for (int i = 0; novo_veiculo.categoria_cnh[i]; i++){
                novo_veiculo.categoria_cnh[i] = toupper(novo_veiculo.categoria_cnh[i]);
            }
            if(!validarCategoriaCNH(novo_veiculo.categoria_cnh)){
                printf("Categoria inválida! Digite (A, B, C, D, E, AB): ");
            }
        }while(!validarCategoriaCNH(novo_veiculo.categoria_cnh));
        
        //========================================================
        printf("\nValor da diária (ex: 150.00): ");
        do 
        {
            if(scanf("%f", &novo_veiculo.valor_diaria) != 1){
                printf("Erro na leitura. Digite um valor válido (ex: 150.00): ");
                while (getchar() != '\n');
                continue;
            }
            if(novo_veiculo.valor_diaria <= 0){
                printf("Valor deve ser maior que zero! Digite novamente: ");
            }
        }while(novo_veiculo.valor_diaria <= 0);
        
        //========================================================
        
        novo_veiculo.ativo = 1;
        
        fwrite(&novo_veiculo, sizeof(Veiculo), 1, veiculos);
        fclose(veiculos);
        
        system("clear");
        printf("\n✅ Veículo cadastrado com sucesso!\n\n");
        
        printf("1 - Cadastrar novo veículo\n2 - Voltar\n\n");
        printf("Selecione a opção: ");
        scanf("%d", &opcao_final);
        
        while (getchar() != '\n');
        
        if (opcao_final != 1) {
            return;
        }
    }while(opcao_final == 1);
}
        
        #include <stdio.h>
#include <stdlib.h>
#include "sistema.h"
#include <ctype.h>
#include <string.h>

void dados_veiculo()
{
    int opcao_final;
    
    do {
        FILE *veiculos = fopen("veiculos.bin","ab");
        
        if(veiculos == NULL){
            printf("❌ Erro ao abrir arquivo de veículos!\n");
            return;
        }
        
        Veiculo novo_veiculo;
        memset(&novo_veiculo, 0, sizeof(Veiculo));
        system("clear");
        printf("=== DADOS DO VEUCULO ===\n\n");
        
        //========================================================
        printf("Placa (7 caracteres, ex: ABC1D23): ");
        do 
        {
            scanf("%7s", novo_veiculo.placa);
            while (getchar() != '\n');
            
            for(int i = 0; novo_veiculo.placa[i]; i++){
                novo_veiculo.placa[i] = toupper(novo_veiculo.placa[i]);
            }
            
            if(!validarPlaca(novo_veiculo.placa)){
                printf("Placa inválida! Use 7 caracteres (ex: ABC1D23): ");
            }
        }while(!validarPlaca(novo_veiculo.placa));
        
        //========================================================
        printf("\nMarca (até 30 caracteres): ");
        scanf(" %[^\n]", novo_veiculo.marca);
        for(int i = 0; novo_veiculo.marca[i]; i++){
            novo_veiculo.marca[i] = toupper(novo_veiculo.marca[i]);
        }
        
        //========================================================
        printf("\nModelo (até 50 caracteres): ");
        scanf(" %[^\n]", novo_veiculo.modelo);
        
        //========================================================
        printf("\nCategoria CNH (A, B, C, D, E, AB): ");
        do 
        {
            scanf("%2s", novo_veiculo.categoria_cnh);
            for (int i = 0; novo_veiculo.categoria_cnh[i]; i++){
                novo_veiculo.categoria_cnh[i] = toupper(novo_veiculo.categoria_cnh[i]);
            }
            if(!validarCategoriaCNH(novo_veiculo.categoria_cnh)){
                printf("Categoria inválida! Digite (A, B, C, D, E, AB): ");
            }
        }while(!validarCategoriaCNH(novo_veiculo.categoria_cnh));
        
        //========================================================
        printf("\nValor da diária (ex: 150.00): ");
        do 
        {
            if(scanf("%f", &novo_veiculo.valor_diaria) != 1){
                printf("Erro na leitura. Digite um valor válido (ex: 150.00): ");
                while (getchar() != '\n');
                continue;
            }
            if(novo_veiculo.valor_diaria <= 0){
                printf("Valor deve ser maior que zero! Digite novamente: ");
            }
        }while(novo_veiculo.valor_diaria <= 0);
        
        //========================================================
        
        novo_veiculo.ativo = 1;
        
        fwrite(&novo_veiculo, sizeof(Veiculo), 1, veiculos);
        fclose(veiculos);
        
        system("clear");
        printf("\n✅ Veículo cadastrado com sucesso!\n\n");
        
        printf("1 - Cadastrar novo veículo\n2 - Voltar\n\n");
        printf("Selecione a opção: ");
        scanf("%d", &opcao_final);
        
        while (getchar() != '\n');
        
        if (opcao_final != 1) {
            return;
        }
    }while(opcao_final == 1);
}
