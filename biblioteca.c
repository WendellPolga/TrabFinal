#include "biblioteca.h"

Aluno biblioteca[max_alunos]; 
int total_alunos = 0;          

Turma cadastro_turmas[max_turmas];
int total_turmas = 0;

Livro catalogo_livros[max_livros];
int total_livros = 0;

void inicializarDados() {
    total_alunos = 0; 
    total_turmas = 0;
    total_livros = 0;
}

int buscarPosicaoAluno(int matricula_busca) {
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

int buscarPosicaoTurma(const char *codigo_busca) {
    for (int i = 0; i < total_turmas; i++) {
        if (strcmp(cadastro_turmas[i].codigo, codigo_busca) == 0) {
            return i;
        }
    }
    return -1;
}

int buscarPosicaoLivro(int id_busca) {
    for (int i = 0; i < total_livros; i++) {
        if (catalogo_livros[i].id == id_busca) {
            return i;
        }
    }
    return -1;
}

void inserirTurma() {
    char novo_codigo[10];
    
    printf("\n--- CADASTRO DE NOVA TURMA ---\n");

    if (total_turmas >= max_turmas) {
        printf("[AVISO] O limite de turmas (%d) foi atingido. Processo cancelado.\n", max_turmas);
        return;
    }

    printf("Digite o codigo da turma: ");
    scanf("%s", novo_codigo);
    while (getchar() != '\n');
    
    if (buscarPosicaoTurma(novo_codigo) != -1) {
        printf("[AVISO] O codigo de turma '%s' ja existe. Processo cancelado.\n", novo_codigo);
        return;
    }
    
    int i = total_turmas;
    while (i > 0 && strcmp(cadastro_turmas[i - 1].codigo, novo_codigo) > 0) {
        cadastro_turmas[i] = cadastro_turmas[i - 1]; 
        i--;
    }

    strcpy(cadastro_turmas[i].codigo, novo_codigo);
    
    printf("Digite o nome do curso: ");
    fgets(cadastro_turmas[i].nome_curso, 40, stdin);
    if (cadastro_turmas[i].nome_curso[strlen(cadastro_turmas[i].nome_curso) - 1] == '\n') {
        cadastro_turmas[i].nome_curso[strlen(cadastro_turmas[i].nome_curso) - 1] = '\0';
    }
    
    cadastro_turmas[i].limite_alunos = 40; 
    
    total_turmas++;
    printf("\n[SUCESSO] Turma '%s' cadastrada (Limite: %d alunos).\n", novo_codigo, 40);
}

void apresentaTurmas() {
    printf("\n--- TOTAL DE TURMAS CADASTRADAS (%d) ---\n", total_turmas);

    if (total_turmas == 0) {
        printf("[AVISO] Nenhuma turma cadastrada.\n");
        return;
    }

    printf("%-10s %-40s %-8s\n", "Código", "Nome do Curso", "Limite");
    printf("----------------------------------------------------------------\n");
    
    for (int i = 0; i < total_turmas; i++) {
        printf("%-10s %-40s %-8d\n", 
            cadastro_turmas[i].codigo, 
            cadastro_turmas[i].nome_curso, 
            cadastro_turmas[i].limite_alunos
        );
    }
    printf("----------------------------------------------------------------\n");
}

void inserirLivro() {
    int novo_id;
    
    printf("\n--- CADASTRO DE NOVO LIVRO ---\n");

    if (total_livros >= max_livros) {
        printf("[AVISO] O limite de livros cadastrados (%d) foi atingido.\n", max_livros);
        return;
    }

    printf("Digite o ID do Livro: ");
    if (scanf("%d", &novo_id) != 1) {
        printf("[ERRO] Entrada de ID invalida.\n");
        while (getchar() != '\n'); 
        return;
    }
    while (getchar() != '\n');
    
    if (buscarPosicaoLivro(novo_id) != -1) {
        printf("[AVISO] O Livro com ID %d ja existe. Processo cancelado.\n", novo_id);
        return;
    }
    
    int i = total_livros;
    while (i > 0 && catalogo_livros[i - 1].id > novo_id) {
        catalogo_livros[i] = catalogo_livros[i - 1]; 
        i--;
    }
    
    catalogo_livros[i].id = novo_id;
    
    printf("Digite o titulo do livro: ");
    fgets(catalogo_livros[i].titulo, 60, stdin);
    if (catalogo_livros[i].titulo[strlen(catalogo_livros[i].titulo) - 1] == '\n') {
        catalogo_livros[i].titulo[strlen(catalogo_livros[i].titulo) - 1] = '\0';
    }
    
    printf("Digite o autor do livro: ");
    scanf("%s", catalogo_livros[i].autor);
    while (getchar() != '\n');

    printf("Digite a quantidade de livros em estoque: ");
    if (scanf("%d", &catalogo_livros[i].qtd_estoque) != 1) {
         printf("[ERRO] Entrada de quantidade invalida.\n");
         while (getchar() != '\n'); 
         return;
    }
    while (getchar() != '\n');
    
    total_livros++;
    printf("\n[SUCESSO] Livro '%s' (ID: %d) cadastrado com %d copias.\n", catalogo_livros[i].titulo, novo_id, catalogo_livros[i].qtd_estoque);
}

void apresentaLivros() {
    printf("\n--- CATÁLOGO DE LIVROS CADASTRADOS (%d) ---\n", total_livros);

    if (total_livros == 0) {
        printf("[AVISO] Nenhum livro cadastrado.\n");
        return;
    }

    // CABEÇALHO
    printf("%-5s %-40s %-25s %-5s\n", "ID", "Título", "Autor", "Estoque");
    printf("--------------------------------------------------------------------------------\n");
    
    for (int i = 0; i < total_livros; i++) {
        printf("%-5d %-40s %-25s %-5d\n", 
            catalogo_livros[i].id, 
            catalogo_livros[i].titulo, 
            catalogo_livros[i].autor,
            catalogo_livros[i].qtd_estoque
        );
    }
    printf("--------------------------------------------------------------------------------\n");
}

void inserirAluno() {
    int nova_matricula;
    char novo_nome[50];
    char codigo_turma_aluno[10];
    
    printf("\n--- CADASTRO DE NOVO ALUNO ---\n");

    if (total_alunos >= max_alunos) {
        printf("[AVISO] O limite de alunos cadastrados (%d) foi atingido. Processo cancelado.\n", max_alunos);
        return;
    }
    
    printf("Digite a matricula do aluno: ");
    if (scanf("%d", &nova_matricula) != 1) { /* ... */ while (getchar() != '\n'); return; }
    while (getchar() != '\n'); 
    if (buscarPosicaoAluno(nova_matricula) != -1) { printf("[AVISO] A matricula %d ja existe. Processo cancelado.\n", nova_matricula); return; }

    printf("Digite o nome do aluno: ");
    if (fgets(novo_nome, 50, stdin) == NULL) { /* ... */ return; }
    if (novo_nome[strlen(novo_nome) - 1] == '\n') { novo_nome[strlen(novo_nome) - 1] = '\0'; }
    if (buscarPorNome(novo_nome) != -1) { printf("[AVISO] Este aluno (Nome: %s) ja foi cadastrado. Processo cancelado.\n", novo_nome); return; }

    printf("Digite o codigo da turma (ex: SI01): ");
    scanf("%s", codigo_turma_aluno);
    while (getchar() != '\n');

    int pos_turma = buscarPosicaoTurma(codigo_turma_aluno);
    if (pos_turma == -1) {
        printf("[ERRO] Turma '%s' nao cadastrada no sistema. Cadastre a turma primeiro.\n", codigo_turma_aluno);
        return;
    }
    
    int i = total_alunos;
    while (i > 0 && biblioteca[i - 1].matricula > nova_matricula) {
        biblioteca[i] = biblioteca[i - 1]; 
        i--;
    }

    biblioteca[i].matricula = nova_matricula;
    strcpy(biblioteca[i].nome, novo_nome);
    strcpy(biblioteca[i].codigo_turma, codigo_turma_aluno);
    biblioteca[i].id_livro_emprestado = 0;

    total_alunos++;
    printf("\n[SUCESSO] Aluno %s inserido na turma %s.\n", novo_nome, codigo_turma_aluno);
}




