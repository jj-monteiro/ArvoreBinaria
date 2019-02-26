#include <iostream>
#include "menu.h"
#include "genBST.h"

#define INSERIR 1
#define REMOVERFUSAO 2
#define REMOVERCOPIA 3
#define BALANCEAR 4
#define MOSTRAR 5
#define FIM 6

using namespace std;
void mostraMenu(){
   int opcaoMenu, elemento;
   bool finalizar = false;
   BST<int> arv;

   while(!finalizar){
      //system("CLS");
      system("tput reset");
      cout << "ARVORE BINARIA - ESTRUTURAS DE DADOS II - FSMA - JOAO MONTEIRO\n";
      cout << "1 - Inserir Elemento\n";
      cout << "2 - Remover por fusao\n";
      cout << "3 - Remover por copia\n";
      cout << "4 - Balancear\n";
      cout << "5 - Mostrar arvore\n";
      cout << "6 - Sair\n";
      cin >> opcaoMenu;

      switch(opcaoMenu){
         case INSERIR:
            cout << "Digite o numero do elemento a ser inserido: ";
            cin >> elemento;
            arv.insert(elemento);
            //system("CLS");
            system("tput reset");
         break;
         case REMOVERFUSAO:
         	cout << "Digite o numero do elemento a ser removido: ";
            cin >> elemento;
            arv.findAndDeleteByMerging(elemento);
			   //system("PAUSE");
            cout << "Digite qualquer tecla para continuar...";
            cin.ignore().get();
            //system("CLS");
            system("tput reset");
         break;
         case REMOVERCOPIA:
            cout << "Digite o numero do elemento a ser removido: ";
            cin >> elemento;
            arv.findAndDeleteByCopying(elemento);
			   //system("PAUSE");
            cout << "Digite qualquer tecla para continuar...";
            cin.ignore().get();
            //system("CLS");
            system("tput reset");
         break;
         case BALANCEAR:
            if(arv.isEmpty()){
               cout << "ATENCAO: a arvore esta vazia.\n\n";
            } else {
               arv.balancear();
            }
            //system("PAUSE");
            cout << "Digite qualquer tecla para continuar...";
            cin.ignore().get();
            //system("CLS");
            system("tput reset");
         break;
         case MOSTRAR:
            if(arv.isEmpty()){
               cout << "ATENCAO: a arvore esta vazia.\n\n";
            }else{
               arv.displayTree();
            }
            //system("PAUSE");
            cout << "Digite qualquer tecla para continuar...";
            cin.ignore().get();
            //system("CLS");
            system("tput reset");
         break;
         case FIM:
            cout << "Saindo...\n\n";
            finalizar = true;
         break;
      }
   }
}
