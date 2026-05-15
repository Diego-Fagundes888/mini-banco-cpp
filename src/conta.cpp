#include "../include/conta.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <random>
#include <algorithm>
#include <limits>
using namespace std;


// ===================================== Construtor =============================================
// Cria a conta zerada para depois ser preenchida pelo login
//==================================================================================================
conta::conta()
{
    cash = 0.0;
    numeroConta = "";
    nomeCliente = "";
    senhaCliente = "";
}

//=====================================================================================================
// ===================================== Sistema de Login =============================================
//======================================================================================================

bool conta::fazerLogin(string cpfDigitado, string senhaDigitado)
{
    ifstream arquivoLeitura("data/contas.txt");

    if (!arquivoLeitura.is_open())
    {
        cout << "Erro banco de dados vazio. \n";
        return false;
    }

    string linha;

    while (getline(arquivoLeitura, linha))
    {
        stringstream ss(linha);
        string numeroSalvo, nomeSalvo, cpfSalvo, senhaSalvo, cashSalvo;

        getline(ss, numeroSalvo, ';');
        getline(ss, nomeSalvo, ';');
        getline(ss, cpfSalvo, ';');
        getline(ss, senhaSalvo, ';');
        getline(ss, cashSalvo);

        if (cpfSalvo == cpfDigitado && senhaSalvo == senhaDigitado)
        {
            this->numeroConta = numeroSalvo;
            this->nomeCliente = nomeSalvo;
            this->senhaCliente = senhaSalvo;
            this->cash = stod(cashSalvo);

            arquivoLeitura.close();
            return true;
        }
        
    }
    arquivoLeitura.close();
    return false;
}






//======================================================================================================
//================================= criação da conta ===================================================
//=======================================================================================================



//chama o menu
void conta::menu()
{
    int op = 0;

    do
    {
        cout << "\n========= Menu da Conta =========" << endl;
        cout << "0 - Sair" << endl;
        cout << "1 - Ver saldo" << endl;
        cout << "2 - Depositar" << endl;
        cout << "3 - Sacar" << endl;
        cout << "4 - Ver numero da conta" << endl;
        cout << "5 - Ver nome da conta" << endl;
        cout << "6 - Verificar senha" << endl;
        cout << "7 - Fazer Trasferencia" << endl;
        cin >> op;

        action(op);

    } while (op != 0);   
}


//recebe a op escolhida do menu
//e faz a escolha
void conta::action(int op)
{
    switch (op)
    {
    //fechamento do sistema
    case 0:
        cout << "Fechando sistema." << endl;
        break;
    // mostra o saldo
    case 1:
        checkBalance();
        break;
    // depositar o valor
    case 2:
        depositCash();
        break;
    // savar o valor
    case 3:
        withdraw();
        break;
    // mostra numeor da conta
    case 4:
        numeroCli();
        break;
    // mostra numeor da conta
    case 5:
        nome();
        break;
    //mostra senha
    case 6:
        senha();
        break;
        // op inalida
    case 7:
        pix();
        break;
    default:
        cout << "Opção invalida" << endl;
        break;
    }
}

// declarando que a função checkBalance mostra o saldo cash
void conta::checkBalance()
{
    cout << "\nSeu saldo atual e: R$" << cash << endl;
}

// declarando que a funcão de deposito
void conta::depositCash()
{
    string nomeArquivo = "/data/contas.txt";
    string linha;
    vector<string> todasAsLinhas;
    double val;

    cout << "valor que deseja depositar: ";
    cin >> val;

   while (cin.fail() || val <= 0)
   {
       cin.clear();
       cin.ignore(numeric_limits<streamsize>::max(), '\n');
       cout << "O valor Insirido e invalido Tente Novamente: ";
       cin >> val;
   }

   cash += val;
   atualizarSaldoNoArquivo();
   cout << "Deposito realizado com sucesso!" << endl;
   checkBalance();
}

// declarando a funçao de saque
void conta::withdraw()
{
    double val;

    cout << "Valor que deseja sacar: ";
    cin >> val;

    while (val <= 0 || val > cash)
    {
        cin.clear();
       cin.ignore(numeric_limits<streamsize>::max(), '\n');
       cout << "O saque Insirido e invalido Tente Novamente: ";
       cin >> val;
    }
    
    cash -= val;
   atualizarSaldoNoArquivo();
   cout << "saque realizado com sucesso!" << endl;
   checkBalance();
}

void conta::numeroCli()
{
    cout << "\nO numero da sua conta e: " << numeroConta << endl;
}

void conta::nome()
{
    cout << "\nO nome da sua conta e: " << nomeCliente << endl;
}

//mostra a senha
void conta::senha()
{
    cout << "\nA senha da sua Conta e: " << senhaCliente << endl;
}


