#include <TFile.h>
#include <TH1.h>
void DrawStuff()
{

//Open TFile and get histograms

  //TFile fhist("beam_Profile.root");
  TFile fhist_0_28_new("ZB_emu_recalc_iet_0.000000_ieta_28/aaron_new/20161116_Data_ZeroBias/rates/rates_ZeroBias_l1EmuMetBE.root");
  TFile fhist_0_27_new("ZB_emu_recalc_iet_0.000000_ieta_27/aaron_new/20161115_Data_ZeroBias/rates/rates_ZeroBias_l1EmuMetBE.root");
  TFile fhist_0_5_28_new("ZB_emu_recalc_iet_0.500000_ieta_28/aaron_new/20161123_Data_ZeroBias/rates/rates_ZeroBias_l1EmuMetBE.root");
  TFile fhist_0_5_27_new("ZB_emu_recalc_iet_0.500000_ieta_27/aaron_new/20161123_Data_ZeroBias/rates/rates_ZeroBias_l1EmuMetBE.root");
  TFile fhist_1_28_new("ZB_emu_recalc_iet_1.000000_ieta_28/aaron_new/20161123_Data_ZeroBias/rates/rates_ZeroBias_l1EmuMetBE.root");
  TFile fhist_1_27_new("ZB_emu_recalc_iet_1.000000_ieta_27/aaron_new/20161123_Data_ZeroBias/rates/rates_ZeroBias_l1EmuMetBE.root");
  TFile fhist_2_28_new("ZB_emu_recalc_iet_2.000000_ieta_28/aaron_new/20161123_Data_ZeroBias/rates/rates_ZeroBias_l1EmuMetBE.root");
  TFile fhist_2_27_new("ZB_emu_recalc_iet_2.000000_ieta_27/aaron_new/20161123_Data_ZeroBias/rates/rates_ZeroBias_l1EmuMetBE.root");
  TFile fhist_5_27_new("ZB_emu_recalc_iet_5.000000_ieta_28/aaron_new/20161116_Data_ZeroBias/rates/rates_ZeroBias_l1EmuMetBE.root");
  TFile fhist_5_28_new("ZB_emu_recalc_iet_5.000000_ieta_27/aaron_new/20161115_Data_ZeroBias/rates/rates_ZeroBias_l1EmuMetBE.root");

//  fhist.ls();

  TH1F *MET75_0_28 = nullptr;
  fhist_0_28_new.GetObject("rates_Av_PU_BE_MET75;1",MET75_0_28);
  int entries = MET75_0_28->GetEntries();

  TH1F *MET75_0_27 = nullptr;
  fhist_0_27_new.GetObject("rates_Av_PU_BE_MET75;1",MET75_0_27);
  int entries2 = MET75_0_27->GetEntries();

  TH1F *MET75_0_5_27 = nullptr;
  fhist_0_5_27_new.GetObject("rates_Av_PU_BE_MET75;1",MET75_0_5_27);
  int entries3 = MET75_0_5_27->GetEntries();

  TH1F *MET75_1_27 = nullptr;
  fhist_1_27_new.GetObject("rates_Av_PU_BE_MET75;1",MET75_1_27);
  int entries4 = MET75_1_27->GetEntries();

  MET75_0_28->DrawCopy();

  TCanvas * cRatio_no28 = new TCanvas("cRatio_no28", "cRatio_no28", 600, 600);

  MET75_0_27->Divide(MET75_0_27, MET75_0_28, entries2, entries);
  MET75_0_27->SetLineColor(kRed);
  MET75_0_27->SetMarkerColor(kRed);

  MET75_0_27->GetXaxis()->SetTitleOffset(-1);
  MET75_0_27->GetXaxis()->SetTitleSize(2);
  MET75_0_27->GetYaxis()->SetTitle("Ratio Rates(ieta up to 27) / rates(ieta up to 28)");
  MET75_0_27->GetYaxis()->SetTitleOffset(0);
  MET75_0_27->DrawCopy();
  cRatio_no28->Update();

// 0.5 GeV et cut, no tower 28
  MET75_0_5_27->Divide(MET75_0_27, MET75_0_28, entries3, entries);
  MET75_0_5_27->SetLineColor(kOrange);
  MET75_0_5_27->SetMarkerColor(kOrange);
  MET75_0_5_27->DrawCopy("same");
  cRatio_no28->Update();

// 1 GeV et cut, no tower 28
  MET75_1_27->Divide(MET75_0_27, MET75_0_28, entries4, entries);
  MET75_1_27->SetLineColor(kGreen);
  MET75_1_27->SetMarkerColor(kGreen);
  MET75_1_27->DrawCopy("same");
  cRatio_no28->Update();


  cRatio_no28->SaveAs("Ratios_Tower28Removed.pdf");

  //fhist.Close();
  fhist_0_28_new.Close();
  fhist_0_27_new.Close();
  fhist_0_5_28_new.Close();
  fhist_0_5_27_new.Close();
  fhist_1_28_new.Close();
  fhist_1_27_new.Close();
  fhist_2_28_new.Close();
  fhist_2_27_new.Close();

}
