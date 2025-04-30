#pragma once

#include "libraryes.h"

class MyException : public std::exception
{
public:
	virtual const char* what() const throw() override = 0;
};

class Input_NAN: public std::exception
{
public:
	const char* what() const throw() override {
		std::string msg = "Input must be numeric!";
		return msg.c_str();
	}
};
class Input_too_low: public std::exception
{
public:
	const char* what() const throw() override {
		std::string msg = "Value is too low!";
		return msg.c_str();
	}
};
class Input_High: public std::exception
{
public:
	const char* what() const throw() override {
		std::string msg = "Input is too high!";
		return msg.c_str();
	}
};
class Input_Invalid: public std::exception
{
public:
	const char* what() const throw() override {
		std::string msg = "Input is invalid!";
		return msg.c_str();
	}
};