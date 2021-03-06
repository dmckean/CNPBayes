#include "miscfunctions.h" // for rdirichlet, tableZ, ...
#include "singlebatch.h"
#include "singlebatch_pooledvar.h"
#include "update.h"
#include <Rcpp.h>

using namespace Rcpp;

// [[Rcpp::export]]
Rcpp::NumericVector full_theta_pooled(Rcpp::S4 xmod) {
  RNGScope scope ;
  Rcpp::S4 model_(xmod) ;
  Rcpp::S4 model = clone(model_) ;
  Rcpp::S4 params=model.slot("mcmc.params") ;
  Rcpp::S4 chains(model.slot("mcmc.chains")) ;  
  int S = params.slot("iter") ;
  // Assume current values are the modes (in R, useModes(object) ensures this)
  // List modes = model.slot("modes") ;
  // NumericVector thetastar = as<NumericVector>(modes["theta"]) ;
  List modes = model.slot("modes") ;
  NumericVector theta_ = as<NumericVector>(modes["theta"]) ;
  NumericVector thetastar=clone(theta_) ;
  int K = thetastar.size() ;
  NumericVector p_theta(S) ;
  NumericVector muc = chains.slot("mu") ;
  NumericVector tau2c = chains.slot("tau2") ;
  // sigma2 is a matrix with one column
  NumericMatrix sigma2 = chains.slot("sigma2") ;
  NumericVector tauc = sqrt(tau2c) ;
  NumericVector tmp(K) ;

  IntegerMatrix Z = chains.slot("z") ;
  IntegerVector zz ;

  double tau2_tilde ;
  NumericVector sigma2_tilde(1) ;

  // this should be updated for each iteration
  NumericVector data_mean(K) ;
  IntegerVector nn(K) ;
  double post_prec;
  double tau_n;
  double mu_n;
  double w1;
  double w2;
  double prod ;
  for(int s=0; s < S; ++s){
    zz = Z(s, _) ;
    model.slot("z") = zz ;
    nn = tableZ(K, zz) ;
    data_mean = compute_means(model) ;
    tau2_tilde = 1/tau2c[s] ;
    sigma2_tilde = 1.0/sigma2(s, 0) ;
    double prod = 1.0;
    for(int k = 0; k < K; ++k) {
      post_prec = tau2_tilde + sigma2_tilde[0] * nn[k];
      tau_n = sqrt(1/post_prec);
      w1 = tau2_tilde/post_prec;
      w2 = nn[k]*sigma2_tilde[0]/post_prec;
      mu_n = w1*muc[s] + w2*data_mean[k];
      tmp = dnorm(thetastar, mu_n, tau_n) ;
      prod = prod * tmp[k] ;
    }
    p_theta[s] = prod ;
  }
  return p_theta ;
}

// not finished




