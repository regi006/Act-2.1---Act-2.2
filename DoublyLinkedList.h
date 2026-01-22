#ifndef _DOUBLYLINKEDLIST_H_
#define _DOUBLYLINKEDLIST_H_

#include "NodeDLL.h"
#include <iostream>
#include <stdexcept>


template <class T> class DoublyLinkedList {
private:
  NodeDLL<T> *head;
  NodeDLL<T> *tail;
  int numElements;
  void quickSort(NodeDLL<T> *low, NodeDLL<T> *high);
  NodeDLL<T> *partition(NodeDLL<T> *low, NodeDLL<T> *high);


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
  int findData(T value);       // Descripcion en Actividad en clase 09b
  void sort();
  void invert();
  // https://stackoverflow.com/questions/40798378/c-deep-copying-linked-list
  DoublyLinkedList(const DoublyLinkedList<T> &other);
  // https://share.google/cEGe387L2Jh5ptNvc
  DoublyLinkedList<T> &operator=(const DoublyLinkedList<T> &other);
};

// Complejidad O(1)
template <class T> DoublyLinkedList<T>::DoublyLinkedList() {
  std::cout << "-->Constructor DoublyLinkedList llamado automaticamente: "
            << this << std::endl;
  head = tail = nullptr;
  numElements = 0;
}

// Complejidad O(n)
template <class T> DoublyLinkedList<T>::~DoublyLinkedList() {
  std::cout << "-->Destructor DoublyLinkedList llamado automaticamente: "
            << this << std::endl;
  NodeDLL<T> *p = head, *q = nullptr;
  while (p != nullptr) {
    q = p->next;
    // std::cout << "Liberando nodo: " << p->data << " ...";
    delete p;
    p = q;
  }
  head = tail = nullptr;
  numElements = 0;
}

// Complejidad O(1)
template <class T> int DoublyLinkedList<T>::getNumElements() const {
  return numElements;
}

// Complejidad O(n)
template <class T> void DoublyLinkedList<T>::printList() const {
  if (head == nullptr && tail == nullptr)
    std::cout << "La lista esta vacia" << std::endl;
  else {
    std::cout << "El contenido de la lista es: " << std::endl;
    NodeDLL<T> *p = head;
    while (p != nullptr) {
      std::cout << p->data << " ";
      p = p->next;
    }
    std::cout << std::endl;
  }
}

// Complejidad O(1)
template <class T> void DoublyLinkedList<T>::addFirst(T value) {
  NodeDLL<T> *newNode = new NodeDLL<T>(value);
  newNode->next = head;
  if (head != nullptr)
    head->prev = newNode;
  else // caso de una lista vacia
    tail = newNode;
  head = newNode;
}

// Complejidad O(1)
template <class T> void DoublyLinkedList<T>::addLast(T value) {
  NodeDLL<T> *newNode = new NodeDLL<T>(value);
  newNode->prev = tail;
  if (tail != nullptr)
    tail->next = newNode;
  else // caso de una lista vacia
    head = newNode;
  tail = newNode;
}

// Complejidad O(n)
template <class T> bool DoublyLinkedList<T>::deleteData(T value) {
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
template <class T> bool DoublyLinkedList<T>::deleteAt(int position) {
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
template <class T> T DoublyLinkedList<T>::getData(int position) const {
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
template <class T> void DoublyLinkedList<T>::updateData(T value, T newValue) {
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

// invert
// Invierte la lista doblemente ligada sin usar memoria adicional
// Complejidad: O(n)
template <class T> void DoublyLinkedList<T>::invert() {
  NodeDLL<T> *current = head;
  NodeDLL<T> *temp = nullptr;

  while (current != nullptr) {
    temp = current->next;
    current->next = current->prev;
    current->prev = temp;
    current = temp;
  }

  temp = head;
  head = tail;
  tail = temp;
}

// Copy Constructor
// Complejidad O(n)
template <class T>
DoublyLinkedList<T>::DoublyLinkedList(const DoublyLinkedList<T> &other) {
  std::cout << "-->Copy Constructor DoublyLinkedList llamado automaticamente: "
            << this << std::endl;
  head = tail = nullptr;
  numElements = 0;
  NodeDLL<T> *curr = other.head;
  while (curr != nullptr) {
    addLast(curr->data);
    curr = curr->next;
  }
}

// Operator=
// Complejidad O(n)
template <class T>
DoublyLinkedList<T> &
DoublyLinkedList<T>::operator=(const DoublyLinkedList<T> &other) {
  std::cout << "-->Operator= DoublyLinkedList llamado automaticamente: " << this
            << std::endl;
  if (this == &other) {
    return *this;
  }
  // Clear existing
  NodeDLL<T> *p = head;
  while (p != nullptr) {
    NodeDLL<T> *next = p->next;
    delete p;
    p = next;
  }
  head = tail = nullptr;
  numElements = 0;

  // Copy new
  NodeDLL<T> *curr = other.head;
  while (curr != nullptr) {
    addLast(curr->data);
    curr = curr->next;
  }
  return *this;
}

// partition
// Particion tipo Lomuto con pivote al final
// Complejidad O(n)
template <class T>
NodeDLL<T>* DoublyLinkedList<T>::partition(NodeDLL<T>* low, NodeDLL<T>* high) {
  // Pivote al final
  T pivot = high->data;

  // i = low - 1  (nodo anterior a low)
  NodeDLL<T>* i = low->prev;

  for (NodeDLL<T>* j = low; j != high; j = j->next) {
    if (j->data < pivot) {
      // i++
      if (i == nullptr) {
        i = low;
      } else {
        i = i->next;
      }

      // swap(i->data, j->data)
      T temp = i->data;
      i->data = j->data;
      j->data = temp;
    }
  }

  // Colocar el pivote en su posicion correcta
  if (i == nullptr) {
    i = low;
  } else {
    i = i->next;
  }

  T temp = i->data;
  i->data = high->data;
  high->data = temp;

  return i;
}

// quickSort
// Complejidad O(n log n) promedio, O(n^2) peor caso
template <class T>
void DoublyLinkedList<T>::quickSort(NodeDLL<T>* low, NodeDLL<T>* high) {
  if (low != nullptr && high != nullptr && low != high && low != high->next) {
    NodeDLL<T>* pi = partition(low, high);

    quickSort(low, pi->prev);
    quickSort(pi->next, high);
  }
}

// sort
// Ordena los datos de la lista usando quicksort
// Complejidad O(n log n) promedio, O(n^2) peor caso
template <class T>
void DoublyLinkedList<T>::sort() {
  if (head == nullptr || head == tail)
    return;

  quickSort(head, tail);
}
 
#endif // _DOUBLYLINKEDLIST_H_
