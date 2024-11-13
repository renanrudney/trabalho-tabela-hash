//Estrutura programa Tabela Hash - Professor Lucas.
#include <stdio.h>
#include <stdlib.h>

void adicionarContato() {
    printf("Funcao para adicionar contato.\n");
}

void buscarContato() {
    printf("Funcao para buscar contato.\n");
}

void removerContato() {
    printf("Funcao para remover contato.\n");
}

void exibirContatos() {
    printf("Funcao para exibir todos os contatos.\n");
}

int main() {
    int opcao;

    do {
        printf("\nEscolha uma opcao:\n");
        printf("1 - Adicionar contato\n");
        printf("2 - Buscar contato por nome\n");
        printf("3 - Remover contato\n");
        printf("4 - Exibir todos os contatos\n");
        printf("0 - Sair\n");
        printf("Digite uma opcao: ");
        
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                adicionarContato();
                break;
            case 2:
                buscarContato();
                break;
            case 3:
                removerContato();
                break;
            case 4:
                exibirContatos();
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
    } while (opcao != 0);

    return 0;
}
