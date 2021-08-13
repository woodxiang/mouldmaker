#include <iostream>

#include <BRepTools.hxx>
#include <BRepPrimAPI_MakeBox.hxx>
#include <BRepPrimAPI_MakeCylinder.hxx>
#include <BRepPrimAPI_MakeSphere.hxx>
#include <BRepMesh_IncrementalMesh.hxx>
#include <BRepAlgoAPI_Fuse.hxx>
#include <BRep_Tool.hxx>
#include <TopExp_Explorer.hxx>
#include <BRepBuilderAPI_Transform.hxx>
#include <TopoDS.hxx>
#include <Poly.hxx>

#include <fstream>
#include <sstream>
#include "test.h"

int main()
{
 	const Standard_Real radius = 10.0;
	const Standard_Real height = 25.0;

	TopoDS_Shape cylindar = BRepPrimAPI_MakeCylinder(radius, height);
	TopoDS_Shape box = BRepPrimAPI_MakeBox(20, 20, 20);

	gp_Trsf trsf;
	trsf.SetTranslation(gp_Vec(-10, -10, -10));

	BRepBuilderAPI_Transform transform(box, trsf);

	box = transform.Shape();

	TopoDS_Shape shape = BRepAlgoAPI_Fuse(cylindar, box);

	// TopoDS_Shape shape = BRepPrimAPI_MakeSphere(radius);

	// TopoDS_Shape shape = BRepPrimAPI_MakeBox(10, 20, 30);

	const Standard_Real linearDeflection = 0.1;
	const Standard_Real angluarDeflection = 0.5;
	BRepMesh_IncrementalMesh mesher(shape, linearDeflection, Standard_False, angluarDeflection, Standard_True);

	mesher.Perform();

	const Standard_Integer status = mesher.GetStatusFlags();

	BRepTools::Triangulation(shape, 0.01);

	SaveSTL(shape);

	for (TopExp_Explorer topoIt(shape, TopAbs_EDGE); topoIt.More(); topoIt.Next())
	{
		auto& edge = TopoDS::Edge(topoIt.Current());
	}

	return 0;

}

void SaveSTL(TopoDS_Shape& shape)
{
	// generate stl
	//
	std::stringstream ss;
	ss << "test" << ".stl";

	std::ofstream ofs(ss.str());
	ofs << "solid test" << std::endl;

	for (TopExp_Explorer topoIt(shape, TopAbs_FACE); topoIt.More(); topoIt.Next())
	{
		auto& face = TopoDS::Face(topoIt.Current());
		TopLoc_Location dummyLoc;
		auto& triList = BRep_Tool::Triangulations(face, dummyLoc);
		auto& trsf = dummyLoc.Transformation();
		Standard_Boolean isMirrored = trsf.VectorialPart().Determinant() < 0;

		for (auto it = triList.cbegin(); it != triList.cend(); it++)
		{
			auto& tris = *it;
			Poly::ComputeNormals(tris);
			std::cout << "triangles Count " << tris->NbTriangles() << std::endl;
			for (int i = 1; i <= tris->NbTriangles(); i++)
			{
				auto& tri = tris->Triangle(i);
				Standard_Integer v1, v2, v3;
				tri.Get(v1, v2, v3);
				std::cout << "Triangle " << i << "uses points (" << v1 << "," << v2 << "," << v3 << ")" << std::endl;

				auto p1 = tris->Node(v1);
				auto p2 = tris->Node(v2);
				auto p3 = tris->Node(v3);

				auto normal = tris->Normal(v1);
				if ((face.Orientation() == TopAbs_REVERSED) ^ isMirrored)
				{
					normal.Reverse();
					auto p = p2;
					p2 = p3;
					p3 = p;
				}
				if (!dummyLoc.IsIdentity())
				{
					p1.Transform(trsf);
					p2.Transform(trsf);
					p3.Transform(trsf);
					normal.Transform(trsf);
				}

				ofs << "facet normal " << normal.X() << " " << normal.Y() << " " << normal.Z() << std::endl;
				ofs << "\touter loop" << std::endl;
				ofs << "\t\t vertex " << p1.X() << " " << p1.Y() << " " << p1.Z() << std::endl;
				ofs << "\t\t vertex " << p2.X() << " " << p2.Y() << " " << p2.Z() << std::endl;
				ofs << "\t\t vertex " << p3.X() << " " << p3.Y() << " " << p3.Z() << std::endl;
				ofs << "\tendloop" << std::endl;
				ofs << "endfacet" << std::endl;
			}
		}
	}

	ofs << "endsolid test" << std::endl;
	ofs.close();
}
