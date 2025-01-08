#ifndef DEC0006_MINHA_LISTA_ENCADEADA_H
#define DEC0006_MINHA_LISTA_ENCADEADA_H

#include <cstddef>
// std::size_t

#include "Elemento.h"
// Elemento
#include "ListaEncadeadaAbstrata.h"
#include "excecoes.h"
// ExcecaoDadoInexistente
// ExcecaoListaEncadeadaVazia
// ExcecaoNaoImplementado
// ExcecaoPosicaoInvalida

/**
 * @brief Uma lista encadeada de dados.
 * 
 * @tparam T O tipo dos dados armazenados na lista.
 */
template<typename T>
class MinhaListaEncadeada: public ListaEncadeadaAbstrata<T>
{
    /**
     * @brief Destrutor. Destroi todos os elementos da lista
     */
    virtual ~MinhaListaEncadeada(){
        while(this->_tamanho != 0) {
            this->removerDoInicio();
        }
    }

    /**
     * @brief Obtém a quantidade de itens na lista.
     * 
     * @return Um inteiro maior ou igual a 0.
     */
    virtual std::size_t tamanho() const
    {
        //substitua a linha abaixo pelo algoritmo esperado
        return this->_tamanho;
    };
    
    /**
     * @brief Indica se há algum item na lista ou não.
     * 
     * @return false se houver algum item na lista; true caso contrário.
     */
    virtual bool vazia() const 
    {
        if(this->_tamanho == 0) return true;
        else return false;
    };

    /**
     * @brief Obtém a posição de um item na lista. Lança
     * ExcecaoListaEncadeadaVazia caso a lista esteja vazia ou
     * ExcecaoDadoInexistente caso o item não esteja contido na lista.
     * 
     * @param dado O item cuja posição deseja-se obter.
     * @return Um inteiro na faixa [0, tamanho); se houver mais que um mesmo
     * item na lista, a posição da primeira ocorrência.
     */
    virtual std::size_t posicao(T dado) const 
    {
        //substitua a linha abaixo pelo algoritmo esperado

        if(this->vazia()) throw ExcecaoListaEncadeadaVazia();


        Elemento<T> * eleAtual  = this->_primeiro;
    

        for(int i = 0; eleAtual != nullptr; i++) {

            if(eleAtual->dado == dado) {
                return i;
            }

            eleAtual = eleAtual->proximo;
        }


        throw ExcecaoDadoInexistente();
    };
    
    /**
     * @brief Indica se um dado item está contido na lista ou não.
     * 
     * @param dado O item sendo buscado.
     * @return true se o item está contido na lista; false caso contrário.
     */
    virtual bool contem(T dado) const
    {

        Elemento<T> * eleAtual  = this->_primeiro;

        for(int i = 0; eleAtual != nullptr; i++) {

            if(eleAtual->dado == dado) {
                return true;
            }

            eleAtual = eleAtual->proximo;
        }

        return false;
    };

    /**
     * @brief Insere um item no início da lista.
     * 
     * @param dado O item sendo inserido.
     */
    virtual void inserirNoInicio(T dado) 
    {
        
        Elemento<T>* novo = new Elemento<T>(dado);
        
        novo->proximo = this->_primeiro;

        this->_primeiro = novo;

        this->_tamanho++;

    };

    /**
     * @brief Insere um item em uma posição específica da lista. Lança
     * ExcecaoPosicaoInvalida caso a posição não esteja na faixa
     * [0, tamanho].
     * 
     * @param posicao Um inteiro dentro da faixa [0, tamanho]. Ao se inserir em
     * uma posição já ocupada, a posição do item que já estava naquela posição
     * será posicao + 1; inserir-se na posicao tamanho significa inserir-se no
     * fim da lista.
     * @param dado O item sendo inserido.
     */
    virtual void inserir(std::size_t posicao, T dado)
    {

        if(posicao > this->_tamanho) throw ExcecaoPosicaoInvalida();
            
        if(posicao == 0) {
            this->inserirNoInicio(dado);
            return;
        }

        if(posicao == this->_tamanho) {
            this->inserirNoFim(dado);
            return;
        }

        Elemento<T>* novo = new Elemento<T>(dado);

        Elemento<T> * eleAtual  = this->_primeiro;

        for (std::size_t i = 0; i < posicao - 1; i++) {
            eleAtual = eleAtual->proximo;
        }
        
        novo->proximo = eleAtual->proximo;
        eleAtual->proximo = novo;

        this->_tamanho++;
        
    };


