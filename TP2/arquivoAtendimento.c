#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    char nome[255];
    char id[20];
    int codAtendimento;
    char dataVisita[10];
    char descricao[255];
    int removido;//0 nao foi removido, 1 foi removido
}Atendimento;

//Função responsável por criar um arquivo
void CriaArquivo(char * nomeArquivo){

    FILE * arquivo = fopen(nomeArquivo, "a+b");
    
    //cabeçalho contendo o numero atual de registros no arquivo
    int cab = 0;
    fwrite(&cab, sizeof(int), 1, arquivo);

    fclose(arquivo);

}

//Função que atualiza o numero de registros no arquivo
int AtualizaIndice(char * nomeArquivo){

    FILE * arquivo = fopen(nomeArquivo, "r+b");

    if(arquivo == NULL){
        printf("ERRO atualiza indice!\n");
        exit(0);
    }

    int indice;
    fseek(arquivo, 0, SEEK_SET);
    int numlidos = fread(&indice, sizeof(int), 1, arquivo);

    if(numlidos == 0){
        printf("erro leitura!\n");
        exit(0);
    }
    
    indice++;

    fseek(arquivo, 0, SEEK_SET);
    fwrite(&indice, sizeof(int), 1, arquivo);

    fclose(arquivo);

    return indice;
}

// Função responsavel por inserir um registro(Atendimento) no fim arquivo
int InserirFimArquivo(char * nomeArquivo){

    //Tenta abrir o arquivo
    FILE * arquivo = fopen(nomeArquivo, "r+b");

    //Se não exitir, cria um arquivo
    if(arquivo == NULL){
        CriaArquivo(nomeArquivo);
    }
    else{
        fclose(arquivo);
    }

    Atendimento a;
    //O codigo do atendimento tem o mesmo valor da posição relativa do registro no arquivo
    a.codAtendimento = AtualizaIndice(nomeArquivo);

    arquivo = fopen(nomeArquivo, "a+b");

    if(arquivo == NULL){
        printf("ERRO inserir!\n");
        exit(0);
    }
    
    //-----------Le os dados do atendimento--------------------------
    getchar();
    printf("Cod Atendimento: %d\n", a.codAtendimento);
    printf("Nome do paciente: ");
    fgets(a.nome, sizeof(a.nome), stdin);

    printf("ID: ");
    scanf("%s", a.id);
    getchar();

    printf("Data da visita: ");
    scanf("%s", a.dataVisita);
    getchar();

    printf("Descricao: ");
    fgets(a.descricao, sizeof(a.descricao), stdin);
    //-----------------------------------------------------------------

    //marca o registro como não removido
    a.removido = 0;

    if(fwrite(&a, sizeof(Atendimento), 1, arquivo) != 1){
        printf("Erro ao escrever no arquivo!\n");
    }
        
    fclose(arquivo);

    //o codigo do atendimento/posicao relativa no arquivo
    return a.codAtendimento;
}

//Função responsável por inserir os cod atendimentos dos registros marcados como não removidos na arvore
void InsereArvore(char * nomeArquivo, struct ArvoreB * A){
    
    FILE * arquivo = fopen(nomeArquivo, "r+b");

    if(arquivo == NULL){
        printf("Arquivo não encontrado!\n");
        return;
    }
    else{
        int tam;
        fseek(arquivo, 0, SEEK_SET);
        fread(&tam, sizeof(int), 1, arquivo);

        int i;
        Atendimento a;
        fseek(arquivo, sizeof(int), SEEK_SET);

        for(i = 0; i < tam; i++){
            int numlidos = fread(&a, sizeof(Atendimento), 1, arquivo);
            if(numlidos == 0){
                printf("Erro na leitura!\n");
                exit(0);
            }

            //Se o registro estiver marcado como não removido, insere na arvore
            if(a.removido == 0)
                Insere(A, a.codAtendimento);
        
        }

    }
    
    fclose(arquivo);

}

//Função responsável por buscar um registro no arquivo dada sua posição relativa no arquivo
void BuscaArquivo(char * nomeArquivo, int posicao){

    FILE * arquivo = fopen(nomeArquivo, "r+b");

	if(arquivo == NULL)
	{
		printf("falha de abertura\n");
		exit(0);
	}

    Atendimento a;

    //posiciona a cabeça de leitura na posição sobre o registro a ser lido
    fseek(arquivo, sizeof(int)+((posicao-1) * sizeof(Atendimento)), SEEK_SET);
    int numlidos = fread(&a, sizeof(Atendimento), 1, arquivo);

    //Se falhar a leitura, mensagem de erro
    if(numlidos == 0){
        printf("Erro na leitura!\n");
        exit(0);
    }

    //Imprime os dados contidos no registro buscado
    printf("------------------Informacoes do Atendimento----------------------\n");
    printf("Nome: %s", a.nome);
    printf("ID: %s\n", a.id);
    printf("Cod. Atendimento: %d\n", a.codAtendimento);	
    printf("Data visita: %s\n", a.dataVisita);
    printf("Descricao: %s", a.descricao);

	fclose(arquivo);
}

//Função responsavel por marcar como removido um registro a ser removido
void RemoveArquivo(char * nomeArquivo, int posicao){

    FILE * arquivo = fopen(nomeArquivo, "r+b");

	if(arquivo == NULL)
	{
		printf("falha de abertura\n");
		exit(0);
	}

    Atendimento a;

    //posiciona a cabeça de leitura na posição sobre o registro a ser 'removido'
    fseek(arquivo, sizeof(int)+((posicao-1) * sizeof(Atendimento)), SEEK_SET);
    int numlidos = fread(&a, sizeof(Atendimento), 1, arquivo);

    if(numlidos == 0){
        printf("Erro na leitura!\n");
        exit(0);
    }

    //marca o registro como removido
    a.removido = 1;

    fseek(arquivo, sizeof(int)+((posicao-1) * sizeof(Atendimento)), SEEK_SET);
    //escreve o registro atualizado de volta no arquivo
    if(fwrite(&a, sizeof(Atendimento), 1, arquivo) == 1)
        printf("Atendimento removido!\n");	

	fclose(arquivo);
}
