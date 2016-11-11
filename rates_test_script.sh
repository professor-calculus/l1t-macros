#!/bin/bash
cd /afs/cern.ch/work/a/atittert/private/CMSSW/CMSSW_8_0_19/src/
eval `scramv1 runtime -sh`
cd /afs/cern.ch/work/a/atittert/private/emu-recalc-l1t-macros-rates_iet_4

root -q -b -l "makeRates.cxx(\"/eos/cms/store/group/dpg_trigger/comm_trigger/L1Trigger/L1Menu2016/Stage2/Collision2016-wRECO-l1t-integration-v88p0/Commissioning/crab_Collision2016-wRECO-l1t-integration-v88p0__283171_Commissioning/161022_161012/0000\")"
