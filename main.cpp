#include <iostream>
#include <string.h>
#include <math.h>
#include <algorithm>
#include <vector>
#include "voronoi.h"
#include "list.h"
using namespace std;


void print_vec(vector<point> &p){
  for(int i = 0; i < p.size(); i++) p[i].print();
  cout <<"-----" <<endl;

}

bool compareY(const point &a, const point &b){
  return a.y > b.y;
}
bool compareX(const point &a, const point &b){
  return a.x < b.x;
}


vector<point> process_input(){
  vector<point> input;
  int n, x, y;
  cin >> n;
  for(int i = 0; i < n; i++){
    cin >> x >> y;
    input.push_back(point(x,y));
  }
  sort(input.begin(), input.end(), compareY);
  return input;
}

point *get_breakpoint(point *pi, point *pj, double l){
  point *ans;
  ans = new point(0,0);

  double a,b,o,d;

  a = pi->x, b = pi->y;
  o = pj->x, d = pj->y;
  if(l == pj->y) return pi;

  double alpha, beta;
  double x_ans, y_ans;

  alpha = (d + b) - (2*l);
  beta = (a * d) + (o * b) - (l * (a + o));
  x_ans = beta/alpha;

  y_ans = (x_ans * x_ans) - 2*(a * x_ans) + (a * a) + (b * b) - (l * l);
  y_ans /= (b - l);

  ans->x = x_ans;
  ans->y = y_ans;
  return ans;
}

point *search_arc(beach_line *T, double l, point *new_point){

  point *pi, *pj, *break_point, *b2;

  if(T->points.size() == 0) return NULL;

  for(int i = 0; i <= T->points.size() - 1; i++){
    pi = &(T->points[i]);
    pj = &(T->points[i+1]);
    break_point = get_breakpoint(pi, pj, l);

    if((new_point->x <= break_point->x) || (break_point == pi)) return pi;
  }
}

void insert_bl(beach_line *T, point *current_event, point *arc_above){
  point new_point(current_event->x, current_event->y);

  if(arc_above == NULL){
    T->points.push_back(new_point);
  }
  else{
    int index = 0;
    for(int i = 0; i < T->points.size(); i++){

      if(T->points[i].x == arc_above->x && T->points[i].y == arc_above->y){
        index = i;
      }
    }
    point aux(T->points[index].x, T->points[index].y);
    T->points.insert(T->points.begin() + index + 1, new_point);
    T->points.insert(T->points.begin() + index + 2, aux);
  }
}

bool p_equal(point *p1, point *p2){
  return ((p1->x == p2->x) && (p1->y == p2->y));
}

bool diff(point *p1, point *p2, point *p3){

  return( !((p_equal(p1, p2)) ||
          (p_equal(p1, p3)) ||
          (p_equal(p2, p3))) );
}

point *circle_center(point *p1, point *p2, point *p3){
  double h,k;

  point *center;

  double A,B,C,D;

  double x1, x2, x3, y1, y2, y3;
  x1 = p1->x, x2 = p2->x, x3 = p3->x;
  y1 = p1->y, y2 = p2->y, y3 = p3->y;

  if(x1 == x2 && x1 == x3 && x2 == x3) return NULL;

  A = (x1*(y2 - y3)) -
      (y1*(x2 - x3)) +
      (x2 * y3) - (x3*y2);

  B = ((x1 * x1 + y1 * y1)*(y3 - y2)) +
      ((x2 * x2 + y2*y2)*(y1 - y3)) +
      ((x3 * x3 + y3 * y3)*(y2 - y1));

  C = (x1 * x1 + y1 * y1)*(x2 - x3) +
      (x2 * x2 + y2 * y2)*(x3 - x1) +
      ((x3 * x3 + y3 * y3)*(x1 - x2));

  h = -B/(2*A);
  k = -C/(2*A);

  double radius;
  radius = sqrt( (x1 - h) * (x1 - h) + (y1 - k) * (y1 - k));

  center = new point(h,k - radius);
  center->radius = radius;
  return center;
}


