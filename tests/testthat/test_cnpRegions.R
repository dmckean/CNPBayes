context("Consensus Regions")

.test_that <- function(nm, expr) NULL

.test_that("test_cnpRegions", {
    g <- GRanges("chr1", IRanges(rep(10, 1000), rep(20, 1000)))
    g2 <- GRanges("chr1", IRanges(rep(5, 10), rep(15, 10)))
    g3 <- GRanges("chr1", IRanges(rep(15, 30), rep(30, 30)))
    g4 <- GRanges("chr1", IRanges(rep(1, 10), rep(25, 10)))
    all_g <- c(g, g2, g3, g4)
    all_g$id <- paste0("sample", seq_along(all_g))
    grl <- split(all_g, all_g$id)
    cnp <- defineCnpRegions(grl, thr = 0.02)
    true_consensus <- GRanges("chr1", IRanges(10, 20))
    expect_identical(true_consensus, cnp)
})
