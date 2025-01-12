%module test
%nspace;

%{
#include "../pch/wi_pch.h"
%}

%include "../.wi/WickedEngine/wiVersion.h"
%include "../.wi/WickedEngine/wiApplication.h"

namespace wi::arguments {
  void Parse(int argc, char *argv[]);
}

%{
namespace wi::version {
	long GetVersion() {
		return 0;
	}
}
%}
