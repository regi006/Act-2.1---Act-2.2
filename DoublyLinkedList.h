#ifndef _DOUBLYLINKEDLIST_H_
#define _DOUBLYLINKEDLIST_H_

#include <iostream>
#include <stdexcept>
#include "NodeDLL.h"

template <class T>
class DoublyLinkedList {
  private:
    NodeDLL<T> *head;
    NodeDLL<T> *tail;
    int numElements;

  public:
    DoublyLinkedList();
    ~DoublyLinkedList();
    int getNumElements() const;
    void printList() const;
    void addFirst(T value);
    void addLast(T value);
    bool deleteData(T value);
    bool deleteAt(int position);
    T getData(int position) const;
    void updateData(T oldValue, T newValue);
    // To-do Act 2.1 y 2.2 
    void updateAt(int position); // Descripcion en Actividad en clase 09b
    int findData(T value); // Descripcion en Actividad en clase 09b
    void sort();
    void invert();
    // https://stackoverflow.com/questions/40798378/c-deep-copying-linked-list
    DoublyLinkedList(const DoublyLinkedList<T>& other);
    // https://share.google/cEGe387L2Jh5ptNvc
    DoublyLinkedList<T>& operator=(const DoublyLinkedList<T>& other);
};

// Complejidad O(1)
template <class T>
DoublyLinkedList<T>::DoublyLinkedList() {
  std::cout << "-->Constructor DoublyLinkedList llamado automaticamente: " << this << std::endl;
  head = tail = nullptr;
  numElements = 0;
}

// Complejidad O(n)
template <class T>
DoublyLinkedList<T>::~DoublyLinkedList() {
  std::cout << "-->Destructor DoublyLinkedList llamado automaticamente: " << this << std::endl;
  NodeDLL<T> *p = head, *q = nullptr;
  while(p != nullptr) {
    q = p->next;
    //std::cout << "Liberando nodo: " << p->data << " ...";
    delete p;
    p = q;
  }
  head = tail = nullptr;
  numElements = 0;
}

// Complejidad O(1)
template <class T>
int DoublyLinkedList<T>::getNumElements() const {
  return numElements;  
}

// Complejidad O(n)
template <class T>
void DoublyLinkedList<T>::printList() const {
  if (head == nullptr && tail == nullptr)
    std::cout << "La lista esta vacia" << std::endl;
  else {
    std::cout << "El contenido de la lista es: " << std::endl;
    NodeDLL<T> *p = head;
    while(p != nullptr) {
      std::cout << p->data << " ";
      p = p->next;
    }
    std::cout << std::endl;
  }    
}

// Complejidad O(1)
template <class T>
void DoublyLinkedList<T>::addFirst(T value) {
  NodeDLL<T> *newNode = new NodeDLL<T>(value);
  newNode->next = head;
  if (head != nullptr)
    head->prev = newNode;
  else  // caso de una lista vacia
    tail = newNode;
  head = newNode;  
}

// Complejidad O(1)
template <class T>
void DoublyLinkedList<T>::addLast(T value) {
  NodeDLL<T> *newNode = new NodeDLL<T>(value);
  newNode->prev = tail;
  if (tail != nullptr)
    tail->next = newNode;
  else // caso de una lista vacia
    head = newNode;
  tail = newNode;
}

// Complejidad O(n)
template <class T>
bool DoublyLinkedList<T>::deleteData(T value) {
  // La lista esta vacia
  if (head == nullptr && tail == nullptr) {
    std::cout << "La lista esta vacia" << std::endl;
    return false;
  }
  // Buscar el nodo con value en la lista
  NodeDLL<T> *p = head, *previous = nullptr;
  while (p != nullptr && p->data != value) {
    previous = p;
    p = p->next;
  }
  // Nodo con value no encontrado
  if (p == nullptr) {
    std::cout << "El valor no existe en la lista" << std::endl;
    return false;
  }
  // Caso 1: borrar el primer nodo de la lista
  if (p == head) {
    head = p->next;
    if (head == nullptr) // Si la lista contiene un solo nodo
      tail = nullptr;
    else
      head->prev = nullptr;
  }
  // Caso 2: borrar el ultimo nodo de la lista
  else if (p == tail) {
    previous->next = nullptr;
    tail = previous;
  }
  // Caso 3: borrar nodo intermedio de la lista
  else {
    previous->next = p->next;
    p->next->prev = previous;
  }
  // Finalmente borramos el nodo apuntado por p
  delete p;
  p = nullptr;
  numElements--;
  return true;
}

// Complejidad O(n)
template <class T>
bool DoublyLinkedList<T>::deleteAt(int position) {
  // Lista vacia
  if (head == nullptr)
    throw std::out_of_range("La lista esta vacia");
  // Posición invalida
  if (position < 0 || position >= numElements)
    throw std::out_of_range("Posicion invalida");
  // Avanzar hasta el nodo en la posicion indicada
  NodeDLL<T> *p = head;
  for (int i = 0; i < position; i++)
    p = p->next;
  // Caso 1: borrar el primer nodo de la lista
  if (p == head) {
    head = p->next;
    if (head == nullptr) // Si la lista contiene un solo nodo
      tail = nullptr;
    else
      head->prev = nullptr;
  }
  // Caso 2: borrar el ultimo nodo de la lista
  else if (p == tail) {
    tail = p->prev;
    tail->next = nullptr;
  }
  // Caso 3: borrar nodo intermedio de la lista
  else {
    p->prev->next = p->next;
    p->next->prev = p->prev;
  }
  // Finalmente borramos el nodo apuntado por p
  delete p;
  p = nullptr;
  numElements--;
  return true;
}

// Complejidad O(n)
template <class T>
T DoublyLinkedList<T>::getData(int position) const {
  // La lista esta vacia
  if (head == nullptr && tail == nullptr)
    throw std::out_of_range("La lista esta vacia");
  // Posicion invalida
  if (position < 0 || position >= numElements)
    throw std::out_of_range("Posicion invalida");
  // Avanzar hasta el nodo en la posicion indicada
  NodeDLL<T> *p = head;
  for (int i = 0; i < position; i++)
    p = p->next;
  return p->data;
}

// Complejidad O(n)
template <class T>
void DoublyLinkedList<T>::updateData(T value, T newValue) {
  // La lista esta vacia
  if (head == nullptr && tail == nullptr)
    throw std::out_of_range("La lista esta vacia");
  // Buscar el nodo con value en la lista
  NodeDLL<T> *p = head;
  while (p != nullptr && p->data != value)
    p = p->next;
  // Nodo con value no encontrado
  if (p == nullptr)
    throw std::out_of_range("El elemento a actualizar no existe en la lista");
  // Actualizar eñ dato encontrado
  p->data = newValue;
}

#endif // _DOUBLYLINKEDLIST_H_
