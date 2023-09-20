#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

typedef struct {
    int codigo;
    char informacoes[200];
    float preco;
} TodasAulas;

typedef struct {
    int codigo_aula;
    char infos[100];
    float preco;
} Aula;

typedef struct {
    char nome_aluno[40];
    char telefone_aluno[15];
    char email_aluno[60];
    char data_nascimento[11];
    int ano_matricula;
    int numero_matricula;
    Aula aulas[10];
    int numAulas;
    float total_a_pagar;
} Aluno;

typedef struct {
    Aluno alunos[100];
    int total_alunos;
    int ano_matricula;
} Academia;
void criar_arq (Academia A) {   // sem a struct...
   FILE *fp;  
 
   fp = fopen ("Academia.dat", "wb"); //arquivo para escrita binária
   if (fp == NULL) {  
      printf ("Erro ao abrir o arquivo.\n");  
      return;  
   }  
   else {  
           printf ("Arquivo Binario criado com sucesso.\n");  
          fwrite(&A, sizeof(Academia), 1, fp); 
          }         
     fclose (fp);  
       
}

void Carregar_Academia(Academia *A){
     FILE *fp;
    
     fp = fopen ("Academia.dat", "rb"); 
      if (fp == NULL) {  
		A->total_alunos=0;
        A->ano_matricula=2023;
		return;
}  else {
          fread(&(*A),sizeof(Academia),1,fp);
          fclose(fp);
         }  
}

void mostrarPlanos() {
    printf("    1 - FUTSAL (segunda - matutino - instrutor Edmundo) Preco: R$ 100,00\n");
    printf("    2 - ACADEMIA (segunda - vespertino - instrutor Thierson) Preco: R$ 100,00\n");
    printf("    3 - VOLEI (terca - matutino - instrutor Renato) Preco: R$ 70,00\n");
    printf("    4 - JUDO (terca - vespertino - instrutor Joao) Preco: R$ 100,00\n");
    printf("    5 - VOLEI (quarta - matutino - instrutor Marcelo) Preco: R$ 70,00\n");
    printf("    6 - ACADEMIA (quarta - vespertino - instrutora Camila) Preco: R$ 100,00\n");
    printf("    7 - GINASTICA (quinta - matutino - instrutora Fernanda) Preco: R$ 60,00\n");
    printf("    8 - FUTEBOL SOCIETY (quinta - vespertino - instrutor Eduardo) Preco: R$ 80,00\n");
    printf("    9 - HANDEBOL (sexta - matutino - instrutura Rafaela) Preco: R$ 70,00\n");
    printf("    10 - ACADEMIA (sexta - vespertino - instrutor Andre) Preco: R$ 100,00\n"); 
}

bool Emailvalido(const char* email) {
    const char* atSign = strchr(email, '@');
    const char* dotCom = strstr(email, ".com");
    return atSign != NULL && dotCom != NULL && dotCom > atSign;
}

bool Datavalida(const char* data) {
    int dia, mes, ano;
    return sscanf(data, "%d/%d/%d", &dia, &mes, &ano) == 3;
}

bool Telefonevalido(const char* telefone) {
    int len = strlen(telefone);
    if (len != 11) {
        return false;
    }
    for (int i = 0; i < len; i++) {
        if (!isdigit(telefone[i])) {
            return false;
        }
    }
    return true;
}

void registrarAluno(Academia *academia, TodasAulas *todasAulas) {
    Aluno novo_aluno;

    novo_aluno.numAulas = 0;
    int aula = 0;
    int encerrar = 2;
    printf("\nDigite o nome do aluno: ");
    scanf(" %[^\n]s", novo_aluno.nome_aluno);

    do {
        printf("Digite o telefone do aluno (apenas 11 digitos): ");
        scanf(" %[^\n]s", novo_aluno.telefone_aluno);
    } while (!Telefonevalido(novo_aluno.telefone_aluno));

    do {
        printf("Digite o email do aluno: ");
        scanf(" %[^\n]s", novo_aluno.email_aluno);
    } while (!Emailvalido(novo_aluno.email_aluno));

    do {
        printf("Digite a data de nascimento do aluno (DD/MM/AAAA): ");
        scanf(" %[^\n]s", novo_aluno.data_nascimento);
    } while (!Datavalida(novo_aluno.data_nascimento));

    novo_aluno.numero_matricula = academia->ano_matricula + 1;
    novo_aluno.ano_matricula = academia->ano_matricula;

    while(encerrar == 2) {
        do {
            mostrarPlanos();
            printf("Digite a aula desejada: ");
            scanf("%d", &aula);
        } while (aula < 1 || aula > 10);
        
        int aulaEncontrada = 0;

        for(int i = 0; i < novo_aluno.numAulas; i++) {
            int codigoAula = novo_aluno.aulas[i].codigo_aula;
            if (aula - 1 == codigoAula) {
                aulaEncontrada = 1; // aula encontrada
                break;
            }
        }
    
        if (aulaEncontrada == 0) {

            novo_aluno.aulas[novo_aluno.numAulas].codigo_aula = todasAulas[aula - 1].codigo;

            strcpy(novo_aluno.aulas[novo_aluno.numAulas].infos, todasAulas[aula - 1].informacoes);

            novo_aluno.aulas[novo_aluno.numAulas].preco = todasAulas[aula - 1].preco;
            
            novo_aluno.total_a_pagar = novo_aluno.total_a_pagar + todasAulas[aula - 1].preco;
            novo_aluno.numAulas++;
            printf("Aula registrada com sucesso!\n");
        } else {
            printf("Essa aula ja foi registrada!\n");
        }

        printf("Gostaria de encerrar?\n1- Encerrar sessao\n2- Cadastrar mais aulas\n");
        scanf("%d", &encerrar);
    }

    academia->alunos[academia->total_alunos] = novo_aluno;
    academia->total_alunos++;
    academia->ano_matricula++;
    printf("Aluno registrado com sucesso!\n");
    printf("Seu no de matricula e: %d\n", novo_aluno.numero_matricula);
}

