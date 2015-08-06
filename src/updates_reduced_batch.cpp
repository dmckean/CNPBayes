#include "miscfunctions.h" // for rdirichlet, tableZ, ...
#include "updates_batch.h"
#include <Rcpp.h>

Rcpp::NumericMatrix toMatrix(Rcpp::NumericVector x, int NR, int NC) {
    Rcpp::NumericMatrix Y(NR, NC);
    int iter = 0;
    for(int j = 0; j < NC; ++j) {
        for(int i = 0; i < NR; ++i) {
            Y(i, j) = x[iter];
            iter++;
        }
    }
    return Y;
}

// [[Rcpp::export]]
Rcpp::NumericVector marginal_theta_batch(Rcpp::S4 xmod) {
    Rcpp::RNGScope scope;
    Rcpp::S4 model_(xmod);
    Rcpp::S4 model = clone(model_);
    Rcpp::S4 params=model.slot("mcmc.params");
    Rcpp::S4 chains(model.slot("mcmc.chains")); 
    int S = params.slot("iter");
    Rcpp::List modes = model.slot("modes");
    Rcpp::NumericMatrix theta_ = Rcpp::as<Rcpp::NumericMatrix>(modes["theta"]);
    Rcpp::NumericMatrix thetastar=clone(theta_);
    int K = thetastar.ncol();
    Rcpp::NumericVector p_theta(S);
    Rcpp::NumericMatrix muc = chains.slot("mu");
    Rcpp::NumericMatrix tau2c = chains.slot("tau2");
    Rcpp::NumericMatrix sigma2 = chains.slot("sigma2");
    int B = thetastar.nrow();
    Rcpp::NumericVector tmp(1);

    Rcpp::IntegerMatrix Z = chains.slot("z");
    Rcpp::IntegerVector zz;

    Rcpp::NumericVector tau2_tilde(K);
    Rcpp::NumericVector sigma2_tilde(K);

    // this should be updated for each iteration
    Rcpp::NumericMatrix data_mean(B,K);
    Rcpp::IntegerVector nn(K);
    double post_prec;
    double tau_n;
    double mu_n;
    double w1;
    double w2;
    Rcpp::NumericVector tauc(K);
    Rcpp::NumericMatrix iSigma2(B,K);
    Rcpp::NumericVector invs2;
    Rcpp::NumericVector theta(1);

    for(int s=0; s < S; ++s) {
        tauc = sqrt(tau2c(s, Rcpp::_));
        zz = Z(s, Rcpp::_);
        model.slot("z") = zz;
        nn = tableZ(K, zz);
        data_mean = compute_means_batch(model);
        tau2_tilde = 1/tau2c(s, Rcpp::_);
        invs2 = 1.0/sigma2(s, Rcpp::_) ;    // this is a vector of length B*K
        sigma2_tilde = Rcpp::as<Rcpp::NumericVector>(toMatrix(invs2, B, K));
        double prod = 1.0;

        for(int k = 0; k < K; ++k) {
            for(int b = 0; b < B; ++b){
                post_prec = tau2_tilde[k] + sigma2_tilde(b, k) * nn[k];
                tau_n = sqrt(1/post_prec);
                w1 = tau2_tilde[k]/post_prec;
                w2 = nn[k] * sigma2_tilde(b, k)/post_prec;
                mu_n = w1*muc(s, k) + w2*data_mean(b, k);
                theta = thetastar(b, k);
                tmp = dnorm(theta, mu_n, tau_n);
                prod = prod * tmp[0];
            }
        }

        p_theta[s] = prod;
    }

    return p_theta;
}

