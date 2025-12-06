#ifndef biblioteca_h
#define biblioteca_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define max_alunos 100 
#define max_livros_por_aluno 1 

typedef struct {
    int matricula;
    char nome[50];
    char turma[10];
    int livro_emprestado;
} Aluno;

void inicializarDados();
void apresentaAlunos();
void inserirAluno();
void removerAluno();
void alterarAluno();
void cadastroSimples(const char *tipo);

int buscarPosicao(int matricula_busca);
int buscarPorNome(const char *nome_busca);

#endif
