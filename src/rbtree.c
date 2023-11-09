#include "rbtree.h"

#include <stdlib.h>

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
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

void left_rotate(rbtree* t, node_t* node){
	// node_t* parent = node->parent;
	// node_t* g_parent = parent->parent;
	// node_t* right = node->right;

	// if(parent==t->root){
	// 	t->root=node;
	// }else{
	// 	if(g_parent->left == parent) g_parent->left = node;
	// 	else g_parent->right = node;
	// }
  	// node->parent = g_parent;
    // parent->parent = node;
    // node->right = parent;
    // right->parent = parent;
    // parent->left = right;
	node_t* y = node->right;
	node->right=y->left;
	if(y->left!=t->nil){
		y->left->parent = node;
	}  
	y->parent = node->parent;
	if(node->parent==t->nil){
		t->root = y;
	}else if(node == node->parent->left){
		node->parent->left = y;
	}else node->parent->right = y;
	y->left=node;
	node->parent = y;
}
void right_rotate(rbtree* t, node_t* node){
	// node_t* parent = node->parent;
	// node_t* grand_parent = parent->parent;
	// node_t* left = node->left;


	// if (parent == t->root)
	// 	t->root = node;
	// else
	// {
	// 	if (grand_parent->left == parent)
	// 	grand_parent->left = node;
	// 	else
	// 	grand_parent->right = node;
	// }
	// node->parent = grand_parent; 
	// parent->parent = node;      
	// node->left = parent;       
	// parent->right = left;
	// left->parent = parent;
	node_t* y = node->left;
	node->left=y->right;
	if(y->right!=t->nil){
		y->right->parent = node;
	}  
	y->parent = node->parent;
	if(node->parent==t->nil){
		t->root = y;
	}else if(node == node->parent->right){
		node->parent->right = y;
	}else node->parent->left = y;
	y->right=node;
	node->parent = y;
}
void exchange_color(node_t* a, node_t* b)
{
  int tmp = a->color;
  a->color = b->color;
  b->color = (tmp == RBTREE_BLACK) ? RBTREE_BLACK : RBTREE_RED;
}

void rbtree_insert_fixup(rbtree* t, node_t* new){
	// node_t* parent = new->parent;
	// node_t* g_parent = parent->parent;

	// if (new == t->root){
	// 	new->color=RBTREE_BLACK;
	// return;
	// }

	// if(parent->color==RBTREE_BLACK){
	// 	return;
	// }
	// node_t* uncle = (parent == g_parent->left)?g_parent->right:g_parent->left;
	// if(uncle->color==RBTREE_RED){
	// 	parent->color=RBTREE_BLACK;
	// 	uncle->color=RBTREE_BLACK;
	// 	g_parent->color=RBTREE_RED;
	// 	rbtree_insert_fixup(t,g_parent);
	// 	return;
	// }

	// if(parent == g_parent->left){
	// 	if(new == parent->left){
	// 		right_rotate(t, parent);
	// 		exchange_color(parent,parent->right);
	// 		return;
	// 	}

	// 	left_rotate(t, new);
	// 	right_rotate(t, new);
	// 	exchange_color(new, new->right);
	// 	return;
	// }
	// else if(new==parent->left){
	// 	right_rotate(t, new);
	// 	left_rotate(t, new);
	// 	exchange_color(new, new->left);
	// 	return;
	// }
	// left_rotate(t, parent);
	// exchange_color(parent,parent->left);
	node_t* y;
	while(new->parent->color == RBTREE_RED){
		if(new->parent == new->parent->parent->left){
			y=new->parent->parent->right;
			if(y->color==RBTREE_RED){
				new->parent->color=RBTREE_BLACK;
				y->color = RBTREE_BLACK;
				new->parent->parent->color=RBTREE_RED;
				new = new->parent->parent;
			}else if( new == new->parent->right){
				new = new->parent;
				left_rotate(t,new);
			}
			else{
				new->parent->color = RBTREE_BLACK;
				new->parent->parent->color = RBTREE_RED;
				right_rotate(t, new->parent->parent);
			}
		}else{
			y=new->parent->parent->left;
			if(y->color==RBTREE_RED){
				new->parent->color=RBTREE_BLACK;
				y->color = RBTREE_BLACK;
				new->parent->parent->color=RBTREE_RED;
				new = new->parent->parent;
			}else if( new == new->parent->left){
				new = new->parent;
				right_rotate(t,new);
			}
			else{
				new->parent->color = RBTREE_BLACK;
				new->parent->parent->color = RBTREE_RED;
				left_rotate(t, new->parent->parent);
			}
		}
	}
	t->root->color=RBTREE_BLACK;
}



