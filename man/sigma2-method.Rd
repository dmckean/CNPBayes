% Generated by roxygen2 (4.1.0): do not edit by hand
% Please edit documentation in R/AllGenerics.R, R/methods-BatchModel.R, R/methods-MarginalModel.R, R/methods-McmcChains.R
\docType{methods}
\name{sigma2}
\alias{sigma2}
\alias{sigma2,BatchModel-method}
\alias{sigma2,MarginalModel-method}
\alias{sigma2,McmcChains-method}
\alias{sigma2,missing-method}
\title{Retrieve the variances of each component and batch distribution}
\usage{
sigma2(object)

\S4method{sigma2}{BatchModel}(object)

\S4method{sigma2}{MarginalModel}(object)

\S4method{sigma2}{McmcChains}(object)
}
\arguments{
\item{object}{see \code{showMethods(sigma2)}}
}
\description{
For a MarginalModel, this function returns a vector of variances. For a BatchModel, returns a matrix of size number of batches by number of components.
}
