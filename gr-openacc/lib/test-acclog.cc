/* -*- c++ -*- */
/*
 * Copyright 2012 Free Software Foundation, Inc.
 *
 * This file is part of GNU Radio
 *
 * GNU Radio is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 *
 * GNU Radio is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with GNU Radio; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <cppunit/TextTestRunner.h>
#include <cppunit/XmlOutputter.h>

#include <gnuradio/unittests.h>
#include <gnuradio/block.h>
#include "qa_openacc.h"
#include <iostream>
#include <fstream>
#include <boost/algorithm/string/replace.hpp>
#include <math.h>  // fabsf

#include "accSComplex.h"
#include "accMathOpTypes.h"
#include "accLog_impl.h"
#include <chrono>
#include <ctime>

//#include "window.h"

bool verbose=true;
int blockSizeUL=1048576;
//[FIXME] MCL fails if the size is smaller than 64.
int largeBlockSize=64;
int platformId=0;
int deviceType=ACCTYPE_ANY;
int deviceId=0;
int d_vlen = 1;
int iterations = 100;

bool testMultiplyConst() {
	int i;
	int numItems=10;
	std::chrono::time_point<std::chrono::steady_clock> start, end;
	std::chrono::duration<double> elapsed_seconds = end-start;
	std::vector<int> ninitems;


	if (verbose) {
        std::cout << "building test array of size " << largeBlockSize << std::endl;
	}

	std::vector<gr_complex> inputItems;
	std::vector<gr_complex> outputItems;
	std::vector<float> inputFloats;
	std::vector<float> outputFloats;
	std::vector<const void *> inputFloatPointers;
	std::vector<void *> outputFloatPointers;

	std::vector< const void *> inputPointers;
	std::vector<void *> outputPointers;

	gr_complex grZero(0.0,0.0);
	gr_complex newComplex(1.0,0.5);

	for (i=0;i<largeBlockSize;i++) {
		inputItems.push_back(gr_complex(1.0f,0.5f));
		outputItems.push_back(gr_complex(0.0,0.0));

		inputFloats.push_back((float)i+1.0);
		outputFloats.push_back(0.0);
	}

	inputPointers.push_back((const void *)&inputItems[0]);
	outputPointers.push_back((void *)&outputItems[0]);

	inputFloatPointers.push_back((const void *)&inputFloats[0]);
	outputFloatPointers.push_back((void *)&outputFloats[0]);

	int noutputitems;

	float elapsed_time;
	float throughput;

	// switch to Log10 of float
	std::cout << "----------------------------------------------------------" << std::endl;

	gr::openacc::accLog_impl *testLog=NULL;
	testLog = new gr::openacc::accLog_impl(deviceType,deviceId,20.0,0);

	numItems = largeBlockSize;

	std::cout << "Testing Log10 float performance with " << numItems << " items..." << std::endl;
	std::cout << "Note: gnuradio log10 uses the following calculation: 'out[i] = n * log10(std::max(in[i], (float) 1e-18)) + k';" << std::endl;
	std::cout << "the extra max() function adds extra time to the call versus a straight log10." << std::endl;
	start = std::chrono::steady_clock::now();
	// make iterations calls to get average.
	for (i=0;i<iterations;i++) {
		noutputitems = testLog->testOpenACC(numItems,ninitems,inputFloatPointers,outputFloatPointers);
	}
	end = std::chrono::steady_clock::now();

	elapsed_seconds = end-start;

	switch(testLog->GetContextType()) {
	case ACCTYPE_GPU:
		std::cout << "OpenACC Context: GPU" << std::endl;
	break;
	case ACCTYPE_CPU:
		std::cout << "OpenACC Context: CPU" << std::endl;
	break;
	case ACCTYPE_ACCELERATOR:
		std::cout << "OpenACC Context: Accelerator" << std::endl;
	break;
	case ACCTYPE_ANY:
		std::cout << "OpenACC Context: Any" << std::endl;
	break;
	}
	elapsed_time = elapsed_seconds.count()/(float)iterations;
	throughput = largeBlockSize / elapsed_time;

#if !defined(TR_MODE) || TR_MODE == 0
#if !defined(OPENARC_ARCH) || OPENARC_ARCH == 0
	std::cout << "OpenACC/CUDA Run Time:   " << std::fixed << std::setw(11)
#else
	std::cout << "OpenACC/OpenCL Run Time:   " << std::fixed << std::setw(11)
#endif
#elif TR_MODE == 1
	std::cout << "OpenMP3 Run Time:   " << std::fixed << std::setw(11)
#elif TR_MODE == 2
	std::cout << "OpenMP4 Run Time:   " << std::fixed << std::setw(11)
#else
	std::cout << "MCL Run Time:   " << std::fixed << std::setw(11)
#endif
    << std::setprecision(6) << elapsed_time << " s  (" << throughput << " sps)" << std::endl << std::endl;


	noutputitems = testLog->testCPU(numItems,ninitems,inputFloatPointers,outputFloatPointers);

	start = std::chrono::steady_clock::now();
	// make iterations calls to get average.
	for (i=0;i<iterations;i++) {
		noutputitems = testLog->testCPU(numItems,ninitems,inputFloatPointers,outputFloatPointers);
	}
	end = std::chrono::steady_clock::now();

	elapsed_seconds = end-start;

	elapsed_time = elapsed_seconds.count()/(float)iterations;
	throughput = largeBlockSize / elapsed_time;

	std::cout << "CPU-only Run Time:   " << std::fixed << std::setw(11)
    << std::setprecision(6) << elapsed_time << " s  (" << throughput << " sps)" << std::endl << std::endl;

	delete testLog;

	inputPointers.clear();
	outputPointers.clear();
	inputItems.clear();
	outputItems.clear();
	ninitems.clear();

	return true;
}

int
main (int argc, char **argv)
{
	if (argc > 1) {
		// 1 is the file name
		if (strcmp(argv[1],"--help")==0) {
			std::cout << std::endl;
//			std::cout << "Usage: [<test buffer size>] [--gpu] [--cpu] [--accel] [--any]" << std::endl;
			std::cout << "Usage: [--gpu] [--cpu] [--accel] [--any] [--device=<platformid>:<device id>] [number of samples (default is 8192)]" << std::endl;
			std::cout << "where: --gpu, --cpu, --accel[erator], or any defines the type of OpenACC device opened." << std::endl;
			std::cout << "The optional --device argument allows for a specific OpenACC platform and device to be chosen.  Use the included clview utility to get the numbers." << std::endl;
			std::cout << std::endl;
			exit(0);
		}

		for (int i=1;i<argc;i++) {
			std::string param = argv[i];

			if (strcmp(argv[i],"--gpu")==0) {
				deviceType=ACCTYPE_GPU;
			}
			else if (strcmp(argv[i],"--cpu")==0) {
				deviceType=ACCTYPE_CPU;
			}
			else if (strcmp(argv[i],"--accel")==0) {
				deviceType=ACCTYPE_ACCELERATOR;
			}
			else if (param.find("--device") != std::string::npos) {
				if (param.find("--device") == std::string::npos) {
					std::cout<< "Error: device format should be <platform id>:<device id>" << std::endl;
					exit(2);
				}

				boost::replace_all(param,"--device=","");
				int posColon = param.find(":");
				platformId=atoi(param.substr(0,1).c_str());
				deviceId=atoi(param.substr(posColon+1,1).c_str());

			}
			else if (strcmp(argv[i],"--any")==0) {
				deviceType=ACCTYPE_ANY;
			}else if (atoi(argv[i]) > 0) {
				int newVal=atoi(argv[i]);

				blockSizeUL=newVal;
				std::cout << "Running with user-defined test buffer size of " << blockSizeUL << std::endl;
			}
			else {
				std::cout << "ERROR: Unknown parameter." << std::endl;
				exit(1);

			}
		}
	}
	bool was_successful;
/*
	CppUnit::TextTestRunner runner;
	std::ofstream xmlfile(get_unittest_path("openacc.xml").c_str());
	CppUnit::XmlOutputter *xmlout = new CppUnit::XmlOutputter(&runner.result(), xmlfile);

	runner.addTest(qa_openacc::suite());
	runner.setOutputter(xmlout);

	bool was_successful = runner.run("", false);  was_successful = testMultiply();
*/
/*
	was_successful = test_complex();
	std::cout << std::endl;
*/

	//for(int i=4; i<=30; i++) {
		//largeBlockSize = (int)exp2f((float)i);
	while ( largeBlockSize <= blockSizeUL ) {
		was_successful = testMultiplyConst();
		std::cout << std::endl;
		largeBlockSize *= 2;
	}

	return was_successful ? 0 : 1;
}