// [[Rcpp::export]]
Rcpp::S4 reduced_sigma_pooled(Rcpp::S4 xmod) {
  RNGScope scope ;
  Rcpp::S4 model_(xmod) ;
  Rcpp::S4 model = clone(model_) ;
  Rcpp::S4 params=model.slot("mcmc.params") ;
  Rcpp::S4 chains=model.slot("mcmc.chains") ;
  int S = params.slot("iter") ;
  List modes = model.slot("modes") ;
  NumericVector sigma2_ = as<NumericVector>(modes["sigma2"]) ;
  NumericVector theta_ = as<NumericVector>(modes["theta"]) ;
  NumericVector thetastar=clone(theta_) ;
  int K = thetastar.size() ;
  NumericVector prec(1) ;
  NumericVector logp_prec(S) ;
  NumericVector y = model.slot("data") ;
  int N = y.size() ;
  NumericVector tau2(1) ;
  NumericVector nu0 (1) ;
  NumericVector s20 (1) ;
  NumericVector s2 (1) ;
  //
  // We need to keep the Z|y,theta* chain
  //
  IntegerMatrix Z = chains.slot("z") ;
  NumericVector nu0chain = chains.slot("nu.0") ;
  NumericVector s20chain = chains.slot("sigma2.0") ;
  NumericVector muchain = chains.slot("mu") ;
  NumericVector tauchain = chains.slot("tau2") ;
  NumericMatrix pichain = chains.slot("pi") ;
  NumericMatrix sigmachain = chains.slot("sigma2") ;
  
  NumericVector sigma2 = model.slot("sigma2") ;
  NumericVector pi = model.slot("pi") ;
  NumericVector tau = model.slot("tau2") ;
  NumericVector mu = model.slot("mu") ;

  //model.slot("theta") = thetastar ;
  IntegerVector zz(N) ;
  //
  // Run reduced Gibbs  -- theta is fixed at modal ordinate
  //  
  for(int s=0; s < S; ++s){
    zz = z_pooled(model) ;
    model.slot("z") = zz ;
    Z(s, _) = zz ;
    model.slot("data.mean") = compute_means(model) ;
    model.slot("data.prec") = compute_prec(model) ;
    //model.slot("theta") = theta_pooled(model) ; Do not update theta !
    model.slot("sigma2") = sigma2_pooled(model) ;
    model.slot("pi") = update_p(model) ;
    model.slot("mu") = update_mu(model) ;
    model.slot("tau2") = update_tau2(model) ;
    model.slot("nu.0") = nu0_pooled(model) ;
    model.slot("sigma2.0") = sigma2_0_pooled(model) ;
    nu0chain[s] = model.slot("nu.0") ;
    s20chain[s] = model.slot("sigma2.0") ;
    // update the following chains for debugging small sigma2.0 values
    sigma2 = model.slot("sigma2") ;
    sigmachain(s, 0) = sigma2[0] ;
    pi = model.slot("pi") ;
    pichain(s, _) = pi ;
    tau = model.slot("tau2") ;
    tauchain[s] = tau[0] ;
    mu = model.slot("mu") ;
    muchain[s] = mu[0] ;
  }
  //return logp_prec ;
  chains.slot("z") = Z ;
  chains.slot("nu.0") = nu0chain ;
  chains.slot("sigma2.0") = s20chain ;

  // update the following chains for debugging
  chains.slot("pi") = pichain ;
  chains.slot("sigma2") = sigmachain ;
  chains.slot("tau2") = tauchain ;
  chains.slot("mu") = muchain ;

  model.slot("mcmc.chains") = chains ;
  return model ;
}

// [[Rcpp::export]]
Rcpp::NumericVector p_sigma_reduced_pooled(Rcpp::S4 xmod) {
    RNGScope scope;
    
    // get model and accessories
    Rcpp::S4 model_(xmod);
    Rcpp::S4 model = clone(model_);
    Rcpp::S4 chains = model.slot("mcmc.chains");
    Rcpp::S4 params = model.slot("mcmc.params");
    Rcpp::List modes = model.slot("modes");

    // get modal ordinates
    Rcpp::NumericVector sigma2_ = Rcpp::as<Rcpp::NumericVector>(modes["sigma2"]);
    Rcpp::NumericVector theta_ = Rcpp::as<Rcpp::NumericVector>(modes["theta"]);
    Rcpp::NumericVector sigma2star = clone(sigma2_);
    Rcpp::NumericVector thetastar = clone(theta_);

    Rcpp::NumericVector x = model.slot("data");
    int n = x.size();
    int S = params.slot("iter");
    int K = thetastar.size();

    Rcpp::NumericVector prec(1);
    Rcpp::NumericVector p_prec(S);
    Rcpp::NumericVector tmp(K);
    Rcpp::NumericVector nu0(1);
    Rcpp::NumericVector s20(1);
    Rcpp::IntegerMatrix Z = chains.slot("z");
    Rcpp::IntegerVector zz;
    Rcpp::IntegerVector nn(K);
    Rcpp::NumericVector nu_n(K);

    //
    // We need to keep the Z|y,theta* chain
    //
    Rcpp::NumericVector nu0chain = chains.slot("nu.0");
    Rcpp::NumericVector s20chain = chains.slot("sigma2.0");

    Rcpp::NumericVector sigma2_n(1);
    Rcpp::NumericVector sigma2_new(1) ;    

    //
    // Run reduced Gibbs    -- theta is fixed at modal ordinate
    //
    prec = 1.0/sigma2star;
    Rcpp::NumericVector ss(1);
    
    for (int s = 0; s < S; ++s) {
      zz = Z(s, Rcpp::_);
      s20 = s20chain[s];
      nu0 = nu0chain[s];

      ss[0] = 0.0 ;
      for(int i = 0; i < n; i++) {
        int k = 0;
        while(k <= K) {
          if( zz[i] == (k + 1) ){
            ss[0] += pow(x[i] - thetastar[k], 2.0);
            break;
          }
          k++;
        }
      }
      nu_n = 0.5*(nu0 + double(n)) ;
      sigma2_n[0] = 1.0 / (0.5*(nu0[0] * s20[0] + ss[0])) ;
      sigma2_new = dgamma(prec, nu_n[0], sigma2_n[0]) ;
      p_prec[s] = sigma2_new[0] ;      
    }
    return p_prec;
}


