#pragma once
#include <fstream>

class CsvManager
{
public:
	CsvManager();
	~CsvManager();


	void WriteCSV(const char * filename);
	
	template<typename T>
	void Write(T s)
	{
		m_sStream << s << ",";
	}

	void ChangeRow();
	void CloseCSV();
private:
	std::ofstream m_sStream;
};

