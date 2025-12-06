#ifndef biblioteca_h
#define biblioteca_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define max_alunos 100 
#define max_turmas 20
#define max_livros 500
#define max_livros_por_aluno 1 

typedef struct {
    int matricula;
    char nome[50];
    char codigo_turma[10];
    int id_livro_emprestado;
} Aluno;

typedef struct {
    char codigo[10];
    char nome_curso[40];
    int limite_alunos;
} Turma;

typedef struct {
    int id;
    char titulo[60];
    char autor[50];
    int qtd_estoque;
} Livro;

void inicializarDados();

void apresentaAlunos();
void inserirAluno();
void removerAluno();
void alterarAluno();
int buscarPosicaoAluno(int matricula_busca);

void inserirLivro();
void apresentaLivros();
int buscarPosicaoLivro(int id_busca);

#endif
