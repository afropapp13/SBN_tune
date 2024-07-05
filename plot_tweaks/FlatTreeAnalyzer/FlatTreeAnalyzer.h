#ifndef FlatTreeAnalyzer_h
#define FlatTreeAnalyzer_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TString.h>

class FlatTreeAnalyzer {

private:
	TFile* fFile;
	TString InputFile;
	TString InputBeam;
	TString InputCurrent;
	TString InputFlavor;
	TString OutputFile;

public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Int_t           Mode;
   Char_t          cc;
   Int_t           PDGnu;
   Float_t         Enu_true;
   Int_t           tgt;
   Int_t           tgta;
   Int_t           tgtz;
   Int_t           PDGLep;
   Float_t         ELep;
   Float_t         CosLep;
   Int_t           nfsp;
   Float_t         px[26];   //[nfsp]
   Float_t         py[26];   //[nfsp]
   Float_t         pz[26];   //[nfsp]
   Float_t         E[26];   //[nfsp]
   Int_t           pdg[26];   //[nfsp]
   Float_t         Weight;
   Double_t        fScaleFactor;
   Int_t           ninitp;
   Float_t         px_init[2];   //[ninitp]
   Float_t         py_init[2];   //[ninitp]
   Float_t         pz_init[2];   //[ninitp]
   Float_t         E_init[2];   //[ninitp]
   Int_t           pdg_init[2];   //[ninitp]
   Int_t           nvertp;
   Float_t         px_vert[18];   //[nvertp]
   Float_t         py_vert[18];   //[nvertp]
   Float_t         pz_vert[18];   //[nvertp]
   Float_t         E_vert[18];   //[nvertp]
   Int_t           pdg_vert[18];   //[nvertp]
   Float_t         Qsqrd;

   // List of branches
   TBranch        *b_Mode;   //!
   TBranch        *b_cc;   //!
   TBranch        *b_PDGnu;   //!
   TBranch        *b_Enu_true;   //!
   TBranch        *b_tgt;   //!
   TBranch        *b_tgta;   //!
   TBranch        *b_tgtz;   //!
   TBranch        *b_PDGLep;   //!
   TBranch        *b_ELep;   //!
   TBranch        *b_CosLep;   //!
   TBranch        *b_nfsp;   //!
   TBranch        *b_px;   //!
   TBranch        *b_py;   //!
   TBranch        *b_pz;   //!
   TBranch        *b_E;   //!
   TBranch        *b_pdg;   //!
   TBranch        *b_Weight;   //!
   TBranch        *b_fScaleFactor;   //!
   TBranch        *b_ninitp;   //!
   TBranch        *b_px_init;   //!
   TBranch        *b_py_init;   //!
   TBranch        *b_pz_init;   //!
   TBranch        *b_E_init;   //!
   TBranch        *b_pdg_init;   //!
   TBranch        *b_nvertp;   //!
   TBranch        *b_px_vert;   //!
   TBranch        *b_py_vert;   //!
   TBranch        *b_pz_vert;   //!
   TBranch        *b_E_vert;   //!
   TBranch        *b_pdg_vert;   //!
   TBranch        *b_Qsqrd;

   FlatTreeAnalyzer(TString infile, TString beam, TString current, TString flavor, TString outfile, TTree *tree=0);
   virtual ~FlatTreeAnalyzer();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef FlatTreeAnalyzer_cxx
FlatTreeAnalyzer::FlatTreeAnalyzer(TString InFile, TString TheBeam, TString TheCurrent, TString TheFlavor, TString OutFile, TTree *tree) : fChain(0) 
{

	InputFile = InFile; 
	InputBeam = TheBeam; 
	InputCurrent = TheCurrent; 
	InputFlavor = TheFlavor; 
	OutputFile = OutFile;

	if (tree == 0) {
		TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject(InFile);
		if (!f || !f->IsOpen()) {
			f = new TFile(InFile);
		}
		f->GetObject("FlatTree_VARS",tree);
		fFile = f;
	}

	Init(tree);

}

FlatTreeAnalyzer::~FlatTreeAnalyzer()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t FlatTreeAnalyzer::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t FlatTreeAnalyzer::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void FlatTreeAnalyzer::Init(TTree *tree)
{

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("Mode", &Mode, &b_Mode);
   fChain->SetBranchAddress("cc", &cc, &b_cc);
   fChain->SetBranchAddress("PDGnu", &PDGnu, &b_PDGnu);
   fChain->SetBranchAddress("Enu_true", &Enu_true, &b_Enu_true);
   fChain->SetBranchAddress("tgt", &tgt, &b_tgt);
   fChain->SetBranchAddress("tgta", &tgta, &b_tgta);
   fChain->SetBranchAddress("tgtz", &tgtz, &b_tgtz);
   fChain->SetBranchAddress("PDGLep", &PDGLep, &b_PDGLep);
   fChain->SetBranchAddress("ELep", &ELep, &b_ELep);
   fChain->SetBranchAddress("CosLep", &CosLep, &b_CosLep);
   fChain->SetBranchAddress("nfsp", &nfsp, &b_nfsp);
   fChain->SetBranchAddress("px", px, &b_px);
   fChain->SetBranchAddress("py", py, &b_py);
   fChain->SetBranchAddress("pz", pz, &b_pz);
   fChain->SetBranchAddress("E", E, &b_E);
   fChain->SetBranchAddress("pdg", pdg, &b_pdg);
   fChain->SetBranchAddress("Weight", &Weight, &b_Weight);
   fChain->SetBranchAddress("fScaleFactor", &fScaleFactor, &b_fScaleFactor);
   fChain->SetBranchAddress("ninitp", &ninitp, &b_ninitp);
   fChain->SetBranchAddress("px_init", px_init, &b_px_init);
   fChain->SetBranchAddress("py_init", py_init, &b_py_init);
   fChain->SetBranchAddress("pz_init", pz_init, &b_pz_init);
   fChain->SetBranchAddress("E_init", E_init, &b_E_init);
   fChain->SetBranchAddress("pdg_init", pdg_init, &b_pdg_init);
   fChain->SetBranchAddress("nvertp", &nvertp, &b_nvertp);
   fChain->SetBranchAddress("px_vert", px_vert, &b_px_vert);
   fChain->SetBranchAddress("py_vert", py_vert, &b_py_vert);
   fChain->SetBranchAddress("pz_vert", pz_vert, &b_pz_vert);
   fChain->SetBranchAddress("E_vert", E_vert, &b_E_vert);
   fChain->SetBranchAddress("pdg_vert", pdg_vert, &b_pdg_vert);
   fChain->SetBranchAddress("Q2", &Qsqrd, &b_Qsqrd);

   Notify();
}

Bool_t FlatTreeAnalyzer::Notify()
{

   return kTRUE;
}

void FlatTreeAnalyzer::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t FlatTreeAnalyzer::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef FlatTreeAnalyzer_cxx
