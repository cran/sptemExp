\name{exeCluster}
\alias{exeCluster}
%- Also NEED an '\alias' for EACH other topic documented here.
\title{
   Efficient Clustering Using Union-Find to Obtain the Clusters for Each Sample
}
\description{
This function is the first step for Adaptive Kruskal algorithm for generating aggregate centers for Thiessen polygons with the aim to obtain the cluster id for each sample point.
}
\usage{
exeCluster(samples, tdist)
}
%- maybe also 'usage' for other objects documented here.
\arguments{
  \item{samples}{
Data frame for samples with the columns of coordinates (column name: x and y)
}
  \item{tdist}{
The target distance for generation of the clusters.  If the minimun distance between any two samples respectively from two different clusters is bigger than tdist, clustering stops and return the results.
}
}
\details{
The Kruskal algorithm is used to obtain the sparse central points from dense points for efficient generation of Thiessen polygons for spatial effect modeling. This function aims to obtain the cluster id for each sample point. We used the union-find method for linear time complexity.
}
\value{
vector format: cluster id for each sample (same sequence as the input)
}
\references{
Thomas, C.; Leiserson, C.; Rivest, R.; Stein, C., Introduction To Algorithms (Third ed.). MIT Press: 2009
}
\author{
Lianfa Li lspatial@gmail.com
}

%% ~Make other sections like Warning with \section{Warning }{....} ~

\seealso{
\code{\link{getClusterCt}}, ~~~
}
\examples{
samplePnt=data.frame(x=runif(100,1,100),y=runif(100,1,100))
clusterId=exeCluster(samplePnt,10)
}
% Add one or more standard keywords, see file 'KEYWORDS' in the
% R documentation directory.
\keyword{ ~cluster }% use one of  RShowDoc("KEYWORDS")
\keyword{ ~union-find }% __ONLY ONE__ keyword per line
