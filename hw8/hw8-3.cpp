// Question 3:
//
// Make the following program const-correct. 
//
// Once you’ve made corrections the program should 
// compile and run without error. You must not change 
// anything in main().

#include <cfloat>
#include <iostream>
using namespace std;
class Object
{
   friend ostream &operator<<(ostream &, Object &);
   
   // additional friend function to handle stream
   // insertion of constant Objects
   friend ostream &operator<<(ostream &, const Object &);

public:
   Object(double mass, double acceleration)
      : mass_(mass),
      acceleration_(acceleration)
   {
      clearForce();
   }

   double getMass() const
   {
      return mass_;
   }

   void setMass(double mass)
   {
      mass_ = mass;
      clearForce();
   }

   double getAcceleration() const
   {
      return acceleration_;
   }

   void setAcceleration(double acceleration)
   {
      acceleration_ = acceleration;
      clearForce();
   }

   double getForce() const
   {
      if (!isForceComputed())
         computeForce();
      return force_;
   }

private:
   void computeForce() const
   {
      force_ = mass_ * acceleration_;
   }

   void clearForce() const
   {
      force_ = DBL_MIN;
   }

   bool isForceComputed() const
   {
      return force_ != DBL_MIN;
   }

   double mass_; // Grams
   double acceleration_; // Meters per second squared
   mutable double force_; // Newtons
};

ostream &operator<<(ostream &out, Object &obj)
{
   return out << obj.getMass() << "g, "
      << obj.getAcceleration() << "m / s^2, "
      << obj.getForce() << "N";
}

// handle stream insertion of const Objects by using
// const_cast to remove constness.  This seems safe as
// the method doesn't return the input Object parameter.
ostream &operator<<(ostream &out, const Object &obj)
{
   return operator<<(out, const_cast<Object &>(obj));
}

int main()
{
   Object obj(12, 150);
   cout << obj << "\n";

   const Object cobj(7, 275);
   cout << cobj << "\n";
}