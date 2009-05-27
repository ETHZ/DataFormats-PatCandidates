//
// $Id: Electron.cc,v 1.15 2009/03/26 06:23:10 hegner Exp $
//

#include "DataFormats/PatCandidates/interface/Electron.h"
#include "FWCore/Utilities/interface/Exception.h"

using namespace pat;


/// default constructor
Electron::Electron() :
    reco::GsfElectron(),
    Lepton(),
    embeddedGsfTrack_(false),
    embeddedSuperCluster_(false),
    embeddedTrack_(false),
    scSigmaEtaEta_(0),
    scSigmaIEtaIEta_(0), 
    scE1x5_(0),
    scE2x5Max_(0), 
    scE5x5_(0) 
{
}


/// constructor from reco::GsfElectron
Electron::Electron(const reco::GsfElectron & anElectron) :
    reco::GsfElectron(anElectron),
    Lepton(),
    embeddedGsfTrack_(false),
    embeddedSuperCluster_(false),
    embeddedTrack_(false),
    scSigmaEtaEta_(0),
    scSigmaIEtaIEta_(0), 
    scE1x5_(0),
    scE2x5Max_(0), 
    scE5x5_(0) 
{
}


/// constructor from ref to reco::GsfElectron
Electron::Electron(const edm::RefToBase<reco::GsfElectron> & ref) :
    reco::GsfElectron(*ref),
    Lepton(),
    embeddedGsfTrack_(false),
    embeddedSuperCluster_(false),
    embeddedTrack_(false),
    scSigmaEtaEta_(0),
    scSigmaIEtaIEta_(0), 
    scE1x5_(0),
    scE2x5Max_(0), 
    scE5x5_(0) 
{
  refToOrig_ = edm::Ptr<reco::Candidate>(ref.id(), ref.get(), ref.key());
}

/// constructor from Ptr to reco::GsfElectron
Electron::Electron(const edm::Ptr<reco::GsfElectron> & ref) :
    reco::GsfElectron(*ref),
    Lepton(),
    embeddedGsfTrack_(false),
    embeddedSuperCluster_(false),
    embeddedTrack_(false),
    scSigmaEtaEta_(0),
    scSigmaIEtaIEta_(0), 
    scE1x5_(0),
    scE2x5Max_(0), 
    scE5x5_(0) 
{
  refToOrig_ = edm::Ptr<reco::Candidate>(ref.id(), ref.get(), ref.key());
}


/// destructor
Electron::~Electron() {
}


/// override the reco::GsfElectron::gsfTrack method, to access the internal storage of the supercluster
reco::GsfTrackRef Electron::gsfTrack() const {
  if (embeddedGsfTrack_) {
    return reco::GsfTrackRef(&gsfTrack_, 0);
  } else {
    return reco::GsfElectron::gsfTrack();
  }
}


/// override the reco::GsfElectron::superCluster method, to access the internal storage of the supercluster
reco::SuperClusterRef Electron::superCluster() const {
  if (embeddedSuperCluster_) {
    return reco::SuperClusterRef(&superCluster_, 0);
  } else {
    return reco::GsfElectron::superCluster();
  }
}


/// override the reco::GsfElectron::track method, to access the internal storage of the track
reco::TrackRef Electron::track() const {
  if (embeddedTrack_) {
    return reco::TrackRef(&track_, 0);
  } else {
    return reco::GsfElectron::track();
  }
}

/// method to store the electron's gsfTrack internally
void Electron::embedGsfTrack() {
  gsfTrack_.clear();
  if (reco::GsfElectron::gsfTrack().isNonnull()) {
      gsfTrack_.push_back(*reco::GsfElectron::gsfTrack());
      embeddedGsfTrack_ = true;
  }
}


/// method to store the electron's supercluster internally
void Electron::embedSuperCluster() {
  superCluster_.clear();
  if (reco::GsfElectron::superCluster().isNonnull()) {
      superCluster_.push_back(*reco::GsfElectron::superCluster());
      embeddedSuperCluster_ = true;
  }
}


/// method to store the electron's track internally
void Electron::embedTrack() {
  track_.clear();
  if (reco::GsfElectron::track().isNonnull()) {
      track_.push_back(*reco::GsfElectron::track());
      embeddedTrack_ = true;
  }
}

// method to retrieve a lepton ID (or throw)
float Electron::electronID(const std::string & name) const {
    for (std::vector<IdPair>::const_iterator it = electronIDs_.begin(), ed = electronIDs_.end(); it != ed; ++it) {
        if (it->first == name) return it->second;
    }
    cms::Exception ex("Key not found");
    ex << "pat::Electron: the ID " << name << " can't be found in this pat::Electron.\n";
    ex << "The available IDs are: ";
    for (std::vector<IdPair>::const_iterator it = electronIDs_.begin(), ed = electronIDs_.end(); it != ed; ++it) {
        ex << "'" << it->first << "' ";
    }
    ex << ".\n";
    throw ex;
}
// check if an ID is there
bool Electron::isElectronIDAvailable(const std::string & name) const {
    for (std::vector<IdPair>::const_iterator it = electronIDs_.begin(), ed = electronIDs_.end(); it != ed; ++it) {
        if (it->first == name) return true;
    }
    return false;
}
/// method to store the electron's cluster shape
void Electron::setClusterShapes (const float& scSigmaEtaEta, const float& scSigmaIEtaIEta, 
                                 const float& scE1x5, const float& scE2x5Max, const float& scE5x5) 
  { 
    scSigmaEtaEta_ = scSigmaEtaEta ; 
    scSigmaIEtaIEta_ = scSigmaIEtaIEta ;
    scE1x5_ = scE1x5 ;
    scE2x5Max_ = scE2x5Max ;
    scE5x5_ = scE5x5 ;
  }


/// reference to the source PFCandidates
reco::PFCandidateRef Electron::pfCandidateRef() const {
  if (embeddedPFCandidate_) {
    return reco::PFCandidateRef(&pfCandidate_, 0);
  } else {
    return pfCandidateRef_;
  }
}
/// embed the IsolatedPFCandidate pointed to by pfCandidateRef_
void Electron::embedPFCandidate() {
  pfCandidate_.clear();
  if ( pfCandidateRef_.isAvailable() && pfCandidateRef_.isNonnull()) {
    pfCandidate_.push_back( *pfCandidateRef_ );
    embeddedPFCandidate_ = true;
  }
}
