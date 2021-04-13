#include <ctime>

using std::ctime;
using std::time;

#include <cstring>

using std::strtok;

#include <iomanip>

using std::setw;

#include <iostream>

using std::cout;
using std::endl;

#include "progress_printer.hpp"

ProgressPrinter::ProgressPrinter(const long ne, const double ui):
start_time(time(nullptr)), n_entries(ne), inverse_n_entries(1./ (double) ne), update_increment(ui), current_percentage(ui){
    cout << get_time_string() << " : Starting to process " << n_entries << " entries." << endl;
}

void ProgressPrinter::operator()(const long index){
    const double percentage = index*inverse_n_entries;

    if(percentage >= current_percentage){
        time_t current_time = time(nullptr);
        cout << get_time_string() << " : " << setw(5) << current_percentage*100. << " % processed in " << setw(5) << current_time - start_time << " second(s)." << endl;

        current_percentage = ((int) ((percentage + update_increment)/update_increment))*update_increment;
    }
}

char* ProgressPrinter::get_time_string() const {
    time_t current_time = time(nullptr);
    return strtok(ctime(&current_time), "\n");
}