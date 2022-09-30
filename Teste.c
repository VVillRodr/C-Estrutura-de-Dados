#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#define TAMANHO 30
#define CLOCKS_PER_SEC 1000
typedef struct ENCPessoa{
    char nome[TAMANHO];
    char rg[TAMANHO];
}ENCPessoa;

typedef struct No{
    ENCPessoa* dados;
    struct No *prox, *ant;

}No;

typedef struct ENCLista {
    No *first,*last; //duplamente encadeada

}ENCLista;

typedef struct SPessoa{
    char nome[TAMANHO], rg[TAMANHO];
}Sessoa;

typedef struct Lista{
    Sessoa** p;
    int tamanho;
}Lista;


void ENCpesquisaSequencial(ENCLista *listaenc){
    No *aux;
    int posicao = 0;
    int Mn = 0, Cn = 0;
    int sinalizador = 0;
    char rgPesquisado[TAMANHO];
    aux = listaenc->first; //aux recebe o primeiro no da lista que ja criamos

    printf("\n   DIGITE O RG QUE VAI SER PESQUISADO:   ");
    scanf("%s",rgPesquisado);
    Cn++;
    while (aux !=NULL && sinalizador !=1){ //essa é uma estrutura padrao pra percorrer à lista pelos ponteiros, usamos a mesma estrutura para imprimir a lista

        posicao++;
        if(strcmp(rgPesquisado,aux->dados->rg)!= 0){ //compara duas strings, caracter por caracter

            aux = aux->prox;//acesso pelos ponteiros
            Mn++;
            Cn++;

        }
        else{

            printf("\n   O RG %s FOI ENCONTRADO!!\n   O NOME ASSOCIADO E: ||  %s  || ",rgPesquisado,aux->dados->nome);
            printf("\n   ELE ESTA NA POSICAO %d DA LISTA \n",posicao);
            sinalizador = 1;

        }
        Cn++;

    }
    if (sinalizador == 0)
            printf("\n  RG NAO ENCONTRADO, TENTE NOVAMENTE!\n   VOCE SERA REDIRECIONADO AO MENU\n");

    printf("C(n): %d\n", Cn);
    printf("M(n): %d\n", Mn);


}

void ENCimprimeLista(ENCLista *listaenc){
    No *aux;
    aux = listaenc->first;
    int Cn = 0, Mn = 0;
    Cn++;
    while (aux != NULL){
        printf("| Nome: %s || RG: %s |\n", aux->dados->nome, aux->dados->rg);
        aux = aux->prox;
        Cn++;

    }
    printf("C(n): %d\n", Cn);
    printf("M(n): %d\n", Mn);
}

ENCLista *ENCcriaLista(char nomearquivo[]){
    FILE *arquivo;
    char line[TAMANHO];
    char *nome;
    char *rg;
    int Cn = 0, Mn = 0;
    No *aux , *no;
    ENCPessoa *dados;
    ENCLista *listaenc;

    listaenc = (ENCLista *)malloc(sizeof(ENCLista));

    no = (No*) malloc(sizeof(No));

    listaenc->first = no;
    Mn++;
    no->ant = NULL;
    Mn++;

    aux = no;
    Mn++;

    arquivo = fopen(nomearquivo,"rt");
    Cn++;
    if (arquivo == NULL){
        printf("Erro ao abrir o arquivo!");
        getchar();
        exit(1);
    }
    Cn++;
    while(!feof(arquivo)){
        Cn++;
        if (fgets(line, TAMANHO, arquivo) == NULL)
        {
            printf("ERRO AO LER O ARQUIVO!");
            getchar();
            exit(1);
        }
        nome = strtok(line,",");
        rg = strtok(NULL, "\n");

        dados = (ENCPessoa *)malloc(sizeof(ENCPessoa));

        strcpy(dados->nome,nome);
        strcpy(dados->rg, rg);

        aux->dados = dados;

        if (!feof(arquivo)){
            Cn++;
            aux->prox = (No *)malloc(sizeof(No));
            if (aux->prox == NULL){
                printf("ERRO");
                exit(1);
            }
            aux->prox->ant = aux;
            Mn++; //anterior ao proximo esta referenciando o aux atual
            aux = aux->prox;
            Mn++; // atual esta referenciando o proximo
        }

        aux->prox = NULL; //proximo esta referenciando NULL, pois será o ultimo da lista
        Mn++;
    }
    listaenc->last = aux; //Ponteiro pegando o ultimo No
    Mn++;
    printf("C(n) da Encadeada: %d\n", Cn);
    printf("M(n) da Encadeada: %d\n", Mn);

    return listaenc;

}

