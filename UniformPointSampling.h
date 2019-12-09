#include <glm/glm.hpp>
#include <vector>
#include <ctime>

using namespace glm;
using namespace std;

double triArea(vec3 v1, vec3 v2, vec3 v3) {
	vec3 e1, e2;
	e1 = v2 - v1;
	e2 = v3 - v1;

	return 0.5 * length(cross(e1, e2));
}

vector<vec3> pointSampling(vector<vec3> vertices,vector<int> indices) {
	
	vector<vec3> sampleList;
	int sampleNum = 500;
	int triNum = indices.size() / 3;
	vector<double> areas;

	srand(time(NULL));

	//calculate each triangle's area
	for (int i = 0; i < indices.size(); i=i+3) {
		areas.push_back(triArea(vertices[indices[i]], vertices[indices[i+1]], vertices[indices[i+2]]));		
	}

	//generate a vector of cumulative areas to remove size bias from face selection
	vector<double> cumulative(areas.size(), 0.0);
	cumulative[0] = areas[0];
	for (int i = 1; i < areas.size(); i++) {
		cumulative[i] = cumulative[i - 1] + areas[i];
	}

	for (int j = 0; j < sampleNum; j++) {
		double sample;
		int faceidx;

		//random face selection
		sample = (cumulative.back() - 0) * ((double)rand() / (double)RAND_MAX) + 0;
		for (faceidx = 0; cumulative[faceidx] < sample && faceidx < cumulative.size(); faceidx++);

		//random point generation within previously selected face area
		vec3 A, B, C, P;
		A = vertices[indices[faceidx * 3]];
		B = vertices[indices[faceidx * 3 + 1]];
		C = vertices[indices[faceidx * 3 + 2]];

		double alpha, beta;
		alpha = (1 - 0) * ((double)rand() / (double)RAND_MAX) + 0;
		beta = (1 - 0) * ((double)rand() / (double)RAND_MAX) + 0;

		float a, b, c;
		a = 1 - sqrt(beta);
		b = (sqrt(beta)) * (1 - alpha);
		c = sqrt(beta) * alpha;

		//resulting sample
		P = a*A + b*B + c*C;
		sampleList.push_back(P);
	}

	return sampleList;
}
