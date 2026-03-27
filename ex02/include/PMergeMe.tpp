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


#define	T_PAIR	T<std::pair<int, int>, std::allocator<std::pair<int, int> > >
#define T_PAIRT	T<std::pair<int, int>, std::allocator<std::pair<int, int> > >::iterator
#define T_INT	T<int, std::allocator<int> >
#define T_INTCT	T<int, std::allocator<int> >::const_iterator

template <typename Iterator>
Iterator	nextIt ( Iterator current ) {
	Iterator next(current);
	++next;
	return ( next );
}

template <typename Iterator>
Iterator	prevIt ( Iterator current ) {
	Iterator prev(current);
	--prev;
	return ( prev );
}

template <typename T>
static void	forEach ( T begin, T end, void(*f)(T) )
{
	T it = begin;
	while (it != end) {
		f(it);
		it++;
	}
}

template <typename T>
static void	pairSwap ( T it )
{
	if (it->first > it->second)
		std::swap(it->first, it->second);
}

/* 
	@brief The goal of this function is to recursively create new pairs, to sort them, 
	then to separate between first and second into main and pending until size = 1
 */

template <template <class, class> class T>
static void pairing( T_INT & container )
{
	if (container.size() == 1)
		return ;

	T_PAIR pairs;
	for (typename T_INTCT it = container.begin(); it != container.end() && nextIt(it) != container.end(); it++) {
		typename T_INTCT	itFirst = it++;
		std::pair<int, int>	tmp (*itFirst, *it);
		pairs.push_back(tmp);
	}
	forEach(pairs.begin(), pairs.end(), pairSwap);
	T_INT	mainCont;
	T_INT	pendCont;
	for (typename T_PAIRT it = pairs.begin(); it != pairs.end(); it++) {
		mainCont.push_back(it->second);
		pendCont.push_back(it->first);
	}
	std::cout << "mainCont is : " << mainCont << std::endl;
	std::cout << "pendCont is : " << pendCont << std::endl;
	pairing(mainCont);
}

template <template <class, class> class T>
void	fordJohnsonSort ( T<int, std::allocator<int> > & container )
{
	pairing<T>(container);
}
