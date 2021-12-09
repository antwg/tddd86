/*
* TDDD86 Pattern Recognition
* This program computes and plots all line segments involving 4 points
* in a file using Qt.
*/
/*
#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>
#include <chrono>
#include "Point.h"
#include "fast.h"

// constants
static const int SCENE_WIDTH = 512;
static const int SCENE_HEIGHT = 512;

void render_points(QGraphicsScene* scene, const vector<Point>& points) {
    for(const auto& point : points) {
        point.draw(scene);
    }
}

void render_line(QGraphicsScene* scene, const Point& p1, const Point& p2) {
    p1.lineTo(scene, p2);
}

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    // open file
    string filename = "input100.txt";
    //string filename = "input3200.txt";
    ifstream input;
    input.open(filename);

    // the vector of points
    vector<Point> points;

    // read points from file
    int N;
    int x;
    int y;

    input >> N;

    for (int i = 0; i < N; ++i) {
        input >> x >> y;
        points.push_back(Point(x, y));
    }
    input.close();

    // setup graphical window
    QGraphicsView *view = new QGraphicsView();
    QGraphicsScene *scene = new QGraphicsScene(0, 0, SCENE_WIDTH, SCENE_HEIGHT);
    view->setScene(scene);
    // draw points to screen all at once
    render_points(scene, points);
    view->scale(1, -1); //screen y-axis is inverted
    view->resize(view->sizeHint());
    view->setWindowTitle("Fast Recognition");
    view->show();

    // sort points by natural order
    // makes finding endpoints of line segments easy
    sort(points.begin(), points.end());
    auto begin = chrono::high_resolution_clock::now();

    // iterate through all combinations of 4 points
    map<double, std::vector<Point>> slopes;
    for (int i = 0 ; i < N ; i++) {
        slopes.clear();
        for (int j = 0 ; j < N ; j++) {
            if (i != j){
                double currSlope = points.at(i).slopeTo(points.at(j));
                if (slopes.count(currSlope) <= 0) {
                    std::vector<Point> *vect = new std::vector<Point>;
                    slopes[currSlope] = *vect;
                }
                else {
                    slopes[currSlope].push_back(points.at(j));
                }
            }
        }
        for (auto slope : slopes){
            if (slope.second.size() >= 3){
                for (Point point : slope.second){
                render_line(scene, points.at(i), point);
                }
            }
        }
    }


    auto end = chrono::high_resolution_clock::now();
    cout << "Computing line segments took "
         << std::chrono::duration_cast<chrono::milliseconds>(end - begin).count()
         << " milliseconds." << endl;

    return a.exec(); // start Qt event loop
}

*/
