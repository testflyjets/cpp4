// CheckingAccount.h
#ifndef CHECKINGACCOUNT_H
#define CHECKINGACCOUNT_H

#include <iosfwd>
#include <list>
#include <string>
#include <vector>
using namespace std;

#include "BankAccount.h" // class BankAccount

class Check;             // forward declaration 

class CheckingAccount : public BankAccount
{
public:
   CheckingAccount(long accountNumber,
      double initialBalance,
      const string &firstName,
      const string &lastName);

   ~CheckingAccount();

   double getBalance() const;
   void depositCheck(const Check &);
   void depositCash(double);
   void withdrawCash(double);
   virtual ostream &print(ostream &) const;

protected:
   void processAccount();

private:
   long accountNumber_;
   double balance_;
   string firstName_;
   string lastName_;
   vector<double> deposits_;
   vector<double> withdrawals_;
   list<Check> checks_;
};

ostream &operator<<(ostream &, const CheckingAccount &);

#endif