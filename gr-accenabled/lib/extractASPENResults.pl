#! /usr/bin/perl

$argn = @ARGV;
if ($argn == 7) { 
	$benchname = "$ARGV[0]";
	$sweep_begin = "$ARGV[1]";
	$sweep_stride = "$ARGV[2]";
	$sweep_end = "$ARGV[3]";
	$rsc_count = "$ARGV[4]";
	$gprof_predict = "$ARGV[5]";
	$inputDevice = "$ARGV[6]";
} elsif ($argn == 4) { 
	$benchname = "$ARGV[0]";
	$sweep_begin = "$ARGV[1]";
	$sweep_stride = "$ARGV[2]";
	$sweep_end = "$ARGV[3]";
	$rsc_count = 1;
	$gprof_predict = 0;
	$inputDevice = "p100";
} elsif ($argn == 1) {
	$benchname = "$ARGV[0]";
	$sweep_begin = 64;
	$sweep_stride = 2;
	$sweep_end = 64;
	$rsc_count = 1;
	$gprof_predict = 0;
	$inputDevice = "p100";
} else {
    print STDOUT "$#ARGV\n";
    print STDOUT "====> Incorrect number of inputs! \n";
    print STDOUT "====> Usage:\n";
    print STDOUT "      extractASPENResults.pl benchname \n";
    print STDOUT "      or\n";
    print STDOUT "      extractASPENResults.pl benchname sweep_begin sweep_stride sweep_end\n";
    print STDOUT "      or\n";
    print STDOUT "      extractASPENResults.pl benchname sweep_begin sweep_stride sweep_end rsc_count gprof_predict device\n";
    print STDOUT "\n";
    print STDOUT "      //supported devices: k40 and p100\n";
    exit;   
}

print STDOUT "Input Benchmark: $ARGV[0]\n";
if ($rsc_count != 0) {
	print STDOUT "Extract resource counts.\n";
}
if ($gprof_predict != 0) {
	print STDOUT "Extract runtime predictions.\n";
}


@inputKernelList = ( "main" );

$KernelListSize = @inputKernelList;

###########################
# Extract resource counts #
###########################

if ( ${rsc_count} == 1 ) {

$inputFile = "${benchname}_rsc_predicted.aspenlog";
$outputFile = "${benchname}_ASPEN_RSC_output.log";

@resourceTypeList = ( "Raw random loads for kernel", "Raw loads for kernel", "Raw random stores for kernel", "Raw stores for kernel", "Raw simd flops for kernel", "Raw flops for kernel", "Raw integer ops for kernel");

if (-e $inputFile) {

print STDOUT "Input file ${inputFile}\n";
print STDOUT "Output file ${outputFile}\n";
open(INFO, ">$outputFile");

print INFO "InputSize\tIrregLoad\tRegLoad\tLoadAll\tIrregStore\tRegStore\tStoreAll\tIrregBytes\tRegBytes\tBytesAll\tSIMDFlops\tScalarFlops\tFlopsAll\tIntops\tFlops/Bite\tFlops/Input\tIntops/Input\tLoads/Input\tStores/Input\n";

for ($k = 0; $k < ${KernelListSize}; ++$k) {
	$inputKernel = $inputKernelList[$k];
	$m = 0;
	for ($size = ${sweep_begin}; $size <= ${sweep_end}; $size = $size  * 2) {
		@Results = ();
		@Bytes = ();
		for ($i = 0; $i < 3; ++$i) {
			$resourceType1 = $resourceTypeList[2 * $i];
			$resourceType2 = $resourceTypeList[2 * $i + 1];

			@Input_lines = `grep "${resourceType1} '${inputKernel}'" $inputFile`;
			@line = split(/\s+/, $Input_lines[$m]);
			$value1 = $line[$#line];           # refers to the last element of array @line

			@Input_lines = `grep "${resourceType2} '${inputKernel}'" $inputFile`;
			@line = split(/\s+/, $Input_lines[$m]);
			$value2 = $line[$#line];           # refers to the last element of array @line

			if( $i == 2 ) {
				$resourceType3 = $resourceTypeList[2 * $i + 2];
				@Input_lines = `grep "${resourceType3} '${inputKernel}'" $inputFile`;
				@line = split(/\s+/, $Input_lines[$m]);
				$value4 = $line[$#line];           # refers to the last element of array @line
				$value2 = $value2 - $value4;
				$value3 = $value2 - $value1;
			} else {
				$value3 = $value2 - $value1;
			}

			push(@Results, $value1);
			push(@Results, $value3);
			push(@Results, $value2);
			if( $i == 2 ) {
				push(@Results, $value4);
			}
		}

		push(@Bytes, $Results[0] + $Results[3]);
		push(@Bytes, $Results[1] + $Results[4]);
		push(@Bytes, $Results[2] + $Results[5]);

		$flopsperbite = $Results[8]/$Bytes[2];
		$flopsperibite = $Results[8]/$size;
		$intopsperibite = $Results[9]/$size;
		$loadsperibite = $Results[2]/$size;
		$storesperibite = $Results[5]/$size;
		#print INFO "$inputKernel\t";
		print INFO "$size\t";
		print INFO "$Results[0]\t$Results[1]\t$Results[2]\t";
		print INFO "$Results[3]\t$Results[4]\t$Results[5]\t";
		print INFO "$Bytes[0]\t$Bytes[1]\t$Bytes[2]\t";
		print INFO "$Results[6]\t$Results[7]\t$Results[8]\t$Results[9]\t";
		print INFO "$flopsperbite\t$flopsperibite\t$intopsperibite\t$loadsperibite\t$storesperibite\n";
		$m = $m + 1;
	}
}
close(INFO);

}

}

########################
# Extract gprof output #
########################

if ( ${gprof_predict} == 1 ) {

$inputFile = "${benchname}_gprof_predicted.aspenlog";
$outputFile = "${benchname}_ASPEN_gprof_output.log";

if (-e $inputFile) {

print STDOUT "Input file ${inputFile}\n";
print STDOUT "Output file ${outputFile}\n";
open(INFO, ">$outputFile");

@Results = ();
for ($k = 0; $k < ${KernelListSize}; ++$k) {
	$inputKernel = $inputKernelList[$k];

	@Input_lines = `grep "${inputKernel}\$" $inputFile`;
	@line = split(/\s+/, $Input_lines[0]);
	$value1 = $line[$#line-1];           # refers to the last element of array @line
	print INFO "$value1\t";
	#if ($k == 20) {
	#	print INFO "$value1\n";
	#} else {
	#	print INFO "$value1\t";
	#}
}
close(INFO);

}

}
