//Codigo baseado no Livro "Estrutura de Dados e Algoritmos em C++ - Adam Drozdek" -
//Novas funcoes implementadas por Joao Monteiro

//************************  genBST.h  **************************
//                 generic binary search tree
#include <queue>
#include <stack>
#include <iostream>
#include <deque>
using namespace std;

#ifndef BINARY_SEARCH_TREE
#define BINARY_SEARCH_TREE


/*Observe que serao definidas "funcoes template" (via template<class >) que poderao usar tipos genericos,
 ou seja, permitirao aplicar metodos para qualquer tipo de dado(s) passado(s) como parametro(s)...
 Leia mais: http://www.cplusplus.com/doc/oldtutorial/templates/
*/
template<class T> //T - sembolo aqui associado a qq tipo generico
class Stack : public stack <T> {//Implementa a funcao pop de uma pilha para o tipo generico T
public:
    T pop() { //sobrecarga de pop() da classe Stack da STL
        T tmp = stack<T>::top(); //armazena o topo no tmp
        stack<T>::pop(); //remove o topo
        return tmp; //retorna tmp para ser exibido
    }
};

template<class T>
class Queue : public queue<T> {//Implementa a funcao dequeue de uma fila para o tipo generico T
public:
    T dequeue() {
        T tmp = queue<T>::front(); //modificacao feita pelo professor Irineu
        queue<T>::pop();
        return tmp;
    }
    void enqueue(const T& el) {//Implementa a funcao enqueue de uma fila para o tipo generico T
        push(el);
    }
};

std::deque<int> vetor;
std::deque<int>::iterator it;

template<class T> class BST;//Declara uma classe de manipulacao de arvore binaria
							              //para tipo generico. Observe que ainda nao possui
                            //atributos ou metodos - a ser feito mais abaixo...

template<class T>
class BSTNode {//Classe generica que define o no-dado para a arvore
public:
	//Construtor: caso sem passagem de parametros
    BSTNode() {
        left = right = 0;
    }
    //Construtor: caso com passagem de parametros
    BSTNode(const T& e, BSTNode<T> *l = 0, BSTNode<T> *r = 0) {
        el = e; //dado generico a ser guardado no n�
		left = l; //ponteiro que encadeia filho e esquerda, podendo ser NULL caso nao seja passado
		right = r;//ponteiro que encadeia filho e direita, podendo ser NULL caso nao seja passado
    }
    //Atributos publicos do no-dado
    T el;
    BSTNode<T> *left, *right;
};

template<class T>
class BST { //Aqui temos a implementacao de metodos e atributos da classe que definira a arvore binaria
public:
    BST() { //construtor
        root = 0; //root e o atributo de controle da ED, ponteiro de inicio, inicia em NULL
    }
    ~BST() { //destrutor
        clear();
    }
    void clear() {//chamada para desalocar tudo que tiver sendo apontado pelo root...
        clear(root);//sobrecarga de metodo mais abaixo, que aceitara parametro (ponteiro) para ir desalocando todos os nos...
        root = 0; //apos anterior, atribui NULL ao controle root
    }
    bool isEmpty() const { //teste se arvore e vazia?
        return root == 0;
    }
    void preorder() { //varre arvore em pre-ordem
        preorder(root); //sobrecarga de metodo mais abaixo
    }
    void inorder() { //varre arvore em in-ordem ("em ordem")
        inorder(root); //sobrecarga de metodo mais abaixo
    }
    void mostraVetor();

    void postorder() { //varre arvore em pos-ordem
        postorder(root); //sobrecarga de metodo mais abaixo
    }
    void insert(const T&);
    void recursiveInsert(const T& el) {
        recursiveInsert(root,el);
    }
    T* search(const T& el) const {
        return search(root,el);
    }
    T* recursiveSearch(const T& el) const {
        return recursiveSearch(root,el);
    }

    void deleteByCopying(BSTNode<T>*&);
    void findAndDeleteByCopying(const T&);
    void deleteByMerging(BSTNode<T>*&);
    void findAndDeleteByMerging(const T&);
//    void balance(T*,int,int);
    void balancear();
    void balance(deque<int>*,int,int);
    void displayTree();

protected:
    BSTNode<T>* root;
    void clear(BSTNode<T>*);
    void recursiveInsert(BSTNode<T>*&, const T&);
    T* search(BSTNode<T>*, const T&) const;
    T* recursiveSearch(BSTNode<T>*, const T&) const;
    void preorder(BSTNode<T>*);
    void inorder(BSTNode<T>*);
    void postorder(BSTNode<T>*);
    virtual void visit(BSTNode<T>* p) {
        cout << p->el << ' ';
    }
};

template<class T>
void BST<T>::clear(BSTNode<T> *p) {//Observe chamada recursiva para delecao de nos terminais (folhas) para raiz
    if (p != 0) {
         clear(p->left); //recursao para no e esquerda
         clear(p->right); //recursao para no e direita
         delete p; //desaloca objeto no-dado
     }
}

