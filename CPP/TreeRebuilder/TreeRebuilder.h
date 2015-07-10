#ifndef TREEREBUILDER_H
#define TREEREBUILDER_H

#include <QtGlobal>
#include <QVector>
#include <QHash>

#include "TreeNode.h"

class TreeRebuilder
{
// Interface
public:
    TreeRebuilder();
    TreeNode *rebuild(QVector<TREE_NODE_VAL_TYPE> *preOrderVisit, QVector<TREE_NODE_VAL_TYPE> *inOrderVisit);

private:
    void mapNodePosInInOrderVisit();
    TreeNode *doRebuild(const qint32 &inOrderLeftLimit, const qint32 &inOrderRightLimit);
    void reset();

// Static utility methods
public:
    static QVector<TREE_NODE_VAL_TYPE> generateInOrderVisit(TreeNode * const root);
    static QVector<TREE_NODE_VAL_TYPE> generatePreOrderVisit(TreeNode * const root);
private:
    static void doGenerateInOrderVisit(TreeNode * const root, QVector<TREE_NODE_VAL_TYPE> *result);
    static void doGeneratePreOrderVisit(TreeNode * const root, QVector<TREE_NODE_VAL_TYPE> *result);

// Member Variables
private:
    qint32                              m_currRootInPreOrderVisit;
    QHash<TREE_NODE_VAL_TYPE, qint32>   m_nodePosInInOrderVisit;
    QVector<TREE_NODE_VAL_TYPE>         *m_preOrderVisit;
    QVector<TREE_NODE_VAL_TYPE>         *m_inOrderVisit;
};

#endif // TREEREBUILDER_H