void ENCinserirNoInicio(ENCLista *listaenc){
    No *novo;
    int Cn = 0, Mn = 0;
    char novoNome[TAMANHO], novoRg[TAMANHO];

    novo = (No *)malloc(sizeof(No));
    novo->dados = (ENCPessoa *) malloc(sizeof(ENCPessoa));

    strcpy(novo->dados->nome, "");//inicializando nome e rg
    strcpy(novo->dados->rg, "");

    novo->ant = NULL;
    Mn++;          //como a inserçao vai ser no início, não vai ter nada anterior ào que vamos inserir
    novo->prox = listaenc->first;
    Mn++;    //o que vai ser refetenciado no próximo do novo elemento é o primeiro elemento da lista que ja foi criada
    listaenc->first->ant = NULL;
    Mn++;   // o elemento anterior ao primeiro elemento não vai ser mais nulo e vai passar a ser o novo que vamos inserir
    listaenc->first = novo;
    Mn++;      // agora, o primeiro elemento passa a ser o novo  e ele ja está apontando para o antigo primeiro elemento

    printf("  INFORME O NOME: ");   //estrai o nome e o rg e passa para o novo que esta passando para a lista
    scanf("%s", novoNome);
    strcpy(novo->dados->nome, novoNome);

    printf("  INFORME O RG: ");
    scanf("%s", novoRg);
    strcpy(novo->dados->rg, novoRg);

    printf("C(n): %d\n", Cn);
    printf("M(n): %d\n", Mn);


}

void ENCinserirNoFinal(ENCLista *listaenc){

    No *novo;
    int Cn = 0, Mn = 0;
    char novoNome[TAMANHO], novoRg[TAMANHO];
    novo = (No *)malloc(sizeof(No));
    novo->dados = (ENCPessoa *) malloc(sizeof(ENCPessoa));

    if (novo == NULL)
    {
        printf("ERRO!");
        getchar();
        exit(1);
    }

    strcpy(novo->dados->nome, "");//inicializando nome e rg
    strcpy(novo->dados->rg, "");

    novo->prox = NULL;
    Mn++;                           //Como novo está sendo inserido no final da lista, ele não vai apontar para um novo elemento
    novo->ant = listaenc->last;
    Mn++;                          //O anterior ao elemento que vamos inserir é o ultimo elemento da lista que já criamos
    listaenc->last->prox = novo;
    Mn++;                         //o proximo ao ultimo elemento da lista ja criada vai ser o novo que criamos

    printf("  Informe o Nome: "); //estrai o nome e o rg e passa para o novo que esta passando para a lista
    scanf("%s", novoNome);
    strcpy(novo->dados->nome, novoNome);

    printf("  Informe o RG: ");
    scanf("%s", novoRg);
    strcpy(novo->dados->rg, novoRg);

    printf("C(n): %d\n", Cn);
    printf("M(n): %d\n", Mn);


}

void ENCinserirNaPosicao(ENCLista *listaenc){
    int i, n;
    int Cn = 0, Mn = 0;
    No *novo, *aux_ant, *aux_pos;
    char nnome[TAMANHO], nrg[TAMANHO];

    aux_ant = listaenc->first;

    novo = (No *)malloc(sizeof(No));
    novo->dados = (ENCPessoa *)malloc(sizeof(ENCPessoa));
    Cn++;
    if (novo == NULL)
    {
        printf("ERRO!");
        exit(1);
    }

    strcpy(novo->dados->nome, "");
    strcpy(novo->dados->rg, "");

    printf("\n   INFORME A POSICAO DA INSERCAO: ");
    scanf("%d", &n);


    for (i = 0; i < n - 2; i++) //vai percorrer até o local que iremos inserir
    {
        Cn++;
        aux_ant = aux_ant->prox;
        Mn++;

        if (aux_ant == NULL)
        {
            printf("informe uma posicao valida!");
            exit(1);
        }
    }
    aux_pos = aux_ant->prox;  //AUX POS VAI RECEBER O PROXIMO DO ANTERIOR
    Mn++;
    aux_ant->prox = novo;  //A ANTIGA POSICAO DO PROXIMO VAI RECEBER O NOVO                          ESQUEMA DO QUE ESTA SENDO FEITO
    Mn++;
    novo->ant = aux_ant;   //ANTERIOR DO NOVO VAI REFERENCIAR O QUE JA ESTAVA EM AUX ANT      //    | ANT  |--> | NOVO |--> | PROX |
    Mn++;                                                                                    //     |      |<-- |      |<-- |      |
    novo->prox = aux_pos; //O PROXIMO DO NOVO VAI REFERENCIAR VAI REFERENCIAR O AUX PROXIMO
    Mn++;
    aux_pos->ant = novo;  //O ANTERIOR DO AUX PROXIMO VAI REFERENCIAR O NOVO
    Mn++;

    printf("\n   INFORME O NOME: ");
    scanf("%s", nnome);
    strcpy(novo->dados->nome, nnome);

    printf("\n   INFORME O RG: ");
    scanf("%s", nrg);
    strcpy(novo->dados->rg, nrg);

    printf("C(n): %d\n", Cn);
    printf("M(n): %d\n", Mn);

}