void check_for_circle_event(beach_line *T,
                            double l,
                            event_queue *events){

  if(T->points.size() <= 2) return;

  point *pi, *pj, *pk;

  point *new_circle_event;

  for(int i=0; i < T->points.size() - 2; i++){


    pi = &T->points[i];
    pj = &T->points[i+1];
    pk = &T->points[i+2];

    bool isdiff = diff(pi, pj, pk);
    bool unique, empty;

    if(isdiff){

      new_circle_event = circle_center(pi, pj, pk);
      if(new_circle_event == NULL) continue;
      if(new_circle_event->y >= l) continue;

      empty = (pi->generate != NULL) &&
              (pj->generate != NULL) &&
              (pk->generate != NULL);

      if(empty){
        unique = p_equal(pi->generate, new_circle_event) ||
                 p_equal(pj->generate, new_circle_event) ||
                 p_equal(pk->generate, new_circle_event);
        if(unique) continue;
      }


      new_circle_event->circle_event = true;

      pj->gx = new_circle_event->x;
      pj->gy = new_circle_event->y;
      pi->generate = new_circle_event,
      pj->generate = new_circle_event,
      pk->generate = new_circle_event;

      events->q.push_back(*new_circle_event);
    }
  }
}

point *get_bisector(point *pi, point *pj){
  double x1 = pi->x, x2 = pj->x, y1 = pi->y, y2 = pj->y;

  double m = -(y2 - y1)/(x2 - x1);

  double xm, ym;

  xm = (x1 + x2)/2, ym = (y1 + y2)/2;

  double alpha, beta;

  double x_e, y_e;



  point *aux = new point(alpha, beta);
  return aux;
}

void add_bisector(edge **dcel, point *pi, point *pj){
  point *bisector = get_bisector(pi, pj);
  double alpha = bisector->x, beta = bisector->y;

  edge *new_bisector = new edge(pi);
}



void site_event(beach_line *T,
                point *current_event,
                double l,
                event_queue *events){

  point *above_arc;
  above_arc = search_arc(T, l, current_event);
  insert_bl(T, current_event, above_arc);
  check_for_circle_event(T,l, events);

}

void circle_event(beach_line *T,
                  vector<point> *vor,
                  point *circle_event,
                  event_queue *events,
                  double l){

  circle_event->y += circle_event->radius;
  vor->push_back(*circle_event);

  circle_event->y -= circle_event->radius;
  point *pi, *pj;
  bool generated, same;
  generated = false, same = false;
  for(int i = 0; i < T->points.size(); i++){

    generated = (T->points[i].gx == circle_event->x) && (T->points[i].gy == circle_event->y);
    if(generated){
      (T->points.begin() + i)->print();
      T->points.erase(T->points.begin() + i);
      break;
    }
  }

  for(int i = 0; i < T->points.size() - 1; i++){
    pi = &T->points[i];
    pj = &T->points[i + 1];
    if(p_equal(pi, pj)){
      T->points.erase(T->points.begin() + i);
      break;
    }
  }

}

vector<point> construct_voronoi(vector<point> *input){

  event_queue events(*input);
  vector<point> voronoi_vertices;

  beach_line T;
  double l;
  point *current_event;

  while(!(events.q.empty())){

    current_event = &events.q.front();

    l = current_event->y;

    print_vec(T.points);
    if(current_event->circle_event == true){
      circle_event(&T, &voronoi_vertices, current_event, &events, l);
    }else{
      site_event(&T, current_event, l, &events);
    }
    cout << "beach line after: " << endl;
    print_vec(T.points);

    events.q.erase(events.q.begin());
    sort(events.q.begin(), events.q.end(), compareY);
  }

  cout << " vertices : " << endl;
  print_vec(voronoi_vertices);
  return(voronoi_vertices);
}





void output(edge **dcel){
  point p1(0,0), p2(0,100), p3(100,0), p4(100,100);
  edge e1(&p1), e2(&p2), e3(&p3), e4(&p4);
  append(dcel, &e1);
  append(dcel, &e2);
  append(dcel, &e3);
  append(dcel, &e4);
  print_list(dcel);
}


int main(){
  vector<point> input = process_input();
  //vector<point> voronoi = construct_voronoi(&input);
  edge *dcel = NULL;
  output(&dcel);
  return 0;
}