void consultarAlunos(Academia *academia) {
    int matricula;
    printf("Digite o no de matricula do aluno: ");
    scanf("%d", &matricula);

    int alunoEncontrado = -1;
    for (int i = 0; i < academia->total_alunos; i++) {
        if (academia->alunos[i].numero_matricula == matricula) {
            alunoEncontrado = i;
            break;
        }
    }

    if (alunoEncontrado >= 0) {
        printf("Aluno encontrado:\n");
        printf("----------------\n");
        printf("Nome: %s\n", academia->alunos[alunoEncontrado].nome_aluno);
        printf("Telefone: %s\n", academia->alunos[alunoEncontrado].telefone_aluno);
        printf("Email: %s\n", academia->alunos[alunoEncontrado].email_aluno);
        printf("Data de Nascimento: %s\n", academia->alunos[alunoEncontrado].data_nascimento);
        printf("Aulas:\n");

        for(int i=0; i < academia->alunos[alunoEncontrado].numAulas; i++) 
            printf("    %s - Preco: R$%.2f\n", academia->alunos[alunoEncontrado].aulas[i].infos, academia->alunos[alunoEncontrado].aulas[i].preco);

        printf("Total a pagar: R$%.2f\n", academia->alunos[alunoEncontrado].total_a_pagar);
        printf("No de matricula: %d\n", academia->alunos[alunoEncontrado].numero_matricula);
        printf("----------------\n");
    } else printf("Aluno nao encontrado.\n");
}

void Menu() {
    printf("\n====== Menu Academia Esportiva ======\n");
    printf("1 - Registrar novo aluno\n");
    printf("2 - Consultar aluno por matricula\n");
    printf("3 - Apresentar planos\n");
    printf("0 - Sair e imprimir relatorio\n\n");
    printf("Escolha uma opcao: ");
}

void salvarAlunosEmArquivo(Academia *academia, TodasAulas *todasAulas) {

    int num = 0;
    char nome_arquivo[50] = "relatorio.txt";

    FILE *arquivo = fopen("relatorio.txt", "w");

    if(arquivo == NULL) printf("Erro, arquivo nao foi criado.\n");

    fprintf(arquivo, "------- ACADEMIA -------\n\n");
    fprintf(arquivo, "------- Aulas -------\n\n");

    for(int i=0; i<10; i++) fprintf(arquivo, "%d - %s Preco: R$%.2f\n", i+1, todasAulas[i].informacoes, todasAulas[i].preco);

    fprintf(arquivo, "\n------ Lista de Alunos ------\n\n");
    if(academia->total_alunos == 0) fprintf(arquivo, "Nenhum aluno registrado.\n");

    for (int i=0; i < academia->total_alunos; i++) {
        fprintf(arquivo, "Aluno: %s\n", academia->alunos[i].nome_aluno);
        fprintf(arquivo, "Matricula: %d\n", academia->alunos[i].numero_matricula);
        fprintf(arquivo, "Telefone: %s\n", academia->alunos[i].telefone_aluno);
        fprintf(arquivo, "Email: %s\n", academia->alunos[i].email_aluno);
        fprintf(arquivo, "Data de Nascimento: %s\n", academia->alunos[i].data_nascimento);
        fprintf(arquivo, "Aulas:\n");

        for(int j=0; j < academia->alunos[i].numAulas; j++) 
            fprintf(arquivo, "      %s - Preco: R$%.2f\n", academia->alunos[i].aulas[j].infos, academia->alunos[i].aulas[j].preco);

        fprintf(arquivo, "Total a pagar: R$%.2f\n", academia->alunos[i].total_a_pagar);
        fprintf(arquivo, "\n---------------------------\n\n");
    }
    fclose(arquivo);
    printf("Arquivo '%s' gerado com sucesso!\n", nome_arquivo);
}

int main() {
    Academia academia;
    TodasAulas todasAulas[10] = {
        {0, "FUTSAL (segunda - matutino - instrutor Edmundo)", 100.0},
        {1, "ACADEMIA (segunda - vespertino - instrutor Thierson)", 100.0},
        {2, "VOLEI (terca - matutino - instrutor Renato)", 70.0},
        {3, "JUDO (terca - vespertino - instrutor Joao)", 100.0},
        {4, "VOLEI (quarta - matutino - instrutor Marcelo)", 70.0},
        {5, "ACADEMIA (quarta - vespertino - instrutora Camila)", 100.0},
        {6, "GINASTICA (quinta - matutino - instrutora Fernanda)", 60.0},
        {7, "FUTEBOL SOCIETY (quinta - vespertino - instrutor Eduardo)", 80.0},
        {8, "HANDEBOL (sexta - matutino - instrutura Rafaela)", 70.0},
        {9, "ACADEMIA (sexta - vespertino - instrutor Andre)", 100.0}
    };

Carregar_Academia(&academia);

    int total_alunos = 0;
    int ano_matricula = 2023;
    int opcao;

    do {
        Menu();
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                registrarAluno(&academia, todasAulas);
                break;
            case 2:
                consultarAlunos(&academia);
                break;
            case 3:
                mostrarPlanos();
            	break;
            case 0:
                salvarAlunosEmArquivo(&academia, todasAulas);
                printf("Obrigado por usar a nossa aplicacao!");
                criar_arq(academia);
                break;
            default:
                printf("Opcao invalida. Digite novamente.\n");
        }
    } while (opcao != 0);

    return 0;
}
