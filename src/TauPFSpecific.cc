#include "DataFormats/PatCandidates/interface/TauPFSpecific.h"

pat::tau::TauPFSpecific::TauPFSpecific(const reco::PFTau &tau) :
    // Tau tag ingo
    PFTauTagInfoRef_(tau.pfTauTagInfoRef()),
    // Leading track
    leadPFChargedHadrCand_(tau.leadPFChargedHadrCand()),
    leadPFChargedHadrCandsignedSipt_(tau.leadPFChargedHadrCandsignedSipt()),
    // Signal cone
    selectedSignalPFCands_(tau.signalPFCands()), 
    selectedSignalPFChargedHadrCands_(tau.signalPFChargedHadrCands()), 
    selectedSignalPFNeutrHadrCands_(tau.signalPFNeutrHadrCands()), 
    selectedSignalPFGammaCands_(tau.signalPFGammaCands()),
    // Isolation cone
    selectedIsolationPFCands_(tau.isolationPFCands()), 
    selectedIsolationPFChargedHadrCands_(tau.isolationPFChargedHadrCands()), 
    selectedIsolationPFNeutrHadrCands_(tau.isolationPFNeutrHadrCands()), 
    selectedIsolationPFGammaCands_(tau.isolationPFGammaCands()),
    isolationPFChargedHadrCandsPtSum_(tau.isolationPFChargedHadrCandsPtSum()),
    isolationPFGammaCandsEtSum_(tau.isolationPFGammaCandsEtSum()),
    maximumHCALPFClusterEt_(tau.maximumHCALPFClusterEt())
{
}
