#ifndef EXCEPTION_H
#define EXCEPTION_H
#include <exception>
class FILEIOERROR:public exception{

	virtual const char * what()const throw(){
		return "File open failed.";
	}
};
class READFILEERROR:public exception{
	virtual const char * what()const throw(){
		return "(Bad Data) Reading file error.";
	}
};

#endif