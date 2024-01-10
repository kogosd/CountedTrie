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
  for (int i = 0; i < 10'000'000; ++i) ct.add(rand()%100);

  uint64_t target = 25;
  auto t1 = getNanos();  
  auto rc = ct.findLessOrEqual(target);
  auto t2 = getNanos();
  cout << "LessOrEqual than: " << target << " is: " << rc << ", time: " << (t2 - t1)<< endl;


  return 0;
}