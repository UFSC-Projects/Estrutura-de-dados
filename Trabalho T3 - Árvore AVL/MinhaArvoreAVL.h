#ifndef MINHA_ARVORE_AVL_HPP
#define MINHA_ARVORE_AVL_HPP

#include "ArvoreBinariaDeBusca.h"

/**
 * @brief Representa uma árvore AVL.
 *
 * @tparam T O tipo de dado guardado na árvore.
 */
template <typename T>
class MinhaArvoreAVL final : public ArvoreBinariaDeBusca<T>
{
    virtual ~MinhaArvoreAVL(){
        limpar(this->raiz);
    };


    void limpar(Nodo<T>* nodo) {
        if (!nodo) return;
        limpar(nodo->filhoEsquerda);
        limpar(nodo->filhoDireita);
        delete nodo;
    }

    /**
     * @brief Verifica se a arvore esta vazia
     * @return Verdade se a arvore esta vazia.
     */
    virtual bool vazia() const
    {
        if(this->raiz == nullptr) {
            return true;
        }
        return false;
    };

    /**
     * @brief Retornar quantidade de chaves na arvore
     * @return Numero natural que representa a quantidade de chaves na arvore
     */
    virtual int quantidade() const
    {
        return this->quantidadeRecu(this->raiz);
    };

    virtual int quantidadeRecu(Nodo<T>* Nodo) const {
        if(Nodo == nullptr) return 0;

        int quantidade = 1 + quantidadeRecu(Nodo->filhoDireita) + quantidadeRecu(Nodo->filhoEsquerda);

        return quantidade;

    }

    /**
     * @brief Verifica se a arvore contem uma chave
     * @param chave chave a ser procurada na arvore
     * @return Verdade se a arvore contem a chave
     */
    virtual bool contem(T chave) const
    {
        Nodo<T>* Nodo = getNodoRec(this->raiz, chave);

        if(Nodo == nullptr) return false;

        if(Nodo->chave == chave) return true;
        
        return false;
    };

     virtual Nodo<T>* getNodoRec(Nodo<T>* Nodo, T chave) const {


        if(Nodo == nullptr) return nullptr;

        if(Nodo->chave == chave) return Nodo;
        
        if(chave < Nodo->chave) return getNodoRec(Nodo->filhoEsquerda, chave);

        return getNodoRec(Nodo->filhoDireita, chave);


    }

    /**
     * @brief Retorna a altura da (sub)arvore
     * @param chave chave que é raiz da (sub)arvore cuja altura queremos.
     * @return Numero inteiro representando a altura da (subarvore). Se chave nao esta na arvore, retorna std::nullopt
     */
    virtual std::optional<int> altura(T chave) const
    {
        Nodo<T>* Nodo = getNodoRec(this->raiz, chave);

        if(Nodo != nullptr) return Nodo->altura;

        return std::nullopt;
    };

    virtual int calcAltura(Nodo<T>* Nodo) const {
        if(Nodo == nullptr) return -1;

        int altura =  1 + std::max(calcAltura(Nodo->filhoEsquerda), calcAltura(Nodo->filhoDireita));

        return altura;
    }


    virtual int calcFatorBalanceamento(Nodo<T>* Nodo) const {
        if(Nodo == nullptr) return 0;

        return calcAltura(Nodo->filhoEsquerda) - calcAltura(Nodo->filhoDireita);
    }

    /**
     * @brief Insere uma chave na arvore
     * @param chave chave a ser inserida
     */
    virtual void inserir(T chave){
        
        this->raiz = inserirRec(this->raiz, chave);
    };


    virtual Nodo<T>* inserirRec(Nodo<T>* NodoAtual, T chave) {

        if(NodoAtual == nullptr) {
            return new Nodo<T> {chave, 0, nullptr, nullptr};

        }


        if(chave < NodoAtual->chave) {
            NodoAtual->filhoEsquerda = inserirRec(NodoAtual->filhoEsquerda, chave);
        } else {
            NodoAtual->filhoDireita = inserirRec(NodoAtual->filhoDireita, chave);
        }

        NodoAtual->altura = calcAltura(NodoAtual);

        int fatorBalanceamento = calcFatorBalanceamento(NodoAtual);

        if(fatorBalanceamento > 1 && chave < NodoAtual->filhoEsquerda->chave) {
            return rotacaoDireitaSimples(NodoAtual);
        }


        if(fatorBalanceamento < -1 && chave > NodoAtual->filhoDireita->chave) {
            return rotacaoEsquerdaSimples(NodoAtual);
        }

        if(fatorBalanceamento > 1 && chave > NodoAtual->filhoEsquerda->chave) {
            NodoAtual->filhoEsquerda = rotacaoEsquerdaSimples(NodoAtual->filhoEsquerda);
            return rotacaoDireitaSimples(NodoAtual);
        } 

        if(fatorBalanceamento < -1 && chave < NodoAtual->filhoDireita->chave) {
            NodoAtual->filhoDireita = rotacaoDireitaSimples(NodoAtual->filhoDireita);
            return rotacaoEsquerdaSimples(NodoAtual);
        }

        return NodoAtual;
    }


