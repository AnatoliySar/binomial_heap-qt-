#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scene = new QGraphicsScene();
    //scene->setSceneRect(0, 0, ui->graphicsView->width()-2, ui->graphicsView->height()-2);
    ui->graphicsView->setScene(scene);
    //connect(ui->pushButton_2, &QPushButton::clicked, this, &MainWindow::on_pushButton_2_clicked);

    heap = insert(heap,10);
    heap = insert(heap,20);
    heap = insert(heap,30);
    heap = insert(heap,40);

    paintHeap(heap);

}

int MainWindow::rec(int n, int k)
{
    if (n == 0 || k == 0)
        return 1;
    if(n==k)
        return 1;
    if(k==1)
        return n;
    return rec(n-1, k-1)+rec(n-1, k);
}

Node* MainWindow::newNode(int key)
{
    Node* temp = new Node(key);
    temp->degree = 0;
    temp->child = temp->parent = temp->sibling = NULL;
    return temp;
}

Node* MainWindow::mergeBinomialTrees(Node *b1, Node *b2)
{
    if (b1->data > b2->data)
    {
        auto tmp = b1;
        b1 = b2;
        b2 = tmp;
    }

    b2->parent = b1;
    b2->sibling = b1->child;
    b1->child = b2;
    b1->degree++;

    return b1;
}

list<Node*> MainWindow::unionBionomialHeap(list<Node*> l1, list<Node*> l2)
{
    list<Node*> _new;
    list<Node*>::iterator it = l1.begin();
    list<Node*>::iterator ot = l2.begin();
    while (it!=l1.end() && ot!=l2.end())
    {
        if((*it)->degree <= (*ot)->degree)
        {
            _new.push_back(*it);
            it++;
        }
        else
        {
            _new.push_back(*ot);
            ot++;
        }
    }
    while (it != l1.end())
    {
        _new.push_back(*it);
        it++;
    }
    while (ot!=l2.end())
    {
        _new.push_back(*ot);
        ot++;
    }
    return _new;
}
list<Node*> MainWindow::adjust(list<Node*> _heap)
{
    if (_heap.size() <= 1)
        return _heap;
    list<Node*> new_heap;
    list<Node*>::iterator it1,it2,it3;
    it1 = it2 = it3 = _heap.begin();
    it2++;
    it3=it2;
    it3++;
    while (it1 != _heap.end())
    {
        if (it2 == _heap.end())
            it1++;

        else if ((*it1)->degree < (*it2)->degree)
        {
            it1++;
            it2++;
            if(it3!=_heap.end())
                it3++;
        }

        else if (it3 != _heap.end() &&
                (*it1)->degree == (*it2)->degree &&
                (*it1)->degree == (*it3)->degree)
        {
            it1++;
            it2++;
            it3++;
        }

        else if ((*it1)->degree == (*it2)->degree)
        {
            Node *temp;
            *it1 = mergeBinomialTrees(*it1,*it2);
            it2 = _heap.erase(it2);
            if(it3 != _heap.end())
                it3++;
        }
    }
    return _heap;
}

list<Node*> MainWindow::insertATreeInHeap(list<Node*> _heap,
                              Node *tree)
{
    list<Node*> temp;

    temp.push_back(tree);

    temp = unionBionomialHeap(_heap,temp);

    return adjust(temp);
}

list<Node*> MainWindow::removeMinFromTreeReturnBHeap(Node *tree)
{
    Node* to_delete = tree;
    list<Node*> heap;
    Node *temp = tree->child;
    Node *lo;

    while (temp)
    {
        lo = temp;
        temp = temp->sibling;
        lo->sibling = NULL;
        lo->parent = NULL;
        heap.push_front(lo);
    }
    delete to_delete;
    return heap;
}

list<Node*> MainWindow::insert(list<Node*> _head, int key)
{
    Node *temp = newNode(key);
    return insertATreeInHeap(_head,temp);
}

Node* MainWindow::getMin(list<Node*> _heap)
{
    list<Node*>::iterator it = _heap.begin();
    Node *temp = *it;
    while (it != _heap.end())
    {
        if ((*it)->data < temp->data)
            temp = *it;
        it++;
    }
    return temp;
}

