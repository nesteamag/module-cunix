#include "../include/binary_tree.h"
#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>

node_t  *allocnode()
{
node_t *tree= (node_t*)malloc(sizeof(node_t));
tree->left = NULL;
tree->right = NULL;
tree->key = NULL;
tree->data = NULL;
return tree;
}

node_t  *insert(node_t *root, char *key, void *data)
{
if (root == NULL)
{
  root = allocnode();
  root->key = key;
  root->data = data;
}
else
{
if(strcmp(root->key,key) > 0)
  root->left = insert(root->left, key, data);
else root->right = insert(root->right, key, data);
}
return root;
}

void    print_node(node_t *node)
{
if (node!= NULL)
{
  print_node(node->left);
  if (node->left != NULL && node->right !=NULL)
    printf("%s", node->data);
  print_node(node->right);
}
}


void 		visit_tree(node_t *node, void (*fp)(node_t *root))
{
  	if(node->right != NULL)
  	{
    		if(node->left != NULL)
    		{
      			visit_tree(node->left, fp);
      			visit_tree(node->right, fp);
    		}
    		else		visit_tree(node->right, fp);
  	}
  	else
  		if(node->left != NULL)
    			visit_tree(node->left, fp);
  	fp(node);
}

void    destroy_tree(node_t *node, void (*fdestroy)(node_t *root))
 {
if(node->right != NULL)
  	{
    		if(node->left != NULL)
    		{
      			destroy_tree(node->left, fdestroy);
      			destroy_tree(node->right, fdestroy);
    		}
    		else destroy_tree(node->right, fdestroy);
  	}
  	else
  	 if(node->left != NULL)
        destroy_tree(node->left, fdestroy);
	fdestroy(node);
	free(node);
}