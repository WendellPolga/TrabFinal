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

void lerString(char *destino, int tamanho) {
    if (fgets(destino, tamanho, stdin) == NULL) return;
    if (destino[strlen(destino) - 1] == '\n') {
        destino[strlen(destino) - 1] = '\0';
    }
}

int buscarPosicaoAluno(int matricula_busca) {
    for (int i = 0; i < total_alunos; i++) {
        if (biblioteca[i].matricula == matricula_busca) return i; 
    }
    return -1; 
}

int buscarPorNome(const char *nome_busca) {
    for (int i = 0; i < total_alunos; i++) {
        if (strcmp(biblioteca[i].nome, nome_busca) == 0) return i;
    }
    return -1;
}

int buscarPosicaoTurma(const char *codigo_busca) {
    for (int i = 0; i < total_turmas; i++) {
        if (strcmp(cadastro_turmas[i].codigo, codigo_busca) == 0) return i;
    }
    return -1;
}

int buscarPosicaoLivro(int id_busca) {
    for (int i = 0; i < total_livros; i++) {
        if (catalogo_livros[i].id == id_busca) return i;
    }
    return -1;
}

void apresentaAlunos() {
    printf("\n--- TOTAL DE ALUNOS CADASTRADOS (%d) ---\n", total_alunos);
    if (total_alunos == 0) { printf("[AVISO] Nenhum aluno cadastrado.\n"); return; }
    printf("%-10s %-30s %-10s %-5s\n", "Matrícula", "Nome", "Turma", "Livro ID");
    printf("----------------------------------------------------------------\n");
    for (int i = 0; i < total_alunos; i++) {
        printf("%-10d %-30s %-10s %-5d\n", 
            biblioteca[i].matricula, 
            biblioteca[i].nome, 
            biblioteca[i].codigo_turma, 
            biblioteca[i].id_livro_emprestado
        );
    }
}

void inserirAluno() {
    int nova_matricula;
    char novo_nome[50];
    char codigo_turma_aluno[10];
    
    printf("\n--- ADICIONAR NOVO ALUNO ---\n");
    if (total_alunos >= max_alunos) { printf("[AVISO] O limite de alunos (%d) foi atingido.\n", max_alunos); return; }
    
    printf("Digite a matricula do aluno: ");
    if (scanf("%d", &nova_matricula) != 1) { printf("[ERRO] Matricula invalida.\n"); while (getchar() != '\n'); return; }
    while (getchar() != '\n'); 
    if (buscarPosicaoAluno(nova_matricula) != -1) { printf("[AVISO] A matricula %d ja existe.\n", nova_matricula); return; }

    printf("Digite o nome do aluno: "); lerString(novo_nome, 50);
    if (buscarPorNome(novo_nome) != -1) { printf("[AVISO] Este aluno (Nome: %s) ja foi cadastrado.\n", novo_nome); return; }
    
    printf("Digite o codigo da turma (ex: ADS1): ");
    scanf("%s", codigo_turma_aluno); while (getchar() != '\n');
    if (buscarPosicaoTurma(codigo_turma_aluno) == -1) {
        printf("[ERRO] Turma '%s' nao cadastrada. Cadastre a turma primeiro.\n", codigo_turma_aluno);
        return;
    }
    
    int i = total_alunos;
    while (i > 0 && biblioteca[i - 1].matricula > nova_matricula) {
        biblioteca[i] = biblioteca[i - 1]; i--;
    }

    biblioteca[i].matricula = nova_matricula;
    strcpy(biblioteca[i].nome, novo_nome);
    strcpy(biblioteca[i].codigo_turma, codigo_turma_aluno); 
    biblioteca[i].id_livro_emprestado = 0; 
    
    total_alunos++;
    printf("\n[SUCESSO] Aluno %s inserido e ordenado.\n", novo_nome);
}

