// This file was generated by Rcpp::compileAttributes
// Generator token: 10BE3573-1514-4C36-9D1C-5A225CD40393

#include <Rcpp.h>

using namespace Rcpp;

// rMultinom
Rcpp::IntegerMatrix rMultinom(Rcpp::NumericMatrix probs, int m);
RcppExport SEXP CNPBayes_rMultinom(SEXP probsSEXP, SEXP mSEXP) {
BEGIN_RCPP
    Rcpp::RObject __result;
    Rcpp::RNGScope __rngScope;
    Rcpp::traits::input_parameter< Rcpp::NumericMatrix >::type probs(probsSEXP);
    Rcpp::traits::input_parameter< int >::type m(mSEXP);
    __result = Rcpp::wrap(rMultinom(probs, m));
    return __result;
END_RCPP
}
// tableZ
IntegerVector tableZ(int K, IntegerVector z);
RcppExport SEXP CNPBayes_tableZ(SEXP KSEXP, SEXP zSEXP) {
BEGIN_RCPP
    Rcpp::RObject __result;
    Rcpp::RNGScope __rngScope;
    Rcpp::traits::input_parameter< int >::type K(KSEXP);
    Rcpp::traits::input_parameter< IntegerVector >::type z(zSEXP);
    __result = Rcpp::wrap(tableZ(K, z));
    return __result;
END_RCPP
}
// full_theta_pooled
Rcpp::NumericVector full_theta_pooled(Rcpp::S4 xmod);
RcppExport SEXP CNPBayes_full_theta_pooled(SEXP xmodSEXP) {
BEGIN_RCPP
    Rcpp::RObject __result;
    Rcpp::RNGScope __rngScope;
    Rcpp::traits::input_parameter< Rcpp::S4 >::type xmod(xmodSEXP);
    __result = Rcpp::wrap(full_theta_pooled(xmod));
    return __result;
END_RCPP
}
// reduced_sigma_pooled
Rcpp::S4 reduced_sigma_pooled(Rcpp::S4 xmod);
RcppExport SEXP CNPBayes_reduced_sigma_pooled(SEXP xmodSEXP) {
BEGIN_RCPP
    Rcpp::RObject __result;
    Rcpp::RNGScope __rngScope;
    Rcpp::traits::input_parameter< Rcpp::S4 >::type xmod(xmodSEXP);
    __result = Rcpp::wrap(reduced_sigma_pooled(xmod));
    return __result;
END_RCPP
}
// p_sigma_reduced_pooled
Rcpp::NumericVector p_sigma_reduced_pooled(Rcpp::S4 xmod);
RcppExport SEXP CNPBayes_p_sigma_reduced_pooled(SEXP xmodSEXP) {
BEGIN_RCPP
    Rcpp::RObject __result;
    Rcpp::RNGScope __rngScope;
    Rcpp::traits::input_parameter< Rcpp::S4 >::type xmod(xmodSEXP);
    __result = Rcpp::wrap(p_sigma_reduced_pooled(xmod));
    return __result;
END_RCPP
}
// reduced_pi_pooled
Rcpp::S4 reduced_pi_pooled(Rcpp::S4 xmod);
RcppExport SEXP CNPBayes_reduced_pi_pooled(SEXP xmodSEXP) {
BEGIN_RCPP
    Rcpp::RObject __result;
    Rcpp::RNGScope __rngScope;
    Rcpp::traits::input_parameter< Rcpp::S4 >::type xmod(xmodSEXP);
    __result = Rcpp::wrap(reduced_pi_pooled(xmod));
    return __result;
END_RCPP
}
// p_pmix_reduced_pooled
Rcpp::NumericVector p_pmix_reduced_pooled(Rcpp::S4 xmod);
RcppExport SEXP CNPBayes_p_pmix_reduced_pooled(SEXP xmodSEXP) {
BEGIN_RCPP
    Rcpp::RObject __result;
    Rcpp::RNGScope __rngScope;
    Rcpp::traits::input_parameter< Rcpp::S4 >::type xmod(xmodSEXP);
    __result = Rcpp::wrap(p_pmix_reduced_pooled(xmod));
    return __result;
END_RCPP
}
// reduced_mu_pooled
Rcpp::S4 reduced_mu_pooled(Rcpp::S4 xmod);
RcppExport SEXP CNPBayes_reduced_mu_pooled(SEXP xmodSEXP) {
BEGIN_RCPP
    Rcpp::RObject __result;
    Rcpp::RNGScope __rngScope;
    Rcpp::traits::input_parameter< Rcpp::S4 >::type xmod(xmodSEXP);
    __result = Rcpp::wrap(reduced_mu_pooled(xmod));
    return __result;
END_RCPP
}
// p_mu_reduced_pooled
Rcpp::NumericVector p_mu_reduced_pooled(Rcpp::S4 xmod);
RcppExport SEXP CNPBayes_p_mu_reduced_pooled(SEXP xmodSEXP) {
BEGIN_RCPP
    Rcpp::RObject __result;
    Rcpp::RNGScope __rngScope;
    Rcpp::traits::input_parameter< Rcpp::S4 >::type xmod(xmodSEXP);
    __result = Rcpp::wrap(p_mu_reduced_pooled(xmod));
    return __result;
END_RCPP
}
// reduced_tau_pooled
Rcpp::S4 reduced_tau_pooled(Rcpp::S4 xmod);
RcppExport SEXP CNPBayes_reduced_tau_pooled(SEXP xmodSEXP) {
BEGIN_RCPP
    Rcpp::RObject __result;
    Rcpp::RNGScope __rngScope;
    Rcpp::traits::input_parameter< Rcpp::S4 >::type xmod(xmodSEXP);
    __result = Rcpp::wrap(reduced_tau_pooled(xmod));
    return __result;
END_RCPP
}
// p_tau_reduced_pooled
Rcpp::NumericVector p_tau_reduced_pooled(Rcpp::S4 xmod);
RcppExport SEXP CNPBayes_p_tau_reduced_pooled(SEXP xmodSEXP) {
BEGIN_RCPP
    Rcpp::RObject __result;
    Rcpp::RNGScope __rngScope;
    Rcpp::traits::input_parameter< Rcpp::S4 >::type xmod(xmodSEXP);
    __result = Rcpp::wrap(p_tau_reduced_pooled(xmod));
    return __result;
END_RCPP
}
// reduced_nu0_pooled
Rcpp::S4 reduced_nu0_pooled(Rcpp::S4 xmod);
RcppExport SEXP CNPBayes_reduced_nu0_pooled(SEXP xmodSEXP) {
BEGIN_RCPP
    Rcpp::RObject __result;
    Rcpp::RNGScope __rngScope;
    Rcpp::traits::input_parameter< Rcpp::S4 >::type xmod(xmodSEXP);
    __result = Rcpp::wrap(reduced_nu0_pooled(xmod));
    return __result;
END_RCPP
}
// p_nu0_reduced_pooled
Rcpp::NumericVector p_nu0_reduced_pooled(Rcpp::S4 xmod);
RcppExport SEXP CNPBayes_p_nu0_reduced_pooled(SEXP xmodSEXP) {
BEGIN_RCPP
    Rcpp::RObject __result;
    Rcpp::RNGScope __rngScope;
    Rcpp::traits::input_parameter< Rcpp::S4 >::type xmod(xmodSEXP);
    __result = Rcpp::wrap(p_nu0_reduced_pooled(xmod));
    return __result;
END_RCPP
}
// reduced_s20_pooled
Rcpp::S4 reduced_s20_pooled(Rcpp::S4 xmod);
RcppExport SEXP CNPBayes_reduced_s20_pooled(SEXP xmodSEXP) {
BEGIN_RCPP
    Rcpp::RObject __result;
    Rcpp::RNGScope __rngScope;
    Rcpp::traits::input_parameter< Rcpp::S4 >::type xmod(xmodSEXP);
    __result = Rcpp::wrap(reduced_s20_pooled(xmod));
    return __result;
END_RCPP
}
// p_s20_reduced_pooled
Rcpp::NumericVector p_s20_reduced_pooled(Rcpp::S4 xmod);
RcppExport SEXP CNPBayes_p_s20_reduced_pooled(SEXP xmodSEXP) {
BEGIN_RCPP
    Rcpp::RObject __result;
    Rcpp::RNGScope __rngScope;
    Rcpp::traits::input_parameter< Rcpp::S4 >::type xmod(xmodSEXP);
    __result = Rcpp::wrap(p_s20_reduced_pooled(xmod));
    return __result;
END_RCPP
}
// loglik_pooled
Rcpp::NumericVector loglik_pooled(Rcpp::S4 xmod);
RcppExport SEXP CNPBayes_loglik_pooled(SEXP xmodSEXP) {
BEGIN_RCPP
    Rcpp::RObject __result;
    Rcpp::RNGScope __rngScope;
    Rcpp::traits::input_parameter< Rcpp::S4 >::type xmod(xmodSEXP);
    __result = Rcpp::wrap(loglik_pooled(xmod));
    return __result;
END_RCPP
}
// stageTwoLogLik_pooled
Rcpp::NumericVector stageTwoLogLik_pooled(Rcpp::S4 xmod);
RcppExport SEXP CNPBayes_stageTwoLogLik_pooled(SEXP xmodSEXP) {
BEGIN_RCPP
    Rcpp::RObject __result;
    Rcpp::RNGScope __rngScope;
    Rcpp::traits::input_parameter< Rcpp::S4 >::type xmod(xmodSEXP);
    __result = Rcpp::wrap(stageTwoLogLik_pooled(xmod));
    return __result;
END_RCPP
}
// multinomialPr_pooled
Rcpp::NumericMatrix multinomialPr_pooled(Rcpp::S4 xmod);
RcppExport SEXP CNPBayes_multinomialPr_pooled(SEXP xmodSEXP) {
BEGIN_RCPP
    Rcpp::RObject __result;
    Rcpp::RNGScope __rngScope;
    Rcpp::traits::input_parameter< Rcpp::S4 >::type xmod(xmodSEXP);
    __result = Rcpp::wrap(multinomialPr_pooled(xmod));
    return __result;
END_RCPP
}
// z_pooled
Rcpp::IntegerVector z_pooled(Rcpp::S4 xmod);
RcppExport SEXP CNPBayes_z_pooled(SEXP xmodSEXP) {
BEGIN_RCPP
    Rcpp::RObject __result;
    Rcpp::RNGScope __rngScope;
    Rcpp::traits::input_parameter< Rcpp::S4 >::type xmod(xmodSEXP);
    __result = Rcpp::wrap(z_pooled(xmod));
    return __result;
END_RCPP
}
// nu0_pooled
Rcpp::NumericVector nu0_pooled(Rcpp::S4 xmod);
RcppExport SEXP CNPBayes_nu0_pooled(SEXP xmodSEXP) {
BEGIN_RCPP
    Rcpp::RObject __result;
    Rcpp::RNGScope __rngScope;
    Rcpp::traits::input_parameter< Rcpp::S4 >::type xmod(xmodSEXP);
    __result = Rcpp::wrap(nu0_pooled(xmod));
    return __result;
END_RCPP
}
// sigma2_0_pooled
Rcpp::NumericVector sigma2_0_pooled(Rcpp::S4 xmod);
RcppExport SEXP CNPBayes_sigma2_0_pooled(SEXP xmodSEXP) {
BEGIN_RCPP
    Rcpp::RObject __result;
    Rcpp::RNGScope __rngScope;
    Rcpp::traits::input_parameter< Rcpp::S4 >::type xmod(xmodSEXP);
    __result = Rcpp::wrap(sigma2_0_pooled(xmod));
    return __result;
END_RCPP
}
// sigma2_pooled
Rcpp::NumericVector sigma2_pooled(Rcpp::S4 xmod);
RcppExport SEXP CNPBayes_sigma2_pooled(SEXP xmodSEXP) {
BEGIN_RCPP
    Rcpp::RObject __result;
    Rcpp::RNGScope __rngScope;
    Rcpp::traits::input_parameter< Rcpp::S4 >::type xmod(xmodSEXP);
    __result = Rcpp::wrap(sigma2_pooled(xmod));
    return __result;
END_RCPP
}
// burnin_singlebatch_pooled
Rcpp::S4 burnin_singlebatch_pooled(Rcpp::S4 xmod, Rcpp::S4 mcmcp);
RcppExport SEXP CNPBayes_burnin_singlebatch_pooled(SEXP xmodSEXP, SEXP mcmcpSEXP) {
BEGIN_RCPP
    Rcpp::RObject __result;
    Rcpp::RNGScope __rngScope;
    Rcpp::traits::input_parameter< Rcpp::S4 >::type xmod(xmodSEXP);
    Rcpp::traits::input_parameter< Rcpp::S4 >::type mcmcp(mcmcpSEXP);
    __result = Rcpp::wrap(burnin_singlebatch_pooled(xmod, mcmcp));
    return __result;
END_RCPP
}
// mcmc_singlebatch_pooled
Rcpp::S4 mcmc_singlebatch_pooled(Rcpp::S4 object, Rcpp::S4 mcmcp);
RcppExport SEXP CNPBayes_mcmc_singlebatch_pooled(SEXP objectSEXP, SEXP mcmcpSEXP) {
BEGIN_RCPP
    Rcpp::RObject __result;
    Rcpp::RNGScope __rngScope;
    Rcpp::traits::input_parameter< Rcpp::S4 >::type object(objectSEXP);
    Rcpp::traits::input_parameter< Rcpp::S4 >::type mcmcp(mcmcpSEXP);
    __result = Rcpp::wrap(mcmc_singlebatch_pooled(object, mcmcp));
    return __result;
END_RCPP
}
// getK
int getK(Rcpp::S4 hyperparams);
RcppExport SEXP CNPBayes_getK(SEXP hyperparamsSEXP) {
BEGIN_RCPP
    Rcpp::RObject __result;
    Rcpp::RNGScope __rngScope;
    Rcpp::traits::input_parameter< Rcpp::S4 >::type hyperparams(hyperparamsSEXP);
    __result = Rcpp::wrap(getK(hyperparams));
    return __result;
END_RCPP
}
// uniqueBatch
Rcpp::IntegerVector uniqueBatch(Rcpp::IntegerVector x);
RcppExport SEXP CNPBayes_uniqueBatch(SEXP xSEXP) {
BEGIN_RCPP
    Rcpp::RObject __result;
    Rcpp::RNGScope __rngScope;
    Rcpp::traits::input_parameter< Rcpp::IntegerVector >::type x(xSEXP);
    __result = Rcpp::wrap(uniqueBatch(x));
    return __result;
END_RCPP
}
// compute_loglik_batch
Rcpp::NumericVector compute_loglik_batch(Rcpp::S4 xmod);
RcppExport SEXP CNPBayes_compute_loglik_batch(SEXP xmodSEXP) {
BEGIN_RCPP
    Rcpp::RObject __result;
    Rcpp::RNGScope __rngScope;
    Rcpp::traits::input_parameter< Rcpp::S4 >::type xmod(xmodSEXP);
    __result = Rcpp::wrap(compute_loglik_batch(xmod));
    return __result;
END_RCPP
}
// update_sigma20_batch
Rcpp::NumericVector update_sigma20_batch(Rcpp::S4 xmod);
RcppExport SEXP CNPBayes_update_sigma20_batch(SEXP xmodSEXP) {
BEGIN_RCPP
    Rcpp::RObject __result;
    Rcpp::RNGScope __rngScope;
    Rcpp::traits::input_parameter< Rcpp::S4 >::type xmod(xmodSEXP);
    __result = Rcpp::wrap(update_sigma20_batch(xmod));
    return __result;
END_RCPP
}
// update_multinomialPr_batch
Rcpp::NumericMatrix update_multinomialPr_batch(Rcpp::S4 xmod);
RcppExport SEXP CNPBayes_update_multinomialPr_batch(SEXP xmodSEXP) {
BEGIN_RCPP
    Rcpp::RObject __result;
    Rcpp::RNGScope __rngScope;
    Rcpp::traits::input_parameter< Rcpp::S4 >::type xmod(xmodSEXP);
    __result = Rcpp::wrap(update_multinomialPr_batch(xmod));
    return __result;
END_RCPP
}
// update_z_batch
Rcpp::IntegerVector update_z_batch(Rcpp::S4 xmod);
RcppExport SEXP CNPBayes_update_z_batch(SEXP xmodSEXP) {
BEGIN_RCPP
    Rcpp::RObject __result;
    Rcpp::RNGScope __rngScope;
    Rcpp::traits::input_parameter< Rcpp::S4 >::type xmod(xmodSEXP);
    __result = Rcpp::wrap(update_z_batch(xmod));
    return __result;
END_RCPP
}
// compute_means_batch
Rcpp::NumericMatrix compute_means_batch(Rcpp::S4 xmod);
RcppExport SEXP CNPBayes_compute_means_batch(SEXP xmodSEXP) {
BEGIN_RCPP
    Rcpp::RObject __result;
    Rcpp::RNGScope __rngScope;
    Rcpp::traits::input_parameter< Rcpp::S4 >::type xmod(xmodSEXP);
    __result = Rcpp::wrap(compute_means_batch(xmod));
    return __result;
END_RCPP
}
// compute_vars_batch
Rcpp::NumericMatrix compute_vars_batch(Rcpp::S4 xmod);
RcppExport SEXP CNPBayes_compute_vars_batch(SEXP xmodSEXP) {
BEGIN_RCPP
    Rcpp::RObject __result;
    Rcpp::RNGScope __rngScope;
    Rcpp::traits::input_parameter< Rcpp::S4 >::type xmod(xmodSEXP);
    __result = Rcpp::wrap(compute_vars_batch(xmod));
    return __result;
END_RCPP
}
// compute_prec_batch
Rcpp::NumericMatrix compute_prec_batch(Rcpp::S4 xmod);
RcppExport SEXP CNPBayes_compute_prec_batch(SEXP xmodSEXP) {
BEGIN_RCPP
    Rcpp::RObject __result;
    Rcpp::RNGScope __rngScope;
    Rcpp::traits::input_parameter< Rcpp::S4 >::type xmod(xmodSEXP);
    __result = Rcpp::wrap(compute_prec_batch(xmod));
    return __result;
END_RCPP
}
// compute_logprior_batch
Rcpp::NumericVector compute_logprior_batch(Rcpp::S4 xmod);
RcppExport SEXP CNPBayes_compute_logprior_batch(SEXP xmodSEXP) {
BEGIN_RCPP
    Rcpp::RObject __result;
    Rcpp::RNGScope __rngScope;
    Rcpp::traits::input_parameter< Rcpp::S4 >::type xmod(xmodSEXP);
    __result = Rcpp::wrap(compute_logprior_batch(xmod));
    return __result;
END_RCPP
}
// stageTwoLogLikBatch
Rcpp::NumericVector stageTwoLogLikBatch(Rcpp::S4 xmod);
RcppExport SEXP CNPBayes_stageTwoLogLikBatch(SEXP xmodSEXP) {
BEGIN_RCPP
    Rcpp::RObject __result;
    Rcpp::RNGScope __rngScope;
    Rcpp::traits::input_parameter< Rcpp::S4 >::type xmod(xmodSEXP);
    __result = Rcpp::wrap(stageTwoLogLikBatch(xmod));
    return __result;
END_RCPP
}
// update_theta_batch
Rcpp::NumericMatrix update_theta_batch(Rcpp::S4 xmod);
RcppExport SEXP CNPBayes_update_theta_batch(SEXP xmodSEXP) {
BEGIN_RCPP
    Rcpp::RObject __result;
    Rcpp::RNGScope __rngScope;
    Rcpp::traits::input_parameter< Rcpp::S4 >::type xmod(xmodSEXP);
    __result = Rcpp::wrap(update_theta_batch(xmod));
    return __result;
END_RCPP
}
// update_sigma2_batch
Rcpp::NumericMatrix update_sigma2_batch(Rcpp::S4 xmod);
RcppExport SEXP CNPBayes_update_sigma2_batch(SEXP xmodSEXP) {
BEGIN_RCPP
    Rcpp::RObject __result;
    Rcpp::RNGScope __rngScope;
    Rcpp::traits::input_parameter< Rcpp::S4 >::type xmod(xmodSEXP);
    __result = Rcpp::wrap(update_sigma2_batch(xmod));
    return __result;
END_RCPP
}
// mcmc_batch_burnin
Rcpp::S4 mcmc_batch_burnin(Rcpp::S4 xmod, Rcpp::S4 mcmcp);
RcppExport SEXP CNPBayes_mcmc_batch_burnin(SEXP xmodSEXP, SEXP mcmcpSEXP) {
BEGIN_RCPP
    Rcpp::RObject __result;
    Rcpp::RNGScope __rngScope;
    Rcpp::traits::input_parameter< Rcpp::S4 >::type xmod(xmodSEXP);
    Rcpp::traits::input_parameter< Rcpp::S4 >::type mcmcp(mcmcpSEXP);
    __result = Rcpp::wrap(mcmc_batch_burnin(xmod, mcmcp));
    return __result;
END_RCPP
}
// mcmc_batch
Rcpp::S4 mcmc_batch(Rcpp::S4 object, Rcpp::S4 mcmcp);
RcppExport SEXP CNPBayes_mcmc_batch(SEXP objectSEXP, SEXP mcmcpSEXP) {
BEGIN_RCPP
    Rcpp::RObject __result;
    Rcpp::RNGScope __rngScope;
    Rcpp::traits::input_parameter< Rcpp::S4 >::type object(objectSEXP);
    Rcpp::traits::input_parameter< Rcpp::S4 >::type mcmcp(mcmcpSEXP);
    __result = Rcpp::wrap(mcmc_batch(object, mcmcp));
    return __result;
END_RCPP
}
// p_theta_batch
Rcpp::NumericVector p_theta_batch(Rcpp::S4 xmod);
RcppExport SEXP CNPBayes_p_theta_batch(SEXP xmodSEXP) {
BEGIN_RCPP
    Rcpp::RObject __result;
    Rcpp::RNGScope __rngScope;
    Rcpp::traits::input_parameter< Rcpp::S4 >::type xmod(xmodSEXP);
    __result = Rcpp::wrap(p_theta_batch(xmod));
    return __result;
END_RCPP
}
// p_theta_zfixed_batch
Rcpp::NumericVector p_theta_zfixed_batch(Rcpp::S4 xmod);
RcppExport SEXP CNPBayes_p_theta_zfixed_batch(SEXP xmodSEXP) {
BEGIN_RCPP
    Rcpp::RObject __result;
    Rcpp::RNGScope __rngScope;
    Rcpp::traits::input_parameter< Rcpp::S4 >::type xmod(xmodSEXP);
    __result = Rcpp::wrap(p_theta_zfixed_batch(xmod));
    return __result;
END_RCPP
}
// reduced_z_theta_fixed
Rcpp::S4 reduced_z_theta_fixed(Rcpp::S4 object);
RcppExport SEXP CNPBayes_reduced_z_theta_fixed(SEXP objectSEXP) {
BEGIN_RCPP
    Rcpp::RObject __result;
    Rcpp::RNGScope __rngScope;
    Rcpp::traits::input_parameter< Rcpp::S4 >::type object(objectSEXP);
    __result = Rcpp::wrap(reduced_z_theta_fixed(object));
    return __result;
END_RCPP
}
// p_sigma2_batch
Rcpp::NumericVector p_sigma2_batch(Rcpp::S4 xmod);
RcppExport SEXP CNPBayes_p_sigma2_batch(SEXP xmodSEXP) {
BEGIN_RCPP
    Rcpp::RObject __result;
    Rcpp::RNGScope __rngScope;
    Rcpp::traits::input_parameter< Rcpp::S4 >::type xmod(xmodSEXP);
    __result = Rcpp::wrap(p_sigma2_batch(xmod));
    return __result;
END_RCPP
}
// loglik
Rcpp::NumericVector loglik(Rcpp::S4 xmod);
RcppExport SEXP CNPBayes_loglik(SEXP xmodSEXP) {
BEGIN_RCPP
    Rcpp::RObject __result;
    Rcpp::RNGScope __rngScope;
    Rcpp::traits::input_parameter< Rcpp::S4 >::type xmod(xmodSEXP);
    __result = Rcpp::wrap(loglik(xmod));
    return __result;
END_RCPP
}
// log_ddirichlet_
Rcpp::NumericVector log_ddirichlet_(Rcpp::NumericVector x_, Rcpp::NumericVector alpha_);
RcppExport SEXP CNPBayes_log_ddirichlet_(SEXP x_SEXP, SEXP alpha_SEXP) {
BEGIN_RCPP
    Rcpp::RObject __result;
    Rcpp::RNGScope __rngScope;
    Rcpp::traits::input_parameter< Rcpp::NumericVector >::type x_(x_SEXP);
    Rcpp::traits::input_parameter< Rcpp::NumericVector >::type alpha_(alpha_SEXP);
    __result = Rcpp::wrap(log_ddirichlet_(x_, alpha_));
    return __result;
END_RCPP
}
// stageTwoLogLik
Rcpp::NumericVector stageTwoLogLik(Rcpp::S4 xmod);
RcppExport SEXP CNPBayes_stageTwoLogLik(SEXP xmodSEXP) {
BEGIN_RCPP
    Rcpp::RObject __result;
    Rcpp::RNGScope __rngScope;
    Rcpp::traits::input_parameter< Rcpp::S4 >::type xmod(xmodSEXP);
    __result = Rcpp::wrap(stageTwoLogLik(xmod));
    return __result;
END_RCPP
}
// update_mu
Rcpp::NumericVector update_mu(Rcpp::S4 xmod);
RcppExport SEXP CNPBayes_update_mu(SEXP xmodSEXP) {
BEGIN_RCPP
    Rcpp::RObject __result;
    Rcpp::RNGScope __rngScope;
    Rcpp::traits::input_parameter< Rcpp::S4 >::type xmod(xmodSEXP);
    __result = Rcpp::wrap(update_mu(xmod));
    return __result;
END_RCPP
}
// update_tau2
Rcpp::NumericVector update_tau2(Rcpp::S4 xmod);
RcppExport SEXP CNPBayes_update_tau2(SEXP xmodSEXP) {
BEGIN_RCPP
    Rcpp::RObject __result;
    Rcpp::RNGScope __rngScope;
    Rcpp::traits::input_parameter< Rcpp::S4 >::type xmod(xmodSEXP);
    __result = Rcpp::wrap(update_tau2(xmod));
    return __result;
END_RCPP
}
// update_sigma2_0
Rcpp::NumericVector update_sigma2_0(Rcpp::S4 xmod);
RcppExport SEXP CNPBayes_update_sigma2_0(SEXP xmodSEXP) {
BEGIN_RCPP
    Rcpp::RObject __result;
    Rcpp::RNGScope __rngScope;
    Rcpp::traits::input_parameter< Rcpp::S4 >::type xmod(xmodSEXP);
    __result = Rcpp::wrap(update_sigma2_0(xmod));
    return __result;
END_RCPP
}
// update_p
Rcpp::NumericVector update_p(Rcpp::S4 xmod);
RcppExport SEXP CNPBayes_update_p(SEXP xmodSEXP) {
BEGIN_RCPP
    Rcpp::RObject __result;
    Rcpp::RNGScope __rngScope;
    Rcpp::traits::input_parameter< Rcpp::S4 >::type xmod(xmodSEXP);
    __result = Rcpp::wrap(update_p(xmod));
    return __result;
END_RCPP
}
// update_multinomialPr
Rcpp::NumericMatrix update_multinomialPr(Rcpp::S4 xmod);
RcppExport SEXP CNPBayes_update_multinomialPr(SEXP xmodSEXP) {
BEGIN_RCPP
    Rcpp::RObject __result;
    Rcpp::RNGScope __rngScope;
    Rcpp::traits::input_parameter< Rcpp::S4 >::type xmod(xmodSEXP);
    __result = Rcpp::wrap(update_multinomialPr(xmod));
    return __result;
END_RCPP
}
// update_z
Rcpp::IntegerVector update_z(Rcpp::S4 xmod);
RcppExport SEXP CNPBayes_update_z(SEXP xmodSEXP) {
BEGIN_RCPP
    Rcpp::RObject __result;
    Rcpp::RNGScope __rngScope;
    Rcpp::traits::input_parameter< Rcpp::S4 >::type xmod(xmodSEXP);
    __result = Rcpp::wrap(update_z(xmod));
    return __result;
END_RCPP
}
// compute_means
Rcpp::NumericVector compute_means(Rcpp::S4 xmod);
RcppExport SEXP CNPBayes_compute_means(SEXP xmodSEXP) {
BEGIN_RCPP
    Rcpp::RObject __result;
    Rcpp::RNGScope __rngScope;
    Rcpp::traits::input_parameter< Rcpp::S4 >::type xmod(xmodSEXP);
    __result = Rcpp::wrap(compute_means(xmod));
    return __result;
END_RCPP
}
// compute_vars
Rcpp::NumericVector compute_vars(Rcpp::S4 xmod);
RcppExport SEXP CNPBayes_compute_vars(SEXP xmodSEXP) {
BEGIN_RCPP
    Rcpp::RObject __result;
    Rcpp::RNGScope __rngScope;
    Rcpp::traits::input_parameter< Rcpp::S4 >::type xmod(xmodSEXP);
    __result = Rcpp::wrap(compute_vars(xmod));
    return __result;
END_RCPP
}
// compute_prec
Rcpp::NumericVector compute_prec(Rcpp::S4 xmod);
RcppExport SEXP CNPBayes_compute_prec(SEXP xmodSEXP) {
BEGIN_RCPP
    Rcpp::RObject __result;
    Rcpp::RNGScope __rngScope;
    Rcpp::traits::input_parameter< Rcpp::S4 >::type xmod(xmodSEXP);
    __result = Rcpp::wrap(compute_prec(xmod));
    return __result;
END_RCPP
}
// compute_logprior
Rcpp::NumericVector compute_logprior(Rcpp::S4 xmod);
RcppExport SEXP CNPBayes_compute_logprior(SEXP xmodSEXP) {
BEGIN_RCPP
    Rcpp::RObject __result;
    Rcpp::RNGScope __rngScope;
    Rcpp::traits::input_parameter< Rcpp::S4 >::type xmod(xmodSEXP);
    __result = Rcpp::wrap(compute_logprior(xmod));
    return __result;
END_RCPP
}
// update_sigma2
Rcpp::NumericVector update_sigma2(Rcpp::S4 xmod);
RcppExport SEXP CNPBayes_update_sigma2(SEXP xmodSEXP) {
BEGIN_RCPP
    Rcpp::RObject __result;
    Rcpp::RNGScope __rngScope;
    Rcpp::traits::input_parameter< Rcpp::S4 >::type xmod(xmodSEXP);
    __result = Rcpp::wrap(update_sigma2(xmod));
    return __result;
END_RCPP
}
// mcmc_marginal_burnin
Rcpp::S4 mcmc_marginal_burnin(Rcpp::S4 xmod, Rcpp::S4 mcmcp);
RcppExport SEXP CNPBayes_mcmc_marginal_burnin(SEXP xmodSEXP, SEXP mcmcpSEXP) {
BEGIN_RCPP
    Rcpp::RObject __result;
    Rcpp::RNGScope __rngScope;
    Rcpp::traits::input_parameter< Rcpp::S4 >::type xmod(xmodSEXP);
    Rcpp::traits::input_parameter< Rcpp::S4 >::type mcmcp(mcmcpSEXP);
    __result = Rcpp::wrap(mcmc_marginal_burnin(xmod, mcmcp));
    return __result;
END_RCPP
}
// mcmc_marginal
Rcpp::S4 mcmc_marginal(Rcpp::S4 object, Rcpp::S4 mcmcp);
RcppExport SEXP CNPBayes_mcmc_marginal(SEXP objectSEXP, SEXP mcmcpSEXP) {
BEGIN_RCPP
    Rcpp::RObject __result;
    Rcpp::RNGScope __rngScope;
    Rcpp::traits::input_parameter< Rcpp::S4 >::type object(objectSEXP);
    Rcpp::traits::input_parameter< Rcpp::S4 >::type mcmcp(mcmcpSEXP);
    __result = Rcpp::wrap(mcmc_marginal(object, mcmcp));
    return __result;
END_RCPP
}
// marginal_theta_batch
Rcpp::NumericVector marginal_theta_batch(Rcpp::S4 xmod);
RcppExport SEXP CNPBayes_marginal_theta_batch(SEXP xmodSEXP) {
BEGIN_RCPP
    Rcpp::RObject __result;
    Rcpp::RNGScope __rngScope;
    Rcpp::traits::input_parameter< Rcpp::S4 >::type xmod(xmodSEXP);
    __result = Rcpp::wrap(marginal_theta_batch(xmod));
    return __result;
END_RCPP
}
// p_theta_zpermuted_batch
Rcpp::NumericVector p_theta_zpermuted_batch(Rcpp::S4 xmod);
RcppExport SEXP CNPBayes_p_theta_zpermuted_batch(SEXP xmodSEXP) {
BEGIN_RCPP
    Rcpp::RObject __result;
    Rcpp::RNGScope __rngScope;
    Rcpp::traits::input_parameter< Rcpp::S4 >::type xmod(xmodSEXP);
    __result = Rcpp::wrap(p_theta_zpermuted_batch(xmod));
    return __result;
END_RCPP
}
// simulate_z_reduced1_batch
Rcpp::S4 simulate_z_reduced1_batch(Rcpp::S4 object);
RcppExport SEXP CNPBayes_simulate_z_reduced1_batch(SEXP objectSEXP) {
BEGIN_RCPP
    Rcpp::RObject __result;
    Rcpp::RNGScope __rngScope;
    Rcpp::traits::input_parameter< Rcpp::S4 >::type object(objectSEXP);
    __result = Rcpp::wrap(simulate_z_reduced1_batch(object));
    return __result;
END_RCPP
}
// simulate_z_reduced2_batch
Rcpp::S4 simulate_z_reduced2_batch(Rcpp::S4 object);
RcppExport SEXP CNPBayes_simulate_z_reduced2_batch(SEXP objectSEXP) {
BEGIN_RCPP
    Rcpp::RObject __result;
    Rcpp::RNGScope __rngScope;
    Rcpp::traits::input_parameter< Rcpp::S4 >::type object(objectSEXP);
    __result = Rcpp::wrap(simulate_z_reduced2_batch(object));
    return __result;
END_RCPP
}
// permutedz_reduced1_batch
Rcpp::S4 permutedz_reduced1_batch(Rcpp::S4 xmod);
RcppExport SEXP CNPBayes_permutedz_reduced1_batch(SEXP xmodSEXP) {
BEGIN_RCPP
    Rcpp::RObject __result;
    Rcpp::RNGScope __rngScope;
    Rcpp::traits::input_parameter< Rcpp::S4 >::type xmod(xmodSEXP);
    __result = Rcpp::wrap(permutedz_reduced1_batch(xmod));
    return __result;
END_RCPP
}
// permutedz_reduced2_batch
Rcpp::S4 permutedz_reduced2_batch(Rcpp::S4 xmod);
RcppExport SEXP CNPBayes_permutedz_reduced2_batch(SEXP xmodSEXP) {
BEGIN_RCPP
    Rcpp::RObject __result;
    Rcpp::RNGScope __rngScope;
    Rcpp::traits::input_parameter< Rcpp::S4 >::type xmod(xmodSEXP);
    __result = Rcpp::wrap(permutedz_reduced2_batch(xmod));
    return __result;
END_RCPP
}
// p_pmix_reduced_batch
Rcpp::NumericVector p_pmix_reduced_batch(Rcpp::S4 xmod);
RcppExport SEXP CNPBayes_p_pmix_reduced_batch(SEXP xmodSEXP) {
BEGIN_RCPP
    Rcpp::RObject __result;
    Rcpp::RNGScope __rngScope;
    Rcpp::traits::input_parameter< Rcpp::S4 >::type xmod(xmodSEXP);
    __result = Rcpp::wrap(p_pmix_reduced_batch(xmod));
    return __result;
END_RCPP
}
// reduced_sigma_batch
Rcpp::S4 reduced_sigma_batch(Rcpp::S4 xmod);
RcppExport SEXP CNPBayes_reduced_sigma_batch(SEXP xmodSEXP) {
BEGIN_RCPP
    Rcpp::RObject __result;
    Rcpp::RNGScope __rngScope;
    Rcpp::traits::input_parameter< Rcpp::S4 >::type xmod(xmodSEXP);
    __result = Rcpp::wrap(reduced_sigma_batch(xmod));
    return __result;
END_RCPP
}
// p_sigma_reduced_batch
Rcpp::NumericVector p_sigma_reduced_batch(Rcpp::S4 xmod);
RcppExport SEXP CNPBayes_p_sigma_reduced_batch(SEXP xmodSEXP) {
BEGIN_RCPP
    Rcpp::RObject __result;
    Rcpp::RNGScope __rngScope;
    Rcpp::traits::input_parameter< Rcpp::S4 >::type xmod(xmodSEXP);
    __result = Rcpp::wrap(p_sigma_reduced_batch(xmod));
    return __result;
END_RCPP
}
// reduced_pi_batch
Rcpp::S4 reduced_pi_batch(Rcpp::S4 xmod);
RcppExport SEXP CNPBayes_reduced_pi_batch(SEXP xmodSEXP) {
BEGIN_RCPP
    Rcpp::RObject __result;
    Rcpp::RNGScope __rngScope;
    Rcpp::traits::input_parameter< Rcpp::S4 >::type xmod(xmodSEXP);
    __result = Rcpp::wrap(reduced_pi_batch(xmod));
    return __result;
END_RCPP
}
// reduced_mu_batch
Rcpp::S4 reduced_mu_batch(Rcpp::S4 xmod);
RcppExport SEXP CNPBayes_reduced_mu_batch(SEXP xmodSEXP) {
BEGIN_RCPP
    Rcpp::RObject __result;
    Rcpp::RNGScope __rngScope;
    Rcpp::traits::input_parameter< Rcpp::S4 >::type xmod(xmodSEXP);
    __result = Rcpp::wrap(reduced_mu_batch(xmod));
    return __result;
END_RCPP
}
// p_mu_reduced_batch
Rcpp::NumericVector p_mu_reduced_batch(Rcpp::S4 xmod);
RcppExport SEXP CNPBayes_p_mu_reduced_batch(SEXP xmodSEXP) {
BEGIN_RCPP
    Rcpp::RObject __result;
    Rcpp::RNGScope __rngScope;
    Rcpp::traits::input_parameter< Rcpp::S4 >::type xmod(xmodSEXP);
    __result = Rcpp::wrap(p_mu_reduced_batch(xmod));
    return __result;
END_RCPP
}
// reduced_tau_batch
Rcpp::S4 reduced_tau_batch(Rcpp::S4 xmod);
RcppExport SEXP CNPBayes_reduced_tau_batch(SEXP xmodSEXP) {
BEGIN_RCPP
    Rcpp::RObject __result;
    Rcpp::RNGScope __rngScope;
    Rcpp::traits::input_parameter< Rcpp::S4 >::type xmod(xmodSEXP);
    __result = Rcpp::wrap(reduced_tau_batch(xmod));
    return __result;
END_RCPP
}
// p_tau_reduced_batch
Rcpp::NumericVector p_tau_reduced_batch(Rcpp::S4 xmod);
RcppExport SEXP CNPBayes_p_tau_reduced_batch(SEXP xmodSEXP) {
BEGIN_RCPP
    Rcpp::RObject __result;
    Rcpp::RNGScope __rngScope;
    Rcpp::traits::input_parameter< Rcpp::S4 >::type xmod(xmodSEXP);
    __result = Rcpp::wrap(p_tau_reduced_batch(xmod));
    return __result;
END_RCPP
}
// reduced_nu0_batch
Rcpp::S4 reduced_nu0_batch(Rcpp::S4 xmod);
RcppExport SEXP CNPBayes_reduced_nu0_batch(SEXP xmodSEXP) {
BEGIN_RCPP
    Rcpp::RObject __result;
    Rcpp::RNGScope __rngScope;
    Rcpp::traits::input_parameter< Rcpp::S4 >::type xmod(xmodSEXP);
    __result = Rcpp::wrap(reduced_nu0_batch(xmod));
    return __result;
END_RCPP
}
// p_nu0_reduced_batch
Rcpp::NumericVector p_nu0_reduced_batch(Rcpp::S4 xmod);
RcppExport SEXP CNPBayes_p_nu0_reduced_batch(SEXP xmodSEXP) {
BEGIN_RCPP
    Rcpp::RObject __result;
    Rcpp::RNGScope __rngScope;
    Rcpp::traits::input_parameter< Rcpp::S4 >::type xmod(xmodSEXP);
    __result = Rcpp::wrap(p_nu0_reduced_batch(xmod));
    return __result;
END_RCPP
}
// reduced_s20_batch
Rcpp::S4 reduced_s20_batch(Rcpp::S4 xmod);
RcppExport SEXP CNPBayes_reduced_s20_batch(SEXP xmodSEXP) {
BEGIN_RCPP
    Rcpp::RObject __result;
    Rcpp::RNGScope __rngScope;
    Rcpp::traits::input_parameter< Rcpp::S4 >::type xmod(xmodSEXP);
    __result = Rcpp::wrap(reduced_s20_batch(xmod));
    return __result;
END_RCPP
}
// p_s20_reduced_batch
Rcpp::NumericVector p_s20_reduced_batch(Rcpp::S4 xmod);
RcppExport SEXP CNPBayes_p_s20_reduced_batch(SEXP xmodSEXP) {
BEGIN_RCPP
    Rcpp::RObject __result;
    Rcpp::RNGScope __rngScope;
    Rcpp::traits::input_parameter< Rcpp::S4 >::type xmod(xmodSEXP);
    __result = Rcpp::wrap(p_s20_reduced_batch(xmod));
    return __result;
END_RCPP
}
// marginal_theta
Rcpp::NumericVector marginal_theta(Rcpp::S4 xmod);
RcppExport SEXP CNPBayes_marginal_theta(SEXP xmodSEXP) {
BEGIN_RCPP
    Rcpp::RObject __result;
    Rcpp::RNGScope __rngScope;
    Rcpp::traits::input_parameter< Rcpp::S4 >::type xmod(xmodSEXP);
    __result = Rcpp::wrap(marginal_theta(xmod));
    return __result;
END_RCPP
}
// p_theta_zpermuted
Rcpp::NumericVector p_theta_zpermuted(Rcpp::S4 xmod);
RcppExport SEXP CNPBayes_p_theta_zpermuted(SEXP xmodSEXP) {
BEGIN_RCPP
    Rcpp::RObject __result;
    Rcpp::RNGScope __rngScope;
    Rcpp::traits::input_parameter< Rcpp::S4 >::type xmod(xmodSEXP);
    __result = Rcpp::wrap(p_theta_zpermuted(xmod));
    return __result;
END_RCPP
}
// simulate_z_reduced1
Rcpp::S4 simulate_z_reduced1(Rcpp::S4 object);
RcppExport SEXP CNPBayes_simulate_z_reduced1(SEXP objectSEXP) {
BEGIN_RCPP
    Rcpp::RObject __result;
    Rcpp::RNGScope __rngScope;
    Rcpp::traits::input_parameter< Rcpp::S4 >::type object(objectSEXP);
    __result = Rcpp::wrap(simulate_z_reduced1(object));
    return __result;
END_RCPP
}
// simulate_z_reduced2
Rcpp::S4 simulate_z_reduced2(Rcpp::S4 object);
RcppExport SEXP CNPBayes_simulate_z_reduced2(SEXP objectSEXP) {
BEGIN_RCPP
    Rcpp::RObject __result;
    Rcpp::RNGScope __rngScope;
    Rcpp::traits::input_parameter< Rcpp::S4 >::type object(objectSEXP);
    __result = Rcpp::wrap(simulate_z_reduced2(object));
    return __result;
END_RCPP
}
// permutedz_reduced1
Rcpp::S4 permutedz_reduced1(Rcpp::S4 xmod);
RcppExport SEXP CNPBayes_permutedz_reduced1(SEXP xmodSEXP) {
BEGIN_RCPP
    Rcpp::RObject __result;
    Rcpp::RNGScope __rngScope;
    Rcpp::traits::input_parameter< Rcpp::S4 >::type xmod(xmodSEXP);
    __result = Rcpp::wrap(permutedz_reduced1(xmod));
    return __result;
END_RCPP
}
// permutedz_reduced2
Rcpp::S4 permutedz_reduced2(Rcpp::S4 xmod);
RcppExport SEXP CNPBayes_permutedz_reduced2(SEXP xmodSEXP) {
BEGIN_RCPP
    Rcpp::RObject __result;
    Rcpp::RNGScope __rngScope;
    Rcpp::traits::input_parameter< Rcpp::S4 >::type xmod(xmodSEXP);
    __result = Rcpp::wrap(permutedz_reduced2(xmod));
    return __result;
END_RCPP
}
// p_pmix_reduced
Rcpp::NumericVector p_pmix_reduced(Rcpp::S4 xmod);
RcppExport SEXP CNPBayes_p_pmix_reduced(SEXP xmodSEXP) {
BEGIN_RCPP
    Rcpp::RObject __result;
    Rcpp::RNGScope __rngScope;
    Rcpp::traits::input_parameter< Rcpp::S4 >::type xmod(xmodSEXP);
    __result = Rcpp::wrap(p_pmix_reduced(xmod));
    return __result;
END_RCPP
}
// reduced_sigma
Rcpp::S4 reduced_sigma(Rcpp::S4 xmod);
RcppExport SEXP CNPBayes_reduced_sigma(SEXP xmodSEXP) {
BEGIN_RCPP
    Rcpp::RObject __result;
    Rcpp::RNGScope __rngScope;
    Rcpp::traits::input_parameter< Rcpp::S4 >::type xmod(xmodSEXP);
    __result = Rcpp::wrap(reduced_sigma(xmod));
    return __result;
END_RCPP
}
// p_sigma_reduced
Rcpp::NumericVector p_sigma_reduced(Rcpp::S4 xmod);
RcppExport SEXP CNPBayes_p_sigma_reduced(SEXP xmodSEXP) {
BEGIN_RCPP
    Rcpp::RObject __result;
    Rcpp::RNGScope __rngScope;
    Rcpp::traits::input_parameter< Rcpp::S4 >::type xmod(xmodSEXP);
    __result = Rcpp::wrap(p_sigma_reduced(xmod));
    return __result;
END_RCPP
}
// reduced_pi
Rcpp::S4 reduced_pi(Rcpp::S4 xmod);
RcppExport SEXP CNPBayes_reduced_pi(SEXP xmodSEXP) {
BEGIN_RCPP
    Rcpp::RObject __result;
    Rcpp::RNGScope __rngScope;
    Rcpp::traits::input_parameter< Rcpp::S4 >::type xmod(xmodSEXP);
    __result = Rcpp::wrap(reduced_pi(xmod));
    return __result;
END_RCPP
}
// reduced_mu
Rcpp::S4 reduced_mu(Rcpp::S4 xmod);
RcppExport SEXP CNPBayes_reduced_mu(SEXP xmodSEXP) {
BEGIN_RCPP
    Rcpp::RObject __result;
    Rcpp::RNGScope __rngScope;
    Rcpp::traits::input_parameter< Rcpp::S4 >::type xmod(xmodSEXP);
    __result = Rcpp::wrap(reduced_mu(xmod));
    return __result;
END_RCPP
}
// p_mu_reduced
Rcpp::NumericVector p_mu_reduced(Rcpp::S4 xmod);
RcppExport SEXP CNPBayes_p_mu_reduced(SEXP xmodSEXP) {
BEGIN_RCPP
    Rcpp::RObject __result;
    Rcpp::RNGScope __rngScope;
    Rcpp::traits::input_parameter< Rcpp::S4 >::type xmod(xmodSEXP);
    __result = Rcpp::wrap(p_mu_reduced(xmod));
    return __result;
END_RCPP
}
// reduced_tau
Rcpp::S4 reduced_tau(Rcpp::S4 xmod);
RcppExport SEXP CNPBayes_reduced_tau(SEXP xmodSEXP) {
BEGIN_RCPP
    Rcpp::RObject __result;
    Rcpp::RNGScope __rngScope;
    Rcpp::traits::input_parameter< Rcpp::S4 >::type xmod(xmodSEXP);
    __result = Rcpp::wrap(reduced_tau(xmod));
    return __result;
END_RCPP
}
// p_tau_reduced
Rcpp::NumericVector p_tau_reduced(Rcpp::S4 xmod);
RcppExport SEXP CNPBayes_p_tau_reduced(SEXP xmodSEXP) {
BEGIN_RCPP
    Rcpp::RObject __result;
    Rcpp::RNGScope __rngScope;
    Rcpp::traits::input_parameter< Rcpp::S4 >::type xmod(xmodSEXP);
    __result = Rcpp::wrap(p_tau_reduced(xmod));
    return __result;
END_RCPP
}
// reduced_nu0
Rcpp::S4 reduced_nu0(Rcpp::S4 xmod);
RcppExport SEXP CNPBayes_reduced_nu0(SEXP xmodSEXP) {
BEGIN_RCPP
    Rcpp::RObject __result;
    Rcpp::RNGScope __rngScope;
    Rcpp::traits::input_parameter< Rcpp::S4 >::type xmod(xmodSEXP);
    __result = Rcpp::wrap(reduced_nu0(xmod));
    return __result;
END_RCPP
}
// p_nu0_reduced
Rcpp::NumericVector p_nu0_reduced(Rcpp::S4 xmod);
RcppExport SEXP CNPBayes_p_nu0_reduced(SEXP xmodSEXP) {
BEGIN_RCPP
    Rcpp::RObject __result;
    Rcpp::RNGScope __rngScope;
    Rcpp::traits::input_parameter< Rcpp::S4 >::type xmod(xmodSEXP);
    __result = Rcpp::wrap(p_nu0_reduced(xmod));
    return __result;
END_RCPP
}
// reduced_s20
Rcpp::S4 reduced_s20(Rcpp::S4 xmod);
RcppExport SEXP CNPBayes_reduced_s20(SEXP xmodSEXP) {
BEGIN_RCPP
    Rcpp::RObject __result;
    Rcpp::RNGScope __rngScope;
    Rcpp::traits::input_parameter< Rcpp::S4 >::type xmod(xmodSEXP);
    __result = Rcpp::wrap(reduced_s20(xmod));
    return __result;
END_RCPP
}
// p_s20_reduced
Rcpp::NumericVector p_s20_reduced(Rcpp::S4 xmod);
RcppExport SEXP CNPBayes_p_s20_reduced(SEXP xmodSEXP) {
BEGIN_RCPP
    Rcpp::RObject __result;
    Rcpp::RNGScope __rngScope;
    Rcpp::traits::input_parameter< Rcpp::S4 >::type xmod(xmodSEXP);
    __result = Rcpp::wrap(p_s20_reduced(xmod));
    return __result;
END_RCPP
}
