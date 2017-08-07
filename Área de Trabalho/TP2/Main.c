#include <stdio.h>
#include <string.h>
#include "arquivoAtendimento.h"
#include "ArvoreB.h"

int main(){

    struct ArvoreB * I = CriaArvoreB();
    printf("Nome arquivo: ");
    char nomeArquivo[50];
    scanf("%s", nomeArquivo);
    getchar();

    InsereArvore(nomeArquivo, I);
    Imprime(I);
    while(1)
	{
		char comando[20];
		if(scanf("%s", comando) < 1 || strcmp(comando, "SAIR") == 0)
			break;	

		if(strcmp(comando, "INSERIR") == 0)
		{
            printf("Nome arquivo: ");
            char nomeArquivo[50];
            scanf("%s", nomeArquivo);
            getchar();
            int chave = InserirFimArquivo(nomeArquivo);
            Insere(I, chave);
		}
		else if(strcmp(comando, "BUSCAR") == 0)
		{
            printf("Nome arquivo: ");
            char nomeArquivo[50];
            scanf("%s", nomeArquivo);
            getchar();

			int c;
            printf("chave de busca:");
			scanf("%d", &c);

			int chave = Busca(I, c);
			if(chave != 1)
				printf("nao encontrado\n");
            else
                BuscaArquivo(nomeArquivo, c);
		}
		else if(strcmp(comando, "REMOVER") == 0)
		{
			printf("Nome arquivo: ");
            char nomeArquivo[50];
            scanf("%s", nomeArquivo);
            getchar();

			int c;
            printf("chave de busca:");
			scanf("%d", &c);

			int chave = Busca(I, c);
			if(chave != 1)
				printf("nao encontrado\n");
            else{
                RemoveArquivo(nomeArquivo, c);
                Remove(I, c);
            }
                
		}
    }

    return 0;
}