// [[Rcpp::export]]
Rcpp::NumericVector p_theta_zpermuted_batch(Rcpp::S4 xmod) {
    Rcpp::RNGScope scope;
    Rcpp::S4 model_(xmod);
    Rcpp::S4 model = clone(model_);
    Rcpp::S4 mcmcp = model.slot("mcmc.params");
    //Rcpp::S4 params(mcmcp);
    int S = mcmcp.slot("iter");
    Rcpp::List modes = model.slot("modes");
    Rcpp::NumericMatrix sigma2_ = Rcpp::as<Rcpp::NumericMatrix>(modes["sigma2"]);
    Rcpp::NumericMatrix theta_ = Rcpp::as<Rcpp::NumericMatrix>(modes["theta"]);
    Rcpp::NumericMatrix sigma2star=clone(sigma2_);
    Rcpp::NumericMatrix thetastar=clone(theta_);
    int K = thetastar.ncol();
    int B = thetastar.nrow();
    Rcpp::NumericVector logp_theta(S);
    Rcpp::S4 chains(model.slot("mcmc.chains"));
    double mu;
    Rcpp::NumericVector tau(1);
    Rcpp::NumericVector tmp(K);
    Rcpp::IntegerMatrix Z = chains.slot("z");
    int N = Z.ncol();
    Rcpp::IntegerVector h (N);
    Rcpp::NumericVector tau2(1);
    for(int s=0; s < S; ++s){
        h = Z(s, Rcpp::_ );
        model.slot("z") = h;
        model.slot("data.mean") = compute_means_batch(model);
        model.slot("data.prec") = compute_prec_batch(model);
        model.slot("theta") = update_theta_batch(model);
        model.slot("sigma2") = update_sigma2_batch(model);
        model.slot("pi") = update_p_batch(model);
        model.slot("mu") = update_mu_batch(model);
        model.slot("tau2") = update_tau2_batch(model);
        model.slot("nu.0") = update_nu0_batch(model);
        model.slot("sigma2.0") = update_sigma20_batch(model);
        mu = model.slot("mu");
        tau2 = model.slot("tau2");
        tau = sqrt(tau2);
        tmp = dnorm(thetastar, mu, tau[0]);
        double prod = 0.0;
        for(int k = 0; k < K; ++k) {
            prod += log(tmp[k]);
        }
        logp_theta[s] = prod;
    }
    return logp_theta;
}

Rcpp::NumericVector marginal_sigma2_batch(Rcpp::S4 xmod, Rcpp::S4 mcmcp) {
    Rcpp::RNGScope scope;
    Rcpp::S4 model_(xmod);
    Rcpp::S4 model = clone(model_) ;    
    Rcpp::S4 params(mcmcp);
    int S = params.slot("iter");
    // Assume current values are the modes (in R, useModes(object) ensures this)
    Rcpp::List modes = model.slot("modes");
    Rcpp::NumericVector sigma2_ = Rcpp::as<Rcpp::NumericVector>(modes["sigma2"]);
    Rcpp::NumericVector theta_ = Rcpp::as<Rcpp::NumericVector>(modes["theta"]);
    //NumericVector sigma2_ = model.slot("sigma2");
    Rcpp::NumericVector sigma2star = clone(sigma2_);
    Rcpp::NumericVector thetastar = clone(theta_);
    Rcpp::NumericVector prec = pow(sigma2star, -1.0);
    int K = prec.size();
    Rcpp::NumericVector logp_prec(S);
    //
    // Run reduced Gibbs    -- theta is fixed at modal ordinate
    //
    Rcpp::S4 chains(model.slot("mcmc.chains"));
    Rcpp::NumericVector tmp(K);
    Rcpp::NumericVector nu0 = chains.slot("nu.0");
    Rcpp::NumericVector s20 = chains.slot("sigma2.0");
    for(int s=0; s < S; ++s){
        model.slot("z") = update_z_batch(model);
        model.slot("data.mean") = compute_means_batch(model);
        model.slot("data.prec") = compute_prec_batch(model);
        // model.slot("theta") = update_theta(model) ;  Do not update theta!
        model.slot("sigma2") = update_sigma2_batch(model);
        model.slot("pi") = update_p_batch(model);
        model.slot("mu") = update_mu_batch(model);
        model.slot("tau2") = update_tau2_batch(model);
        model.slot("nu.0") = update_nu0_batch(model);
        model.slot("sigma2.0") = update_sigma20_batch(model);
        nu0 = model.slot("nu.0");
        s20 = model.slot("sigma2.0");
        tmp = dgamma(prec, 0.5*nu0[0], 2.0 / (nu0[0]*s20[0]));
        double total = 0.0;
        for(int k = 0; k < K; ++k){
            total += log(tmp[k]);
        }
        logp_prec[s] = total;
    }
    return logp_prec;
}

