#include "rbtree.h"

#include <stdlib.h>

rbtree *new_rbtree(void) {
  rbtree *p = (rbtree *)calloc(1, sizeof(rbtree));
  // TODO: initialize struct if needed
  node_t* nil = (node_t*)calloc(1,sizeof(node_t));
  p->nil = p->root = nil;
  p->nil->color = RBTREE_BLACK;
  return p;
}
void rbtree_delete_recursion(rbtree* t, node_t* node){
  if(node == t->nil) return;
  rbtree_delete_recursion(t, node->left);
  rbtree_delete_recursion(t,node->right);
  free(node);
}
 
void delete_rbtree(rbtree *t) {
  // TODO: reclaim the tree nodes's memory
  node_t* root = t->root;
  if (root != t->nil){
    rbtree_delete_recursion(t, root);
  }
  free(t->nil);
  free(t);
}

node_t* createNode(rbtree* t, const key_t key){
  node_t* newNode = (node_t*)calloc(1,sizeof(node_t));
  newNode->key = key;
  newNode->color = RBTREE_RED;
  newNode->left = t->nil;
  newNode->right = t->nil;
  return newNode;
}

void right_rotate(rbtree* t, node_t* node){
	node_t* parent = node->parent;
	node_t* g_parent = parent->parent;
	node_t* right = node->right;

	if(parent==t->nil){
		t->root=node;
	}else{
		if(g_parent->left == parent) g_parent->left = node;
		else g_parent->right = node;
	}
  	node->parent = g_parent;
    parent->parent = node;
    node->right = parent;
    right->parent = parent;
    parent->left = right;

  
}
void left_rotate(rbtree* t, node_t* node){

	node_t* parent = node->parent;
	node_t* grand_parent = parent->parent;
	node_t* left = node->left;


	if (parent == t->root)
		t->root = node;
	else
	{
		if (grand_parent->left == parent)
		grand_parent->left = node;
		else
		grand_parent->right = node;
	}
	node->parent = grand_parent; 
	parent->parent = node;      
	node->left = parent;       
	parent->right = left;
	left->parent = parent;
}
void exchange_color(node_t* a, node_t* b)
{
  int tmp = a->color;
  a->color = b->color;
  b->color = (tmp == RBTREE_BLACK) ? RBTREE_BLACK : RBTREE_RED;
}

void rbtree_insert_fixup(rbtree* t, node_t* new){
	node_t* parent = new->parent;
	node_t* g_parent = parent->parent;

	if (new == t->root){
		new->color=RBTREE_BLACK;
	return;
	}

	if(parent->color==RBTREE_BLACK){
		return;
	}
	node_t* uncle = (parent == g_parent->left)?g_parent->right:g_parent->left;
	if(uncle->color==RBTREE_RED){
		g_parent=RBTREE_RED;
		uncle->color = parent->color = RBTREE_BLACK;
		rbtree_insert_fixup(t,g_parent);
		return;
	}

	if(parent == g_parent->left){
		if(new == parent->left){
			right_rotate(t, parent);
			exchange_color(parent,parent->right);
			return;
		}

		left_rotate(t, new);
		right_rotate(t, new);
		exchange_color(new, new->right);
		return;
	}
	else if(new==parent->left){
		right_rotate(t, new);
		left_rotate(t, new);
		exchange_color(new, new->left);
		return;
	}
	left_rotate(t, parent);
	exchange_color(parent,parent->left);
}


node_t *rbtree_insert(rbtree *t, const key_t key) {
	// TODO: implement insert
	node_t* newNode = createNode(t, key);
	node_t* node=t->nil;
	node_t* current = t->root;
	while (current != t->nil){
		node=current;
		if (current->key < key) current = current->right;
		else current = current->left;
	}
	newNode->parent = node;
	if (current == t->nil) t->root = newNode;
	else if (newNode->key < current->key) current->left = newNode;
	else current->right = newNode;
	// Fix-up function
	rbtree_insert_fixup(t, newNode);
	return newNode;
}

node_t *rbtree_find(const rbtree *t, const key_t key) {
  	// TODO: implement find
	node_t* current = t->root;

	while(current!=t->nil){
		if(current->key == key) return current;
		current = (current->key<key)?current->right:current->left;
	}
	// return t->root;
	return NULL;
}

node_t *rbtree_min(const rbtree *t) {
	// TODO: implement find
	node_t* current = t->nil;
	while (current!=t->nil){
		current = current->left;
	}
	return current->parent;
}

node_t *rbtree_max(const rbtree *t) {
	// TODO: implement find
	node_t* current = t->nil;
	while(current!=t->nil){
		current=current->right;
	}
	return current->parent;
}

int rbtree_erase(rbtree *t, node_t *p) {
	// TODO: implement erase
	return 0;
}

int rbtree_to_array(const rbtree *t, key_t *arr, const size_t n) {
	// TODO: implement to_array
	return 0;
}
