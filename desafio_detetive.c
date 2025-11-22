#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NOME 50
#define MAX_SUSPEITOS 5
#define TAMANHO_HASH 10

// ========== ESTRUTURAS ==========

// Estrutura para nó da árvore binária (mansão)
typedef struct NoSala {
    char nome[MAX_NOME];
    struct NoSala* esquerda;
    struct NoSala* direita;
} NoSala;

// Estrutura para nó da árvore de busca (pistas)
typedef struct NoPista {
    char pista[MAX_NOME];
    struct NoPista* esquerda;
    struct NoPista* direita;
} NoPista;

// Estrutura para entrada da tabela hash
typedef struct EntradaHash {
    char pista[MAX_NOME];
    char suspeito[MAX_NOME];
    struct EntradaHash* proximo;
} EntradaHash;

// ========== VARIÁVEIS GLOBAIS ==========
NoSala* raizMansao = NULL;
NoPista* raizPistas = NULL;
EntradaHash* tabelaHash[TAMANHO_HASH];
int nivel = 0;

// ========== FUNÇÕES AUXILIARES ==========

// Função hash simples
int funcaoHash(char* chave) {
    int hash = 0;
    for (int i = 0; chave[i] != '\0'; i++) {
        hash += chave[i];
    }
    return hash % TAMANHO_HASH;
}

// ========== NÍVEL NOVATO - ÁRVORE BINÁRIA ==========

NoSala* criarSala(char* nome) {
    NoSala* novaSala = (NoSala*)malloc(sizeof(NoSala));
    strcpy(novaSala->nome, nome);
    novaSala->esquerda = NULL;
    novaSala->direita = NULL;
    return novaSala;
}

void construirMansao() {
    // Criando a estrutura da mansão
    raizMansao = criarSala("Hall de Entrada");
    
    raizMansao->esquerda = criarSala("Biblioteca");
    raizMansao->direita = criarSala("Sala de Estar");
    
    raizMansao->esquerda->esquerda = criarSala("Escritorio");
    raizMansao->esquerda->direita = criarSala("Quarto dos Fundos");
    
    raizMansao->direita->esquerda = criarSala("Cozinha");
    raizMansao->direita->direita = criarSala("Quarto Principal");
    
    raizMansao->esquerda->esquerda->esquerda = criarSala("Porão");
    raizMansao->direita->direita->direita = criarSala("Sótão");
}

void explorarMansao() {
    NoSala* atual = raizMansao;
    char opcao;
    
    printf("\n=== EXPLORANDO A MANSÃO ===\n");
    printf("Você está no: %s\n", atual->nome);
    
    while (1) {
        printf("\nOpções:\n");
        if (atual->esquerda) printf("e - Ir para esquerda\n");
        if (atual->direita) printf("d - Ir para direita\n");
        printf("s - Sair da exploração\n");
        printf("Escolha: ");
        
        scanf(" %c", &opcao);
        
        switch (opcao) {
            case 'e':
                if (atual->esquerda) {
                    atual = atual->esquerda;
                    printf("\nVocê entrou na: %s\n", atual->nome);
                    
                    // Nivel Aventureiro - encontrar pistas em algumas salas
                    if (nivel >= 2) {
                        if (strcmp(atual->nome, "Biblioteca") == 0) {
                            inserirPista("Livro Manchado");
                            printf("🔍 Pista encontrada: Livro Manchado\n");
                        }
                        else if (strcmp(atual->nome, "Escritorio") == 0) {
                            inserirPista("Carta Rasgada");
                            printf("🔍 Pista encontrada: Carta Rasgada\n");
                        }
                        else if (strcmp(atual->nome, "Cozinha") == 0) {
                            inserirPista("Faca Suja");
                            printf("🔍 Pista encontrada: Faca Suja\n");
                        }
                        else if (strcmp(atual->nome, "Porão") == 0) {
                            inserirPista("Pegadas");
                            printf("🔍 Pista encontrada: Pegadas\n");
                        }
                    }
                } else {
                    printf("Não há caminho à esquerda!\n");
                }
                break;
                
            case 'd':
                if (atual->direita) {
                    atual = atual->direita;
                    printf("\nVocê entrou na: %s\n", atual->nome);
                    
                    // Nivel Aventureiro - encontrar pistas em algumas salas
                    if (nivel >= 2) {
                        if (strcmp(atual->nome, "Sala de Estar") == 0) {
                            inserirPista("Almofada Revirada");
                            printf("🔍 Pista encontrada: Almofada Revirada\n");
                        }
                        else if (strcmp(atual->nome, "Quarto Principal") == 0) {
                            inserirPista("Gaveta Aberta");
                            printf("🔍 Pista encontrada: Gaveta Aberta\n");
                        }
                        else if (strcmp(atual->nome, "Sótão") == 0) {
                            inserirPista("Baú Violado");
                            printf("🔍 Pista encontrada: Baú Violado\n");
                        }
                    }
                } else {
                    printf("Não há caminho à direita!\n");
                }
                break;
                
            case 's':
                printf("Saindo da exploração...\n");
                return;
                
            default:
                printf("Opção inválida!\n");
        }
    }
}

