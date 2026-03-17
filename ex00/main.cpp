/* *************************************************************************************************************** */
/*   main.cpp                                                                                                      */
/*   By: lvan-bre                                                                   .,                             */
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



#include "BitcoinExchange.hpp"

static int dateChecking ( std::string date )
{
	std::string	strYear;
	std::string	strMonth;
	std::string	strDay;
	int	year;
	int	month;
	int	day;
	int len;

	while (date[len] != '-') {
		if (!std::isdigit(date[len]))
			return (INVALID);
		strYear += date[len++];
	}
	year = atoi(strYear.c_str());
	len++;
	while (date[len] != '-') {
		if (!std::isdigit(date[len]))
			return (INVALID);
		strMonth += date[len++];
	}
	month = atoi(strMonth.c_str());
	if (month > 12)
		return (INVALID);
	len++;
	while (date[len] != ',') {
		if (!std::isdigit(date[len]))
			return (INVALID);
		strDay += date[len];
	}
	day = atoi(strDay.c_str());

	int		year_nonleap[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	int 	year_leap[12] = { 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	bool	is_leap = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);

	if ( !is_leap ) {
		if (year_nonleap[month - 1] < day)
			return (INVALID);
	}
	else
		if (year_leap[month - 1] < day)
			return (INVALID);
			
	return (len);
}


static std::map<std::string, int> dataParsing ( std::ifstream & data )
{
	std::string					ctn;
	std::map<std::string, int>	Map;
	int							val;
	int							line = 0;
	int							dateLen;
	
	while (getline(data, ctn)) {
		dateLen = dateChecking(ctn);
		if (dateLen == INVALID)	
			throw (parsingError("data.csv", line));
		line++;
	}
	return (Map);
}

int main ( int ac, char **av )
{
	using	std::cout;

	if ( ac != 2 ) {
		cout << "Fatatl error : btc takes one .txt arg\n";
		return 1;
	}
	/* ARG AND FILES CHECKING  */

	/* Opening and parsing of data.csv and putting the result in dataMap */

	std::ifstream	data("data.csv");
	try {
		std::map<std::string, int> dataMap = dataParsing(data);
	}
	catch (parsingError &e) {
		std::cout << e.what() << std::endl;
		return (1);
	}
	// Opening import file and getting fd
	std::ifstream	ifs(av[1]);

	
}