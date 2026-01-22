#include <iostream>

template <typename T> struct Node {
  T data;
  Node *next;

  Node(T val) : data(val), next(nullptr) {}
};

template <typename T> class LinkedList {
private:
  Node<T> *head;

  // Helper para limpiar la memoria
  void clear() {
    Node<T> *current = head;
    while (current != nullptr) {
      Node<T> *nextNode = current->next;
      delete current;
      current = nextNode;
    }
    head = nullptr;
  }

public:
  LinkedList() : head(nullptr) {}

  // Destructo
  ~LinkedList() { clear(); }

  // Método para agregar elementos
  void append(T val) {
    if (!head) {
      head = new Node<T>(val);
      return;
    }
    Node<T> *current = head;
    while (current->next) {
      current = current->next;
    }
    current->next = new Node<T>(val);
  }

  // Método para imprimir
  void print() const {
    Node<T> *current = head;
    while (current) {
      std::cout << current->data << " -> ";
      current = current->next;
    }
    std::cout << "nullptr" << std::endl;
  }

  LinkedList<T> &operator=(const LinkedList<T> &other) {

    if (this == &other) {
      return *this;
    }

    this->clear();

    if (other.head == nullptr) {
      head = nullptr;
    } else {
      // Copiar el primer nodo
      head = new Node<T>(other.head->data);

      Node<T> *currentNew = head; // Puntero para la lista nueva (esta)
      Node<T> *currentOld = other.head->next; // Puntero para recorrer la lista
                                              // que ta vieja

      while (currentOld != nullptr) {
        currentNew->next = new Node<T>(currentOld->data);

        // Avanzar
        currentNew = currentNew->next;
        currentOld = currentOld->next;
      }
    }

    // Retornamos para permitir encadenamiento
    return *this;
  }
};

int main() {

  LinkedList<int> lista1;
  lista1.append(1);
  lista1.append(2);
  lista1.append(3);

  std::cout << "Lista 1 original: ";
  lista1.print();

  LinkedList<int> lista2;
  lista2.append(10);
  lista2.append(20);

  std::cout << "Lista 2 original: ";
  lista2.print();

  std::cout << "Asignando Lista 1 = Lista 2..." << std::endl;
  lista1 = lista2;

  std::cout << "Lista 1 despues de asignacion (deberia ser 10->20): ";
  lista1.print();

  std::cout << "Lista 2 intacta: ";
  lista2.print();

  return 0;
}
