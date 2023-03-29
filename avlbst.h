 #ifndef AVLBST_H
#define AVLBST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <cstdint>
#include <algorithm>
#include "bst.h"

struct KeyError { };

/**
* A special kind of node for an AVL tree, which adds the balance as a data member, plus
* other additional helper functions. You do NOT need to implement any functionality or
* add additional data members or helper functions.
*/
template <typename Key, typename Value>
class AVLNode : public Node<Key, Value>
{
public:
    // Constructor/destructor.
    AVLNode(const Key& key, const Value& value, AVLNode<Key, Value>* parent);
    virtual ~AVLNode();

    // Getter/setter for the node's height.
    int8_t getBalance () const;
    void setBalance (int8_t balance);
    void updateBalance(int8_t diff);

    // Getters for parent, left, and right. These need to be redefined since they
    // return pointers to AVLNodes - not plain Nodes. See the Node class in bst.h
    // for more information.
    virtual AVLNode<Key, Value>* getParent() const override;
    virtual AVLNode<Key, Value>* getLeft() const override;
    virtual AVLNode<Key, Value>* getRight() const override;

protected:
    int8_t balance_;    // effectively a signed char
};

/*
  -------------------------------------------------
  Begin implementations for the AVLNode class.
  -------------------------------------------------
*/

/**
* An explicit constructor to initialize the elements by calling the base class constructor
*/
template<class Key, class Value>
AVLNode<Key, Value>::AVLNode(const Key& key, const Value& value, AVLNode<Key, Value> *parent) :
    Node<Key, Value>(key, value, parent), balance_(0)
{

}

/**
* A destructor which does nothing.
*/
template<class Key, class Value>
AVLNode<Key, Value>::~AVLNode()
{

}

/**
* A getter for the balance of a AVLNode.
*/
template<class Key, class Value>
int8_t AVLNode<Key, Value>::getBalance() const
{
    return balance_;
}

/**
* A setter for the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::setBalance(int8_t balance)
{
    balance_ = balance;
}

/**
* Adds diff to the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::updateBalance(int8_t diff)
{
    balance_ += diff;
}

/**
* An overridden function for getting the parent since a static_cast is necessary to make sure
* that our node is a AVLNode.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getParent() const
{
    return static_cast<AVLNode<Key, Value>*>(this->parent_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getLeft() const
{
    return static_cast<AVLNode<Key, Value>*>(this->left_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getRight() const
{
    return static_cast<AVLNode<Key, Value>*>(this->right_);
}


/*
  -----------------------------------------------
  End implementations for the AVLNode class.
  -----------------------------------------------
*/


template <class Key, class Value>
class AVLTree : public BinarySearchTree<Key, Value>
{
public:
    virtual void insert (const std::pair<const Key, Value> &new_item); // TODO

    virtual void remove(const Key& key);  // TODO
protected:
    virtual void nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2);

    // Add helper functions here
		void insertFix(AVLNode<Key,Value>* child, AVLNode<Key,Value>* parent);
		void removeFix(AVLNode<Key,Value> * node, int diff);
		
		void rotateRight(AVLNode<Key,Value>* node);
		void rotateLeft(AVLNode<Key,Value>* node);


};

/*
 * Recall: If key is already in the tree, you should 
 * overwrite the current value with the updated value.
 */
