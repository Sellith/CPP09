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


/* -------------------------------------------------- */
/* ---------------- Class definition ---------------- */
/* -------------------------------------------------- */

template <template <class, class> class T>
PMergeMe<T>::PMergeMe ( void ) {}

template <template <class, class> class T>
PMergeMe<T>::PMergeMe ( char * array ) 
{
	std::stringstream	ss(array);
	std::string			tmp;

	while (getline(ss, tmp, ' ')) {
		if (!tmp.empty()) {
			cont_.push_back(atoi(tmp.c_str()));
		}
	}
}

template <template <class, class> class T>
PMergeMe<T>::PMergeMe ( T<int, std::allocator<int> > const & other ) 
	: cont_(other) {}

template <template <class, class> class T>
PMergeMe<T>::PMergeMe ( PMergeMe const & other ) 
	: cont_(other.cont_) {}

template <template <class, class> class T>
PMergeMe<T>::~PMergeMe ( void ) {}

template <template <class, class> class T>
PMergeMe<T> &	PMergeMe<T>::operator= ( PMergeMe const & other )
{
	if ( this != &other )
		cont_ = other.cont_;
	return ( *this );
}

/* --------------------------------------------------- */
/* ---------------- Utility functions ---------------- */
/* --------------------------------------------------- */

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

template <typename Iterator>
static void	forEach ( Iterator begin, Iterator end, void(*f)(Iterator) )
{
	Iterator it = begin;
	while (it != end) {
		f(it);
		it++;
	}
}

template <typename Iterator>
static void	pairSwap ( Iterator it )
{
	if (it->first > it->second)
		std::swap(it->first, it->second);
}
/* ----------------------------------------------- */
/* ---------------- Class methods ---------------- */
/* ----------------------------------------------- */

template <template <class, class> class T>
T<int, std::allocator<int> >	PMergeMe<T>::getCont ( void ) 
{return (cont_);}

template <template <class, class> class T>
T<int, std::allocator<int> >	PMergeMe<T>::getSorted ( void ) 
{return (sorted_);}

template <template <class, class> class T>
time_t	PMergeMe<T>::getBeginTime ( void ) 
{return (begin_);}

template <template <class, class> class T>
void	PMergeMe<T>::insertContent ( T<int, std::allocator<int> > const & ctn )
{cont_ = ctn;}

/* 
	@brief The goal of this function is to recursively create new pairs, to sort them, 
	then to separate between first and second into main and pending until size = 1
 */

template <template <class, class> class T>
static T_INT mergeInsertion( T_INT & container )
{
	std::cout << container << std::endl;
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
	if (container.size() % 2)
		pendCont.push_back(container.back());
	T_INT newMain;
	if (mainCont.size() > 2)
		newMain = mergeInsertion(mainCont);
	else {
		std::swap(mainCont.front(), mainCont.back());
		newMain = mainCont;
	}
	for (typename T_INT::reverse_iterator it = pendCont.rbegin(); it != pendCont.rend(); it++) {
		newMain.push_back(*it);
	}
	std::cout << newMain << std::endl;
	return ( newMain );
}

template <template <class, class> class T>
void	PMergeMe<T>::fordJohnsonSort ( void )
{
	sorted_ = mergeInsertion<T>(cont_);
}
