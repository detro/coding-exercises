#include "TreeRebuilder.h"
#include <QDebug>

TreeRebuilder::TreeRebuilder() { }


TreeNode *TreeRebuilder::rebuild(QVector<TREE_NODE_VAL_TYPE> *preOrderVisit, QVector<TREE_NODE_VAL_TYPE> *inOrderVisit) {
    reset();

    m_preOrderVisit = preOrderVisit;
    m_inOrderVisit = inOrderVisit;

    mapNodePosInInOrderVisit();

    return doRebuild(0, m_inOrderVisit->size() - 1);
}

void TreeRebuilder::mapNodePosInInOrderVisit() {
    if ( !m_inOrderVisit ) {
        qCritical() << "InOrder Visit not provided";
    }

    // Memorize the Position in the InOrder Visit of every element for quick-lookup
    for (qint32 i = 0; i < m_inOrderVisit->size(); ++i) {
        m_nodePosInInOrderVisit.insert(m_inOrderVisit->at(i), i);
    }
}

TreeNode *TreeRebuilder::doRebuild(const qint32 &inOrderLeftLimit, const qint32 &inOrderRightLimit) {
    TreeNode *newNode = new TreeNode;

    qDebug() << "[Node:\t" << m_preOrderVisit->at( m_currRootInPreOrderVisit ) << "]";
    newNode->val = m_preOrderVisit->at( m_currRootInPreOrderVisit++ ); // Post-increment used to select the next New Node value, taken from the PreOrder Visit

    if ( inOrderLeftLimit < inOrderRightLimit ) {
        // If the current Node Value is not the first in the InOrderVisit current range, means there is a Left Child
        if ( m_nodePosInInOrderVisit.value(newNode->val) > inOrderLeftLimit ) {
            qDebug() << "   Found Left Child";
            newNode->leftChild = doRebuild(inOrderLeftLimit, m_nodePosInInOrderVisit.value(newNode->val) -1);
        }

        // If the current Node Value is not the last in the InOrderVisit current range, means there is a Right Child
        if ( m_nodePosInInOrderVisit.value(newNode->val) < inOrderRightLimit ) {
            qDebug() << "   Found Right Child";
            newNode->rightChild = doRebuild(m_nodePosInInOrderVisit.value(newNode->val) + 1, inOrderRightLimit);
        }
    }

    qDebug() << "[/Node:\t" << newNode->val << "]";

    return newNode;
}

void TreeRebuilder::reset() {
    m_currRootInPreOrderVisit = 0;
    m_preOrderVisit = NULL;
    m_inOrderVisit = NULL;
    m_nodePosInInOrderVisit.clear();
}

QVector<TREE_NODE_VAL_TYPE> TreeRebuilder::generateInOrderVisit(TreeNode * const root) {
    QVector<TREE_NODE_VAL_TYPE> result;

    TreeRebuilder::doGenerateInOrderVisit(root, &result);

    return result;
}

void TreeRebuilder::doGenerateInOrderVisit(TreeNode * const root, QVector<TREE_NODE_VAL_TYPE> *result) {
    if ( NULL != root ) {
        doGenerateInOrderVisit(root->leftChild, result);
        result->append(root->val);
        doGenerateInOrderVisit(root->rightChild, result);
    }
}

QVector<TREE_NODE_VAL_TYPE> TreeRebuilder::generatePreOrderVisit(TreeNode * const root) {
    QVector<TREE_NODE_VAL_TYPE> result;

    TreeRebuilder::doGeneratePreOrderVisit(root, &result);

    return result;
}

void TreeRebuilder::doGeneratePreOrderVisit(TreeNode * const root, QVector<TREE_NODE_VAL_TYPE> *result) {
    if ( NULL != root ) {
        result->append(root->val);
        doGeneratePreOrderVisit(root->leftChild, result);
        doGeneratePreOrderVisit(root->rightChild, result);
    }
}
