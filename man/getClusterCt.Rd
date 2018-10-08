\name{getClusterCt}
\alias{getClusterCt}
%- Also NEED an '\alias' for EACH other topic documented here.
\title{
Retrieve the Central Coordinates for Each Cluser after Clustering Done.
}
\description{
This function is the second step for Adaptive Kruskal algorithm for generating aggregate centers for Thiessen polygons with the aim to obtain the central point for each cluster.
}
\usage{
getClusterCt(samples, clsInf)
}
%- maybe also 'usage' for other objects documented here.
\arguments{
  \item{samples}{
Data frame for samples with the columns of coordinates (column name: x and y)
}
  \item{clsInf}{
Cluster results obtained from the fucntion,exeCluster
}
}
\details{
Retrieve the central point for each cluster.
}
\value{
vector format: coordinates (x and y) for each cluster
}
\references{
Thomas, C.; Leiserson, C.; Rivest, R.; Stein, C., Introduction To Algorithms (Third ed.). MIT Press: 2009
}
\author{
Lianfa Li lspatial@gmail.com
}

%% ~Make other sections like Warning with \section{Warning }{....} ~

\seealso{
\code{\link{exeCluster}}, ~~~
}
\examples{
samplePnt=data.frame(x=runif(100,1,100),y=runif(100,1,100))
clusterId=exeCluster(samplePnt,10)
clscenters=getClusterCt(samplePnt,clusterId)
}
% Add one or more standard keywords, see file 'KEYWORDS' in the
% R documentation directory.
\keyword{ ~cluster }% use one of  RShowDoc("KEYWORDS")
\keyword{ ~union-find }% __ONLY ONE__ keyword per line
