#pragma once
#include <vtkPoints.h>
#include <vtkLine.h>

#include <vtkSphereSource.h>
#include <vtkGlyph3D.h>

#include <vtkCellArray.h>

#include <vtkSmartPointer.h>

#include <vtkTubeFilter.h>
#include <vtkTriangleFilter.h>

#include <vtkPolyData.h>
#include <vtkPolyDataNormals.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkProperty.h>

#include <vtkPolyDataBooleanFilter.h>

#include <vtkOBJExporter.h>
#include <vtkOBJReader.h>

#include "SlidingAverageFilter.h"

class Tube
{
public:
	Tube();
	~Tube();

private:

public:
	void InsertPointsFromFile(const char * filename);
	void InsertPoints(const vector<vector<double>> &points);
	void GenerateTube(double radius = 1.5, int res = 16);

	inline vtkSmartPointer<vtkTubeFilter> GetTubeFilter() { return m_TubeFilter; }
	inline vtkSmartPointer<vtkActor> GetTubeActor() { return m_TubeActor; }
	inline vtkSmartPointer<vtkActor> GetLineActor() { return m_LineActor; }
	inline vtkSmartPointer<vtkActor> GetGlyphActor() { return m_GlyphActor; }

private:
	// Basic members
	vtkSmartPointer<vtkPoints> m_Points;
	vtkSmartPointer<vtkCellArray> m_Connectivity;
	vtkSmartPointer<vtkLine> m_Line;
	vtkSmartPointer<vtkPolyData> m_PolyData;

	// Tube members
	vtkSmartPointer<vtkTubeFilter> m_TubeFilter;
	vtkPolyDataMapper *m_TubeMapper;
	vtkSmartPointer<vtkActor> m_TubeActor;

	// Line members
	vtkPolyDataMapper *m_LineMapper;
	vtkSmartPointer<vtkActor> m_LineActor;

	// gylph members
	vtkSmartPointer<vtkSphereSource> m_Ball;
	vtkSmartPointer<vtkGlyph3D> m_Glyph;
	vtkPolyDataMapper *m_GlyphMapper;
	vtkSmartPointer<vtkActor> m_GlyphActor;
};

class Merger
{
public:
	Merger();
	~Merger();

	void SetInput(vtkSmartPointer<vtkTubeFilter> tube1, vtkSmartPointer<vtkTubeFilter> tube2);
	void Merge();

	inline vtkSmartPointer<vtkActor> GetMergerActor() { return m_Actor; }

private:
	vtkPolyDataBooleanFilter* m_BooleanFilter;
	vtkSmartPointer<vtkPolyDataNormals> m_Normal;
	vtkSmartPointer<vtkTriangleFilter> m_TriFilter1;
	vtkSmartPointer<vtkTriangleFilter> m_TriFilter2;
	vtkSmartPointer<vtkPolyDataMapper> m_Mapper;
	vtkSmartPointer<vtkActor> m_Actor;
};

namespace ObjFileManager
{
	inline void SaveAsObjFile(std::string filename, vtkRenderWindow *renWin)
	{
		vtkSmartPointer<vtkOBJExporter> exporter = vtkSmartPointer<vtkOBJExporter>::New();
		exporter->SetFilePrefix(filename.c_str());
		exporter->SetInput(renWin);
		exporter->Write();
	}
	inline vtkSmartPointer<vtkOBJReader> ReadObjFile(std::string filename)
	{
		vtkSmartPointer<vtkOBJReader> reader = vtkSmartPointer<vtkOBJReader>::New();
		reader->SetFileName(filename.c_str());
		reader->Update();

		return reader;
	}
}