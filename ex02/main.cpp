/* *************************************************************************************************************** */
/*   main.cpp                                                                                                      */
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

int	main ( int ac, char ** av )
{
	if (ac == 1) {
		std::cout << "No arg were passed, nothing happened..." << std::endl;
		return (0);
	}
	if (!valChecking(av[1]))
		return (1);

	std::stringstream	ss(av[1]);
	std::vector<int>	vec;
	std::list<int>		lst;
	std::string			tmp;

	while (getline(ss, tmp, ' ')) {
		if (!tmp.empty()) {
			vec.push_back(atoi(tmp.c_str()));
			lst.push_back(atoi(tmp.c_str()));
		}
	}
	std::cout << "Before: " << vec << std::endl;
	std::cout << "vectors : \n";
	mergeInsertion<std::vector>(vec);
	std::cout << "lists : \n";
	mergeInsertion<std::list>(lst);
}