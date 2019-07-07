
#' @title exClusterByKruskal
#'
#' @description This function is implementation of Kruskal clustering.
#'
#' @param spcoords: Data frame with the columns of x and y coordinates
#'
#' @param mininterClusterDist: Minimum intercluster distance used in Kruskal clustering
#'
#' @param dist_scalor: Scaling factor for the coordinates to avoid overflow by too big integers.
#'
#' @return A list: (clusterid,clsCenter,sumCls,withinss,tot.withinss)
#'
#' @export exClusterByKruskal
#'

exClusterByKruskal=function(spcoords,mininterClusterDist=8000,dist_scalor=1000){
  # spcoords=coords ; mininterClusterDist=8000; dist_scalor=1000
  spcoords=spcoords/dist_scalor
  adist=mininterClusterDist/dist_scalor
  res=exeCluster(spcoords,adist)
  spcoords$clsid=res
  summ=data.frame(table(res))
  ttt=getClusterCt(spcoords,res)
  clsCenter=data.frame(clsindex=ttt$clsindex, x=ttt$x*dist_scalor,y=ttt$y*dist_scalor)
  cls=unique(res)
  allvarwithincls=0
  for(i in c(1:length(cls))){  # i=1
    k=cls[i]
    spcoords_cls=spcoords[which(spcoords$clsid==k),]
    acenter=clsCenter[which(clsCenter$clsindex==k),]
    for(j in c(1:nrow(spcoords_cls))){ # i=1
      apoint=spcoords_cls[j,]*dist_scalor
      adist=(apoint$x-acenter$x)^2+(apoint$y-acenter$y)^2
      if(j==1){
        sumWithin=adist
      }else{
        sumWithin=sumWithin+adist
      }
    }
    adf=data.frame(cls=k,varwithincls=sumWithin)
    if(i==1){
      alldf=adf
    }else{
      alldf=cbind(alldf,adf)
    }
    allvarwithincls=allvarwithincls+sumWithin
  }
  return(list(clusterid=res,clsCenter=clsCenter,sumCls=summ,
              withinss=alldf,tot.withinss=allvarwithincls))
}
