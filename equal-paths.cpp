#ifndef RECCHECK
//if you want to add any #includes like <iostream> you must do them here (before the next endif)
#include <iostream>
#endif

#include "equal-paths.h"
using namespace std;


// You may add any prototypes of helper functions here


bool equalPaths(Node * root)
{
    // Add your code below
    
		int rootDepth = depth(root);
		
		if(rootDepth == -1)
		{
			return false;
		}
		return true;
    
}

int depth(Node* root)
{
	if(root == NULL)
	{
		return 0;
	}
	else
	{
		int left = depth(root->left);
		int right = depth(root->right);

		cout<< left << " " << right << endl;
		if(right == -1 || left == -1)
		{
			return -1;
		}
		if(right == left)
		{
			return left + 1;
		}
		else if(right == 0)
		{
			return left + 1;
		}
		else if(left == 0)
		{
			return right + 1;
		}
		else
		{
			return -1;
		}
		
	}
}

