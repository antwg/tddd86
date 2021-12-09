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

template <typename K, typename V>
bool comparePairs(const std::pair<K,V>& lhs, const std::pair<K,V>& rhs)
{
  return lhs.second < rhs.second;
}

void drawLines(vector<pair<Point, double>> pairs, Point p,  QGraphicsScene* scene) {
    int start = 0;
    double currSlope = pairs[0].second;

    for (unsigned end = 0; end < pairs.size(); end++) {
        if (pairs[end].second != currSlope || end == pairs.size() - 1) {
            if (end - start >= 3){
                for (unsigned i = start; i < end; i++){
                    render_line(scene, p, pairs[i].first);
                }
            }
            start = end;
            currSlope = pairs[start].second;
        }
    }
}


int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    // open file
    string filename = "grid4x4.txt";
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
    view->setWindowTitle("Brute Force Pattern Recognition");
    view->show();

    // sort points by natural order
    // makes finding endpoints of line segments easy
    sort(points.begin(), points.end());
    auto begin = chrono::high_resolution_clock::now();

    // iterate through all combinations of 4 points

    vector<pair<Point, double>> slopes;
    for (int i = 0 ; i < N ; i++) {
        slopes.clear();
        for (int j = 0 ; j < N ; j++) {
            if (i != j){
                pair<Point, double> pair = make_pair(points.at(j), points.at(i).slopeTo(points.at(j)));
                slopes.push_back(pair);
            }
        }
        sort(slopes.begin(), slopes.end(), comparePairs<Point, double>);

        drawLines(slopes, points[i], scene);
    }

    auto end = chrono::high_resolution_clock::now();
    cout << "Computing line segments took "
         << std::chrono::duration_cast<chrono::milliseconds>(end - begin).count()
         << " milliseconds." << endl;

    return a.exec(); // start Qt event loop
}
*/
