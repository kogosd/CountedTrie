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
  CountedTrie<18> ct;
  for (int i = 0; i < 1'000; ++i) ct.add(rand()%100);

  uint64_t target = 25;
  auto rc = ct.findLessOrEqual(target);
  cout << "LessOrEqual than: " << target << " is: " << rc << endl;


  return 0;
}