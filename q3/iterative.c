/* iterative version */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

static double diff_in_second(struct timespec t1, struct timespec t2)
{
    struct timespec diff;
    if (t2.tv_nsec-t1.tv_nsec < 0) {
        diff.tv_sec  = t2.tv_sec - t1.tv_sec - 1;
        diff.tv_nsec = t2.tv_nsec - t1.tv_nsec + 1000000000;
    } else {
        diff.tv_sec  = t2.tv_sec - t1.tv_sec;
        diff.tv_nsec = t2.tv_nsec - t1.tv_nsec;
    }
    return (diff.tv_sec + diff.tv_nsec / 1000000000.0);
}

typedef struct __TREENODE {
	int value;
	struct __TREENODE *left;
	struct __TREENODE *right;
} TreeNode;

void flatten(TreeNode *root)
{
	TreeNode *cur = root, *temp;

	while (cur->left != NULL || cur->right != NULL) {
		if (cur->right != NULL) {
			if (cur->left != NULL) {
				temp = cur->left;
				while (temp->right != NULL) {
					temp = temp->right;
				}
				temp->right = cur->right;
				cur->right = NULL;
			}
			else {
				cur = cur->right;
			}
		}
		else {
			cur->right = cur->left;
			cur->left = NULL;
		}
	}
}

/* testing tree
       1
     /   \
    2     3
  /   \    \
 4     5    6
*/
TreeNode *creatTree(TreeNode *root)
{
	TreeNode *node1 = (TreeNode *) malloc(sizeof(TreeNode));
	node1->value = 1;
	TreeNode *node2 = (TreeNode *) malloc(sizeof(TreeNode));
	node2->value = 2;
	TreeNode *node3 = (TreeNode *) malloc(sizeof(TreeNode));
	node3->value = 3;
	TreeNode *node4 = (TreeNode *) malloc(sizeof(TreeNode));
	node4->value = 4;
	TreeNode *node5 = (TreeNode *) malloc(sizeof(TreeNode));
	node5->value = 5;
	TreeNode *node6 = (TreeNode *) malloc(sizeof(TreeNode));
	node6->value = 6;

	root = node1;
	node1->left = node2;
	node1->right = node5;
	node2->left = node3;
	node2->right = node4;
	node3->left = NULL;
	node3->right = NULL;
	node4->left = NULL;
	node4->right = NULL;
	node5->left = NULL;
	node5->right = node6;
	node6->left = NULL;
	node6->right = NULL;

	return root;
}

void printTree(TreeNode *root)
{
	TreeNode *cur = root;
	while (cur != NULL) {
		printf("%d\t", cur->value);
		cur = cur->right;
	}
	printf("\n");
}

int main()
{
    struct timespec start, end;

	TreeNode *root = (TreeNode *) malloc(sizeof(TreeNode));
	root = creatTree(root);

    /* compute the execution time */
    clock_gettime(CLOCK_REALTIME, &start);

    int i;
    for (i = 0; i < 10000; ++i) {
		flatten(root);
	}

    clock_gettime(CLOCK_REALTIME, &end);
    double cpu_time = diff_in_second(start, end);

	printTree(root);
    printf("execution time: %lf sec\n", cpu_time);

    return 0;
}
