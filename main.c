#include "biblioteca.h" 

int menuPrincipal() {
    int opcao;
    printf("\n--- Sistema de Gerenciamento de Biblioteca---\n");
    printf("--- ALUNOS ---\n");
    printf("1. ➕ Inserir Novo Aluno\n");
    printf("2. ❌ Remover Aluno\n");
    printf("3. ✍️ Alterar Dados de Aluno\n");
    printf("4. 📋 Apresentar Todos os Alunos\n");
    printf("-----------------------------------\n");
    printf("--- TURMAS ---\n");
    printf("5. ➕ Inserir Nova Turma\n");
    printf("6. ❌ Remover Turma\n");
    printf("7. ✍️ Alterar Turma\n");
    printf("8. 📋 Apresentar Turmas\n");
    printf("-----------------------------------\n");
    printf("--- LIVROS ---\n");
    printf("9. ➕ Inserir Novo Livro\n");
    printf("10. ❌ Remover Livro\n");
    printf("11. ✍️ Alterar Livro\n");
    printf("12. 📋 Apresentar Catálogo de Livros\n");
    printf("-----------------------------------\n");
    printf("--- EMPRESTIMO / DEVOLUCAO---\n");
    printf("13. 📚 Realizar Empréstimo\n"); 
    printf("14. 🔙 Realizar Devolução\n"); 
    printf("-----------------------------------\n");
    printf("0. SAIR\n");
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
            case 6: removerTurma(); break; 
            case 7: alterarTurma(); break; 
            case 8: apresentaTurmas(); break;
            
            case 9: inserirLivro(); break;
            case 10: removerLivro(); break;
            case 11: alterarLivro(); break;
            case 12: apresentaLivros(); break;
        
            case 13: realizarEmprestimo(); break;
            case 14: realizarDevolucao(); break;

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
