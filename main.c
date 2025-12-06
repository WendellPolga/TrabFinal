#include "biblioteca.h" 

int menuPrincipal() {
    int opcao;
    printf("\n--- Sistema de Gerenciamento da Biblioteca ---\n");
    printf("--- ALUNOS ---\n");
    printf("1. Inserir Novo Aluno\n");
    printf("2. Remover Aluno\n");
    printf("3. Alterar Dados de Aluno\n");
    printf("4. Apresentar Todos os Alunos\n");
    printf("--- TURMAS E LIVROS ---\n");
    printf("5. Cadastrar Nova Turma\n");
    printf("6. Apresentar Turmas Cadastradas\n");
    printf("7. Cadastrar Novo Livro\n");
    printf("8. Apresentar Catálogo de Livros\n");
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
            case 1: inserirAluno(); break; 
            case 2: removerAluno(); break;
            case 3: alterarAluno(); break; 
            case 4: apresentaAlunos(); break; 
            
            case 5: inserirTurma(); break;
            case 6: apresentaTurmas(); break; 
            
            case 7: inserirLivro(); break;
            case 8: apresentaLivros(); break; 

            case 0:
                printf("\nEncerrando o Sistema.\n");
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
