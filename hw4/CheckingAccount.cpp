
#include <list>
using std::list;

#include <string>
using std::string;

#include <vector>
using std::vector;

#include "CheckingAccount.h"

struct CheckingAccount::CheckingAccountImpl
{
   long accountNumber_;
   double balance_;
   string firstName_;
   string lastName_;
   vector<double> deposits_;
   vector<double> withdrawals_;
   list<Check> checks_;
};