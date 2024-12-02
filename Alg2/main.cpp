#include <iostream>
#define SIZE 25
void gen_rand(int a[SIZE]);
struct Node* insertNode(struct Node* root, int data);
void printTree(struct Node* root, int space);


struct Node { 
	int data;
	struct Node* left;
	struct Node* right; 
};

int main(){
	int arr[SIZE];
	gen_rand(arr);
	struct Node* root = NULL;
	root = insertNode(root, arr[0]);
	for(int i = 1; i < SIZE; ++i){
		printf("%d\n", arr[i]);
		insertNode(root, arr[i]);
	}
	printTree(root, 0);


}

void gen_rand(int a[SIZE]){//generation of array of random data
	for(int i = 0; i < SIZE; ++i){
		while(true){
			a[i] = rand()%100 + 100;
			for(int j = 0; j < i; ++j){
				if(a[i] == a[j]){
					continue;
				}
			}
			break;
		}
	}

}

struct Node* createNode(int data) {//creating new node
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;//inserting data
    newNode->left = NULL;//putting child nodes as undefined
		newNode->right = NULL;
    return newNode;
}

struct Node* insertNode(struct Node* root, int data) {
    if (root == NULL) {
        return createNode(data);
    }

    if (data < root->data) {
        root->left = insertNode(root->left, data);
    } else if (data > root->data) {
        root->right = insertNode(root->right, data);
    }

    return root;
}

/*void printTree(struct Node *root, int level)
{      
    if (root->left) 
        printTree(root->left, level + 1);
    for (int i = 0; i < level; i++)
         std::cout << " ";
    std::cout << root->data << std::endl;
    if (root->right) 
       printTree(root->right, level + 1);
}*/

void printTree(struct Node* root, int space) {
    int COUNT = 10;
    if (root == NULL) {
        return;
    }

    space += COUNT;

    printTree(root->right, space);
    printf("\n");
    for (int i = COUNT; i < space; i++) {
        printf(" ");
    }
    printf("%d\n", root->data);
    printTree(root->left, space);
}

