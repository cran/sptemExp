#include <Rcpp.h>
#include <dirent.h>
#include <string>
#include <vector>
#include <unordered_map>
#include <regex>
#include <iostream>
#include <fstream>
#include <math.h>

#include "ufcls_lib.h"

using namespace Rcpp;
using namespace std ;


vector<pair<double,double>> getPairVec0(Rcpp::DataFrame df){
  std::vector<double> x=as< std::vector<double> >(df["x"]);
  std::vector<double> y=as< std::vector<double> >(df["y"]);
  // create a vector of length of the smaller vector
  std::vector<std::pair<double, double>> pnts(x.size());
  for (unsigned i = 0; i < pnts.size(); i++)
    pnts[i] = std::make_pair(x[i], y[i]);
  return pnts;
}

// [[Rcpp::export]]
Rcpp::NumericVector exeCluster1D(Rcpp::NumericVector samples, double tdist){
  std::vector<double> samP = as<std::vector<double> >(samples);
  vector<int> clsInf=clustering1D(samP,tdist);
  return wrap(clsInf);
}

// [[Rcpp::export]]
Rcpp::NumericVector exeCluster(Rcpp::DataFrame samples, double tdist){
  vector<pair<double,double>> samP=getPairVec0(samples);
  vector<int> clsInf=clustering(samP,tdist);
//  Rcout<<clsInf.size()<<endl;
//  for(auto ac:clsInf){
//    Rcout<<ac<<endl;
//  }
  return wrap(clsInf);
}

// [[Rcpp::export]]
Rcpp::DataFrame getClusterCt(Rcpp::DataFrame samples, Rcpp::NumericVector clsInf){
  vector<pair<double,double>> samP=getPairVec0(samples);
  vector<int> clsInfC=as< std::vector<int> >(clsInf);
  vector<pair<int,pair<double,double>>> clsRes=getClsCenter1(samP, clsInfC);
  NumericVector clsindex(clsRes.size());
  NumericVector xx(clsRes.size());
  NumericVector yy(clsRes.size());
  for(auto i=0;i<clsRes.size();i++){
    clsindex[i]=clsRes[i].first;
    xx[i]=clsRes[i].second.first;
    yy[i]=clsRes[i].second.second;
  }
  Rcpp::List myList(3);
  Rcpp::CharacterVector namevec;
  myList[0]=clsindex;
  namevec.push_back("clsindex");

  myList[1]=xx;
  namevec.push_back("x");

  myList[2]=yy;
  namevec.push_back("y");
  myList.attr("names") = namevec;
  Rcpp::DataFrame dfout=DataFrame::create(myList,_["stringsAsFactors"] = false);
  return dfout;
}


//  Sys.setenv("PKG_CXXFLAGS"="-std=c++11")

