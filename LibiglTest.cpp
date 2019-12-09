#include <iostream>
#include <UniformPointSampling.h>
#include <igl/readOBJ.h>
#include <igl/opengl/glfw/Viewer.h>

Eigen::MatrixXd V;
Eigen::MatrixXi F;

void iglToVectors(vector<vec3> &vertices, vector<int> &indices) {
	for (int i = 0; i < V.rows(); i++) vertices.push_back(vec3(V.row(i)(0), V.row(i)(1), V.row(i)(2)));
	for (int i = 0; i < F.rows(); i++) { 
		indices.push_back(F.row(i)(0)); 
		indices.push_back(F.row(i)(1));
		indices.push_back(F.row(i)(2));
	}
}

void main() {
	vector<vec3> vertices,samples;
	vector<int> indices;

	igl::readOBJ("head.obj", V, F);
	iglToVectors(vertices, indices);
	samples=pointSampling(vertices, indices);

	//sample vector to eigen matrix
	Eigen::MatrixXd P;
	P.resize(samples.size(),3);
	for (int i = 0; i < samples.size(); i++) {
		P.row(i) = Eigen::Vector3d(samples[i].x, samples[i].y, samples[i].z);
	}

	//initialize igl viewer
	igl::opengl::glfw::Viewer viewer;
	viewer.data().set_mesh(V, F);
	viewer.data().add_points(P, Eigen::RowVector3d(0, 0, 1));
	viewer.launch();
}