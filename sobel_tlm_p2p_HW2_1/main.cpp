#include <iostream>
#include <string>
using namespace std;

// Wall Clock Time Measurement
#include <sys/time.h>

#include "SobelFilter.h"  // plays the role of the TLM target
#include "Testbench.h"    // works as TLM initiators

// TIMEVAL STRUCT IS Defined ctime
// use start_time and end_time variables to capture
// start of simulation and end of simulation
struct timeval start_time, end_time;

// int main(int argc, char *argv[])
int sc_main(int argc, char **argv) {
  if ((argc < 3) || (argc > 4)) {
    cout << "No arguments for the executable : " << argv[0] << endl;
    cout << "Usage : >" << argv[0] << " in_image_file_name out_image_file_name"
         << endl;
    return 0;
  }

  // capture the start time of the simulation
  gettimeofday(&start_time, NULL);

  Testbench tb("tb");
  SobelFilter sobel_filter("sobel_filter");
  tb.initiator.i_skt(sobel_filter.t_skt);

  tb.read_bmp(argv[1]);
  sc_start();

  // capture the end time of the simulation
  gettimeofday(&end_time, NULL);

  // calculate the actual simulation run time in seconds
  double run_time = (end_time.tv_sec - start_time.tv_sec) +
                    (end_time.tv_usec - start_time.tv_usec) / 1000000.0;

  std::cout << "Simulated time == " << sc_core::sc_time_stamp() << std::endl;
  std::cout << "Actual simulation run time == " << run_time << " seconds" << std::endl;

  tb.write_bmp(argv[2]);

  return 0;
}
