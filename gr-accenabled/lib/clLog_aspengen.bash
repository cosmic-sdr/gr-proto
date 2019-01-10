#! /bin/bash

if [ "$openarc" = "" ] || [ ! -d "${openarc}" ]; then
    echo "Environment variable, openarc, should be set to the OpenARC home directory to use this script; exit"
    exit
fi

if [ ! -f "${openarc}/bin/openarc" ]; then
    echo "OpenARC executable, ${openarc}/bin/openarc, does not exist; run \"build.sh bin\" in the OpenARC root directory to build the executable; exit"
    exit
fi

benchname="clLog"
inputSource="clLog_kernel.c"
entryFunction="log_kernel"
confFile="openarcConf_clLog.txt"
runMode=3
postprocessing=0

${openarc}/bin/openarc -addIncludePath=${openarc}/openarcrt -SetAccEntryFunction=${entryFunction} -ASPENModelGen=mode=${runMode}:modelname=${benchname}:postprocessing=${postprocessing}:entryfunction=${entryFunction} -macro=GEN_ASPEN ${inputSource}

