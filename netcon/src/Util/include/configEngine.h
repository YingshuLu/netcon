#ifndef __CONFIGENGINE_H_H_H__

#define __CONFIGENGINE_H_H_H__
/*Common */
#include <iostream>
#include <string>
#include <map>

#define SECTB  '['
#define SECTE  ']'
#define COMTB  '#'
#define KEYB   '='

const int SECTION = 0;
const int COMMENT = 1;
const int KEYVAL = 2;
const int ERRLINE = -1;

class configEngine
{

public:

	static configEngine* getInstance();

	void setConfigPath(const std::string&);

	std::string getValueByKey(const std::string& section, const std::string& key);

	void getAllKey();
private:

	configEngine() :isFileExisted(false), isRefreshed(false){}

	configEngine(const std::string&);

	std::string filename;

	bool isFileExisted;

	bool isRefreshed;

	//map <section map<key, value>>
	std::map<std::string, std::map<std::string, std::string> > configMap;

	int loadConfig2Map();

	bool isCommented(const std::string& line);

	bool isVaildSetting(const std::string& line);

	bool isVaildSection(const std::string& line);

	int decideLineType(const std::string& line, std::string& content);

	static configEngine* pInstance;

};


#endif
