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

#pragma once

// TODO: delete the following #include
#include <deque>

const int B_NODE_CAPACITY = 16;

// TODO: create a template class called BNode that represents a
// doubly-linked node holding a fixed-capacity array of
// B_NODE_CAPACITY elements.

template <typename Element>
class BNode {	//This should have been a class not a struct
private:
	Element arrayFixedCap[B_NODE_CAPACITY];
	BNode<Element> *_prev;
	BNode<Element> *_next;
	template <typename Element>
	friend class BList; //Allows class BList to access variables of class BNode
};

template <typename Element>
class BList{
public:
	// These two statements tell the compiler to delete the the copy and
	// assignment constructors.  If you get an error at these lines, you are
	// attempting to copy a list, so don't do that! (because the destructor 
	// will double delete your nodes)!
	BList(const BList&) = delete;
	BList& operator=(const BList&) = delete;

	BList() {
		/*_head = nullptr;
		_tail = nullptr;
		_size = 0;*/

		//My Implementation, you can change it back if you don't like it, lol
		_head = new BNode<Element>;
		_tail = new BNode<Element>;
		_head->_next = _tail;		//Have them point to each other since list is 'empty'
		_tail->_prev = _head;
		_size = 0;
	}

	~BList() {
		/*clear();
		delete _head;
		delete _tail;
		*/

		//Another implementation
		while (!is_empty()) {
			remove_front();
		}
		delete _head;
		delete _tail;
	}

	bool is_empty() {
		/*if(_head == nullptr){
		return true;
		}
		else {
		return false;
		}*/

		return (_head->_next == _tail);
	}

	int size() {
		BNode<Element>* tmp = _head;

		while (tmp) {
			tmp = tmp->_next;
			_size++;
		}
		return _size;
	}

	Element front() {

		return _head->_next->arrayFixedCap[_size]; //Unsure if this is correct

	}

	Element back() {

		return _tail->_prev->arrayFixedCap[_size]; //Unsure if this is correct

	}
	void add_front(Element e) {
		/*if(_size == B_NODE_CAPACITY || _head == nullptr){
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
		}*/

		add(_head->_next, e);
		_size++;

	}
	void add_back(Element e) {
		/*if(_size == B_NODE_CAPACITY || _head == nullptr){
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
		}*/

		add(_tail, e);
		_size++;
	}

	void remove_front() {

		remove(_head->_next);
		_size--;

	}

	void remove_back() {

		remove(_tail->_prev);
		_size--;
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

protected:

	//Function to add element to the front or back
	void add(BNode<Element>* n, const Element& e) //Inserts a new node before 'n' node
	{
		BNode<Element>* tmp = new BNode<Element>; 
		tmp->arrayFixedCap[_size] = e;
		tmp->_next = n;					
		tmp->_prev = n->_prev;
		n->_prev->_next = n->_prev = tmp;
	}

	//Function to remove first or last element
	void remove(BNode<Element>* n) //Remove node 'n'
	{
		BNode<Element>* tmp = n->_prev;
		BNode<Element>* tmp2 = n->_next;
		n->_next = tmp2;
		tmp2->_prev = tmp;
		delete n;
	}
};
