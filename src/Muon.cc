//
// $Id: Muon.cc,v 1.5.2.1 2008/04/18 11:50:18 lowette Exp $
//

#include "DataFormats/PatCandidates/interface/Muon.h"

#include "RecoMuon/MuonIdentification/interface/IdGlobalFunctions.h"


using namespace pat;


/// default constructor
Muon::Muon() : Lepton<MuonType>() {
}


/// constructor from MuonType
Muon::Muon(const MuonType & aMuon) : Lepton<MuonType>(aMuon) {
}


/// constructor from ref to MuonType
Muon::Muon(const edm::RefToBase<MuonType> & aMuonRef) : Lepton<MuonType>(aMuonRef) {
}


/// destructor
Muon::~Muon() {
}


/// return the lepton ID discriminator
float Muon::leptonID() const {
  return leptonID_;
}


/// return the lepton ID discriminator
float Muon::segmentCompatibility() const {
  return muonid::getSegmentCompatibility(*this);
}


/// method to set the lepton ID discriminator
void Muon::setLeptonID(float id) {
  leptonID_ = id;
}
