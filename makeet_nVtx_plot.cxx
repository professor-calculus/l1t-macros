#include <string>
#include <vector>

#include "Plotting/tdrstyle.C"
#include "Event/TL1EventClass.h"
#include "Utilities/TL1Progress.C"
#include "Utilities/TL1DateTime.C"
#include "Plotting/TL1et_ieta_plot.h"

std::vector<double> metBins();
void SetMyStyle(int palette, double rmarg, TStyle * myStyle);

void makeet_nVtx_plot(std::string run, double cut_et, int cut_ieta)
{
    TStyle * myStyle(new TStyle(TDRStyle()));
    SetMyStyle(55, 0.08, myStyle);
    double eta_size;
    
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
    
    std::string outDirtot = "/afs/cern.ch/work/a/atittert/private/dev_rates_scripts/ZB_emu_recalc_iet_" + std::to_string(cut_et) + "_ieta_"+ std::to_string(cut_ieta) + "/aaron_new";
    
    
    //std::vector<std::string> puType = {"0nVtx10","10nVtx20","20nVtx30","30nVtx40","40nVtx50"};
    std::vector<std::string> puType = {"nVtx1","nVtx2","nVtx3","nVtx4","nVtx5","nVtx6","nVtx7","nVtx8","nVtx9","nVtx10","nVtx11","nVtx12","nVtx13","nVtx14","nVtx15","nVtx16","nVtx17","nVtx18","nVtx19","nVtx20","nVtx21","nVtx22","nVtx23","nVtx24","nVtx25","nVtx26","nVtx27","nVtx28","nVtx29","nVtx30"};
    std::vector<double> puBins = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42};
    //std::vector<double> puBins = {1,5,10,15,20,25,30,35,40,45,50,55,60,65,70,75,80};
    
    std::vector<double> eta_values = {0.,0.087,0.174,0.261,0.348,0.435,0.522,0.609,0.695,0.783,0.87,0.957,1.044,1.131,1.218,1.305,1.392,1.479,1.566,1.653,1.74,1.83,1.93,2.043,2.172,2.322,2.5,2.65,3.0};
    
    std::vector<double> etbins = {5,10,15,20,25,30,35,40,45,50,55,60,65,70,75,80};
    
    
    std::vector<std::string> inDir;
    
    
    inDir.push_back(Form("root://eoscms.cern.ch/%s",run.c_str()));
    
    std::string outDir = outDirtot+"/"+TL1DateTime::GetDate()+"_"+sampleName+"_"+triggerName+"/et_nVtx_plots/";
    TL1EventClass * event(new TL1EventClass(inDir, cut_et, cut_ieta));
    
    //std::vector<int> metbins = {75,80,85,90,95,100,120,99999};
    
    std::vector<TL1et_ieta_plot*> et_ieta_plots;
    
    // et vs ieta
    et_ieta_plots.emplace_back(new TL1et_ieta_plot());
    et_ieta_plots[0]->SetX("et_vs_nVtx","ieta");
    et_ieta_plots[0]->SetXBins(puBins);
    et_ieta_plots[0]->SetYBins(etbins);
    et_ieta_plots[0]->SetOutName(triggerName+"_et_vs_nVtx");
    
    // et density vs ieta
    et_ieta_plots.emplace_back(new TL1et_ieta_plot());
    et_ieta_plots[1]->SetX("et_density_vs_nVtx","ieta");
    et_ieta_plots[1]->SetXBins(puBins);
    et_ieta_plots[1]->SetYBins(etbins);
    et_ieta_plots[1]->SetOutName(triggerName+"_et_density_vs_nVtx");
    
    std::vector<int> metbins = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,99999};
    
    for(auto it=et_ieta_plots.begin(); it!=et_ieta_plots.end(); ++it)
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
    while( event->Next(cut_et, cut_ieta) )
    {
        unsigned position = event->GetPEvent()->GetPosition()+1;
        
        
        TL1Progress::PrintProgressBar(position, NEntries);
        
        int pu = event->GetPEvent()->fVertex->nVtx;
        
        
        std::vector< std::vector<double> > et_ieta = event->GetEtVsiEta();
        
        //	double l1EmuMetBE = event->fL1EmuMet;
        //  double l1EmuMetHF = event->fL1EmuMetHF;
        
        for(int j=0; j<et_ieta.size(); j++)
        {
            et_ieta_plots[0]->Fill(double(pu), et_ieta[j][0], et_ieta[j][1]);               // et vs nVtx
            
            if(et_ieta[j][1] < 29)
            {
                eta_size = eta_values[j+1] - eta_values[j];
                
                et_ieta_plots[1]->Fill(double(pu), et_ieta[j][0]/eta_size, et_ieta[j][1]);      // et_density vs nVtx
            }
        }
    }
    
    for(auto it=et_ieta_plots.begin(); it!=et_ieta_plots.end(); ++it)
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
