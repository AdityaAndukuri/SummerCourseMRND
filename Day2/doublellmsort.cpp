#include <stdio.h>
#include <stdlib.h>
struct DLLNode{
	int data;
	DLLNode *left, *right;
};


static DLLNode* getDLLNode(int val){
	DLLNode *temp = (DLLNode*)malloc(sizeof(DLLNode));
	temp->data = val;
	temp->left = NULL;
	temp->right = NULL;
	return temp;
}

static DLLNode* split(DLLNode *root){
	DLLNode *slow = root, *fast = root, *mid;
	while (fast&&fast->right){
		slow = slow->right;
		fast = fast->right->right;
	}
	mid = slow;
	if (mid->left)
		mid->left->right = NULL;
	mid->left = NULL;
	return mid;
}

static void printDLL(DLLNode *root){
	while (root){
		printf("%d ", root->data);
		root = root->right;
	}
	printf("\n");
}

static DLLNode* merge(DLLNode *low, DLLNode *mid){
	DLLNode *root = NULL;
	/*printf("LOW:\n");
	printDLL(low);
	printf("MID\n");
	printDLL(mid);*/
	DLLNode *temp, *prev = NULL;
	while (low&&mid){
		prev = low;
		if (low->data < mid->data){
			if (!root)
				root = low;
			low = low->right;
		}
		else{
			if (!root)
				root = mid;
			//printf("here\n");
			temp = mid->right;
			if (low->left)
				low->left->right = mid;
			mid->left = low->left;
			low->left = mid;
			if (mid->right)
				mid->right->left = NULL;
			mid->right = low;
			mid = temp;
		}
	}
	if (mid){
		prev->right = mid;
		mid->left = prev;
		//prev = mid;
		//mid = mid->right;
	}
	//printf("check print\n");
	//printDLL(low);
	return root;
}

static void mergeSort(DLLNode **root){
	DLLNode *mid;
	if ((*root) && (*root)->right){
		mid = split(*root);
		mergeSort(root);
		mergeSort(&mid);
		(*root) = merge((*root), mid);
		//printDLL((*root));
	}
}

static void testMergeSort(){
	int data[] = { 1, 2, 3 };
	int n = 3, i;
	DLLNode *temp, *trav;
	DLLNode *root = NULL;
	for (i = 0; i < n; i++){
		if (!root){
			root = getDLLNode(data[i]);
			trav = root;
		}
		else{
			temp = getDLLNode(data[i]);
			trav->right = temp;
			temp->left = trav;
			trav = temp;
		}
	}
	mergeSort(&root);
	printDLL(root);
}
