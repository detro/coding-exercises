#include <QtCore/QCoreApplication>
#include <QVector>
#include <QDebug>

#include "TreeNode.h"
#include "TreeRebuilder.h"

int main(int argc, char *argv[])
{
    Q_UNUSED(argc)
    Q_UNUSED(argv)

    QVector<TREE_NODE_VAL_TYPE> preOrderVisit;
    QVector<TREE_NODE_VAL_TYPE> inOrderVisit;
    TreeNode *treeRebuilt;

    // Create input
    preOrderVisit << 8 << 2 << 1 << 9 << 3 << 4 << 10 << 7 << 11;
    inOrderVisit << 1 << 2 << 9 << 8 << 4 << 10 << 3 << 11 << 7;

    // Rebuild
    TreeRebuilder rebuilder;
    qDebug() << "=== START REBUILDING ===";
    treeRebuilt = rebuilder.rebuild(&preOrderVisit, &inOrderVisit);
    qDebug() << "=== DONE REBUILDING ===";

    // Test
    if ( inOrderVisit == rebuilder.generateInOrderVisit(treeRebuilt) ) {
        if ( preOrderVisit == rebuilder.generatePreOrderVisit(treeRebuilt) ) {
            qDebug() << "Rebuilding Result: SUCCESS";
            return EXIT_SUCCESS;
        }
    }

    qDebug() << "Rebuilding Result: FAILURE";
    return EXIT_FAILURE;
}
