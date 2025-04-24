#include <iostream>

using namespace std;

class MyException : public std::exception
{
private:
	string message;

public:
	MyException(const string& s) : message{ s } {}

	const char* what() const throw() override {
		return this->message.c_str();
	}
};


void f()
{
	throw MyException{ "exaaaaception\n" };
}

void handle()
{
	try
	{
		f();
	}
	catch (std::exception& e)
	{
		cout << e.what();
	}
}

int main()
{
	try 
	{
		cout << "Code before the exception" << endl;
		f() ;
		if(1)
        {
			cout << "Throw exception" << endl;
			throw 12;
		}
		cout << "Code after the exception" << endl;
	}
	catch ( MyException & e )   ////             <------------------- referinta!!
	{ 
		cout << "Error handling code " << endl;
        cout << e.what() <<"\n";
	}
    catch( ... )
    {
        cout <<"pula";
    }

	cout << "Done." << endl;
}