node_t *rbtree_insert(rbtree *t, const key_t key) {
	// TODO: implement insert
	// node_t* newNode = createNode(t, key);
	// node_t* node=t->nil;
	// node_t* current = t->root;
	// while(current != t->nil){
	// 	node = current;
	// 	if(key < current->key){
	// 		current=current->left;
	// 	}else{
	// 		current=current->right;
	// 	}
	// }
	// newNode->parent = node;
	// if (node == t->nil) {
    // 	t->root = newNode;
	// }else if(node->key<newNode->key){
	// 	node->right=newNode;
	// }else{                            
	// 	node->left=newNode;
	// }

	// // Fix-up function
	// rbtree_insert_fixup(t, newNode);
	// return newNode;
	node_t* z = createNode(t, key);
	node_t* y = t->nil;
	node_t* x = t->root;

	while(x!=t->nil){
		y=x;
		if(z->key < x->key){
			x = x->left;
		}else x = x->right;
	} 
	z->parent = y;
	if( y==t->nil)t->root=z;
	else if(z->key < y->key) y->left=z;
	else y->right=z;
	rbtree_insert_fixup(t,z);
	return z;
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
	node_t* current = t->root;
	while (current!=t->nil){
		if (current->left==t->nil) return current;
		current = current->left;
	}
	return current->parent;
}

node_t *rbtree_max(const rbtree *t) {
	// TODO: implement find
	node_t* current = t->root;
	while(current!=t->nil){
		if(current->right==t->nil) return current;
		current=current->right;
	}
	return current->parent;
}

void rbtree_transplant(rbtree* t, node_t* u, node_t* v){
	if(u->parent == t->nil) t->root=v;
	else if(u==u->parent->left) u->parent->left=v;
	else u->parent->right=v;
	v->parent=u->parent;
}

void rbtree_erase_fixup(rbtree* t, node_t* x){
	while((x!=t->root) && (x->color == RBTREE_BLACK)){
		if(x==x->parent->left){
			node_t* uncle = x->parent->right;
			if(uncle->color==RBTREE_RED){
				uncle->color=RBTREE_BLACK;
				x->parent->color=RBTREE_RED;
				left_rotate(t,x->parent);
				uncle = x->parent->right;
			}
			if((uncle->left->color == RBTREE_BLACK) && (uncle->right->color==RBTREE_BLACK)){
				uncle->color=RBTREE_RED;
				x=x->parent;
			}else if(uncle->right->color==RBTREE_BLACK){
				uncle->left->color=RBTREE_BLACK;
				uncle->color=RBTREE_RED;
				right_rotate(t,uncle);
				uncle=x->parent->right;
			}
			else{
				uncle->color=x->parent->color;
				x->parent->color=RBTREE_BLACK;
				uncle->right->color=RBTREE_BLACK;
				left_rotate(t,x->parent);
				x=t->root;
			}
		}else{
			node_t* uncle = x->parent->left;
			if(uncle->color==RBTREE_RED){
				uncle->color=RBTREE_BLACK;
				x->parent->color=RBTREE_RED;
				right_rotate(t,x->parent);
				uncle = x->parent->left;
			}
			if((uncle->right->color == RBTREE_BLACK) && (uncle->left->color==RBTREE_BLACK)){
				uncle->color=RBTREE_RED;
				x=x->parent;
			}else if(uncle->left->color==RBTREE_BLACK){
				uncle->right->color=RBTREE_BLACK;
				uncle->color=RBTREE_RED;
				left_rotate(t,uncle);
				uncle=x->parent->left;
			}
			else{
				uncle->color=x->parent->color;
				x->parent->color=RBTREE_BLACK;
				uncle->left->color=RBTREE_BLACK;
				right_rotate(t,x->parent);
				x=t->root;
			}
		}
	}
	x->color=RBTREE_BLACK;
}

node_t* find_succesor(rbtree* t, node_t* node){
	node_t* current = t->nil;
	while(node != t->nil){
		current = node;
		node = node->left;
	}
	return current;
}

int rbtree_erase(rbtree *t, node_t *p) {
	// TODO: implement erase
	node_t* y =p;
	node_t* x = t->nil;
	color_t y_original_color = y->color;
	if(p->left == t->nil){
		x=p->right;
		rbtree_transplant(t,p,p->right);
	}else if(p->right==t->nil){
		x=p->left;
		rbtree_transplant(t,p,p->left);
	}else{
		y=find_succesor(t,p->right);
		y_original_color=y->color;
		x=y->right;
		if(y->parent==p) x->parent = y;
		else {
			rbtree_transplant(t,y,y->right);
			y->right=p->right;
			y->right->parent=y;
		}
		rbtree_transplant(t,p,y);
		y->left=p->left;
		y->left->parent=y;
		y->color=p->color;
	}
	if (y_original_color==RBTREE_BLACK) rbtree_erase_fixup(t,x);
	free(p);
	return 0;
}


int rbtree_to_array(const rbtree *t, key_t *arr, const size_t n) {
	int i = 0;
	void array_recursion(node_t* node){
		if(node != t->nil){
			array_recursion(node->left);
			arr[i]=node->key;
			i++;
			array_recursion(node->right);
		}
	}
	array_recursion(t->root);
	for(int k=0;k<n;k++){
		printf("%d,",arr[k]);
	}
	return 0;
}


// int main(){
// 	rbtree *t = new_rbtree();
// 	key_t entries[] = {10, 5, 8, 34, 67, 23, 156, 24, 2, 12};
// 	const size_t n = sizeof(entries) / sizeof(entries[0]);
// 	for(int i =0; i<10;i++){
// 		rbtree_insert(t,entries[i]);
// 	}
// 	printf("%d\n",t->root->key);
// 	printf("%d\n",rbtree_min(t)->key);
// }