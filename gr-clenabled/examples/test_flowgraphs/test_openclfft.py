#!/usr/bin/env python2
# -*- coding: utf-8 -*-
##################################################
# GNU Radio Python Flow Graph
# Title: Test Openclfft
# Generated: Thu Dec 20 17:54:28 2018
##################################################

from gnuradio import analog
from gnuradio import blocks
from gnuradio import eng_notation
from gnuradio import fft
from gnuradio import gr
from gnuradio.eng_option import eng_option
from gnuradio.fft import window
from gnuradio.filter import firdes
from optparse import OptionParser
import clenabled


class test_openclfft(gr.top_block):

    def __init__(self):
        gr.top_block.__init__(self, "Test Openclfft")

        ##################################################
        # Variables
        ##################################################
        self.samp_rate = samp_rate = 2.4e6
        self.fftsize = fftsize = 1024

        ##################################################
        # Blocks
        ##################################################
        self.fft_vxx_0 = fft.fft_vcc(fftsize, True, (), False, 1)
        self.clenabled_clFFT_0 = 	clenabled.clFFT(fftsize, -1, (),1,4,1,0,0,0)
        self.blocks_vector_to_stream_0_0 = blocks.vector_to_stream(gr.sizeof_gr_complex*1, fftsize)
        self.blocks_vector_to_stream_0 = blocks.vector_to_stream(gr.sizeof_gr_complex*1, fftsize)
        self.blocks_throttle_0 = blocks.throttle(gr.sizeof_gr_complex*1, samp_rate,True)
        self.blocks_stream_to_vector_1 = blocks.stream_to_vector(gr.sizeof_gr_complex*1, fftsize)
        self.blocks_null_sink_1 = blocks.null_sink(gr.sizeof_int*1)
        self.blocks_null_sink_0 = blocks.null_sink(gr.sizeof_int*1)
        self.blocks_complex_to_mag_0_0 = blocks.complex_to_mag(1)
        self.blocks_complex_to_mag_0 = blocks.complex_to_mag(1)
        self.blocks_add_xx_0 = blocks.add_vcc(1)
        self.analog_sig_source_x_0_0 = analog.sig_source_c(samp_rate, analog.GR_COS_WAVE, 500e3, 1, 0)
        self.analog_sig_source_x_0 = analog.sig_source_c(samp_rate, analog.GR_COS_WAVE, 1e6, 1, 0)



        ##################################################
        # Connections
        ##################################################
        self.connect((self.analog_sig_source_x_0, 0), (self.blocks_add_xx_0, 0))
        self.connect((self.analog_sig_source_x_0_0, 0), (self.blocks_add_xx_0, 1))
        self.connect((self.blocks_add_xx_0, 0), (self.blocks_throttle_0, 0))
        self.connect((self.blocks_complex_to_mag_0, 0), (self.blocks_null_sink_0, 0))
        self.connect((self.blocks_complex_to_mag_0_0, 0), (self.blocks_null_sink_1, 0))
        self.connect((self.blocks_stream_to_vector_1, 0), (self.clenabled_clFFT_0, 0))
        self.connect((self.blocks_stream_to_vector_1, 0), (self.fft_vxx_0, 0))
        self.connect((self.blocks_throttle_0, 0), (self.blocks_stream_to_vector_1, 0))
        self.connect((self.blocks_vector_to_stream_0, 0), (self.blocks_complex_to_mag_0, 0))
        self.connect((self.blocks_vector_to_stream_0_0, 0), (self.blocks_complex_to_mag_0_0, 0))
        self.connect((self.clenabled_clFFT_0, 0), (self.blocks_vector_to_stream_0_0, 0))
        self.connect((self.fft_vxx_0, 0), (self.blocks_vector_to_stream_0, 0))

    def get_samp_rate(self):
        return self.samp_rate

    def set_samp_rate(self, samp_rate):
        self.samp_rate = samp_rate
        self.blocks_throttle_0.set_sample_rate(self.samp_rate)
        self.analog_sig_source_x_0_0.set_sampling_freq(self.samp_rate)
        self.analog_sig_source_x_0.set_sampling_freq(self.samp_rate)

    def get_fftsize(self):
        return self.fftsize

    def set_fftsize(self, fftsize):
        self.fftsize = fftsize


def main(top_block_cls=test_openclfft, options=None):

    tb = top_block_cls()
    tb.start(1024)
    tb.wait()


if __name__ == '__main__':
    main()
