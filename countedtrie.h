#pragma once

#include <time.h>

#include <array>
#include <iostream>
#include <random>
#include <vector>

#include "util.h"
#include "countedtrie.h"
#include "test.h"
using namespace std;

extern bool debug;

template<int SIZE>
struct CountedTrieNode {
  int count{0};
  unique_ptr<CountedTrieNode> children[10];
  void add() { ++count; }

  void print(ostream& o = cout, int indent = 0) {
    o << "count: " << count << endl;
    for (int i = 0; i < 10; ++i) {
      if (children[i].get() == nullptr) continue;
      o << string(indent, ' ') << i << ":";
      children[i]->print(o, indent + 1);
    }
  }
};

template<uint8_t SIZE>
struct CountedTrie {
  CountedTrieNode<SIZE> root;
  uint64_t count{0};

  array<uint8_t, SIZE> getArray(uint64_t num) {
    array<uint8_t, SIZE> a{0};
    uint8_t index{0};
    while (num) {
      a[index++] = num % 10;
      num /= 10;
    }
    std::reverse(a.begin(), a.end());
    return a;
  }

  uint64_t getNum(array<uint8_t, SIZE> &a) {
    uint64_t num = 0;
    for (int i = 0; i < SIZE; ++i) {
      num = num * 10 + a[i];
    }
    return num;
  }

  void add(uint64_t num) {
    CountedTrieNode<SIZE> *curr = &root;
    auto a = getArray(num);
    ++count;
    curr->add();
    for (int i = 0; i < SIZE; ++i) {
      if (debug) cout << "a[" << i << "] = " << a[i] << endl;
      if (curr->children[a[i]] == nullptr) {
        curr->children[a[i]] =
            unique_ptr<CountedTrieNode<SIZE>>(new CountedTrieNode<SIZE>());
      }
      curr = curr->children[a[i]].get();
      curr->add();
    }
  }

  uint64_t find(uint64_t num) {
    auto a = getArray(num);
    CountedTrieNode<SIZE> *curr = &root;
    for (int i = 0; i < SIZE; ++i) {
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
    uint64_t targetindex = count * p;
    return get(targetindex);
  }

  uint64_t get(uint64_t target) {
    CountedTrieNode<SIZE> *curr = &root;
    uint64_t currcount{0};
    array<uint8_t, SIZE> a{0};
    for (int j = 0; j < SIZE; ++j) {
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
    if (debug) cerr << "currcount: " << currcount << "/" << count << endl;
    return getNum(a);
  }

  uint64_t findLessOrEqual(uint64_t num) {
    auto a = getArray(num);
    CountedTrieNode<SIZE> *curr = &root;
    uint64_t total{0};
    for (int i = 0; i < SIZE; ++i) {
      for (int j = 0; j < a[i]; ++j) {
        if (curr->children[j].get() == nullptr) continue;
        if (debug) cerr << j << ": " << curr->children[j]->count << endl;
        total += curr->children[j]->count;
      }
      if (curr->children[a[i]].get() == nullptr) break;
      curr = curr->children[a[i]].get();
    }
    return total;
  }

  void print(ostream& o = cout) {
    o << "CountedTrie: Count: " << count << endl;
    root.print(o);
  }
};
