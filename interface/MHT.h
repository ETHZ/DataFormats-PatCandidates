
#ifndef DataFormats_PatCandidates_MHT_h
#define DataFormats_PatCandidates_MHT_h

#include "DataFormats/Candidate/interface/CompositeRefBaseCandidate.h"
#include "DataFormats/Candidate/interface/Candidate.h"

namespace pat {
  
  class MHT : public reco::CompositeRefBaseCandidate {
  public:
    MHT () {}
    MHT (const Particle::LorentzVector& p4, double ht, double signif) :
      CompositeRefBaseCandidate(0,p4), ht_(ht), significance_(signif) {}
    virtual ~MHT () {}
    
    double mht() const {return pt();};
    double phi() const {return phi();};
    double ht()  const {return ht_;};
    double significance() const {return significance_;};
    double error()  const{return 0.5*significance()*mht()*mht();};
    
    double getNumberOfJets() const;
    void   setNumberOfJets(const double & numberOfJets);
    
    double getNumberOfElectrons() const;
    void   setNumberOfElectrons(const double & numberOfElectrons);

    double getNumberOfMuons() const;
    void   setNumberOfMuons(const double & numberOfMuons);

    void   setUncorMET(const double & uncor_met);
    double getUncorMET() const ;
    void   setUncorMETsignificance(const double & uncor_met_significance);
    double getUncorMETsignificance() const ;
    
    void   setMET(const double & met);
    double getMET() const ;
    void   setMETsignificance(const double & met_significance);
    double getMETsignificance() const ;
    
   private:
    
    double ht_;
    double significance_;
    double number_of_jets_;
    double number_of_electrons_;
    double number_of_muons_;
    
    double uncor_met_;
    double uncor_met_significance_;

    double met_;
    double met_significance_;
  
  };
  
  typedef std::vector<pat::MHT> MHTCollection;
}

#endif






