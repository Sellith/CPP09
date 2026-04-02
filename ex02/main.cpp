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

#define TEST (function, message) \
if (function) {std::cout << _GREEN << "Success: Containers is successfully sorted" << std::endl;} \
else {std::cout << _RED << "Failure: Container is not sorted" << std::endl;}

int	main ( int ac, char ** av )
{
	if (ac == 1) {
		std::cout << "No arg were passed, nothing happened..." << std::endl;
		return (0);
	}
	if (!valChecking(av[1]))
		return (1);

	{
		PMergeMe<std::vector>	vec(av[1]);
		std::cout << "Before\t: " << vec.getCont() << std::endl;
		vec.fordJohnsonSort();
		std::cout << "After \t: " << vec.getSorted() << std::endl;
		std::cout << "Time to process a range of " 
			<< vec.getSize() << " with std::vector : "
			<< vec.getTimestamp() << " ms" << std::endl;
	}

	std::cout << "\n";

	{
		PMergeMe<std::list>	lst(av[1]);
		std::cout << "Before\t: " << lst.getCont() << std::endl;
		lst.fordJohnsonSort();
		std::cout << "After \t: " << lst.getSorted() << std::endl;
		std::cout << "Time to process a range of " 
			<< lst.getSize() << " with std::list : " 
			<< lst.getTimestamp() << " ms" << std::endl;
	}
}