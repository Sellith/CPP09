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
Iterator	moveIt ( Iterator current, int offset ) {
	Iterator ret(current);
	if (offset < 0) {
		for (int i = offset; i < 0; i++)
			ret--;
	}
	else {
		for (int i = offset; i > 0; i--)
			ret++;
	}
	return (ret);
}

template <class Container>
static int	refAt ( Container cont, size_t index )
{
	typename Container::iterator	Iter = cont.begin();
	for (size_t i = 0; i < index; i++) {
		Iter++;
	}
	return ( *Iter );
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
/* ---------------- Class Getters ---------------- */
/* ----------------------------------------------- */

template <template <class, class> class T>
T<int, std::allocator<int> >	PMergeMe<T>::getCont ( void ) const
{return (cont_);}

template <template <class, class> class T>
T<int, std::allocator<int> >	PMergeMe<T>::getSorted ( void ) const
{return (sorted_);}

template <template <class, class> class T>
double	PMergeMe<T>::getTimestamp ( void ) const
{return (timestamp_ / (CLOCKS_PER_SEC / 1000));}

template <template <class, class> class T>
int	PMergeMe<T>::getSize ( void ) const
{return (cont_.size());}


template <template <class, class> class T>
T_INT insertContent( T_INT const & main, T_INT const & pend )
{
	typedef typename T_INT::iterator	Iter;
	
	T_INT result = main;

	if (pend.empty())
		return ( result );

	// Insérer pend[0] (son "grand" est mainCont[0], déjà dans result)
	{
		Iter	pos		= std::upper_bound(result.begin(), result.end(), pend.front());
		result.insert(pos, pend.front());
	}

	size_t	index		= 1;
	size_t	prevJacob	= 1;

	while (true) {
		size_t	currentJacob = jacobsthal(index);

		// Clamp au nombre d'éléments réellement disponibles
		size_t	limit = currentJacob < pend.size() ? currentJacob : pend.size();
		
		// Insérer le batch courant en ordre décroissant d'indice
		for (size_t i = limit; i > prevJacob; i--) {
			size_t	idx		= i - 1;
			Iter	pos		= std::upper_bound(result.begin(), result.end(), refAt(pend, idx));
			result.insert(pos, refAt(pend, idx));
		}

		prevJacob = limit;

		if (currentJacob >= pend.size())
			break ;

		index++;
	}

	// Éléments restants au-delà du dernier Jacobsthal complet
	for (size_t i = pend.size(); i > prevJacob; i--) {
		size_t	idx		= i - 1;
		Iter	pos		= std::upper_bound(result.begin(), result.end(), refAt(pend, idx));
		result.insert(pos, refAt(pend, idx));
	}

	return ( result );
}

// ─── mergeInsertion ───────────────────────────────────────────────────────

/* 
	@brief The goal of this function is to recursively create new pairs, to sort them, 
	then to separate between first and second into main and pending until size = 1
*/

template <template <class, class> class T>
T_INT mergeInsertion(T_INT & container)
{
	typedef typename T_INT::iterator	Iter;
	typedef typename T_PAIR::iterator	PairIter;

	// ── 1. Construire les paires
	T_PAIR pairs;
	for (Iter it = container.begin(); it != container.end(); it++) {
		Iter itFirst = it;
		++it;
		if (it == container.end()) 
			break;
		pairs.push_back(std::make_pair(*itFirst, *it));
	}

	// ── 2. Trier chaque paire (petit, grand)
	forEach(pairs.begin(), pairs.end(), pairSwap);

	// ── 3. Séparer main (grands) et pend (petits)
	T_INT mainCont;
	T_INT pendCont;
		
	for (PairIter it = pairs.begin(); it != pairs.end(); it++) {
		mainCont.push_back(it->second);
		pendCont.push_back(it->first);
	}

	// Élément impair → dans pend
	if (container.size() % 2)
		pendCont.push_back(container.back());

	// ── 4. Trier récursivement les grands
	T_INT newMain;
	if (mainCont.size() > 2) {
		newMain = mergeInsertion<T>(mainCont);
	}
	else if (mainCont.size() == 2) {
		// Deux elements restant dans le Container principal : on les trie simplement
		if (mainCont.front() > mainCont.back())
			std::swap(mainCont.front(), mainCont.back());
		newMain = mainCont;
	}
	else {
		newMain = mainCont;
	}

	// ── 5. Insérer les petits dans l'ordre Ford-Johnson
	T_INT ret = insertContent<T>(newMain, pendCont);
	return ( ret );
}

template <template <class, class> class T>
void	PMergeMe<T>::fordJohnsonSort ( void )
{
	clock_t	start	= clock();
	sorted_ 		= mergeInsertion<T>(cont_);
	clock_t	end		= clock();
	timestamp_ = end - start;
}
