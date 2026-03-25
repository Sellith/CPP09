/* *************************************************************************************************************** */
/*   RPN.cpp                                                                                                       */
/*   By: lvan_bre                                                                   .,                             */
/*                                                                                 okxl                            */
/*                                                                                xkddo                            */
/*                                                                               kkxddo                            */
/*                                                                              lxxddol                            */
/*                                                                              xxdolol.                           */
/*                                                                             :kxdddddl                 .ox,      */
/*                                                                       ..,cdkOOkkkxdddd'      ;o.     ckkd,      */
/*                                                               .,:coxOOOkkkkkkkxxxxxddddo:...lxdl.   ckkxd.      */
/*                                                           ;oxOOOOkkxxkxxxxxxxxxxdddddodddxxxkkxxxdlckkxdd.      */
/*                                                        ,oOOOkkkkxxxdddxdddddddddddddoooooodooddddooooddooc      */
/*                                                      ;kkkkkxxxxxddoooooooooooooooooooooooooollooooooololll      */
/*                                                     oxodddddoooooolllllllolooooollloooollllolllllloooolccl;     */
/*                                                    'x:::cclccllllccccccccccclllclllllllllllllllll     .;;cl;    */
/*                                                    d;c::cc:cc:::;::c:c:cccccclccc:cccclllllll,         .:cl.    */
/*                                                      c;,;:;;::::;;::::c..,cccllcc:c;;:lloodk.                   */
/*                                                        'ooooooooodddxxkkkOOOkOOOOOOc:cclllloo'                  */
/*                                                           .XXXXXXXKKXXXXXXXXXXXXXXXkcccclcccllo                 */
/*                                                                 ,KKKKKXXXXXXXXXXXXK0.  .:ccllclll;.             */
/*                                                                                           .ccccccllc,.          */
/*                                                                                                 :::cl:          */
/*                                                                                                                 */
/* *************************************************************************************************************** */

#include "RPN.hpp"

RPN::RPN ( void ) {}
RPN::RPN ( std::string const & p_ctn )
{
	for (std::string::const_iterator it = p_ctn.begin(); it != p_ctn.end(); it++) {
		if (isdigit(*it))
			stackValue_.push(std::atoi(&*it));
		else {
			switch (*it)
			{
			case '+':
				operation(&RPN::addition);
				break ;
			case '-':
				operation(&RPN::substraction);
				break ;
			case '*':
				operation(&RPN::multiplication);
				break ;
			case '/':
				operation(&RPN::division);
				break ;
			default:
				throw std::runtime_error("Error : Unexepected input : " + std::string(&*it));
			}
		}
		if (it + 1 != p_ctn.end()) {
			it++;
			if (*it != ' ')
				throw std::runtime_error("Error : Unexepected input : " + std::string(&*it));
		}
	}
}

RPN::RPN ( RPN const & other ) : stackValue_(other.stackValue_) {}
RPN::~RPN ( void ) {}

RPN &	RPN::operator= ( RPN const & other )
{
	if ( this != &other )
		stackValue_ = other.stackValue_;
	return ( *this );
}

void RPN::operation ( int (RPN::*func)(int, int)) 
{
	if (stackValue_.size() < 2)	
		throw std::runtime_error("Error: bad input");
	int tmp[2];
	for (int i = 0; i < 2; i++) {
		tmp[i] = stackValue_.top();
		stackValue_.pop();
	}
	stackValue_.push((this->*func)(tmp[1], tmp[0]));
}

int	RPN::addition( int a, int b ) {return (a + b);}
int	RPN::substraction( int a, int b ) {return (a - b);}
int	RPN::multiplication( int a, int b ) {return (a * b);}
int	RPN::division( int a, int b ) 
{
	if (b == 0)
		throw std::runtime_error("Error: division by 0");
	return (a / b);
}

int	RPN::getStackValue ( void ) const 
{
	if (stackValue_.size() > 1)
		throw std::runtime_error("Error: non valid end stack size");
	if (stackValue_.empty())
		throw std::runtime_error("Error: Empty stack");
	return (stackValue_.top());
}