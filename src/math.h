static f32
Square(f32 n)
{
	return n*n;
}

static f32
Sqrt(f32 n)
{
	return sqrtf(n);
}

typedef struct V2
{
	f32 x;
	f32 y;
} V2;

#define V2(X, Y) (V2){ .x = (X), .y = (Y) }

static V2
V2_Add(V2 a, V2 b)
{
	return V2(a.x + b.x, a.y + b.y);
}

static V2
V2_Sub(V2 a, V2 b)
{
	return V2(a.x - b.x, a.y - b.y);
}

static V2
V2_Hadamard(V2 a, V2 b)
{
	return V2(a.x * b.x, a.y * b.y);
}

static V2
V2_Scale(V2 v, f32 n)
{
	return V2(v.x*n, v.y*n);
}

static V2
V2_ScaleRes(V2 v, f32 n)
{
	return V2(v.x/n, v.y/n);
}

f32
V2_Inner(V2 a, V2 b)
{
	return a.x*b.x + a.y*b.y;
}

f32
V2_Len(V2 v)
{
	return Sqrt(V2_Inner(v, v));
}

static V2
V2_Normalize(V2 v)
{
	return V2_ScaleRes(v, V2_Len(v));
}

typedef struct V2S
{
	s32 x;
	s32 y;
} V2S;

#define V2S(X, Y) (V2S){ .x = (X), .y = (Y) }

static V2S
V2S_Add(V2S a, V2S b)
{
	return V2S(a.x + b.x, a.y + b.y);
}

static V2S
V2S_Sub(V2S a, V2S b)
{
	return V2S(a.x - b.x, a.y - b.y);
}

static V2S
V2S_Hadamard(V2S a, V2S b)
{
	return V2S(a.x * b.x, a.y * b.y);
}

static V2S
V2S_Scale(V2S v, f32 n)
{
	return V2S(v.x*n, v.y*n);
}

static V2S
V2S_ScaleRes(V2S v, f32 n)
{
	return V2S(v.x/n, v.y/n);
}

static s32
V2S_Inner(V2S a, V2S b)
{
	return a.x*b.x + a.y*b.y;
}
