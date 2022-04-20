## 6x6 size matrix multiplier acceleration ip

 - Axi4 Lite Interface
 - IEEE-754 Single Precision Floating Point
 - Calculation done interrupt
 - Hardware written in C++
 - Synthesized by Vitis HLS
 - Block design was done by communicating with MicroBlaze soft processor
 - Software written in C
 - Loop unrolled up to FPGA capacity with pragmas

## Block Design
![Screenshot](https://github.com/SafaKucukkomurler/matrix_multiply_hls/blob/master/block_design.JPG)

## Matrix Multiply Module C/RTL Co-Simulation Waveform
![Screenshot](https://github.com/SafaKucukkomurler/matrix_multiply_hls/blob/master/waveform.JPG)
