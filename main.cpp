#include <iostream>
#include <stack>
#include <string>
#include <sstream>
#include <vector>
#include <iterator>

using namespace std;
bool isoperator(const string& entrada);
void calcular(const string& entrada, stack<double>& valores);
bool isNumber(char c);
bool isOperator(char c);
void transformarString(string& entrada);

bool isNumber(const string& val){
    istringstream iss(val);
    int number;
    if (!(iss >> number).fail()){
        return true;
    }else{
        return false;
    }
}
int aInt(string valor){
    int resultado = 0;
    stringstream(valor) >> resultado;
    return resultado;
}
bool isOperator(const string& val){
    if(val == "+" || val == "*" || val == "/" || val == "-"){
        return true;
    }else{
        return false;
    }
}

class Nodo{
public:
    string valor;
    Nodo *izquierda, *derecha;
    Nodo(string datos){
        this->valor = datos;
        this->izquierda = 0;
        this->derecha = 0;
    }
};

class NodoStack{
public:
    Nodo *nodo;
    NodoStack *siguiente;
    NodoStack(Nodo *nodo){
        this->nodo = nodo;
        siguiente = 0;
    }
};

class Arbol{
private:
    NodoStack *raiz;
public:
    Arbol(){
        raiz = 0;
    }

    void limpiar(){
        raiz = 0;
    }

    void push(Nodo *ptr){
        if(raiz == 0){
            raiz = new NodoStack(ptr);
        }else{
            NodoStack *sptr = new NodoStack(ptr);
            sptr->siguiente = raiz;
            raiz = sptr;
        }
    }

    Nodo *pop(){
        if(raiz == 0){
            cout << "El arbol esta vacio"<<endl;
        }else{
            Nodo *ptr = raiz->nodo;
            raiz = raiz->siguiente;
            return ptr;
        }
    }

    Nodo *ver(){
        return raiz->nodo;
    }
    //Inserta strings que sean numeros u operadores
    void insertar(string valor){
        if(isNumber(valor)){
            Nodo *ptr = new Nodo(valor);
            push(ptr);
        }
        else if(isoperator(valor)){
            Nodo *ptr = new Nodo(valor);
            ptr->izquierda = pop();
            ptr->derecha = pop();
            push(ptr);
        }else{
            return;
        }
    }
    //Toma una expresion compatible con espacios y construye el arbol
    void construirArbol(string expresion){
        istringstream iss(expresion);
        for(string s; iss >> s;){
            insertar(s);
        }
//        for(auto& s : tokens){
//            insertar(s)
//        }
    }

    double evaluar(){
        return evaluar(ver());
    }

    //Metodo recorre el arbol binario para obtener el resultado
    int evaluar(Nodo *ptr){
        if(ptr->izquierda == 0 && ptr->derecha == 0){
            return aInt(ptr->valor);
        }else{
            int resultado = 0;
            int izquierda = evaluar(ptr->izquierda);
            int derecha = evaluar(ptr->derecha);
            char operador = ptr->valor[0];
            switch(operador){
                case('+'):
                    resultado = izquierda + derecha;
                    break;
                case('-'):
                    resultado = izquierda - derecha;
                    break;
                case('*'):
                    resultado = izquierda * derecha;
                    break;
                case('/'):
                    resultado = izquierda / derecha;
                    break;
                default:
                    resultado = izquierda + derecha;
                    break;

            }
            return resultado;
        }
    }
};

//Toma la expresión sin espacios y la lleva a con espacios
void transformarString(string& entrada){
    string temp;
    for(int i = 0; i < entrada.size(); i++){
        if(isNumber(entrada[i]) && isOperator(entrada[i+1]) ){
            temp += entrada[i];
            temp += " ";
        }else if(isOperator(entrada[i]) && isOperator(entrada[i+1])){
            temp += entrada[i];
            temp += " ";
        }else if(isOperator(entrada[i]) && isNumber(entrada[i+1]) ){
            temp += entrada[i];
            temp += " ";

        }else if(isOperator(entrada[i]) || isNumber(entrada[i]) || entrada[i] == ' '){
            temp += entrada[i];
        }

    }
    entrada = temp;
}
bool isNumber(char c){
    if(c == '0' || c == '1' || c == '2' || c == '3' || c == '4' || c == '5' || c == '6' || c == '7' || c == '8' || c == '9'){
        return true;
    }else{
        return false;
    }
}





bool isOperator(char c){
    if(c == '+' || c == '*' || c == '/' || c == '-'){
        return true;
    }else{
        return false;
    }
}

bool isoperator(const string& entrada){
    string operadores[] = {"+", "-", "*", "/"};
    for(int i = 0; i < 4; i++){
        if(entrada == operadores[i]){
            return true;
        }
    }
    return false;
}
int main()
{
    cout << "Bienvenido a la calculadora en notacion polaca inversa!" << endl <<"s para salir" <<endl;
    stack<double> valores;
    string entrada;
    while(true){
        cout << "Expresion->";
        getline(cin, entrada);
        if(entrada == "s"){
            return 0;
        }
        transformarString(entrada);
        Arbol arb;
        arb.construirArbol(entrada);
        cout <<"= "<<arb.evaluar()<<endl;
    }
    return 0;
}