    virtual Nodo<T>* rotacaoDireitaSimples(Nodo<T>* NodoAtual) {

        Nodo<T> * novoNodoPai = NodoAtual->filhoEsquerda;
        Nodo<T> * AntigoFilhoDireitaNovoPai = novoNodoPai->filhoDireita;
        

        novoNodoPai->filhoDireita = NodoAtual;
        NodoAtual->filhoEsquerda = AntigoFilhoDireitaNovoPai;

        NodoAtual->altura = calcAltura(NodoAtual);
        novoNodoPai->altura = calcAltura(novoNodoPai);

        return novoNodoPai;
        
    }

    virtual Nodo<T>* rotacaoEsquerdaSimples(Nodo<T>* NodoAtual) {

        Nodo<T> * novoNodoPai = NodoAtual->filhoDireita;
        Nodo<T> * AntigoFilhoEsquerdaNovoPai = novoNodoPai->filhoEsquerda;


        novoNodoPai->filhoEsquerda = NodoAtual;
        NodoAtual->filhoDireita = AntigoFilhoEsquerdaNovoPai;

        novoNodoPai->altura = calcAltura(novoNodoPai);
        NodoAtual->altura = calcAltura(NodoAtual);

        return novoNodoPai;
    }

    /**
     * @brief Remove uma chave da arvore
     * @param chave chave a removida
     */
    virtual void remover(T chave){
        
        this->raiz = removerRec(this->raiz, chave);
    };


    virtual Nodo<T>* removerRec(Nodo<T>* NodoAtual, T chave) {

        if(NodoAtual == nullptr) return nullptr;
        
        if(chave < NodoAtual->chave) {
            NodoAtual->filhoEsquerda = removerRec(NodoAtual->filhoEsquerda, chave);
        } else if (chave > NodoAtual->chave) {
            NodoAtual->filhoDireita = removerRec(NodoAtual->filhoDireita, chave);
        } else if (chave == NodoAtual->chave) {

            if(NodoAtual->filhoEsquerda == nullptr && NodoAtual->filhoDireita == nullptr) {
                delete NodoAtual;
                return nullptr;
            }

            if(NodoAtual->filhoDireita == nullptr) {

                Nodo<T>* aux = NodoAtual->filhoEsquerda;
                Nodo<T>* NodoPai = getPaiNodo(this->raiz, chave);
                if(NodoPai->filhoEsquerda == NodoAtual) NodoPai->filhoEsquerda = aux;
                delete NodoAtual;
                return aux;     
            }

            if(NodoAtual->filhoEsquerda == nullptr) {
                Nodo<T>* aux = NodoAtual->filhoDireita;
                Nodo<T>* NodoPai = getPaiNodo(this->raiz, chave);
                if(NodoPai->filhoEsquerda == NodoAtual) NodoPai->filhoEsquerda = aux;
                delete NodoAtual;
                return aux;
            }

            if(NodoAtual->filhoDireita != nullptr && NodoAtual->filhoEsquerda != nullptr) {

                Nodo<T>* aux = getMenorNodo(NodoAtual->filhoDireita);
                NodoAtual->chave = aux->chave;
                NodoAtual->filhoDireita = removerRec(NodoAtual->filhoDireita, aux->chave);
                return NodoAtual;

            }
        }

        NodoAtual->altura = calcAltura(NodoAtual);

        int fatorBalanceamento = calcFatorBalanceamento(NodoAtual);

        if (fatorBalanceamento > 1 && calcFatorBalanceamento(NodoAtual->filhoEsquerda) >= 0) {
            return rotacaoDireitaSimples(NodoAtual);
        }

        if (fatorBalanceamento < -1 && calcFatorBalanceamento(NodoAtual->filhoDireita) <= 0) {
            return rotacaoEsquerdaSimples(NodoAtual);
        }

        if (fatorBalanceamento > 1 && calcFatorBalanceamento(NodoAtual->filhoEsquerda) < 0) {
            NodoAtual->filhoEsquerda = rotacaoEsquerdaSimples(NodoAtual->filhoEsquerda);
            return rotacaoDireitaSimples(NodoAtual);
        }

        if (fatorBalanceamento < -1 && calcFatorBalanceamento(NodoAtual->filhoDireita) > 0) {
            NodoAtual->filhoDireita = rotacaoDireitaSimples(NodoAtual->filhoDireita);
            return rotacaoEsquerdaSimples(NodoAtual);
        }
            
        return NodoAtual;
    }

