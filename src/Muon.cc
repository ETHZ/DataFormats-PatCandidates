//
// $Id: Muon.cc,v 1.5 2008/04/03 12:29:09 gpetrucc Exp $
//

#include "DataFormats/PatCandidates/interface/Muon.h"


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
  return segmentCompatibility_;
}


/// method to set the lepton ID discriminator
void Muon::setLeptonID(float id) {
  leptonID_ = id;
}


/// method to set the lepton ID discriminator
void Muon::setSegmentCompatibility(float sc) {
  segmentCompatibility_ = sc;
}
