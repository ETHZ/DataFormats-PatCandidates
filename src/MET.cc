//
// $Id: MET.cc,v 1.3 2009/01/19 22:14:34 xs32 Exp $
//

#include "DataFormats/PatCandidates/interface/MET.h"


using namespace pat;


/// default constructor
MET::MET(): uncorInfo_(0) {
}


/// constructor from METType
MET::MET(const METType & aMET) : PATObject<METType>(aMET), uncorInfo_(0) {
}


/// constructor from ref to METType
MET::MET(const edm::RefToBase<METType> & aMETRef) : PATObject<METType>(aMETRef), uncorInfo_(0) {
}


/// destructor
MET::~MET() {
}


/// return the generated MET from neutrinos
const reco::GenMET * MET::genMET() const {
  return (genMET_.size() > 0 ? &genMET_.front() : 0 );
}

/// method to set the generated MET
void MET::setGenMET(const reco::GenMET & gm) {
  genMET_.clear();
  genMET_.push_back(gm);
}

/// method to set the MET Significance
void MET::setSignificance(const double & sgf) {
  significance_ = sgf;
}

//! return uncorrrection related stuff
uint MET::nCorrections() const { checkUncor_(); return nCorrections_; }

double MET::corEx(UncorectionType ix) const { checkUncor_(); return uncorInfo_[ix].corEx; }
double MET::corEy(UncorectionType ix) const { checkUncor_(); return uncorInfo_[ix].corEy; }
double MET::corSumEt(UncorectionType ix) const { checkUncor_(); return uncorInfo_[ix].corSumEt; }
double MET::uncorrectedPt(UncorectionType ix) const { checkUncor_(); return uncorInfo_[ix].pt; }
double MET::uncorrectedPhi(UncorectionType ix) const { checkUncor_(); return uncorInfo_[ix].phi; }


//! check and set transients
void MET::checkUncor_() const {
  if (uncorInfo_.size() == uncorrMAXN && oldPt_ == pt() ) return;

  oldPt_ = pt();
  std::vector<CorrMETData> corrs(mEtCorr());
  nCorrections_ = corrs.size();

  uncorInfo_.resize(uncorrMAXN);
  UncorectionType ix;

  //! ugly
  //! ALL
  ix = uncorrALL;
  uncorInfo_[ix] = UncorInfo();
  for (uint iC=0; iC < nCorrections_; ++iC){
    uncorInfo_[ix].corEx +=    corrs[iC].mex;
    uncorInfo_[ix].corEy +=    corrs[iC].mey;
    uncorInfo_[ix].corSumEt += corrs[iC].sumet;
  }
  setPtPhi_(uncorInfo_[ix]);

  //! JES
  ix = uncorrJES;
  uncorInfo_[ix] = UncorInfo();
  if (nCorrections_ >=1 ){
    uint iC = 0;
    uncorInfo_[ix].corEx +=    corrs[iC].mex;
    uncorInfo_[ix].corEy +=    corrs[iC].mey;
    uncorInfo_[ix].corSumEt += corrs[iC].sumet;
  }
  setPtPhi_(uncorInfo_[ix]);

  //! MUON
  ix = uncorrMUON;
  uncorInfo_[ix] = UncorInfo();
  if (nCorrections_ >=2 ){
    uint iC = 1;
    uncorInfo_[ix].corEx +=    corrs[iC].mex;
    uncorInfo_[ix].corEy +=    corrs[iC].mey;
    uncorInfo_[ix].corSumEt += corrs[iC].sumet;
  }
  setPtPhi_(uncorInfo_[ix]);

}

void MET::setPtPhi_(UncorInfo& uci) const {
  double lpx = px() - uci.corEx;
  double lpy = py() - uci.corEy;
  uci.pt = sqrt(lpx*lpx + lpy*lpy);
  uci.phi = atan2(lpy, lpx);  
}


void
pat::MET::setNumberOfMuons(const double & numberOfMuons)
{
  number_of_muons_ = numberOfMuons;
}

double
pat::MET::getNumberOfMuons() const
{
  return number_of_muons_;
}

void 
pat::MET::setNumberOfJets(const double & numberOfJets)
{
  number_of_jets_ = numberOfJets;
}

double
pat::MET::getNumberOfJets() const{
  return number_of_jets_;
}




void 
pat::MET::setNumberOfElectrons(const double & numberOfElectrons){
  number_of_electrons_ = numberOfElectrons;
}

double
pat::MET::getNumberOfElectrons() const{
  return number_of_electrons_;
}

