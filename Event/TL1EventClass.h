#ifndef TL1EVENTCLASS_H
#define TL1EVENTCLASS_H

#include <string>
#include <vector>

#include <TMath.h>
#include <TVector2.h>

#include "TL1PrimitiveEventClass.h"

class TL1EventClass
{
    public:
        TL1EventClass(std::vector<std::string> inDir, double cut_et, int cut_ieta);

        bool Next(double cut_et, int cut_ieta);
        void GetEntry(int i, double cut_et, int cut_ieta);
        void GetDerivatives(double cut_et, int cut_ieta);

        TL1PrimitiveEventClass const * GetPEvent() const;

        // Get L1
        double fL1Met, fL1Mht, fL1Ett, fL1Htt, fL1MetPhi, fL1MhtPhi;
        double fL1EmuMet, fL1EmuMht, fL1EmuEtt, fL1EmuHtt, fL1EmuMetPhi, fL1EmuMhtPhi;
        double fL1MetHF, fL1MhtHF, fL1EttHF, fL1HttHF, fL1MetPhiHF, fL1MhtPhiHF;
        double fL1EmuMetHF, fL1EmuMhtHF, fL1EmuEttHF, fL1EmuHttHF, fL1EmuMetPhiHF, fL1EmuMhtPhiHF;
        std::vector<double> fL1JetEt, fL1JetPhi, fL1JetEta;
    
        //et_ieta
        std::vector< std::vector<double> > TL1EventClass::GetEtVsiEta();
    
        // Filter flags
        bool fMuonFilterPassFlag, fMetFilterPassFlag;
        std::vector<bool> fJetFilterPassFlags;
        
        // Recalc L1 MET sums
        double fRecalcL1Met, fRecalcL1MetPhi;
        double fRecalcL1MetHF, fRecalcL1MetPhiHF;

        // Recalc L1 Ht/Et Sums
        double fRecalcL1Mht, fRecalcL1MhtPhi;
        int fNJetL1Mht;
        double fRecalcL1Ett;

        // Recalc Reco Ht/Et Sums
        double fRecalcRecoMht, fRecalcRecoMhtPhi, fRecalcRecoHtt;
        int fNJetRecoMht;
        bool fMhtPassFlag;
        double fRecalcRecoEtt;

        // Jets
        bool fIsLeadingRecoJet, fIsMatchedL1Jet;
        int fLeadingRecoJetIndex;
        int fMatchedL1JetIndex;

    private:
        TL1PrimitiveEventClass * fPrimitiveEvent;

        // Get L1
        void GetL1Jets();
        void GetL1Sums();
        void GetL1EmuSums();

        // Filters
        void MuonFilter();
        void JetFilter();
        void SumsFilter();

        // Recalc L1 MET sum
        void GetRecalcL1Met(double cut_et, int cut_ieta);

        // Recalc L1 Ht/Et Sums
        void GetRecalcL1Mht();
        void GetRecalcL1Ett();

        // Recalc Reco Ht/Et Sums
        void GetRecalcRecoHtSums();
        void GetRecalcRecoEtt();

        // Jets
        void GetLeadingRecoJet();
        void GetMatchedL1Jet();

};

TL1EventClass::TL1EventClass(std::vector<std::string> inDir, double cut_et, int cut_ieta) :
    fPrimitiveEvent(new TL1PrimitiveEventClass(inDir)),
    fMuonFilterPassFlag(true), fMetFilterPassFlag(true),
    fMhtPassFlag(true),
    fIsLeadingRecoJet(true), fIsMatchedL1Jet(true)
{
}

bool TL1EventClass::Next(double cut_et, int cut_ieta)
{
    bool isNext = fPrimitiveEvent->Next();
    this->GetDerivatives(cut_et, cut_ieta);
    return isNext;
}

void TL1EventClass::GetEntry(int i, double cut_et, int cut_ieta)
{
    fPrimitiveEvent->GetEntry(i);
    this->GetDerivatives(cut_et, cut_ieta);
}

