/* Ben
reviewed by Alex 08.10 */
#include <stdlib.h>
#include "binary_search_tree_additional.h"
#include "binary_search_tree.h"

struct bst
{
	void*  key;
	bst_t* left;
	bst_t* right;
	compare_func_t cmp;
};


bst_t *BstCreate(compare_func_t cmp) 
{
	bst_t* root = (bst_t*)malloc(sizeof(bst_t));
	
	root->key = NULL;
	root->left = NULL;
	root->right = NULL;
	root->cmp = cmp;
	
	return root;
}

void BstDestroy(bst_t *bst) 
{	
	if (!bst)
	{
		return;
	}
	
	if (!bst->left || !bst->right)
	{
		if (!bst->left && !bst->right)
		{
			free(bst);
			bst = NULL;
			return;
		}
		return;
	}
	
	BstDestroy(bst->left);
	BstDestroy(bst->right);
	
	free(bst);
	bst = NULL;
}

void BstRemove(bst_t *bst, const void *data) 
{
	bst_t 	   *remove = (bst_t*)BstFind(bst, data);
	bst_t 	   *temp = bst;
	int	    status = 1;	

	
	if (!remove)
	{
		return;
	}
	
	if (!bst->right)
	{
		temp = SwitchValues(bst->left, status);
	}
	
	temp = SwitchValues(bst->right, 0);
	
	remove->key = temp->key;
	remove->left = temp->left;
	remove->right = temp->right;
	free(temp);
	temp = NULL;
}

int BstInsert(bst_t *bst, void *data) 
{
	if (BstFind(bst, data))
	{
		return 3;
	}
	else if (!bst->key)
	{
		bst->key = data;
		return 1;
	}
	else if (!bst)
	{
		NewNode(data, bst->cmp);
		return 1;
	}

	if (bst->cmp(bst->key, data) < 0)		
	{
		if (!bst->right)
		{
			bst->right = NewNode(data, bst->cmp);
			return 1;
		}
		BstInsert(bst->right, data);
	}
	else
	{
		if (!bst->left)
		{
			bst->left = NewNode(data, bst->cmp);
			return 1;
		}
		BstInsert(bst->left, data);
	}
	
	return 0;
}

void *BstFind(bst_t *bst, const void *data)
{
	if (!bst)
	{
		return NULL;
	}
	else if (!bst->cmp(bst->key, data))
	{
		return bst;
	}
	else if (!bst->left || !bst->right)
	{
		return NULL;
	}
	
	
	BstFind(bst->left, data);
	BstFind(bst->right, data);
	
	return NULL;
}

int BstForEach(bst_t *bst, action_function_t action_func, void *param)
{
	if (!bst)
	{
		return 0;
	}
	
	action_func(bst->key, param);
	
	BstForEach(bst->left, action_func, param);
	BstForEach(bst->right, action_func, param);
	
	return 1;
}

size_t BstSize(const bst_t *bst)
{
	if (!bst)
	{
		return 0;
	}
	else
	{
		return (BstSize(bst->right) + 1 + BstSize(bst->left));
	}
}

int BstIsEmpty(const bst_t *bst)
{
	if ((!bst->left && !bst->right && !bst->key) || !bst)
	{
		return 1;
	}

		return 0;
}

bst_t *SwitchValues(bst_t* bst, int data)
{
	if (!bst)
	{
		return NULL;
	}
	else if (data && !bst->right)
	{
		return NULL;
	}
	else if (data)
	{
		SwitchValues(bst->right, data);
	}
	else if (!bst->left && !bst->right)
	{
		return NULL;
	}
	else
	{
		SwitchValues(bst->left, data);
	}
	
	return bst;
}

bst_t *NewNode(void* data, compare_func_t cmp)
{
	bst_t* new = (bst_t*)malloc(sizeof(bst_t));
	
	new->key = data;
	new->left = NULL;
	new->right = NULL;
	new->cmp = cmp;
	
	return new;
}