// [[Rcpp::export]]
Rcpp::S4 reduced_pi_pooled(Rcpp::S4 xmod) {
  RNGScope scope ;
  Rcpp::S4 model_(xmod) ;
  Rcpp::S4 model = clone(model_) ;
  Rcpp::S4 params=model.slot("mcmc.params") ;
  Rcpp::S4 chains=model.slot("mcmc.chains") ;
  int S = params.slot("iter") ;
  List modes = model.slot("modes") ;
  NumericVector sigma2_ = as<NumericVector>(modes["sigma2"]) ;
  NumericVector theta_ = as<NumericVector>(modes["theta"]) ;
  NumericVector pi_ = as<NumericVector>(modes["mixprob"]) ;
  NumericVector sigma2star=clone(sigma2_) ;
  NumericVector thetastar=clone(theta_) ;
  NumericVector prec(1) ;
  NumericVector logp_prec(S) ;
  NumericVector y = model.slot("data") ;
  int N = y.size() ;
  //
  // We need to keep the Z|y,theta* chain
  //
  IntegerMatrix Z = chains.slot("z") ;
  NumericVector zz(N) ;
  model.slot("theta") = thetastar ;
  model.slot("sigma2") = sigma2star ;
  //
  // Run reduced Gibbs:
  //   -- theta is fixed at modal ordinate
  //   -- sigma2 is fixed at modal ordinate
  //  
  for(int s=0; s < S; ++s){
    zz = z_pooled(model) ;
    model.slot("z") = zz ;
    Z(s, _) = zz ;
    model.slot("data.mean") = compute_means(model) ;
    model.slot("data.prec") = compute_prec(model) ;
    // model.slot("theta") = theta_pooled(model) ; Do not update theta !
    // model.slot("sigma2") = sigma2_pooled(model) ;
    model.slot("pi") = update_p(model) ;
    model.slot("mu") = update_mu(model) ;
    model.slot("tau2") = update_tau2(model) ;
    model.slot("nu.0") = nu0_pooled(model) ;
    model.slot("sigma2.0") = sigma2_0_pooled(model) ;
  }
  chains.slot("z") = Z ;
  model.slot("mcmc.chains") = chains ;
  return model ;
}

// [[Rcpp::export]]
Rcpp::NumericVector p_pmix_reduced_pooled(Rcpp::S4 xmod) {
  RNGScope scope ;
  Rcpp::S4 model(xmod) ;
  Rcpp::S4 mcmcp = model.slot("mcmc.params") ;
  Rcpp::S4 chains = model.slot("mcmc.chains") ;
  Rcpp::S4 hypp = model.slot("hyperparams") ;
  List modes = model.slot("modes") ;
  //
  //
  NumericVector x = model.slot("data") ;    
  int K = hypp.slot("k") ;
  int S = mcmcp.slot("iter") ;  
  int N = x.size() ;
  //
  NumericVector p_=as<NumericVector>(modes["mixprob"]) ;
  NumericVector pstar = clone(p_) ;
  IntegerMatrix Z = chains.slot("z") ;
  NumericVector alpha = hypp.slot("alpha") ;
  NumericVector pmix(S) ;
  //
  // Run reduced Gibbs  -- theta,sigma2 fixed at modal ordinates
  //
  IntegerVector h(N) ;
  NumericVector alpha_n(K) ;
  NumericVector tmp(1) ;
  tmp[0] = 0 ;
  for(int s=0; s < S; ++s){
    h = Z(s, _ ) ;    
    for(int k = 0 ; k < K; ++k){
      alpha_n[k] = sum(h == k+1) + alpha[k] ;
    }
    tmp = log_ddirichlet_(pstar, alpha_n) ;
    pmix[s] = exp(tmp[0]) ;
  }
  return pmix ;
}