// ========== NÍVEL AVENTUREIRO - ÁRVORE DE BUSCA ==========

NoPista* inserirPistaRecursivo(NoPista* raiz, char* pista) {
    if (raiz == NULL) {
        NoPista* novoPista = (NoPista*)malloc(sizeof(NoPista));
        strcpy(novoPista->pista, pista);
        novoPista->esquerda = NULL;
        novoPista->direita = NULL;
        return novoPista;
    }
    
    if (strcmp(pista, raiz->pista) < 0) {
        raiz->esquerda = inserirPistaRecursivo(raiz->esquerda, pista);
    } else if (strcmp(pista, raiz->pista) > 0) {
        raiz->direita = inserirPistaRecursivo(raiz->direita, pista);
    }
    
    return raiz;
}

void inserirPista(char* pista) {
    raizPistas = inserirPistaRecursivo(raizPistas, pista);
    
    // Nivel Mestre - associar pista a suspeito
    if (nivel >= 3) {
        char* suspeito;
        if (strcmp(pista, "Livro Manchado") == 0 || strcmp(pista, "Carta Rasgada") == 0) {
            suspeito = "Professor Johnson";
        }
        else if (strcmp(pista, "Faca Suja") == 0 || strcmp(pista, "Almofada Revirada") == 0) {
            suspeito = "Chef Maria";
        }
        else if (strcmp(pista, "Pegadas") == 0 || strcmp(pista, "Gaveta Aberta") == 0) {
            suspeito = "Mordomo James";
        }
        else {
            suspeito = "Sra. Wilson";
        }
        
        inserirNaHash(pista, suspeito);
    }
}

void exibirPistasEmOrdem(NoPista* raiz) {
    if (raiz != NULL) {
        exibirPistasEmOrdem(raiz->esquerda);
        printf("- %s\n", raiz->pista);
        exibirPistasEmOrdem(raiz->direita);
    }
}

void listarPistas() {
    printf("\n=== PISTAS COLETADAS ===\n");
    if (raizPistas == NULL) {
        printf("Nenhuma pista coletada ainda.\n");
    } else {
        exibirPistasEmOrdem(raizPistas);
    }
}

// ========== NÍVEL MESTRE - TABELA HASH ==========

void inicializarHash() {
    for (int i = 0; i < TAMANHO_HASH; i++) {
        tabelaHash[i] = NULL;
    }
}

void inserirNaHash(char* pista, char* suspeito) {
    int indice = funcaoHash(pista);
    
    EntradaHash* novaEntrada = (EntradaHash*)malloc(sizeof(EntradaHash));
    strcpy(novaEntrada->pista, pista);
    strcpy(novaEntrada->suspeito, suspeito);
    novaEntrada->proximo = tabelaHash[indice];
    tabelaHash[indice] = novaEntrada;
}

void exibirAssociacoes() {
    printf("\n=== ASSOCIAÇÕES PISTA → SUSPEITO ===\n");
    
    for (int i = 0; i < TAMANHO_HASH; i++) {
        EntradaHash* atual = tabelaHash[i];
        while (atual != NULL) {
            printf("🔍 %s → %s\n", atual->pista, atual->suspeito);
            atual = atual->proximo;
        }
    }
}

