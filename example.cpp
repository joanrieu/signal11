#include <iostream>
#include "signal11.h"

void display_generic(const char* header, const char* msg, int x) {
  std::cout << "> " << header << '\t' << msg << ' ' << x << std::endl;
}

void display_regular(const char* msg, int x) {
  display_generic("regular", msg, x);
}

int main() {

  using namespace std::placeholders; // for std::bind

  std::cout << "Declaring a signal with 2 arguments..." << std::endl;
  signal11<const char*, int> signal;

  std::cout << "> Connecting a regular function..." << std::endl;
  signal.connect(display_regular);

  std::cout << "> Connecting a function with bound arguments..." << std::endl;
  signal.connect(std::bind(display_generic, "binding", _1, _2));

  std::cout << "> Connecting a lambda expression..." << std::endl;
  auto connection = signal.connect([](const char* msg, int x) {
    display_generic("lambda", msg, x);
  });

  std::cout << "> Connecting a oneshot lambda expression..." << std::endl;
  signal.connect_oneshot([](const char* msg, int x) {
    display_generic("oneshot", msg, x);
  });

  std::cout << "\nTriggering a first event..." << std::endl;
  signal("Hello, World!", 1);

  std::cout << "\nTriggering a second event..." << std::endl;
  signal("Hello, World!", 2);

  std::cout << "\nDisconnecting the lambda expression..." << std::endl;
  signal.disconnect(connection);

  std::cout << "\nTriggering a third event..." << std::endl;
  signal("Hello, World!", 3);

}
