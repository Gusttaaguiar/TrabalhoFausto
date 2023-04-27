#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <locale.h>

// Estrutura para armazenar os dados de um aluno
typedef struct aluno {
    char nome[50];
    int matricula;
    char cpf[12];
    char data_nasc[11];
    float notas[4];
    struct aluno *prox;
} Aluno;

// Função para validar o CPF de um aluno
int validar_cpf(char *cpf) {
    int i, j, digito1, digito2, soma;
    int peso1[10] = {10, 9, 8, 7, 6, 5, 4, 3, 2};
    int peso2[11] = {11, 10, 9, 8, 7, 6, 5, 4, 3, 2};

    // Verifica se o CPF tem 11 dígitos
    if (strlen(cpf) != 11) {
        return 0;
    }

    // Verifica se o CPF é formado por dígitos repetidos
    for (i = 0; i < 10; i++) {
        if (cpf[0] == '0' + i) {
            for (j = 1; j < 11; j++) {
                if (cpf[j] != cpf[0]) {
                    break;
                }
            }
            if (j == 11) {
                return 0;
            }
        }
    }

    // Calcula o primeiro dígito verificador
    soma = 0;
    for (i = 0; i < 9; i++) {
        soma += (cpf[i] - '0') * peso1[i];
    }
    digito1 = (soma * 10) % 11;
    if (digito1 == 10) {
        digito1 = 0;
    }

    // Calcula o segundo dígito verificador
    soma = 0;
    for (i = 0; i < 10; i++) {
        soma += (cpf[i] - '0') * peso2[i];
    }
    digito2 = (soma * 10) % 11;
    if (digito2 == 10) {
        digito2 = 0;
    }

    // Verifica se os dígitos verificadores são iguais aos informados
    if (digito1 == cpf[9] - '0' && digito2 == cpf[10] - '0') {
        return 1;
    } else {
        return 0;
    }
}

// Função para calcular a idade de um aluno com base na data de nascimento
int calcular_idade(char *data_nasc) {
    int dia, mes, ano;
    int dia_atual, mes_atual, ano_atual;
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    // Extrai o dia, mês e ano da data de nascimento
    sscanf(data_nasc, "%d/%d/%d", &dia, &mes, &ano);

    // Obtém o dia, mês e ano atual do sistema
    dia_atual = tm.tm_mday;
    mes_atual = tm.tm_mon + 1;
    ano_atual = tm.tm_year + 1900;

    // Calcula a idade em anos
    int idade = ano_atual - ano;

    // Ajusta a idade se o mês ou dia atual for menor que o de nascimento
    if (mes_atual < mes || (mes_atual == mes && dia_atual < dia)) {
        idade--;
    }

    return idade;
}

// Função para criar um novo nó da lista de alunos
Aluno* criar_aluno(char *nome, int matricula, char *cpf,
                    char *data_nasc, float notas[4]) {

    Aluno *novo = malloc(sizeof(Aluno));

    strcpy(novo->nome, nome);

novo->matricula = matricula;

strcpy(novo->cpf,cpf);

strcpy(novo->data_nasc,data_nasc);

for(int i=0;i<4;i++){

novo->notas[i]=notas[i];

}

novo->prox=NULL;

return novo;

}
// Função para inserir um aluno na lista ordenada pelo nome
void inserir_aluno(Aluno **lista, Aluno *novo) {
    Aluno *ant = NULL;
    Aluno *atual = *lista;

    // Procura a posição de inserção na lista
    while (atual != NULL && strcmp(atual->nome, novo->nome) < 0) {
        ant = atual;
        atual = atual->prox;
    }

    // Insere o novo nó na lista
    if (ant == NULL) {
        // Insere no início da lista
        novo->prox = *lista;
        *lista = novo;
    } else {
        // Insere no meio ou fim da lista
        novo->prox = atual;
        ant->prox = novo;
    }
}

