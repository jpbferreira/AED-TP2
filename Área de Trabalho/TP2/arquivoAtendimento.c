#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    int nome;
    int id;
    int codAtendimento;
    int dataVisita;
    int removido;//0 nao foi removido, 1 foi removido
}Atendimento;

void CriaArquivo(char * nomeArquivo){

    printf("cria arquivo\n");

    FILE * arquivo = fopen(nomeArquivo, "a+b");
    
    int cab = 0;
    fwrite(&cab, sizeof(int), 1, arquivo);

    fclose(arquivo);

}

int AtualizaIndice(char * nomeArquivo){

    FILE * arquivo = fopen(nomeArquivo, "r+b");

    if(arquivo == NULL){
        printf("ERRO atualiza indice!\n");
        exit(0);
    }

    int indice;
    fseek(arquivo, 0, SEEK_SET);
    int numlidos = fread(&indice, sizeof(int), 1, arquivo);

    printf("indice: %d\n", indice);

    if(numlidos == 0){
        printf("erro leitura\n");
        exit(0);
    }
    
    indice++;

    fseek(arquivo, 0, SEEK_SET);
    fwrite(&indice, sizeof(int), 1, arquivo);

    fclose(arquivo);

    return indice;
}

int InserirFimArquivo(char * nomeArquivo){

    FILE * arquivo = fopen(nomeArquivo, "r+b");

    if(arquivo == NULL){
        CriaArquivo(nomeArquivo);
    }
    else{
        fclose(arquivo);
    }

    Atendimento a;
    a.codAtendimento = AtualizaIndice(nomeArquivo);

    arquivo = fopen(nomeArquivo, "a+b");

    if(arquivo == NULL){
        printf("ERRO inserir!\n");
        exit(0);
    }
    
    /*size_t tamstring = 0;
    char * nome;
    int tamnome = getline(&nome, &tamstring, stdin);
    nome[tamnome-1] = '\0';
    strcpy(a.nome, nome);*/

    scanf("%d", &(a.nome));

    scanf("%d %d", &(a.id), &(a.dataVisita));

    printf("id: %d\n", a.id);

    a.removido = 0;

    if(fwrite(&a, sizeof(Atendimento), 1, arquivo) != 1){
        printf("Erro fwrite!\n");
    }
        
    fclose(arquivo);

    return a.id;
}

void InsereArvore(char * nomeArquivo, struct ArvoreB * A){
    
    FILE * arquivo = fopen(nomeArquivo, "r+b");

    if(arquivo == NULL){
        printf("Arquivo não encontrado!\n");
    }
    else{
        int tam;
        fseek(arquivo, 0, SEEK_SET);
        int numlidos = fread(&tam, sizeof(int), 1, arquivo);

        int i;
        Atendimento a;
        fseek(arquivo, sizeof(int), SEEK_SET);

        for(i = 0; i < tam; i++){
            int numlidos = fread(&a, sizeof(Atendimento), 1, arquivo);
            if(numlidos == 0){
                printf("Erro na leitura!\n");
                exit(0);
            }

            if(a.removido == 0)
                Insere(A, a.id);
        
        }

    }
    
    fclose(arquivo);

}

void LeArquivo(char * nomeArquivo){

    FILE * arquivo = fopen(nomeArquivo, "r+b");

	if(arquivo == NULL)
	{
		printf("falha de abertura\n");
		exit(0);
	}

    int n;
    fread(&n, sizeof(int), 1, arquivo);
    printf("cab: %d\n", n);

    Atendimento a;

    fseek(arquivo, sizeof(int)+sizeof(Atendimento), SEEK_SET);
    int numlidos = fread(&a, sizeof(Atendimento), 1, arquivo);

    printf("numLidos: %d\n", numlidos);

    if(numlidos == 0){
        printf("Erro na leitura!\n");
        exit(0);
    }
         
    printf("chegou aqui!\n");

    printf("%d, %d, %d, %d, %d\n", a.nome, a.id, a.codAtendimento, a.dataVisita, a.removido);	

	fclose(arquivo);
}


void BuscaArquivo(char * nomeArquivo, int posicao){

    FILE * arquivo = fopen(nomeArquivo, "r+b");

	if(arquivo == NULL)
	{
		printf("falha de abertura\n");
		exit(0);
	}

    Atendimento a;

    fseek(arquivo, sizeof(int)+((posicao-1) * sizeof(Atendimento)), SEEK_SET);
    int numlidos = fread(&a, sizeof(Atendimento), 1, arquivo);

    if(numlidos == 0){
        printf("Erro na leitura!\n");
        exit(0);
    }

    printf("%d, %d, %d, %d, %d\n", a.nome, a.id, a.codAtendimento, a.dataVisita, a.removido);	

	fclose(arquivo);
}

void RemoveArquivo(char * nomeArquivo, int posicao){

    FILE * arquivo = fopen(nomeArquivo, "r+b");

	if(arquivo == NULL)
	{
		printf("falha de abertura\n");
		exit(0);
	}

    Atendimento a;

    fseek(arquivo, sizeof(int)+((posicao-1) * sizeof(Atendimento)), SEEK_SET);
    int numlidos = fread(&a, sizeof(Atendimento), 1, arquivo);

    if(numlidos == 0){
        printf("Erro na leitura!\n");
        exit(0);
    }

    a.removido = 1;

    fseek(arquivo, sizeof(int)+((posicao-1) * sizeof(Atendimento)), SEEK_SET);
    if(fwrite(&a, sizeof(Atendimento), 1, arquivo) == 1)
        printf("Removido\n");	

	fclose(arquivo);
}