// [[Rcpp::export]]
Rcpp::S4 simulate_z_reduced1_batch(Rcpp::S4 object) {
    Rcpp::RNGScope scope;
    Rcpp::S4 model_(object);
    Rcpp::S4 model = clone(model_);
    Rcpp::S4 params=model.slot("mcmc.params");
    Rcpp::S4 chains=model.slot("mcmc.chains");
    int S = params.slot("iter");
    Rcpp::List modes = model.slot("modes");
    Rcpp::NumericVector sigma2_ = Rcpp::as<Rcpp::NumericVector>(modes["sigma2"]);
    Rcpp::NumericVector theta_ = Rcpp::as<Rcpp::NumericVector>(modes["theta"]);
    Rcpp::NumericVector sigma2star=clone(sigma2_);
    Rcpp::NumericVector thetastar=clone(theta_);
    int K = thetastar.size();
    Rcpp::NumericVector prec(K);
    Rcpp::NumericVector logp_prec(S);
    Rcpp::NumericVector tmp(K);
    Rcpp::NumericVector y = model.slot("data");
    int N = y.size();
    Rcpp::NumericVector tau2(1);
    Rcpp::NumericVector nu0 (1);
    Rcpp::NumericVector s20 (1);
    Rcpp::NumericVector s2 (1);
    //
    // We need to keep the Z|y,theta* chain
    //
    Rcpp::IntegerMatrix Z = chains.slot("z");
    Rcpp::NumericVector nu0chain = chains.slot("nu.0");
    Rcpp::NumericVector s20chain = chains.slot("sigma2.0");
    Rcpp::IntegerVector h(N);
    model.slot("theta") = thetastar;
    //
    // Run reduced Gibbs    -- theta is fixed at modal ordinate
    //  
    for(int s=0; s < S; ++s){
        model.slot("z") = update_z(model);
        model.slot("data.mean") = compute_means(model);
        model.slot("data.prec") = compute_prec(model);
        //model.slot("theta") = update_theta(model) ; Do not update theta !
        model.slot("sigma2") = update_sigma2(model);
        model.slot("pi") = update_p(model);
        model.slot("mu") = update_mu(model);
        model.slot("tau2") = update_tau2(model);
        model.slot("nu.0") = update_nu0(model);
        model.slot("sigma2.0") = update_sigma2_0(model);
        nu0chain[s] = model.slot("nu.0");
        s20chain[s] = model.slot("sigma2.0");
        h = model.slot("z");
        Z(s, Rcpp::_) = h;
    }
    //return logp_prec;
    chains.slot("z") = Z;
    chains.slot("nu.0") = nu0chain;
    chains.slot("sigma2.0") = s20chain;
    model.slot("mcmc.chains") = chains;
    //return logp_prec;
    return model;
}

// [[Rcpp::export]]
Rcpp::S4 simulate_z_reduced2_batch(Rcpp::S4 object) {
    RNGScope scope ;
    Rcpp::S4 model_(object) ;
    Rcpp::S4 model = clone(model_) ;
    Rcpp::S4 params=model.slot("mcmc.params") ;
    Rcpp::S4 chains=model.slot("mcmc.chains") ;
    int S = params.slot("iter") ;
    List modes = model.slot("modes") ;
    NumericVector sigma2_ = as<NumericVector>(modes["sigma2"]) ;
    NumericVector theta_ = as<NumericVector>(modes["theta"]) ;
    NumericVector sigma2star=clone(sigma2_) ;
    NumericVector thetastar=clone(theta_) ;
    int K = thetastar.size() ;
    NumericVector prec(K) ;
    NumericVector logp_prec(S) ;
    NumericVector tmp(K) ;
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
    IntegerVector h(N) ;
    model.slot("theta") = thetastar ;
    model.slot("sigma2") = sigma2star ;  
    //
    // Run reduced Gibbs:
    //   -- theta is fixed at modal ordinate
    //   -- sigma2 is fixed at modal ordinate
    for(int s=0; s < S; ++s){
        model.slot("z") = update_z(model) ;
        model.slot("data.mean") = compute_means(model) ;
        model.slot("data.prec") = compute_prec(model) ;
        // model.slot("theta") = update_theta(model) ; Do not update theta !
        // model.slot("sigma2") = update_sigma2(model) ;
        model.slot("pi") = update_p(model) ;
        model.slot("mu") = update_mu(model) ;
        model.slot("tau2") = update_tau2(model) ;
        model.slot("nu.0") = update_nu0(model) ;
        model.slot("sigma2.0") = update_sigma2_0(model) ;
        h = model.slot("z") ;
        Z(s, _) = h ;
    }
    //return logp_prec ;
    chains.slot("z") = Z ;
    // chains.slot("nu.0") = nu0chain ;
    // chains.slot("sigma2.0") = s20chain ;
    model.slot("mcmc.chains") = chains ;
    //return logp_prec ;
    return model ;
}

