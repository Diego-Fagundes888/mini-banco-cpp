#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <iostream>
#include <string>
#include "../include/conta.h"



int main(void)
{
    //aceitamento de acentuação
    system("chcp 65001");
    system("cls");
    setlocale(LC_ALL, "Portuguese_Brasil");

    //declaração de varivel

    int op;
    //Menu
     
    printf("\n========= Mini Banco =========\n");
    printf("1 - Criar conta\n");
    printf("2 - Fazer login\n");
    printf("3 - Lista de contas\n");
    printf("0 - sair\n\n");
    printf("Escolha umas das opção: ");
        scanf("%d", &op);
                    while (op != 1 && op != 2 && op  != 3 && op != 0)
                    {
                        printf("\n*****OPCAO INVÁLIDA*****\n");
                        printf("1 - Criar conta\n");
                        printf("2 - Fazer login\n");
                        printf("3 - Lista de contas\n");
                        printf("0 - sair\n\n");
                         printf("\nInsira uma opcao correta: ");
                            scanf("%d", &op);
                    }

switch(op)
    {
    case 1:
    {
        criarConta criar_Conta;
       if (criar_Conta.solicitarDados() == true) 
        {
            criar_Conta.salvarNoBancoTxt();
        }
        else 
        {
            printf("\nRetornando ao menu principal...\n");
        }

        break;
    }
    case 2:
    {
        // Criamos variáveis para guardar o que o usuário vai digitar
        std::string cpfInput, senhaInput;

        printf("Digite seu CPF: ");
        std::cin >> cpfInput; // Usando cin pois estamos lidando com std::string
        
        printf("Digite sua senha: ");
        std::cin >> senhaInput;

        conta minhaConta;
        
        // Passamos o CPF e a senha para a função verificar.
        // O if checa se a função retornou "true" (login válido)
        if (minhaConta.fazerLogin(cpfInput, senhaInput)) 
        {
            printf("\nLogin efetuado com sucesso!\n");
            minhaConta.menu(); // Só abre o menu se o login estiver correto
        } 
        else 
        {
            printf("\nErro: CPF ou Senha incorretos. Tente novamente.\n");
        }

        break;
    }
    case 3:
        printf("Voce escolheu: Lista de contas\n");

        break;
    case 0:
        printf("Voce escolheu: Sair\n");
        printf("programa finalizado volte sempre");

        break;
    }

    return 0;
}
   
