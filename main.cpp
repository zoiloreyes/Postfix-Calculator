#include <iostream>
#include <stack>
#include <string>
#include <sstream>
using namespace std;
bool isoperator(const string& entrada);
void calcular(const string& entrada, stack<double>& valores);
bool isNumber(char c);
bool isOperator(char c);
void transformarString(string& entrada);


void transformarString(string& entrada){
    string queso;
    for(int i = 0; i < entrada.size(); i++){
        if(isNumber(entrada[i]) && isOperator(entrada[i+1]) ){
            queso += entrada[i];
            queso += " ";
        }else if(isOperator(entrada[i]) && isOperator(entrada[i+1])){
            queso += entrada[i];
            queso += " ";
        }else if(isOperator(entrada[i]) && isNumber(entrada[i+1]) ){
            queso += entrada[i];
            queso += " ";

        }else if(isOperator(entrada[i]) || isNumber(entrada[i]) || entrada[i] == ' '){
            queso = queso + entrada[i];
        }

    }
    entrada = queso;
    cout << entrada << endl;
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
void calcular(const string& entrada, stack<double>& valores){


//    double primero, segundo, resultado;
//    if(valores.size() < 2){
//        cout << "No hay suficientes valores para realizar operacion"<<endl;
//        return;
//    }
//    segundo = valores.top();
//    valores.pop();
//    primero = valores.top();
//    valores.pop();
//
//    if(entrada == "-"){
//        resultado = primero - segundo;
//    }else if(entrada == "+"){
//        resultado = primero + segundo;
//    }else if(entrada == "*"){
//        resultado = primero * segundo;
//    }else if(entrada == "/"){
//        resultado = primero / segundo;
//    }
//
//    cout << resultado << endl;
//    valores.push(resultado);
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
    double numero;
    while(true){
        cout << "->";
        getline(cin, entrada);
        if(entrada == "s"){
            return 0;
        }
        transformarString(entrada);
//        if(istringstream(entrada) >> numero){
//            valores.push(numero);
//        }else if(isoperator(entrada)){
//            calcular(entrada, valores);
//        }
//
//        else
//        else{
//            cout << "Entrada invalida"<<endl;
//        }
    }
}
