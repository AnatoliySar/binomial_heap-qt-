#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <list>
#include <vector>
#include <utility>
#include <QPainter>
#include "node.h"
#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include <QMessageBox>

using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_2_pressed();

    void on_pushButton_3_clicked();

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    QGraphicsScene* scene;
    list<Node*> heap;
    list<Node*> elements_to_delete;

    void paintTree(Node *node, int i, int j, vector<int>& floor);
    void paintHeap(list<Node*> heap);
    void check_deleted(Node *node);

    int rec(int n, int k);
    Node* newNode(int key);
    list<Node*> insert(list<Node*> _head, int key);
    Node* mergeBinomialTrees(Node *b1, Node *b2);
    list<Node*> unionBionomialHeap(list<Node*> l1, list<Node*> l2);
    list<Node*> adjust(list<Node*> _heap);
    Node* getMin(list<Node*> _heap);
    void deleteElem(list<Node*>&, Node*);
    list<Node*> removeMinFromTreeReturnBHeap(Node *tree);
    list<Node*> insertATreeInHeap(list<Node*> _heap, Node *tree);
    list<Node*> extractMin(list<Node*> _heap);
};




#endif // MAINWINDOW_H