template<class Key, class Value>
void AVLTree<Key, Value>::insert(const std::pair<const Key, Value> &new_item)
{
		//cout << endl;
		//cout << "Inserting: " << new_item.first << endl;
    // TODO
    if(this->empty())
    {
				//cout << "Empty, new root!" << endl;
				AVLNode<Key, Value>* trav = new AVLNode<Key,Value>(new_item.first, new_item.second, NULL);
				trav->setBalance(0);
				this->root_ = trav;
        return;
    }

		Node<Key, Value>* trav = this->root_;
    Node<Key, Value>* parent = NULL;
    bool right = false;	
    while(trav != NULL)
    {
        if(new_item.first < trav->getKey())
        {
            parent = trav;
            trav = trav->getLeft();
            //parent->setLeft(trav);
            right = false;
        }
        else if(new_item.first > trav->getKey())
        {
            parent = trav;
            trav = trav->getRight();
            
            right = true;
        }
        else if(new_item.first == trav->getKey()) //key exists
        {
            trav->setValue(new_item.second);
            return;
        }
    }

    AVLNode<Key, Value>* travIn = new AVLNode<Key, Value>(new_item.first, new_item.second, (AVLNode<Key,Value> *) (parent)); 
		travIn->setBalance(0);  
		AVLNode<Key, Value>* parentIn = travIn->getParent();
    if(right) //tracks ending branch (only possibilites from here)
    {
        parentIn->setRight(travIn);
    }
    else
    {
        parentIn->setLeft(travIn);
    }

		/*
		cout << "BEFORE BALANCE:" << endl;
		int x  = parentIn->getBalance();
		cout << "Parent Balance: [" << x << "]" << endl;
		if(parentIn->getParent() != NULL)
		{
			int y = parentIn->getParent()->getBalance();
			cout << "Grandparent Balance: [" << y << "]" << endl;
		}
		
		*/


    //setBalance
    if(parentIn->getBalance() == 1 || parentIn->getBalance() == -1)
    {
        parentIn->setBalance(0);
    }
    else if(parentIn->getBalance() == 0) //setting out of balance!!!
    {
        if(parentIn->getRight() == travIn)
        {
            parentIn->setBalance(1);
        }
        else if(parentIn->getLeft() == travIn)
        {
            parentIn->setBalance(-1);
        }

        insertFix(travIn, parentIn);
    }
    //this->printRoot(this->root_);

}

template<class Key, class Value>
void AVLTree<Key, Value>::insertFix(AVLNode<Key, Value>* child, AVLNode<Key, Value>* parent)
{
	
	if( parent == NULL || parent->getParent() == NULL)
	{
			//cout << "No check necessary!" << endl;
			return;
	}


	AVLNode<Key, Value> * grandParent = parent->getParent();
	
	if(parent == grandParent->getLeft()) //parent is left child
	{
		grandParent->updateBalance(-1);
		if(grandParent->getBalance() == 0)
		{
			return;
		}
		else if(grandParent->getBalance() == -1)
		{
				insertFix(parent, grandParent);
		}
		else
		{
				
			//zig zig
			if(child == parent->getLeft())
			{
					//cout << "Zig-zig Left parent!" << endl;
					rotateRight(grandParent);
					grandParent->setBalance(0);
					parent->setBalance(0);
			}
			//zig zag
			else
			{
				//cout << "Zig-zag Left parent!" << endl;
				rotateLeft(parent);
				rotateRight(grandParent);

				if(child->getBalance() == -1)
				{
					parent->setBalance(0);
					grandParent->setBalance(1);

				}
				else if(child->getBalance() == 0)
				{
					parent->setBalance(0);
					grandParent->setBalance(0);
				}
				else if(child->getBalance() == 1)
				{
					parent->setBalance(-1);
					grandParent->setBalance(0);
				}					
				child->setBalance(0);
			}
		}

	}
	else //parent is right child
	{
		grandParent->updateBalance(+1);
		if(grandParent->getBalance() == 0)
		{
			return;
		}
		if(grandParent->getBalance() == 1)
		{
			//cout << "grandParent Balance is 1!" << endl;
			insertFix(parent, grandParent);
		}
		else if(grandParent->getBalance() == 2)
		{
			
			//zig zig
			if(child == parent->getRight())
			{
					//cout << "Zig-zig Right parent!" << endl;
					rotateLeft(grandParent);
					grandParent->setBalance(0);
					parent->setBalance(0);
			}
			//zig zag
			else
			{
				//cout << "Zig-zag Right parent!" << endl;
				rotateRight(parent);
				rotateLeft(grandParent);

				if(child->getBalance() == 1)
				{
					parent->setBalance(0);
					grandParent->setBalance(-1);
					
				}
				else if(child->getBalance() == 0)
				{
					parent->setBalance(0);
					grandParent->setBalance(0);
				}
				else if(child->getBalance() == -1)
				{
					parent->setBalance(1);
					grandParent->setBalance(0);
				}
				child->setBalance(0);
			}
		}

		//this->printRoot(this->root_);
	}
	/*
	cout << "AFTER BALANCE:" << endl;
	
	cout << "Done printing root!" << endl;

	int x  = parent->getBalance();
	cout << "Parent Balance: [" << x << "]" << endl;
	if(parent->getParent() != NULL)
	{
		int y = parent->getParent()->getBalance();
		cout << "Grandparent Balance: [" << y << "]" << endl;
	}
	*/
}




