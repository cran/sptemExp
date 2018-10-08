#include <Rcpp.h>

#include "ufcls_lib.h"

int find(int k,vector<int> & p){
  int ok=k;
  while(p[k]!=k)
    k=p[k];
  int pk=k;
  k=ok;
  while(p[k]!=pk){
    int tmp=p[k];
    p[k]=pk;
    k=p[k] ;
  }
  return pk;
}

int find2(int k,vector<int> & p){
  if(p[k]==k)
    return k;
  int pk=find2(p[k],p);
  p[k]=pk;
  return pk;
}

bool unionP(int a,int b,vector<int>& p){
  int pa=find(a,p);
  int pb=find(b,p);
  if(pa==pb)
    return false;
  for(auto i=0;i<p.size();i++){
    if(p[i]==pb)
      p[i]=pa;
  }
  return true;
}

distQ getDistsInf(vector<pair<double,double>> & pnts){
  distQ res;
  for(auto i=0;i<pnts.size()-1;i++) {
    for (auto j = i + 1; j < pnts.size(); j++) {
      double dist = pow(pnts[i].first - pnts[j].first, 2) + pow(pnts[i].second - pnts[j].second, 2);
      dist=sqrt(dist);
      distPt ele = {dist, make_pair(i, j)};
      res.push(ele);
    }
  }
  return res;
}

vector<int> clustering(vector<pair<double,double>> & pnts, double tarDist){
  distQ dQ=getDistsInf(pnts);
  vector<int> p;
  for(auto i=0;i<pnts.size();i++){
    p.push_back(i);
  }
  int cls=p.size();
  //cout<<dQ.top().first<<endl;
  while(!dQ.empty() && dQ.top().first<=tarDist){
    distPt ele=dQ.top();
    dQ.pop();
    pair<int,int> apnt=ele.second;
    if(unionP(apnt.first,apnt.second,p))
      cls--;
  }
  unordered_map<int,int> cindexMap;
  int nclsInex=1;
  for(auto i=0;i<p.size();i++){
    if(cindexMap.find(p[i]) == cindexMap.end()){
      cindexMap[p[i]]=nclsInex;
      p[i]=nclsInex;
      nclsInex++;
    }else{
      p[i]=cindexMap[p[i]];
    }
  }
  return p;
}

vector<pair<int,pair<double,double>>> getClsCenter1(vector<pair<double,double>> & pnts, vector<int> & cls){
  map<int,vector<int>> clsMap;
  for(auto i=0;i<cls.size();i++){
    if(clsMap.find(cls[i])!=clsMap.end()){
      clsMap[cls[i]].push_back(i);
    }else{
      vector<int> items;
      items.push_back(i);
      clsMap[cls[i]]=items;
    }
  }
  Rcout<<"Numb of clusters: "<<clsMap.size()<<endl;
  vector<pair<int,pair<double,double>>> clsCenter;
  for(auto item:clsMap){
    int key=item.first;
    vector<int> index=item.second;
    double avx,avy;
    avx=avy=0;
    for(auto j:index){
      avx+=pnts[j].first;
      avy+=pnts[j].second;
    }
    avx/=(double)index.size();
    avy/=(double)index.size();
    clsCenter.push_back(make_pair(key,make_pair(avx,avy)));
  }
  return clsCenter ;
}

void getRandPnts(vector<pair<double,double>> & pnts,int lim,int x1,int x2,int y1,int y2,int sz){
  int cnt=0;
  while(cnt<sz){
    vector<int> xx=as< std::vector<int> > (runif(1,0,INT_MAX));
    vector<int> yy=as< std::vector<int> > (runif(1,0,INT_MAX));
    int ax=xx[0] % lim;
    int ay=xx[0] % lim;
    if(ax>x1 && ax<x2 && ay>y1 && ay<y2){
      pair<double,double> apair=make_pair((double)ax,(double)ay);
      pnts.push_back(apair);
      cnt++;
    }
  }
}

