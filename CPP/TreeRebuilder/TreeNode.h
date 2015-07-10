#ifndef TREENODE_H
#define TREENODE_H

#include <QtGlobal>

#define TREE_NODE_VAL_TYPE  qint8

typedef struct TreeNode {
    TREE_NODE_VAL_TYPE  val;
    TreeNode            *leftChild;
    TreeNode            *rightChild;
    TreeNode() { leftChild = rightChild = NULL; }
};

#endif // TREENODE_H
