/*
  blist.hh

  CPSC 131, Spring 2016, Instructor Tim Finer, Project 2

  Written in 2015 by Kevin Wortman (kwortman@fullerton.edu)

  To the extent possible under law, the author(s) have dedicated all
  copyright and related and neighboring rights to this software to the
  public domain worldwide. This software is distributed without any
  warranty. You should have received a copy of the CC0 Public Domain
  Dedication along with this software. If not, see
  <http://creativecommons.org/publicdomain/zero/1.0/>.
 */
 //test

#pragma once

// TODO: delete the following #include
#include <deque>

const int B_NODE_CAPACITY = 16;

// TODO: create a template class called BNode that represents a
// doubly-linked node holding a fixed-capacity array of
// B_NODE_CAPACITY elements.
template <typename Element>
struct BNode {
    Element arrayFixedCap[B_NODE_CAPACITY];
    BNode<Element> *_prev;
    BNode<Element> *_next;
    
};

template <typename Element>
class BList {
public:
  // These two statements tell the compiler to delete the the copy and
  // assignment constructors.  If you get an error at these lines, you are
  // attempting to copy a list, so don't do that! (because the destructor 
  // will double delete your nodes)!
  BList(const BList&) = delete;
  BList& operator=(const BList&) = delete;

  BList() {
      _head = nullptr;
      _tail = nullptr;
      _size = 0;
  }

  ~BList() {
      clear();
      delete _head;
      delete _tail;
  }

  bool is_empty() {
      if(_head == nullptr){
          return true;
      }
      else {
          return false;
      }
  }

  int size() {
      BNode<Element>* tmp = _head;
      
      while(tmp){
          tmp = tmp->_next;
          _size++;
      }
      return _size;
  }

  Element front() {
    // TODO: re-implement this function to operate on BNode objects
    // instead of just using std::deque
    check_nonempty();
    return deque_.front();
  }

  Element back() {
    // TODO: re-implement this function to operate on BNode objects
    // instead of just using std::deque
    check_nonempty();
       return deque_.back();
  }
  void add_front(Element e) {
      if(_size == B_NODE_CAPACITY || _head == nullptr){
          BNode<Element>* tmp = new BNode<Element>;
          tmp->arrayFixedCap[_size] = e;
          tmp->_prev = nullptr;
          tmp->_next = _head;
          _head->_prev = tmp;
          _head = tmp;
          _size++;
      }
      else {
          int tmp = 0;
          for (int i = _size; i >= 0; i--){
              tmp = _head->arrayFixedCap[i];
              if (i == 0) {
                  _head->arrayFixedCap[i]=e;
              }
              else {
                  _head->arrayFixedCap[i]= _head->arrayFixedCap[i-1];
              }
              _head->arrayFixedCap[i+1] = tmp;
          }
      }
  }
  void add_back(Element e) {
      if(_size == B_NODE_CAPACITY || _head == nullptr){
          BNode<Element>* tmp = new BNode<Element>;
          tmp->arrayFixedCap[_size] = e;
          tmp->_prev = nullptr;
          tmp->_next = _head;
          _head->_prev = tmp;
          _head = tmp;
          _size++;
      }
      else {
          _head->arrayFixedCap[_size] = e;
          _size++;
      }
  }

  void remove_front() {
    // TODO: re-implement this function to operate on BNode objects
    // instead of just using std::deque
    check_nonempty();
       deque_.pop_front();
  }

  void remove_back() {
    // TODO: re-implement this function to operate on BNode objects
    // instead of just using std::deque
    check_nonempty();
       deque_.pop_back();
  }

  Element get(int index) {
    // TODO: re-implement this function to operate on BNode objects
    // instead of just using std::deque
    check_index(index);
    return deque_.at(index);
  }

  void set(int index, Element e) {
    // TODO: re-implement this function to operate on BNode objects
    // instead of just using std::deque
    check_index(index);
    deque_.at(index) = e;
  }

  void clear() {
    // TODO: re-implement this function to operate on BNode objects
    // instead of just using std::deque
    deque_.clear();
  }

private:
    BNode<Element> *_head;
    BNode<Element> *_tail;
    int _size;

  std::deque<Element> deque_;

  void check_nonempty() {
    assert(!deque_.empty());
  }

  void check_index(int index) {
    assert(index >= 0 && index < size());
  }

};
