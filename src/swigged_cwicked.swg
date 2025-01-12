%module test

%{
#include "../pch/wi_pch.h"
%}

namespace wi {
class Application {
  public:
    Application();
    ~Application();
    void Initialize();
};
}