//================================================================================================================================= Salvar conta e criaçao de conta =============================================== =========================================================================================================

bool criarConta::solicitarDados()
{

    cout << "\n--- Cadastro de Nova Conta ---\n";

    cin.ignore();

    cout << "Digite Seu Nome Completo: ";
    getline(cin, nome);

    cout << "Digite Seu CPF Completo: ";
    getline(cin, cpf);

    this->cpf_limpo = limparCPF(cpf);
    this->cpf_vazio = CPFvazio(this->cpf_limpo);
    this->cpf_limpo = CPFvazio(limparCPF(cpf)); 
    if (verificarCpfExiste(this->cpf_limpo))

    {
        cout << "CPF Existente Operação Cancelada. \n";
        return false;
    }
    

    cout << "Digite Sua senha: ";
    getline(cin, senha);
    this->senha_verificada = verificarSenha(senha);

    // --- Lógica de Geração da Conta ---

    random_device rd;
    mt19937 gen(rd());

    uniform_int_distribution<long long> dis(1000000000LL, 9999999999LL);

    string novaConta;

    do {
        novaConta = to_string(dis(gen));
    } while (verificarContaExiste(novaConta));

    // Salva na propriedade da classe (certifique-se de ter essa variável string na sua classe)
    this->numeroContaDaNovaConta = novaConta; 

    cout << "\nNumero da conta gerado com sucesso: " << this->numeroContaDaNovaConta << "\n";
    return true;
}

void criarConta::salvarNoBancoTxt()
{

    ofstream arquivo("data/contas.txt", ios::app);

    if (arquivo.is_open())
    {
        arquivo << numeroContaDaNovaConta << ";" << nome << ";" << cpf_limpo << ";" << senha_verificada << ";" << 0.0 <<
                                                                                          "\n";
        arquivo.close();
        cout << "Conta Cadastrada Com sucesso!\n";
    }
    else
    {
        cout << "Erro no cadastro\n";
    }
    
}
//======================================================================================================
//                 Função que verifica se a conta ou cpf existe no banco
//======================================================================================================

bool criarConta::verificarContaExiste(string contaTestada)
{
    ifstream arquivoLeitura("data/contas.txt");
    
    // Se o arquivo não abrir, provavelmente é porque ainda não existe nenhuma conta criada.
    // Sendo assim, a conta testada obviamente não existe no banco, então retornamos false.
    if (!arquivoLeitura.is_open())
    {
        return false; 
    }

    string linha;
    // Lê o arquivo linha por linha até o final
    while (getline(arquivoLeitura, linha))
    {
        stringstream ss(linha);
        string numeroSalvo;

        // Como vamos salvar no formato: numeroConta;nome;cpf;senha
        // O primeiro item antes do primeiro ';' é o número da conta.
        getline(ss, numeroSalvo, ';');

        // Se o número lido do arquivo for igual ao que acabamos de gerar, achamos um repetido!
        if (numeroSalvo == contaTestada)
        {
            arquivoLeitura.close();
            return true; 
        }
    }

    // Se o loop terminar e não achar nada, o número está livre
    arquivoLeitura.close();
    return false; 
}

bool criarConta::verificarCpfExiste(string CpfTestada)
{
    ifstream arquivoLeitura("data/contas.txt");

    if (!arquivoLeitura.is_open())
    {
        return false;
    }

    string linha;

    while (getline(arquivoLeitura, linha))
    {
        stringstream ss(linha);
        string numeroSalvo, nomeSalvo, cpfSalvo;

        getline(ss, numeroSalvo, ';');
        getline(ss, nomeSalvo, ';');
        getline(ss, cpfSalvo, ';');

        if (cpfSalvo == CpfTestada)
        {
            arquivoLeitura.close();
            return true;
        }
        
    }
    arquivoLeitura.close();
    return false;
}



//======================================================================================================
//======================================================================================================
//======================================================================================================


void conta::atualizarSaldoNoArquivo()
{
    ifstream arquivoLeitura("data/contas.txt");

    if (!arquivoLeitura.is_open())
    {
        cout << "Erro ao abrir o banco de dados para atualizar o saldo.\n";
        return;
    }

    vector<string> todasAsLinhas;
    string linha;

    while (getline(arquivoLeitura, linha))
    {
        stringstream ss(linha);
        string numeroSalvo, nomeSalvo, cpfSalvo, senhaSalvo, cashSalvo;

        getline(ss, numeroSalvo, ';');
        getline(ss, nomeSalvo, ';');
        getline(ss, cpfSalvo, ';');
        getline(ss, senhaSalvo, ';');
        getline(ss, cashSalvo);

        if (numeroSalvo == this->numeroConta)
        {
            linha = numeroSalvo + ";" + nomeSalvo + ";" + cpfSalvo + ";" + senhaSalvo + ";" + to_string(this->cash);
        }
        todasAsLinhas.push_back(linha);
    }
    arquivoLeitura.close();

    ofstream arquivoEscrita("data/contas.txt");
    
    if (arquivoEscrita.is_open()) {
        for (size_t i = 0; i < todasAsLinhas.size(); i++) {
            arquivoEscrita << todasAsLinhas[i] << "\n";
        }
        arquivoEscrita.close();
    } else {
        cout << "Erro ao salvar as alteracoes no arquivo.\n";
    }

}

