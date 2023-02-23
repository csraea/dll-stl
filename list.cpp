#include "list.h"


// Constructor instantiates head node with value NULL
template <typename T>
LinkedList<T>::LinkedList() : head(NULL)
{
}
// Copy Constructor takes another list as the parameter 'source' then
// loops through each node and uses the 'addFront(const T& e)' to rebuild
// a new list with the copied data.
//
// Example of calling this constructor:
// LinkedList<int> list1 = list;
template <typename T>
LinkedList<T>::LinkedList(LinkedList<T>& source)
{

	Node<T>* temp = source.head;
	for (int i = 0; i < source.count()-1; i++)
	{
		temp = temp->next;		
	}

	for (int a = source.count()-1; a > 0; a--)
	{
		
		temp = source.head;
		for (int i = 0; i < a; i++)
		{
			
			temp = temp->next;

		}
		addFront(temp->elem);
	}

	addFront(source.head->elem);
}


//---------------------------------------------------------------
// Overloaded boolean operators perform operations on the AMOUNT of
// elements in the compared lists.
template <typename T>
bool LinkedList<T>::operator<(LinkedList<T>& source)
{
	return this->count() < source.count();
}

template <typename T>
bool LinkedList<T>::operator>(LinkedList<T>& source)
{
	return this->count() > source.count();
}

template <typename T>
bool LinkedList<T>::operator==(LinkedList<T>& source)
{
	return this->count() == source.count();
}

template <typename T>
bool LinkedList<T>::operator!=(LinkedList<T>& source)
{
	return this->count() != source.count();
}
//---------------------------------------------------------------

// Destructor deletes the dynamically allocated nodes in the list using
// 'deleteFront()' while the list is not 'empty()'.
template <typename T>
LinkedList<T>::~LinkedList()
{
	while (!empty())
		deleteFront();
}

// Returns element of the head node in the list, throws exeception if
// list is empty.
template <typename T>
T& LinkedList<T>::front() const
{
	try
	{
		if (empty())
			std::cout << "List is empty" << std::endl;
		return head->elem;
	}
	catch (ListException e)
	{
		std::cout << e.what();
	}
}

// Returns true if list is empty.
template <typename T>
bool LinkedList<T>::empty() const
{
	return head == NULL;
}

// Adds new node to list and stores the 'ele' parameter as its 'elem'.
//
// Accomplished by changing its 'next' to pointer to point to the current 
// 'head' node, then changing the 'head' pointer to point to this node.
template <typename T>
void LinkedList<T>::addFront(const T& ele)
{
	Node<T>* newNode = new Node<T>;
	newNode->elem = ele;
	newNode->next = head;
	newNode->prev = NULL;
	newNode->next->prev = newNode;

	head = newNode;
}

// Deletes the current 'head' node then has the 'head' node point to the
// next node in the list. 
//
// Exeception is thrown if this is attempted on an empty list.
template <typename T>
void LinkedList<T>::deleteFront()
{
	try
	{
		if (empty())
			throw ListException();

		Node<T>* oldFront = head;
		head = head->next;
		head->prev = NULL;

		delete oldFront;

	}
	catch (ListException e)
	{
		std::cout << e.what();
	}
}

// Loops through list and prints each node element.
template <typename T>
void LinkedList<T>::outputAll()
{
	Node<T>* temp = head;
	while (temp != NULL)
	{
		std::cout << temp->elem << std::endl;
		temp = temp->next;
	}
}

// Loops through list to count each element then returns
// the amount.
template <typename T>
int LinkedList<T>::count()
{
	Node<T>* temp = head;
	int count = 0;
	while (temp != NULL)
	{
		temp = temp->next;
		count++;
	}
	return count;
}

// a template function to delete the last elemnt of the linked list
template <typename T>
void LinkedList<T>::deleteLast()
{
	Node<T>* temp = head;
	Node<T>* temp2 = head;
	while (temp->next != NULL)
	{
		temp2 = temp;
		temp = temp->next;
	}
	temp2->next = NULL;
	temp->prev = NULL;

	delete temp;
}

