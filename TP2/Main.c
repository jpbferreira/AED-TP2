#include <stdio.h>
#include <string.h>
#include "arquivoAtendimento.h"
#include "ArvoreB.h"

int main(){

    //Cria a árvore que armazenará o codigo dos atendimentos
    struct ArvoreB * I = CriaArvoreB();
    printf("Nome arquivo: ");//Nome do arquivo onde serão armazenados os registros com os atendimentos
    char nomeArquivo[50];
    scanf("%s", nomeArquivo);
    getchar();

    //tenta abrir o arquivo
    FILE * arquivo = fopen(nomeArquivo, "r+b");

    //Se o arquivo já existir
    if(arquivo != NULL){
        //Insere o codigo dos atendimentos marcados como não removidos na árvore
        InsereArvore(nomeArquivo, I);
        fclose(arquivo);    
    }
    
    while(1)
	{
        printf("\nOPCOES: CADASTRO - BUSCA - REMOCAO - SAIR\n\n");
		char comando[20];
		if(scanf("%s", comando) < 1 || strcmp(comando, "SAIR") == 0)
			break;	

		if(strcmp(comando, "CADASTRO") == 0)
		{
            printf("------------------Cadastro de um novo atendimento------------------\n");
            //Insere o registro no fim do arquivo
            int chave = InserirFimArquivo(nomeArquivo);
            //Insere o codigo do atendimento na arvore
            Insere(I, chave);
		}
		else if(strcmp(comando, "BUSCA") == 0)
		{
            printf("------------------Buscar pelo codigo do atendimento------------------\n");
			int c;
            printf("Codigo de atendimento: ");
			scanf("%d", &c);

            //Busca na arvore a posicao relativa do atendimento 
            // com o cod. atendimento inserido pelo usuario
			int chave = Busca(I, c);
			if(chave != 1)
				printf("Atendimento nao encontrado!\n");
            else
                BuscaArquivo(nomeArquivo, c);
		}
		else if(strcmp(comando, "REMOCAO") == 0)
		{
            printf("----------------Remocao de Atendimento-----------------\n");
			int c;
            printf("Codigo do atendimento: ");
			scanf("%d", &c);

            //Busca na arvore a posicao relativa do atendimento 
            // com o cod. atendimento inserido pelo usuario
			int chave = Busca(I, c);
			if(chave != 1)
				printf("Atendimento nao encontrado!\n");
            //Se encontrar marca o registro no arquivo como removido e remove o cod. atendimento da arvore
            else{
                RemoveArquivo(nomeArquivo, c);
                Remove(I, c);
            }
                
		}
    }

    return 0;
}