// [[Rcpp::export]]
Rcpp::S4 reduced_mu_pooled(Rcpp::S4 xmod) {
  RNGScope scope ;
  Rcpp::S4 model_(xmod) ;
  Rcpp::S4 model = clone(model_) ;
  Rcpp::S4 params=model.slot("mcmc.params") ;
  Rcpp::S4 chains=model.slot("mcmc.chains") ;
  int S = params.slot("iter") ;
  List modes = model.slot("modes") ;
  NumericVector sigma2_ = as<NumericVector>(modes["sigma2"]) ;
  NumericVector theta_ = as<NumericVector>(modes["theta"]) ;
  NumericVector pi_ = as<NumericVector>(modes["mixprob"]) ;
  NumericVector sigma2star=clone(sigma2_) ;
  NumericVector thetastar=clone(theta_) ;
  NumericVector pistar=clone(pi_) ;
  int K = thetastar.size() ;
  NumericVector prec(1) ;
  NumericVector logp_prec(S) ;
  NumericVector y = model.slot("data") ;
  NumericVector tau2chain(S) ;
  int N = y.size() ;
  //
  // We need to keep the Z|y,theta* chain
  //
  IntegerMatrix Z = chains.slot("z") ;
  IntegerVector zz(N) ;
  model.slot("theta") = thetastar ;
  model.slot("sigma2") = sigma2star ;
  model.slot("pi") = pistar ;

  // keep chains for debugging
  NumericVector nu0chain = chains.slot("nu.0") ;
  NumericVector s20chain = chains.slot("sigma2.0") ;
  NumericVector muchain = chains.slot("mu") ;
  NumericVector tauchain = chains.slot("tau2") ;
  NumericVector mu = model.slot("mu") ;
  NumericVector nu0 = model.slot("nu.0") ;
  NumericVector s20 = model.slot("sigma2.0") ;
  NumericVector tau2 = model.slot("tau2") ;  
  
  //
  // Run reduced Gibbs:
  //   -- theta is fixed at modal ordinate
  //   -- sigma2 is fixed at modal ordinate
  //  
  for(int s=0; s < S; ++s){
    zz = z_pooled(model) ;
    model.slot("z") = zz ;
    Z(s, _) = zz ;    
    model.slot("data.mean") = compute_means(model) ;
    model.slot("data.prec") = compute_prec(model) ;
    // model.slot("theta") = update_theta(model) ; Do not update theta !
    // model.slot("sigma2") = sigma2_pooled(model) ;
    // model.slot("pi") = update_p(model) ;
    mu = update_mu(model) ;
    tau2 = update_tau2(model) ;
    nu0 = nu0_pooled(model) ;
    s20 = sigma2_0_pooled(model) ;
    
    model.slot("mu") = mu ;
    model.slot("tau2") = tau2 ;
    model.slot("nu.0") = nu0 ;
    model.slot("sigma2.0") = s20 ;
    nu0chain[s] = nu0[0] ;
    s20chain[s] = s20[0] ;
    muchain[s] = mu[0] ;
    tau2chain[s] = tau2[0] ;
  }
  chains.slot("tau2") = tau2chain ;
  chains.slot("mu") = muchain ;
  chains.slot("nu.0") = nu0chain ;
  chains.slot("sigma2.0") = s20chain ;  
  chains.slot("z") = Z ;
  model.slot("mcmc.chains") = chains ;
  return model ;
}

