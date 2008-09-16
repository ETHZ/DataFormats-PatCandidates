
#ifndef DataFormats_PatCandidates_MHT_h
#define DataFormats_PatCandidates_MHT_h
                                                                                                                   
#include "DataFormats/Candidate/interface/CompositeRefBaseCandidate.h"
#include "DataFormats/Candidate/interface/Candidate.h"
                                                                                                                   
namespace pat {
                                                                                                                   
  class MHT : public reco::CompositeRefBaseCandidate {
  public:
    MHT () {}
    MHT (const Particle::LorentzVector& p4, float ht, float signif) :
      CompositeRefBaseCandidate(0,p4), ht_(ht), significance_(signif) {}
    virtual ~MHT () {}
                                                                                                                   
    float mht() {return pt();};
    float phi() {return phi();};
    float ht() {return ht_;};
    float significance() {return significance_;};
    float error() {return 0.5*significance()*mht()*mht();};
                                                                                                                   
  private:
                                                                                                                   
    float ht_;
    float significance_;
                                                                                                                   
                                                                                                                   
  };
                                                                                                                   
  typedef std::vector<MHT> MHTCollection;
}
                                                                                                                   
#endif






