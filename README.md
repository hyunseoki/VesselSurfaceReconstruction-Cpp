# Vessel_Surface_Reconstruction-C
Blood vessel surface reconstruction from vessel center skeleton using VTK

During this project, I found that boolean function is unstable and decided to employ Romer's vtkBooleanOperation function instead of vtk's one 

I poseted it in VTK forum and they guided Romer's boolean function 
VTK Forum : https://discourse.vtk.org/t/mesh-flaw-occurs-when-using-vtkbooleanoperation/1502/9
Romer's codes :  https://github.com/zippy84/vtkbool

You may need to build Romer's vtk add-on libary

At now, it seems that vtk employ Romer's function as their basic function. You may check it and can use newly released vtk version

You can ask me hyunseoki@kaist.ac.kr
