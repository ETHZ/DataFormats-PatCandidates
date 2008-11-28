//
// $Id: Muon.cc,v 1.15 2008/10/10 17:44:57 lowette Exp $
//

#include "DataFormats/PatCandidates/interface/Muon.h"


using namespace pat;


/// default constructor
Muon::Muon() :
    Lepton<reco::Muon>(),
    embeddedTrack_(false),
    embeddedStandAloneMuon_(false),
    embeddedCombinedMuon_(false),
    embeddedPFCandidate_(false),
    pfCandidateRef_()
{
}


/// constructor from reco::Muon
Muon::Muon(const reco::Muon & aMuon) :
    Lepton<reco::Muon>(aMuon),
    embeddedTrack_(false),
    embeddedStandAloneMuon_(false),
    embeddedCombinedMuon_(false),
    embeddedPFCandidate_(false),
    pfCandidateRef_()
{
}


/// constructor from ref to reco::Muon
Muon::Muon(const edm::RefToBase<reco::Muon> & aMuonRef) :
    Lepton<reco::Muon>(aMuonRef),
    embeddedTrack_(false),
    embeddedStandAloneMuon_(false),
    embeddedCombinedMuon_(false),
    embeddedPFCandidate_(false),
    pfCandidateRef_()
{
}


/// constructor from ref to reco::Muon
Muon::Muon(const edm::Ptr<reco::Muon> & aMuonRef) :
    Lepton<reco::Muon>(aMuonRef),
    embeddedTrack_(false),
    embeddedStandAloneMuon_(false),
    embeddedCombinedMuon_(false),
    embeddedPFCandidate_(false),
    pfCandidateRef_()
{
}


/// destructor
Muon::~Muon() {
}


/// reference to Track reconstructed in the tracker only (reimplemented from reco::Muon)
reco::TrackRef Muon::track() const {
  if (embeddedTrack_) {
    return reco::TrackRef(&track_, 0);
  } else {
    return reco::Muon::innerTrack();
  }
}


/// reference to Track reconstructed in the muon detector only (reimplemented from reco::Muon)
reco::TrackRef Muon::standAloneMuon() const {
  if (embeddedStandAloneMuon_) {
    return reco::TrackRef(&standAloneMuon_, 0);
  } else {
    return reco::Muon::outerTrack();
  }
}


/// reference to Track reconstructed in both tracked and muon detector (reimplemented from reco::Muon)
reco::TrackRef Muon::combinedMuon() const {
  if (embeddedCombinedMuon_) {
    return reco::TrackRef(&combinedMuon_, 0);
  } else {
    return reco::Muon::globalTrack();
  }
}


/// reference to the source IsolatedPFCandidates
reco::IsolatedPFCandidateRef Muon::pfCandidateRef() const {
  if (embeddedPFCandidate_) {
    return reco::IsolatedPFCandidateRef(&pfCandidate_, 0);
  } else {
    return pfCandidateRef_;
  }
}


/// embed the Track reconstructed in the tracker only
void Muon::embedTrack() {
  track_.clear();
  if (reco::Muon::innerTrack().isNonnull()) {
      track_.push_back(*reco::Muon::innerTrack());
      embeddedTrack_ = true;
  }
}


/// embed the Track reconstructed in the muon detector only
void Muon::embedStandAloneMuon() {
  standAloneMuon_.clear();
  if (reco::Muon::outerTrack().isNonnull()) {
      standAloneMuon_.push_back(*reco::Muon::outerTrack());
      embeddedStandAloneMuon_ = true;
  }
}


/// embed the Track reconstructed in both tracked and muon detector
void Muon::embedCombinedMuon() {
  combinedMuon_.clear();
  if (reco::Muon::globalTrack().isNonnull()) {
      combinedMuon_.push_back(*reco::Muon::globalTrack());
      embeddedCombinedMuon_ = true;
  }
}


/// embed the IsolatedPFCandidate pointed to by pfCandidateRef_
void Muon::embedPFCandidate() {
  pfCandidate_.clear();
  if ( pfCandidateRef_.isAvailable() && pfCandidateRef_.isNonnull()) {
    pfCandidate_.push_back( *pfCandidateRef_ );
    embeddedPFCandidate_ = true;
  }
}