list<Node*> MainWindow::extractMin(list<Node*> _heap)
{
    if (_heap.empty())
        return _heap;
    list<Node*> new_heap,lo;
    Node *temp;

    temp = getMin(_heap);
    list<Node*>::iterator it;
    it = _heap.begin();
    while (it != _heap.end())
    {
        if (*it != temp)
        {
            new_heap.push_back(*it);
        }
        it++;
    }
    lo = removeMinFromTreeReturnBHeap(temp);
    new_heap = unionBionomialHeap(new_heap,lo);
    new_heap = adjust(new_heap);
    return new_heap;
}

void MainWindow::deleteElem(list<Node*>& _heap, Node* elem)
{    
    elem->data = INT_MIN;
    int tmp;
    bool tmpflag;
    while (elem->parent != NULL)
    {
        tmp = elem->data;
        tmpflag = elem->pressed;

        elem->data = elem->parent->data;
        elem->pressed = elem->parent->pressed;

        elem->parent->data = tmp;
        elem->parent->pressed = tmpflag;

        elem = elem->parent;
        elem->pressed = tmpflag;
    }
    _heap = extractMin(_heap);
}


void MainWindow::MainWindow::paintTree(Node* node, int i, int j, vector<int>& floor)
{
    int x = i;
    int y = j;
    while (node != NULL)
    {
        node->setPos(floor[(y - 20) / 100], y);
        if (!scene->items().contains(node))
            scene->addItem(node);
        floor[(y - 20) / 100] += 100;

        if (node->child != NULL)
        {
            paintTree(node->child, x, y + 100, floor);
        }

        node = node->sibling;
    }
}

void MainWindow::paintHeap(list<Node*> heap)
{
    if (heap.empty())
    {
        scene->clear();
        ui->plainTextEdit->clear();
        return;
    }
    int posX = 20;
    int posY = 20;
    int counter = 0;
    vector<int> floor;
    for (auto tree : heap)
    {
        for (auto i = floor.begin(); i != floor.end(); i++)
        {
            *i = posX;
        }
        int s = floor.size();
        for (int i = 0; i <= tree->degree - s; i++)
        {
            floor.push_back(posX);
        }
        paintTree(tree, posX, posY, floor);
        posX += rec(tree->degree, tree->degree / 2) * 100 + 50;
    }
    QString info = "Binomial heap of ";
    info.append(QString::number(heap.size()));
    info.append(" trees with sizes:\n");
    auto powof2 = [] (int a)
    {
        int result = 1;
        for (int i = 0; i < a; i++)
            result *= 2;
        return result;
    };
    for (auto jj = heap.begin(); jj != heap.end(); jj++)
    {
        info.append(QString::number(powof2((*jj)->degree)));

        if (std::next(jj) != heap.end())
        {
            info.append(", ");
        }
    }
    ui->plainTextEdit->document()->setPlainText(info);
}

void MainWindow::check_deleted(Node* node)
{
    while (node != NULL)
    {
        check_deleted(node->child);
        if (node->pressed)
        {
            elements_to_delete.push_back(node);
            return;
        }
        node = node->sibling;
    }
}



MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_2_clicked()
{
    if (ui->lineEdit->text().isEmpty())
        return;
    for(auto ch : ui->lineEdit->text())
    {
        if (ch > '9' || ch < '0')
        {
            QMessageBox* aa = new QMessageBox;
            aa->setWindowTitle("Ошибка!");
            aa->setIcon(QMessageBox::Warning);
            aa->setText("Введите целое число!");
            aa->show();
            ui->lineEdit->clear();
            return;
        }
    }
    heap = insert(heap, ui->lineEdit->text().toInt());
    scene->update();
    paintHeap(heap);
}


void MainWindow::on_pushButton_2_pressed()
{

}


void MainWindow::on_pushButton_3_clicked()
{
    heap = extractMin(heap);
    scene->update();
    paintHeap(heap);
}


void MainWindow::on_pushButton_clicked()
{
    for (auto i = heap.begin(); i != heap.end(); i++)
    {
        check_deleted(*i);
        if (!elements_to_delete.empty())
            break;
    }
    while (!elements_to_delete.empty())
    {
        deleteElem(heap, *elements_to_delete.begin());
        elements_to_delete.clear();
        for (auto i = heap.begin(); i != heap.end(); i++)
        {
            check_deleted(*i);
            if (!elements_to_delete.empty())
                break;
        }
    }

    paintHeap(heap);

}

