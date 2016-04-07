/*
  test_main.cc

  CPSC 131, Spring 2016, Instructor Tim Finer, Project 2

  Written in 2015 by Kevin Wortman (kwortman@fullerton.edu)
  Modified a little in 2016 by Tim Finer

  To the extent possible under law, the author(s) have dedicated all
  copyright and related and neighboring rights to this software to the
  public domain worldwide. This software is distributed without any
  warranty. You should have received a copy of the CC0 Public Domain
  Dedication along with this software. If not, see
  <http://creativecommons.org/publicdomain/zero/1.0/>.
 */

#include <cassert>
#include <iostream>

#include "blist.h"

using namespace std;


void GenerateBack(BList<int>& list, int start, int end) {
  for (int i = start; i < end; i++)
      list.add_back(i);
}

void GenerateFront(BList<int>& list, int start, int end) {
  for (int i = start; i < end; i++)
      list.add_front(i);
}

void AddBackTest() {
  cout << "BList::add_back" << endl;
  BList<int> empty, one, three, thousand;

  assert(empty.is_empty());
  assert(one.is_empty());
  assert(three.is_empty());
  assert(thousand.is_empty());
  assert(0 == empty.size());
  assert(0 == one.size());
  assert(0 == three.size());
  assert(0 == thousand.size());

  GenerateBack(one,      1, 2);
  GenerateBack(three,    1, 4);
  GenerateBack(thousand, 1, 1001);

  cout << "BList::is_empty" << endl;
  assert(empty.is_empty());
  assert(!one.is_empty());
  assert(!three.is_empty());
  assert(!thousand.is_empty());

  cout << "BList::size" << endl;
  assert(0 == empty.size());
  assert(1 == one.size());
  assert(3 == three.size());
  assert(1000 == thousand.size());

  cout << "BList::front" << endl;
  assert(1 == one.front());
  assert(1 == three.front());
  assert(1 == thousand.front());

  cout << "BList::back" << endl;
  assert(1 == one.back());
  assert(3 == three.back());
  assert(1000 == thousand.back());
}

void AddFrontTest() {
  cout << "BList::add_front" << endl;
  BList<int> hundred;

  for (int i = 0; i < 100; i++) {
    hundred.add_front(i);
    assert(!hundred.is_empty());
    assert(hundred.size() == (i+1));
    assert(hundred.front() == i);
    assert(hundred.back() == 0);
  }

  for (int i = 0; i < 100; i++) {
    // std::cout << "i: " << i << " = " << hundred.get(99-i) << "\n";
    assert(hundred.get(i) == 99-i);
  }
}


void RemoveFrontTest() {
  cout << "BList::remove_front" << endl;
  BList<int> hundred;
  GenerateBack(hundred, 0, 100);

  for (int i = 0; i < 100; ++i) {
    assert(hundred.size() == 100-i);
    assert(hundred.front() == i);
    assert(hundred.back() == 99);
    hundred.remove_front();
  }
}

void RemoveBackTest() {
  cout << "BList::remove_back" << endl;

  BList<int> hundred;
  GenerateBack(hundred, 0, 100);

  // simultaneously remove elements from both ends
  for (int f = 0, b = 99, size = 100; f < 50; f++, b--, size-=2) {
    assert(!hundred.is_empty());
    assert(hundred.front() == f);
    assert(hundred.back() == b);

    // std::cout << "size: " << size << " = " << hundred.size() << "\n";
    assert(hundred.size() == size);

    hundred.remove_front();
    hundred.remove_back();
  }

  assert(hundred.is_empty());
}


void GetTest() {
  cout << "BList::get" << endl;

  BList<int> thousand;
  GenerateBack(thousand, 0, 1001);

  for (int i = 0; i < 1000; i++) {
    assert(thousand.get(i) == i);
  }
}

void SetTest() {
  cout << "BList::set" << endl;

  BList<int> hundred;
  GenerateBack(hundred, 0, 101);

  for (int i = 0; i < 100; i++) {
    hundred.set(i, -i);
    assert(hundred.get(i) == -i);
  }
}

// This main() function performs unit tests to confirm that the BList
// class is implemented properly.
int main() {
  cout << "BList tests:" << endl << endl;

  AddBackTest();
  AddFrontTest();
  RemoveFrontTest();
  RemoveBackTest();
  GetTest();
  SetTest();

  return 0;
}
