#include "pch.h"
#include "ObjectManager.h"

#include <string>
#include <sstream>
#include <fstream>

Tube::Tube()
{
	m_Points = vtkSmartPointer<vtkPoints>::New();
	m_Connectivity = vtkSmartPointer<vtkCellArray>::New();
	m_Line = vtkSmartPointer<vtkLine>::New();
	m_PolyData = vtkSmartPointer<vtkPolyData>::New();

	m_TubeFilter = vtkSmartPointer<vtkTubeFilter>::New();
	m_TubeMapper = vtkPolyDataMapper::New();
	m_TubeActor = vtkSmartPointer<vtkActor>::New();

	m_LineMapper = vtkPolyDataMapper::New();
	m_LineActor = vtkSmartPointer<vtkActor>::New();

	m_Ball = vtkSmartPointer<vtkSphereSource>::New();
	m_Glyph = vtkSmartPointer<vtkGlyph3D>::New();
	m_GlyphMapper = vtkPolyDataMapper::New();
	m_GlyphActor = vtkSmartPointer<vtkActor>::New();
}

Tube::~Tube()
{
}

void Tube::InsertPointsFromFile(const char * filename)
{
	////// TODO: Add your implementation code here.
	std::string line, cell;

	std::vector<double> point;
	vector<vector<double>> points;

	std::ifstream m_readStream;
	m_readStream.open(filename);

	while (!m_readStream.eof())
	{
		std::getline(m_readStream, line);
		std::stringstream ss(line);
		while (std::getline(ss, cell, ','))
		{
			point.push_back(std::stod(cell));
		}

		if (point.size()) points.push_back(point);

		point.clear();
	}

	vector<vector<double>> result = SlidingAverageFilter::RecursiveSlidingAverageFilter(points);
	   	 
	InsertPoints(result);

	//int j = 0;
	//while (!m_readStream.eof())
	//{
	//	std::getline(m_readStream, line);
	//	std::stringstream ss(line);

	//	double point[3];
	//	int i = 0;

	//	while (std::getline(ss, cell, ','))
	//	{
	//		point[i] = std::stod(cell);
	//		i++;
	//	}

	//	vtkSmartPointer<vtkLine> _line = vtkSmartPointer<vtkLine>::New();

	//	if (i == 3) 
	//	{
	//		m_Points->InsertNextPoint(point[0], point[1], point[2]);
	//		if (j)
	//		{
	//			_line->GetPointIds()->SetId(0, j - 1);
	//			_line->GetPointIds()->SetId(1, j);
	//			m_Connectivity->InsertNextCell(_line);
	//		}
	//		j++;
	//	}
	//}
}

void Tube::InsertPoints(const vector<vector<double>>& points)
{
	int pointNb = (int)(points.size());

	m_Points->SetNumberOfPoints(pointNb);
	m_Connectivity->InsertNextCell(pointNb);

	for (int i = 0; i < pointNb; i++)
	{
		m_Points->InsertPoint(i, points[i][0], points[i][1], points[i][2]);
		m_Connectivity->InsertCellPoint(i);
	}
}

void Tube::GenerateTube(double radius, int res)
{
	// TODO: Add your implementation code here.
	m_PolyData->SetPoints(m_Points);
	m_PolyData->SetLines(m_Connectivity);

	m_TubeFilter->SetInputData(m_PolyData);
	m_TubeFilter->SetNumberOfSides(res);
	m_TubeFilter->SetRadius(radius);

	m_TubeMapper->SetInputConnection(m_TubeFilter->GetOutputPort());
	m_TubeActor->SetMapper(m_TubeMapper);
	m_TubeActor->GetProperty()->SetOpacity(0.5);

	m_LineMapper->SetInputData(m_PolyData);
	m_LineActor->SetMapper(m_LineMapper);
	m_LineActor->GetProperty()->SetColor(0.0, 1.0, 0.0);

	m_Glyph->SetInputData(m_PolyData);
	m_Glyph->SetSourceConnection(m_Ball->GetOutputPort());
	m_Glyph->SetScaleFactor(0.07);

	m_GlyphMapper->SetInputConnection(m_Glyph->GetOutputPort());
	m_GlyphActor->SetMapper(m_GlyphMapper);
	m_GlyphActor->GetProperty()->SetColor(1.0, 0.0, 0.0);
}

Merger::Merger()
{
	m_BooleanFilter = vtkPolyDataBooleanFilter::New();
	m_Normal = vtkSmartPointer<vtkPolyDataNormals>::New();
	m_TriFilter1 = vtkSmartPointer<vtkTriangleFilter>::New();
	m_TriFilter2 = vtkSmartPointer<vtkTriangleFilter>::New();
	m_Mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
	m_Actor = vtkSmartPointer<vtkActor>::New();
}

Merger::~Merger()
{
}

void Merger::SetInput(vtkSmartPointer<vtkTubeFilter> tube1, vtkSmartPointer<vtkTubeFilter> tube2)
{
	// TODO: Add your implementation code here.
	m_TriFilter1->SetInputConnection(tube1->GetOutputPort());
	m_TriFilter2->SetInputConnection(tube2->GetOutputPort());

	m_BooleanFilter->SetInputConnection(0, m_TriFilter1->GetOutputPort());
	m_BooleanFilter->SetInputConnection(1, m_TriFilter2->GetOutputPort());
}


void Merger::Merge()
{
	// TODO: Add your implementation code here.
	m_BooleanFilter->SetOperModeToUnion();
	m_BooleanFilter->Update();

	m_Normal->SetInputData(m_BooleanFilter->GetOutput());
	m_Normal->ComputePointNormalsOn();
	m_Normal->ComputeCellNormalsOn();
	m_Normal->Update();

	m_Mapper->SetInputConnection(m_Normal->GetOutputPort());
	//m_Mapper->SetInputConnection(m_BooleanFilter->GetOutputPort());

	m_Actor->SetMapper(m_Mapper);
}