template<class T>
void BST<T>::insert(const T& el) {
    BSTNode<T> *p = root, *prev = 0; //cria 2 ponteiros do tipo no, um aponta para o no raiz e o outro para NULL.
    while (p != 0) {  //loop para varrer a arvore (enquanto p for diferente de NULL)
        prev = p;     //ponteiro prev aponta para onde p aponta
        if (el < p->el) //se o elemento a ser inserido for menor que o elemento anterior...
            p = p->left; //vai para o filho a esquerda
        else
			p = p->right; //senao (igual ou maior), vai para o filho a direita
    }
    if (root == 0)                   //ou poderia ser testado "prev" //quando a arvore esta vazia
        root = new BSTNode<T>(el);  //cria novo elemento e o atribui ao no raiz
    else if (el < prev->el)          //se nao estiver vazia e o valor do elemento for menor que o valor do no anterior
        prev->left  = new BSTNode<T>(el); //filho a esquerda recebe um novo no com o elemento
    else
		prev->right = new BSTNode<T>(el); //filho a direita recebe um novo no com o elemento
}

template<class T>
void BST<T>::recursiveInsert(BSTNode<T>*& p, const T& el) {//insercao feita com recursividade
    if (p == 0)
         p = new BSTNode<T>(el);
    else if (el < p->el)
         recursiveInsert(p->left, el);
    else recursiveInsert(p->right,el);
}

template<class T>
T* BST<T>::search(BSTNode<T>* p, const T& el) const {//busca elemento a partir do raiz
    while (p != 0)
        if (el == p->el)     //testa raiz (ou raiz de uma subarbore)
            return &p->el;   //retorno se achar elemento no no
        else if (el < p->el) //caso contrario, decide ir para subarvore e esquerda
            p = p->left;
        else
			p = p->right;    //caso contrario, decide ir para subarvore e direita
    return 0;                //retorno se nao achar elemento ou arvore vazia
}

template<class T>
T* BST<T>::recursiveSearch(BSTNode<T>* p, const T& el) const {//uso de recursividade
    if (p != 0)
         if (el == p->el)
              return &p->el;
         else if (el < p->el)
              return recursiveSearch(p->left,el);
         else return recursiveSearch(p->right,el);
    else return 0;
}

template<class T>
void BST<T>::mostraVetor() {
     if (vetor.empty()){
		std::cout << "\nA fila esta vazia!\n";
	} else {
		it = vetor.begin();
		std::cout << "\nElementos da fila: ";
		while(it!=vetor.end()){
			std::cout << *it << " ";
			it++;
		}
		std::cout << "\n";
	}
}

template<class T>
void BST<T>::inorder(BSTNode<T> *p) {
     if (p != 0) {
         inorder(p->left);
         //visit(p);
         vetor.push_back(p->el);
         inorder(p->right);
	 }
}

template<class T>
void BST<T>::preorder(BSTNode<T> *p) {
    if (p != 0) {
        visit(p);
        preorder(p->left);
        preorder(p->right);
    }
}

template<class T>
void BST<T>::postorder(BSTNode<T>* p) {
    if (p != 0) {
        postorder(p->left);
        postorder(p->right);
        visit(p);
    }
}

template<class T>
void BST<T>::deleteByCopying(BSTNode<T>*& node) {
    BSTNode<T> *previous, *tmp = node;
     if (node->right == 0)                  // testa se o no tem filho a direita
          node = node->left;                // se move para esquerda
     else if (node->left == 0)              // testa de o no tem filho a esquerda
          node = node->right;               // se move para direita
     else {                                 // caso tenha filho a direita e a esquerda
          tmp = node->left;                 // 1. tmp aponta para filho a esquerda do no
          previous = node;                  //    previous aponta para no
          while (tmp->right != 0) {         // 2. enquando filho a direita for diferente de nulo
              previous = tmp;               //    previous aponta para onde tmp aponta
              tmp = tmp->right;             //    tmp anda para a direita
          }
          node->el = tmp->el;               // 3. copia o elemento de tmp para node
          if (previous == node)             // testa se previous e igual ao no a ser apagado
               previous->left  = tmp->left; // se for, o filho a esquerda de previous aponta para o filho a esquerda de tmp
          else
		       previous->right = tmp->left;  // 4. se nao for, o filho a direita de previous aponta para o filho a esquerda de tmp
     }
     delete tmp;                            // 5. apaga o no apontado por tmp
}

// findAndDeleteByCopying() searches the tree to locate the node containing
// el. If the node is located, the function DeleteByCopying() is called.

template<class T>
void BST<T>::findAndDeleteByCopying(const T& el) {
    BSTNode<T> *p = root, *prev = 0;
     while (p != 0 && !(p->el == el)) {
        prev = p;
        if (el < p->el)
           	p = p->left;
        else
			p = p->right;
     }
     if (p != 0 && p->el == el)
        if (p == root)
           	deleteByCopying(root);
        else if (prev->left == p)
           	deleteByCopying(prev->left);
        else
			deleteByCopying(prev->right);
     else if (root != 0)
        cout << "Elemento " << el << " nao esta na arvore\n";
     else
	 	cout << "A arvore esta vazia\n";
}

