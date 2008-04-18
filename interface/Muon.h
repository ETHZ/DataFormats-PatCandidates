//
// $Id: Muon.h,v 1.8.2.1 2008/04/10 19:25:59 srappocc Exp $
//

#ifndef DataFormats_PatCandidates_Muon_h
#define DataFormats_PatCandidates_Muon_h

/**
  \class    pat::Muon Muon.h "DataFormats/PatCandidates/interface/Muon.h"
  \brief    Analysis-level muon class

   Muon implements the analysis-level muon class within the 'pat' namespace.

  \author   Steven Lowette
  \version  $Id: Muon.h,v 1.8.2.1 2008/04/10 19:25:59 srappocc Exp $
*/

#include "DataFormats/MuonReco/interface/Muon.h"
#include "DataFormats/MuonReco/interface/MuonFwd.h"
#include "DataFormats/PatCandidates/interface/Lepton.h"


namespace pat {


  typedef reco::Muon MuonType;
  typedef reco::MuonCollection MuonTypeCollection;


  class Muon : public Lepton<MuonType> {

    public:

      Muon();
      Muon(const MuonType & aMuon);
      Muon(const edm::RefToBase<MuonType> & aMuonRef);
      virtual ~Muon();

      virtual Muon * clone() const { return new Muon(*this); }

      float leptonID() const;
      float segmentCompatibility() const; // calo compatibility is already stored in the reco::Muon class

      void setLeptonID(float id);
      void setSegmentCompatibility(float sc);

    protected:

      float leptonID_;
      float segmentCompatibility_;

  };


}

#endif
