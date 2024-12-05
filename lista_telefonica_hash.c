// Lista telefonica - Renan Rudney

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TABLE_SIZE 100

// Contato
typedef struct HashNode {
    char *nome;
    char *telefone;
    struct HashNode *proximo;
} HashNode;

typedef struct HashTable {
    HashNode *buckets[TABLE_SIZE];
} HashTable;

unsigned int calcularHash(const char *nome) {
    unsigned int hash_value = 0;
    while (*nome) {
        hash_value = (hash_value << 5) + *nome++;
    }
    return hash_value % TABLE_SIZE;
}

HashTable *inicializarTabela() {
    HashTable *tabela = (HashTable *)malloc(sizeof(HashTable));
    for (int i = 0; i < TABLE_SIZE; i++) {
        tabela->buckets[i] = NULL;
    }
    return tabela;
}

void adicionarContato(HashTable *tabela, const char *nome, const char *telefone) {
    clock_t inicio = clock();

    unsigned int indice = calcularHash(nome);
    HashNode *noAtual = tabela->buckets[indice];

    while (noAtual) {
        if (strcmp(noAtual->nome, nome) == 0) {
            printf("Contato com nome '%s' já existe! Atualizando o telefone.\n", nome);
            free(noAtual->telefone);
            noAtual->telefone = strdup(telefone);
            printf("Contato atualizado com sucesso.\n");
            printf("Tempo de inserção: %.2f ms\n", ((double)(clock() - inicio)) / CLOCKS_PER_SEC * 1000);
            return;
        }
        noAtual = noAtual->proximo;
    }

    HashNode *novoNo = (HashNode *)malloc(sizeof(HashNode));
    novoNo->nome = strdup(nome);
    novoNo->telefone = strdup(telefone);
    novoNo->proximo = tabela->buckets[indice];
    tabela->buckets[indice] = novoNo;

    printf("Contato '%s' adicionado com sucesso.\n", nome);
    printf("Tempo de inserção: %.2f ms\n", ((double)(clock() - inicio)) / CLOCKS_PER_SEC * 1000);
}


void buscarContato(HashTable *tabela, const char *nome) {
    clock_t inicio = clock();

    unsigned int indice = calcularHash(nome);
    HashNode *noAtual = tabela->buckets[indice];

    while (noAtual) {
        if (strcmp(noAtual->nome, nome) == 0) {
            printf("Tempo de busca: %.2f ms\n", ((double)(clock() - inicio)) / CLOCKS_PER_SEC * 1000);
            return noAtual->telefone;
        }
        noAtual = noAtual->proximo;
    }

    printf("Tempo de busca: %.2f ms\n", ((double)(clock() - inicio)) / CLOCKS_PER_SEC * 1000);
}

void removerContato(HashTable *tabela, const char *nome) {
    unsigned int indice = calcularHash(nome);
    HashNode *noAtual = tabela->buckets[indice];
    HashNode *anterior = NULL;

    while (noAtual) {
        if (strcmp(noAtual->nome, nome) == 0) {
            if (anterior == NULL) {
                tabela->buckets[indice] = noAtual->proximo;
            } else {
                anterior->proximo = noAtual->proximo;
            }
            free(noAtual->nome);
            free(noAtual->telefone);
            free(noAtual);
            printf("Contato '%s' removido com sucesso.\n", nome);
            return;
        }
        anterior = noAtual;
        noAtual = noAtual->proximo;
    }
    printf("Contato '%s' não encontrado.\n", nome);
}

void exibirContatos(HashTable *tabela) {
    int encontrados = 0;
    for (int i = 0; i < TABLE_SIZE; i++) {
        HashNode *noAtual = tabela->buckets[i];
        while (noAtual) {
            encontrados++;
            printf("Nome: %s\nTelefone: %s\n", noAtual->nome, noAtual->telefone);
            noAtual = noAtual->proximo;
        }
    }
    if (encontrados == 0) {
        printf("A tabela está vazia!\n");
    }
}

void liberarTabela(HashTable *tabela) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        HashNode *noAtual = tabela->buckets[i];
        while (noAtual) {
            HashNode *temp = noAtual;
            noAtual = noAtual->proximo;
            free(temp->nome);
            free(temp->telefone);
            free(temp);
        }
    }
    free(tabela);
}

int main() {
    int opcao;
    HashTable *tabelaHash = inicializarTabela();
    char nome[50];
    char telefone[20];

    do {
        printf("\nEscolha uma opção:\n");
        printf("1 - Adicionar contato\n");
        printf("2 - Buscar contato por nome\n");
        printf("3 - Remover contato\n");
        printf("4 - Exibir todos os contatos\n");
        printf("0 - Sair\n");
        printf("Digite uma opção: ");

        scanf("%d", &opcao);
        while (getchar() != '\n');

        switch (opcao) {
            case 1:
                printf("\nDigite o nome do contato: ");
                fgets(nome, sizeof(nome), stdin);
                nome[strcspn(nome, "\n")] = '\0';
                printf("Digite o telefone do contato: ");
                fgets(telefone, sizeof(telefone), stdin);
                telefone[strcspn(telefone, "\n")] = '\0';
                adicionarContato(tabelaHash, nome, telefone);
                break;
            case 2:
                printf("\nDigite o nome do contato: ");
                fgets(nome, sizeof(nome), stdin);
                nome[strcspn(nome, "\n")] = '\0';
                char *resultado = buscarContato(tabelaHash, nome);
                if (resultado) {
                    printf("Telefone de %s: %s\n", nome, resultado);
                } else {
                    printf("Contato '%s' não encontrado.\n", nome);
                }
                break;
            case 3:
                printf("\nDigite o nome do contato a ser removido: ");
                fgets(nome, sizeof(nome), stdin);
                nome[strcspn(nome, "\n")] = '\0';
                removerContato(tabelaHash, nome);
                break;
            case 4:
                exibirContatos(tabelaHash);
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
        }
    } while (opcao != 0);

    liberarTabela(tabelaHash);
    return 0;
}
