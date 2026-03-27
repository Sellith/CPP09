/* *************************************************************************************************************** */
/*   PMergeMe.hpp                                                                                                  */
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

#ifndef PMERGEME_HPP
# define PMERGEME_HPP

# include <iostream>
# include <sstream>
# include <vector>
# include <list>
# include <cstdlib>
# include <algorithm>
# include <ctime>

# define _RED		"\e[1;91m"
# define _GREEN		"\e[1;92m"
# define _YELLOW	"\e[1;93m"
# define _PURPLE	"\e[1;95m"
# define _CYAN		"\e[1;96m"
# define _WHITE		"\e[1;97m"
# define _RESET		"\e[0m"

template <template <class, class > class T>
class PMergeMe
{

public:

	PMergeMe ( void );
	PMergeMe ( T<int, std::allocator<int> > const & );
	PMergeMe ( char * );
	PMergeMe ( PMergeMe const & );
	~PMergeMe ( void );

	PMergeMe & operator= ( PMergeMe const & );

	T<int, std::allocator<int> >	getCont ( void );
	T<int, std::allocator<int> >	getSorted ( void );
	time_t							getBeginTime ( void );

	void	insertContent ( T<int, std::allocator<int> > const &);
	void	fordJohnsonSort ( void );

private:

	T<int, std::allocator<int> >	cont_;
	T<int, std::allocator<int> >	sorted_;
	time_t	begin_;

};


bool	valChecking ( std::string values );

template <class Iterator>
Iterator		nextIt ( Iterator current );
template <class Iterator>
Iterator		prevIt ( Iterator current );


std::ostream &	operator<< ( std::ostream & o, std::vector<int> const & vec );
std::ostream &	operator<< ( std::ostream & o, std::list<int> const & lst );

# include "PMergeMe.tpp"

#endif // PMERGEME_HPP