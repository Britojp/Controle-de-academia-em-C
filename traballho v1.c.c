#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char nome_aluno[40];
    char telefone_aluno[15];
    char email_aluno[60];
    char data_nascimento[11];
    int ano_matricula;
    int numero_matricula;
} Aluno;
typedef struct{ Aluno aluno[100];
                int ult;
                int quantidade;
                char nome_academia[50];
                float valor_fixo;
} Academia;

void iniciar_academia(Academia *a){
    a->ult=0;
    a->quantidade=0;
    printf("Entre com o nome da academia\n");
    scanf(" %[^\n]s", a->nome_academia);
}

void registrarAluno(Aluno alunos[], int *total_alunos, int *ano_matricula) {
    Aluno novo_aluno;
    printf("Digite o nome do aluno: ");
    scanf(" %[^\n]s", novo_aluno.nome_aluno);
    printf("Digite o telefone do aluno: ");
    scanf(" %[^\n]s", novo_aluno.telefone_aluno);
    printf("Digite o email do aluno: ");
    scanf(" %[^\n]s", novo_aluno.email_aluno);
    printf("Digite a data de nascimento do aluno (DD/MM/AAAA): ");
    scanf(" %[^\n]s", novo_aluno.data_nascimento);
    novo_aluno.numero_matricula = (*ano_matricula) + 1;
    novo_aluno.ano_matricula = *ano_matricula;

    alunos[*total_alunos] = novo_aluno;
    (*total_alunos)++;
    (*ano_matricula)++;

    printf("Aluno registrado com sucesso!\n");
    printf("Seu numero de matricula e: %d\n", novo_aluno.numero_matricula);
}

void consultarAlunos(Aluno alunos[], int total_alunos) {
    printf("\nLista de Alunos:\n");
    printf("================\n");
    for (int i = 0; i < total_alunos; i++) {
        printf("Nome: %s\n", alunos[i].nome_aluno);
        printf("Telefone: %s\n", alunos[i].telefone_aluno);
        printf("Email: %s\n", alunos[i].email_aluno);
        printf("Data de Nascimento: %s\n", alunos[i].data_nascimento);
        printf("Numero de Matricula: %d\n", alunos[i].numero_matricula);
        printf("================\n");
    }
}

void Menu() {
    printf("\n====== Menu academia esportiva ======\n");
    printf("1 - Registrar novo aluno\n");
    printf("2 - Consultar alunos\n");
    printf("3 - Apresentar planos\n");
    printf("0 - Sair\n");
    printf("Escolha uma opcao: ");
}

void aluno(Aluno *alun) {
    getchar();
    printf("Entre com o Nome do aluno :\n");
    fgets(alun->nome_aluno, 40, stdin);
    printf("Entre com o Telefone do aluno :\n");
    fgets(alun->telefone_aluno, 15, stdin);
    printf("Entre com o E-Mail do aluno :\n");
    fgets(alun->email_aluno, 60, stdin);
    printf("Entre com a Data de Nascimento do aluno :\n");
    fgets(alun->data_nascimento, 11, stdin);
}

void criar_arq(Aluno alunos[], int total_alunos) {
    FILE *fp;
    fp = fopen("Academia.dat", "wb");
    if (fp == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    } else {
        printf("Arquivo Binario criado com sucesso.\n");
        fwrite(alunos, sizeof(Aluno), total_alunos, fp);
    }
    fclose(fp);
}

int main() {
    Aluno alunos[100];
    int total_alunos = 0;
    int ano_matricula = 20230;
    int opcao;

    do {
        Menu();
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                registrarAluno(alunos, &total_alunos, &ano_matricula);
                break;
            case 2: {
                consultarAlunos(alunos, total_alunos);
                break;
            }
            case 0: {
                criar_arq(alunos, total_alunos);
                printf("Encerrando o programa.\n");
                break;
            }
            default:
                printf("Opcao invalida. Digite novamente.\n");
        }
    } while (opcao != 0);

    return 0;
}