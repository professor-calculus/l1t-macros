#include <string>
#include <vector>

#include "Plotting/tdrstyle.C"
#include "Event/TL1EventClass.h"
#include "Utilities/TL1Progress.C"
#include "Utilities/TL1DateTime.C"
#include "Plotting/TL1Turnon.h"

vector<double> bins();
void SetMyStyle(int palette, double rmarg, TStyle * myStyle);

void makeJetTurnons(std::string run)
{
    TStyle * myStyle(new TStyle(TDRStyle()));
    SetMyStyle(55, 0.07, myStyle);

    // Basic
    std::string sampleName = "Data";
    std::string sampleTitle = "2016 Data";
    std::string triggerName = "SingleMu";
    std::string triggerTitle = "Single Muon";
    std::string puFilename = "/afs/cern.ch/work/s/sbreeze/l1tClasses/PUWeights/20160719_Data-SingleMu-2016Bv1_VBFHinv/pu_mcReweightedToData.root";


    std::string outDirBase = Form("%s",run.c_str());

    std::string startstring = "/eos/cms/store/group/dpg_trigger/comm_trigger/L1Trigger/L1Menu2016/Stage2/Collision2016-wRECO-l1t-integration-v86p4/SingleMuon/crab_Collision2016-wRECO-l1t-integration-v86p4__";

    std::string::size_type lol = outDirBase.find(startstring);

    if (lol != std::string::npos)
    {
     	outDirBase.erase(lol, startstring.length());
    }

    std::string outDirtot = "/afs/cern.ch/work/a/atittert/private/4_10_2016/"+outDirBase;

    //std::string run = "276243";
    //std::string outDirBase = "/afs/cern.ch/work/s/sbreeze/L1TriggerStudiesOutput";
    bool doFit = false;
    std::vector<std::string> puType = {"0PU12","13PU19","20PU"};
    std::vector<int> puBins = {0,13,20,999};

    std::vector<std::string> inDir;
    // inDir.push_back("/afs/cern.ch/work/s/sbreeze/public/jets_and_sums/160511_l1t-integration-v48p2/SingleMu/Ntuples");
    // inDir.push_back("/afs/cern.ch/work/s/sbreeze/public/jets_and_sums/160519_l1t-integration-v53p1/SingleMu_273301/Ntuples");
    // inDir.push_back("/afs/cern.ch/work/s/sbreeze/public/jets_and_sums/160602_r273450_SingleMu_l1t-int-v53p1");
    // inDir.push_back("/afs/cern.ch/work/s/sbreeze/public/jets_and_sums/160607_combinedRuns_SingleMu");
    // inDir.push_back("/afs/cern.ch/work/s/sbreeze/public/jets_and_sums/160704_SingleMu2016Bv1_l1t-int-v67p0");
    //inDir.push_back("/afs/cern.ch/work/s/sbreeze/public/jets_and_sums/160713_r276243_SingleMu_l1t-int-71p1/");
    inDir.push_back(Form("root://eoscms.cern.ch/%s",run.c_str()));

    std::string outDir = outDirtot+"/"+TL1DateTime::GetDate()+"_"+sampleName+"_"+"run-"+run+"_"+triggerName+"/TurnonsJets/";
    TL1EventClass * event(new TL1EventClass(inDir));
    std::vector<TL1Turnon*> turnons;

    // Jet Et - barrel
    // turnons.emplace_back(new TL1Turnon());
    // turnons[0]->SetSeeds({0., 36., 68., 128., 200.});
    // turnons[0]->SetXBins(bins());
    // turnons[0]->SetX("recoJetEt","Offline Jet E_{T} (GeV)");
    // turnons[0]->SetSeed("l1JetEt","L1 Jet E_{T}");
    // turnons[0]->SetOutName(triggerName+"_recoJetEt_l1JetEtSeeds_barrel");
    // turnons[0]->SetFit(doFit);
    // turnons[0]->SetAddMark("|#eta| < 1.479");

    // Jet Et - end cap
    // turnons.emplace_back(new TL1Turnon());
    // turnons[1]->SetSeeds({0., 36., 68., 128., 200.});
    // turnons[1]->SetXBins(bins());
    // turnons[1]->SetX("recoJetEt","Offline Jet E_{T} (GeV)");
    // turnons[1]->SetSeed("l1JetEt","L1 Jet E_{T}");
    // turnons[1]->SetOutName(triggerName+"_recoJetEt_l1JetEtSeeds_endcap");
    // turnons[1]->SetFit(doFit);
    // turnons[1]->SetAddMark("1.479 < |#eta| < 3.0");

    // Jet Et - barrel + endcap
    turnons.emplace_back(new TL1Turnon());
    turnons[0]->SetSeeds({0., 36., 68., 128., 200.});
    turnons[0]->SetXBins(bins());
    turnons[0]->SetX("recoJetEt","Offline Jet E_{T} (GeV)");
    turnons[0]->SetSeed("l1JetEt","L1 Jet E_{T}");
    turnons[0]->SetOutName(triggerName+"_recoJetEt_l1JetEtSeeds_barrel-endcap");
    turnons[0]->SetFit(doFit);
    turnons[0]->SetAddMark("|#eta| < 3.0");

    // Jet Et - HF
    turnons.emplace_back(new TL1Turnon());
    turnons[1]->SetSeeds({0., 36., 68., 128., 176.});
    turnons[1]->SetXBins(bins());
    turnons[1]->SetX("recoJetEt","Offline Jet E_{T} (GeV)");
    turnons[1]->SetSeed("l1JetEt","L1 Jet E_{T}");
    turnons[1]->SetOutName(triggerName+"_recoJetEt_l1JetEtSeeds_hf");
    turnons[1]->SetFit(doFit);
    turnons[1]->SetAddMark("|#eta| > 3.0");

    for(auto it=turnons.begin(); it!=turnons.end(); ++it)
    {
        (*it)->SetSample(sampleName,sampleTitle);
        (*it)->SetTrigger(triggerName,triggerTitle);
        (*it)->SetRun(run);
        (*it)->SetOutDir(outDir);
        //(*it)->SetPuType(puType);
        //(*it)->SetPuBins(puBins);
        //(*it)->SetPuFile(puFilename);
        (*it)->InitPlots();
    }

    unsigned NEntries = event->GetPEvent()->GetNEntries();
    while( event->Next() )
    {
        unsigned position = event->GetPEvent()->GetPosition()+1;
        TL1Progress::PrintProgressBar(position, NEntries);

        if( !event->fIsLeadingRecoJet ) continue;
        if( !event->fIsMatchedL1Jet ) continue;

        int pu = event->GetPEvent()->fVertex->nVtx;
        auto recoJet = event->GetPEvent()->fJets;

        double recoEt = recoJet->etCorr[event->fLeadingRecoJetIndex];
        double recoEta = recoJet->eta[event->fLeadingRecoJetIndex];
        double recoPhi = recoJet->phi[event->fLeadingRecoJetIndex];

        double l1Et = event->fL1JetEt[event->fMatchedL1JetIndex];
        double l1Eta = event->fL1JetEta[event->fMatchedL1JetIndex];
        double l1Phi = event->fL1JetPhi[event->fMatchedL1JetIndex];

        if( abs(recoEta) <= 1.479 )
        {
            //turnons[0]->Fill(recoEt, l1Et, pu);
            turnons[0]->Fill(recoEt, l1Et, pu);
        }
        else if( abs(recoEta) <= 3.0 )
        {
            //turnons[1]->Fill(recoEt, l1Et, pu);
            turnons[0]->Fill(recoEt, l1Et, pu);
        }
        else
            turnons[1]->Fill(recoEt, l1Et, pu);
    }

    for(auto it=turnons.begin(); it!=turnons.end(); ++it)
    {
        (*it)->DrawPlots();
        (*it)->DrawTurnons();
    }
}