void TL1EventClass::GetDerivatives(double cut_et, int cut_ieta)
{
    // L1
    bool isUpgrade = fPrimitiveEvent->fIsUpgrade;
    if( isUpgrade ) this->GetL1Jets();
    if( isUpgrade ) this->GetL1Sums();
    if( fPrimitiveEvent->fIsEmuUpgrade ) this->GetL1EmuSums();

    // Filter
    bool isJetReco = fPrimitiveEvent->fIsJetReco;
    if( fPrimitiveEvent->fIsMuonReco ) this->MuonFilter();
    if( isJetReco ) this->JetFilter();
    if( fPrimitiveEvent->fIsMetFilterReco ) this->SumsFilter();

    // Recalc
    if( fPrimitiveEvent->fIsCaloTower ) this->GetRecalcL1Met(cut_et, cut_ieta);
    //this->GetRecalcL1Mht();
    //this->GetRecalcL1Ett();
    
    //this->GetRecalcRecoHtSums();
    //this->GetRecalcRecoEtt();

    // Jets
    if( isJetReco ) this->GetLeadingRecoJet();
    if( isJetReco ) this->GetMatchedL1Jet();
}

TL1PrimitiveEventClass const * TL1EventClass::GetPEvent() const
{
    return fPrimitiveEvent;
}

void TL1EventClass::GetL1Jets()
{
    fL1JetEt.clear();
    fL1JetEta.clear();
    fL1JetPhi.clear();
    for(unsigned iJet=0; iJet<fPrimitiveEvent->fUpgrade->nJets; ++iJet)
    {
        if( fPrimitiveEvent->fUpgrade->jetBx[iJet] == 0 )
        {
            fL1JetEt.push_back(fPrimitiveEvent->fUpgrade->jetEt[iJet]);
            fL1JetEta.push_back(fPrimitiveEvent->fUpgrade->jetEta[iJet]);
            fL1JetPhi.push_back(fPrimitiveEvent->fUpgrade->jetPhi[iJet]);
        }
    }
}

void TL1EventClass::GetL1Sums()
{
    auto upgrades = fPrimitiveEvent->fUpgrade;
    for(int iter=0; iter<upgrades->nSums; ++iter)
    {
        double et = upgrades->sumEt[iter];
        double phi = upgrades->sumPhi[iter];
        if( upgrades->sumBx[iter] == 0 )
        {
            int sumType = upgrades->sumType[iter];
            if(sumType == l1t::EtSum::EtSumType::kTotalEt)   fL1Ett = et;
            if(sumType == l1t::EtSum::EtSumType::kTotalHt)   fL1Htt = et;
            if(sumType == l1t::EtSum::EtSumType::kMissingEt)
            {
                fL1Met = et;
                fL1MetPhi = phi;
            }
            if(sumType == l1t::EtSum::EtSumType::kMissingHt)
            {
                fL1Mht = et;
                fL1MhtPhi = phi;
            }
            if(sumType == l1t::EtSum::EtSumType::kTotalEtHF) fL1EttHF = et;
            if(sumType == l1t::EtSum::EtSumType::kTotalHtHF) fL1HttHF = et;
            if(sumType == l1t::EtSum::EtSumType::kMissingEtHF)
            {
                fL1MetHF = et;
                fL1MetPhiHF = phi;
            }
            if(sumType == l1t::EtSum::EtSumType::kMissingHtHF)
            {
                fL1MhtHF = et;
                fL1MhtPhiHF = phi;
            }
        }
    }
}

