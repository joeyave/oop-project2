#pragma once
#include <iostream>
#include <fstream>

template <class T>
class Stack
{
private:
	struct Node
	{
		T val;
		Node* next;

		// Constructor with params.
		Node(T _val, Node* _next)
		{
			val = _val;
			next = _next;
		}
	};

	Node* head;

	void clone(const Stack<T>& src)
	{
		Node* srctrav = src.head;
		while (srctrav)
		{
			Node* temp = new Node(srctrav->val, nullptr);
			if (!temp) return;

			if (!head)
				head = temp;
			else
			{
				Node* trav = head;
				while (trav->next)
					trav = trav->next;
				trav->next = temp;
			}
			srctrav = srctrav->next;
		}
	}

public:
	// Constructors.
	Stack<T>()
	{
		head = nullptr;
	}

	// Copy constructor.
	Stack<T>(const Stack& src)
	{
		if (!src.head)
		{
			head = nullptr;
		}
		else
		{
			clone(src);
		}
	}

	bool is_empty()
	{
		if (!head) return true;
		return false;
	}

	// Methods.
	void push(T val)
	{
		Node* temp = new Node(val, head);
		if (!temp) return;

		head = temp;
		// std::cout << val << " pushed to the stack.\n";
	}

	void print()
	{
		if (is_empty())
		{
			std::cout << "Stack is empty.\n";
			return;
		}

		Node* trav = head;
		while (trav)
		{
			std::cout << trav->val << " ";
			trav = trav->next;
		}
		std::cout << std::endl;
	}

	T pop()
	{
		Node* trav = head;
		trav = trav->next;
		T popped = head->val;
		delete head;
		head = trav;

		// std::cout << popped << " popped from the stack.\n";
		return popped;
	}

	T top() const
	{
		// std::cout << "Top element is " << head->val << std::endl;
		return head->val;
	}

	// Operators overloading.

	Stack<T> operator=(const Stack& src) const
	{
		if (&src == this)
			return *this;

		if (!src.is_empty())
		{
			clone(src);
		}
	}

	T operator[](size_t n) const
	{
		Node* trav = head;
		while (trav && n-- > 0)
			trav = trav->next;
		return (trav == nullptr ? 0 : trav->val);
	}

	friend std::ostream& operator<<(std::ostream& out, Stack<T>& stk)
	{
		if (stk.head)
		{
			if (stk.is_empty())
			{
				std::cout << "Stack is empty.\n";
				return out;
			}

			Node* trav = stk.head;
			while (trav)
			{
				out << trav->val << " ";
				trav = trav->next;
			}
			std::cout << std::endl;
		}
		return out;
	}

	friend std::istream& operator>>(std::istream& in, Stack<T>& stk)
	{
		T val;
		in >> val;
		stk.push(val);
		return in;
	}
};