#include <iostream>
using namespace std;

struct Node {
    int valor;
    Node* esquerda;
    Node* direita;
    int altura;
};

int altura(Node* no) {
    return (no == NULL) ? 0 : no->altura;
}

Node* createNode(int valor) {
    Node* newNode = new Node;
    newNode -> valor = valor;
    newNode -> esquerda = NULL;
    newNode -> direita = NULL;
    return newNode;
}

int fatorBalanceamento(Node* no) {
    if (no == NULL) return 0;
    return altura(no->esquerda) - altura(no->direita);
}

Node* rotacaoDireita(Node* y) {
    Node* x = y->esquerda;
    Node* T2 = x->direita;

    x->direita = y;
    y->esquerda = T2;

    y->altura = max(altura(y->esquerda), altura(y->direita)) + 1;
    x->altura = max(altura(x->esquerda), altura(x->direita)) + 1;

    return x;
}

Node* rotacaoEsquerda(Node* x) {
    Node* y = x->direita;
    Node* T2 = y->esquerda;

    y->esquerda = x;
    x->direita = T2;

    x->altura = max(altura(x->esquerda), altura(x->direita)) + 1;
    y->altura = max(altura(y->esquerda), altura(y->direita)) + 1;

    return y;
}

Node* insert(Node* raiz, int valor) {
    if (raiz == NULL) return createNode(valor);

    if (valor < raiz -> valor) {
        raiz -> esquerda = insert(raiz -> esquerda, valor);
    }
    else if ( valor > raiz -> valor) {
        raiz -> direita = insert(raiz -> direita, valor);
    }

    return raiz;

    raiz->altura = max(altura(raiz->esquerda), altura(raiz->direita)) + 1;
    int balance = fatorBalanceamento(raiz);

    if (balance > 1 && valor < raiz->esquerda->valor)
        return rotacaoDireita(raiz);
    
    if (balance < -1 && valor > raiz->direita->valor)
        return rotacaoEsquerda(raiz);
    
    if (balance > 1 && valor > raiz->esquerda->valor) {
        raiz->esquerda = rotacaoEsquerda(raiz->esquerda);
        return rotacaoDireita(raiz);
    }

    if (balance < -1 && valor < raiz->direita->valor) {
        raiz->direita = rotacaoDireita(raiz->direita);
        return rotacaoEsquerda(raiz);
    }

    return raiz;
}

void emOrdem(Node* raiz) {
    if (raiz != NULL) {
        emOrdem(raiz->esquerda);
        cout << raiz->valor << " ";
        emOrdem(raiz->direita);
    }
}

int main() {
    Node* root = NULL;

    root = insert(root, 10);
    insert(root, 20);
    insert(root, 30);
    insert(root, 40);
    insert(root, 50);
    insert(root, 60);
    insert(root, 70);

    cout << "Árvore: ";
    emOrdem(root);
    cout << endl;

    return 0;
}
