#include <time.h>

#include <array>
#include <iostream>
#include <random>
#include <vector>

#include "util.h"
using namespace std;

bool debug{false};

struct CountedTrieNode {
  int count{0};
  unique_ptr<CountedTrieNode> children[10];
  void add() { ++count; }

  void print(int indent = 0) {
    cout << "count: " << count << endl;
    for (int i = 0; i < 10; ++i) {
      if (children[i].get() == nullptr) continue;
      cout << string(indent, ' ') << i << ":";
      children[i]->print(indent + 1);
    }
  }
};

struct CountedTrie {
  CountedTrieNode root;
  int count{0};

  array<int, 10> getArray(int num) {
    array<int, 10> a{0};
    int index{0};
    while (num) {
      a[index++] = num % 10;
      num /= 10;
    }
    std::reverse(a.begin(), a.end());
    return a;
  }

  int getNum(array<int, 10> &a) {
    int num = 0;
    for (int i = 0; i < 10; ++i) {
      num = num * 10 + a[i];
    }
    return num;
  }

  void add(int num) {
    CountedTrieNode *curr = &root;
    auto a = getArray(num);
    ++count;
    curr->add();
    for (int i = 0; i < 10; ++i) {
      if (debug) cout << "a[" << i << "] = " << a[i] << endl;
      if (curr->children[a[i]] == nullptr) {
        curr->children[a[i]] =
            unique_ptr<CountedTrieNode>(new CountedTrieNode());
      }
      curr = curr->children[a[i]].get();
      curr->add();
    }
  }

  int find(int num) {
    auto a = getArray(num);
    CountedTrieNode *curr = &root;
    for (int i = 0; i < 10; ++i) {
      if (curr->children[a[i]] == nullptr) return 0;
      curr = curr->children[a[i]].get();
    }
    return curr->count;
  }

  double median() {
    if (count & 1) {
      return get(count / 2);
    }

    auto low = get(count / 2 - 1);
    auto high = get(count / 2);
    return (low + high) / 2.;
  }

  double percentile(double p) {
    int targetindex = count * p;
    return get(targetindex);
  }

  int get(int target) {
    CountedTrieNode *curr = &root;
    int currcount{0};
    array<int, 10> a{0};
    for (int j = 0; j < 10; ++j) {
      a[j] = 0;
      for (int i = 0; i < 10; ++i) {
        if (curr->children[i] == nullptr) continue;
        currcount += curr->children[i].get()->count;
        if (currcount > target) {
          currcount -= curr->children[i].get()->count;
          curr = curr->children[i].get();
          a[j] = i;
          break;
        }
      }
    }
    cerr << "currcount: " << currcount << "/" << count << endl;
    return getNum(a);
  }

  int findLessOrEqual(int num) {
    auto a = getArray(num);
    CountedTrieNode *curr = &root;
    int total{0};
    for (int i = 0; i < 10; ++i) {
      for (int j = 0; j <= a[i]; ++j) {
        if (curr->children[j].get() == nullptr) continue;
        cerr << j << ": " << curr->children[j]->count << endl;
        total += curr->children[j]->count;
      }
      curr = curr->children[a[i]].get();
    }
    return total;
  }

  void print() {
    cout << "CountedTrie: Count: " << count << endl;
    root.print();
  }
};

void testMedian() {
  srand(time(NULL));
  CountedTrie ct;
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
  CountedTrie ct;
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
  cout << "starting find\n";
  srand(time(NULL));
  CountedTrie ct;
  for (int i = 0; i < 1001; ++i) ct.add(i);
  ct.add(1000);
  ct.add(1000);

  if (debug) ct.print();

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

int main(int argc, char **argv) {
  if (argc > 1 and string(argv[1]) == "debug") {
    debug = true;
  }

  if (argc > 1 and string(argv[1]) == "test") {
    test();
    return 0;
  }
  return 0;
}