void ENCremoverDoInicio(ENCLista *listaenc){
    int Cn = 0, Mn = 0;
    No *aux;
    aux = listaenc->first; //AUX VAI RECEBER O PRIMEIRO ELEMENTO DA LISTA
    Mn++;
    listaenc->first = listaenc->first->prox; //O PRIMEIRO ELEMENTO DA LISTA VAI PASSAR SER O SEGUNDO, POIS O PRIMEIRO VAI SER REMOVIDO
    Mn++;
    listaenc->first->ant = NULL; // A REFERENCIA DO ELEMENTO QUE ESTAVA EM SEGUNDO VAI PASSAR A SER NULA, POIS ELE ESTA NO INICIO, AGORA
    Mn++;
    free(aux->dados);
    free(aux);

    printf("C(n): %d\n", Cn);
    printf("M(n): %d\n", Mn);


}

void ENCremoverDoFinal (ENCLista *listaenc){
    int Cn = 0, Mn = 0;

    No *aux = listaenc->last; //aux recebe  o ultimo elemento da lista

    listaenc->last = listaenc->last->ant; //o ultimo elemento vai receber o que estava anterior à ele
    Mn++;
    listaenc->last->prox = NULL; //o novo ultimo elemento, nao vai apontar para nada no proximo
    Mn++;
    free(aux->dados);
    free(aux);

    printf("C(n): %d\n", Cn);
    printf("M(n): %d\n", Mn);


}

void ENCremoverNaPosicao(ENCLista *listaenc){

    No *aux = listaenc->first;
    int i, posicao;
    int Cn = 0, Mn = 0;
    printf("\n   INFORME UMA POSICAO:\n");
    scanf("%d", &posicao);
    printf("111");
    Cn++;
    for (i = 0; i < posicao - 1; i++)
    {

        Mn++;
        Cn++;
        aux = aux->prox;//percorre pelos ponteiros ate a posiçao

    }

    aux->ant->prox = aux->prox;

    Mn++;

    free(aux->dados);
    free(aux);

    printf("C(n): %d\n", Cn);
    printf("M(n): %d\n", Mn);


}

void ENCcriaArquivo(ENCLista *listaenc){

    FILE *arq;
    No *aux;

    char novoarq[50];

    aux = listaenc->first;

    printf("\nINSIRA O NOME DO ARQUIVO:\n");
    scanf("%s", &novoarq);

    arq = fopen(novoarq, "w+");

    if (arq == NULL){
        printf("ERRO AO ABRIR O ARQUIVO!");
        getchar();
        exit(1);
    }
    while (aux != NULL)   //Vamos percorrer a lista pelos ponteiros e usar o fprint para jogar no arquivo que criamos
    {
        if (aux->prox == NULL){
            fprintf(arq, "%s,%s", aux->dados->nome, aux->dados->rg);
        }
        else
        {
            fprintf(arq, "%s,%s\n", aux->dados->nome, aux->dados->rg);
        }
        aux = aux->prox;
    }
    fclose(arq);



}

void ENCdesaloca(ENCLista *listaenc){
    No *aux_pro, *aux_a;

    aux_a = listaenc->first;
    while (aux_a != NULL)
    {
        aux_pro = aux_a->prox;
        free(aux_a->dados);
        free(aux_a);
        aux_a = aux_pro;
    }
}