void analisarSuspeitos() {
    char suspeitos[MAX_SUSPEITOS][MAX_NOME] = {"Professor Johnson", "Chef Maria", "Mordomo James", "Sra. Wilson", "Desconhecido"};
    int contador[MAX_SUSPEITOS] = {0};
    
    printf("\n=== ANÁLISE DOS SUSPEITOS ===\n");
    
    for (int i = 0; i < TAMANHO_HASH; i++) {
        EntradaHash* atual = tabelaHash[i];
        while (atual != NULL) {
            for (int j = 0; j < MAX_SUSPEITOS; j++) {
                if (strcmp(atual->suspeito, suspeitos[j]) == 0) {
                    contador[j]++;
                    break;
                }
            }
            atual = atual->proximo;
        }
    }
    
    // Exibir contagem
    for (int i = 0; i < MAX_SUSPEITOS; i++) {
        if (contador[i] > 0) {
            printf("%s: %d pista(s)\n", suspeitos[i], contador[i]);
        }
    }
    
    // Encontrar suspeito mais citado
    int maxPistas = 0, suspeito_principal = -1;
    for (int i = 0; i < MAX_SUSPEITOS; i++) {
        if (contador[i] > maxPistas) {
            maxPistas = contador[i];
            suspeito_principal = i;
        }
    }
    
    if (suspeito_principal != -1) {
        printf("\n🎯 PRINCIPAL SUSPEITO: %s (%d pistas)\n", 
               suspeitos[suspeito_principal], maxPistas);
    }
}

// ========== MENUS ==========

void exibirMenuNivel() {
    printf("\n========================================\n");
    printf("    🕵️ DETECTIVE QUEST 🕵️\n");
    printf("========================================\n");
    printf("Escolha o nível do desafio:\n\n");
    printf("1 - 🟢 NOVATO: Navegação pela mansão\n");
    printf("2 - 🟡 AVENTUREIRO: + Coleta de pistas\n");
    printf("3 - 🔴 MESTRE: + Análise de suspeitos\n");
    printf("0 - Sair\n");
    printf("========================================\n");
    printf("Escolha: ");
}

void exibirMenuJogo() {
    printf("\n=== DETECTIVE QUEST - NÍVEL ");
    if (nivel == 1) printf("NOVATO ===\n");
    else if (nivel == 2) printf("AVENTUREIRO ===\n");
    else printf("MESTRE ===\n");
    
    printf("1 - Explorar mansão\n");
    
    if (nivel >= 2) {
        printf("2 - Listar pistas coletadas\n");
    }
    
    if (nivel >= 3) {
        printf("3 - Ver associações pista → suspeito\n");
        printf("4 - Analisar suspeitos\n");
    }
    
    printf("0 - Voltar ao menu principal\n");
    printf("Escolha: ");
}

// ========== MAIN ==========

int main() {
    int opcaoNivel, opcaoJogo;
    
    // Inicializar estruturas
    construirMansao();
    inicializarHash();
    
    while (1) {
        exibirMenuNivel();
        scanf("%d", &opcaoNivel);
        
        if (opcaoNivel == 0) {
            printf("Obrigado por jogar Detective Quest!\n");
            break;
        }
        
        if (opcaoNivel < 1 || opcaoNivel > 3) {
            printf("Opção inválida!\n");
            continue;
        }
        
        nivel = opcaoNivel;
        
        // Menu do jogo
        while (1) {
            exibirMenuJogo();
            scanf("%d", &opcaoJogo);
            
            if (opcaoJogo == 0) {
                break;
            }
            
            switch (opcaoJogo) {
                case 1:
                    explorarMansao();
                    break;
                    
                case 2:
                    if (nivel >= 2) {
                        listarPistas();
                    } else {
                        printf("Opção não disponível neste nível!\n");
                    }
                    break;
                    
                case 3:
                    if (nivel >= 3) {
                        exibirAssociacoes();
                    } else {
                        printf("Opção não disponível neste nível!\n");
                    }
                    break;
                    
                case 4:
                    if (nivel >= 3) {
                        analisarSuspeitos();
                    } else {
                        printf("Opção não disponível neste nível!\n");
                    }
                    break;
                    
                default:
                    printf("Opção inválida!\n");
            }
        }
    }
    
    return 0;
}
