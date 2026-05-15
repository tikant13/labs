#ifndef CONFIG_H
#define CONFIG_H

#include <vector>
#include<string>

using namespace std;

vector<string> globalTickets; // номера талонов
vector<int> globalTimes; // время обслуживания для каждого талона
int ticketCounter = 1;

#endif