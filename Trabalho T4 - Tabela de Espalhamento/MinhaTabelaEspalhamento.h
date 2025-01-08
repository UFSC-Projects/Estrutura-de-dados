#ifndef MINHA_TABELA_ESPALHAMENTO_H
#define MINHA_TABELA_ESPALHAMENTO_H

#include "MinhaListaEncadeada.h"
// MinhaListaEncadeada
#include "TabelaEspalhamentoAbstrata.h"
// TabelaEspalhamentoAbstrata
#include "excecoes.h"
// ExcecaoDadoInexistente

template <typename T, std::size_t capac>
class MinhaTabelaEspalhamento final : public TabelaEspalhamentoAbstrata<T, capac>
{
public:

    /**
     * @brief Obtém a capacidade da tabela.
     * 
     * @return Um inteiro maior do que 0.
     */
    virtual std::size_t capacidade() const
    {
        std::size_t result = capac;;
        return result;
    };

    /**
     * @brief Insere um dado na tabela. Se a tabela já contiver o dado, ele não
     * é inserido novamente.
     *
     * @param dado O dado a ser inserido.
     */
    virtual void inserir(T dado) 
    {
        int pos = this->funcaoEspalhamento(dado);

        if(this->tabela[pos].contem(dado))
            return;
        
        this->tabela[pos].inserirNoFim(dado);
        
    };

    /**
     * @brief Remove um dado da tabela. Se a tabela não contiver o dado, uma
     * exceção ExcecaoDadoInexistente é lançada.
     *
     * @param dado O dado a ser removido.
     */
    virtual void remover(T dado) {
        size_t posTabela = this->funcaoEspalhamento(dado);

        if(!this->tabela[posTabela].contem(dado)) {
            throw ExcecaoDadoInexistente();
        } else {
            size_t posDadoLista = this->tabela[posTabela].posicao(dado);
            this->tabela[posTabela].removerDe(posDadoLista);
        }

    };

    /**
     * @brief Verifica se \p dado está contido na tabela.
     *
     * @param dado O dado sendo buscado.
     * @return true se o dado está contido na tabela; false caso contrário.
     */
    virtual bool contem(T dado) const
    {
        size_t pos = this->funcaoEspalhamento(dado);
        
        if(this->tabela[pos].contem(dado)) return true;

        return false;
    };

    /**
     * @brief Obtém a quantidade de dados contidos na árvore.
     *
     * @return Um inteiro maior ou igual a 0.
     */
    virtual std::size_t quantidade() const
    {
        if(capac == 0) return 0;

        int quantidade = 0;

        for(int i = 0; i < capac; i++) {

            quantidade += this->tabela[i].tamanho();

        }
        


        return quantidade;
    };

protected:
    /**
     * @brief Obtém a posição correspondente na tabela para o dado.
     * 
     * @param dado O dado.
     * @return Um inteiro na faixa [0, capacidade).
     */
    virtual std::size_t funcaoEspalhamento(T dado) const
    {
        if constexpr (std::is_integral<T>::value) {
            return dado % capac;
        } else if constexpr (std::is_same<T, std::string>::value) {
            std::size_t hash = codigoEspalhamento(dado);
            return hash % capac;
        }
        
        return 0;
    };

private:
    /**
     * @brief Calcula a representação numérica de um tipo integral.
     *
     * @tparam U O tipo integral.
     * @param integral Um valor integral.
     * @return Um inteiro calculado através de static_cast<std::size_t>(integral)
     */
    template <typename U, typename = std::enable_if_t<std::is_integral<U>::value>>
    std::size_t codigoEspalhamento(U integral) const
    {
        return static_cast<std::size_t>(integral);
    };

    /**
     * @brief Calcula a representação numérica de um string.
     *
     * @param s um string.
     * @return Um inteiro calculado conforme s[0]*31^(n-1) + s[1]*31^(n-2) + ... + s[n-1].
     */
    std::size_t codigoEspalhamento(std::string const &string) const
    {
        
        size_t result = 0;
        
        for(char c : string) {
            result = 31 * result + c;
        }

        return result;
    }
};

#endif
