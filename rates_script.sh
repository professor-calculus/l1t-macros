#!/bin/bash
cd /afs/cern.ch/work/a/atittert/private/CMSSW/CMSSW_8_0_19/src/
eval `scramv1 runtime -sh`
cd /afs/cern.ch/work/a/atittert/private/emu-recalc-l1t-macros-rates/

root -q -b -l "makeRates.cxx";