void removerAluno() {
    int matricula_remover;
    printf("\n--- REMOVER ALUNO ---\n");
    if (total_alunos == 0) { printf("[AVISO] Nao ha alunos para remover.\n"); return; }
    
    printf("Digite a matricula do aluno a ser removido: ");
    if (scanf("%d", &matricula_remover) != 1) { printf("[ERRO] Entrada invalida.\n"); while (getchar() != '\n'); return; }
    while (getchar() != '\n');
    
    int pos = buscarPosicaoAluno(matricula_remover);
    if (pos == -1) { printf("[AVISO] Aluno com matricula %d nao encontrado.\n", matricula_remover); return; }

    if (biblioteca[pos].id_livro_emprestado != 0) {
        printf("[AVISO] O aluno tinha o livro ID %d emprestado. Removido.\n", biblioteca[pos].id_livro_emprestado);
    }
    
    for (int i = pos; i < total_alunos - 1; i++) {
        biblioteca[i] = biblioteca[i + 1];
    }
    
    total_alunos--;
    printf("\n[SUCESSO] Aluno com matricula %d removido.\n", matricula_remover);
    
    if (total_alunos == 0) { printf("[AVISO] Todos os alunos foram removidos.\n"); }
}

void alterarAluno() {
    int matricula_alterar, novo_livro_id;
    char nova_turma_codigo[10], resposta;
    printf("\n--- ALTERAÇÃO DE DADOS DO ALUNO ---\n");
    if (total_alunos == 0) { printf("[AVISO] Nao ha alunos para alterar.\n"); return; }

    printf("Digite a matricula do aluno a ser alterado: ");
    if (scanf("%d", &matricula_alterar) != 1) { printf("[ERRO] Entrada invalida.\n"); while (getchar() != '\n'); return; }
    while (getchar() != '\n');
    int pos = buscarPosicaoAluno(matricula_alterar);
    if (pos == -1) { printf("[AVISO] Aluno com matricula %d nao encontrado.\n", matricula_alterar); return; }
    
    printf("\nAluno encontrado: %s | Turma: %s | Livro atual: %d\n", biblioteca[pos].nome, biblioteca[pos].codigo_turma, biblioteca[pos].id_livro_emprestado);

    printf("Deseja alterar a turma? (S/N): "); scanf(" %c", &resposta); while (getchar() != '\n'); 
    if (resposta == 'S' || resposta == 's') {
        printf("Digite o novo codigo de turma: "); scanf("%s", nova_turma_codigo); while (getchar() != '\n');
        if (buscarPosicaoTurma(nova_turma_codigo) == -1) {
            printf("[ERRO] Turma '%s' nao cadastrada. Alteracao cancelada.\n", nova_turma_codigo);
        } else {
            strcpy(biblioteca[pos].codigo_turma, nova_turma_codigo);
            printf("[SUCESSO] Turma alterada para: %s\n", nova_turma_codigo);
        }
    }

    printf("Deseja ALTERAR o livro (Empréstimo/Devolução)? (S/N): "); scanf(" %c", &resposta); while (getchar() != '\n'); 
    if (resposta == 'S' || resposta == 's') {
        printf("[AVISO] Use as opcoes 13 (Empréstimo) ou 14 (Devolução) para transacoes.\n");
        printf("Se for devolver agora (use 0): ");
        if (scanf("%d", &novo_livro_id) != 1) { printf("[ERRO] Entrada invalida.\n"); while (getchar() != '\n'); return; }
        while (getchar() != '\n');

        if (novo_livro_id == 0) {
             biblioteca[pos].id_livro_emprestado = 0;
             printf("[SUCESSO] Livro devolvido (campo atualizado).\n");
        } else {
            printf("[ERRO] Use as opcoes 13/14 para emprestar.\n");
        }
    }
    printf("\n[SUCESSO] Alteracoes concluidas.\n");
}

void apresentaTurmas() {
    printf("\n--- RELAÇÃO DE TURMAS CADASTRADAS (%d) ---\n", total_turmas);
    if (total_turmas == 0) { printf("[AVISO] Nenhuma turma cadastrada.\n"); return; }
    printf("%-10s %-40s %-8s\n", "Código", "Nome do Curso", "Limite");
    printf("----------------------------------------------------------------\n");
    for (int i = 0; i < total_turmas; i++) {
        printf("%-10s %-40s %-8d\n", cadastro_turmas[i].codigo, cadastro_turmas[i].nome_curso, cadastro_turmas[i].limite_alunos);
    }
}