int tamlista(char fileName[]){
    FILE *arq;
    int i = 0;
    char line[50];
    char *result;

    arq = fopen(fileName, "rt");

    if (arq == NULL)
    {
        printf("Erro ao abrir o arquivo!");
        getchar();
        exit(1);
    }

    while (!feof(arq))
    {
        if (fgets(line, TAMANHO, arq) != NULL)
        {
            i++;
        }
    }

    fclose(arq);

    return i;
}

Sessoa **SEQalocaLista(int tam){
    Sessoa **p;

    p = (Sessoa **)malloc(tam * sizeof(Sessoa *));

    if (p == NULL)
    {
        printf("Erro na alocação!");
        getchar();
        exit(1);
    }

    return p;
}

void SEQcriaLista(char fileName[], Lista *lista){
    FILE *arq;
    int i;
    char line[TAMANHO];
    char *nome, *rg;

    arq = fopen(fileName, "rt");

    if (arq == NULL)
    {
        printf("Erro ao abrir o arquivo!");
        getchar();
        exit(1);
    }

    for (i = 0; i < (lista->tamanho); i++)
    {
        if (fgets(line, TAMANHO, arq) == NULL)
        { // lê toda a lista e coloca em line
            printf("ERRO AO LER O ARQUIVO!");
            getchar();
            exit(1);
        }

        nome = strtok(line, ","); // atribui à nome tudo antes da vigula
        rg = strtok(NULL, "\n");  // atribui à rg tudo depois da virgula

        lista->p[i] = (Sessoa *)malloc(sizeof(Sessoa)); // aloca o espaço para Sessoa no espaço correspondente no vetor de ponteiros

        strcpy(lista->p[i]->nome, nome); // copia os dados para os espaços da struct
        strcpy(lista->p[i]->rg, rg);

        if (nome == NULL || rg == NULL)
        {
            printf("ERRO EM %d", (i + 1));
            exit(1);
        }
    }

    fclose(arq);
}

void SEQdesaloca(Lista *lista){
    int i;
    int Cn = 0, Mn = 0;
    for (i = 0; i < lista->tamanho; i++)
    {
        Cn++;
        free(lista->p[i]);
    }

    free(lista->p);
    printf("C(n): %d\n", Cn);
    printf("M(n): %d\n", Mn);
}

void SEQimprimeLista(Lista *lista){
    int i;
    int Cn = 0, Mn = 0;
    for (i = 0; i < lista->tamanho; i++)
    {
        Cn++;
        printf("|  %s  |  %s  |\n", lista->p[i]->nome, lista->p[i]->rg);
    }
    printf("C(n): %d\n", Cn);
    printf("M(n): %d\n", Mn);
}

void SEQnonoinicio(Lista *lista){
    int Cn = 0, Mn = 0;
    char nnome[TAMANHO] = "", nrg[TAMANHO] = "";
    lista->p = (Sessoa **)realloc(lista->p, sizeof(Sessoa *) * (lista->tamanho + 1));
    //vamos realocar espaço para a mesma lista so que com um espaço à mais para os dados que vamos inserir

    if (lista->p == NULL)
    {
        printf("Erro na alocação!");
        getchar();
        exit(1);
    }
    for (int i = (lista->tamanho); i > 0; i--) //estamos movendo todos os elementos de lugar
    {
        lista->p[i] = lista->p[i - 1];
        Mn++;
    }
    printf("\nInsira nome:");
    scanf("%s", nnome);
    getchar();
    printf("\nInsira rg:");
    scanf("%s", nrg);
    getchar();

    Sessoa *pessoa = (Sessoa *)malloc(sizeof(Sessoa));

    if (pessoa == NULL)
    {
        printf("Erro na alocação!");
        getchar();
        exit(1);
    }

    strcpy(pessoa->nome, nnome); // copia os dados para os espaços da struct

    strcpy(pessoa->rg, nrg);

    lista->p[0] = pessoa; // o novo primeiro elemento vai receber os novos dados

    lista->tamanho++;

    printf("C(n): %d\n", Cn);
    printf("M(n): %d\n", Mn);
}

