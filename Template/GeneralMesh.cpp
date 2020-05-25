#include <iostream>
#include <algorithm>
#include <functional>
#include <mutex>
#include "comms-Math/comms-Math.h"
#include "ClassEngine/classengine.h"
#include "ClassEngine/types.h"
#include "ClassEngine/Layered.h"
#include "GeneralMesh.h"

void test() {
	GeneralMesh m;
}

int GeneralMesh::addObject(const char* name) {
	meshObject obj;
	int n = Objects.Add(obj);
	meshObject& ob = Objects.GetLast();
	ob.Name = name;
	ob.Visible = true;
	return n;
}

int GeneralMesh::addFace(int Object) {
	meshFace ff;
	int n = faces.Add(ff);
	geometry.EnsureIndexExists(n);
	meshFace& f = faces.GetLast();
	f.Object = Object;
	f.cellID = -1;
	f.Visible = true;
	f.Hidden = false;
	return n;
}

void GeneralMesh::addVertex(int id, const cVec3& pos, int Layer) {
	meshVertex* m = verts.Add(id, Layer);
	m->Pos = pos;
}

void GeneralMesh::finishFace(int f) {
	auto co = geometry.context(f);
	while(geometry.next_edge(co)) {
		meshFonV* mv = FonV.Add(co.prev->Index);
		mv->Face = f;
		mv->NextV = co.cur->Index;
	}
}

void GeneralMesh::addUvVertexToFace(int Face, const cVec2& uu, int Layer) {
	meshUvVertex* mv = uv.Add(Face, Layer);
	if(mv) {
		mv->Uv = uu;
	}
}

void GeneralMesh::addVertexToFace(int Face, int Vertex) {
	if (Face >= 0 && Face < faces.Count()) {
		meshVertexRef* m = geometry.Add(Face);
		if(m)m->Index = Vertex;
	}
}







