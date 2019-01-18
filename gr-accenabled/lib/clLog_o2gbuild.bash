#! /bin/bash

inputSize1=8192
benchname="clLog"
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

if [ "$openarc" = "" ] || [ ! -d "${openarc}" ]; then
    echo "Environment variable, openarc, should be set to the OpenARC home directory to use this script; exit"
    exit
fi

if [ ! -f "${openarc}/bin/openarc" ]; then
    echo "OpenARC executable, ${openarc}/bin/openarc, does not exist; run \"build.sh bin\" in the OpenARC root directory to build the executable; exit"
    exit
fi

${openarc}/bin/openarc -addIncludePath=${openarc}/openarcrt -macro=__INPUTSIZE1__=${inputSize1} -gpuConfFile=openarcConf_${benchname}.txt acc_helper.c  ${inputSource}
