#include <string>
#include <vector>

#include "Plotting/tdrstyle.C"
#include "Event/TL1EventClass.h"
#include "Utilities/TL1Progress.C"
#include "Utilities/TL1DateTime.C"
#include "Plotting/TL1et_1d_plot.h"
#include "TH1.h"
#include "TFile.h"

std::vector<double> metBins();
void SetMyStyle(int palette, double rmarg, TStyle * myStyle);

void makeet_1d_plot(std::string run, double cut_et, int cut_ieta)
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
    
    std::string outDirtot = "/afs/cern.ch/work/a/atittert/private/dev_rates_scripts/Commissioning_et_ieta_nVtx_plots";
    
    
    
    std::vector<std::string> puType = {"0nVtx10","10nVtx20","20nVtx30","30nVtx40","40nVtx50","50nVtx60"};
    std::vector<std::string> puType2 = {"ieta3","ieta17","ieta27","ieta28","ieta29"};
    //std::vector<std::string> puType = {"PU1","PU2","PU3","PU4","PU5","PU6","PU7","PU8","PU9","PU10","PU11","PU12","PU13","PU14","PU15","PU16","PU17","PU18","PU19","PU20","PU21","PU22","PU23","PU24","PU25","PU26","PU27","PU28","PU29","PU30","PU31","PU32","PU33","PU34","PU35","PU36","PU37","PU38","PU39","PU40","PU41","PU42","PU43","PU44"};
    std::vector<double> puBins2 = {3,17,27,28,29,9999};
    std::vector<double> puBins = {10,20,30,40,50,60,9999};
    //std::vector<double> puBins = {1,5,10,15,20,25,30,35,40,45,50,55,60,65,70,75,80};
    
    std::vector<double> eta_values = {0.087, 0.087, 0.087, 0.087, 0.087, 0.087, 0.087, 0.087, 0.087, 0.087, 0.087, 0.087, 0.087, 0.087, 0.087, 0.087, 0.087, 0.087, 0.087, 0.087, 0.09, 0.1, 0.113, 0.129, 0.15, 0.178, 0.15, 0.35};
    
    std::vector<double> etbins = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60};
    
    std::vector<double> etbins_dens = {0,10,20,30,40,50,60,70,80,90,100,110,120,130,140,150,160,170,180,190,200,210,220,230,240,250,260,270,280,290,300,310,320,330,340,350,360,370,380,390,400,410,420,430,440,450,460,470,480,490,500,510,520,530,540,550,560,570,580,590,600};
    
    
    std::vector<std::string> inDir;
    
    
    inDir.push_back(Form("root://eoscms.cern.ch/%s",run.c_str()));
    
    std::string outDir = outDirtot+"/"+TL1DateTime::GetDate()+"_"+sampleName+"_"+triggerName+"/et_eta_plots/";
    std::string rootout = outDirtot+"/et_dens_histos.root";
    
    TL1EventClass * event(new TL1EventClass(inDir, cut_et, cut_ieta));
    
    //std::vector<int> metbins = {75,80,85,90,95,100,120,99999};
    
    
    TFile *g = TFile::Open(rootout.c_str(),"RECREATE");
    
    
//    typedef struct {double et_dens; int ieta, nVtx;} TOWERS;
    
//    static TOWERS towers;
    
    std::vector<TH1F*> nVtx10;
    std::vector<TH1F*> nVtx20;
    std::vector<TH1F*> nVtx30;
    std::vector<TH1F*> nVtx40;
    std::vector<TH1F*> nVtx50;
    std::vector<TH1F*> nVtx60;
    
//    std::vector<TH1*> ieta3;
//    std::vector<TH1*> ieta16;
//    std::vector<TH1*> ieta17;
//    std::vector<TH1*> ieta26;
//    std::vector<TH1*> ieta27;
//    std::vector<TH1*> ieta28;
    