void inserirTurma() {
    char novo_codigo[10];
    printf("\n--- CADASTRO DE NOVA TURMA ---\n");
    if (total_turmas >= max_turmas) { printf("[AVISO] O limite de turmas (%d) foi atingido.\n", max_turmas); return; }

    printf("Digite o codigo da turma: ");
    scanf("%s", novo_codigo); while (getchar() != '\n');
    if (buscarPosicaoTurma(novo_codigo) != -1) { printf("[AVISO] O codigo de turma '%s' ja existe.\n", novo_codigo); return; }

    int i = total_turmas;
    while (i > 0 && strcmp(cadastro_turmas[i - 1].codigo, novo_codigo) > 0) {
        cadastro_turmas[i] = cadastro_turmas[i - 1]; i--;
    }

    strcpy(cadastro_turmas[i].codigo, novo_codigo);
    printf("Digite o nome do curso: "); lerString(cadastro_turmas[i].nome_curso, 40);
    cadastro_turmas[i].limite_alunos = 40; 

    total_turmas++;
    printf("\n[SUCESSO] Turma '%s' cadastrada (Limite: %d alunos).\n", novo_codigo, 40);
}

void removerTurma() {
    char codigo_remover[10];
    printf("\n--- REMOÇÃO DE TURMA ---\n");
    if (total_turmas == 0) { printf("[AVISO] Nao ha turmas para remover.\n"); return; }
    
    printf("Digite o codigo da turma a ser removida: ");
    scanf("%s", codigo_remover); while (getchar() != '\n');
    
    int pos = buscarPosicaoTurma(codigo_remover);
    if (pos == -1) { printf("[AVISO] Turma '%s' NAO encontrada.\n", codigo_remover); return; }
    
    for(int i = 0; i < total_alunos; i++) {
        if(strcmp(biblioteca[i].codigo_turma, codigo_remover) == 0) {
            printf("[ERRO] Nao foi possivel remover. Ha alunos cadastrados nesta turma.\n");
            return;
        }
    }
    
    for (int i = pos; i < total_turmas - 1; i++) {
        cadastro_turmas[i] = cadastro_turmas[i + 1];
    }
    
    total_turmas--;
    printf("\n[SUCESSO] Turma '%s' removida com sucesso.\n", codigo_remover);
}

void alterarTurma() {
    char codigo_alterar[10], resposta;
    printf("\n--- ALTERAÇÃO DE TURMA ---\n");
    if (total_turmas == 0) { printf("[AVISO] Nao ha turmas para alterar.\n"); return; }

    printf("Digite o codigo da turma a ser alterada: ");
    scanf("%s", codigo_alterar); while (getchar() != '\n');
    int pos = buscarPosicaoTurma(codigo_alterar);
    if (pos == -1) { printf("[AVISO] Turma '%s' NAO encontrada.\n", codigo_alterar); return; }
    
    printf("\nTurma encontrada: %s\n", cadastro_turmas[pos].nome_curso);

    printf("Deseja alterar o nome do curso? (S/N): "); scanf(" %c", &resposta); while (getchar() != '\n'); 
    if (resposta == 'S' || resposta == 's') {
        printf("Digite o novo nome do curso: "); lerString(cadastro_turmas[pos].nome_curso, 40);
        printf("[SUCESSO] Nome do curso alterado.\n");
    }
    printf("\n[SUCESSO] Alteracoes na Turma concluidas.\n");
}

void apresentaLivros() {
    printf("\n--- CATÁLOGO DE LIVROS CADASTRADOS (%d) ---\n", total_livros);
    if (total_livros == 0) { printf("[AVISO] Nenhum livro cadastrado.\n"); return; }

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
}

