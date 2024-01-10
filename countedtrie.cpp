#include "countedtrie.h"

bool debug{false};


int main(int argc, char **argv) {
  if (argc > 1 and string(argv[1]) == "debug") {
    debug = true;
  }

  if (argc > 1 and string(argv[1]) == "test") {
    test();
    return 0;
  }

  //test current feature
  srand(time(NULL));
  CountedTrie ct;
  for (int i = 0; i < 1'000'000; ++i) ct.add(99+rand()%100);

  int target = 100;
  auto rc = ct.findLessOrEqual(target);
  cout << "LessOrEqual than: " << target << " is: " << rc << endl;


  return 0;
}