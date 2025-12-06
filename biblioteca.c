#include "biblioteca.h"

Aluno biblioteca[max_alunos]; 
int total_alunos = 0;          

void inicializarDados() {
    total_alunos = 0; 
}

int buscarPosicao(int matricula_busca) {
    for (int i = 0; i < total_alunos; i++) {
        if (biblioteca[i].matricula == matricula_busca) {
            return i; 
        }
    }
    return -1;
}

int buscarPorNome(const char *nome_busca) {
    for (int i = 0; i < total_alunos; i++) {
        if (strcmp(biblioteca[i].nome, nome_busca) == 0) {
            return i;
        }
    }
    return -1;
}

void apresentaAlunos() {
    printf("\n--- Total de Alunos Cadastrados: (%d) ---\n", total_alunos);

    if (total_alunos == 0) {
        printf("[AVISO] Nenhum Aluno Cadastrado.\n");
        return;
    }

    printf("%-10s %-30s %-8s %-5s\n", "Matricula", "Nome", "Turma", "Livro");
    printf("----------------------------------------------------------------\n");
    
    for (int i = 0; i < total_alunos; i++) {
        printf("%-10d %-30s %-8s %-5d\n", 
            biblioteca[i].matricula, 
            biblioteca[i].nome, 
            biblioteca[i].turma, 
            biblioteca[i].livro_emprestado
        );
    }
    printf("----------------------------------------------------------------\n");
}

void inserirAluno() {
    int nova_matricula;
    char novo_nome[50];
    
    printf("\n--- INSERÇÃO DE NOVO ALUNO ---\n");

    if (total_alunos >= max_alunos) {
        printf("[AVISO] O limite de alunos (%d) foi atingido. Nao foi possivel incluir mais alunos.\n", max_alunos);
        return;
    }
  
    printf("Digite a matricula do aluno: ");
    if (scanf("%d", &nova_matricula) != 1) {
        printf("[ERRO] Entrada de matricula invalida.\n");
        while (getchar() != '\n');
        return;
    }
    while (getchar() != '\n');

    if (buscarPosicao(nova_matricula) != -1) {
        printf("[AVISO] A matricula %d ja existe. Processo cancelado.\n", nova_matricula);
        return;
    }
  
    printf("Digite o nome do aluno: ");
    if (fgets(novo_nome, 50, stdin) == NULL) return;
    if (novo_nome[strlen(novo_nome) - 1] == '\n') {
        novo_nome[strlen(novo_nome) - 1] = '\0';
    }

    if (buscarPorNome(novo_nome) != -1) {
        printf("[AVISO] Este aluno (Nome: %s) ja foi cadastrado. Processo cancelado.\n", novo_nome);
        return;
    }
  
    int i = total_alunos;
    while (i > 0 && biblioteca[i - 1].matricula > nova_matricula) {
        biblioteca[i] = biblioteca[i - 1]; 
        i--;
    }
  
    biblioteca[i].matricula = nova_matricula;
    strcpy(biblioteca[i].nome, novo_nome);
    
    printf("Digite a turma do aluno: ");
    scanf("%s", biblioteca[i].turma);
    while (getchar() != '\n'); 

    biblioteca[i].livro_emprestado = 0; 

    total_alunos++;
    printf("\n[SUCESSO] Aluno %s (Matricula: %d) inserido.\n", novo_nome, nova_matricula);
}

void removerAluno() {
    int matricula_remover;
    printf("\n--- REMOÇÃO DE ALUNO ---\n");
    
    if (total_alunos == 0) {
        printf("[AVISO] Nao ha alunos para remover.\n");
        return;
    }
    
    printf("Digite a matricula do aluno a ser removido: ");
    if (scanf("%d", &matricula_remover) != 1) {
        printf("[ERRO] Entrada de matricula invalida.\n");
        while (getchar() != '\n');
        return;
    }
    while (getchar() != '\n');
    
    int pos = buscarPosicao(matricula_remover);
    
    if (pos == -1) {
        printf("[AVISO] Aluno com matricula %d não encontrado.\n", matricula_remover);
        return;
    }

    if (biblioteca[pos].livro_emprestado != 0) {
        printf("[AVISO] O aluno %s tinha o livro %d emprestado. Ele foi removido.\n", 
               biblioteca[pos].nome, biblioteca[pos].livro_emprestado);
    }
    
    for (int i = pos; i < total_alunos - 1; i++) {
        biblioteca[i] = biblioteca[i + 1];
    }
    
    total_alunos--;
    printf("\n[SUCESSO] Aluno com matricula %d removido com sucesso.\n", matricula_remover);
    
    if (total_alunos == 0) {
        printf("[AVISO] Todos os alunos foram removidos (lista vazia).\n");
    }
}

void alterarAluno() {
    int matricula_alterar;
    int pos;
    int novo_livro;
    char resposta;

    printf("\n--- ALTERAÇÃO DE DADOS DO ALUNO ---\n");

    if (total_alunos == 0) {
        printf("[AVISO] Nao ha alunos para alterar.\n");
        return;
    }

    printf("Digite a matricula do aluno a ser alterado: ");
    if (scanf("%d", &matricula_alterar) != 1) {
        printf("[ERRO] Entrada de matricula invalida.\n");
        while (getchar() != '\n');
        return;
    }
    while (getchar() != '\n');

    pos = buscarPosicao(matricula_alterar);

    if (pos == -1) {
        printf("[AVISO] Aluno com matricula %d não encontrado. Processo cancelado.\n", matricula_alterar);
        return;
    }
    
    printf("\nAluno encontrado: %s - Livro atual: %d\n", 
        biblioteca[pos].nome, 
        biblioteca[pos].livro_emprestado
    );

    printf("Deseja alterar a turma (atual: %s)? (S/N): ", biblioteca[pos].turma);
    scanf(" %c", &resposta);
    while (getchar() != '\n');

    if (resposta == 'S' || resposta == 's') {
        printf("Digite a nova turma: ");
        scanf("%s", biblioteca[pos].turma);
        while (getchar() != '\n');
        printf("[SUCESSO] Turma alterada para: %s\n", biblioteca[pos].turma);
    }
  
    printf("Deseja alterar o livro emprestado (atual: %d)? (S/N): ", biblioteca[pos].livro_emprestado);
    scanf(" %c", &resposta);
    while (getchar() != '\n'); 
    
    if (resposta == 'S' || resposta == 's') {
        printf("Digite o ID do novo livro (0 para devolver/nenhum): ");
        if (scanf("%d", &novo_livro) != 1) {
            printf("[ERRO] Entrada de livro invalida.\n");
            while (getchar() != '\n');
            return;
        }
        while (getchar() != '\n');

        if (novo_livro != 0 && biblioteca[pos].livro_emprestado != 0 && novo_livro != biblioteca[pos].livro_emprestado) {
            printf("[AVISO] O aluno ja possui um livro. Limite de %d livro(s) por aluno.\n", max_livros_por_aluno);
        } else {
            biblioteca[pos].livro_emprestado = novo_livro;
            printf("[SUCESSO] Emprestimo/Devolucao atualizado.\n");
        }
    }

    printf("\n[SUCESSO] Alteracoes no Aluno %d concluidas.\n", matricula_alterar);
}

void cadastroSimples(const char *tipo) {
    printf("\n--- CADASTRO DE %s (Simples) ---\n", tipo);
    printf("Funcionalidade completa de cadastro de %s nao implementada.\n", tipo);
    printf("Pressione ENTER para retornar ao menu.\n");
    getchar(); 
}