void SEQnonofinal(Lista *lista){
    int Cn = 0, Mn = 0;
    char nnome[TAMANHO] = "", nrg[TAMANHO] = "";
    lista->p = (Sessoa **)realloc(lista->p, sizeof(Sessoa *) * (lista->tamanho + 1));
    //vamos realocar espaço para a mesma lista so que com um espaço à mais para os dados que vamos inserir
    if (lista->p == NULL)
    {
        printf("Erro na alocação!");
        getchar();
        exit(1);
    }
    printf("\n  INSIRA UM NOME:");
    scanf("%s", nnome);
    getchar();
    printf("\n   INSIRA UM NOME:");
    scanf("%s", nrg);
    getchar();

    Sessoa *pessoa = (Sessoa *)malloc(sizeof(Sessoa));

    if (pessoa == NULL)
    {
        printf("Erro na alocação!");
        getchar();
        exit(1);
    }

    strcpy(pessoa->nome, nnome); // copia os dados para os espaços da struct

    strcpy(pessoa->rg, nrg);

    lista->p[lista->tamanho] = pessoa;

    lista->tamanho++;
    printf("C(n): %d\n", Cn);
    printf("M(n): %d\n", Mn);
}

void SEQnonopos(Lista *lista){
    int n, Cn = 0, Mn = 0;
    char nnome[TAMANHO] = "", nrg[TAMANHO] = "";
    lista->p = (Sessoa **)realloc(lista->p, sizeof(Sessoa *) * (lista->tamanho + 1));

    do
    {
        printf("\nInsira a posicao desejada, entre 1 e %d\n", (lista->tamanho));
        scanf("%d", &n);
    } while ((n > ((lista->tamanho)-1)) || (n < 0));
    n = n - 1;

    if (lista->p == NULL)
    {
        printf("Erro na alocação!");
        getchar();
        exit(1);
    }
    for (int i = lista->tamanho; i > n; i--)
    {
        lista->p[i] = lista->p[i - 1];
        Mn++;
    }
    printf("\nInsira nome:");
    scanf("%s", nnome);
    getchar();
    printf("\nInsira rg:");
    scanf("%s", nrg);
    getchar();

    Sessoa *pessoa = (Sessoa *)malloc(sizeof(Sessoa));

    if (pessoa == NULL)
    {
        printf("Erro na alocação!");
        getchar();
        exit(1);
    }

    strcpy(pessoa->nome, nnome); // copia os dados para os espaços da struct

    strcpy(pessoa->rg, nrg);

    lista->p[n] = pessoa;

    lista->tamanho++;
    printf("C(n): %d\n", Cn);
    printf("M(n): %d\n", Mn);
}

void SEQremnonoinicio(Lista *lista){
    int i, Cn = 0, Mn = 0;

    free(lista->p[0]);

    for (int i = 0; i < ((lista->tamanho) - 1); i++) //esta trazendo todos elementos seguintes ao primeiro para uma posiçao anterior
    {
        lista->p[i] = lista->p[i + 1];
        Mn++;
    }
    (lista->tamanho)--;
    lista->p = (Sessoa **)realloc(lista->p, (lista->tamanho) * sizeof(Sessoa));
    printf("C(n): %d\n", Cn);
    printf("M(n): %d\n", Mn);
}

void SEQremnonofinal(Lista *lista){
    int Cn=0, Mn=0;

    free(lista->p[(lista->tamanho - 1)]); //-1 por que a primeira posiçao é 0
    (lista->tamanho)--;
    lista->p = (Sessoa **)realloc(lista->p, (lista->tamanho) * sizeof(Sessoa));
    printf("C(n): %d\n", Cn);
    printf("M(n): %d\n", Mn);
}

void SEQremnonopos(Lista *lista){
    int i, n,Cn=0,Mn=0;
    do
    {
        printf("\nInsira a posicao desejada, entre 1 e %d\n", (lista->tamanho));
        scanf("%d", &n);
    } while ((n > (lista->tamanho)) || (n < 0));
    n = n - 1;

    free(lista->p[n]);Cn++;//ps

    for (i = n; i < ((lista->tamanho) - 1); i++)
    {
        lista->p[i] = lista->p[i + 1];
        Mn++;
    }
    printf("C(n): %d\n", Cn);
    printf("M(n): %d\n", Mn);
    (lista->tamanho)--;
    lista->p = (Sessoa **)realloc(lista->p, (lista->tamanho) * sizeof(Sessoa));

}