// [[Rcpp::export]]
Rcpp::NumericVector p_mu_reduced_pooled(Rcpp::S4 xmod) {
  RNGScope scope ;
  Rcpp::S4 model(xmod) ;
  Rcpp::S4 mcmcp = model.slot("mcmc.params") ;
  Rcpp::S4 chains = model.slot("mcmc.chains") ;
  Rcpp::S4 hypp = model.slot("hyperparams") ;
  List modes = model.slot("modes") ;
  //
  //
  NumericVector x = model.slot("data") ;    
  int K = hypp.slot("k") ;
  int S = mcmcp.slot("iter") ;  
  int N = x.size() ;
  //
  NumericVector p_=as<NumericVector>(modes["mixprob"]) ;
  NumericVector theta_=as<NumericVector>(modes["theta"]) ;
  NumericVector mu_=as<NumericVector>(modes["mu"]) ;
  NumericVector pstar = clone(p_) ;
  NumericVector mustar = clone(mu_) ;
  NumericVector thetastar = clone(theta_) ;
  IntegerMatrix Z = chains.slot("z") ;
  NumericVector tau2chain = chains.slot("tau2") ;
  IntegerVector zz(N) ;

  IntegerVector nn(K) ;
  NumericVector mu0=hypp.slot("mu.0") ;
  double mu_0 = mu0[0] ;
  NumericVector tau2_0 = hypp.slot("tau2.0") ;
  double tau20_tilde = 1.0/tau2_0[0] ;

  double mu_k ;
  NumericVector tau2_tilde = 1.0/tau2chain ;
  double w1 ;
  double w2 ;
  double tau_k ;
  NumericVector p_mu(S) ;
  NumericVector tmp(1) ;
  for(int s = 0; s < S; ++s){
    zz = Z(s, _) ;
    nn = tableZ(K, zz) ;
    double total = 0.0 ;
    double thetabar = 0.0 ;    
    for(int k = 0; k < K; k++) total += nn[k] ;    
    for(int k = 0; k < K; k++) thetabar += nn[k] * thetastar[k] / total ;
    double post_prec = tau20_tilde + K*tau2_tilde[s] ;
    w1 = tau20_tilde/post_prec ;
    w2 = K*tau2_tilde[s]/post_prec ;
    mu_k =  w1*mu_0 +  w2*thetabar ;
    tau_k = sqrt(1.0/post_prec) ;
    tmp  = dnorm(mustar, mu_k, tau_k) ;
    p_mu[s] = tmp[0] ;
  }
  return p_mu ;
}


// [[Rcpp::export]]
Rcpp::S4 reduced_tau_pooled(Rcpp::S4 xmod) {
  RNGScope scope ;
  Rcpp::S4 model_(xmod) ;
  Rcpp::S4 model = clone(model_) ;
  Rcpp::S4 params=model.slot("mcmc.params") ;
  Rcpp::S4 chains=model.slot("mcmc.chains") ;
  int S = params.slot("iter") ;
  List modes = model.slot("modes") ;
  NumericVector sigma2_ = as<NumericVector>(modes["sigma2"]) ;
  NumericVector theta_ = as<NumericVector>(modes["theta"]) ;
  NumericVector pi_ = as<NumericVector>(modes["mixprob"]) ;
  NumericVector mu_ = as<NumericVector>(modes["mu"]) ;
  NumericVector sigma2star=clone(sigma2_) ;
  NumericVector thetastar=clone(theta_) ;
  NumericVector pistar=clone(pi_) ;
  NumericVector mustar=clone(mu_) ;
  int K = thetastar.size() ;
  NumericVector prec(1) ;
  NumericVector logp_prec(S) ;
  NumericVector tmp(K) ;
  NumericVector y = model.slot("data") ;
  //NumericVector s20chain(S) ;
  int N = y.size() ;
  //
  // We need to keep the Z|y,theta* chain
  //
  IntegerMatrix Z = chains.slot("z") ;
  IntegerVector zz(N) ;
  model.slot("theta") = thetastar ;
  model.slot("sigma2") = sigma2star ;
  model.slot("pi") = pistar ;
  model.slot("mu") = mustar ;
  //
  // Run reduced Gibbs:
  //   -- theta is fixed at modal ordinate
  //   -- sigma2 is fixed at modal ordinate
  //  
  for(int s=0; s < S; ++s){
    zz = z_pooled(model) ;
    model.slot("z") = zz ;
    Z(s, _) = zz ;    
    model.slot("data.mean") = compute_means(model) ;
    model.slot("data.prec") = compute_prec(model) ;
    // model.slot("theta") = update_theta(model) ; Do not update theta !
    // model.slot("sigma2") = sigma2_pooled(model) ;
    // model.slot("pi") = update_p(model) ;
    // model.slot("mu") = update_mu(model) ;
    model.slot("tau2") = update_tau2(model) ;
    model.slot("nu.0") = nu0_pooled(model) ;
    model.slot("sigma2.0") = sigma2_0_pooled(model) ;
    //s20chain[s] = model.slot("sigma2.0") ;
  }
  chains.slot("z") = Z ;
  model.slot("mcmc.chains") = chains ;
  return model ;
}


