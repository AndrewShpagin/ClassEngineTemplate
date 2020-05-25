#pragma once
struct meshEdge {
	int OppositeEdge;
	int NextEdge;
};
struct meshVertex {
	cVec3 Pos;
	int Layer;
	int next;
};
struct meshVertexRef {
	int Index;
	int next;
};
struct meshUvVertex {
	cVec2 Uv;
	int Layer;
	int next;
};
struct meshVertexPbr {
	cVec4 Color;
	float Gloss;
	float Metall;
	int Layer;
	int next;	
};

struct meshFace {
	int Object;
	int cellID;
	bool Visible : 1;
	bool Hidden : 1;
};
struct meshObject {
	cStr Name;
	bool Visible;
};
struct meshTextureLayer {
	cStr Name;
};
struct meshVertexTexture {
	cStr Name;
};
struct meshFonV {
	int Face;
	int NextV;
	int next;
};

template <class X> using LayersOf = Layered<X, int, int>;

class GeneralMesh {
public:
	clist<meshObject> Objects;
	//clist<meshEdge> edges;
	clist<meshFace> faces;

	///faces on vertices
	LayersOf<meshFonV> FonV;
	
	///list of vertices over the face
	LayersOf<meshVertexRef> geometry;

	///vertex positons and layers of additional displacement
	LayersOf<meshVertex> verts;

	///uv-coordinates of verts over the faces
	LayersOf<meshUvVertex> uv;

	///pbr values over the pos - vertex
	LayersOf<meshVertexPbr> pbr;

	
	LayersOf<int> facesInCells;
	

	int addObject(const char* name);
	int addFace(int Object);
	void addVertex(int index, const cVec3& pos, int Layer);
	void finishFace(int f);
	void addUvVertexToFace(int Face, const cVec2& uv, int Layer);
	void addVertexToFace(int Face, int Vertex);

	///walking the mesh
	///walk vertices on the face
	class verts_on_face {
		Layered<meshVertexRef, int, int>::scan_context context;
		GeneralMesh* mesh;
	public:
		inline verts_on_face(GeneralMesh& mesh, int face);
		inline bool next();
		inline int vertex();
		inline int vertex(int idx);
		inline int count();
	};
	///walk edges on the face
	class edges_on_face {
		Layered<meshVertexRef, int, int>::scan_context context;
		GeneralMesh* mesh;
	public:
		inline edges_on_face(GeneralMesh& mesh, int face);
		inline bool next();
		inline int opposite_face();
		inline int vertex1();
		inline int vertex2();
	};
	///walk faces on the vertex
	class faces_on_vertex {
		Layered<meshFonV, int, int>::scan_context context;
		GeneralMesh* mesh;
	public:
		inline faces_on_vertex(GeneralMesh& mesh,int vertex);
		inline bool next();
		inline int face();
		inline int vertex_on_face();
	};
	///walk vertices near vertex
	class verts_near_vert {
		Layered<meshFonV, int, int>::scan_context context;
		GeneralMesh* mesh;
	public:
		inline verts_near_vert(GeneralMesh& mesh, int vertex);
		inline bool next();
		inline int vertex();
		///fast!!
		inline int face1();
		///slow!!!
		inline int face2();
	};
};

inline GeneralMesh::verts_on_face::verts_on_face(GeneralMesh& _mesh, int face) {
	mesh = &_mesh;
	context = mesh->geometry.context(face);
}

inline bool GeneralMesh::verts_on_face::next() {
	return mesh->geometry.next(context);
}

inline int GeneralMesh::verts_on_face::vertex() {
	return context.cur ? context.cur->Index : -1;
}

inline int GeneralMesh::verts_on_face::vertex(int idx) {
	meshVertexRef* ref = mesh->geometry.get(context.Index, idx);
	return ref ? ref->Index : -1;
}

inline int GeneralMesh::verts_on_face::count() {
	return mesh->geometry.size(context.Index);
}

inline GeneralMesh::edges_on_face::edges_on_face(GeneralMesh& _mesh, int face) {
	mesh = &_mesh;
	context = mesh->geometry.context(face);
}

inline bool GeneralMesh::edges_on_face::next() {
	return mesh->geometry.next_edge(context);
}

inline int GeneralMesh::edges_on_face::opposite_face() {
	if(context.prev && context.cur) {
		int vc = context.cur->Index;
		int vp = context.prev->Index;
		auto co = mesh->FonV.context(vc);
		while(mesh->FonV.next(co)) {
			if (co.cur->NextV == vp)return co.cur->Face;
		}
	}
	return -1;
}

inline int GeneralMesh::edges_on_face::vertex1() {
	return context.prev ? context.prev->Index : -1;
}

inline int GeneralMesh::edges_on_face::vertex2() {
	return context.cur ? context.cur->Index : -1;
}

inline GeneralMesh::faces_on_vertex::faces_on_vertex(GeneralMesh& _mesh, int vertex) {
	mesh = &_mesh;
	context = mesh->FonV.context(vertex);
}

inline bool GeneralMesh::faces_on_vertex::next() {
	return mesh->FonV.next(context);
}

inline int GeneralMesh::faces_on_vertex::face() {
	return context.cur ? context.cur->Face : -1;
}

inline int GeneralMesh::faces_on_vertex::vertex_on_face() {
	return context.cur ? context.cur->NextV : -1;
}

inline GeneralMesh::verts_near_vert::verts_near_vert(GeneralMesh& _mesh, int vertex) {
	mesh = &_mesh;
	context = mesh->FonV.context(vertex);
}

inline bool GeneralMesh::verts_near_vert::next() {
	return mesh->FonV.next(context);
}

inline int GeneralMesh::verts_near_vert::vertex() {
	return context.cur ? context.cur->NextV : -1;
}

inline int GeneralMesh::verts_near_vert::face1() {
	return context.cur ? context.cur->Face : -1;
}

inline int GeneralMesh::verts_near_vert::face2() {
	int vc = context.cur->NextV;
	int vp = context.Index;
	auto co = mesh->FonV.context(vc);
	while (mesh->FonV.next(co)) {
		if (co.cur->NextV == vp)return co.cur->Face;
	}
	return -1;
}