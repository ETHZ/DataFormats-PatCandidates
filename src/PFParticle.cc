//
// $Id: PFParticle.cc,v 1.2 2008/11/28 19:02:15 lowette Exp $
//

#include "DataFormats/PatCandidates/interface/PFParticle.h"


using namespace pat;


/// constructor from PFParticleType
PFParticle::PFParticle(const reco::PFCandidate & aPFParticle) : 
  reco::PFCandidate(aPFParticle),
  PATObject()
{
}

/// constructor from ref
PFParticle::PFParticle(const edm::RefToBase<reco::PFCandidate>& ref) : 
  reco::PFCandidate(*ref),
  PATObject()
{
  refToOrig_ = edm::Ptr<reco::Candidate>(ref.id(), ref.get(), ref.key());
}


/// constructor from ptr
PFParticle::PFParticle(const edm::Ptr<reco::PFCandidate>& ref) : 
  reco::PFCandidate(*ref),
  PATObject()
{
  refToOrig_ = edm::Ptr<reco::Candidate>(ref.id(), ref.get(), ref.key());
}

