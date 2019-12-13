#!/usr/bin/env python2
# -*- coding: utf-8 -*-
##################################################
# GNU Radio Python Flow Graph
# Title: Top Block
# Generated: Mon Nov 25 10:34:24 2019
##################################################

if __name__ == '__main__':
    import ctypes
    import sys
    if sys.platform.startswith('linux'):
        try:
            x11 = ctypes.cdll.LoadLibrary('libX11.so')
            x11.XInitThreads()
        except:
            print "Warning: failed to XInitThreads()"

from PyQt4 import Qt
from gnuradio import analog
from gnuradio import blocks
from gnuradio import eng_notation
from gnuradio import gr
from gnuradio.eng_option import eng_option
from gnuradio.filter import firdes
from optparse import OptionParser
import ornl
import pmt
import sys
from gnuradio import qtgui


class top_block(gr.top_block, Qt.QWidget):

    def __init__(self):
        gr.top_block.__init__(self, "Top Block")
        Qt.QWidget.__init__(self)
        self.setWindowTitle("Top Block")
        qtgui.util.check_set_qss()
        try:
            self.setWindowIcon(Qt.QIcon.fromTheme('gnuradio-grc'))
        except:
            pass
        self.top_scroll_layout = Qt.QVBoxLayout()
        self.setLayout(self.top_scroll_layout)
        self.top_scroll = Qt.QScrollArea()
        self.top_scroll.setFrameStyle(Qt.QFrame.NoFrame)
        self.top_scroll_layout.addWidget(self.top_scroll)
        self.top_scroll.setWidgetResizable(True)
        self.top_widget = Qt.QWidget()
        self.top_scroll.setWidget(self.top_widget)
        self.top_layout = Qt.QVBoxLayout(self.top_widget)
        self.top_grid_layout = Qt.QGridLayout()
        self.top_layout.addLayout(self.top_grid_layout)

        self.settings = Qt.QSettings("GNU Radio", "top_block")
        self.restoreGeometry(self.settings.value("geometry").toByteArray())


        ##################################################
        # Variables
        ##################################################
        self.samp_rate = samp_rate = 32000

        ##################################################
        # Blocks
        ##################################################
        self.ornl_vecadd_1 = ornl.vecadd(64, 4)
        self.ornl_vecadd_0 = ornl.vecadd(128, 1)
        (self.ornl_vecadd_0).set_min_output_buffer(1)
        (self.ornl_vecadd_0).set_max_output_buffer(8192)
        self.ornl_saxpy_0 = ornl.saxpy(128, 5)
        self.blocks_null_source_0 = blocks.null_source(gr.sizeof_int*1)
        self.blocks_file_source_2 = blocks.file_source(gr.sizeof_int*1, '/home/eck/sandbox/gnuradio/ornl-add/in2.txt', False)
        self.blocks_file_source_2.set_begin_tag(pmt.PMT_NIL)
        self.blocks_file_source_1 = blocks.file_source(gr.sizeof_int*1, '/home/eck/sandbox/gnuradio/ornl-add/in1.txt', False)
        self.blocks_file_source_1.set_begin_tag(pmt.PMT_NIL)
        self.blocks_file_source_0 = blocks.file_source(gr.sizeof_int*1, '/home/eck/sandbox/gnuradio/ornl-add/in0.txt', False)
        self.blocks_file_source_0.set_begin_tag(pmt.PMT_NIL)
        self.blocks_file_sink_0 = blocks.file_sink(gr.sizeof_int*1, '/home/eck/sandbox/gnuradio/ornl-add/output.txt', False)
        self.blocks_file_sink_0.set_unbuffered(True)
        self.analog_const_source_x_0 = analog.sig_source_i(0, analog.GR_CONST_WAVE, 0, 0, 1)



        ##################################################
        # Connections
        ##################################################
        self.connect((self.analog_const_source_x_0, 0), (self.ornl_saxpy_0, 0))
        self.connect((self.blocks_file_source_0, 0), (self.ornl_vecadd_0, 0))
        self.connect((self.blocks_file_source_1, 0), (self.ornl_vecadd_0, 1))
        self.connect((self.blocks_file_source_2, 0), (self.ornl_saxpy_0, 2))
        self.connect((self.blocks_null_source_0, 0), (self.ornl_vecadd_1, 1))
        self.connect((self.ornl_saxpy_0, 0), (self.ornl_vecadd_1, 0))
        self.connect((self.ornl_vecadd_0, 0), (self.ornl_saxpy_0, 1))
        self.connect((self.ornl_vecadd_1, 0), (self.blocks_file_sink_0, 0))

    def closeEvent(self, event):
        self.settings = Qt.QSettings("GNU Radio", "top_block")
        self.settings.setValue("geometry", self.saveGeometry())
        event.accept()

    def get_samp_rate(self):
        return self.samp_rate

    def set_samp_rate(self, samp_rate):
        self.samp_rate = samp_rate


def main(top_block_cls=top_block, options=None):

    from distutils.version import StrictVersion
    if StrictVersion(Qt.qVersion()) >= StrictVersion("4.5.0"):
        style = gr.prefs().get_string('qtgui', 'style', 'raster')
        Qt.QApplication.setGraphicsSystem(style)
    qapp = Qt.QApplication(sys.argv)

    tb = top_block_cls()
    tb.start()
    tb.show()

    def quitting():
        tb.stop()
        tb.wait()
    qapp.connect(qapp, Qt.SIGNAL("aboutToQuit()"), quitting)
    qapp.exec_()


if __name__ == '__main__':
    main()
