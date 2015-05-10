// CheckingAccount.h
#ifndef CHECKINGACCOUNT_H
#define CHECKINGACCOUNT_H

#include <iosfwd>
using std::ostream;

#include <string>
using std::string;

#include "BankAccount.h" // class BankAccount, must include
                         // due to public inheritance

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
   struct CheckingAccountImpl;
   CheckingAccountImpl *pimpl_;
};

ostream &operator<<(ostream &, const CheckingAccount &);

#endif