// [[Rcpp::export]]
Rcpp::S4 permutedz_reduced1_batch(Rcpp::S4 xmod) {
    RNGScope scope ;
    Rcpp::S4 model_(xmod) ;
    Rcpp::S4 model = clone(model_) ;
    Rcpp::S4 params=model.slot("mcmc.params") ;
    Rcpp::S4 chains=model.slot("mcmc.chains") ;
    int S = params.slot("iter") ;
    List modes = model.slot("modes") ;
    NumericVector sigma2_ = as<NumericVector>(modes["sigma2"]) ;
    NumericVector theta_ = as<NumericVector>(modes["theta"]) ;
    NumericVector sigma2star=clone(sigma2_) ;
    NumericVector thetastar=clone(theta_) ;
    int K = thetastar.size() ;
    NumericVector prec(K) ;
    NumericVector logp_prec(S) ;
    NumericVector tmp(K) ;
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
    IntegerVector h(N) ;
    model.slot("theta") = thetastar ;
    //
    // Run reduced Gibbs    -- theta is fixed at modal ordinate
    //  
    for(int s=0; s < S; ++s){
        h = Z(s, _) ;
        //model.slot("z") = update_z(xmod) ;
        model.slot("z") = h ;
        model.slot("data.mean") = compute_means(model) ;
        model.slot("data.prec") = compute_prec(model) ;
        //model.slot("theta") = update_theta(model) ; Do not update theta !
        model.slot("sigma2") = update_sigma2(model) ;
        model.slot("pi") = update_p(model) ;
        model.slot("mu") = update_mu(model) ;
        model.slot("tau2") = update_tau2(model) ;
        model.slot("nu.0") = update_nu0(model) ;
        model.slot("sigma2.0") = update_sigma2_0(model) ;
        nu0chain[s] = model.slot("nu.0") ;
        s20chain[s] = model.slot("sigma2.0") ;
    }
    //return logp_prec ;
    // chains.slot("z") = Z ;
    chains.slot("nu.0") = nu0chain ;
    chains.slot("sigma2.0") = s20chain ;
    model.slot("mcmc.chains") = chains ;
    //return logp_prec ;
    return model ;
}


// [[Rcpp::export]]
Rcpp::S4 permutedz_reduced2_batch(Rcpp::S4 xmod) {
    RNGScope scope ;
    Rcpp::S4 model_(xmod) ;
    Rcpp::S4 model = clone(model_) ;
    Rcpp::S4 params=model.slot("mcmc.params") ;
    Rcpp::S4 chains=model.slot("mcmc.chains") ;
    int S = params.slot("iter") ;
    List modes = model.slot("modes") ;
    NumericVector sigma2_ = as<NumericVector>(modes["sigma2"]) ;
    NumericVector theta_ = as<NumericVector>(modes["theta"]) ;
    NumericVector sigma2star=clone(sigma2_) ;
    NumericVector thetastar=clone(theta_) ;
    int K = thetastar.size() ;
    NumericVector prec(K) ;
    NumericVector logp_prec(S) ;
    NumericVector tmp(K) ;
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
    IntegerVector h(N) ;
    model.slot("theta") = thetastar ;
    //
    // Run reduced Gibbs:
    //   -- theta is fixed at modal ordinate
    //   -- sigma2 is fixed at modal ordinate
    //  
    for(int s=0; s < S; ++s){
        h = Z(s, _) ;
        //model.slot("z") = update_z(xmod) ;
        model.slot("z") = h ;
        model.slot("data.mean") = compute_means(model) ;
        model.slot("data.prec") = compute_prec(model) ;
        // model.slot("theta") = update_theta(model) ; Do not update theta !
        // model.slot("sigma2") = update_sigma2(model) ;
        model.slot("pi") = update_p(model) ;
        model.slot("mu") = update_mu(model) ;
        model.slot("tau2") = update_tau2(model) ;
        model.slot("nu.0") = update_nu0(model) ;
        model.slot("sigma2.0") = update_sigma2_0(model) ;
        nu0chain[s] = model.slot("nu.0") ;
        s20chain[s] = model.slot("sigma2.0") ;
    }
    //return logp_prec ;
    // chains.slot("z") = Z ;
    chains.slot("nu.0") = nu0chain ;
    chains.slot("sigma2.0") = s20chain ;
    model.slot("mcmc.chains") = chains ;
    //return logp_prec ;
    return model ;
}