    /**
     * @brief Insere um item no fim da lista.
     * 
     * @param dado O item sendo inserido.
     */
    virtual void inserirNoFim(T dado)
    {

        if(this->_primeiro == nullptr) {
            this->inserirNoInicio(dado);
            return;
        }

        Elemento<T>* novo = new Elemento<T>(dado);
        Elemento<T> * eleAtual  = this->_primeiro;


        while(eleAtual->proximo != nullptr) {
            eleAtual = eleAtual->proximo;
        }

        eleAtual->proximo = novo;
        this->_tamanho++;

    };

    /**
     * @brief Remove o primeiro item da lista. Lança ExcecaoListaEncadeadaVazia
     * caso não haja nenhum item na lista.
     * 
     * @return O item removido.
     */
    virtual T removerDoInicio()
    {
        if(this->vazia()) throw ExcecaoListaEncadeadaVazia();

        Elemento<T> * Primeiro  = this->_primeiro;

        T DadoPrimeiro = this->_primeiro->dado;

        this->_primeiro = this->_primeiro->proximo;

        delete Primeiro;

        this->_tamanho--;
        
        return DadoPrimeiro;
    };

    /**
     * @brief Remove um item de uma posição específica da lista. Lança
     * ExcecaoPosicaoInvalida caso a posição não esteja na faixa [0, tamanho).
     * 
     * @param posicao Um inteiro dentro da faixa [0, tamanho).
     * @return O item removido.
     */
    virtual T removerDe(std::size_t posicao)
    {
        if(posicao >= this->_tamanho || this->_tamanho == 0) throw ExcecaoPosicaoInvalida();

        if(posicao == 0) {
            T dadoRemovido = this->removerDoInicio();
            return dadoRemovido;
        }

        if(posicao == this->_tamanho - 1) {
            T dadoRemovido = this->removerDoFim();
            return dadoRemovido;
        }

        Elemento<T> * eleAtual  = this->_primeiro;

        for (std::size_t i = 0; i < posicao - 1; i++) {
            eleAtual = eleAtual->proximo;
        }

        Elemento<T> * eleRemover = eleAtual->proximo;
    
        T dadoRemovido = eleRemover->dado;

        eleAtual->proximo = eleRemover->proximo;

        delete eleRemover;
        
        this->_tamanho--;

        return dadoRemovido;
    };

    /**
     * @brief Remove o último item da lista. Lança ExcecaoListaEncadeadaVazia
     * caso não haja nenhum item na lista.
     * 
     * @return O item removido.
     */
    virtual T removerDoFim()
    {

        if(this->_tamanho == 0) throw ExcecaoListaEncadeadaVazia();

        if(this->_tamanho == 1) {
            
            return this->removerDoInicio();
        }

        Elemento<T> * eleAtual  = this->_primeiro;

        for (int i = 0; i < this->_tamanho - 2 ; i++) {
            eleAtual = eleAtual->proximo;
        }

        Elemento<T> * eleRemover = eleAtual->proximo;

        T dadoRemovido = eleRemover->dado;

        eleAtual->proximo = nullptr;

        delete eleRemover;

        this->_tamanho--;
        
        return dadoRemovido;
    };

    /**
     * @brief Remove um item específico da lista. Lança
     * ExcecaoListaEncadeadaVazia caso não haja nenhum item na lista ou
     * ExcecaoDadoInexistente caso o item não esteja contido na lista.
     * 
     * @param dado O item a ser removido. Se houver mais que um item com
     * o mesmo valor, remove a primeira ocorrência.
     */
    virtual void remover(T dado)
    {
        
        if(this->_tamanho == 0) throw ExcecaoListaEncadeadaVazia();

        if(this->contem(dado)) {

            size_t posicao = this->posicao(dado);

            this->removerDe(posicao);
        
        } else {
            throw ExcecaoDadoInexistente();
        }
    };
};

#endif