void TL1EventClass::GetL1EmuSums()
{
    auto emuUpgrades = fPrimitiveEvent->fEmuUpgrade;
    for(int iter=0; iter<emuUpgrades->nSums; ++iter)
    {
        double et = emuUpgrades->sumEt[iter];
        double phi = emuUpgrades->sumPhi[iter];

        int sumType = emuUpgrades->sumType[iter];
        if(sumType == l1t::EtSum::EtSumType::kTotalEt)   fL1EmuEtt = et;
        if(sumType == l1t::EtSum::EtSumType::kTotalHt)   fL1EmuHtt = et;
        if(sumType == l1t::EtSum::EtSumType::kMissingEt)
        {
            fL1EmuMet = et;
            fL1EmuMetPhi = phi;
        }
        if(sumType == l1t::EtSum::EtSumType::kMissingHt)
        {
            fL1EmuMht = et;
            fL1EmuMhtPhi = phi;
        }
        if(sumType == l1t::EtSum::EtSumType::kTotalEtHF) fL1EmuEttHF = et;
        if(sumType == l1t::EtSum::EtSumType::kTotalHtHF) fL1EmuHttHF = et;
        if(sumType == l1t::EtSum::EtSumType::kMissingEtHF)
        {
            fL1EmuMetHF = et;
            fL1EmuMetPhiHF = phi;
        }
        if(sumType == l1t::EtSum::EtSumType::kMissingHtHF)
        {
            fL1EmuMhtHF = et;
            fL1EmuMhtPhiHF = phi;
        }
    }
}

void TL1EventClass::MuonFilter()
{
    bool pass(false);
    for(unsigned jMuon=0; jMuon<fPrimitiveEvent->fMuons->nMuons; ++jMuon)
    {
        double pt = fPrimitiveEvent->fMuons->pt[jMuon];
        double iso = fPrimitiveEvent->fMuons->iso[jMuon];
        double isLoose = fPrimitiveEvent->fMuons->isLooseMuon[jMuon];
        if( pt>=20.0 && iso<=0.1 && isLoose==1.0 )
            pass = true;
    }
    fMuonFilterPassFlag = pass;
}

void TL1EventClass::JetFilter()
{
    fJetFilterPassFlags.clear();
    for(unsigned iJet=0; iJet<fPrimitiveEvent->fJets->nJets; ++iJet)
    {
        auto recoJets = fPrimitiveEvent->fJets;

        // Muon mult filter
        int muMult  = recoJets->muMult[iJet];
        if( muMult != 0 ){ fJetFilterPassFlags.push_back(false); continue; }

        // No hf jets
        double eta  = recoJets->eta[iJet];
        if( TMath::Abs(eta) > 3. ){ fJetFilterPassFlags.push_back(false); continue; }

        // nhef
        double nhef = recoJets->nhef[iJet];
        if( nhef >= 0.9 ){ fJetFilterPassFlags.push_back(false); continue; }

        // pef
        double pef  = recoJets->pef[iJet];
        if( pef >= 0.9 ){ fJetFilterPassFlags.push_back(false); continue; }

        // mef
        double mef  = recoJets->mef[iJet];
        if( mef >= 0.8 ){ fJetFilterPassFlags.push_back(false); continue; }

        // sumMult
        int sumMult = recoJets->chMult[iJet] + recoJets->chMult[iJet] + recoJets->elMult[iJet];
        int nhMult  = recoJets->nhMult[iJet];
        int phMult  = recoJets->phMult[iJet];
        if( sumMult+nhMult+phMult <= 1 ){ fJetFilterPassFlags.push_back(false); continue; }

        if( TMath::Abs(eta)>2.4 ){ fJetFilterPassFlags.push_back(true); continue; }

        // sumMult
        if( sumMult <= 0 ){ fJetFilterPassFlags.push_back(false); continue; }

        // chef
        double chef = recoJets->chef[iJet];
        if( chef <= 0 ){ fJetFilterPassFlags.push_back(false); continue; }

        // eef
        double eef  = recoJets->eef[iJet];
        if( eef >= 0.9 ){ fJetFilterPassFlags.push_back(false); continue; }

        // pass
        fJetFilterPassFlags.push_back(true);
    }
    if( fJetFilterPassFlags.size() != fPrimitiveEvent->fJets->nJets )
        std::cerr << "ERROR: Size of fJetFilterPassFlags does not match the number of reco Jets in fPrimitiveEvent" << std::endl;
}

