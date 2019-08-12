#include "pch.h"

#include "ObjectManager.h"

int main()
{

	Tube tube1, tube2;
	tube1.InsertPointsFromFile("./data/points3D_1.csv");
	tube1.GenerateTube(1.0);

	tube2.InsertPointsFromFile("./data/points3D_2.csv");
	tube2.GenerateTube(1.5);
	
	Merger merger;
	merger.SetInput(tube1.GetTubeFilter(), tube2.GetTubeFilter());
	merger.Merge();

	vtkRenderer *ren = vtkRenderer::New(); 
	ren->AddActor(tube1.GetGlyphActor());
	ren->AddActor(tube1.GetLineActor());
	ren->AddActor(tube1.GetTubeActor());

	ren->AddActor(tube2.GetGlyphActor());
	ren->AddActor(tube2.GetLineActor());
	ren->AddActor(tube2.GetTubeActor());

	ren->AddActor(merger.GetMergerActor());

	vtkRenderWindow *renWin = vtkRenderWindow::New();
	renWin->AddRenderer(ren);

	vtkRenderWindowInteractor *iren = vtkRenderWindowInteractor::New();
	vtkInteractorStyleTrackballCamera *style = vtkInteractorStyleTrackballCamera::New();
	iren->SetInteractorStyle(style);
	iren->SetRenderWindow(renWin);

	ren->SetBackground(0.4, 0.5, 0.6);
	renWin->SetSize(800, 800);
	renWin->Render();

	renWin->SetWindowName("Surface Renderer"); // Render() 다음에 SetWindowName이 와야 함

	iren->Start();
	
	//ObjFileManager::SaveAsObjFile("union_vtk", renWin);

	return 0;
}

