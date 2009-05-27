//
// $Id: CompositeCandidate.cc,v 1.2 2008/11/28 19:25:02 lowette Exp $
//

#include "DataFormats/PatCandidates/interface/CompositeCandidate.h"


using namespace pat;


/// default constructor
CompositeCandidate::CompositeCandidate() : 
  reco::CompositeCandidate(reco::CompositeCandidate(0, reco::CompositeCandidate::LorentzVector(0, 0, 0, 0), reco::CompositeCandidate::Point(0,0,0))),
  PATObject()
{
}


/// constructor from CompositeCandidateType
CompositeCandidate::CompositeCandidate(const reco::CompositeCandidate & aCompositeCandidate) : 
  reco::CompositeCandidate(aCompositeCandidate),
  PATObject()
{
}



/// constructor from CompositeCandidateRef
CompositeCandidate::CompositeCandidate( const  edm::RefToBase<reco::CompositeCandidate> & ref) : 
  reco::CompositeCandidate(*ref),
  PATObject()
{
  refToOrig_ = edm::Ptr<reco::Candidate>(ref.id(), ref.get(), ref.key());
}



/// constructor from CompositeCandidateRef
CompositeCandidate::CompositeCandidate( const  edm::Ptr<reco::CompositeCandidate> & ref) : 
  reco::CompositeCandidate(*ref),
  PATObject()
{
  refToOrig_ = edm::Ptr<reco::Candidate>(ref.id(), ref.get(), ref.key());  
}

/// destructor
CompositeCandidate::~CompositeCandidate() {
}
