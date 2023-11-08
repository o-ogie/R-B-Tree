nt == t->nil) t->root = newNode;
	else if (newNode->key < current->key) current->left = newNode;
	else current->right = newN