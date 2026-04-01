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

// template <template <class, class> class T>
// static T_INT	insertContent ( T_INT const & main, T_INT const & pend )
// {
// 	T_INT result = main;

// 	if (pend.empty())
// 		return (result);

// 	typename T_INT::iterator pos = std::upper_bound(result.begin(), result.end(), pend[0]);
// 	result.insert(pos, pend.at(0));

// 	typename T_INT::iterator	worstCase = result.begin();
// 	typename T_INT::iterator	delimiter = result.begin();

// 	size_t index = 1;
// 	size_t prevJacob = 1;

// 	while (true) {
// 		size_t currentJacob = jacobsthal(index);
// 		if (currentJacob >= pend.size())
// 			break ;
// 		for(size_t i = currentJacob; i > prevJacob; i--) {
// 			size_t idx = i - 1;
// 			typename T_INT::iterator pos = std::upper_bound(worstCase, moveIt(delimiter, idx), pend[idx]);
// 			result.insert(pos, pend[idx]);
// 		}
// 		prevJacob = currentJacob;
// 		index++;
// 	}
// 	delimiter = worstCase;
// 	for (size_t i = pend.size(); i > prevJacob; i--) {
// 		size_t idx = i - 1;
// 		typename T_INT::iterator pos = std::upper_bound(worstCase, moveIt(delimiter, idx), pend[idx]);
// 		result.insert(pos, pend[idx]);
// 	}
// 	return ( result );
// }

// /* 
// 	@brief The goal of this function is to recursively create new pairs, to sort them, 
// 	then to separate between first and second into main and pending until size = 1
//  */

// template <template <class, class> class T>
// static T_INT mergeInsertion( T_INT & container )
// {
// 	T_PAIR pairs;
// 	for (typename T_INTCT it = container.begin(); it != container.end() && nextIt(it) != container.end(); it++) {
// 		typename T_INTCT	itFirst = it;
// 		it++;
// 		std::pair<int, int>	tmp (*itFirst, *it);
// 		pairs.push_back(tmp);
// 	}
// 	forEach(pairs.begin(), pairs.end(), pairSwap);
// 	T_INT	mainCont;
// 	T_INT	pendCont;
// 	for (typename T_PAIRT it = pairs.begin(); it != pairs.end(); it++) {
// 		mainCont.push_back(it->second);
// 		pendCont.push_back(it->first);
// 	}
// 	if (container.size() % 2)
// 		pendCont.push_back(container.back());
// 	T_INT newMain = mainCont;
// 	if (mainCont.size() > 2)
// 		newMain = mergeInsertion(mainCont);
// 	else {
// 		std::swap(mainCont.front(), mainCont.back());
// 		newMain = mainCont;
// 	}
// 	std::cout << pendCont << std::endl;
// 	T_INT ret = insertContent(newMain, pendCont);
// 	return ( ret );
// }

template <template <class, class> class T>
T<int, std::allocator<int> > insertContent(
    T<int, std::allocator<int> > const & main,
    T<int, std::allocator<int> > const & pend,
    T<int, std::allocator<int> > const & mainCont)  // ← on passe mainCont pour retrouver les "grands"
{
    typedef typename T_INT::iterator             Iter;

    T_INT result = main;

    if (pend.empty())
        return result;

    // Insérer pend[0] (son "grand" est mainCont[0], déjà dans result)
    {
        Iter bound = std::upper_bound(result.begin(), result.end(), mainCont[0]);
        Iter pos   = std::upper_bound(result.begin(), bound, pend[0]);
        result.insert(pos, pend[0]);
    }

    size_t index     = 1;
    size_t prevJacob = 1;

    while (true)
    {
        size_t currentJacob = jacobsthal(index);

        // Clamp au nombre d'éléments réellement disponibles
        size_t limit = currentJacob < pend.size() ? currentJacob : pend.size();

        // Insérer le batch courant en ordre décroissant d'indice
        for (size_t i = limit; i > prevJacob; i--)
        {
            size_t idx = i - 1;
            // borne supérieure = position du "grand" de pend[idx] dans result
            Iter bound = std::upper_bound(result.begin(), result.end(), mainCont[idx]);
            Iter pos   = std::upper_bound(result.begin(), bound, pend[idx]);
            result.insert(pos, pend[idx]);
        }

        prevJacob = limit;

        if (currentJacob >= pend.size())
            break;   // on sort APRÈS avoir inséré le batch

        index++;
    }

    // Éléments restants au-delà du dernier Jacobsthal complet
    for (size_t i = pend.size(); i > prevJacob; i--)
    {
        size_t idx = i - 1;
        Iter bound = std::upper_bound(result.begin(), result.end(), mainCont[idx]);
        Iter pos   = std::upper_bound(result.begin(), bound, pend[idx]);
        result.insert(pos, pend[idx]);
    }

    return result;
}

// ─── mergeInsertion ───────────────────────────────────────────────────────

template <template <class, class> class T>
T<int, std::allocator<int> > mergeInsertion(
    T<int, std::allocator<int> > & container)
{
    typedef typename T_INT::iterator                        Iter;
    typedef typename T_PAIR::iterator                       PairIter;

    // ── 1. Construire les paires ──────────────────────────────────────────
    T_PAIR pairs;
    {
        Iter it = container.begin();
        while (it != container.end())
        {
            Iter itFirst = it;
            ++it;
            if (it == container.end()) break;
            pairs.push_back(std::make_pair(*itFirst, *it));
            ++it;
        }
    }

    // ── 2. Trier chaque paire (petit, grand) ─────────────────────────────
    forEach(pairs.begin(), pairs.end(), pairSwap<PairIter>);

    // ── 3. Séparer main (grands) et pend (petits) ────────────────────────
    T_INT mainCont;
    T_INT pendCont;
    {
        PairIter it = pairs.begin();
        while (it != pairs.end())
        {
            mainCont.push_back(it->second);
            pendCont.push_back(it->first);
            ++it;
        }
    }

    // Élément impair → dans pend
    if (container.size() % 2)
        pendCont.push_back(container.back());

    // ── 4. Trier récursivement les grands ────────────────────────────────
    T_INT newMain;
    if (mainCont.size() > 2)
    {
        newMain = mergeInsertion<T>(mainCont);
    }
    else if (mainCont.size() == 2)
    {
        // Deux grands : on les trie simplement
        if (mainCont.front() > mainCont.back())
            std::swap(mainCont.front(), mainCont.back());
        newMain = mainCont;
    }
    else
    {
        newMain = mainCont;
    }

    // ── 5. Insérer les petits dans l'ordre Ford-Johnson ──────────────────
    // On reconstruit mainCont dans l'ordre original pour la correspondance d'indices.
    // Après tri récursif, mainCont est réordonné ; on passe mainCont original
    // non-trié pour retrouver le "grand" associé à chaque petit.
    // Note : mainCont ci-dessus a déjà été trié par la récursion si size > 2,
    // mais les indices pend[i] ↔ mainCont[i] restent valides CAR pend et mainCont
    // ont été construits ensemble avant le tri.
    T_INT ret = insertContent<T>(newMain, pendCont, mainCont);
    return ret;
}

template <template <class, class> class T>
void	PMergeMe<T>::fordJohnsonSort ( void )
{
	sorted_ = mergeInsertion<T>(cont_);
}
