//
// $Id: Tau.cc,v 1.4.2.2 2008/05/20 10:02:48 lowette Exp $
//

#include "DataFormats/PatCandidates/interface/Tau.h"


using namespace pat;


/// default constructor
Tau::Tau() :
    Lepton<TauType>(),
    embeddedIsolationTracks_(false),
    embeddedLeadTrack_(false),
    embeddedSignalTracks_(false),
    emEnergyFraction_(0.),
    eOverP_(0.),
    leadeOverP_(0.),
    HhotOverP_(0.),
    HtotOverP_(0.)
{
}


/// constructor from TauType
Tau::Tau(const TauType & aTau) :
    Lepton<TauType>(aTau),
    embeddedIsolationTracks_(false),
    embeddedLeadTrack_(false),
    embeddedSignalTracks_(false),
    emEnergyFraction_(0.),
    eOverP_(0.),
    leadeOverP_(0.),
    HhotOverP_(0.),
    HtotOverP_(0.)
{
}


/// constructor from ref to TauType
Tau::Tau(const edm::RefToBase<TauType> & aTauRef) :
    Lepton<TauType>(aTauRef),
    embeddedIsolationTracks_(false),
    embeddedLeadTrack_(false),
    embeddedSignalTracks_(false),
    emEnergyFraction_(0.),
    eOverP_(0.),
    leadeOverP_(0.),
    HhotOverP_(0.),
    HtotOverP_(0.)
{
}


/// destructor
Tau::~Tau() {
}


/// override the TauType::isolationTracks method, to access the internal storage of the track
const reco::TrackRefVector & Tau::isolationTracks() const {
  if (embeddedIsolationTracks_) {
    transientIsolationTracksRefVector_.clear();
    for (unsigned int i = 0; i < isolationTracks_.size(); i++) {
      transientIsolationTracksRefVector_.push_back(reco::TrackRef(&isolationTracks_, i));
    }
    return transientIsolationTracksRefVector_;
  } else {
    return TauType::isolationTracks();
  }
}


/// override the TauType::track method, to access the internal storage of the track
const reco::TrackRef & Tau::leadTrack() const {
  if (embeddedLeadTrack_) {
    transientLeadTrackRef_ = reco::TrackRef(&leadTrack_, 0);
    return transientLeadTrackRef_;
  } else {
    return TauType::leadTrack();
  }
}


/// override the TauType::track method, to access the internal storage of the track
const reco::TrackRefVector & Tau::signalTracks() const {
  if (embeddedSignalTracks_) {
    transientSignalTracksRefVector_.clear();
    for (unsigned int i = 0; i < signalTracks_.size(); i++) {
      transientSignalTracksRefVector_.push_back(reco::TrackRef(&signalTracks_, i));
    }
    return transientSignalTracksRefVector_;
  } else {
    return TauType::signalTracks();
  }
}


/// method to store the isolation tracks internally
void Tau::embedIsolationTracks() {
  isolationTracks_.clear();
  reco::TrackRefVector trackRefVec = TauType::isolationTracks();
  for (unsigned int i = 0; i < trackRefVec.size(); i++) {
    isolationTracks_.push_back(*trackRefVec.at(i));
  }
  embeddedIsolationTracks_ = true;
}


/// method to store the isolation tracks internally
void Tau::embedLeadTrack() {
  leadTrack_.clear();
  if (TauType::leadTrack().isNonnull()) {
      leadTrack_.push_back(*TauType::leadTrack());
      embeddedLeadTrack_ = true;
  }
}


/// method to store the isolation tracks internally
void Tau::embedSignalTracks(){
  signalTracks_.clear();
  reco::TrackRefVector trackRefVec = TauType::signalTracks();
  for (unsigned int i = 0; i < trackRefVec.size(); i++) {
    signalTracks_.push_back(*trackRefVec.at(i));
  }
  embeddedSignalTracks_ = true;
}