// Função para remover um aluno da lista pelo CPF
int remover_aluno(Aluno **lista, char *cpf) {
    Aluno *ant = NULL;
    Aluno *atual = *lista;

    // Procura o nó a ser removido na lista
    while (atual != NULL && strcmp(atual->cpf, cpf) != 0) {
        ant = atual;
        atual = atual->prox;
    }

    // Verifica se encontrou o nó
    if (atual == NULL) {
        // Não encontrou o aluno com o CPF informado
        return 0;
    } else {
        // Remove o nó da lista
        if (ant == NULL) {
            // Remove o primeiro nó da lista
            *lista = atual->prox;
        } else {
            // Remove um nó do meio ou fim da lista
            ant->prox = atual->prox;
        }
        free(atual);
        return 1;
    }
}

// Função para alterar os dados de um aluno na lista pelo CPF
int alterar_aluno(Aluno *lista, char *cpf, char *nome, int matricula,
                  char *data_nasc, float notas[4]) {

    Aluno *atual = lista;

    // Procura o nó a ser alterado na lista
    while (atual != NULL && strcmp(atual->cpf, cpf) != 0) {
        atual = atual->prox;
    }

    // Verifica se encontrou o nó
    if (atual == NULL) {
        // Não encontrou o aluno com o CPF informado
        return 0;
    } else {
        // Altera os dados do nó na lista
        strcpy(atual->nome, nome);
        atual->matricula = matricula;
        strcpy(atual->data_nasc, data_nasc);
        for (int i = 0; i < 4; i++) {
            atual->notas[i] = notas[i];
        }
        return 1;
    }
}

// Função para consultar os dados de um aluno na lista pelo CPF
Aluno* consultar_aluno(Aluno *lista, char *cpf) {
    Aluno *atual = lista;

    // Procura o nó a ser consultado na lista
    while (atual != NULL && strcmp(atual->cpf, cpf) != 0) {
        atual = atual->prox;
    }

    // Retorna o ponteiro para o nó encontrado ou NULL se não encontrou
    return atual;
}

// Função para imprimir os dados de um aluno na tela
void imprimir_aluno(Aluno *aluno) {
    printf("Nome: %s\n", aluno->nome);
    printf("Matrícula: %d\n", aluno->matricula);
    printf("CPF: %s\n", aluno->cpf);
    printf("Data de nascimento: %s\n", aluno->data_nasc);

printf("Idade: %d anos\n", calcular_idade(aluno->data_nasc));

printf("Notas: ");

for(int i=0;i<4;i++){

printf("%.1f ",aluno->notas[i]);

}

printf("\n");

}

// Função para imprimir todos os alunos da lista na tela
void imprimir_lista(Aluno *lista) {

Aluno *atual=lista;

while(atual!=NULL){

imprimir_aluno(atual);

printf("\n");

atual=atual->prox;

}

}

// Função para salvar os dados da lista em um arquivo binário
void salvar_arquivo(Aluno *lista, char *nome_arquivo) {
    FILE *arq = fopen(nome_arquivo, "wb");
    Aluno *atual = lista;

    // Verifica se o arquivo foi aberto com sucesso
    if (arq == NULL) {
        printf("Erro ao abrir o arquivo %s\n", nome_arquivo);
        return;
    }

    // Escreve os dados de cada nó da lista no arquivo
    while (atual != NULL) {
        fwrite(atual, sizeof(Aluno), 1, arq);
        atual = atual->prox;
    }

    // Fecha o arquivo
    fclose(arq);
}

// Função para carregar os dados da lista de um arquivo binário
void carregar_arquivo(Aluno **lista, char *nome_arquivo) {
    FILE *arq = fopen(nome_arquivo, "rb");
    Aluno *novo;

    // Verifica se o arquivo foi aberto com sucesso
    if (arq == NULL) {
        printf("Erro ao abrir o arquivo %s\n", nome_arquivo);
        return;
    }

    // Lê os dados de cada nó do arquivo e insere na lista
    while (!feof(arq)) {
        novo = malloc(sizeof(Aluno));
        if (fread(novo, sizeof(Aluno), 1, arq) == 1) {
            inserir_aluno(lista, novo);
        } else {
            free(novo);
        }
    }

    // Fecha o arquivo
    fclose(arq);
}