void SEQbuscarg(Lista *lista){

    int i, achou = 0, Cn=0,Mn=0;
    char rgg[TAMANHO];
    printf("Insira o RG de quem deseja procurar: ");
    scanf("%s", rgg);
    Cn++;
    for (i = 0; i < lista->tamanho && achou != 1; i++)
    {
        if (strcmp(lista->p[i]->rg, rgg) == 0)
        {
            Cn++;
            achou = 1;
            printf("\n   O RG %s FOI ENCONTRADO!!\n    NOME ASSOCIADO : ||  %s  || ",rgg,lista->p[i]->nome);
            printf("\n   ELE ESTA NA POSICAO %d DA LISTA \n",i+1);
        }
        Cn++;
    }
    if (achou == 0)
    {
        Cn++;
        printf("RG não encontrado!");
    }
    printf("C(n): %d\n", Cn);
    printf("M(n): %d\n", Mn);
}

void SEQcriaarquivo(Lista *lista){
    FILE *arq;
    int i = 0;
    char novoarq[50];
    printf("\nInsira o nome do novo arquivo:\n");
    scanf("%s", novoarq);
    arq = fopen(novoarq, "w+");

    if (arq == NULL)
    {
        printf("Erro ao abrir o arquivo!");
        getchar();
        exit(1);
    }
    for (i = 0; i < ((lista->tamanho) - 1); i++)
    {
        if (i == ((lista->tamanho) - 1) - 1)
        {
            fprintf(arq, "%s,%s", lista->p[i]->nome, lista->p[i]->rg);
        }
        else
        {
            fprintf(arq, "%s,%s\n", lista->p[i]->nome, lista->p[i]->rg);
        }
    }
    fclose(arq);
}

