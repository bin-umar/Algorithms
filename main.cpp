//
// Created by jahongir on 12/17/18.
//

#include "module3/task1/CListGraph.h"
#include "module3/task1/CMatrixGraph.h"
#include "module3/task1/CSetGraph.h"
#include "module3/task1/CArcGraph.h"
#include "module3/task1/IGraph.h"

#include "time.h"
#include "iostream"
#include "random"

using std::cout;
using std::endl;
using std::string;

void fillGraph(IGraph *graph, const size_t count, double k, string type) {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(1, count);
    std::uniform_real_distribution<double> operation(1, 2);

    int edgesCount = (count * (count - 1) * k) / 2;
    clock_t tStart = clock();

    for (int i=0; i < edgesCount; i++) {
        graph->AddEdge((int)dist(mt), (int)dist(mt));
    }

    cout << "AddEdge method in " << type << " Graph      | " << k * 100 << "% |  "
         << (double)(clock() - tStart) / CLOCKS_PER_SEC << endl;

    tStart = clock();

    for (int i=0; i < count; i++) {
        switch ((int)operation(mt)) {
            case 1:
                graph->GetNextVertices((int)dist(mt));
                break;
            case 2:
                graph->GetPrevVertices((int)dist(mt));
                break;
            default:
                break;
        }
    }

    cout << "GetVertices method in " << type << " Graph  | " << k * 100 << "% |  "
         << (double)(clock() - tStart) / CLOCKS_PER_SEC << endl;
}

void printEmptyStr() {
    cout << "---------------------------------------------------"  << endl;
}

void test() {
    size_t testEdgesCount = 300;

    cout << "Method | Graph Type               | or% |  time (s)"  << endl;
    printEmptyStr();

    /******************************* Test List Graph **************************************/
    CListGraph listGraph(testEdgesCount);
    fillGraph(&listGraph, testEdgesCount, 0.25, "List");
    fillGraph(&listGraph, testEdgesCount, 0.5, "List");
    fillGraph(&listGraph, testEdgesCount, 0.75, "List");
    printEmptyStr();

    /******************************* Test Arc Graph ***************************************/
    CArcGraph arcGraph(testEdgesCount);
    fillGraph(&arcGraph, testEdgesCount, 0.25, "Arc");
    fillGraph(&arcGraph, testEdgesCount, 0.5, "Arc");
    fillGraph(&arcGraph, testEdgesCount, 0.75, "Arc");
    printEmptyStr();

    /******************************* Test Matrix Graph ************************************/
    CMatrixGraph matrixGraph(testEdgesCount);
    fillGraph(&matrixGraph, testEdgesCount, 0.25, "Matrix");
    fillGraph(&matrixGraph, testEdgesCount, 0.5, "Matrix");
    fillGraph(&matrixGraph, testEdgesCount, 0.75, "Matrix");
    printEmptyStr();

    /******************************* Test Set Graph **************************************/
    CSetGraph setGraph(testEdgesCount);
    fillGraph(&setGraph, testEdgesCount, 0.25, "Set");
    fillGraph(&setGraph, testEdgesCount, 0.5, "Set");
    fillGraph(&setGraph, testEdgesCount, 0.75, "Set");
    printEmptyStr();

    /************************* Test Converting to List Graph *****************************/
    CListGraph listGraph1(&arcGraph);
    cout << "|***** List Graph from arcGraph passed!!! *********|" << endl;

    CListGraph listGraph2(&matrixGraph);
    cout << "|***** List Graph from matrixGraph passed!!! ******|" << endl;

    CListGraph listGraph3(&setGraph);
    cout << "|***** List Graph from setGraph passed!!! *********|" << endl << endl;

    /************************* Test Converting to Arc Graph ******************************/
    CArcGraph arcGraph1(&listGraph);
    cout << "|***** Arc Graph from listGraph passed!!! *********|" << endl;

    CArcGraph arcGraph2(&matrixGraph);
    cout << "|***** Arc Graph from matrixGraph passed!!! *******|" << endl;

    CArcGraph arcGraph3(&setGraph);
    cout << "|***** Arc Graph from setGraph passed!!! **********|" << endl << endl;

    /************************ Test Converting to Matrix Graph ****************************/
    CMatrixGraph matrixGraph1(&listGraph);
    cout << "|***** Matrix Graph from listGraph passed!!! ******|" << endl;

    CMatrixGraph matrixGraph2(&arcGraph);
    cout << "|***** Matrix Graph from arcGraph passed!!! *******|" << endl;

    CMatrixGraph matrixGraph3(&setGraph);
    cout << "|***** Matrix Graph from setGraph passed!!! *******|" << endl << endl;

    /************************* Test Converting to Set Graph ******************************/
    CSetGraph setGraph1(&listGraph);
    cout << "|***** Set Graph from listGraph passed!!! *********|" << endl;

    CSetGraph setGraph2(&arcGraph);
    cout << "|***** Set Graph from arcGraph passed!!! **********|" << endl;

    CSetGraph setGraph3(&matrixGraph);
    cout << "|***** Set Graph from matrixGraph passed!!! *******|" << endl << endl;

    /************************** Tests successfully finished ******************************/
    cout << "|***** Tests successfully finished ****************|";

}

int main() {
    test();
    return 0;
}