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
	int len = 0;

	while (date[len] != '-' && date[len]) {
		if (!std::isdigit(date[len]))
			return (INVALID);
		strYear += date[len++];
	}
	if (!date[len])
		return (INVALID);
	year = std::atoi(strYear.c_str());
	len++;
	while (date[len] != '-'  && date[len]) {
		if (!std::isdigit(date[len]))
			return (INVALID);
		strMonth += date[len++];
	}
	month = std::atoi(strMonth.c_str());
	if (month > 12 || month < 1 || !date[len])
		return (INVALID);
	len++;
	while (date[len] != ','  && date[len]) {
		if (!std::isdigit(date[len]))
			return (INVALID);
		strDay += date[len++];
	}
	if (!date[len])
		return (INVALID);
	day = std::atoi(strDay.c_str());

	int		year_nonleap[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	int 	year_leap[12] = { 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	bool	is_leap = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);

	if ( !is_leap ) {
		if (day < 1 || year_nonleap[month - 1] < day)
			return (INVALID);
	}
	else
		if (day < 1 || year_leap[month - 1] < day)
			return (INVALID);
			
	return (len);
}


static std::map<std::string, int> dataParsing ( std::ifstream & p_data )
{
	std::string					ctn;
	std::string					buf;
	std::map<std::string, int>	data;
	int							line = 0;
	int							dateLen;

	getline(p_data,ctn);
	while (getline(p_data, ctn)) {
		dateLen = dateChecking(ctn);
		if (dateLen == INVALID)	
			throw (parsingError("data.csv", line));
		else {
			buf = ctn;
			buf.erase(dateLen);
			data[buf] = std::atoi(ctn.c_str() + dateLen + 1);
		}
		line++;
	}
	for (std::map<std::string, int>::iterator it = data.begin(); it != data.end(); it++)
		std::cout << it->first << " value : " << it->second << std::endl; 
	return (data);
}

int main ( int ac, char **av )
{
	using	std::cout;

	if ( ac != 2 ) {
		cout << "Fatal error : btc takes one '.txt' arg\n";
		return 1;
	}
	/* ARG AND FILES CHECKING  */

	/* Opening and parsing of data.csv and putting the result in dataMap */

	std::ifstream	data("data.csv");
	try {
		std::map<std::string, int> dataMap = dataParsing(data);
	}
	catch (parsingError &e) {
		std::cout << e.what() << " at line " << e.getLine() << std::endl;
		return (1);
	}
	// Opening import file and getting fd
	std::ifstream	ifs(av[1]);

	
}