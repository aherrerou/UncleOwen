#include <iostream>
#ifndef _util
#define _util

using namespace std;

enum Error {
  ERR_NO_FIELDS, 
  ERR_UNKNOWN_OPTION,
  ERR_WRONG_MODEL,
  ERR_WRONG_FIELD,
  ERR_WRONG_SPEED, 
  ERR_WRONG_PRODUCTS,
  ERR_NAME,
  ERR_OPEN_FILE,
  ERR_ARGS,
  ERR_MAXANDROIDS
};

class Util{
    
    public:
        static void error(Error n);
};
#endif