void inserirLivro() {
    int novo_id;
    printf("\n--- CADASTRO DE NOVO LIVRO ---\n");
    if (total_livros >= max_livros) { printf("[AVISO] O limite do catalogo (%d) foi atingido.\n", max_livros); return; }

    printf("Digite o ID do Livro: ");
    if (scanf("%d", &novo_id) != 1) { printf("[ERRO] ID invalido.\n"); while (getchar() != '\n'); return; }
    while (getchar() != '\n');
    
    if (buscarPosicaoLivro(novo_id) != -1) { printf("[AVISO] O Livro com ID %d ja existe.\n", novo_id); return; }

    int i = total_livros;
    while (i > 0 && catalogo_livros[i - 1].id > novo_id) {
        catalogo_livros[i] = catalogo_livros[i - 1]; i--;
    }

    catalogo_livros[i].id = novo_id;
    printf("Digite o TITULO: "); lerString(catalogo_livros[i].titulo, 60);
    printf("Digite o AUTOR: "); scanf("%s", catalogo_livros[i].autor); while (getchar() != '\n');
    printf("Digite a QUANTIDADE em Estoque: ");
    if (scanf("%d", &catalogo_livros[i].qtd_estoque) != 1) { catalogo_livros[i].qtd_estoque = 1; }
    while (getchar() != '\n');
    
    total_livros++;
    printf("\n[SUCESSO] Livro '%s' (ID: %d) cadastrado.\n", catalogo_livros[i].titulo, novo_id);
}

void removerLivro() {
    int id_remover;
    printf("\n--- REMOÇÃO DE LIVRO ---\n");
    if (total_livros == 0) { printf("[AVISO] Nao ha livros para remover.\n"); return; }
    
    printf("Digite o ID do livro a ser removido: ");
    if (scanf("%d", &id_remover) != 1) { printf("[ERRO] Entrada invalida.\n"); while (getchar() != '\n'); return; }
    while (getchar() != '\n');
    
    int pos = buscarPosicaoLivro(id_remover);
    if (pos == -1) { printf("[AVISO] Livro com ID %d NAO encontrado.\n", id_remover); return; }
    
    for(int i = 0; i < total_alunos; i++) {
        if(biblioteca[i].id_livro_emprestado == id_remover) {
            printf("[ERRO] Nao eh possivel remover. Livro ID %d esta emprestado ao aluno %s.\n", id_remover, biblioteca[i].nome);
            return;
        }
    }
    
    for (int i = pos; i < total_livros - 1; i++) {
        catalogo_livros[i] = catalogo_livros[i + 1];
    }
    
    total_livros--;
    printf("\n[SUCESSO] Livro com ID %d removido com sucesso.\n", id_remover);
}

void alterarLivro() {
    int id_alterar, novo_estoque;
    char resposta;
    printf("\n--- ALTERAÇÃO DE LIVRO ---\n");
    if (total_livros == 0) { printf("[AVISO] Nao ha livros para alterar.\n"); return; }

    printf("Digite o ID do livro a ser alterado: ");
    if (scanf("%d", &id_alterar) != 1) { printf("[ERRO] Entrada invalida.\n"); while (getchar() != '\n'); return; }
    while (getchar() != '\n');
    int pos = buscarPosicaoLivro(id_alterar);
    if (pos == -1) { printf("[AVISO] Livro com ID %d NAO encontrado.\n", id_alterar); return; }
    
    printf("\nLivro encontrado: %s - Estoque atual: %d\n", catalogo_livros[pos].titulo, catalogo_livros[pos].qtd_estoque);

    printf("Deseja alterar o estoque? (S/N): "); scanf(" %c", &resposta); while (getchar() != '\n'); 
    if (resposta == 'S' || resposta == 's') {
        printf("Digite a nova quantidade em estoque: ");
        if (scanf("%d", &novo_estoque) != 1) { printf("[ERRO] Entrada invalida.\n"); while (getchar() != '\n'); return; }
        while (getchar() != '\n');
        
        catalogo_livros[pos].qtd_estoque = novo_estoque;
        printf("[SUCESSO] Estoque alterado para %d.\n", novo_estoque);
    }
    printf("\n[SUCESSO] Alteracoes no Livro concluidas.\n");
}

