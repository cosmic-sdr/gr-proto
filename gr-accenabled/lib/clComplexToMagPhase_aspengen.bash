#! /bin/bash


########################################
# OpenARC Option: ASPENModelGen        #
########################################
#ASPENModelGen=modelname=name:mode=number:entryfunction=entryfunc:complement=0|1:functions=foo,bar:postprocessing=number
#Generate ASPEN model for the input program; 
#modelname = [name of generated Aspen model]
#mode = 0 (skip the whole Aspen model gereation passes)
#       1 (analyze an input program and generated output C program annotated with Aspen directives)
#       2 (skip analysis pass and generate output Aspen model only with Aspen directives annotated in the input program)
#       3 (mode 1 + 2; analyze an input program, annotate it with Aspen directives, and generate output Aspen model (default))
#       4 (mode 3 + modify the input OpenACC program such that each compute region is selectively offloaded using HI_aspenpredic() function)
#entryfunction = [entry function to generate Aspen model]
#functions = [comma-separated list of functions]
#complement = 0 (ignore functions if specified in functions sub-option (default))
#             1 (ignore functions if not specified in functions sub-option)
#postprocessing = 0 (does not perform any Aspen IR flattening transformation)
#                 1 (inline Aspen kernels called within Aspen maps)
#                 2 (inline Aspen kernels + merge Aspen maps if directly nested (default))
########################################

inputSize1=8192
benchname="clComplexToMagPhase"
inputSource="${benchname}_kernel.c"
entryFunction="${benchname}_kernel"
runMode=3
postprocessing=0

function usage()
{
    echo "./${benchmark}_aspengen.bash"
    echo "List of options:"
    echo -e "\t-h --help"
    echo -e "\t-p=name --program=name (default: ${benchname})"
    echo -e "\t-i=data --input=data (default: ${inputSize1})"
    echo -e "\t-f=inputfile --file=inputfile (default: ${inputSource})"
    echo ""
}

while [ "$1" != "" ]; do
    PARAM=`echo $1 | awk -F= '{print $1}'`
    VALUE=`echo $1 | awk -F= '{print $2}'`
    case $PARAM in
        -h | --help)
            usage
            exit
            ;;
        -p | --program)
            benchname=${VALUE}
            ;;
        -i | --input)
            inputSize1=${VALUE}
            ;;
        -f | --file)
            inputSource=${VALUE}
            ;;
        *)
            echo "ERROR: unknown parameter \"$PARAM\""
            usage
            exit 1
            ;;
    esac
    shift
done

if [ "$openarc" = "" ] || [ ! -d "${openarc}" ]; then
    echo "Environment variable, openarc, should be set to the OpenARC home directory to use this script; exit"
    exit
fi

if [ ! -f "${openarc}/bin/openarc" ]; then
    echo "OpenARC executable, ${openarc}/bin/openarc, does not exist; run \"build.sh bin\" in the OpenARC root directory to build the executable; exit"
    exit
fi

${openarc}/bin/openarc -addIncludePath=${openarc}/openarcrt -outdir=aspen_output_${benchname} -SetAccEntryFunction=${entryFunction} -ASPENModelGen=mode=${runMode}:modelname=${benchname}:postprocessing=${postprocessing}:entryfunction=${entryFunction} -macro=GEN_ASPEN,__INPUTSIZE1__=${inputSize1} ${inputSource}

if [ -f "./aspen_output_${benchname}/${benchname}.aspen" ]; then
	cat "./aspen_output_${benchname}/${benchname}.aspen" | sed "s|kernel main|kernel ${benchname}|" > "${benchname}.aspen"
	#cp "./aspen_output_${benchname}/${benchname}.aspen" .
fi