void TL1EventClass::SumsFilter()
{
    fMetFilterPassFlag = fPrimitiveEvent->fMetFilters->hbheNoiseFilter;
}

void TL1EventClass::GetRecalcL1Mht()
{
    TVector2 * mht(new TVector2(0.0,0.0));
    int jetCount=0;
    for(unsigned iJet=0; iJet<fL1JetEt.size(); ++iJet)
    {
        if( TMath::Abs(fL1JetEta[iJet]) > 3.0 ) continue;
        if( fL1JetEt[iJet] < 30.0 ) continue;
        TVector2 * jet(new TVector2(0.0,0.0));
        jet->SetMagPhi(fL1JetEt[iJet], fL1JetPhi[iJet]);
        ++jetCount;
        *(mht) -= *(jet);
    }
    fRecalcL1Mht = mht->Mod();
    fRecalcL1MhtPhi = mht->Phi();
    fNJetL1Mht = jetCount;
}

void TL1EventClass::GetRecalcL1Ett()
{
    int iEtaMax = 28;
    Double_t sumEt = 0.0;
    int jetCount = 0;
    for(int jTower=0; jTower<fPrimitiveEvent->fCaloTowers->nTower; ++jTower)
    {
        int ieta = fPrimitiveEvent->fCaloTowers->ieta[jTower];
        int iet  = fPrimitiveEvent->fCaloTowers->iet[jTower];
        if( TMath::Abs(ieta) <= iEtaMax )
        {
            sumEt += 0.5 * (double)iet;
            ++jetCount;
        }
    }
    fRecalcL1Ett = sumEt;
    //fNJetsL1Ett = jetCount;
}

void TL1EventClass::GetRecalcL1Met(double cut_et, int cut_ieta)
{
    TVector2 met(0.0,0.0), metHF(0.0,0.0);
    auto caloTowers = fPrimitiveEvent->fCaloTowers;
    int ieta(0);
    double phi(0.0), et(0.0);
    for(int jTower=0; jTower<caloTowers->nTower; ++jTower)
    {
        ieta = caloTowers->ieta[jTower];
        phi = (TMath::Pi()/36.0) * (double)caloTowers->iphi[jTower];
        et = 0.5 * (double)caloTowers->iet[jTower];
        TVector2 temp(0.0,0.0);
        temp.SetMagPhi(et,phi);

        if( abs(ieta) <= cut_ieta && et > cut_et ) met -= temp;
        if( et > cut_et ) metHF -= temp;
    }
    fRecalcL1Met = met.Mod();
    fRecalcL1MetPhi = met.Phi();
    fRecalcL1MetHF = metHF.Mod();
    fRecalcL1MetPhiHF = metHF.Phi();
}

std::vector< std::vector<double> > TL1EventClass::GetEtVsiEta()
{
    auto caloTowers = fPrimitiveEvent->fCaloTowers;
    int ieta(0);
    double et;
    std::vector< vector<double> > et_vs_ieta;
    vector<double> et_ieta;
    et_ieta.push_back(et);
    et_ieta.push_back(ieta);
    double phi(0.0);
    for(int jTower=0; jTower<caloTowers->nTower; ++jTower)
    {
        ieta = caloTowers->ieta[jTower];
        phi = (TMath::Pi()/36.0) * (double)caloTowers->iphi[jTower];
        et = 0.5 * (double)caloTowers->iet[jTower];
        et_ieta[0] = et;
        et_ieta[1] = ieta;
        et_vs_ieta.push_back(et_ieta);
    }
    return et_vs_ieta;
}

