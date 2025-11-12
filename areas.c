#include "sistema.h"
#include <stdio.h>
#include <stdlib.h>

    void area_cadastro(){
        
    int opcao_cadastro;
    int voltar_cadastro = 0;
                
                while(!voltar_cadastro) { 
                    system("clear");
                    printf("╔════════════════════════════════════════╗\n");
                    printf("║             ÁREA DE CADASTRO           ║\n");
                    printf("╚════════════════════════════════════════╝\n\n");
                    printf("1 - Cadastrar cliente\n2 - Cadastrar veículo\n3- Voltar\n\n");
                    printf("\nSelecione a opção desejada: ");
                    scanf("%d",&opcao_cadastro);
                    
                    switch(opcao_cadastro){
                        case 1:{
                            cadastro_cliente();
                            break;
                        }
                        case 2:{
                            cadastro_veiculo();
                            break;
                        }
                        case 3:{
                            voltar_cadastro = 1;  
                            break;
                        }
                        default:{
                            system("clear");
                            printf("⚠️ Opção não existe!\n\n");
                            getchar(); 
                            getchar();
                            break;
                        }
                    }
                }
    };
                
    void area_consulta(){
        
    int opcao_consulta;
    int voltar_consulta = 0;  
                
                while(!voltar_consulta) {
                    system("clear");
                    printf("╔════════════════════════════════════════╗\n");
                    printf("║             ÁREA DE CONSULTA           ║\n");
                    printf("╚════════════════════════════════════════╝\n\n");
                    printf("1 - Consultar cliente\n2 - Consultar veículo\n3- Voltar\n\n");
                    printf("\nSelecione a opção desejada: ");
                    scanf("%d",&opcao_consulta);
                    
                    switch(opcao_consulta){
                        case 1:{
                            consulta_cliente();
                            break;
                        }
                        case 2:{
                            consulta_veiculo();
                            break;
                        }
                        case 3:{
                            voltar_consulta = 1;
                            break;
                        }
                        default:{
                            system("clear");
                            printf("⚠️ Opção não existe!\n\n");
                            getchar(); 
                            getchar();
                            break;
                        }
                    }
                }
        
    }
    
    void area_locacao(){
    
    int opcao;
    int voltar_locacao = 0;
    
    while(!voltar_locacao) {
        printf("\033[2J\033[H");
        printf("╔════════════════════════════════════════╗\n");
        printf("║             ÁREA DE LOCAÇÃO            ║\n");
        printf("╚════════════════════════════════════════╝\n\n");
        printf("1 - Alugar veículo\n");
        printf("2 - Registros de locação\n");
        printf("3 - Voltar\n\n");
        printf("Selecione a opção desejada: ");
        scanf("%d", &opcao);
        
        switch(opcao) {
            case 1:
                alugar_veiculo();
                break;
            case 2:
                registro_locacao();
                break;
            case 3:
                voltar_locacao = 1;
                break;
            default:
                system("clear");
                printf("⚠️ Opção não existe!\n\n");
                getchar(); 
                getchar();
                break;
        }
    }
}