void realizarEmprestimo() {
    int matricula_aluno, id_livro;
    printf("\n--- REALIZAR NOVO EMPRÉSTIMO ---\n");
    if (total_alunos == 0 || total_livros == 0) { printf("[AVISO] Necessário ter alunos e livros cadastrados.\n"); return; }

    printf("Digite a matricula do Aluno: ");
    if (scanf("%d", &matricula_aluno) != 1) { printf("[ERRO] Entrada invalida.\n"); while (getchar() != '\n'); return; }
    while (getchar() != '\n');
    int pos_aluno = buscarPosicaoAluno(matricula_aluno);
    if (pos_aluno == -1) { printf("[ERRO] Aluno nao encontrado.\n"); return; }

    if (biblioteca[pos_aluno].id_livro_emprestado != 0) {
        printf("[AVISO] Aluno %s já possui livro. Limite de %d livro(s) atingido.\n", biblioteca[pos_aluno].nome, max_livros_por_aluno);
        return;
    }
    
    printf("Digite o ID do Livro para Empréstimo: ");
    if (scanf("%d", &id_livro) != 1) { printf("[ERRO] Entrada invalida.\n"); while (getchar() != '\n'); return; }
    while (getchar() != '\n');
    
    int pos_livro = buscarPosicaoLivro(id_livro);
    if (pos_livro == -1) { printf("[ERRO] Livro NAO encontrado no catálogo.\n"); return; }

    if (catalogo_livros[pos_livro].qtd_estoque <= 0) {
        printf("[AVISO] O Livro '%s' está esgotado.\n", catalogo_livros[pos_livro].titulo);
        return;
    }

    biblioteca[pos_aluno].id_livro_emprestado = id_livro;
    catalogo_livros[pos_livro].qtd_estoque--; 

    printf("\n[SUCESSO] Empréstimo realizado!\n");
    printf("Aluno: %s | Livro: %s | Novo Estoque: %d\n", 
           biblioteca[pos_aluno].nome, catalogo_livros[pos_livro].titulo, catalogo_livros[pos_livro].qtd_estoque);
}

void realizarDevolucao() {
    int matricula_aluno;
    printf("\n--- REALIZAR DEVOLUÇÃO DE LIVRO ---\n");
    if (total_alunos == 0) { printf("[AVISO] Nao ha alunos cadastrados.\n"); return; }

    printf("Digite a matricula do Aluno que fará a devolução: ");
    if (scanf("%d", &matricula_aluno) != 1) { printf("[ERRO] Entrada invalida.\n"); while (getchar() != '\n'); return; }
    while (getchar() != '\n');
    
    int pos_aluno = buscarPosicaoAluno(matricula_aluno);
    if (pos_aluno == -1) { printf("[ERRO] Aluno nao encontrado.\n"); return; }
    
    int id_livro_devolvido = biblioteca[pos_aluno].id_livro_emprestado;

    if (id_livro_devolvido == 0) {
        printf("[AVISO] O Aluno %s não possui livros emprestados.\n", biblioteca[pos_aluno].nome);
        return;
    }
    
    int pos_livro = buscarPosicaoLivro(id_livro_devolvido);

    if (pos_livro != -1) {
        catalogo_livros[pos_livro].qtd_estoque++;
        printf("Livro devolvido: %s | Novo Estoque: %d\n", 
               catalogo_livros[pos_livro].titulo, catalogo_livros[pos_livro].qtd_estoque);
    } else {
        printf("[ALERTA CRÍTICO] O livro ID %d não foi encontrado no catálogo.\n", id_livro_devolvido);
    }
    
    biblioteca[pos_aluno].id_livro_emprestado = 0; 
    
    printf("\n[SUCESSO] Devolução concluída para o Aluno %s.\n", biblioteca[pos_aluno].nome);
}
