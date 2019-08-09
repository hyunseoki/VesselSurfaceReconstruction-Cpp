#include "CsvManager.h"



CsvManager::CsvManager()
{
}


CsvManager::~CsvManager()
{
}


void CsvManager::WriteCSV(const char * filename = "unnamed.csv")
{
	// TODO: Add your implementation code here.
	m_sStream.open(filename);
}

void CsvManager::ChangeRow()
{
	// TODO: Add your implementation code here.
	m_sStream << "\n";
}


void CsvManager::CloseCSV()
{
	// TODO: Add your implementation code here.
	m_sStream.close();
}