template<class T>
void BST<T>::deleteByMerging(BSTNode<T>*& node) {
    BSTNode<T> *tmp = node;
    if (node != 0) {
        if (!node->right)           // caso o no nao tenha filho a direita
             node = node->left;     // filho a esquerda e anexado a seu pai.
        else if (node->left == 0)   // caso nao tenha filho a esquerda
             node = node->right;    // filho a direita e anexado a seu pai
        else {                      // be ready for merging subtrees;
             tmp = node->left;      // 1. move para a esquerda
             while (tmp->right != 0){// 2. e entao mova-se para a direita o maximo que puder
                tmp = tmp->right;   // (pare quando o no nao tem mais filhos a direita)
             }
			 tmp->right = node->right;  // 3. estabelece o link entra o no mais a direita
                			            //    da sub-arvore esquerda com a sub-arvore direita
             tmp = node;            	// 4. faz tmp apontar para o no a ser removido
             node = node->left;     	// 5. o novo no toma lugar do antigo no
        }
        delete tmp;                 	// 6. apaga o no
     }
}

template<class T>
void BST<T>::findAndDeleteByMerging(const T& el) {
    BSTNode<T> *node = root, *prev = 0; //cria ponteiro node (apontando p/ root) e prev (apontando p/ NULL)
    while (node != NULL) {    //enquanto ponteiro node for diferente de NULL
        if (node->el == el) //testa se o elemento para onde node aponta e igual ao elemento a ser encontrado e removido
            break;          //se for verdadeiro sai do loop while (nesse caso, o no a ser removido e o no raiz)
        prev = node;        //prev passa a apontar para onde node aponta
        if (el < node->el)  //testa se o elemento a ser removido e menor que o elemento para onde node aponta
            node = node->left; //caso verdadeiro, faz node apontar para o filho a esquerda do no antereriormente apontado
        else
			node = node->right; //caso falso, faz node apontar para o filho a esquerda do no anteriormente apontado
    }
    if (node != 0 && node->el == el) //caso node NAO aponte para NULL e o elemento a ser removido e igual ao elemento para onde node aponta
    	if (node == root)            //se node aponta para o no raiz
            deleteByMerging(root);   //chama o metodo para apagar o no raiz
        else if (prev->left == node) //se o filho esquerdo do no apontado por prev for igual ao no apontado por node
            deleteByMerging(prev->left); //chama o metodo para apagar o filho esquerdo do no anterior
        else
			deleteByMerging(prev->right); //chama o metodo para apagar o filho direito do no anterior
    else if (root != 0)              //caso root seja diferente de zero
        cout << "Elemento " << el << " nao esta na arvore.\n"; //o elemento nao foi encontrado
    else                              //caso nem root exista
		cout << "Arvore esta vazia.\n"; //arvore vazia pois node aponta para NULL.
}


//template<class T>
//void BST<T>::balance(T data[], int first, int last) {
//    if (first <= last) {
//        int middle = (first + last)/2;
//        insert(data[middle]);
//        balance(data,first,middle-1);
//        balance(data,middle+1,last);
//    }
//}

template<class T>
void BST<T>::balancear() {
	vetor.clear(); //limpa vetor
	inorder();
	clear(); //limpa arvore
    balance(&vetor, 0, vetor.size()-1);
}

template<class T>
void BST<T>::balance(deque<int>* data, int first, int last) {
    if (first <= last) {                 //se valor inicial for menor ou igual o valor final
        int middle = (first + last)/2;   //acha o indice meio
        insert(data->at(middle));         //insere na arvore o valor do meio do vetor
        balance(data,first,middle-1);    //chama recursivamente o metodo para balancear a metade esquerda do vetor
        balance(data,middle+1,last);     //chama recursivamente o metodo para balancear a metade direita do vetor
    }
}

template<class T>
void BST<T>::displayTree(){
	Stack<BSTNode<T>*> pilhaGlobal;
	pilhaGlobal.push(root);
	int nEspacos = 32;
	bool isLinhaVazia = false;
	cout << "___________________________________________________________________________\n";

	while(isLinhaVazia==false){
		Stack<BSTNode<T>*> pilhaLocal;
		isLinhaVazia = true;
		for (int i=0; i<nEspacos; i++)
			cout << " ";
		while(pilhaGlobal.empty()==false){
			BSTNode<T> *tmp = pilhaGlobal.pop();
			if(tmp!=0){
				cout << tmp->el;
				pilhaLocal.push(tmp->left);
				pilhaLocal.push(tmp->right);
				if (tmp->left != 0 || tmp->right != 0)
					isLinhaVazia = false;
			} else {
				cout << "--";
				pilhaLocal.push(0); //coloca NULL na pilhaLocal
				pilhaLocal.push(0); //coloca NULL na pilhaLocal
			}
			for(int j=0; j<nEspacos*2-2; j++){
				cout << " ";
			}
		}
		cout << endl;
		nEspacos /= 2;
		while(pilhaLocal.empty()==false){
			pilhaGlobal.push(pilhaLocal.pop());
		}
	}
	cout << "___________________________________________________________________________\n";
}

#endif
