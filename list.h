#pragma once

#include <iostream>
#include <exception>

// Class for singly linked list data structure where nodes are created that store
// generic (templated) data and a pointer to the next link in the list.
//         1         2         3         5          5
// ex. [NULL|2]->[elem|3]->[elem|4]->[elem|4]->[elem|NULL]
// Contains various functions to maintain/manipulate list.
template <typename T>
class LinkedList
{
  private:
	// Exception class for empty list
	class ListException : public std::exception
	{
	  public:
		const char *what() const throw()
		{
			return "Cannot perform operation on empty list";
		}
	};

	// The actual Node with data element and pointer to the next node
	template <typename U>
	struct Node
	{
	  public:
		U elem;
		Node<U> *next;
		Node<U> *prev;
	};

	Node<T> *head;

public:
	// constructor sets head node to NULL
	LinkedList();

	// copy constructor
	LinkedList(LinkedList<T> &source);

	// assignment operator overloaded for list type
	LinkedList<T> &operator=(LinkedList<T> &source);

	// assignment move operator overloaded for list type
	LinkedList<T> &operator=(LinkedList<T> &&source);

	// addition operator overloaded to append lists
	LinkedList<T> &operator+(LinkedList<T> &source);

	// destructor cleares memory allocated by list
	~LinkedList();

	// Overloaded boolean operators perform operations on the AMOUNT of
	// elements in the compared lists.
	bool operator<(LinkedList<T> &source);
	bool operator>(LinkedList<T> &source);
	bool operator==(LinkedList<T> &source);
	bool operator!=(LinkedList<T> &source);

	// returns element from head node
	T &front() const;

	// returns true of list is empty
	bool empty() const;

	// adds new node to front of list with element 'e' as its data
	void addFront(const T &ele);

	// adds new node to end of list with element 'e' as its data
	void addLast(const T &ele);

	// deletes the head node and names its 'next' node as the new head
	void deleteFront();

	// deletes the last node and names its 'next' node as the new head
	void deleteLast();

	// reverses the order of the list
	void reverse();

	// prints all of the nodes in the list
	void outputAll();

	// sort a list 
	void sort();

	// returns amount of elements in the list
	int count();

	namespace utl
	{
		// function to sort a singly linked list using insertion
    	// sort
		<template typename T>
    	void insertionSort(Node<T>* headref)
    	{
        	// Initialize sorted linked list
        	sorted = NULL;
        	Node* current = headref;
        	// Traverse the given linked list and insert every
        	// node to sorted
        	while (current != NULL) {
            	// Store next for next iteration
            	Node* next = current->next;
            	// insert current in sorted linked list
            	sortedInsert(current);
            	// Update current
            	current = next;
        	}
        	// Update head_ref to point to sorted linked list
        	head = sorted;
		}
 
	    /*
    	 * function to insert a new_node in a list. Note that
    	 * this function expects a pointer to head_ref as this
    	 * can modify the head of the input linked list
    	 * (similar to push())
    	 */
    	void sortedInsert(Node* newnode)
    	{
        	/* Special case for the head end */
        	if (sorted == NULL || sorted->val >= newnode->val) {
        	    newnode->next = sorted;
        	    sorted = newnode;
        	}
        	else
			{
            	Node* current = sorted;
            	/* Locate the node before the point of insertion
            	 */
            	while (current->next != NULL && current->next->val < newnode->val)
				{
                	current = current->next;
            	}
            	newnode->next = current->next;
            	current->next = newnode;
        	}
    	}
	};
};
