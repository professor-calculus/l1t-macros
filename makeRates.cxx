#include <string>
#include <vector>

#include "Plotting/tdrstyle.C"
#include "Event/TL1EventClass.h"
#include "Utilities/TL1Progress.C"
#include "Utilities/TL1DateTime.C"
#include "Plotting/TL1Rates.h"

std::vector<double> metBins();
void SetMyStyle(int palette, double rmarg, TStyle * myStyle);

void makeRates(std::string run, double cut_et, int cut_ieta)
{
    TStyle * myStyle(new TStyle(TDRStyle()));
    SetMyStyle(55, 0.08, myStyle);

    // Basic
    std::string sampleName = "Data";
    std::string sampleTitle = "2016 Data";
    //std::string triggerName = "SingleMu";
    //std::string triggerTitle = "Single Muon";
    std::string triggerName = "ZeroBias";
    std::string triggerTitle = "Zero Bias";
//    std::string puFilename = "/afs/cern.ch/work/a/atittert/L1SingleMuonRates/PU.root";


/*    std::string outDirBase = Form("%s",run.c_str());

    //std::string startstring = "/eos/cms/store/group/dpg_trigger/comm_trigger/L1Trigger/L1Menu2016/Stage2/Collision2016-wRECO-l1t-integration-v86p4/SingleMuon/crab_Collision2016-wRECO-l1t-integration-v86p4__";

    size_t pos = outDirBase.find("__");
    outDirBase.erase(0,pos + 2);							//Gets rid of all up to the __ part of the ntuples (in theory)

    std::string runstring = outDirBase;
    size_t pos2 = runstring.find("_");
    size_t endofstring = runstring.length();
    runstring.erase(pos2,endofstring);                      // NOT GOOD FOR AARON'S NTUPLES! Useful for when we have ntuples from
*/                                                          // usual /eos locations where run # preceeded by "__"
    
    std::string runstring = "281639";

    std::string outDirtot = "/afs/cern.ch/work/a/atittert/private/L1_ZB_emu_recalc_iet_4_ieta_26/aaron_new";

    //std::string run = "281613_161005";
    //std::string outDirtot = "/afs/cern.ch/work/a/atittert/private/SM_Rates_Post_Calibration_Emu";
    std::vector<std::string> puType = {"MET75","MET80","MET85","MET90","MET95","MET100","MET120"};
    //std::vector<std::string> puType = {"PU1","PU2","PU3","PU4","PU5","PU6","PU7","PU8","PU9","PU10","PU11","PU12","PU13","PU14","PU15","PU16","PU17","PU18","PU19","PU20","PU21","PU22","PU23","PU24","PU25","PU26","PU27","PU28","PU29","PU30","PU31","PU32","PU33","PU34","PU35","PU36","PU37","PU38","PU39","PU40","PU41","PU42","PU43","PU44"};
    std::vector<double> puBins = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50};
    //std::vector<double> puBins = {1,5,10,15,20,25,30,35,40,45,50,55,60,65,70,75,80};

    std::vector<std::string> inDir;
    // inDir.push_back("/afs/cern.ch/work/s/sbreeze/public/jets_and_sums/160704_SingleMu2016Bv1_l1t-int-v67p0");
    //inDir.push_back("root://eoscms.cern.ch//eos/cms/store/group/dpg_trigger/comm_trigger/L1Trigger/L1Menu2016/Stage2/Collision2016-wRECO-l1t-integration-v86p4/SingleMuon/crab_Collision2016-wRECO-l1t-integration-v86p4__281613_SingleMuon/161005_194102/0000");
    //inDir.push_back("root://eoscms.cern.ch//eos/cms/store/group/dpg_trigger/comm_trigger/L1Trigger/bundocka/ZeroBias/run281693_zbOld/160930_113228/0000");
    //inDir.push_back("root://eoscms.cern.ch//eos/cms/store/group/dpg_trigger/comm_trigger/L1Trigger/L1Menu2016/Stage2/Collision2016-wRECO-l1t-integration-v88p0/Commissioning/crab_Collision2016-wRECO-l1t-integration-v88p0__283171_Commissioning/161022_161012/0000");
    inDir.push_back(Form("root://eoscms.cern.ch/%s",run.c_str()));

    std::string outDir = outDirtot+"/"+TL1DateTime::GetDate()+"_"+sampleName+"_"+triggerName+"/rates/";
    TL1EventClass * event(new TL1EventClass(inDir, cut_et, cut_ieta));
    std::vector<TL1Rates*> rates;

    // l1 MET BE
    rates.emplace_back(new TL1Rates());
    rates[0]->SetX("Av_PU_BE","<PU>");
    rates[0]->SetXBins(puBins);
    rates[0]->SetOutName(triggerName+"_l1EmuMetBE");

    // l1 MET HF
    rates.emplace_back(new TL1Rates());
    rates[1]->SetX("Av_PU_HF","<PU> (HF)");
    rates[1]->SetXBins(puBins);
    rates[1]->SetOutName(triggerName+"_l1EmuMetHF");

    std::vector<int> metbins = {75,80,85,90,95,100,120,99999};

    for(auto it=rates.begin(); it!=rates.end(); ++it)
    {
        (*it)->SetSample(sampleName,sampleTitle);
        (*it)->SetTrigger(triggerName,triggerTitle);
        (*it)->SetRun(runstring);
        (*it)->SetOutDir(outDir);
        (*it)->SetPuType(puType);
        (*it)->SetPuBins(metbins);
//        (*it)->SetPuFile(puFilename);
        (*it)->InitPlots();
    }

    unsigned NEntries = event->GetPEvent()->GetNEntries();
    while( event->Next() )
    {
        unsigned position = event->GetPEvent()->GetPosition()+1;
        TL1Progress::PrintProgressBar(position, NEntries);

        int pu = event->GetPEvent()->fVertex->nVtx;

        double l1EmuMetBE = event->fRecalcL1Met;
        double l1EmuMetHF = event->fRecalcL1MetHF;          // Changed to recalc in order to compare with before

//	double l1EmuMetBE = event->fL1EmuMet;
//      double l1EmuMetHF = event->fL1EmuMetHF;

	rates[0]->Fill(pu, l1EmuMetBE, 0.0);

	rates[1]->Fill(pu, l1EmuMetHF, 0.0);
    }

    for(auto it=rates.begin(); it!=rates.end(); ++it)
        (*it)->DrawPlots();
}

std::vector<double> metBins()
{
    std::vector<double> temp;
    for(double bin=75.0; bin<=100.0; bin+=5.0) temp.push_back(bin);
    temp.push_back(120.0);
    temp.push_back(99999.0);
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