template<class Key, class Value>
void AVLTree<Key, Value>::rotateRight(AVLNode<Key,Value>* node)
{
	//cout << "rotating " << node->getKey() << " Right!" << endl;
	AVLNode<Key,Value>* leftChild = node->getLeft();
	AVLNode<Key,Value>* jumpChild = leftChild->getRight();
	AVLNode<Key,Value>* parent = node->getParent();


	if(parent != NULL)
	{
		if(node == parent->getRight()) //node a right child
		{
			parent->setRight(leftChild);
		}
		else //node a left child
		{
			parent->setLeft(leftChild);
		}
	}
	else //shifting root!
	{
		this->root_ = leftChild;
	}
	leftChild->setParent(parent);
	leftChild->setRight(node);

	node->setParent(leftChild);
	node->setLeft(jumpChild);
	if(jumpChild != NULL)
	{
		jumpChild->setParent(node);
	}


	//cout << "Done rotating right!" << endl;
	//this->printRoot(this->root_);
}





template<class Key, class Value>
void AVLTree<Key, Value>::rotateLeft(AVLNode<Key,Value>* node)
{
	//cout << "rotating " << node->getKey() << " Left!" << endl;
	AVLNode<Key,Value>* rightChild = node->getRight();
	AVLNode<Key,Value>* jumpChild = rightChild->getLeft();
	AVLNode<Key,Value>* parent = node->getParent();




	if(parent != NULL)
	{
		if(node == parent->getRight()) //node a right child
		{
			parent->setRight(rightChild);
		}
		else //node a left child
		{
			parent->setLeft(rightChild);
		}
	}
	else //shifting root!
	{
		this->root_ = rightChild;
	}
	
	rightChild->setParent(parent);
	rightChild->setLeft(node);
	node->setParent(rightChild);
	node->setRight(jumpChild);
	if(jumpChild != NULL)
	{
		jumpChild->setParent(node);
	}

	//cout << "Done rotating left!" << endl;

	//this->printRoot(this->root_);
}



template<class Key, class Value>
void AVLTree<Key, Value>::remove(const Key& key)
{
	
	//cout << endl;
	//cout << "Removing: " << key << endl;
	//cout << "BEFORE REMOVAL:" << endl;
	//this->printRoot(this->root_);
	

	AVLNode<Key,Value>* node =  (AVLNode<Key,Value> *) (this->internalFind(key));

	if(node == NULL)
	{
		return;
	}

	if(node->getLeft() != NULL && node->getRight() != NULL)
	{
		nodeSwap(node, (AVLNode<Key,Value>*)this->predecessor(node));
	}

	AVLNode<Key,Value>* parent = node->getParent();
	
	int diff = 0;
	if(parent != NULL)
	{
		if(parent->getRight() == node)
		{
			diff = -1;
		}
		else if(parent->getLeft() == node)
		{
			diff = 1;
		}
	}


	if(node->getLeft() != NULL) //had a left child
  {
		AVLNode<Key, Value> * child = node->getLeft();
		child->setParent(node->getParent());

		AVLNode<Key, Value>* parent = node->getParent();
		
		if(parent == NULL)
		{
				this->root_ = child;
		}
		else if(parent->getRight() == node) //right child
		{
				parent->setRight(child);
		}
		else //left child
		{
				parent->setLeft(child);
    }

  }
	else if(node->getRight() != NULL) //had a right child
  {
		AVLNode<Key, Value> * child = node->getRight();
		child->setParent(node->getParent());
		
		AVLNode<Key, Value>* parent = node->getParent();
		if(parent == NULL)
		{
				this->root_ = child;
		}
		else if(parent->getRight() == node) //right child
		{
				parent->setRight(child);
		}
		else //left child
		{
				parent->setLeft(child);
		}

  }
	else //no children
	{
		AVLNode<Key, Value>* parent = node->getParent();

		if(parent == NULL) //removing top
		{
				this->root_ = NULL;
		}
		else if((parent->getRight()) == node) //right child
		{
				parent->setRight(NULL);
		}
		else //left child
		{
				parent->setLeft(NULL);
		}

	}
	
	

	delete node;



	removeFix(parent, diff);
	/*
	cout << "AFTER REMOVE FIX:" << endl;
	if(parent != NULL)
	{
		cout << "parent: " << parent->getKey() << " has bal: " << (int)parent->getBalance() << endl;
	}
	
	this->printRoot(this->root_);
	*/

}




