%module test
%nspace;

%{
#include "../pch/wi_pch.h"
%}

namespace wi {
  class Application {
    public:
      void Initialize();
  };

}

namespace wi::arguments {
  void Parse(int argc, char *argv[]);
}
