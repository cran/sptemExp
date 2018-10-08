#include <Rcpp.h>

#include <stdio.h>
#include <queue>
#include <algorithm>
#include <stdlib.h>
#include <unordered_map>
#include <cstdlib>
#include <climits>

using namespace Rcpp;
using namespace std;

typedef pair<double, pair<int,int>> distPt;
auto comp=[](distPt & a,distPt & b){return a.first>b.first ; };
struct lessByDist{
  bool operator ()(const distPt & a, const distPt & b){
    return a.first>b.first;
  }
};

typedef priority_queue<distPt, vector<distPt>, lessByDist> distQ;
int find(int k,vector<int> & p);
int find2(int k,vector<int> & p);
bool unionP(int a,int b,vector<int> & p);
distQ  getDistsInf(vector<pair<double,double>> & pnts);
vector<int> clustering(vector<pair<double,double>> & pnts,double tarDist);
vector<pair<int,pair<double,double>>> getClsCenter1(vector<pair<double,double>> & pnts, vector<int> & cls);
void getRandPnts(vector<pair<double,double>> & pnts,int lim,int x1,int x2,int y1,int y2,int sz);