//    for(int i=0; i<6; i++)
//    {
//        
//        ieta3.push_back(new TH1(Form("ieta3_%i",i),"ieta==3",200,0,1000));
//        ieta16.push_back(new TH1(Form("ieta16_%i",i),"ieta==16",200,0,1000));
//        ieta17.push_back(new TH1(Form("ieta17_%i",i),"ieta==17",200,0,1000));
//        ieta26.push_back(new TH1(Form("ieta26_%i",i),"ieta==26",200,0,1000));
//        ieta27.push_back(new TH1(Form("ieta27_%i",i),"ieta==27",200,0,1000));
//        ieta28.push_back(new TH1(Form("ieta28_%i",i),"ieta==28",200,0,1000));
//    }
    
    for(int k=1; k<29; k++)
    {
        nVtx10.push_back(new TH1F(Form("nVtx10_ieta%i",k),"0<nVtx<=10",200,0,400));
        nVtx20.push_back(new TH1F(Form("nVtx20_ieta%i",k),"10<nVtx<=20",200,0,400));
        nVtx30.push_back(new TH1F(Form("nVtx30_ieta%i",k),"20<nVtx<=30",200,0,400));
        nVtx40.push_back(new TH1F(Form("nVtx40_ieta%i",k),"30<nVtx<=40",200,0,400));
        nVtx50.push_back(new TH1F(Form("nVtx50_ieta%i",k),"40<nVtx<=50",200,0,400));
        nVtx60.push_back(new TH1F(Form("nVtx60_ieta%i",k),"50<nVtx<=60",200,0,400));
    }
    
    
    
    
    //TTree *outputtree = new TTree("TOWERS","Output Tree");
    
    //outputtree->Branch("Towers", &towers, "et_dens/D:ieta/I:nVtx");

    
    unsigned NEntries = event->GetPEvent()->GetNEntries();
    while( event->Next(cut_et, cut_ieta) )
    {
        unsigned position = event->GetPEvent()->GetPosition()+1;
        
        
        TL1Progress::PrintProgressBar(position, NEntries);
        
        int pu = event->GetPEvent()->fVertex->nVtx;
        //std::cout << pu << endl;
        
        std::vector< std::vector<double> > et_ieta = event->GetEtVsiEta();
        
        auto caloTowers = event->GetPEvent()->fCaloTowers;
        
        
        for(int j=0; j<et_ieta.size(); j++)
        {
            //et_ieta_plots[0]->Fill(et_ieta[j][1], et_ieta[j][0], double(pu));   // et vs ieta
            
            if(abs(et_ieta[j][1]) > 0 && abs(et_ieta[j][1]) < 29)
            {
                eta_size = eta_values[abs(et_ieta[j][1])-1];
                
                double et_dens = et_ieta[j][0]/eta_size;
                
                if(pu < 11)
                {
                    nVtx10[abs(et_ieta[j][1])-1]->Fill(et_dens);
                }
                else if(pu > 10 && pu < 21)
                {
                    nVtx20[abs(et_ieta[j][1])-1]->Fill(et_dens);
                }
                else if(pu > 20 && pu < 31)
                {
                    nVtx30[abs(et_ieta[j][1])-1]->Fill(et_dens);
                }
                else if(pu > 30 && pu < 41)
                {
                    nVtx40[abs(et_ieta[j][1])-1]->Fill(et_dens);
                }
                else if(pu > 40 && pu < 51)
                {
                    nVtx50[abs(et_ieta[j][1])-1]->Fill(et_dens);
                }
                else if(pu > 50 && pu < 61)
                {
                    nVtx60[abs(et_ieta[j][1])-1]->Fill(et_dens);
                }
                
                //towers.et_dens = et_dens;
                //towers.ieta = et_ieta[j][1];
                //towers.nVtx = pu;
                
                //outputtree->Fill();
                
                
                //et_ieta_plots[1]->Fill(et_ieta[j][1], et_dens, double(pu));     // et_density vs ieta
            }
        }
    }
    
    //outputtree->Write();
    
    for(int l=1; l<29; l++)
    {
        nVtx10[l]->Write();
        nVtx20[l]->Write();
        nVtx30[l]->Write();
        nVtx40[l]->Write();
        nVtx50[l]->Write();
        nVtx60[l]->Write();
    }
    
    g->Close();
    
    
    
    //for(auto it=et_ieta_plots.begin(); it!=et_ieta_plots.end(); ++it)
        //(*it)->DrawPlots();
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