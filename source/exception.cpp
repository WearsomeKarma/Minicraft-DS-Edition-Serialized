#include <nds.h>
#include "exception.h"

void Exception::init()
{
  defaultExceptionHandler();
}

void Exception::raise()
{
  *(u32*)8192 = 100;
}
