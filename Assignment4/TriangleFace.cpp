//#include "TriangleFace.h"
//
//#define EPSILON 0.000001
//
//TriangleFace::TriangleFace()
//{
//}
//
//
//TriangleFace::~TriangleFace()
//{
//}
//
//bool TriangleFace::RayIntersect(const Ray& ray, Vec3f& p, bool barycentricCoord) const
//{
//	Vec3f edge1, edge2, tvec, pvec, qvec;
//	double det, inv_det, t, u ,v;
//	Vec3f dir = ray.GetDir();
//	Vec3f ori = ray.GetOri();
//
//	edge1 = v1.position - v0.position;
//	edge2 = v2.position - v0.position;
//	pvec = dir.cross(edge2);
//	det = edge1.dot(pvec);
//#ifndef NON_TEST_CULL
//	if (det < EPSILON)
//		return false;
//
//	tvec = ori - v0.position;
//	u = tvec.dot(pvec);
//	if (u<0.0 || u>det)
//		return false;
//
//	qvec = tvec.cross(edge1);
//	v = dir.dot(qvec);
//	if (v<0.0 || u + v>det)
//		return false;
//
//	t = edge2.dot(qvec);
//	inv_det = 1.0 / det;
//	t *= inv_det;
//	u *= inv_det;
//	v *= inv_det;
//#else
//	if (det > -EPSILON && det < EPSILON)
//		return false;
//	inv_det = 1.0 / det;
//	tvec = ori - v0.position;
//	
//	u = tvec.dot(pvec)*inv_det;
//	if (u<0.0 || u>1.0)
//		return 0;
//
//	qvec = tvec.cross(edge1);
//
//	v = dir.dot(qvec)*inv_det;
//	if (v<0.0 || v>1.0)
//		return 0;
//
//	t = edge2.dot(qvec)*inv_det;
//#endif
//if(barycentricCoord)
//{
//	p.x = 1.0 - u - v;
//	p.y = u;
//	p.z = v;	
//}	
//else
//{
//	p.x = (1.0 - u - v)*v0.position.x + u*v1.position.x + v*v2.position.x;
//	p.y = (1.0 - u - v)*v0.position.y + u*v1.position.y + v*v2.position.y;
//	p.z = (1.0 - u - v)*v0.position.z + u*v1.position.z + v*v2.position.z;
//}
//	return true;
//}
//
//Vec3f TriangleFace::GetNormal(const Vec3f & p) const
//{
//	//TODO avg of the vertex normals;
//	return Vec3f();
//}
