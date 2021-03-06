context("SingleBatchModel")

.test_that <- function(name, expr){}

test_that("test_marginal_empty_component", {
    set.seed(1)
    truth <- simulateData(N = 10, p = rep(1/3, 3), theta = c(-1,
        0, 1), sds = rep(0.1, 3))
    mp <- McmcParams(iter = 5, burnin = 5, nStarts = 1)
    model <- SingleBatchModel2(dat = y(truth),
                               hp=hpList(k = 3)[["SB"]],
                               mp = mp)
    expect_false(any(is.na(computeMeans(model))))
})


test_that("test_marginal_few_data", {
  expect_error(model <- SingleBatchModel2(dat = 0:1,
                                          hp=hpList(k = 3)[["SB"]]))
})

test_that("hard", {
    set.seed(1337)
    truth <- simulateData(N = 1000,
                          theta = c(-2, -0.4, 0),
                          sds = c(0.3, 0.15, 0.15),
                          p = c(0.005, 1/10, 1 - 0.005 - 1/10))
    expect_is(truth, "SingleBatchModel")
    if(FALSE){
      ## mcmcp <- McmcParams(iter = 1000, burnin = 500, thin = 10,
      ##                     nStarts = 20)
      ##
      ## do enough iterations so that any label switching occurs
      ##
      mcmcp <- McmcParams(iter = 500, burnin = 200, thin = 0,
                          nStarts = 20)
      model <- SingleBatchModel2(dat=y(truth), hp=hpList(k = 3)[["SB"]])
      model <- posteriorSimulation(model)
      i <- order(theta(model))
      expect_identical(i, 1:3)
      expect_equal(theta(truth), theta(model), tolerance=0.15)
      expect_equal(sigma(truth), colMeans(sigmac(model)), tolerance=0.1)
      expect_equal(p(truth), colMeans(pic(model)), tolerance=0.18)
      expect_identical(numberObs(truth), 1000L)
    }
})

test_that("moderate", {
    set.seed(100)
    truth <- simulateData(N = 1000,
                          theta = c(-2, -0.4, 0),
                          sds = c(0.3, 0.15, 0.15),
                          p = c(0.05, 0.1, 0.8))
    ## verify that if we start at the true value, we remain in a region of
    ## high posterior probability after an arbitrary number of mcmc updates
    mcmcp <- McmcParams(iter = 1000, burnin = 300,
                        thin = 1, nStarts=1)
    model <- SingleBatchModel2(dat=y(truth),
                               hp=hpList(k = 3)[["SB"]],
                               mp = mcmcp)
    model <- startAtTrueValues(model, truth)
    model <- posteriorSimulation(model)
    expect_equal(theta(truth), theta(model), tolerance=0.2)
    expect_equal(sigma(truth), sigma(model), tolerance=0.15)
    expect_equal(p(truth), colMeans(pic(model)), tolerance=0.2)
  })


test_that("easy", {
    set.seed(1)
    truth <- simulateData(N = 1500, p = rep(1/3, 3),
                          theta = c(-1, 0, 1),
                          sds = rep(0.1, 3))
    mp <- McmcParams(iter = 100, burnin = 100)
    model <- SingleBatchModel2(dat = y(truth),
                               hp=hpList(k=3)[["SB"]],
                               mp = mp)
    model <- posteriorSimulation(model)
    if (FALSE) {
        SingleBatchModelExample <- model
        save(SingleBatchModelExample, file = "data/SingleBatchModelExample.RData")
    }
    expect_equal(theta(model), theta(truth), tolerance=0.03)
    expect_equal(sigma(model), sigma(truth), tolerance=0.11)
    expect_equal(p(model), p(truth), tolerance=0.05)
    i <- argMax(model)
    expect_true(i == which.max(logPrior(chains(model)) + log_lik(chains(model))))
    expect_identical(sort(thetac(model)[i, ]), modes(model)[["theta"]])
    expect_identical(sort(sigmac(model)[i, ]),
                     sort(sqrt(modes(model)[["sigma2"]])))
})


