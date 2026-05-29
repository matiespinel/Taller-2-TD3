#ifndef __LISTA_H__
#define __LISTA_H__

#include <iostream>
using namespace std;
template <typename T>
class Lista {
    public:
    Lista();
    ~Lista();

    int longitud();

    void agregarAtras(T elemento);
    /*borrarUltimo: dada una lista enlazada con al menos un elemento, borrar el elemento de la última
posición. La memoria reservada para el elemento debe liberarse correspondientemente*/\
    //Pre: 1<= longitud
    void borrarUltimo();  
    void borrarIesimo(const int pos); 
    //Pre: Longitud() > 0
    T cursor(); // es basicamente una segunda lista???
    void avanzar(); 

    // Pre: 0 <= posicion < longitud()
    T iesimo(const int posicion);

    private:
        struct nodo {
            nodo(T un_elemento) : elemento(un_elemento), siguiente(nullptr) {}
            T elemento;
            nodo* siguiente;
            nodo* _anterior; 
        };
        nodo* _cursor;
        nodo* _primero;
        nodo* _ultimo; // puedo suponer ya como doblemente anclada???
        int _longitud;
};
template <typename T> // lo repito en todos lados para que sepa que es un T generico???
Lista<T>::Lista() : _primero(nullptr), _longitud(0), _ultimo(nullptr), _cursor(nullptr) {}
template <typename T>
int Lista<T>::longitud() {
    return _longitud;
}
template <typename T>
void Lista<T>::agregarAtras(const T elemento) {
    nodo * nuevo = new nodo(elemento);

    if (_primero == nullptr) {
          _primero = nuevo;
          _ultimo = nuevo;
          nuevo -> _anterior = _ultimo; //enlazada como ciculo??
          //primer elemento es cursor 
          _cursor = nuevo;
        

    } else {
        // avanzo hasta que `actual` sea el último nodo
        nodo* actual = _primero;
        while (actual->siguiente != nullptr) {
            actual = actual->siguiente;
        }
        // estoy en el ultimo nodo 
        actual->siguiente = nuevo;
        nuevo->_anterior = actual; 
        _ultimo = nuevo; 
    }
    _longitud++;
}
template <typename T>
T Lista<T>::iesimo(const int posicion) { // T ahora ya que devuelvo un elemnto tipo T
    // avanzo hasta que `actual` sea el iésimo nodo
    nodo* actual = _primero;
    int i = 0;
    while (i < posicion){
        actual = actual->siguiente;
        i++;
    }

    return actual->elemento;
}
template <typename T>
Lista<T>::~Lista() {
    nodo * actual = _primero;
    while (actual != nullptr) {
        nodo* sig = actual->siguiente;
        delete actual;
        actual = sig;
    }
    _primero = nullptr;
}

template<typename T>
void Lista<T>::borrarUltimo(){
    //tengo que poder llegar al anterior de ultimo o que ultimo sea doble enlazado asi puedo acceder a esa pos.
   // Caso 1: La lista tiene un único elemento
    if (_longitud == 1) { 
        
        delete _ultimo;
        _primero = nullptr;
        _ultimo = nullptr;
        _cursor = nullptr; 
        
    } 
    // Caso 2: La lista tiene 2 o más elementos
    else {
        if (_ultimo == _cursor){
            nodo* nuevoUltimo = _ultimo->_anterior; // Guardo el penúltimo
            nuevoUltimo->siguiente = nullptr;
            delete _ultimo;
            _ultimo = nuevoUltimo;
            _cursor = _ultimo;
        }
        else{
            nodo* nuevoUltimo = _ultimo->_anterior; // Guardo el penúltimo
            nuevoUltimo->siguiente = nullptr;
            delete _ultimo;
            _ultimo = nuevoUltimo;
        }
       
    }

    _longitud--;
}
template<typename T>
//Pre: // Pre: 0 <= posicion < longitud() 
void Lista<T>::borrarIesimo(const int pos){
    if (pos == 0){
        nodo* actual = _primero->siguiente;
        if (_primero == _cursor){
            _cursor = _primero->siguiente;
            delete _primero;
            _primero = actual;
            _longitud --;
        }
        delete _primero;
        _primero = actual;
        _longitud --;
    }
    else{
    nodo* actual = _primero;
    int i = 0;
    while (i < pos){
        actual = actual->siguiente;
        i++;
    }
    if(actual == _cursor && actual->siguiente == nullptr){
        _cursor= actual->_anterior
        actual->_anterior->siguiente = actual->siguiente;
        delete actual;
        _longitud --;}
    
    if (actual == _cursor && actual->siguiente != nullptr){}
        actual->_anterior->siguiente = actual->siguiente;
        _cursor = actual->siguiente;
        delete actual;
        _longitud --;
    }
    actual->_anterior->siguiente = actual->siguiente;
    delete actual;
    _longitud --;
    }
template<typename T>
T Lista<T>::cursor(){
    return *_cursor; 
}
#endif