/*
 * Recall: The writeup specifies that if a node has 2 children you
 * should swap with the predecessor and then remove.
 */
template<class Key, class Value>
void AVLTree<Key, Value>::removeFix(AVLNode<Key,Value> * node, int diff)
{
		if(node != NULL)
		{
			cout << "remove fixing of node!: " << node->getKey() << endl;
    }
		// TODO
		if(node == NULL)
		{
			cout << "Node is null, aborting fix" << endl;
			return;
		}

		int ndiff = 0;

		AVLNode<Key,Value>* parent = node->getParent();

		if(node->getParent() != NULL)
		{
			if(node == parent->getLeft())
			{
				ndiff = 1;
			}
			else
			{
				ndiff = -1;
			}
		}


		if(diff == -1) //right child
		{
			cout << "right Child being removed" << endl;
			if(node->getBalance() + diff == -2)
			{

				AVLNode<Key, Value> * leftChild = node->getLeft();
				
				if(leftChild == NULL)
				{
					cout << "this is nullllll!" << endl;
					return;
				}

				if(leftChild->getBalance() == -1) //zig zig
				{
					rotateRight(node);
					node->setBalance(0);
					leftChild->setBalance(0);
					removeFix(parent,ndiff);
				}
				else if(leftChild->getBalance() == 0) //zig zag
				{
					rotateRight(node);
					node->setBalance(-1);
					leftChild->setBalance(1);
				}
				else if(leftChild->getBalance() == 1) //zig zag
				{
					AVLNode<Key,Value>* right = leftChild->getRight();
					rotateLeft(leftChild);
					rotateRight(node);

					if(right->getBalance() == 1)
					{
						node->setBalance(0);
						leftChild->setBalance(-1);
					}
					else if(right->getBalance() == 0)
					{
						node->setBalance(0);
						leftChild->setBalance(0);
					}
					else if(right->getBalance() == -1)
					{
						node->setBalance(1);
						leftChild->setBalance(0);
					}
					right->setBalance(0);


				}

			}
			else if(node->getBalance() + diff == -1)
			{
				node->setBalance(-1);
				return;
			}
			else if(node->getBalance() + diff == 0)
			{
				node->setBalance(0);
				removeFix(parent, ndiff);
			}
		}
		else //left child
		{
			cout << "left Child being removed" << endl;
			if(node->getBalance() + diff == 2)
			{

				AVLNode<Key, Value> * rightChild = node->getRight();
				
				if(rightChild == NULL)
				{
					cout << "this is nullllll!" << endl;
					return;
				}

				if(rightChild->getBalance() == 1) //zig zig
				{
					rotateLeft(node);
					node->setBalance(0);
					rightChild->setBalance(0);
					removeFix(parent,ndiff);
				}
				else if(rightChild->getBalance() == 0) //zig zag
				{
					rotateLeft(node);
					node->setBalance(1);
					rightChild->setBalance(-1);
				}
				else if(rightChild->getBalance() == -1) //zig zag
				{
					AVLNode<Key,Value>* left = rightChild->getLeft();
					rotateRight(rightChild);
					rotateLeft(node);

					if(left->getBalance() == -1)
					{
						node->setBalance(0);
						rightChild->setBalance(1);
					}
					else if(left->getBalance() == 0)
					{
						node->setBalance(0);
						rightChild->setBalance(0);
					}
					else if(left->getBalance() == 1)
					{
						node->setBalance(-1);
						rightChild->setBalance(0);
					}
					left->setBalance(0);


				}

			}
			else if(node->getBalance() + diff == 1)
			{
				node->setBalance(1);
				return;
			}
			else if(node->getBalance() + diff == 0)
			{
				node->setBalance(0);
				removeFix(parent, ndiff);
			}
		}


}

template<class Key, class Value>
void AVLTree<Key, Value>::nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2)
{
    BinarySearchTree<Key, Value>::nodeSwap(n1, n2);
    int8_t tempB = n1->getBalance();
    n1->setBalance(n2->getBalance());
    n2->setBalance(tempB);
}


#endif
