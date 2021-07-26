
#include <iostream>
#include <queue>

using namespace std;


typedef struct point{
  double x,y;
  bool circle_event = false;
  bool false_event = false;
  point *ri, *rj, *rk;
  double gx = 0, gy = 0;
  point *generate = NULL;
  double radius;
  struct edge *em;

  point(double val_x, double val_y){
    x = val_x;
    y = val_y;
  }

  void print(){
    cout << x << " " << y << endl;
  }
}point;


typedef struct edge{

    point *vert;

    edge *prev;
    edge *next;
    
    edge *face;
    edge(point *p){
      vert = p;
    }
}edge;

typedef struct event_queue{
  vector<point> q;

  event_queue(vector<point> input){
    for(int i = 0; i < input.size(); i++) q.push_back(input[i]);
  }
}event_queue;

typedef struct beach_line{
  vector<point> points;
}beach_line;