// Função principal do programa
int main() {

setlocale(LC_ALL, "Portuguese");

char nome_arquivo[20]="alunos.dat";

char nome[50],cpf[12],data_nasc[11];

int matricula,opcao;

float notas[4];

Aluno *lista=NULL;

Aluno *aluno;

// Carrega os dados do arquivo para a lista
carregar_arquivo(&lista,nome_arquivo);

// Exibe o menu de opções
do{

printf("Escolha uma opção:\n");

printf("1 - Cadastrar aluno\n");

printf("2 - Consultar aluno\n");

printf("3 - Remover aluno\n");

printf("4 - Alterar aluno\n");

printf("5 - Imprimir todos os alunos\n");

printf("6 - Sair\n");

scanf("%d",&opcao);

switch(opcao){

case 1:

// Cadastrar aluno

printf("Digite o nome do aluno: ");

scanf("%s",nome);

printf("Digite a matrícula do aluno: ");

scanf("%d",&matricula);

do{

printf("Digite o CPF do aluno: ");

scanf("%s",cpf);

if(!validar_cpf(cpf)){

printf("CPF inválido. Digite novamente.\n");

}

}while(!validar_cpf(cpf));

printf("Digite a data de nascimento do aluno (dd/mm/aaaa): ");

scanf("%s",data_nasc);

printf("Digite as quatro notas do aluno: ");

for(int i=0;i<4;i++){

scanf("%f",&notas[i]);

}

// Cria um novo nó e insere na lista
aluno=criar_aluno(nome,matricula,cpf,data_nasc,notas);

inserir_aluno(&lista,aluno);

printf("Aluno cadastrado com sucesso.\n");

break;

case 2:

// Consultar aluno

printf("Digite o CPF do aluno que deseja consultar: ");

scanf("%s",cpf);

// Busca o nó na lista pelo CPF
aluno=consultar_aluno(lista,cpf);

if(aluno==NULL){

// Não encontrou o aluno
printf("Não há aluno cadastrado com esse CPF.\n");

}else{

// Encontrou o aluno e imprime seus dados
imprimir_aluno(aluno);

}

break;

case 3:

// Remover aluno

printf("Digite o CPF do aluno que deseja remover: ");

scanf("%s",cpf);

// Remove o nó da lista pelo CPF
if(remover_aluno(&lista,cpf)){

// Remoção bem sucedida
printf("Aluno removido com sucesso.\n");

}else{

// Não encontrou o aluno
printf("Não há aluno cadastrado com esse CPF.\n");

}

break;

case 4:

// Alterar aluno

printf("Digite o CPF do aluno que deseja alterar: ");

scanf("%s",cpf);

// Busca o nó na lista pelo CPF




// Alterar aluno

printf("Digite o CPF do aluno que deseja alterar: ");

scanf("%s",cpf);

// Busca o nó na lista pelo CPF
aluno=consultar_aluno(lista,cpf);

if(aluno==NULL){

// Não encontrou o aluno
printf("Não há aluno cadastrado com esse CPF.\n");

}else{

// Encontrou o aluno e pede os novos dados
printf("Digite o novo nome do aluno: ");

scanf("%s",nome);

printf("Digite a nova matrícula do aluno: ");

scanf("%d",&matricula);

printf("Digite a nova data de nascimento do aluno (dd/mm/aaaa): ");

scanf("%s",data_nasc);

printf("Digite as novas quatro notas do aluno: ");

for(int i=0;i<4;i++){

scanf("%f",&notas[i]);

}

// Altera os dados do nó na lista
if(alterar_aluno(lista,cpf,nome,matricula,data_nasc,notas)){

// Alteração bem sucedida
printf("Aluno alterado com sucesso.\n");

}else{

// Não conseguiu alterar o aluno
printf("Erro ao alterar o aluno.\n");

}

}

break;

case 5:

// Imprimir todos os alunos

// Imprime os dados de todos os nós da lista
imprimir_lista(lista);

break;

case 6:

// Sair

// Salva os dados da lista no arquivo
salvar_arquivo(lista,nome_arquivo);

printf("Obrigado por usar o programa. Até mais!\n");

break;

default:

// Opção inválida
printf("Opção inválida. Digite novamente.\n");

break;

}

}while(opcao!=6);

return 0;

}