// [[Rcpp::export]]
Rcpp::NumericVector p_tau_reduced_pooled(Rcpp::S4 xmod) {
  RNGScope scope ;
  Rcpp::S4 model(xmod) ;
  Rcpp::S4 mcmcp = model.slot("mcmc.params") ;
  Rcpp::S4 chains = model.slot("mcmc.chains") ;
  Rcpp::S4 hypp = model.slot("hyperparams") ;
  List modes = model.slot("modes") ;
  //
  //
  NumericVector x = model.slot("data") ;    
  int K = hypp.slot("k") ;
  int S = mcmcp.slot("iter") ;  
  int N = x.size() ;
  //
  NumericVector p_=as<NumericVector>(modes["mixprob"]) ;
  NumericVector theta_=as<NumericVector>(modes["theta"]) ;
  NumericVector mu_=as<NumericVector>(modes["mu"]) ;
  NumericVector tau2_=as<NumericVector>(modes["tau2"]) ;
  NumericVector pstar = clone(p_) ;
  NumericVector mustar = clone(mu_) ;
  NumericVector tau2star = clone(tau2_) ;
  NumericVector thetastar = clone(theta_) ;
  IntegerMatrix Z = chains.slot("z") ;
  IntegerVector zz(N) ;
  NumericVector p_tau(S) ;

  double m2_0 = hypp.slot("m2.0") ;
  double eta_0 = hypp.slot("eta.0") ;
  double eta_k = eta_0 + K ;
  NumericVector s2_k(1) ;
  for(int k = 0; k < K; k++) s2_k[0] += pow(thetastar[k] - mustar[0], 2.0) ;
  NumericVector m2_k(1) ;
  m2_k[0] = 1/eta_k * (eta_0 * m2_0 + s2_k[0]) ;
  p_tau = dgamma(1.0/tau2star, 0.5 * eta_k, 1.0/(0.5 * eta_k * m2_k[0])) ;
  return p_tau ;
}

// [[Rcpp::export]]
Rcpp::S4 reduced_nu0_pooled(Rcpp::S4 xmod) {
  RNGScope scope ;
  Rcpp::S4 model_(xmod) ;
  Rcpp::S4 model = clone(model_) ;
  Rcpp::S4 params=model.slot("mcmc.params") ;
  Rcpp::S4 chains=model.slot("mcmc.chains") ;
  int S = params.slot("iter") ;
  List modes = model.slot("modes") ;
  NumericVector sigma2_ = as<NumericVector>(modes["sigma2"]) ;
  NumericVector theta_ = as<NumericVector>(modes["theta"]) ;
  NumericVector pi_ = as<NumericVector>(modes["mixprob"]) ;
  NumericVector mu_ = as<NumericVector>(modes["mu"]) ;
  NumericVector tau2_ = as<NumericVector>(modes["tau2"]) ;
  NumericVector sigma2star=clone(sigma2_) ;
  NumericVector thetastar=clone(theta_) ;
  NumericVector pistar=clone(pi_) ;
  NumericVector mustar=clone(mu_) ;
  NumericVector tau2star=clone(tau2_) ;
  int K = thetastar.size() ;
  NumericVector prec(K) ;
  NumericVector logp_prec(S) ;
  NumericVector tmp(K) ;
  NumericVector y = model.slot("data") ;
  NumericVector s20chain(S) ;
  int N = y.size() ;
  //
  // We need to keep the Z|y,theta* chain
  //
  IntegerMatrix Z = chains.slot("z") ;
  IntegerVector zz(N) ;
  model.slot("theta") = thetastar ;
  model.slot("sigma2") = sigma2star ;
  model.slot("pi") = pistar ;
  model.slot("mu") = mustar ;
  model.slot("tau2") = tau2star ;

  for(int s=0; s < S; ++s){
    zz = z_pooled(model) ;
    model.slot("z") = zz ;
    Z(s, _) = zz ;    
    model.slot("data.mean") = compute_means(model) ;
    model.slot("data.prec") = compute_prec(model) ;
    // model.slot("theta") = update_theta(model) ; Do not update theta !
    // model.slot("sigma2") = sigma2_pooled(model) ;
    // model.slot("pi") = update_p(model) ;
    // model.slot("mu") = update_mu(model) ;
    // model.slot("tau2") = update_tau2(model) ;
    model.slot("nu.0") = nu0_pooled(model) ;
    model.slot("sigma2.0") = sigma2_0_pooled(model) ;
    s20chain[s] = model.slot("sigma2.0") ;
  }
  chains.slot("z") = Z ;
  chains.slot("sigma2.0") = s20chain ;
  model.slot("mcmc.chains") = chains ;
  return model ;
}