vector<double> bins()
{
    vector<double> temp;
    for(double binLowerEdge= 0.0; binLowerEdge< 120.0; binLowerEdge+=10.0) temp.push_back(binLowerEdge);
    for(double binLowerEdge=120.0; binLowerEdge< 180.0; binLowerEdge+=20.0) temp.push_back(binLowerEdge);
    for(double binLowerEdge=180.0; binLowerEdge< 300.0; binLowerEdge+=40.0) temp.push_back(binLowerEdge);
    for(double binLowerEdge=300.0; binLowerEdge< 400.1; binLowerEdge+=100.0) temp.push_back(binLowerEdge);
//    for(double binLowerEdge= 40.0; binLowerEdge< 70.0; binLowerEdge+= 2.5) temp.push_back(binLowerEdge);
//    for(double binLowerEdge= 70.0; binLowerEdge<200.0; binLowerEdge+= 5.0) temp.push_back(binLowerEdge);
//    for(double binLowerEdge=200.0; binLowerEdge<300.0; binLowerEdge+=10.0) temp.push_back(binLowerEdge);
//    for(double binLowerEdge=300.0; binLowerEdge<400.1; binLowerEdge+=20.0) temp.push_back(binLowerEdge);
    return temp;
}

void SetMyStyle(int palette, double rmarg, TStyle * myStyle)
{
    myStyle->SetCanvasDefW(800);
    myStyle->SetCanvasDefH(600);
    myStyle->SetNumberContours(255);
    myStyle->SetPalette(palette);
    myStyle->SetPadRightMargin(rmarg);
    myStyle->cd();
}
