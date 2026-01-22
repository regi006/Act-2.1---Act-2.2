/**
 * Ejemplo que implementa una lista doblemente ligada con head y tail
 *
 * Compilacion para debug:
 *    g++ -std=c++17 -Wall -g -o main *.cpp
 * Ejecucion con valgrind:
 *    modify hidden file replit.nix to add pkgs.valgrind
 *    valgrind --run-libc-freeres=no --leak-check=full ./main
 *    https://www.youtube.com/watch?v=8JEEYwdrexc
 *
 * Compilacion para ejecucion:
 *    g++ -std=c++17 -Wall -O3 -o main *.cpp
 * Ejecucion:
 *    ./main
 **/

#include "DoublyLinkedList.h"
#include <iostream>


int main() {
  DoublyLinkedList<int> miLista;
  // std::cout << "numElements: " << miLista.getNumElements() << std::endl;

  // addFirst
  std::cout << "Agregando 10 elementos al frente..." << std::endl;
  for (int i = 1; i < 11; i++) {
    miLista.addFirst(i);
  }
  std::cout << "numElements: " << miLista.getNumElements() << std::endl;
  miLista.printList();
  std::cout << std::endl;

  // addLast
  std::cout << "Agregando 5 elementos al final..." << std::endl;
  for (int i = 20; i < 26; i++) {
    miLista.addLast(i);
  }
  std::cout << "numElements: " << miLista.getNumElements() << std::endl;
  miLista.printList();
  std::cout << std::endl;
  /*
    // deleteData
    std::cout << "deleteData 10: " << std::endl;
    miLista.deleteData(10);
    std::cout << "numElements: " << miLista.getNumElements() << std::endl;
    std::cout << "deleteData 5: " << std::endl;
    miLista.deleteData(5);
    std::cout << "numElements: " << miLista.getNumElements() << std::endl;
    std::cout << "deleteData 25: " << std::endl;
    miLista.deleteData(25);
    std::cout << "numElements: " << miLista.getNumElements() << std::endl;
    std::cout << "deleteData 114: " << std::endl;
    miLista.deleteData(114);
    std::cout << "numElements: " << miLista.getNumElements() << std::endl;
    miLista.printList();
    std::cout << std::endl;

    // DeleteAt puede lanzar una excepcion
    try {
      std::cout << "DeleteAt 0: " << std::endl;
      miLista.deleteAt(0);
    } catch (std::out_of_range &e) {
      std::cout << "Error: " << e.what() << std::endl
                << "No se modifico la lista" << std::endl;
    } catch (...) {
      std::cout << "Error desconocido, no se modifico la lista" << std::endl;
    }
    std::cout << "numElements: " << miLista.getNumElements() << std::endl;
    try {
      std::cout << "DeleteAt 2: " << std::endl;
      miLista.deleteAt(2);
    } catch (std::out_of_range &e) {
      std::cout << "Error: " << e.what() << std::endl
                << "No se modifico la lista" << std::endl;
    } catch (...) {
      std::cout << "Error desconocido, no se modifico la lista" << std::endl;
    }
    std::cout << "numElements: " << miLista.getNumElements() << std::endl;
    try {
      std::cout << "DeleteAt 10: " << std::endl;
      miLista.deleteAt(10);
    } catch (std::out_of_range &e) {
      std::cout << "Error: " << e.what() << std::endl
                << "No se modifico la lista" << std::endl;
    } catch (...) {
      std::cout << "Error desconocido, no se modifico la lista" << std::endl;
    }
    std::cout << "numElements: " << miLista.getNumElements() << std::endl;
    try {
      std::cout << "DeleteAt 49: " << std::endl;
      miLista.deleteAt(49);
    } catch (std::out_of_range &e) {
      std::cout << "Error: " << e.what() << std::endl
                << "No se modifico la lista" << std::endl;
    } catch (...) {
      std::cout << "Error desconocido, no se modifico la lista" << std::endl;
    }
    std::cout << "numElements: " << miLista.getNumElements() << std::endl;
    miLista.printList();
    std::cout << std::endl;

    // getData
    try {
      std::cout << "getData(0): " << miLista.getData(0) << std::endl;
    } catch (std::out_of_range &e) {
      std::cout << "Error: " << e.what() << std::endl
                << "No se modifico la lista" << std::endl;
    } catch (...) {
      std::cout << "Error desconocido, no se modifico la lista" << std::endl;
    }
    try {
      std::cout << "getData(3): " << miLista.getData(3) << std::endl;
    } catch (std::out_of_range &e) {
      std::cout << "Error: " << e.what() << std::endl
                << "No se modifico la lista" << std::endl;
    } catch (...) {
      std::cout << "Error desconocido, no se modifico la lista" << std::endl;
    }
    try {
      std::cout << "getData(9): " << miLista.getData(9) << std::endl;
    } catch (std::out_of_range &e) {
      std::cout << "Error: " << e.what() << std::endl
                << "No se modifico la lista" << std::endl;
    } catch (...) {
      std::cout << "Error desconocido, no se modifico la lista" << std::endl;
    }
    try {
      std::cout << "getData(113): " << miLista.getData(113) << std::endl;
    } catch (std::out_of_range &e) {
      std::cout << "Error: " << e.what() << std::endl
                << "No se modifico la lista" << std::endl;
    } catch (...) {
      std::cout << "Error desconocido, no se modifico la lista" << std::endl;
    }
    std::cout << "numElements: " << miLista.getNumElements() << std::endl;
    miLista.printList();
    std::cout << std::endl;

    //updateData
    try {
      std::cout << "updateData(8, 111): " << std::endl;
      miLista.updateData(8, 111);
    } catch (std::out_of_range &e) {
      std::cout << "Error: " << e.what() << std::endl
                << "No se modifico la lista" << std::endl;
    } catch (...) {
      std::cout << "Error desconocido, no se modifico la lista" << std::endl;
    }
    try {
      std::cout << "updateData(20, 999): " << std::endl;
      miLista.updateData(20, 999);
    } catch (std::out_of_range &e) {
      std::cout << "Error: " << e.what() << std::endl
                << "No se modifico la lista" << std::endl;
    } catch (...) {
      std::cout << "Error desconocido, no se modifico la lista" << std::endl;
    }
    try {
      std::cout << "updateData(23, 555): " << std::endl;
      miLista.updateData(23, 555);
    } catch (std::out_of_range &e) {
      std::cout << "Error: " << e.what() << std::endl
                << "No se modifico la lista" << std::endl;
    } catch (...) {
      std::cout << "Error desconocido, no se modifico la lista" << std::endl;
    }
    try {
      std::cout << "updateData(110, 55): " << std::endl;
      miLista.updateData(110, 55);
    } catch (std::out_of_range &e) {
      std::cout << "Error: " << e.what() << std::endl
                << "No se modifico la lista" << std::endl;
    } catch (...) {
      std::cout << "Error desconocido, no se modifico la lista" << std::endl;
    }
    std::cout << "numElements: " << miLista.getNumElements() << std::endl;
    miLista.printList();
    std::cout << std::endl;
  */
  // Test Operator=
  std::cout << std::endl << "--- Prueba de Operator= ---" << std::endl;
  DoublyLinkedList<int> lista2;
  lista2.addFirst(999);
  std::cout << "Lista 2 antes de asignacion: ";
  lista2.printList();

  std::cout << "Asignando miLista a lista2..." << std::endl;
  lista2 = miLista;

  std::cout << "Lista 2 despues de asignacion: ";
  lista2.printList();

  std::cout << "Verificando independencia (modificando lista2)..." << std::endl;
  lista2.addFirst(100);
  std::cout << "Lista 2 modificada: ";
  lista2.printList();
  std::cout << "miLista original (no deberia tener 100): ";
  miLista.printList();

  return 0;
}
