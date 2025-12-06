#include "biblioteca.h"

int menuPrincipal() {
    int opcao;
    printf("\n--- Sistema de Gerenciamento da Biblioteca ---\n");
    printf("1. Inserir Novo Aluno\n");
    printf("2. Remover Aluno\n");
    printf("3. Alterar Dados de Aluno\n");
    printf("4. Apresentar Todos os Alunos\n");
    printf("5. Cadastrar Livros\n"); 
    printf("6. Cadastrar Turmas\n"); 
    printf("0. Sair\n");
    printf("Escolha uma opcao: ");
    
    if (scanf("%d", &opcao) != 1) {
        while (getchar() != '\n');
        return -1;
    }
    while (getchar() != '\n'); 
    return opcao;
}

int main() {
    inicializarDados(); 
    int opcao;

    do {
        opcao = menuPrincipal(); 
      
        switch (opcao) {
            case 1:
                inserirAluno(); 
                break;
            case 2:
                removerAluno(); 
                break;
            case 3:
                alterarAluno(); 
                break;
            case 4:
                apresentaAlunos(); 
                break;
            case 5:
                cadastroSimples("LIVROS"); 
                break;
            case 6:
                cadastroSimples("TURMAS"); 
                break;
            case 0:
                printf("\nEncerrando o sistema! Obrigado por usar o programa.\n");
                break;
            default:
                printf("\n[ERRO] Opcao invalida. Tente novamente.\n");
                break;
        }

        if (opcao != 0) {
             printf("\nPressione ENTER para voltar ao menu principal...");
             getchar(); 
        }

    } while (opcao != 0);

    return 0;
}
