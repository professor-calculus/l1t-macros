#!/bin/bash
cd /afs/cern.ch/work/a/atittert/private/CMSSW/CMSSW_8_0_9/src/
eval `scramv1 runtime -sh`
cd /afs/cern.ch/work/a/atittert/private/l1t-macros-rates/

mapfile -t myArray < folders.txt
for j in "${myArray[@]}"
do
	root -q -b -l "makeTurnons.cxx(\"$j\")";
done