    virtual Nodo<T>* getMenorNodo(Nodo<T>* NodoAtual) const {
        if(NodoAtual->filhoEsquerda == nullptr) return NodoAtual;

        return getMenorNodo(NodoAtual->filhoEsquerda);
    }

    virtual Nodo<T>* getPaiNodo (Nodo<T>* NodoAtual,T chave) const {


        if(NodoAtual->filhoDireita->chave == chave) return NodoAtual;

        if(NodoAtual->filhoEsquerda->chave == chave) return NodoAtual;

        if(chave > NodoAtual->chave) {
            return getPaiNodo(NodoAtual->filhoDireita, chave);
        } else {
            return getPaiNodo(NodoAtual->filhoEsquerda, chave);
        }
    }

    /**
     * @brief Busca a chave do filho a esquerda de uma (sub)arvore
     * @param chave chave da arvore que eh pai do filho a esquerda
     * @return Chave do filho a esquerda. Se chave nao esta na arvore, retorna std::nullopt
     */
    virtual std::optional<T> filhoEsquerdaDe(T chave) const
    {
        if(this->raiz == nullptr) return std::nullopt;

        Nodo<T>* Nodo = getNodoRec(this->raiz, chave);

        if(Nodo == nullptr) return std::nullopt;

        if(Nodo->filhoEsquerda == nullptr) return std::nullopt;

        return Nodo->filhoEsquerda->chave;
    };

    /**
     * @brief Busca a chave do filho a direita de uma (sub)arvore
     * @param chave chave da arvore que eh pai do filho a direita
     * @return Chave do filho a direita. Se chave nao esta na arvore, retorna nullptr
     */
    virtual std::optional<T> filhoDireitaDe(T chave) const
    {
        if(this->raiz == nullptr) return std::nullopt;

        Nodo<T>* Nodo = getNodoRec(this->raiz, chave);

        if(Nodo == nullptr) return std::nullopt;

        if(Nodo->filhoDireita == nullptr) return std::nullopt;

        return Nodo->filhoDireita->chave;
    };

    /**
     * @brief Lista chaves visitando a arvore em ordem
     * @return Lista encadeada contendo as chaves em ordem.
     */
    virtual ListaEncadeadaAbstrata<T> *emOrdem() const
    {
        ListaEncadeadaAbstrata<T>* lista = new MinhaListaEncadeada<T>();
        emOrdemRec(this->raiz, lista);
        return lista;
    };

    virtual void emOrdemRec(Nodo<T>* Nodo, ListaEncadeadaAbstrata<T>* lista) const {

        if(Nodo == nullptr) return;

        emOrdemRec(Nodo->filhoEsquerda, lista);
        lista->inserirNoFim(Nodo->chave);
        emOrdemRec(Nodo->filhoDireita, lista);
    }

    /**
     * @brief Lista chaves visitando a arvore em pre-ordem
     * @return Lista encadeada contendo as chaves em pre-ordem.
     */
    virtual ListaEncadeadaAbstrata<T> *preOrdem() const
    {
        ListaEncadeadaAbstrata<T>* lista = new MinhaListaEncadeada<T>();
        preOrdemRec(this->raiz, lista);
        return lista;
    };

    void preOrdemRec(Nodo<T>* Nodo, ListaEncadeadaAbstrata<T>* lista) const {
        if (Nodo == nullptr) return;

        lista->inserirNoFim(Nodo->chave);         
        preOrdemRec(Nodo->filhoEsquerda, lista); 
        preOrdemRec(Nodo->filhoDireita, lista); 
    }

    /**
     * @brief Lista chaves visitando a arvore em pos-ordem
     * @return Lista encadeada contendo as chaves em pos ordem.
     */
    virtual ListaEncadeadaAbstrata<T> *posOrdem() const
    {
        ListaEncadeadaAbstrata<T>* lista = new MinhaListaEncadeada<T>();
        posOrdemRec(this->raiz, lista);
        return lista;
    };

    virtual void posOrdemRec(Nodo<T>* Nodo, ListaEncadeadaAbstrata<T>* lista) const {
        if (Nodo == nullptr) return;

        posOrdemRec(Nodo->filhoEsquerda, lista); 
        posOrdemRec(Nodo->filhoDireita, lista); 
        lista->inserirNoFim(Nodo->chave);
    }
};

#endif