// [[Rcpp::export]]
Rcpp::NumericVector p_pmix_reduced_batch(Rcpp::S4 xmod) {
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
    NumericMatrix Z = chains.slot("z") ;
    NumericVector alpha = hypp.slot("alpha") ;
    NumericVector pmix(S) ;
    //
    // Run reduced Gibbs    -- theta,sigma2 fixed at modal ordinates
    //
    NumericVector h(N) ;
    NumericVector alpha_n(K) ;
    NumericVector tmp(1) ;
    for(int s=0; s < S; ++s){
        h = Z(s, _ ) ;      
        for(int k = 0 ; k < K; ++k){
            alpha_n[k] = sum(h == k+1) + alpha[k] ;
        }
        tmp = log_ddirichlet_(pstar, alpha_n) ;
        pmix[s] = exp(tmp[0]) ;
    }
    // return tmp ;
    return pmix ;
}


// [[Rcpp::export]]
Rcpp::S4 reduced_sigma_batch(Rcpp::S4 xmod) {
    RNGScope scope ;
    Rcpp::S4 model_(xmod) ;
    Rcpp::S4 model = clone(model_) ;
    Rcpp::S4 params=model.slot("mcmc.params") ;
    Rcpp::S4 chains=model.slot("mcmc.chains") ;
    int S = params.slot("iter") ;
    List modes = model.slot("modes") ;
    NumericVector sigma2_ = as<NumericVector>(modes["sigma2"]) ;
    NumericVector theta_ = as<NumericVector>(modes["theta"]) ;
    NumericVector sigma2star=clone(sigma2_) ;
    NumericVector thetastar=clone(theta_) ;
    int K = thetastar.size() ;
    NumericVector prec(K) ;
    NumericVector logp_prec(S) ;
    NumericVector tmp(K) ;
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

    
    IntegerVector h(N) ;
    model.slot("theta") = thetastar ;
    IntegerVector zz ;
    //
    // Run reduced Gibbs    -- theta is fixed at modal ordinate
    //  
    for(int s=0; s < S; ++s){
        zz = update_z(model) ;
        model.slot("z") = zz ;
        Z(s, _) = zz ;
        model.slot("data.mean") = compute_means(model) ;
        model.slot("data.prec") = compute_prec(model) ;
        //model.slot("theta") = update_theta(model) ; Do not update theta !
        model.slot("sigma2") = update_sigma2(model) ;
        model.slot("pi") = update_p(model) ;
        model.slot("mu") = update_mu(model) ;
        model.slot("tau2") = update_tau2(model) ;
        model.slot("nu.0") = update_nu0(model) ;
        model.slot("sigma2.0") = update_sigma2_0(model) ;
        nu0chain[s] = model.slot("nu.0") ;
        s20chain[s] = model.slot("sigma2.0") ;
        // update the following chains for debugging small sigma2.0 values
        sigma2 = model.slot("sigma2") ;
        sigmachain(s, _) = sigma2 ;
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
    //return logp_prec ;
    return model ;
}

// [[Rcpp::export]]
Rcpp::NumericVector p_sigma_reduced_batch(Rcpp::S4 xmod) {
    RNGScope scope ;
    Rcpp::S4 model_(xmod) ;
    Rcpp::S4 model = clone(model_) ;
    Rcpp::S4 chains=model.slot("mcmc.chains") ;
    Rcpp::S4 params=model.slot("mcmc.params") ;
    NumericVector x = model.slot("data") ;
    int n = x.size() ;
    int S = params.slot("iter") ;
    List modes = model.slot("modes") ;
    NumericVector sigma2_ = as<NumericVector>(modes["sigma2"]) ;
    NumericVector theta_ = as<NumericVector>(modes["theta"]) ;
    NumericVector sigma2star=clone(sigma2_) ;
    NumericVector thetastar=clone(theta_) ;
    int K = thetastar.size() ;
    NumericVector prec(K) ;
    NumericVector p_prec(S) ;
    NumericVector tmp(K) ;
    NumericVector nu0 (1) ;
    NumericVector s20 (1) ;
    IntegerMatrix Z = chains.slot("z") ;
    IntegerVector zz ;
    IntegerVector nn(K) ;
    NumericVector nu_n(K) ;
    //
    // We need to keep the Z|y,theta* chain
    //
    NumericVector nu0chain = chains.slot("nu.0") ;
    NumericVector s20chain = chains.slot("sigma2.0") ;
    //
    NumericVector sigma2_n(1) ;
    NumericVector sigma2_new(K) ;  
    //
    // Run reduced Gibbs    -- theta is fixed at modal ordinate
    //
    prec = 1.0/sigma2star ;
    for(int s=0; s < S; ++s){
        zz = Z(s, _) ;
        nn = tableZ(K, zz) ;
        s20 = s20chain[s] ;
        nu0 = nu0chain[s] ;

        NumericVector ss(K) ;
        for(int i = 0; i < n; i++){
            int k = 0 ;
            while(k <= K) {
                if( zz[i] == k + 1 ){
                    ss[k] += pow(x[i] - thetastar[k], 2.0) ;
                    break ;
                }
                k++ ;
            }
        }
        
        double total = 1.0 ;        
        for(int k = 0; k < K; ++k){
            nu_n = nu0 + nn[k] ;
            sigma2_n = 1.0/nu_n[0]*(nu0*s20 + ss[k]) ;
            tmp = dgamma(prec, 0.5*nu_n[0], 2.0 / (nu_n[0]*sigma2_n[0])) ;
            total = total*tmp[k] ;
        }
        p_prec[s] = total ;
    }
    return p_prec ;
}


// [[Rcpp::export]]
Rcpp::S4 reduced_pi_batch(Rcpp::S4 xmod) {
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
    int K = thetastar.size() ;
    NumericVector prec(K) ;
    NumericVector logp_prec(S) ;
    NumericVector tmp(K) ;
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
        zz = update_z(model) ;
        model.slot("z") = zz ;
        Z(s, _) = zz ;
        model.slot("data.mean") = compute_means(model) ;
        model.slot("data.prec") = compute_prec(model) ;
        // model.slot("theta") = update_theta(model) ; Do not update theta !
        // model.slot("sigma2") = update_sigma2(model) ;
        model.slot("pi") = update_p(model) ;
        model.slot("mu") = update_mu(model) ;
        model.slot("tau2") = update_tau2(model) ;
        model.slot("nu.0") = update_nu0(model) ;
        model.slot("sigma2.0") = update_sigma2_0(model) ;
    }
    chains.slot("z") = Z ;
    model.slot("mcmc.chains") = chains ;
    return model ;
}