test_that("cnProbability", {
    set.seed(1)
    truth <- simulateData(N = 2500, p = rep(1/3, 3),
                          theta = c(-1, 0, 1), sds = rep(0.1, 3))
    mp <- McmcParams(iter = 200, burnin = 100, nStarts = 1)
    model <- SingleBatchModel2(dat = y(truth),
                              hp=hpList(k = 3)[["SB"]], mp = mp)
    model <- posteriorSimulation(model)
    map_model <- mapModel(model)
    expect_identical(z(map_model), zChain(model)[argMax(model),])
    expect_identical(theta(map_model), thetac(model)[argMax(model), 
        ])
    probs <- mapCnProbability(model)
    pz <- probz(model)
    expect_equal(head(pz), head(probs), tolerance=0.01)
})

context("Check computeMeans method")

test_that("computeMeans", {
  set.seed(2000)
  truth <- simulateData(N = 1000, theta = c(-2, -0.4, 0),
                        sds = c(0.3, 0.15, 0.15),
                        p = c(0.005, 1/10, 1 - 0.005 - 1/10))
  mp <- McmcParams(iter = 10, burnin = 10)
  model <- SingleBatchModel2(dat=y(truth), hp=hpList(k = 3)[["SB"]],
                             mp=mp)
  model <- posteriorSimulation(model)
  mns <- sapply(split(y(model), z(model)), mean)
  mns <- as.numeric(mns)

  mns2 <- compute_means(model)
  expect_equal(mns, mns2)
})

test_that("relabel", {
    set.seed(1)
    truth <- simulateData(N = 2500, p = rep(1/3, 3), theta = c(-1, 
        0, 1), sds = rep(0.1, 3))
    mp <- McmcParams(iter = 500, burnin = 500)
    model <- SingleBatchModel2(dat = y(truth), hp=hpList(k = 3)[["SB"]],
                               mp = mp)
    model <- posteriorSimulation(model)
    zindex <- c(3, 2, 1)
    model2 <- relabel(model, zindex)
    expect_identical(as.integer(tablez(model2)[zindex]), 
        as.integer(tablez(model)))
    expect_identical(dataMean(model2)[zindex], dataMean(model))
    expect_identical(theta(model2), theta(model))
    expect_identical(mu(model2), mu(model))
    expect_identical(p(model2), p(model))
    expect_identical(sigma(model2), sigma(model))
    expect_identical(nu.0(model2), nu.0(model))
    if (FALSE) {
        burnin(model2) <- 0
        model2 <- posteriorSimulation(model2)
        head(thetac(model2))
        plot.ts(thetac(model2), plot.type = "single", col = 1:3)
        set.seed(1)
        truth <- simulateData(N = 2500, p = rep(1/3, 3), theta = c(-1, 
            0, 1), sds = rep(0.5, 3))
        mp <- McmcParams(iter = 500, burnin = 500)
        model <- SingleBatchModel(data = y(truth), k = 3, mcmc.params = mp)
        model <- posteriorSimulation(model)
        zindex <- c(3, 2, 1)
        model2 <- relabel(model, zindex)
        burnin(model2) <- 0
        model2 <- posteriorSimulation(model2)
        par(mfrow = c(1, 2))
        plot.ts(thetac(model), col = 1:3, plot.type = "single")
        plot.ts(thetac(model2), col = 1:3, plot.type = "single")
    }
})

test_that("targeted seq", {
  set.seed(123)
  mp <- McmcParams(iter=500, burnin=1000, nStarts=4)
  extfile <- file.path(system.file("extdata", package="CNPBayes"),
                       "targeted_seq.txt")
  dat <- read.delim(extfile)[[1]]
  dat <- sample(dat, 500)
  mlist <- gibbs(model="SB", mp=mp, dat=dat, k_range=c(2, 3))
  ##
  ## Select k=3
  ##
  expect_identical(names(mlist)[1], "SB3")
})