void TL1EventClass::GetRecalcRecoHtSums()
{
    TVector2 * mht(new TVector2(0.,0.));
    double jetEt(0.0);
    unsigned jetCount(0);
    fMhtPassFlag = true;
    for(int iJet=0; iJet<fPrimitiveEvent->fJets->nJets; ++iJet)
    {
        bool passJetFilter = fJetFilterPassFlags[iJet];
        if( fPrimitiveEvent->fJets->etCorr[iJet] < 30.0 ) continue;
        if( !passJetFilter )
        {
            fMhtPassFlag = false;
            break;
        }
        TVector2 * jet(new TVector2(0.,0.));
        jet->SetMagPhi(fPrimitiveEvent->fJets->etCorr[iJet], fPrimitiveEvent->fJets->phi[iJet]);
        jetEt += fPrimitiveEvent->fJets->etCorr[iJet];
        ++jetCount;
        *(mht) -= *(jet);
    }
    fRecalcRecoMht = mht->Mod();
    fRecalcRecoMhtPhi = mht->Phi();
    fRecalcRecoHtt = jetEt;
    fNJetRecoMht = jetCount;
}

void TL1EventClass::GetRecalcRecoEtt()
{
    double jetEt(0.0);
    int jetCount = 0;
    for(int iJet=0; iJet<fPrimitiveEvent->fJets->nJets; ++iJet)
    {
        if( fPrimitiveEvent->fJets->etCorr[iJet] >= 30.0 )
        {
            jetEt += fPrimitiveEvent->fJets->etCorr[iJet];
            ++jetCount;
        }
    }
    fRecalcRecoEtt = jetEt;
    //fNJetsRecoEtt = jetCount;
}

void TL1EventClass::GetLeadingRecoJet()
{
    int iLeadingReco = 0;
    double leadingRecoEt = 10.0;
    fIsLeadingRecoJet = false;
    for(int iReco=0; iReco<fJetFilterPassFlags.size(); ++iReco)
    {
        // If central jet, require tightLepVeto and muMult==0
        auto recoJet = fPrimitiveEvent->fJets;
        if( TMath::Abs(recoJet->eta[iReco])<=3.0 )
            if( !fJetFilterPassFlags[iReco] ) continue;
        if( recoJet->etCorr[iReco] < leadingRecoEt ) continue;
        iLeadingReco = iReco;
        leadingRecoEt = recoJet->etCorr[iReco];
    }
    if( leadingRecoEt > 10.0 )
    {
        fIsLeadingRecoJet = true;
        fLeadingRecoJetIndex = iLeadingReco;
    }
}

void TL1EventClass::GetMatchedL1Jet()
{
    // No leading jet, no match
    fIsMatchedL1Jet = false;
    if( !fIsLeadingRecoJet ) return;

    // Keep track of the current matched l1 jet. Set minDeltaR to 0.3
    int iMatchedL1 = 0;
    double minDeltaR = 0.3;

    // Get Leading jet parameters
    auto recoJet = fPrimitiveEvent->fJets;
    double leadingRecoJetEta = recoJet->eta[fLeadingRecoJetIndex]; 
    double leadingRecoJetPhi = recoJet->phi[fLeadingRecoJetIndex];

    for(int iL1=0; iL1<fL1JetEt.size(); ++iL1)
    {
        // Get l1 jet parameters
        double l1JetEta = fL1JetEta[iL1];
        double l1JetPhi = fL1JetPhi[iL1];

        // Check dEta > dR
        double dEta = leadingRecoJetEta - l1JetEta;
        if( dEta > minDeltaR ) continue;
        
        // Check dPhi > dR
        double dPhi = leadingRecoJetPhi - l1JetPhi;
        if( dPhi > minDeltaR ) continue;

        // Check dR < mindR
        double dR = TMath::Sqrt(dEta*dEta + dPhi*dPhi);
        if( dR < minDeltaR )
        {
            // Update new minDeltaR and matched L1 Jet
            minDeltaR = dR;
            iMatchedL1 = iL1;
        }
    }
    // If minDeltaR has changed then we have a match
    if( minDeltaR < 0.3 )
    {
        fIsMatchedL1Jet = true;
        fMatchedL1JetIndex = iMatchedL1;
    }
}

#endif
