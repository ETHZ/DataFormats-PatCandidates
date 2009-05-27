//
// $Id: PATObject.h,v 1.25 2009/04/20 19:47:18 vadler Exp $
//

#ifndef DataFormats_PatCandidates_PATObject_h
#define DataFormats_PatCandidates_PATObject_h

/**
  \class    pat::PATObject PATObject.h "DataFormats/PatCandidates/interface/PATObject.h"
  \brief    Templated PAT object container

   PATObject is the templated base PAT object that wraps around reco objects.

   Please post comments and questions to the Physics Tools hypernews:
   https://hypernews.cern.ch/HyperNews/CMS/get/physTools.html

  \author   Steven Lowette, Giovanni Petrucciani, Frederic Ronga, Volker Adler, Sal Rappoccio
  \version  $Id: PATObject.h,v 1.25 2009/04/20 19:47:18 vadler Exp $
*/


#include "DataFormats/Common/interface/Ptr.h"
#include "DataFormats/Candidate/interface/CandidateFwd.h"
#include "DataFormats/Candidate/interface/Candidate.h"
#include <vector>
#include <string>

#include "DataFormats/PatCandidates/interface/TriggerObjectStandAlone.h"
#include "DataFormats/PatCandidates/interface/LookupTableRecord.h"

#include "DataFormats/HepMCCandidate/interface/GenParticle.h"

#include "DataFormats/PatCandidates/interface/UserData.h"
#include "DataFormats/Common/interface/OwnVector.h"


namespace pat {


   class PATObject : virtual public reco::Candidate {
    public:

      typedef  reco::Candidate             base_type;

      /// default constructor
      PATObject() {}
      /// destructor
      virtual ~PATObject() {}
      /// returns a clone 
      virtual PATObject * clone() const = 0;

      /// access to the original object; returns zero for null Ref and throws for unavailable collection
      virtual const reco::Candidate * originalObject() const;
      /// reference to original object. Returns a null reference if not available
      virtual const edm::Ptr<reco::Candidate> & originalObjectRef() const;

      /// set original object reference from RefToBase
      virtual void setOriginalObjectRef(const edm::RefToBase<reco::Candidate> & ref);
      /// set original object reference from Ptr
      virtual void setOriginalObjectRef(const edm::Ptr<reco::Candidate> & ref);

      /// embedded trigger matches
      const TriggerObjectStandAloneCollection & triggerObjectMatches() const;
      const TriggerObjectStandAloneCollection   triggerObjectMatchesByFilterID( const unsigned id ) const; // filter IDs are defined in enum trigger::TriggerObjectType (DataFormats/HLTReco/interface/TriggerTypeDefs.h)
      const TriggerObjectStandAloneCollection   triggerObjectMatchesByCollection( const std::string & coll ) const; // filter IDs are defined in enum trigger::TriggerObjectType (DataFormats/HLTReco/interface/TriggerTypeDefs.h)
      const TriggerObjectStandAloneCollection   triggerObjectMatchesByFilter( const std::string & labelFilter ) const;
      const TriggerObjectStandAloneCollection   triggerObjectMatchesByPath( const std::string & namePath ) const;
      /// add a trigger match
      void addTriggerObjectMatch( const TriggerObjectStandAlone & trigObj );

      /// Returns an efficiency given its name
      const pat::LookupTableRecord       & efficiency(const std::string &name) const ;
      /// Returns the efficiencies as <name,value> pairs (by value)
      std::vector<std::pair<std::string,pat::LookupTableRecord> > efficiencies() const ;
      /// Returns the list of the names of the stored efficiencies 
      const std::vector<std::string> & efficiencyNames() const { return efficiencyNames_; }
      /// Returns the list of the values of the stored efficiencies (the ordering is the same as in efficiencyNames())
      const std::vector<pat::LookupTableRecord> & efficiencyValues() const { return efficiencyValues_; }
      /// Store one efficiency in this item, in addition to the existing ones
      /// If an efficiency with the same name exists, the old value is replaced by this one
      /// Calling this method many times with names not sorted alphabetically will be slow
      void setEfficiency(const std::string &name, const pat::LookupTableRecord & value) ;
     
      /// Get generator level particle reference (might be a transient ref if the genParticle was embedded)
      /// If you stored multiple GenParticles, you can specify which one you want.
      reco::GenParticleRef      genParticleRef(size_t idx=0) const { 
            if (idx >= genParticlesSize()) return reco::GenParticleRef();
            return genParticleEmbedded_.empty() ? genParticleRef_[idx] : reco::GenParticleRef(&genParticleEmbedded_, idx); 
      }
      /// Get a generator level particle reference with a given pdg id and status
      /// If there is no MC match with that pdgId and status, it will return a null ref
      /// Note: this might be a transient ref if the genParticle was embedded
      reco::GenParticleRef      genParticleById(int pdgId, int status) const ;

      /// Get generator level particle, as C++ pointer (might be 0 if the ref was null)
      /// If you stored multiple GenParticles, you can specify which one you want.
      const reco::GenParticle * genParticle(size_t idx=0)    const { 
            reco::GenParticleRef ref = genParticleRef(idx); 
            return ref.isNonnull() ? ref.get() : 0; 
      }
      /// Number of generator level particles stored as ref or embedded
      size_t genParticlesSize() const { 
            return genParticleEmbedded_.empty() ? genParticleRef_.size() : genParticleEmbedded_.size(); 
      }
      /// Return the list of generator level particles.
      /// Note that the refs can be transient refs to embedded GenParticles
      std::vector<reco::GenParticleRef> genParticleRefs() const ;