// [[Rcpp::export]]
Rcpp::S4 reduced_mu_batch(Rcpp::S4 xmod) {
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
    NumericVector prec(K) ;
    NumericVector logp_prec(S) ;
    NumericVector tmp(K) ;
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
        zz = update_z(model) ;
        model.slot("z") = zz ;
        Z(s, _) = zz ;      
        model.slot("data.mean") = compute_means(model) ;
        model.slot("data.prec") = compute_prec(model) ;
        // model.slot("theta") = update_theta(model) ; Do not update theta !
        // model.slot("sigma2") = update_sigma2(model) ;
        // model.slot("pi") = update_p(model) ;
        mu = update_mu(model) ;
        tau2 = update_tau2(model) ;
        nu0 = update_nu0(model) ;
        s20 = update_sigma2_0(model) ;
        
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
Rcpp::NumericVector p_mu_reduced_batch(Rcpp::S4 xmod) {
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
Rcpp::S4 reduced_tau_batch(Rcpp::S4 xmod) {
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
    NumericVector prec(K) ;
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
        zz = update_z(model) ;
        model.slot("z") = zz ;
        Z(s, _) = zz ;      
        model.slot("data.mean") = compute_means(model) ;
        model.slot("data.prec") = compute_prec(model) ;
        // model.slot("theta") = update_theta(model) ; Do not update theta !
        // model.slot("sigma2") = update_sigma2(model) ;
        // model.slot("pi") = update_p(model) ;
        // model.slot("mu") = update_mu(model) ;
        model.slot("tau2") = update_tau2(model) ;
        model.slot("nu.0") = update_nu0(model) ;
        model.slot("sigma2.0") = update_sigma2_0(model) ;
        //s20chain[s] = model.slot("sigma2.0") ;
    }
    chains.slot("z") = Z ;
    //chains.slot("sigma2.0") = s20chain ;
    model.slot("mcmc.chains") = chains ;
    return model ;
}


// [[Rcpp::export]]
Rcpp::NumericVector p_tau_reduced_batch(Rcpp::S4 xmod) {
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
    //  NumericVector tmp(1) ;
    //  for(int s = 0; s < S; ++s) {
    //      tmp = dgamma(1.0/tau2star, 0.5 * eta_k, 1.0/(0.5 * eta_k * m2_k[0])) ;
    //      p_tau[s] = tmp ;
    //  }
    p_tau = dgamma(1.0/tau2star, 0.5 * eta_k, 1.0/(0.5 * eta_k * m2_k[0])) ;
    return p_tau ;
}

// [[Rcpp::export]]
Rcpp::S4 reduced_nu0(Rcpp::S4 xmod) {
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
        zz = update_z(model) ;
        model.slot("z") = zz ;
        Z(s, _) = zz ;      
        model.slot("data.mean") = compute_means(model) ;
        model.slot("data.prec") = compute_prec(model) ;
        // model.slot("theta") = update_theta(model) ; Do not update theta !
        // model.slot("sigma2") = update_sigma2(model) ;
        // model.slot("pi") = update_p(model) ;
        // model.slot("mu") = update_mu(model) ;
        // model.slot("tau2") = update_tau2(model) ;
        model.slot("nu.0") = update_nu0(model) ;
        model.slot("sigma2.0") = update_sigma2_0(model) ;
        s20chain[s] = model.slot("sigma2.0") ;
    }
    chains.slot("z") = Z ;
    chains.slot("sigma2.0") = s20chain ;
    model.slot("mcmc.chains") = chains ;
    return model ;
}

