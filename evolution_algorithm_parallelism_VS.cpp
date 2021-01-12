// evolution_algorithm_parallelism_VS.cpp : 此檔案包含 'main' 函式。程式會於該處開始執行及結束執行。
//
#include "headers/header.h"
#include <map>
#include <unordered_map>
#include <omp.h>

//#pragma omp parallel for

int main()
{
	evolutionalgorithm::Variables v;
	evolutionalgorithm::ReadConfig rc;
	rc.NextRun(v);
	omp_set_num_threads(2);
	double start, end;
	int problem_counter = 0;

#pragma omp parallel for num_threads(14) private(problem_counter)
	for (problem_counter = 0; problem_counter < v.GetProblemAmount(); ++problem_counter) {
		{	
			if (v.IsProblemExecuting(problem_counter)) {

				int thread_id = omp_get_thread_num();
				std::cout << "P" << problem_counter << " @ T" << thread_id << std::endl;
				Benchmarks* fp;
				evolutionalgorithm::ExecutiveVariables ev(v);
				evolutionalgorithm::differentialevolution::ProcessController pc;
				double now_best = DBL_MAX;
				fp = FunctionChooser(problem_counter, ev);
				start = clock();
				for (unsigned int run_counter = 0; run_counter < 51; ++run_counter) {
					now_best = DBL_MAX;
					pc.SetExecutiveVariables(ev);
					fp->nextRun();
					pc.NextRun();
					pc.SetBenchmark(fp);
					pc.Execute();
					double best = pc.GetBest();
					if (best < now_best) {
						now_best = best;
					}
					std::cout << "Problem :" << problem_counter << " @ Run " << run_counter << ":" << now_best << std::endl;
				}
				end = clock();
				std::cout << "Time(ms):" << (end - start) << std::endl << std::endl;
				delete fp;
			}
		}
	}
	system("PAUSE");
}

/*evolutionalgorithm::ExecutiveVariables ev(v);
ev.UpdateDE_CR(5.9);
std::cout << "\n\nev CR:" << ev.GetDE_CR();


evolutionalgorithm::ExecutiveVariables ev2(v);

std::cout << "\nv CR:"<<v.get_CR()<<"\tev2 CR:" << ev2.GetDE_CR();*/


// 執行程式: Ctrl + F5 或 [偵錯] > [啟動但不偵錯] 功能表
// 偵錯程式: F5 或 [偵錯] > [啟動偵錯] 功能表

// 開始使用的提示: 
//   1. 使用 [方案總管] 視窗，新增/管理檔案
//   2. 使用 [Team Explorer] 視窗，連線到原始檔控制
//   3. 使用 [輸出] 視窗，參閱組建輸出與其他訊息
//   4. 使用 [錯誤清單] 視窗，檢視錯誤
//   5. 前往 [專案] > [新增項目]，建立新的程式碼檔案，或是前往 [專案] > [新增現有項目]，將現有程式碼檔案新增至專案
//   6. 之後要再次開啟此專案時，請前往 [檔案] > [開啟] > [專案]，然後選取 .sln 檔案

Benchmarks* FunctionChooser(unsigned serial_number, evolutionalgorithm::ExecutiveVariables& ev) {
	Benchmarks* fp;
	if (serial_number > 0 && serial_number < 29) {
		fp = new CEC2013Benchmarks(ev.GetDE_Dim(), serial_number);
		return fp;
	}
	switch (serial_number) {
	case 0:
		fp = new F1();
		break;
	default:
		std::cout << "Unknown function number." << std::endl;
		return nullptr;
	}
	return fp;
}