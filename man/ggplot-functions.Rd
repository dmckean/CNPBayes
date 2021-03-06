% Generated by roxygen2: do not edit by hand
% Please edit documentation in R/AllGenerics.R, R/plot-functions.R
\docType{methods}
\name{ggChains}
\alias{ggChains}
\alias{ggMixture}
\alias{ggSingleBatch}
\alias{ggMultiBatch}
\alias{ggSingleBatchChains}
\alias{ggMixture,MultiBatchCopyNumber-method}
\alias{ggMixture,MultiBatchCopyNumberPooled-method}
\alias{ggMixture,SingleBatchModel-method}
\alias{ggMixture,MultiBatchModel-method}
\alias{ggMixture,MultiBatchPooled-method}
\alias{ggMixture,SingleBatchCopyNumber-method}
\alias{ggChains,MultiBatchModel-method}
\alias{ggChains,MultiBatchPooled-method}
\alias{ggChains,SingleBatchPooled-method}
\alias{ggChains,SingleBatchModel-method}
\title{Trace plots of MCMC chains and mixture model densities}
\usage{
ggChains(model)

ggMixture(model, bins)

ggSingleBatch(model, bins)

ggMultiBatch(model, bins)

ggSingleBatchChains(model)

\S4method{ggMixture}{MultiBatchCopyNumber}(model, bins)

\S4method{ggMixture}{MultiBatchCopyNumberPooled}(model, bins)

\S4method{ggMixture}{SingleBatchModel}(model, bins)

\S4method{ggMixture}{MultiBatchModel}(model, bins)

\S4method{ggMixture}{MultiBatchPooled}(model, bins)

\S4method{ggMixture}{SingleBatchCopyNumber}(model, bins)

\S4method{ggChains}{MultiBatchModel}(model)

\S4method{ggChains}{MultiBatchPooled}(model)

\S4method{ggChains}{SingleBatchPooled}(model)

\S4method{ggChains}{SingleBatchModel}(model)
}
\arguments{
\item{model}{A SB, MB, SBP, or MBP model}

\item{bins}{a length-one numeric vector indicating the number of bins -- passed to \code{geom_hist}}
}
\value{
A \code{gg} object

a \code{ggplot} object

a list of \code{ggplot} objects. Chains are grouped by the length of
  the parameter vector. For example, in the single-batch model, the means
  (theta) and variances (sigma2) are component-specific (length k, where k is
  number of components) and are plotted together in a single \code{ggplot}
  object.
}
\description{
The \code{ggChains} method provides a convenient wrapper for plotting the chains of all parameters in the various mixture model implementations.  In addition to the estimated number of independent MCMC draws (effective sample size) and Gelman-Rubin convergence diagnostics implemented in \code{gibbs}, visualization of the chains is helpful for assessing convergence.

ggplot-style functions for diagnosing convergence
}
\details{
The \code{ggMixture} method overlays the posterior approximation of the Gaussian mixture on the empirical data.
}
\examples{
  sb <- SingleBatchModelExample
  iter(sb, force=TRUE) <- 1000
  burnin(sb) <- 100
  sb <- posteriorSimulation(sb)
  fig.chains <- ggChains(sb)
  ## component-specific chains
  fig.chains[["comp"]]
  ## single-parameter chains and log-likelihood
  fig.chains[["single"]]

  ## plot the mixture
  fig.mix <- ggMixture(sb)
sb <- SingleBatchModelExample
plist.sb <- ggChains(sb)
\dontrun{
## chains for parameter vectors of length k
plist.sb[["comp"]]
## chains for parameters vectors of length 1
plist.sb[["single"]]
}

mb <- MultiBatchModelExample
plist.mb <- ggChains(mb)
\dontrun{
## chains for parameters that are batch- and component-specific
plist.mb[["batch"]]
## chains for parameters vectors of length k
plist.mb[["comp"]]
## chains for parameter vectors of length 1
plist.mb[["single"]]
}
}
\seealso{
\code{\link{gibbs}}
}