// [[Rcpp::export]]
Rcpp::NumericVector p_nu0_reduced_pooled(Rcpp::S4 xmod) {
  RNGScope scope ;
  Rcpp::S4 model(xmod) ;
  Rcpp::S4 mcmcp = model.slot("mcmc.params") ;
  Rcpp::S4 chains = model.slot("mcmc.chains") ;
  Rcpp::S4 hypp = model.slot("hyperparams") ;
  List modes = model.slot("modes") ;
  //
  //
  NumericVector x = model.slot("data") ;    
  int K = hypp.slot("k") ;
  int S = mcmcp.slot("iter") ;  
  int N = x.size() ;
  //
  NumericVector p_=as<NumericVector>(modes["mixprob"]) ;
  NumericVector theta_=as<NumericVector>(modes["theta"]) ;
  NumericVector mu_=as<NumericVector>(modes["mu"]) ;
  NumericVector tau2_=as<NumericVector>(modes["tau2"]) ;
  IntegerVector nu0_=as<IntegerVector>(modes["nu0"]) ;
  NumericVector sigma2_=as<NumericVector>(modes["sigma2"]) ;
  NumericVector pstar = clone(p_) ;
  NumericVector mustar = clone(mu_) ;
  NumericVector tau2star = clone(tau2_) ;
  NumericVector thetastar = clone(theta_) ;
  NumericVector sigma2star = clone(sigma2_) ;
  IntegerVector nu0=clone(nu0_) ;
  NumericVector p_nu0(S) ;
  int nu0star = nu0[0] ;

  NumericVector s20chain = chains.slot("sigma2.0") ;
  double betas = hypp.slot("beta") ;

  //
  // compute p(nu0*, ) from *normalized* probabilities
  //
  NumericVector d(100) ;  // 100 is the maximum allowed value for nu_0
  NumericVector lpnu0(100);
  double prec = 1.0/sigma2star[0] ;
  double lprec = log(prec) ;
  d = seq_len(100) ;
  NumericVector y1(100) ;
  NumericVector y2(100) ;
  NumericVector y3(100) ;
  for(int s = 0; s < S; ++s) {
    y1 = K*(0.5*d*log(s20chain[s]*0.5*d) - lgamma(d*0.5)) ;
    y2 = (0.5*d - 1.0) * lprec ;
    y3 = d*(betas + 0.5*s20chain[s]*prec) ;
    lpnu0 =  y1 + y2 - y3 ;
    NumericVector prob(100) ;
    prob = exp(lpnu0) ; // - maxprob) ;
    prob = prob/sum(prob) ;  // this is now normalized
    p_nu0[s] = prob[nu0star] ;
  }
  return p_nu0 ;
}

