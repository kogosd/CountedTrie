#include "test.h"
#include "countedtrie.h"

void testMedian() {
  srand(time(NULL));
  CountedTrie<10> ct;
  for (int i = 0; i < 10; ++i) ct.add(i);

  if (debug) ct.print();

  cout << "starting median\n";
  auto t1 = getNanos();
  auto med = ct.median();
  auto t2 = getNanos();
  cout << "med=" << med << ", time: " << (t2 - t1) << endl;
  assert(med == 4.5);
}

void testPercentile() {
  srand(time(NULL));
  CountedTrie<10> ct;
  for (int i = 0; i < 10; ++i) ct.add(i);

  if (debug) ct.print();

  cout << "starting percentile\n";
  for (auto p : {0.25, 0.5, 0.75, 0.9, 0.99}) {
    auto t1 = getNanos();
    auto per = ct.percentile(p);
    auto t2 = getNanos();
    cout << p * 100 << ": " << per << ", time: " << (t2 - t1) << endl;
  }
}



void testFind() {
  int COUNT {1'000'000};
  cout << "populating " << COUNT << " trie\n";
  srand(time(NULL));
  CountedTrie<10> ct;
  for (int i = 0; i < COUNT; ++i) ct.add(i);
  ct.add(1000);
  ct.add(1000);

  if (debug) ct.print();

  cout << "Starting find\n";
  auto t1 = getNanos();
  int target = 1000;
  auto f1000 = ct.find(1000);
  auto t2 = getNanos();
  cout << "Count of target: " << target << " is: " << f1000 << ", time: " << (t2 - t1) << endl;
  assert(f1000==3);
}

void test() {
  testMedian();
  testPercentile();
  testFind();
}
