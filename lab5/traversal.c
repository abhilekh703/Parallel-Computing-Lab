#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
struct node 
{
    int data;
    struct node *left;
    struct node *right;
};
 

struct node* newNode(int data)
{
  struct node* node = (struct node*)malloc(sizeof(struct node));
  node->data = data;
  node->left = NULL;
  node->right = NULL;
  return(node);
}
void postorder(struct node *p,int n) { 
    if (p->left) 
      #pragma omp task 
        postorder(p->left,3); 
    if (p->right) 
      #pragma omp task 
        postorder(p->right,3); 
    #pragma omp taskwait 
    if(p->data == n)
    printf("found\n");  
}
int main()
{
	struct node *root = newNode(1);
	 root->left = newNode(2);
  	 root->right = newNode(3);
  	 root->left->left  = newNode(4);
  	 postorder(root,3);
	return 0;
}
 
