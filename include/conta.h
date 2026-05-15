#ifndef CONTA_H
#define CONTA_H
#include <string>

std::string limparCPF(std::string entrada);
std::string CPFvazio(std::string entrada);
std::string verificarSenha(std::string entrada);

class conta
{
    public:
        conta();
        void menu();
        void action(int);
        void numeroCli();
        void senha();
        void nome();
        void checkBalance();
        void depositCash();
        void withdraw();
        void pix();
        
        bool fazerLogin(std::string cpfDigitado, std::string senhaDigitado);

    private:
        std::string numeroConta;
        std::string nomeCliente;
        std::string senhaCliente;
        double cash;

        void atualizarSaldoNoArquivo();
};

class criarConta
{   
    public:
        bool solicitarDados();
        void salvarNoBancoTxt();
        bool verificarContaExiste(std::string contaTestada);
        bool verificarCpfExiste(std::string CpfTestada);

    private:
        std::string nome;
        std::string cpf;
        std::string senha;
        std::string cpf_limpo;
        std::string cpf_vazio;
        std::string senha_verificada;
        std::string numeroContaDaNovaConta;
        double cash;
};

class validador
{
    public:
        void limparCPF();
};


#endif //CONTA_H