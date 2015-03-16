#ifndef _UTILS_DEBUG_H_
#define _UTILS_DEBUG_H_

#define TEST_EQUAL(f,s) if ( f != s ) {  std::cout << "TEST failed line " << __LINE__ << std::endl; return -1; }
#define TEST_NOT_EQUAL(f,s) if ( f == s ) { std::cout << "TEST failed line " << __LINE__ << std::endl; return -1; }
#define FAILED_BLOCK() { std::cout << "TEST failed line " << __LINE__ << std::endl; return -1;  }
#define IS_TRUE( f ) if ( !f ) { std::cout << "TEST failed line " << __LINE__ << std::endl; return -1; }
#define IS_FALSE( f ) if ( f ) { std::cout << "TEST failed line " << __LINE__ << std::endl; return -1; } 

#endif