#!/bin/bash
directory=$PWD
cd /afs/cern.ch/work/a/atittert/private/CMSSW/CMSSW_8_0_19/src/
eval `scramv1 runtime -sh`
cd /afs/cern.ch/work/a/atittert/private/emu-recalc-l1t-macros-rates_iet_4_ieta_26

root -q -b -l "makeRates.cxx(\"/eos/cms/store/group/dpg_trigger/comm_trigger/L1Trigger/bundocka/ZeroBias/run281693_zb/161007_103707/0000\")"
