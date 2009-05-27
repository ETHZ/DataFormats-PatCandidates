//
// $Id: Lepton.h,v 1.14 2008/10/07 18:15:13 lowette Exp $
//

#ifndef DataFormats_PatCandidates_Lepton_h
#define DataFormats_PatCandidates_Lepton_h

/**
  \class    pat::Lepton Lepton.h "DataFormats/PatCandidates/interface/Lepton.h"
  \brief    Analysis-level lepton class

   Lepton implements the analysis-level charged lepton class within the 'pat'
   namespace. It currently provides the link to the generated lepton and
   the isolation information.

   Please post comments and questions to the Physics Tools hypernews:
   https://hypernews.cern.ch/HyperNews/CMS/get/physTools.html

  \author   Steven Lowette, Giovanni Petrucciani, Frederic Ronga
  \version  $Id: Lepton.h,v 1.14 2008/10/07 18:15:13 lowette Exp $
*/

#include "DataFormats/Candidate/interface/Particle.h"
#include "DataFormats/PatCandidates/interface/PATObject.h"
#include "DataFormats/PatCandidates/interface/Isolation.h"


namespace pat {

  class Lepton : public PATObject {

    public:

      Lepton();
      virtual ~Lepton() {}

      virtual Lepton * clone() const = 0;

      const reco::GenParticle * genLepton() const { return PATObject::genParticle(); }

      void setGenLepton(const reco::GenParticleRef & gl, bool embed=false) { PATObject::setGenParticleRef(gl, embed); }


      //============ BEGIN ISOLATION BLOCK =====
      /// Returns the isolation variable for a specifc key (or pseudo-key like CaloIso), or -1.0 if not available
      float isolation(IsolationKeys key) const;

      /// Sets the isolation variable for a specifc key.
      /// Note that you can't set isolation for a pseudo-key like CaloIso
      void setIsolation(IsolationKeys key, float value);

      // ---- specific getters ----
      /// Return the tracker isolation variable that was stored in this object when produced, or -1.0 if there is none
      float trackIso() const { return isolation(TrackerIso); }
      /// Return the sum of ecal and hcal isolation variable that were stored in this object when produced, or -1.0 if at least one is missing
      float caloIso()  const { return isolation(CaloIso); }
      /// Return the ecal isolation variable that was stored in this object when produced, or -1.0 if there is none
      float ecalIso()  const { return isolation(ECalIso); }
      /// Return the hcal isolation variable that was stored in this object when produced, or -1.0 if there is none
      float hcalIso()  const { return isolation(HCalIso); }
      /// Return the user defined isolation variable #index that was stored in this object when produced, or -1.0 if there is none
      float userIso(uint8_t index=0)  const { return isolation(IsolationKeys(UserBaseIso + index)); }

      // ---- specific setters ----
      /// Sets tracker isolation variable
      void setTrackIso(float trackIso) { setIsolation(TrackerIso, trackIso); }
      /// Sets ecal isolation variable
      void setECalIso(float caloIso)   { setIsolation(ECalIso, caloIso);  } 
      /// Sets hcal isolation variable
      void setHCalIso(float caloIso)   { setIsolation(HCalIso, caloIso);  }
      /// Sets user isolation variable #index
      void setUserIso(float value, uint8_t index=0)  { setIsolation(IsolationKeys(UserBaseIso + index), value); }


      //============ BEGIN ISODEPOSIT BLOCK =====
      /// Returns the IsoDeposit associated with some key, or a null pointer if it is not available
      const IsoDeposit * isoDeposit(IsolationKeys key) const ;

      /// Sets the IsoDeposit associated with some key; if it is already existent, it is overwritten.
      void setIsoDeposit(IsolationKeys key, const IsoDeposit &dep);

      // ---- specific getters ----
      const IsoDeposit * trackerIsoDeposit() const { return isoDeposit(TrackerIso); }
      const IsoDeposit * ecalIsoDeposit()    const { return isoDeposit(ECalIso); }
      const IsoDeposit * hcalIsoDeposit()    const { return isoDeposit(HCalIso); }
      const IsoDeposit * userIsoDeposit(uint8_t index=0) const { return isoDeposit(IsolationKeys(UserBaseIso + index)); }

      // ---- specific setters ----
      void trackerIsoDeposit(const IsoDeposit &dep) { setIsoDeposit(TrackerIso, dep); }
      void ecalIsoDeposit(const IsoDeposit &dep)    { setIsoDeposit(ECalIso, dep); }
      void hcalIsoDeposit(const IsoDeposit &dep)    { setIsoDeposit(HCalIso, dep); }
      void userIsoDeposit(const IsoDeposit &dep, uint8_t index=0) { setIsoDeposit(IsolationKeys(UserBaseIso + index), dep); }


    protected:
      // --- Isolation and IsoDeposit related datamebers ---
      typedef std::vector<std::pair<IsolationKeys, pat::IsoDeposit> > IsoDepositPairs;
      IsoDepositPairs    isoDeposits_;
      std::vector<float> isolations_;
  };

}

#endif
