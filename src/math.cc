#include "math.hh"

namespace msr{

float frac(float t) {
    float r = t - (int)t;
    if(r < 0.f)
        r = 1.0f - std::abs(r);

    return r;
}

float gamma(float x){
    return pow(x,1.0/2.2);
}

//求反射向量
vec3 reflect(const vec3& I, const vec3& N)
{
	//公式 R = I - 2(I·N)N
	return I - 2.f * (I * N) * N;
	 
}

vec3 cross(const vec3& v1, const vec3& v2) {
    return vec3{ v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z, v1.x * v2.y - v1.y * v2.x };
}

vec3 normalized(const vec3& v) {
    vec3 ret(v.x, v.y, v.z);
    ret.normalize();
    return ret;
}

vec3 barycentric(vec3& A, vec3& B, vec3& C, vec3& p) {
    vec3 xvec(C.x - A.x, B.x - A.x, A.x - p.x);
    vec3 yvec(C.y - A.y, B.y - A.y, A.y - p.y);
    vec3 u = cross(xvec, yvec);
    if(std::abs(u.z) < 0.999f)
        return vec3(-1, 1, 1); 

    return vec3(1.f - (u.x + u.y) / u.z, u.y / u.z, u.x / u.z);
}

mat4 getIdentityMatrix() {
    mat4 ret;
    for(int i = 0; i < 4; ++i)
        for(int j = 0; j < 4; ++j)
            ret[i][j] = (i == j ? 1.0f : 0.0f);
    return ret;
}

mat4 getTranslateMatrix(float x, float y, float z) {
    mat4 ret = getIdentityMatrix();
    ret[0][3] = x;
    ret[1][3] = y;
    ret[2][3] = z;
    return ret;
}

mat4 getScaleMatrix(float x, float y, float z) {
    mat4 ret = getIdentityMatrix();
    ret[0][0] = x;
    ret[1][1] = y;
    ret[2][2] = z;
    return ret;
}

mat4 inverse(mat4 m){
    float arr[4][4];
    for(int i = 0;i < 4; i++)
		for(int j = 0;j < 4; j++)
            arr[i][j] = m[i][j];

    return Gaussian_elimination_mat4(arr);
}

//使用高斯消元法对矩阵进行求逆
mat4 Gaussian_elimination_mat4(float (*arr)[4])
{
    constexpr int N = 4;
	int i, j, k;
	float W[N][2*N];
	float tem_1, tem_2, tem_3;

    mat4 result;
 
	// 对矩阵右半部分进行扩增
	for(i = 0;i < N; i++){
		for(j = 0;j < 2 * N; j++){
			if(j<N){
				W[i][j] = (float) arr[i][j];
			}
			else{
				W[i][j] = (float) (j-N == i ? 1:0);
			}
		}
	}
 
	for(i=0;i<N;i++)
	{
		// 判断矩阵第一行第一列的元素是否为0，若为0，继续判断第二行第一列元素，直到不为0，将其加到第一行
		if( ((int) W[i][i]) == 0)
		{ 
			for(j=i+1;j<N;j++)
			{
				if( ((int) W[j][i]) != 0 ) break;
			}
			if(j == N)
			{
				printf("这个矩阵不能求逆");
				break;
			}
			//将前面为0的行加上后面某一行
			for(k=0;k<2*N;k++)
			{
				W[i][k] += W[j][k];
			}
		}
 
		//将前面行首位元素置1
		tem_1 = W[i][i];
		for(j=0;j<2*N;j++)
		{
			W[i][j] = W[i][j] / tem_1;
		}
 
		//将后面所有行首位元素置为0
		for(j=i+1;j<N;j++)
		{
			tem_2 = W[j][i];
			for(k=i;k<2*N;k++)
			{
				W[j][k] = W[j][k] - tem_2 * W[i][k];
			}
		}
	}
 
	// 将矩阵前半部分标准化
	for(i=N-1;i>=0;i--)
	{
		for(j=i-1;j>=0;j--)
		{
			tem_3 = W[j][i];
			for(k=i;k<2*N;k++)
			{
				W[j][k] = W[j][k] - tem_3*W[i][k];
			}
		}
	}
 
	//得出逆矩阵
	for(i=0;i<N;i++)
	{
		for(j=N;j<2*N;j++)
		{
			result[i][j-N] = W[i][j];
		}
	}

	return result;
}

mat4 transpose(mat4 m){

    mat4 t;

    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            t[i][j] = m[i][j];
        }
    }

    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            m[i][j] = t[j][i];
        }
    }

    return m;
}

mat4 lookat(vec3 eye, vec3 target, vec3 upd) {
    mat4 ret = getIdentityMatrix();

    vec3 forward = eye - target;
    forward.normalize();

    vec3 left = cross(upd,forward);
    left.normalize();

    vec3 up = cross(forward,left);
    up.normalize();

    ret[0][0] = left.x;
    ret[1][0] = left.y;
    ret[2][0] = left.z;
    ret[0][1] = up.x;
    ret[1][1] = up.y;
    ret[2][1] = up.z;
    ret[0][2] = forward.x;
    ret[1][2] = forward.y;
    ret[2][2] = forward.z;

    ret[0][3] = -left.x * eye.x - left.y * eye.y - left.z * eye.z;
    ret[1][3] = -up.x * eye.x - up.y * eye.y - up.z * eye.z;
    ret[2][3] = -forward.x * eye.x - forward.y * eye.y - forward.z * eye.z;


    return ret;
}

mat4 perspective(float fov, float aspect, float znear, float zfar) {
    float fax = 1.0f / (float)tan(fov * 0.5f);
    mat4 ret = getIdentityMatrix();
    ret[0][0] = fax / aspect;
    ret[1][1] = fax;
    ret[2][2] = zfar / (zfar - znear);
    ret[3][2] = -znear * zfar / (zfar - znear);
    ret[2][3] = 1.f;
    return ret;
}

};