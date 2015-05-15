namespace ChrisMcCann { namespace hw5 {

   template <typename X>
   class auto_ptr
   {
   public:
      // Constructors
      explicit auto_ptr(X * = 0) throw();
      auto_ptr(auto_ptr &) throw();
      template <typename Y> auto_ptr(auto_ptr<Y> &) throw();

      // Destructor
      ~auto_ptr() throw();

      // Access
      X *get() const throw();
      X &operator*() const throw();
      X *operator->() const throw();

      // Assignment
      auto_ptr &operator=(auto_ptr &) throw();
      template <typename Y> auto_ptr &operator=(auto_ptr<Y> &) throw();

      // Release & Reset
      X *release() throw();
      void reset(X * = 0) throw();
   };

}}