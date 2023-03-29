#include <iostream>
#include <map>
#include "bst.h"
#include "avlbst.h"

using namespace std;


int main(int argc, char *argv[])
{
	// Binary Search Tree tests

	/*
	BinarySearchTree<char,int> bt;
	bt.insert(std::make_pair('b',1));
	bt.insert(std::make_pair('a',2));
	bt.insert(std::make_pair('c',5));
	bt.insert(std::make_pair('e',5));
	bt.insert(std::make_pair('f',5));
	bt.insert(std::make_pair('d',5));

	cout << "Binary Search Tree contents:" << endl;
	
	for(BinarySearchTree<char,int>::iterator it = bt.begin(); it != bt.end(); ++it) {
			cout << "here!" << endl;
			cout << it->first << " " << it->second << endl;
	}

	if(bt.find('b') != bt.end()) {
			cout << "Found b" << endl;
	}
	else {
			cout << "Did not find b" << endl;
	}
	cout << "Erasing b" << endl;
	bt.remove('b');

	
	*/

	

	// AVL Tree Tests
	AVLTree<char,int> at;
	at.insert(std::make_pair('a',1));
	at.insert(std::make_pair('c',2));
	at.insert(std::make_pair('b',3));
	at.insert(std::make_pair('d',1));
	at.insert(std::make_pair('f',2));
	at.insert(std::make_pair('e',3));
	at.insert(std::make_pair('j',1));

	at.insert(std::make_pair('g',2));
	at.insert(std::make_pair('k',3));
	at.insert(std::make_pair('u',1));
	at.insert(std::make_pair('q',2));
	at.insert(std::make_pair('w',3));

	at.insert(std::make_pair('t',1));
	at.insert(std::make_pair('h',2));
	at.insert(std::make_pair('x',3));
	at.insert(std::make_pair('r',1));
	at.insert(std::make_pair('i',2));
	at.insert(std::make_pair('n',3));
	at.insert(std::make_pair('p',1));
	at.insert(std::make_pair('m',2));
	at.insert(std::make_pair('z',3));
	at.insert(std::make_pair('v',1));
	at.insert(std::make_pair('l',2));
	at.insert(std::make_pair('s',3));
	
	
	//at.insert(std::make_pair('b',3));
	//at.insert(std::make_pair('a',3));



	cout << "\nAVLTree contents:" << endl;
	for(AVLTree<char,int>::iterator it = at.begin(); it != at.end(); ++it) {
			cout << it->first << " " << endl; //(*it)->getBalance()
	}
	/*
	if(at.find('b') != at.end()) {
			cout << "Found b" << endl;
	}
	else {
			cout << "Did not find b" << endl;
	}
	cout << "Erasing b" << endl;
	at.remove('b');
	*/
	

	cout << "Reached end! Wahoo!" << endl;

  return 0;
}