int main(){

    ENCLista *listaenc;
    Lista lista;
    char nomearquivo[TAMANHO];
    int el, es, ee, ea;
    clock_t ini, fim;
    double timeE, timeS;


    printf("   DIGITE O NOME DO ARQUIVO:  ");
    scanf("%s",nomearquivo);
    ini = clock();
    listaenc = ENCcriaLista(nomearquivo);
    lista.tamanho = tamlista(nomearquivo);
    lista.p = SEQalocaLista(lista.tamanho);
    fim = clock();
    timeS = ((double)(fim - ini)) / CLOCKS_PER_SEC;
    printf("Tempo de Criacao da Lista S: %f\n", timeS);
    ini = clock();
    SEQcriaLista(nomearquivo, &lista);
    fim = clock();
    timeE = ((double)(fim - ini)) / CLOCKS_PER_SEC;
    printf("Tempo de Criacao da Lista E: %f\n", timeE);

    printf("\n   ARQUIIVO CARREGADO");

    do
    {
        printf("\n\t|1- Inserir no inicio da lista|\n\t|2-inserir no no fim da lista|\n\t|3-inserir no na posicao N|");
        printf("\n\t|4-retirar no do inicio da lista|\n\t|5-retirar no do fim da lista|\n\t|6-retirar no da posicao N|\n\t|7-Procurar no por RG|");
        printf("\n\t|8-Imprimir Lista|\n\t|9-Salvar a lista em um arquivo\n\t|10-Ler a lista de um arquivo|\n\t|11-Sair|\n\tR: ");



        scanf("%d", &ee);
        switch (ee)
        {
        case 1:
            ini = clock();
            printf("\n   LISTA SEQUENCIAL:\n");
            SEQnonoinicio(&lista);
            fim = clock();
            timeS = ((double)(fim - ini)) / CLOCKS_PER_SEC;

            ini = clock();
            printf("\n   LISTA ENCADEADA:\n");
            ini = clock();
            ENCinserirNoInicio(listaenc);
            fim = clock();
            timeE = ((double)(fim - ini)) / CLOCKS_PER_SEC;

            printf("Tempo de execucao E: %f\n", timeE);
            printf("Tempo de execucao S: %f\n", timeS);

            break;
        case 2:
            printf("\nLista Sequencial:\n");
            ini = clock();
            SEQnonofinal(&lista);
            fim = clock();
            timeS = ((double)(fim - ini)) / CLOCKS_PER_SEC;

            printf("\nLista Encadeada:\n");
            ini = clock();
            ENCinserirNoFinal(listaenc);
            fim = clock();
            timeE = ((double)(fim - ini)) / CLOCKS_PER_SEC;
            printf("Tempo de execucao E: %f\n", timeE);
            printf("Tempo de execucao S: %f\n", timeS);
            break;
        case 3:
            printf("\nLista Sequencial:\n");
            ini = clock();
            SEQnonopos(&lista);
            fim = clock();
            timeS = ((double)(fim - ini)) / CLOCKS_PER_SEC;

            printf("\nLista Encadeada:\n");
            ini = clock();
            ENCinserirNaPosicao(listaenc);
            fim = clock();
            timeE = ((double)(fim - ini)) / CLOCKS_PER_SEC;
            printf("Tempo de execucao E: %f\n", timeE);
            printf("Tempo de execucao S: %f\n", timeS);
            break;
        case 4:
            printf("\nLista Sequencial:\n");
            ini = clock();
            SEQremnonoinicio(&lista);
            fim = clock();
            timeS = ((double)(fim - ini)) / CLOCKS_PER_SEC;

            printf("\nLista Encadeada:\n");
            ini = clock();
            ENCremoverDoInicio(listaenc);
            fim = clock();
            timeE = ((double)(fim - ini)) / CLOCKS_PER_SEC;
            printf("Tempo de execucao E: %f\n", timeE);
            printf("Tempo de execucao S: %f\n", timeS);
            break;
        case 5:
            printf("\nLista Sequencial:\n");
            ini = clock();
            SEQremnonofinal(&lista);
            fim = clock();
            timeS = ((double)(fim - ini)) / CLOCKS_PER_SEC;

            printf("\nLista Encadeada:\n");
            ini = clock();
            ENCremoverDoFinal(listaenc);
            fim = clock();
            timeE = ((double)(fim - ini)) / CLOCKS_PER_SEC;
            printf("Tempo de execucao E: %f\n", timeE);
            printf("Tempo de execucao S: %f\n", timeS);
            break;
        case 6:
            printf("\nLista Sequencial:\n");
            ini = clock();
            SEQremnonopos(&lista);
            fim = clock();
            timeS = ((double)(fim - ini)) / CLOCKS_PER_SEC;

            printf("\nLista Encadeada:\n");
            ini = clock();
            ENCremoverNaPosicao(listaenc);
            fim = clock();
            timeE = ((double)(fim - ini)) / CLOCKS_PER_SEC;
            printf("Tempo de execucao E: %f\n", timeE);
            printf("Tempo de execucao S: %f\n", timeS);
            break;
        case 7:
            printf("\nLista Sequencial:\n");
            ini = clock();
            SEQbuscarg(&lista);
            fim = clock();
            timeS = ((double)(fim - ini)) / CLOCKS_PER_SEC;

            printf("\nLista Encadeada:\n");
            ini = clock();
            ENCpesquisaSequencial(listaenc);
            fim = clock();
            timeE = ((double)(fim - ini)) / CLOCKS_PER_SEC;
            printf("Tempo de execucao E: %f\n", timeE);
            printf("Tempo de execucao S: %f\n", timeS);
            break;
        case 8:
            printf("\nLista Sequencial:\n");
            ini = clock();
            SEQimprimeLista(&lista);
            fim = clock();
            timeS = ((double)(fim - ini)) / CLOCKS_PER_SEC;

            printf("\nLista Encadeada:\n");
            ini = clock();
            ENCimprimeLista(listaenc);
            fim = clock();
            timeE = ((double)(fim - ini)) / CLOCKS_PER_SEC;
            printf("Tempo de execucao E: %f\n", timeE);
            printf("Tempo de execucao S: %f\n", timeS);
            break;
        case 9:

            printf("Salvando Arquivo de lista Sequencial:\n");
            ini = clock();
            SEQcriaarquivo(&lista);
            fim = clock();
            timeS = ((double)(fim - ini)) / CLOCKS_PER_SEC;

            printf("Salvando Arquivo de lista Encadeada:\n");
            ini = clock();
            ENCcriaArquivo(listaenc);
            fim = clock();
            timeE = ((double)(fim - ini)) / CLOCKS_PER_SEC;
            printf("Tempo de execucao E: %f\n", timeE);
            printf("Tempo de execucao S: %f\n", timeS);
            break;
        case 10:

            printf("Insira o Nome do Arquivo que deseja ler:\n");
            scanf("%s", nomearquivo);
            listaenc = ENCcriaLista(nomearquivo);
            lista.tamanho = tamlista(nomearquivo);
            lista.p = SEQalocaLista(lista.tamanho);
            SEQcriaLista(nomearquivo, &lista);
            break;
        case 11:
            exit(1);
            break;
        default:
            ("\nEi, essa opcao nao existe >:(\n");
            break;
        }
    } while (ee != 11);










    return(0);
}




