/* *************************************************************************************************************** */
/*   PMergeMe.tpp                                                                                                  */
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

template <class T>
T	nextIt ( T current ) {
	T next(current);
	++next;
	return ( next );
}

template <template <class, class> class T>
static T<std::pair<int, int>, std::allocator<std::pair<int, int> > >
	pairing( T<int, std::allocator<int> > const & container )
{
	T<std::pair<int, int>, std::allocator<std::pair<int, int> > > pairs;
	for (typename T<int, std::allocator<int> >::const_iterator it = container.begin(); it != container.end() && nextIt(it) != container.end(); it++) {
		typename T<int, std::allocator<int> >::const_iterator	itFirst = it++;
		std::pair<int, int>										tmp (*itFirst, *it);
		pairs.push_back(tmp);
	}
	return (pairs);
}

template <template <class, class> class T>
void	mergeInsertion ( T<int, std::allocator<int> > container )
{
	T<std::pair<int, int>, std::allocator<std::pair<int, int> > > pairs = pairing<T>(container);
	for (typename T<std::pair<int, int>, std::allocator<std::pair<int, int> > >::const_iterator it = pairs.begin(); it != pairs.end(); it++) {
		std::cout << "first: " << it->first << " second: " << it->second << std::endl;
	}
}
