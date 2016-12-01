#ifndef TL1ET_IETA_PLOT_H
#define TL1ET_IETA_PLOT_H

#include <string>
#include <vector>
#include <sstream>

#include <TH1F.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TFile.h>
#include <TLatex.h>
#include <TStyle.h>

#include "TL1Plots.h"

class TL1et_ieta_plot : public TL1Plots
{
public:
    ~TL1et_ieta_plot();
    
    virtual void InitPlots();
    virtual void Fill(const double & xVal, const double & yVal, const int & nVtxVal);
    virtual void DrawPlots();
    TH2F * GetCumulative(TH2F * plot);
    void PlotE2(TH2F * plot, bool puOn);
    void DrawCmsStamp();
    
    void SetX(const std::string & xName, const std::string & xTitle);
    void SetXBins(const std::vector<double> & xBins);
    
private:
    std::vector<TH2F*> fPlot;
    TH1 *histMET = new TH1F("MET", "MET/GeV", 200, 0.0, 1000.0);
    TFile * fRootFile;
    
    std::string fXName, fXTitle;
    std::vector<double> fXBins;
    
};

void TL1et_ieta_plot::InitPlots()
{
    fRootFile = TFile::Open(Form("%s/et_ieta_plot_%s.root", this->GetOutDir().c_str(), this->GetOutName().c_str()), "RECREATE");
    fPlot.emplace_back(new TH1F(Form("rates_%s",fXName.c_str()),"", fXBins.size()-1,&(fXBins)[0]));
    fPlot.back()->Sumw2();
    fPlot.back()->SetDirectory(0);
    fPlot.back()->GetXaxis()->SetTitle(fXTitle.c_str());
    fPlot.back()->GetYaxis()->SetTitle("et / GeV");
    for(int ipu=0; ipu<this->GetPuType().size(); ++ipu)
    {
        fPlot.emplace_back(new TH1F(Form("rates_%s_%s",fXName.c_str(),this->GetPuType()[ipu].c_str()),"", fXBins.size()-1,&(fXBins)[0]));
        fPlot.back()->Sumw2();
        fPlot.back()->SetDirectory(0);
        fPlot.back()->GetXaxis()->SetTitle(fXTitle.c_str());
        fPlot.back()->GetYaxis()->SetTitle("et / GeV");
    }
    
}

void TL1et_ieta_plot::Fill(const double & xVal, const double & yVal, const int & nVtxVal)
{
    //fPlot[0]->Fill(xVal,yVal);
    
    for(int ipu=0; ipu<this->GetPuType().size(); ++ipu)
    {
        if( nVtxVal >= this->GetPuBins()[ipu] && nVtxVal < this->GetPuBins()[ipu] )
            fPlot[ipu]->Fill(xVal,yVal);
        //fPlot[ipu+1]->Divide(fPlot[0]);
    }
}

void TL1et_ieta_plot::DrawPlots()
{
    
    if( !(this->GetPuType().size() > 0) ) return;
    
    TCanvas * can2(new TCanvas(Form("can_%d",this->GetRnd()),""));
    TLegend * leg2(new TLegend(0.65,0.55,0.88,0.55+0.05*this->GetPuType().size()));
    for(int ipu=0; ipu<this->GetPuType().size(); ++ipu)
    {
        //fPlot[ipu+1]->Divide(fPlot[0]);
        
        //TH1F * fPuCumulative = GetCumulative(fPlot[ipu]);
        
//        bin1 = fPuCumulative->GetBinContent(1);
//        fPuCumulative->Scale(4.0e7/bin1);
//        this->SetColor(fPuCumulative, ipu, this->GetPuType().size());
        fRootFile->WriteTObject(fPlot[ipu]);
        
        PlotE2(fPlot[ipu], true);
        //can2->SetLogy();
        
//        std::stringstream entryName;
//        if( ipu<this->GetPuType().size()-1 ) entryName << this->GetPuBins()[ipu] << " #leq PU < " << this->GetPuBins()[ipu+1];
//        else entryName << this->GetPuBins()[ipu] << " #leq PU";
//        leg2->AddEntry(fPuCumulative, entryName.str().c_str());
//        entryName.str("");
    }
    //can2->SetLogy();
    can2->Update();
    DrawCmsStamp();
    can2->Update();
//    leg2->Draw();
//    can2->Update();
    
//    outName = Form("%s/et_iet_plot_%s_Bins.pdf", this->GetOutDir().c_str(), this->GetOutName().c_str());
//    can2->SaveAs(outName.c_str());
//    fRootFile->WriteTObject(can2);
}

TH2F * TL1et_ieta_plot::GetCumulative(TH2F * plot)
{
    std::string newName = Form("cumulative_%s",plot->GetName());
    TH1F * temp = (TH1F*)plot->Clone(newName.c_str());
    temp->SetDirectory(0);
    for(int i=0; i< plot->GetNbinsX()+1; ++i)
    {
        double content(0.0), error2(0.0);
        for(int j=0; j<i+1; ++j)
        {
            content += plot->GetBinContent(j);
            error2 += plot->GetBinError(j)*plot->GetBinError(j);
        }
        temp->SetBinContent(i,content);
        temp->SetBinError(i,TMath::Sqrt(error2));
    }
    return temp;
}

void TL1et_ieta_plot::PlotE2(TH2F * plot, bool puOn)
{
    //plot->SetLineColor(plot->GetLineColor()+15);
    //plot->SetFillColor(plot->GetLineColor()+15);
    //plot->SetMarkerStyle(0);
    //std::string extra = "";
    //if( puOn ) extra = "same";
    //plot->DrawCopy(Form("E2%s",extra.c_str()));
    
    //plot->SetFillStyle(0);
    //plot->SetLineColor(plot->GetLineColor()-15);
    //plot->SetFillStyle(0);
    //plot->SetLineWidth(2);
    plot->DrawCopy("colz");
    //plot->SetFillStyle(1001);
}

void TL1et_ieta_plot::DrawCmsStamp()
{
    TLatex * latex(new TLatex());
    latex->SetNDC();
    latex->SetTextFont(42);
    if( this->GetSampleName() == "Data" )
    {
        latex->DrawLatex(0.15,0.92,"#bf{CMS} #it{Preliminary} 2016 Data");
        latex->SetTextAlign(31);
        latex->DrawLatex(0.92,0.92,Form("%s (13 TeV)",this->GetRun().c_str()));
    }
    else
    {
        latex->DrawLatex(0.15,0.92,"#bf{CMS} #it{Simulation Preliminary}");
        latex->SetTextAlign(31);
        latex->DrawLatex(0.92,0.92,Form("%s (13 TeV)",this->GetSampleName().c_str()));
    }
    latex->SetTextAlign(32);
    latex->DrawLatex(0.82,0.25,this->GetAddMark().c_str());
}

void TL1et_ieta_plot::SetX(const std::string & xName, const std::string & xTitle)
{
    fXName = xName;
    fXTitle = xTitle;
}

void TL1et_ieta_plot::SetXBins(const std::vector<double> & xBins)
{
    fXBins = xBins;
}

#endif
