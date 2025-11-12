#include <stdio.h>
#include <stdlib.h>
#include "sistema.h"
#include <string.h>
#include <ctype.h>
#include <time.h>

void verificar_atrasos()
{
    FILE *arquivo = fopen("relatorios.bin", "r+b");
    if(!arquivo)
    {
        printf("❌ Erro ao abrir arquivo de locações.\n");
        return;
    }

    Locacao loc;
    time_t t = time(NULL);
    struct tm *hoje = localtime(&t);

    char data_hoje[11];
    strftime(data_hoje, 11, "%d/%m/%Y", hoje);

    int dia_atual, mes_atual, ano_atual;
    sscanf(data_hoje, "%d/%d/%d", &dia_atual, &mes_atual, &ano_atual);

    while(fread(&loc, sizeof(Locacao), 1, arquivo)){
        int dia_dev, mes_dev, ano_dev;
        sscanf(loc.data_devolucao, "%d/%d/%d", &dia_dev, &mes_dev, &ano_dev);

        if(ano_atual > ano_dev ||(ano_atual == ano_dev && mes_atual > mes_dev) ||
           (ano_atual == ano_dev && mes_atual == mes_dev && dia_atual > dia_dev)){
            
            if(loc.entregue_no_prazo == 1)
            {
                loc.entregue_no_prazo = 0;
                fseek(arquivo, -sizeof(Locacao), SEEK_CUR);
                fwrite(&loc, sizeof(Locacao), 1, arquivo);
            }
        }
    }
    fclose(arquivo);
}

int validarCategoriaCNH(const char* categoria)
{
	const char* categorias_validas[] = {"A", "B", "C", "D", "E", "AB"};
	int num_categorias = 6;

	for(int i = 0; i < num_categorias; i++) {
		if(strcmp(categoria, categorias_validas[i]) == 0) {
			return 1;
		}
	}
	return 0;
}

int validarPlaca(char placa[])
{
	if(strlen(placa) != 7) {
		return 0;
	}
	for(int i = 0; i < 7; i++) {
		if(i < 3 || i == 4) {
			if(!isalpha(placa[i])) return 0;
		} else {
			if(!isdigit(placa[i])) return 0;
		}
	}
	return 1;
}

int validarCNH(char cnh[])
{
    if(strlen(cnh) != 11)
    {
        return 0;
    }
    
    for(int i = 0; i < 11; i++){
        if(!isdigit(cnh[i]))
        {
            return 0;
        }
    }
    
    return 1;
}

int validarCPF(char cpf[])
{
    int i, j;
    int digito1 = 0, digito2 = 0;
    
    if (strlen(cpf) != 11)
    {
        return 0;
    }
    
    for(i = 0; i < 11; i++){
        if(!isdigit(cpf[i]))
        {
            return 0;
        }
    }
    
    int todos_iguais = 1;
    for(i = 1; i < 11; i++){
        if(cpf[i] != cpf[0])
        {
            todos_iguais = 0;
            break;
        }
    }
    if(todos_iguais)
    {
        return 0;
    }
    
    for(i = 0, j = 10; i < 9; i++, j--){
        digito1 += (cpf[i] - '0') * j;
    }
    digito1 %= 11;
    digito1 = (digito1 < 2) ? 0 : 11 - digito1;
    
    if(digito1 != (cpf[9] - '0'))
    {
        return 0;
    }
    
    for(i = 0, j = 11; i < 10; i++, j--){
        digito2 += (cpf[i] - '0') * j;
    }
    digito2 %= 11;
    digito2 = (digito2 < 2) ? 0 : 11 - digito2;
    
    if(digito2 != (cpf[10] - '0'))
    {
        return 0;
    }
    
    return 1;
}

int validarCompatibilidadeCategoria(const char* categoria_cliente, const char* categoria_veiculo)
{
    if(strcmp(categoria_cliente, "AB") == 0) {
        return (strcmp(categoria_veiculo, "A") == 0 || 
                strcmp(categoria_veiculo, "B") == 0 ||
                strcmp(categoria_veiculo, "AB") == 0);
    }
    return (strcmp(categoria_cliente, categoria_veiculo) == 0);
}

void verificar_tamanho_struct() {
    printf("Tamanho da struct Cliente: %zu bytes\n", sizeof(Cliente));
    printf("Tamanho esperado: ~142 bytes\n");
}

void menu()
{
	int opcao;

	do {
		system("clear");
		printf("Sistema de Gerenciamento de Aluguel de Carros\n\n1. Area de cadastro\n\n2. Area de consulta\n\n3. Area de locacao\n\n4. Encerrar\n");
		printf("\nSelecione a opcao desejada: ");
		scanf("%d", &opcao);

		switch(opcao) {
		case 1: {
			area_cadastro();
			break;
		}

		case 2: {
			area_consulta();
			break;
		}

		case 3: {
			area_locacao();
			break;
		}

		case 4: {
			system("clear");
			printf("Encerrando sistema...\n");
			break;
		}

		default: {
			system("clear");
			printf("Opcao nao existe!\n\n");
			getchar();
			getchar();
			break;
		}
		}
	} while(opcao != 4);

	return;
}
