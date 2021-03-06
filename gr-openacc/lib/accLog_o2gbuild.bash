#! /bin/bash

inputSize1=8192
benchname="accLog"
inputSource="${benchname}_kernel.c"
entryFunction="${benchname}_kernel"

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

if [ "$openarcinstall" = "" ] || [ ! -d "${openarcinstall}" ]; then
    echo "Environment variable, openarcinstall, should be set to the OpenARC install directory to use this script; exit"
    exit
fi

if [ ! -f "${openarcinstall}/bin/openarc" ]; then
    echo "OpenARC executable, ${openarcinstall}/bin/openarc, does not exist; run \"build.sh bin\" in the OpenARC root directory to build the executable; exit"
    exit
fi

${openarcinstall}/bin/openarc -addIncludePath=${openarcinstall}/openarcrt -macro=__INPUTSIZE1__=${inputSize1} -gpuConfFile=openarcConf_${benchname}.txt ${inputSource}
