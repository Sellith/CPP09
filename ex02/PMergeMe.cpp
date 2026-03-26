/* *************************************************************************************************************** */
/*   PMergeMe.cpp                                                                                                      */
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

#include "PMergeMe.hpp"

bool	valChecking ( std::string values )
{
	for (std::string::iterator it = values.begin(); it != values.end(); it++) {
		if (!isdigit(*it) && *it != ' ') {
			std::cout << "Error: non valid character found" << std::endl;
			return (false);
		}
	}
	return (true);
}

std::ostream &	operator<< ( std::ostream & o, std::vector<int> const & vec )
{
	for (std::vector<int>::const_iterator it = vec.begin(); it != vec.end(); it++) {
		o << *it;
		if (nextIt(it) != vec.end())
			o << " ";
	}
	return (o);
}

std::ostream &	operator<< ( std::ostream & o, std::list<int> const & lst )
{
	for (std::list<int>::const_iterator it = lst.begin(); it != lst.end(); it++) {
		o << *it;
		if (nextIt(it) != lst.end())
			o << " ";
	}
	return (o);
}