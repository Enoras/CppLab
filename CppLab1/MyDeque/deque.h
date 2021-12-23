#pragma once
#include<iostream>
#include<exception>
#include"allocator.h"

//template<class Type, class Memallocator = Allocator> class Deque;
//std::ostream& operator<<(std::ostream& os, const Deque<Type>& deq);


template<class Type, class Memallocator = Allocator>
class Deque {
private:
	/* struct of one element */
	struct Node {
		Type data;
		Node* next;
		Node* prev;
	};

	Node* beginNode;
	Node* endNode;
	Memallocator allocator;
	unsigned int size;


	class Iterator {
	private:
		Node* node;
	public:
		/*delete defualt constructor */
		Iterator() = delete;

		/* constructor by node */
		Iterator(Node* node) : node(node) { };

		/* defualt copy constructor */
		Iterator(const Iterator&) = default;

		/* default move constructor */
		Iterator(Iterator&&) = default;

		/* operators */
		bool operator==(Iterator const & it) {
			return this->node == it.node;
		}

		bool operator!=(Iterator const & it) {
			return this->node != it.node;
		}

		Iterator& operator=(const Iterator& it) {
			this->node = it.node;
			return *this;
		}

		/* increment */
		Iterator& operator++() {
			if (node == nullptr) {
				throw std::exception("Nullptr error");
			}

			node = node->next;
			return *this;
		}

		Iterator& operator++(int) {
			if (node == nullptr) {
				throw std::exception("Nullptr error");
			}

			Iterator out = *this;
			node = node->next;
			return out;
		}

		Type& operator*() {
			return node->data;
		}

		Type& getValue() {
			if (node == nullptr) {
				throw std::exception("Nullptr error");
			}

			return node->data;
		}
	};
public:
	/* default constructor */
	Deque() : beginNode(nullptr), endNode(nullptr), size(0) { };

	/* copy constructor */
	Deque(Deque const& deq) : beginNode(nullptr), endNode(nullptr), size(0) {
		for (Iterator i = deq.begin()
			; i != deq.end(); 
			i++) {
			pushBack(i.getValue());
		}
	}

	/* move constructor */
	Deque(Deque&& deq) : beginNode(nullptr), endNode(nullptr), size(0) {
		this->beginNode = deq.beginNode;
		this->endNode = deq.endNode;

		deq.beginNode = deq.endNode = nullptr;
	}

	Deque(std::initializer_list<Type> initList) : beginNode(nullptr), endNode(nullptr) {
		for (auto& el : initList) {
			pushBack(el);
		}
	}

	/* begin/end methods */
	Iterator begin() const {
		return Iterator(beginNode);
	}

	Iterator end() const {
		return Iterator(nullptr);
	}

	/* copy operator */
 	Deque& operator=(Deque const& deq) {
		for (auto& dq : deq) {
			pushBack(dq);
		}
		return *this;
	}
	
	// push with copy semantic
	void pushBack(Type const& data) {
		Node* newNode = (Node*)allocator.allocate(sizeof(Node));
		if (newNode == nullptr)
			throw std::exception("Not enough memory");

		newNode->data = data;
		newNode->next = nullptr;
		newNode->prev = endNode;
		size++;

		if (endNode != nullptr)
			endNode->next = newNode;
		endNode = newNode;

		if (beginNode == nullptr)
			beginNode = newNode;
	}

	void pushFront(Type const& data) {
		Node* newNode = (Node*)allocator.allocate(sizeof(Node));
		if (newNode == nullptr)
			throw std::exception("Not enough memory");

		newNode->data = data;
		newNode->next = beginNode;
		newNode->prev = nullptr;
		size++;

		if (beginNode != nullptr)
			beginNode->prev = newNode;
		beginNode = newNode;

		if (endNode == nullptr)
			endNode = newNode;
	}

	// push with move semantic
	void pushBack(Type&& data) {
		Node* newNode = (Node*)allocator.allocate(sizeof(Node));
		if (newNode == nullptr)
			throw std::exception("Not enough memory");

		newNode->data = std::move(data);
		newNode->next = nullptr;
		newNode->prev = endNode;
		size++;

		if (endNode != nullptr)
			endNode->next = newNode;
		endNode = newNode;

		if (beginNode == nullptr)
			beginNode = newNode;
	}

	void pushFront(Type&& data) {
		Node* newNode = (Node*)allocator.allocate(sizeof(Node));
		if (newNode == nullptr)
			throw std::exception("Not enough memory");

		newNode->data = std::move(data);
		newNode->next = beginNode;
		newNode->prev = nullptr;
		size++;

		if (beginNode != nullptr)
			beginNode->prev = newNode;
		beginNode = newNode;

		if (endNode == nullptr)
			endNode = newNode;
	}

	void popFront() {
		if (endNode == nullptr)
			throw std::exception("Delete element from empty deque");

		Node* tmp = beginNode;
		beginNode = beginNode->next;
		allocator.deallocate((unsigned char*)tmp);

		if (beginNode == nullptr)
			endNode = nullptr;
		else
			beginNode->prev = nullptr;

		size--;
	}

	void popBack() {
		if (endNode == nullptr)
			throw std::exception("Delete element from empty deque");

		Node* tmp = endNode;
		endNode = endNode->prev;
		allocator.deallocate((unsigned char*)tmp);

		if (endNode == nullptr)
			beginNode = nullptr;
		else
			endNode->next = nullptr;

		size--;
	}

	Type peekFront() {
		if (beginNode == nullptr)
			throw std::exception("Nullptr error");

		return beginNode->data;
	}

	Type peekBack() {
		if (endNode == nullptr)
			throw std::exception("Nullptr error");

		return endNode->data;
	}

	unsigned int Size() {
		return size;
	}

	void clear() {
		while (beginNode != nullptr)
			popFront();
	}

	/* concat move semantic */
	void concat(Deque&& deq) {
		if (deq.beginNode == nullptr)
			return;

		if (beginNode == nullptr) {
			beginNode = deq.beginNode;
			endNode = deq.endNode;
			size = deq.size;
		}
		else {
			endNode->next = deq.beginNode;
			endNode = deq.endNode;
			deq.beginNode->prev = endNode;
			size += deq.size;
		}
		deq.beginNode = deq.endNode = nullptr;
	}

	bool isEmpty() {
		return beginNode == nullptr;
	}

	Type& at(const unsigned int id) {
		if(id > size)
			throw std::exception("Index out of range");

		Node* tmp = beginNode;
		for (unsigned int i = 0; i < id; i++){
			tmp = tmp->next;
		}
		return tmp->data;
	}

	Type& operator[](const unsigned int id) {
		Node* tmp = beginNode;
		for (unsigned int i = 0; i < id; i++) {
			tmp = tmp->next;
		}
		return tmp->data;
	}


	friend std::ostream& operator<<(std::ostream& os, const Deque<Type>& deq) {
		for (auto& d : deq) {
			os << d << " ";
		}
		return os;
	}

	~Deque() {
		clear();
	}
};


