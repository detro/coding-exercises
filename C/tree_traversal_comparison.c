#include <stdio.h>
#include <stdlib.h>

typedef struct node_s {
    int value;
    struct node_s *left;
    struct node_s *right;
} node;

node *create_node(const int value, node *left, node *right) {
    node *new_node = (node *)malloc(sizeof(node));

    new_node->value = value;
    new_node->left = left;
    new_node->right = right;

    return new_node;
}

void recursive_pre_order_traversal(const node *root) {
    static int counter = 1;

    printf("%d: %d\n", counter++, root->value);

    if (root->left != NULL) {
        recursive_pre_order_traversal(root->left);
    }

    if (root->right != NULL) {
        recursive_pre_order_traversal(root->right);
    }
}

void recursive_in_order_traversal(const node *root) {
    static int counter = 1;
    if (root->left != NULL) {
        recursive_in_order_traversal(root->left);
    }
    printf("%d: %d\n", counter++, root->value);
    if (root->right != NULL) {
        recursive_in_order_traversal(root->right);
    }
}

void recursive_post_order_traversal(const node *root) {
    static int counter = 1;
    if (root->left != NULL) {
        recursive_post_order_traversal(root->left);
    }

    if (root->right != NULL) {
        recursive_post_order_traversal(root->right);
    }

    printf("%d: %d\n", counter++, root->value);
}

#define UP      1
#define DOWN    2

void de_marino_bst_post_order_traversal(node *root) {
    node *curr = root;  //< current node
    node *par = NULL;   //< parent of current node
    node *next = root;  //< next node to traversal (but sometimes, just temp variable)
    int dir = DOWN;     //< direction in which we are moving

    static int counter = 1;

    do {
        // printf("par: %d - curr: %d - next: %d\n",
        //     par != NULL ? par->value : -1,
        //     curr != NULL ? curr->value : -1,
        //     next != NULL ? next->value : -1);

        if (dir == DOWN && curr->left != NULL) {
            // Go down left
            next = curr->left;
            curr->left = par;
            par = curr;
            curr = next;
        } else if (dir == DOWN && curr->right != NULL) {
            // Go down right
            next = curr->right;
            curr->right = par;
            par = curr;
            curr = next;
        } else {
            printf("%d: %d\n", counter++, curr != NULL ? curr->value : -1);

            if (par->value > curr->value && par->right != NULL) {
                // Go down right, coming from left
                // NOTE: order gives us a hint about where we come from
                dir = DOWN;

                next = par->left;   // hold the way back
                par->left = curr;
                curr = par->right;
                par->right = next;  // store the way back in the right child of par now
                next = curr;
            } else {
                dir = UP;

                if (par->value > curr->value) {
                    // Go up, coming from left
                    // NOTE: order gives us a hint about where we come from
                    next = par->left;
                    par->left = curr;
                } else {
                    // Go up, coming from right
                    // NOTE: order gives us a hint about where we come from
                    next = par->right;
                    par->right = curr;
                }
                curr = par;
                par = next;
            }
        }
    } while(next != NULL && par != NULL);
    printf("%d: %d\n", counter++, curr != NULL ? curr->value : -1);
}

void morris_inorder_traversal(node *root) {
    int count = 1;
    node *cur;      //< "current"
    node *pre;      //< "predecessor"

    cur = root;
    while (cur != NULL) {
        if (cur->left == NULL) {
            // No left branch: print current's value and
            // descend in the right branch of current
            printf("%d: %d\n", count++, cur->value);
            cur = cur->right;
        } else {
            // Find the in-order predecessor of current:
            // aka "the rightmost node in the left branch of current"
            pre = cur->left;
            while(pre->right != NULL && pre->right != cur) {
                pre = pre->right;
            }

            if (pre->right == NULL) {
                // If we reached the rightmost node in the left branch of current,
                // make current as right child of its in-order predecessor
                // and descend in the left branch of current
                pre->right = cur;
                cur = cur->left;
            } else {
                // Else we found a loop (above "pre->right == cur"), so we need to
                // revert the changes made in the if part to restore the
                // original tree - i.e. fix the right child of predecessor
                pre->right = NULL;
                printf("%d: %d\n", count++, cur->value);
                cur = cur->right;
            }
        }
    }
}

int main() {
    node *root = create_node(14,
        create_node(5,
            create_node(1,
                create_node(0, NULL, NULL),
                create_node(2, NULL, NULL)),
            create_node(9,
                create_node(8, NULL, NULL),
                create_node(11, NULL, NULL))),
        create_node(18,
            create_node(16,
                create_node(15, NULL, NULL),
                create_node(17, NULL, NULL)),
            create_node(20,
                create_node(19, NULL, NULL),
                create_node(21, NULL, NULL))));

    printf("Recursive Pre-Order Traversal\n");
    recursive_pre_order_traversal(root);

    printf("Recursive In-Order Traversal\n");
    recursive_in_order_traversal(root);

    printf("Recursive Post-Order Traversal\n");
    recursive_post_order_traversal(root);

    printf("Morris In-Order Traversal\n");
    morris_inorder_traversal(root);

    printf("De Marino BST Post-Order Traversal\n");
    de_marino_bst_post_order_traversal(root);
}