// [[Rcpp::export]]
Rcpp::NumericVector p_nu0_reduced(Rcpp::S4 xmod) {
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
    double prec = 0.0 ;
    double lprec = 0.0 ;
    for(int k = 0; k < K; k++) prec += 1.0/sigma2star[k] ;
    for(int k = 0; k < K; k++) lprec += log(1.0/sigma2star[k]) ;
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
Rcpp::S4 reduced_s20(Rcpp::S4 xmod) {
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
        zz = update_z(model) ;
        model.slot("z") = zz ;
        Z(s, _) = zz ;      
        model.slot("data.mean") = compute_means(model) ;
        model.slot("data.prec") = compute_prec(model) ;
        // model.slot("theta") = update_theta(model) ; Do not update theta !
        // model.slot("sigma2") = update_sigma2(model) ;
        // model.slot("pi") = update_p(model) ;
        // model.slot("mu") = update_mu(model) ;
        // model.slot("tau2") = update_tau2(model) ;
        // model.slot("nu.0") = update_nu0(model) ;
        model.slot("sigma2.0") = update_sigma2_0(model) ;
    }
    chains.slot("z") = Z ;
    model.slot("mcmc.chains") = chains ;
    return model ;
}

// [[Rcpp::export]]
Rcpp::NumericVector p_s20_reduced(Rcpp::S4 xmod) {
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
    NumericVector s20_=as<NumericVector>(modes["sigma2.0"]) ;
    NumericVector pstar = clone(p_) ;
    NumericVector mustar = clone(mu_) ;
    NumericVector tau2star = clone(tau2_) ;
    NumericVector thetastar = clone(theta_) ;
    NumericVector sigma2star = clone(sigma2_) ;
    NumericVector s20star = clone(s20_) ;
    IntegerVector nu0=clone(nu0_) ;
    int nu0star = nu0[0] ;
    
    NumericVector p_s20(S) ;

    double a = hypp.slot("a") ;
    double b = hypp.slot("b") ;  
    double a_k = a + 0.5*K*nu0star ;
    double b_k ;

    for (int k=0; k < K; k++) {
        b_k += 0.5*nu0star/sigma2star[k];
    }
    b_k += b ;
    p_s20 = dgamma(s20star, a_k, 1.0/b_k) ;
    return p_s20 ;
}

