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
#include "qa_clenabled.h"
#include <iostream>
#include <fstream>
#include <boost/algorithm/string/replace.hpp>
#include <math.h>  // fabsf

#include "clSComplex.h"
#include "clMathOpTypes.h"
#include "clComplexToMag_impl.h"
#include <chrono>
#include <ctime>

//#include "window.h"

bool verbose=false;
int largeBlockSize=8192;
int opencltype=OCLTYPE_ANY;
int selectorType=OCLDEVICESELECTOR_FIRST;
int platformId=0;
int devId=0;
int d_vlen = 1;
int iterations = 100;

int ComplexToMagCPU(int noutput_items,
        gr_vector_int &ninput_items,
        gr_vector_const_void_star &input_items,
        gr_vector_void_star &output_items)
	{
    const gr_complex *in = (const gr_complex *) input_items[0];
    float *out = (float *) output_items[0];
    int noi = noutput_items * d_vlen;

    // turned out to be faster than aligned/unaligned switching
    volk_32fc_magnitude_32f_u(out, in, noi);

    return noutput_items;
}

bool testComplexToMag() {
	std::cout << "----------------------------------------------------------" << std::endl;

	std::cout << "Testing Complex to mag" << std::endl;

	gr::clenabled::clComplexToMag_impl *test=NULL;
	try {
		test = new gr::clenabled::clComplexToMag_impl(opencltype,selectorType,platformId,devId,true);
	}
	catch (...) {
		std::cout << "ERROR: error setting up OpenCL environment." << std::endl;

		if (test != NULL) {
			delete test;
		}

		return false;
	}

	test->setBufferLength(largeBlockSize);

	int i;
	std::chrono::time_point<std::chrono::steady_clock> start, end;
	std::chrono::duration<double> elapsed_seconds = end-start;
	std::vector<int> ninitems;


	if (verbose) {
		std::cout << "building test array..." << std::endl;
	}

	std::vector<gr_complex> inputItems;
	std::vector<float> outputItems;
	std::vector<const void *> inputPointers;
	std::vector<void *> outputPointers;

	gr_complex grZero(0.0,0.0);
	gr_complex newComplex(1.0,0.5);

	for (i=0;i<largeBlockSize;i++) {
		inputItems.push_back(gr_complex(1.0f,0.5f));
		outputItems.push_back(0.0);
	}

	inputPointers.push_back((const void *)&inputItems[0]);
	outputPointers.push_back((void *)&outputItems[0]);

	// Run empty test
	int noutputitems;

	// Get a test run out of the way.
	noutputitems = test->testOpenCL(largeBlockSize,ninitems,inputPointers,outputPointers);

	start = std::chrono::steady_clock::now();
	// make iterations calls to get average.
	for (i=0;i<iterations;i++) {
		noutputitems = test->testOpenCL(largeBlockSize,ninitems,inputPointers,outputPointers);
	}
	end = std::chrono::steady_clock::now();

	elapsed_seconds = end-start;

	switch(test->GetContextType()) {
	case CL_DEVICE_TYPE_GPU:
		std::cout << "OpenCL Context: GPU" << std::endl;
	break;
	case CL_DEVICE_TYPE_CPU:
		std::cout << "OpenCL Context: CPU" << std::endl;
	break;
	case CL_DEVICE_TYPE_ACCELERATOR:
		std::cout << "OpenCL Context: Accelerator" << std::endl;
	break;
	case CL_DEVICE_TYPE_ALL:
		std::cout << "OpenCL Context: ALL" << std::endl;
	break;
	}

	float elapsed_time,throughput;
	elapsed_time = elapsed_seconds.count()/(float)iterations;
	throughput = largeBlockSize / elapsed_time;

	std::cout << "OpenCL Run Time:   " << std::fixed << std::setw(11)
    << std::setprecision(6) << elapsed_time << " s  (" << throughput << " sps)" << std::endl << std::endl;

	int j;

	noutputitems = test->testCPU(largeBlockSize,ninitems,inputPointers,outputPointers);

	start = std::chrono::steady_clock::now();
	for (j=0;j<iterations;j++) {
		noutputitems = test->testCPU(largeBlockSize,ninitems,inputPointers,outputPointers);
	}
	end = std::chrono::steady_clock::now();

	elapsed_seconds = end-start;

	elapsed_time = elapsed_seconds.count()/(float)iterations;
	throughput = largeBlockSize / elapsed_time;

	std::cout << "CPU-only Run Time:   " << std::fixed << std::setw(11)
    << std::setprecision(6) << elapsed_time << " s  (" << throughput << " sps)" << std::endl << std::endl;

	std::cout << std::endl;

	// ----------------------------------------------------------------------
	// Clean up
	if (test != NULL) {
		delete test;
	}

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
			std::cout << "where: --gpu, --cpu, --accel[erator], or any defines the type of OpenCL device opened." << std::endl;
			std::cout << "The optional --device argument allows for a specific OpenCL platform and device to be chosen.  Use the included clview utility to get the numbers." << std::endl;
			std::cout << std::endl;
			exit(0);
		}

		for (int i=1;i<argc;i++) {
			std::string param = argv[i];

			if (strcmp(argv[i],"--gpu")==0) {
				opencltype=OCLTYPE_GPU;
			}
			else if (strcmp(argv[i],"--cpu")==0) {
				opencltype=OCLTYPE_CPU;
			}
			else if (strcmp(argv[i],"--accel")==0) {
				opencltype=OCLTYPE_ACCELERATOR;
			}
			else if (param.find("--device") != std::string::npos) {
				if (param.find("--device") == std::string::npos) {
					std::cout<< "Error: device format should be <platform id>:<device id>" << std::endl;
					exit(2);
				}

				selectorType = OCLDEVICESELECTOR_SPECIFIC;
				boost::replace_all(param,"--device=","");
				int posColon = param.find(":");
				platformId=atoi(param.substr(0,1).c_str());
				devId=atoi(param.substr(posColon+1,1).c_str());

			}
			else if (strcmp(argv[i],"--any")==0) {
				opencltype=OCLTYPE_ANY;
			}else if (atoi(argv[i]) > 0) {
				int newVal=atoi(argv[i]);

				largeBlockSize=newVal;
				std::cout << "Running with user-defined test buffer size of " << largeBlockSize << std::endl;
			}
			else {
				std::cout << "ERROR: Unknown parameter." << std::endl;
				exit(1);

			}
		}
	}
	bool was_successful;

	for(int i=4; i<=30; i++) {
		largeBlockSize = (int)exp2f((float)i);
		was_successful = testComplexToMag();
		std::cout << std::endl;
	}

	return was_successful ? 0 : 1;
}