// [[Rcpp::export]]
Rcpp::S4 reduced_s20_pooled(Rcpp::S4 xmod) {
  RNGScope scope ;
  Rcpp::S4 model_(xmod) ;
  Rcpp::S4 model = clone(model_) ;
  Rcpp::S4 params=model.slot("mcmc.params") ;
  Rcpp::S4 chains=model.slot("mcmc.chains") ;
  int S = params.slot("iter") ;
  List modes = model.slot("modes") ;
  NumericVector sigma2_ = as<NumericVector>(modes["sigma2"]) ;
  NumericVector theta_ = as<NumericVector>(modes["theta"]) ;
  NumericVector pi_ = as<NumericVector>(modes["mixprob"]) ;
  NumericVector mu_ = as<NumericVector>(modes["mu"]) ;
  NumericVector tau2_ = as<NumericVector>(modes["tau2"]) ;
  IntegerVector nu0_ = as<IntegerVector>(modes["nu0"]) ;
  NumericVector sigma2star=clone(sigma2_) ;
  NumericVector thetastar=clone(theta_) ;
  NumericVector pistar=clone(pi_) ;
  NumericVector mustar=clone(mu_) ;
  NumericVector tau2star=clone(tau2_) ;
  IntegerVector nu0star=clone(nu0_) ;
  int K = thetastar.size() ;
  NumericVector y = model.slot("data") ;
  int N = y.size() ;
  //
  // We need to keep the Z|y,theta* chain
  //
  IntegerMatrix Z = chains.slot("z") ;
  IntegerVector zz(N) ;
  model.slot("theta") = thetastar ;
  model.slot("sigma2") = sigma2star ;
  model.slot("pi") = pistar ;
  model.slot("mu") = mustar ;
  model.slot("tau2") = tau2star ;
  model.slot("nu.0") = nu0star ;

  for(int s=0; s < S; ++s){
    zz = z_pooled(model) ;
    model.slot("z") = zz ;
    Z(s, _) = zz ;    
    model.slot("data.mean") = compute_means(model) ;
    model.slot("data.prec") = compute_prec(model) ;
    // model.slot("theta") = update_theta(model) ; Do not update theta !
    // model.slot("sigma2") = sigma2_pooled(model) ;
    // model.slot("pi") = update_p(model) ;
    // model.slot("mu") = update_mu(model) ;
    // model.slot("tau2") = update_tau2(model) ;
    // model.slot("nu.0") = nu0_pooled(model) ;
    model.slot("sigma2.0") = sigma2_0_pooled(model) ;
  }
  chains.slot("z") = Z ;
  model.slot("mcmc.chains") = chains ;
  return model ;
}

// [[Rcpp::export]]
Rcpp::NumericVector p_s20_reduced_pooled(Rcpp::S4 xmod) {
  RNGScope scope ;
  Rcpp::S4 model(xmod) ;
  Rcpp::S4 mcmcp = model.slot("mcmc.params") ;
  Rcpp::S4 chains = model.slot("mcmc.chains") ;
  Rcpp::S4 hypp = model.slot("hyperparams") ;
  List modes = model.slot("modes") ;
  //
  //
  NumericVector x = model.slot("data") ;    
  int K = hypp.slot("k") ;
  //
  NumericVector p_=as<NumericVector>(modes["mixprob"]) ;
  NumericVector theta_=as<NumericVector>(modes["theta"]) ;
  NumericVector mu_=as<NumericVector>(modes["mu"]) ;
  NumericVector tau2_=as<NumericVector>(modes["tau2"]) ;
  NumericVector nu0_=as<NumericVector>(modes["nu0"]) ;
  NumericVector sigma2_=as<NumericVector>(modes["sigma2"]) ;
  NumericVector s20_=as<NumericVector>(modes["sigma2.0"]) ;
  NumericVector pstar = clone(p_) ;
  NumericVector mustar = clone(mu_) ;
  NumericVector tau2star = clone(tau2_) ;
  NumericVector thetastar = clone(theta_) ;
  NumericVector sigma2star = clone(sigma2_) ;
  NumericVector s20star = clone(s20_) ;
  NumericVector nu0=clone(nu0_) ;
  double nu0star = nu0[0] ;
  NumericVector p_s20(1) ;
  
  double a = hypp.slot("a") ;
  double b = hypp.slot("b") ;  
  double a_k = a + 0.5*K*nu0star ;
  double b_k = b + 0.5 * nu0star/sigma2star[0];
  p_s20 = dgamma(s20star, a_k, 1.0/b_k) ;
  return p_s20 ;
}