      /// Set the generator level particle reference
      void setGenParticleRef(const reco::GenParticleRef &ref, bool embed=false) ; 
      /// Add a generator level particle reference
      /// If there is already an embedded particle, this ref will be embedded too
      void addGenParticleRef(const reco::GenParticleRef &ref) ; 
      /// Set the generator level particle from a particle not in the Event (embedding it, of course)
      void setGenParticle( const reco::GenParticle &particle ) ; 
      /// Embed the generator level particle(s) in this PATObject
      /// Note that generator level particles can only be all embedded or all not embedded.
      void embedGenParticle() ;

      /// Returns true if there was at least one overlap for this test label
      bool hasOverlaps(const std::string &label) const ;
      /// Return the list of overlaps for one label (can be empty)
      /// The original ordering of items is kept (usually it's by increasing deltaR from this item)
      const reco::CandidatePtrVector & overlaps(const std::string &label) const ;
      /// Returns the labels of the overlap tests that found at least one overlap
      const std::vector<std::string> & overlapLabels() const { return overlapLabels_; }
      /// Sets the list of overlapping items for one label 
      /// Note that adding an empty PtrVector has no effect at all
      /// Items within the list should already be sorted appropriately (this method won't sort them)
      void setOverlaps(const std::string &label, const reco::CandidatePtrVector & overlaps) ;

      /// Returns user-defined data. Returns NULL if the data is not present, or not of type T.
      template<typename T> const T * userData(const std::string &key) const {
          const pat::UserData * data = userDataObject_(key);
          return (data != 0 ? data->template get<T>() : 0);
          
      }
      /// Check if user data with a specific type is present
      bool hasUserData(const std::string &key) const {
          return (userDataObject_(key) != 0);
      }
      /// Get human-readable type of user data object, for debugging
      const std::string & userDataObjectType(const std::string &key) const { 
          static const std::string EMPTY("");
          const pat::UserData * data = userDataObject_(key);
          return (data != 0 ? data->typeName() : EMPTY);
      }; 
      /// Get list of user data object names
      const std::vector<std::string> & userDataNames() const  { return userDataLabels_; }

      /// Get the data as a void *, for CINT usage.
      /// COMPLETELY UNSUPPORTED, USE ONLY FOR DEBUGGING
      const void * userDataBare(const std::string &key) const {
          const pat::UserData * data = userDataObject_(key);
          return (data != 0 ? data->bareData() : 0);
      }
    
      /// Set user-defined data
      /// Needs dictionaries for T and for pat::UserHolder<T>, 
      /// and it will throw exception if they're missing,
      /// unless transientOnly is set to true 
      template<typename T>
      void addUserData( const std::string & label, const T & data, bool transientOnly=false ) {
          userDataLabels_.push_back(label);
          userDataObjects_.push_back(pat::UserData::make<T>(data, transientOnly));
      }

      /// Set user-defined data. To be used only to fill from ValueMap<Ptr<UserData>>
      /// Do not use unless you know what you are doing.
      void addUserDataFromPtr( const std::string & label, const edm::Ptr<pat::UserData> & data ) {
          userDataLabels_.push_back(label);
          userDataObjects_.push_back(data->clone());
      }
      
      /// Get user-defined float
      /// Note: it will return 0.0 if the key is not found; you can check if the key exists with 'hasUserFloat' method.
      float userFloat( const std::string & key ) const;
      /// Set user-defined float
      void addUserFloat( const  std::string & label, float data );
      /// Get list of user-defined float names
      const std::vector<std::string> & userFloatNames() const  { return userFloatLabels_; }
      /// Return true if there is a user-defined float with a given name
      bool hasUserFloat( const std::string & key ) const {
        return std::find(userFloatLabels_.begin(), userFloatLabels_.end(), key) != userFloatLabels_.end();
      }
      /// Get user-defined int
      /// Note: it will return 0 if the key is not found; you can check if the key exists with 'hasUserInt' method.
      int32_t userInt( const std::string & key ) const;
      /// Set user-defined int
      void addUserInt( const std::string & label,  int32_t data );
      /// Get list of user-defined int names
      const std::vector<std::string> & userIntNames() const  { return userIntLabels_; }
      /// Return true if there is a user-defined int with a given name
      bool hasUserInt( const std::string & key ) const {
        return std::find(userIntLabels_.begin(), userIntLabels_.end(), key) != userIntLabels_.end();
      }
 
    protected:
      // reference back to the original object
      edm::Ptr<reco::Candidate> refToOrig_;

      /// vector of trigger matches
      TriggerObjectStandAloneCollection triggerObjectMatchesEmbedded_;

      /// vector of the efficiencies (values)
      std::vector<pat::LookupTableRecord> efficiencyValues_;
      /// vector of the efficiencies (names)
      std::vector<std::string> efficiencyNames_;

      /// Reference to a generator level particle
      std::vector<reco::GenParticleRef> genParticleRef_;
      /// vector to hold an embedded generator level particle
      std::vector<reco::GenParticle>    genParticleEmbedded_; 

      /// Overlapping test labels (only if there are any overlaps)
      std::vector<std::string> overlapLabels_;
      /// Overlapping items (sorted by distance)
      std::vector<reco::CandidatePtrVector> overlapItems_;

      /// User data object
      std::vector<std::string>      userDataLabels_;
      pat::UserDataCollection       userDataObjects_;
      // User float values
      std::vector<std::string>      userFloatLabels_;
      std::vector<float>            userFloats_;
      // User int values
      std::vector<std::string>      userIntLabels_;
      std::vector<int32_t>          userInts_;

    private:
      const pat::UserData *  userDataObject_(const std::string &key) const ;
  };




}

#endif