// a template function to add an element to the end of the linked list
template <typename T>
void LinkedList<T>::addLast(const T& ele)
{
	Node<T>* temp = head;
	while (temp->next != NULL)
	{
		temp = temp->next;
	}
	Node<T>* newNode = new Node<T>;
	newNode->elem = ele;
	newNode->next = NULL;
	temp->next = newNode;
	newNode->prev = temp;
}

// a template function to reverse the linked list
template <typename T>
void LinkedList<T>::reverse()
{
        // Initialize current, previous and next pointers
        Node<T>* current = head;
        Node<T>*prev = NULL, *next = NULL;
 
        while (current != NULL) {
            // Store next
            next = current->next;
            // Reverse current node's pointer
            current->next = prev;
            // Move pointers one position ahead.
            prev = current;
            current = next;
        }
        head = prev;
}

// a template function to sort a linked list
template <typename T>
void LinkedList<T>::sort()
{
	
}




int main(void)
{
	LinkedList<int> list;
	list.addFront(1);
	list.addFront(2);
	list.addFront(3);
	list.addFront(4);

	list.outputAll();

	list.reverse();

	list.outputAll();
}










// Overloaded Assignment Operator takes another list as the parameter 'source' and
// returns a ref to 'this' list (for list=list1=list2 operations).
// Assignment accomplished by first checking which list has greater size,
// if the original list contains more elements it is trimmed to the size of the 'source'
// list. If the 'source' list is larger elements are added to the original list. Next, 
// the orginial list is overwritten with the data from the source list.
//
// This is a Non-Destructive copy that leaves the original list intact, for large copies it
// is not perfered (see overloaded move assignment operator).
//
// Example of calling this overloaded operator:
// list1 = list;
template <typename T>
LinkedList<T>& LinkedList<T>::operator=(LinkedList<T>& source)
{
	if (this == &source)
		return *this;

	Node<T>* tempThis = head;
	Node<T>* tempSource = source.head;

	int diff = this->count() - source.count();

	if (diff > 0)
	{
		for (int i = 0; i < diff; i++)
		{
			this->deleteFront();
		}
	}
	tempThis = head;

	for (int i = 0; i < source.count(); i++)
	{

		if ((tempThis->next == NULL) && (i != source.count() - 1))
		{
			Node<T>* newNode = new Node<T>;
			tempThis->next = newNode;
			newNode->next = NULL;

		}
		tempThis->elem = tempSource->elem;
		tempThis = tempThis->next;
		tempSource = tempSource->next;

	}

	return *this;
}

// Overloaded Assignment Move Operator takes an Rvalue list as the parameter 'source'
// and returns a ref to 'this' list (for list=std::move(list1)=std::move(list2) operations).
// Move is accomplished by freeing the resources to the original list and re-instantiating
// its 'head' node as the 'head' node of the 'source' list.
//
// This IS a destructive move as now both the original list and the 'source' list are pointing
// to the same memory ie. data is not copied, the resources are moved.
//
// Example of calling this overloaded operator:
// list1 = std::move(list);
template <typename T>
LinkedList<T>& LinkedList<T>::operator=(LinkedList<T>&& source)
{
	if (this == &source)
		return *this;

	this->~LinkedList();
	head = source.head;

	return *this;
}

// Overloaded addition operator takes list as the parameter 'source' and
// returns a ref to 'this' list (for list+list1+list2 operations).
// Addition is analogous to appending two lists as the 'source' list simply
// has each of its elements added to the front of the original list.
//
// Example of calling this overloaded operator:
// list1 + list;
// 'list1' now has all of the elements of 'list' added to it.
template <typename T>
LinkedList<T>& LinkedList<T>::operator+(LinkedList<T>& source)
{
	if (source.count() == 0)
		return *this;

	Node<T>* temp = source.head;

	for (int i = 0; i < source.count(); i++)
	{
		addFront(temp->elem);
		temp = temp->next;
	}

	return *this;
}