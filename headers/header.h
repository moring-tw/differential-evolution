#pragma once
#ifndef EA_INC_HEADER_H_
#define EA_INC_HEADER_H_

#include <stdio.h>
#include <float.h>
#include <omp.h>

#include <iostream>
#include <cstring>
#include <cstdio>
#include <fstream>
#include <sstream>
#include <ctime>
#include <time.h>

// benchmark set header files


// ea header files
#include "readconfig.h"
#include "corematerial.h"
#include "executivevariables.h"
#include "publicfunction.h"
#include "differential_evolution/process_controller.h"
//#include "de.h"
#include "../benchmark/inc/Benchmarks.h"
#include "../benchmark/inc/CEC/F1.h"
#include "../benchmark/inc/1999/benchmark_1999_F1.h"
#include "../benchmark/inc/1999/benchmark_1999_F2.h"
#include "../benchmark/inc/1999/benchmark_1999_F3.h"
#include "../benchmark/inc/1999/benchmark_1999_F4.h"
#include "../benchmark/inc/1999/benchmark_1999_F5.h"
#include "../benchmark/inc/1999/benchmark_1999_F6.h"
#include "../benchmark/inc/1999/benchmark_1999_F7.h"
#include "../benchmark/inc/1999/benchmark_1999_F8.h"
#include "../benchmark/inc/1999/benchmark_1999_F9.h"
#include "../benchmark/inc/CEC_2013/cec2013benchmarks.h"

Benchmarks* FunctionChooser(unsigned, evolutionalgorithm::ExecutiveVariables&);
void CheckFilePath(const std::string&);
#endif // EA_INC_HEADER_H_