//======================================================================================================
//========================= limpar campos ==============================================================
//======================================================================================================

string limparCPF(string entrada)
{
    string resultado = "";


    for(char c : entrada)
    {
        if (isdigit(c))
        {
            resultado = resultado + c;
        }
        
    }
    return resultado;
}

string CPFvazio(string entrada)
{

    string resultado = limparCPF(entrada);

    while (resultado == "")
    {
        cout << "coloque um CPF valido: ";
        getline(cin, entrada);
        resultado = limparCPF(entrada);
    }

    while ((resultado.length()) != 11)
    {
        cout << "E Nessesario 11 Digitos Do CPF: ";
        getline(cin, entrada);
        resultado = limparCPF(entrada);
    }    

    return resultado;
}

//======================================================================================================
//========================= verificar senha ============================================================
//======================================================================================================


string verificarSenha(string entrada)
{
    string resultado = entrada;

    while (resultado == "")
    {
        cout << "coloque uma senha valida: ";
        getline(cin, resultado);
    }

    while (resultado.length() < 4)
    {
        cout << "A Senha Tem Que Ter No Minimo 4 Caracteres: ";
        getline(cin, resultado);
    }
    

    return resultado;
}


//=======================================================================================================
//                               LOGICA DE FAZER TRASFERENCIA 
//=======================================================================================================


void conta::pix()
{
    string cpfDestino;
    double valorTransferencia;

    cout << "\n--- AREA DE PIX ---\n";
    cout << "Digite o CPF do destinatario (apenas numeros): ";
    cin >> cpfDestino;

    cpfDestino = limparCPF(cpfDestino);

    cout << "Valor que deseja transferir: R$ ";
    cin >> valorTransferencia;

    while (cin.fail() || valorTransferencia <= 0 || valorTransferencia > cash)
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Valor invalido ou saldo insuficiente! Tente novamente: R$ ";
        cin >> valorTransferencia;
    }

    ifstream arquivoLeitura("data/contas.txt");
    if (!arquivoLeitura.is_open())
    {
        cout << "Erro ao abrir o banco de dados.\n";
        return;
    }

    vector<string> todasAsLinhas;
    string linha;
    bool destinatarioEncontrado = false;

    while (getline(arquivoLeitura, linha))
    {
        stringstream ss(linha);
        string numeroSalvo, nomeSalvo, cpfSalvo, senhaSalvo, cashSalvo;

        getline(ss, numeroSalvo, ';');
        getline(ss, nomeSalvo, ';');
        getline(ss, cpfSalvo, ';');
        getline(ss, senhaSalvo, ';');
        getline(ss, cashSalvo);

        if (cpfSalvo == cpfDestino)
        {
            destinatarioEncontrado = true;
            double cashDestinatario = stod(cashSalvo);
            cashDestinatario += valorTransferencia;

            linha = numeroSalvo + ";" + nomeSalvo + ";" + cpfSalvo + ";" + senhaSalvo + ";" + to_string(cashDestinatario);
        }
        else if (numeroSalvo == this->numeroConta)
        {
            linha = numeroSalvo + ";" + nomeSalvo + ";" + cpfSalvo + ";" + senhaSalvo + ";" + to_string(this->cash - valorTransferencia);
        }
        todasAsLinhas.push_back(linha);
        

    }
    arquivoLeitura.close();

    if (!destinatarioEncontrado)
    {
        cout << "CPF nao encontrado no sistema. Transferencia cancelada.\n";
        return;
    }

    // Atualiza o saldo do usuário logado na memória do programa
    this->cash -= valorTransferencia;

    // Regrava o banco de dados com as informações atualizadas de ambos
    ofstream arquivoEscrita("data/contas.txt");
    if (arquivoEscrita.is_open())
    {
        for (size_t i = 0; i < todasAsLinhas.size(); i++)
        {
            arquivoEscrita << todasAsLinhas[i] << "\n";
        }
        arquivoEscrita.close();
        
        cout << "\nTransferencia PIX de R$ " << valorTransferencia << " realizada com sucesso!\n";
        checkBalance();
    }
    else
    {
        cout << "Erro ao salvar a transferencia no banco de dados.\n";
    }
    
}
