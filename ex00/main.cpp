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

static int dateChecking ( std::string date, char separation)
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
	while (date[len] != separation  && date[len]) {
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

static std::map<std::string, float> dataParsing ( std::ifstream & p_data )
{
	std::string						ctn;
	std::string						buf;
	std::map<std::string, float>	data;
	int								line = 2;
	int								dateLen;

	getline(p_data,ctn);
	while (getline(p_data, ctn)) {
		dateLen = dateChecking(ctn, ',');
		if (dateLen == INVALID)	
			throw (parsingError("data.csv", line, ctn));
		else {
			int	decimal = 0;
			for (std::string::iterator it = ctn.begin() + dateLen + 1; it != ctn.end(); it++) {
				if (*it == '.')
					decimal++;
				if ((!std::isdigit(*it) && *it != '.') || (*it == '.'  && decimal > 1))
					throw (parsingError("data.csv", line, ctn));
			}
			buf = ctn;
			buf.erase(dateLen);
			data[buf] = std::strtof((ctn.c_str() + dateLen + 1), NULL);
		}
		line++;
	}
	return (data);
}

static void	algorithm ( std::map<std::string, float> p_data, std::string p_infDate, float p_value )
{
	(void)p_data;
	switch (static_cast<int>(p_value))
	{
	case INVALID:
		std::cout << "Error: bad input => " << p_infDate << "\n";
		return ;
	case NEGATIVE:
		std::cout << "Error: not a positive number" << "\n";
		return ;
	case TOO_LARGE:
		std::cout << "Error: too large of a number" << "\n";
		return ;
	}
	for (std::map<std::string, float>::iterator it = p_data.begin(); it != p_data.end(); it++) {
		if (std::strcmp(it->first.c_str(), p_infDate.c_str()) > 0) {
			it--;
			std::cout << p_infDate << " => " << p_value << " = " << it->second * p_value << "\n";
			return ;
		}
	}

}

static void	infileParsing ( std::ifstream & p_ifs, std::map<std::string, float> p_data )
{
	std::string	ctn;
	std::string	buf;
	int			dateLen;
	float		val;
	
	while (getline(p_ifs, ctn)) {
		dateLen = dateChecking(ctn, ' ');
		val = std::strtof((ctn.c_str() + dateLen + 3), NULL);
		if (val > 1000.0f) 
			val = TOO_LARGE;
		else if (val < 0.0f)
			val = NEGATIVE;
		if (val < 0) {
			algorithm(p_data, ctn, val);
			continue ;
		}
		if (dateLen == INVALID || ctn[dateLen + 1] != '|' || ctn[dateLen + 2] != ' ') {
			val = INVALID;
			algorithm(p_data, ctn, val);
			continue ;
		}
		int	decimal = 0;
		int symbol = 0;
		for (std::string::iterator it = ctn.begin() + dateLen + 3; it != ctn.end(); it++) {
			if (*it == '-')
				symbol++;
			if (*it == '.')
				decimal++;
			if ((!std::isdigit(*it) && *it != '.') || (*it == '.'  && decimal > 1) || ((*it == '-' || *it == '+') && symbol > 1))
				val = INVALID;
		}
		buf = ctn;
		if (val != INVALID)
			buf.erase(dateLen);
		algorithm(p_data, buf, val);
	}
	return ;
}

int main ( int ac, char **av )
{
	using	std::cout;

	if ( ac != 2 ) {
		cout << "Fatal error : btc takes one '.txt' arg\n";
		return 1;
	}
	/* ARG AND FILES CHECKING  */

	/* Opening and parsing of data.csv and the file taken in argv[1] and putting the result in dataMap */
	std::ifstream	data("data.csv");
	if (!data.is_open()) {
		std::cout << "Fatal error : couldn't open data.csv" << std::endl;
		return (1);
	}
	std::ifstream	ifs(av[1]);
	if (!ifs.is_open()) {
		std::cout << "Fatal error : couldn't open " << av[1] << std::endl;
		return (1);
	}	
	try {
		std::map<std::string, float>	dataMap = dataParsing(data);
		infileParsing(ifs, dataMap);
	}
	catch (parsingError &e) {
		std::cout << e.what() << " in " << e.getFile() << " at line " << e.getLine() << " : " << e.getError() << std::endl;
		return (1);
	}
	return (0);
}